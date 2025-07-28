from flask import Flask, render_template, request
from cs50 import SQL

app = Flask(__name__)

sports = ['Football','Tennis', 'Volleyball', 'Basketball']

db = SQL('sqlite:///froshims.db')

@app.route('/')
def index():
    return render_template("index.html",sports = sports)

@app.route('/register',methods = ['post'])
def register():
    name = request.form.get('name')
    sport = request.form.get('sport')

    if not name or (sport not in sports):
        return render_template('failure.html', sport = sport, sports = sports, name = name)

    # Insert the values into the database.
    db.execute('INSERT INTO registrations (name,sport) values(?,?)', name, sport)
    return render_template('success.html',name = name)

@app.route('/registrants')
def registrants():
    # registrants is a list of dictionaries.
    registrants = db.execute('SELECT name, sport FROM registrations')
    return render_template('registrants.html',registrants = registrants)
