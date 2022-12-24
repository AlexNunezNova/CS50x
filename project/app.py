from __future__ import print_function
from cs50 import SQL
from flask import Flask, redirect, render_template, request
from mailmerge import MailMerge

from helpers import apology

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
def index():
    """Show main page"""

    # show page
    if request.method == "GET":
        # use test variable to check how info is displayed or built in the page
        test = ":)"

        return render_template("index.html")


@app.route("/nda", methods=["GET", "POST"])
def nda():
    """Show form for contract"""
    fieldsList = ["fecha_acuerdo", "nombre_cliente", "rut_cliente", "domicilio_cliente", "comuna_cliente",\
        "ciudad_cliente", "nombre_proveedor", "rut_proveedor", "domicilio_proveedor", "comuna_proveedor",\
            "ciudad_proveedor", "descripción_servicios"]

    # Show form with all the fields in the list
    if request.method == "GET":
         return render_template("nda.html", fieldsList=fieldsList)

    # Use MailMerge to get fields from document
    with MailMerge('templates/Acuerdo de Confidencialidad Tipo Proveedor.docx') as document:
        print(document.get_merge_fields())

        document.merge(
            fecha_acuerdo = request.form.get("fecha_acuerdo"),
            nombre_cliente = request.form.get("nombre_cliente"),
            rut_cliente = request.form.get("rut_cliente"),
            domicilio_cliente = request.form.get("domicilio_cliente"),
            comuna_cliente = request.form.get("comuna_cliente"),
            ciudad_cliente = request.form.get("ciudad_cliente"),
            nombre_proveedor = request.form.get("nombre_proveedor"),
            rut_proveedor = request.form.get("rut_proveedor"),
            domicilio_proveedor = request.form.get("domicilio_proveedor"),
            comuna_proveedor = request.form.get("comuna_proveedor"),
            ciudad_proveedor = request.form.get("ciudad_proveedor"),
            descripción_servicios = request.form.get("descripción_servicios")
        )

        document.write('Output.docx')

    return redirect("/")

@app.route("/about", methods=["GET", "POST"])
def about():
    return apology("Página en construcción")
