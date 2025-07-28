from cs50 import SQL
from flask import request,Flask,render_template,jsonify,sessions
# from flask_session import Session

app = Flask(__name__)

db = SQL('sqlite:///movies.db')

'''
app.config['SESSION_PERMANENT'] = False
app.config['SESSION_TYPE'] = 'filesystem'
Session(app)
'''

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/search')
def search():
    # If the query exists:
    if request.args.get('q'):
        show_details = db.execute('SELECT * FROM movies WHERE title like (?) LIMIT 25',('%' + request.args.get('q') + '%'))
        return render_template('search.html',show_details = show_details)

@app.route('/autocomplete')
def autocomplete():
    if request.args.get('q'):
        show_details = db.execute('SELECT * FROM movies WHERE title like (?) LIMIT 25',('%' + request.args.get('q') + '%'))
    return jsonify(show_details)
