import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


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

    user_id = session["user_id"]

    cash = db.execute("SELECT * FROM users WHERE id=?;", user_id)[0]["cash"]
    stock_total = 0

    owned_stocks_data = db.execute("SELECT * FROM owned_stocks WHERE user_id=?;", user_id)

    table_data=[]

    for row in owned_stocks_data:
        lookup_result = lookup(row["symbol"])
        stock_current_value = lookup_result["price"]
        print(stock_current_value)
        shares_owned = row["amount"]
        total_value = stock_current_value * shares_owned

        stock_total += total_value

        row_data = {
            "symbol": lookup_result["symbol"],
            "name": lookup_result["name"],
            "shares": shares_owned,
            "price": usd(stock_current_value),
            "total": usd(total_value),
        }

        table_data.append(row_data)

    return render_template("index.html", balance=usd(cash), grand_total=usd(cash+stock_total), table_data=table_data)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        symbol = request.form.get("symbol")
        result = lookup(symbol)

        if not result:
            return apology("Invalid symbol")

        shares = request.form.get("shares")

        if not shares:
            return apology("No amount of shares")
        
        try:
            shares = float(shares)
            if shares < 0 or shares%1 != 0:
                raise ValueError
            shares = int(shares)
        except ValueError:
            return apology("Invalid number of shares")
        
        unit_cost = result["price"]
        total_cost = shares * unit_cost

        user_id = session["user_id"]

        user_funds = db.execute("SELECT * FROM users WHERE id=?;", user_id)[0]["cash"]

        if total_cost > user_funds:
            return apology("Insufficient funds")
        
        db.execute("INSERT INTO transactions (user_id, symbol, amount, unit_price) VALUES (?, ?, ?, ?)", 
                        user_id,
                        result["symbol"], 
                        shares,
                        unit_cost,)
        
        # insert this into the owned_stocks table. If the pair of id/stock exists, update the value
        # if not add a new value
        # excluded.amount is the value we tried to add before the conflict
        db.execute("""
            INSERT INTO owned_stocks (user_id, symbol, amount)
            VALUES (?, ?, ?)
            ON CONFLICT(user_id, symbol)
            DO UPDATE SET amount = amount + excluded.amount
        """, user_id, result["symbol"], shares)


        new_funds = round(user_funds - total_cost, 2)
        db.execute("UPDATE users SET cash=? WHERE users.id = ?", new_funds, user_id)
        
        return redirect("/")

    return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    user_id = session["user_id"]
    transaction_data = db.execute("SELECT * FROM transactions WHERE user_id=? ORDER BY time DESC", user_id)

    history = []

    for row in transaction_data:
        symbol = row["symbol"]
        shares = row["amount"]

        event = {
            "transaction": "Buy" if shares > 0 else "Sell",
            "symbol": symbol,
            "name": lookup(symbol)["name"],
            "price": usd(row["unit_price"]),
            "shares": abs(shares),
            "time": row["time"],
        }
        
        history.append(event)

    return render_template("history.html", history=history)


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
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
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
    if request.method == "POST":
        symbol = request.form.get("symbol")
        if not symbol:
            return apology("No symbol")
        
        result = lookup(symbol)
        if not result:
            return apology("Invalid symbol")
    
        name = result["name"]
        price = usd(result["price"])
        symbol = result["symbol"]
        return render_template("quoted.html", name=name, price=price, symbol=symbol)
        
    return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    if request.method == "POST":

        username = request.form.get("username")

        if not username:
            return apology("No username")

        password1 = request.form.get("password")
        password2 = request.form.get("confirmation")

        if not password1:
            return apology("No password entered")
        if not password2:
            return apology("Didn't confirm password")
        if password1 != password2:
            return apology("Passwords don't match")
        

        try:
            db.execute("INSERT INTO users (username, hash) VALUES (?, ?);", username, generate_password_hash(password1))
        except ValueError:
            return apology("Username taken")
        pass

        return redirect("/")
        

    return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    if request.method=="POST":
        symbol = request.form.get("symbol")

        if not symbol:
            return apology("No stock symbol")
        
        result = lookup(symbol)

        if not result:
            return apology("Invalid stock symbol")

        shares = request.form.get("shares")

        if not shares:
            return apology("No amount of shares")
        
        try:
            shares = float(shares)
            if shares < 0 or shares%1 != 0:
                raise ValueError
            shares = int(shares)
        except ValueError:
            return apology("Invalid number of shares")
        
        user_id = session["user_id"]

        currently_owned_shares = db.execute("SELECT * FROM owned_stocks WHERE user_id=? AND symbol=?;", user_id, result["symbol"])[0]["amount"]

        if shares > currently_owned_shares:
            return apology("Not enough shares owned")


        unit_value = result["price"]
        total_value = unit_value * shares

        db.execute("INSERT INTO transactions (user_id, symbol, amount, unit_price) VALUES (?, ?, ?, ?);", 
                   user_id, 
                   result["symbol"], 
                   -shares,  
                   unit_value,)
        
        new_shares = currently_owned_shares - shares
        
        if new_shares == 0:
            db.execute("DELETE FROM owned_stocks WHERE user_id=? AND symbol=?",
                       user_id, 
                       result["symbol"],)
        else:
            db.execute("UPDATE owned_stocks SET amount=? WHERE user_id=? AND symbol=?",
                   new_shares,
                   user_id, 
                   result["symbol"],)

        db.execute("UPDATE users SET cash=cash+? WHERE id=?;", total_value, user_id)
        
        return redirect("/")

    user_id = session["user_id"]
    owned_stocks_data = db.execute("SELECT * FROM owned_stocks WHERE user_id=?", user_id)
    return render_template("sell.html", owned_stocks_data=owned_stocks_data)

@app.route("/password", methods=["GET", "POST"])
@login_required
def change_password():
    if request.method=="POST":
        old = request.form.get("old")
        if not old:
            return apology("No old password entered")
        

        user_id = session["user_id"]
        rows = db.execute("SELECT * FROM users WHERE id=?", user_id)
        
        if not check_password_hash(rows[0]["hash"], old):
            return apology("Incorrect old password")

        new1 = request.form.get("password")
        new2 = request.form.get("confirmation")

        if not new1:
            return apology("No new password entered")
        if not new2:
            return apology("Didn't confirm new password")
        if new1 != new2:
            return apology("Passwords don't match")

        db.execute("UPDATE users SET hash=? WHERE id=?;", generate_password_hash(new1), user_id)

        return redirect("/")

    return render_template("password.html")