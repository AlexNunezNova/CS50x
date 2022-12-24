import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    # show page

    if request.method == "GET":
        # determine variables to show in page
        userID = session["user_id"]
        username = db.execute("SELECT username FROM users WHERE id = ?", userID)  # added location in template
        userCash = db.execute("SELECT cash FROM users WHERE id = ?", userID)[0]["cash"]

        # define a dict to hold user stocks
        stocks = db.execute("SELECT DISTINCT stock_symbol FROM transactions WHERE user_id = ?", userID)

        # extract symbols in a list, this list is used from now on
        stockSymbols = [stock["stock_symbol"] for stock in stocks]  # notice how for loop is inside the brackets

        # use for loop to store query results
        amounts = [db.execute("SELECT SUM(amount) as total_stocks FROM transactions WHERE user_id = ? AND stock_symbol = ?", userID, stock)[
            0]["total_stocks"] for stock in stockSymbols]
        stockValues = [lookup(stock)["price"] for stock in stockSymbols]  # works in relation to stockSymbols list

        # sum all the values in list and add current cash
        # notice how for loop does not use the for stock in stocks formula
        subtotalStocks = [stockValues[stock] * amounts[stock] for stock in range(len(stockSymbols))]
        totalValue = sum([stockValues[stock] * amounts[stock] for stock in range(len(stockSymbols))])
        totalCash = totalValue + userCash

        # use test variable to check how info is displayed or built in the page
        test = ":)"

        return render_template("index.html", subtotalStocks=subtotalStocks, stockSymbols=stockSymbols, test=test, userCash=userCash, username=username, amounts=amounts, stockValues=stockValues, totalValue=totalValue, totalCash=totalCash)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    # show form at first
    if request.method == "GET":
        return render_template("buy.html")

    # look for the quote and obtain dictionary
    stockLookup = lookup(request.form.get("symbol"))
    rawShares = request.form.get("shares")  # check at data without transforming to int

    # if stock not found, return apology
    if not stockLookup:
        return apology("Stock symbol not found. Please try again")

    # validate form data (check isnumeric() documentation)
    # validating that string exists and that string obtained is not a float not a positive integer
    if not rawShares or not rawShares.isnumeric() or int(rawShares) == 0:
        return apology("Request failed. Please enter valid numeric amount")

    shares = int(rawShares)  # change str to int if validations are ok

    # look for elements for transaction: user cash, stock price and amount
    userID = session["user_id"]
    # obtain cash, execute result is a list of dict elements so add [0][key]
    userCash = db.execute("SELECT cash FROM users WHERE id = ?", userID)[0]["cash"]

    stockPrice = stockLookup["price"]

    # if money is not enough for purchase, return apology
    if stockPrice * shares > userCash:
        return apology("Not enough cash to perform this operation")

    # otherwise, register purchase
    remainingCash = userCash - (stockPrice * shares)
    db.execute("UPDATE users SET cash = ? WHERE id = ?", remainingCash, userID)
    db.execute("INSERT INTO transactions (user_id, operation, stock_symbol, amount)\
        VALUES (?, ?, ?, ?)", userID, "Buy", stockLookup["symbol"], shares)

    # go back to the main page
    return redirect("/")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    # show page at first
    if request.method == "GET":
        userID = session["user_id"]
        username = db.execute("SELECT username FROM users WHERE id = ?", userID)[0]["username"]

        # use log dictionary to fill in table directly in html
        log = db.execute("SELECT stock_symbol, operation, amount, time FROM transactions WHERE user_id = ?", userID)

        test = ":)"
    return render_template("history.html", test=test, username=username, log=log)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""

    # show form at first
    if request.method == "GET":
        return render_template("quote.html")

    # create variable to store dictionary obtained from quote
    stockLookup = lookup(request.form.get("symbol"))

    if not stockLookup:
        return apology("Stock Symbol not found. Please try again")

    # if search is successful, show in html with dictionary results
    else:
        quotefound = True
        return render_template("quote.html", quotefound=quotefound, stockLookup=stockLookup)  # dictionary divided in template


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    # first: show html page at the beginning (will access via GET)

    if request.method == "GET":
        return render_template("register.html")

    username = request.form.get("username")
    password = request.form.get("password")
    confirmation = request.form.get("confirmation")
    users = db.execute("SELECT username FROM users")
    hash = generate_password_hash(password)

    userlist = [user["username"] for user in users]

    if username in userlist:
        return apology("Username already exists. Please try again")

    elif not username:
        return apology("Username not provided. Please try again")

    elif password != confirmation:
        return apology("Password does not match confirmation. Please try again")

    # added extra length verification
    elif not password or len(password) < 8:
        return apology("Password not provided or not long enough. Please try again")

    else:
        db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", username, hash)

    return redirect("/")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    # get data to show options
    userID = session["user_id"]
    userCash = db.execute("SELECT cash FROM users WHERE id = ?", userID)[0]["cash"]
    # define a dict to hold user stocks
    stocks = db.execute("SELECT DISTINCT stock_symbol FROM transactions WHERE user_id = ?", userID)
    # extract symbols in a list, this list is used from now on
    stockSymbols = [stock["stock_symbol"] for stock in stocks]  # notice how for loop is inside the brackets

    # show form
    if request.method == "GET":
        return render_template("sell.html", stockSymbols=stockSymbols)

    # create variables to store form info
    rawShares = request.form.get("shares")
    symbol = request.form.get("symbol")

    # validate form data
    # (check isnumeric() documentation)
    # validating that string exists and that string obtained is not a float not a positive integer
    if not rawShares or not rawShares.isnumeric() or int(rawShares) == 0:
        return apology("Request failed. Please enter valid numeric amount")

    if not symbol or symbol not in stockSymbols:
        return apology("Stock Symbol not found or not in wallet. Please try again")

    # if validations are ok, turn string to int
    amount = int(rawShares)

    # lookup for stock info
    stockLookup = lookup(symbol)

    # validate stock info
    if not stockLookup:
        return apology("Stock Symbol not found or not in wallet. Please try again")

    # if stock exists, validate sale info
    totalStocks = db.execute(
        "SELECT SUM(amount) as total_stocks FROM transactions WHERE user_id = ? AND stock_symbol = ?", userID, symbol)[0]["total_stocks"]
    if amount > totalStocks:
        return apology("Amount of stocks sold is bigger than stocks owned. Please insert a valid amount")

    # execute sale if everything works
    stockPrice = stockLookup["price"]
    remainingCash = userCash + (stockPrice * amount)

    # use negative integers to express sale and consider them in total sum
    saleAmount = amount * -1
    db.execute("UPDATE users SET cash = ? WHERE id = ?", remainingCash, userID)
    db.execute("INSERT INTO transactions (user_id, operation, stock_symbol, amount)\
        VALUES (?, ?, ?, ?)", userID, "Sell", stockLookup["symbol"], saleAmount)

    return redirect("/")


@app.route("/cash", methods=["GET", "POST"])
@login_required
def cash():
    """Add cash to the wallet"""
    # show page at first
    if request.method == "GET":
        return render_template("cash.html")

    userID = session["user_id"]
    cashAdded = int(request.form.get("cashAdded"))
    currentCash = db.execute("SELECT cash FROM users WHERE id = ?", userID)[0]["cash"]

    if cashAdded <= 0:
        return apology("Please enter a valid amount of cash")

    newCash = currentCash + cashAdded
    db.execute("UPDATE users SET cash = ? WHERE id = ?", newCash, userID)

    return redirect("/")
