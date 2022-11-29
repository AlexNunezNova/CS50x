# TODO
# bring get_float from cs50
from cs50 import get_float

# create main function


def main():
    cents = getCents()

    quarters = calculateQuarters(cents)
    cents = cents - quarters * 25

    dimes = calculateDimes(cents)
    cents = cents - dimes * 10

    nickels = calculateNickels(cents)
    cents = cents - nickels * 5

    pennies = calculatePennies(cents)
    cents = cents - pennies

    print(quarters + dimes + nickels + pennies)


def getCents():
    # obtain a positive amount of cash
    while True:
        try:
            cents = get_float("Please insert your cash: ")
            if cents > 0:
                break
        except ValueError:
            print("Please enter a positive amount of cash")
    # convert to number of coins by multiplying by 100
    return cents * 100


def calculateQuarters(cents):
    # Ready: return number of quarters. Attention: convert to int to truncate and obtain coins!
    quarters = int(cents / 25)
    return quarters


def calculateDimes(cents):
    # Ready: return number of dimes
    dimes = int(cents / 10)
    return dimes


def calculateNickels(cents):
    # Ready: return number of nickels
    nickels = int(cents / 5)
    return nickels


def calculatePennies(cents):
    # Ready: return number of cents
    pennies = int(cents)
    return pennies


main()

