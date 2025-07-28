from flask import Flask , render_template, redirect, request, session
from cs50 import SQL
from flask_session import Session

app = Flask(__name__)

db = SQL('sqlite:///store.db')

app.config['SESSION_PERMANENT'] = False
app.config['SESSION_TYPE'] = 'filesystem'
Session(app)


@app.route('/')
def index():
    books = db.execute("SELECT * FROM books")
    return render_template('index.html', books = books)

@app.route('/cart',methods = ['POST','GET'])
def cart():

    # For the first cart addition. Not required for subsequent cart addition.
    if "cart" not in session:
        session['cart'] = []
        # session = {'cart':[book_ids],other cookies if configured}

    # Essential to accept on requests sent via 'post'. (request.form - Invalid for 'get' requests.)
    if request.method == 'POST':
        book_id = request.form.get('id')
        if book_id: #Server-side evaluation.
            session['cart'].append(book_id)
        return redirect('/cart')

    # If just viewing the cart.
    books = db.execute('SELECT name FROM books WHERE id in (?)',session['cart'])
    return render_template('cart.html', books = books)


@app.route('/clearcart',methods = ['POST',"GET"])
def clearcart():
    session.clear()
    return redirect('/')
