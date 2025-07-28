from flask import Flask, render_template, request, session, redirect
from flask_session import Session

app = Flask(__name__)

app.config['SESSION_PERMANENT'] = False
app.config['SESSION_TYPE'] = 'filesystem'
Session(app)

@app.route('/')
def index():
    return render_template('index.html', mail = session.get('mail'))


@app.route('/login',methods = ['POST','GET'])
def login():
    if request.method == 'POST':
        session['mail'] = request.form.get('mail')
        return redirect('/')

    return render_template('login.html', name = request.form.get('name'))

@app.route('/logout')
def logout():
    session.clear()
    return redirect('/')
