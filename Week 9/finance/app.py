from cs50 import SQL
from flask import Flask, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash
from datetime import datetime

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
    if session["user_id"]:
        portfolio = db.execute(
            "SELECT ticker,quantity FROM stocks WHERE id = ? ORDER BY quantity ASC", session["user_id"])
        balance = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]['cash']

        # Current prices of each stock held
        ticker = db.execute(
            "SELECT ticker FROM stocks WHERE id = ? ORDER BY quantity ASC", session["user_id"])
        current_prices = []
        for dict in ticker:
            current_prices.append(lookup(dict['ticker'])["price"])

        i, total_holdings = 0, 0
        for dict in portfolio:
            total_holdings += current_prices[i]*dict['quantity']
            i += 1
        total_holdings += balance

        return render_template("portfolio.html", portfolio=portfolio, balance=balance, current_prices=current_prices, total_holdings=total_holdings)


@app.route("/add_cash", methods=["POST", "GET"])
@login_required
def add_cash():
    if request.method == "POST":
        if not request.form.get('deposit'):
            return apology("Amount Required!")

        deposit = request.form.get('deposit').strip()
        try:
            float(deposit)
        except ValueError:
            return apology("Enter a real number")
        deposit = float(deposit)
        if deposit <= 0:
            return apology("Deposit is positive")

        # Depositing cash in db
        db.execute("UPDATE users SET cash = cash + ? WHERE id = ?", deposit, session["user_id"])
        return redirect('/')

    else:
        return render_template("deposit.html")


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    if request.method == "POST":
        if not request.form.get('symbol'):
            return apology("Enter a ticker symbol")
        elif not request.form.get('shares'):
            return apology("Invalid Number of Units")

        # Validity of the ticker symbol
        units = request.form.get('shares').strip()
        ticker_symbol = request.form.get('symbol').upper()
        quote = lookup(ticker_symbol)
        if not quote or not units.isnumeric():
            return apology("Invalid Ticker Symbol/Units")

        # Validity of the number of units
        units = int(units)
        unit_price = float(quote['price'])
        purchase_price = units*unit_price
        balance = (db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"]))[0]['cash']
        if (purchase_price > balance):
            return apology("Insufficient Balance!")

        # Purchasing the stock.
        db.execute("INSERT INTO stocks (id,ticker,quantity) VALUES(?,?,?) ON CONFLICT(id,ticker) DO UPDATE SET quantity = quantity + ?",
                   session["user_id"], ticker_symbol, units, units)
        db.execute("UPDATE users SET cash = ? WHERE id = ?",
                   balance-purchase_price, session["user_id"])

        # Updating the history
        db.execute("INSERT INTO history (id,ticker,price,logtime,quantity) VALUES(?,?,?,?,?)",
                   session["user_id"], ticker_symbol, unit_price, datetime.now(), units)

        return redirect('/')

    else:
        return render_template("buy.html")


@app.route("/history", methods=["GET", "POST"])
@login_required
def history():
    if request.method == "POST":
        return redirect("/buy")
    else:
        history = db.execute(
            "SELECT ticker,price,quantity,logtime FROM history WHERE id = ? ORDER BY logtime ASC", session["user_id"])
        return render_template("history.html", history=history)


@app.route("/login", methods=["GET", "POST"])
def login():
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
            # Beware of trailing and leading whitespaces.
            "SELECT * FROM users WHERE username = ?", request.form.get("username").strip()
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
    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    if request.method == "POST":
        # Input validation
        if request.form.get('symbol'):
            quote = lookup(request.form.get('symbol'))
            if quote:
                return render_template("quote.html", quote=quote)
            else:
                return apology("Invalid Ticker Symbol")

        else:
            return apology("Enter a ticker symbol")

    else:
        return render_template("quote_form.html")


@app.route("/register", methods=["GET", "POST"])
def register():

    if request.method == 'POST':
        # Input Validation
        if not request.form.get('username'):
            return apology("Enter a username")
        elif not request.form.get('password'):
            return apology("Enter a password")
        elif not (request.form.get('password') == request.form.get('confirmation')):
            return apology("Passwords Didn't Match")

        # Check username duplication.
        username = request.form.get('username')
        duplication_value = db.execute(
            "SELECT count(username) FROM users WHERE username = ?", username)

        if duplication_value[0]['count(username)']:
            return apology("Username Exists!", 400)

        # Populate database with user credentials.
        pass_hash = generate_password_hash(request.form.get('password'))
        username = request.form.get('username')

        db.execute("INSERT INTO users (username,hash) VALUES(?,?)", username, pass_hash)
        session["user_id"] = db.execute(
            "SELECT id FROM users WHERE username = ?", username.strip())[0]['id']
        return redirect('/')

    else:
        return render_template("registration.html")


@app.route("/delete_account", methods=["GET", "POST"])
@login_required
def delete_account():
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute(
            # Beware of trailing and leading whitespaces.
            "SELECT * FROM users WHERE username = ?", request.form.get("username").strip()
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 403)

        # Delete all data
        db.execute("DELETE FROM stocks WHERE id = ?", session["user_id"])
        db.execute("DELETE FROM history WHERE id = ?", session["user_id"])
        db.execute("DELETE FROM users WHERE id = ?", session["user_id"])
        # Remove Session(logout)
        session.clear()

        return redirect("/")

    else:
        return render_template("delete_account.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    ticker_data = db.execute(
        "SELECT ticker FROM stocks WHERE id = ? ORDER BY quantity ASC", session["user_id"])

    if request.method == "POST":
        if not request.form.get('symbol'):
            return apology("Enter a valid ticker symbol")
        elif not request.form.get('shares'):
            return apology("Enter valid number of units to be sold")

        # Validate if the ticker in list
        present, ticker = 0, request.form.get('symbol').strip().upper()
        for row in ticker_data:
            if ticker == row['ticker']:
                present = 1
        if not present:
            return apology("Invalid Ticker Symbol")

        # Validate if the stocks to sell is a valid number and less than or equal to holdings
        units_to_sell = request.form.get('shares')
        if not units_to_sell.isnumeric():
            return apology("Invalid number of units to sell")
        else:
            units_to_sell = int(units_to_sell)

        max_units = db.execute("SELECT quantity FROM stocks WHERE id = ? AND ticker = ?",
                               session["user_id"], ticker)[0]['quantity']
        if units_to_sell > max_units:
            return apology("Cannot Sell more than what you have!")

        elif units_to_sell == max_units:
            db.execute("DELETE FROM stocks WHERE id = ? AND ticker = ?", session["user_id"], ticker)

        else:
            db.execute("UPDATE stocks SET quantity = ? WHERE id = ? AND ticker = ?",
                       max_units-units_to_sell, session["user_id"], ticker)

        current_value = lookup(ticker)['price']
        balance = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]['cash']
        db.execute("UPDATE users SET cash = ? where id = ?", balance +
                   current_value * units_to_sell, session["user_id"])

        # Solve race conditions

        # Update history
        db.execute("INSERT INTO history (id,ticker,price,logtime,quantity) VALUES(?,?,?,?,?)",
                   session["user_id"], ticker, current_value, datetime.now(), -1*units_to_sell)
        return redirect('/')

    else:
        return render_template("sell.html", ticker=ticker_data)
