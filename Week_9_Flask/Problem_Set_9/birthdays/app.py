import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///birthdays.db")

@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/", methods=["GET", "POST"])
def index():
    if request.method == "POST":

        # TODO: Add the user's entry into the database
        db.execute("INSERT INTO birthdays (name, month, day) VALUES (?, ?, ?);", 
                   request.form.get("name"), 
                   request.form.get("month"), 
                   request.form.get("day"))
        return redirect("/")

    else:

        if request.args.get("birthday_id"):
            db.execute("DELETE FROM birthdays WHERE id=?;", request.args.get("birthday_id"))
            return redirect("/")

        # TODO: Display the entries in the database on index.html
        return render_template("index.html", data=db.execute("SELECT * FROM birthdays;"))