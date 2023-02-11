# -*- encoding: utf-8 -*-

# Flask modules
from flask   import render_template, request, session, abort
from jinja2  import TemplateNotFound

# App modules
from apps import app

# other modules
#from myproject import app,db
from flask import render_template, url_for, redirect

from flask_wtf import FlaskForm
from wtforms import StringField, HiddenField, validators

from wtforms import PasswordField
from .models import User
from hashlib import sha256

from flask_login import login_user , current_user
from flask_login import logout_user

from flask_login import login_required

# App main route + generic routing

@app.route('/', defaults={'path': 'index.html'})
@app.route('/<path>')
def index(path):

    #try:
        if 'attempt' not in session:
            session['attempt'] = 2
        # Detect the current page
        segment = get_segment( request )

        # Serve the file (if exists) from app/templates/home/FILE.html
        return render_template( 'home/' + path, segment=segment )
    
    #except TemplateNotFound:
        #return render_template('home/page-404.html'), 404
        #return redirect(url_for('not_found'))
"""
@app.route('/')
def index():
    if 'attempt' not in session:
        session['attempt'] = 2

    try:

        # Serve the file (if exists) from app/templates/home/FILE.html
        return render_template('home/index.html')
    
    except TemplateNotFound:
        return render_template('home/page-404.html'), 404
"""

@app.route('/about')
def about():

    #try:

        # Serve the file (if exists) from app/templates/home/FILE.html
        return render_template('home/about.html')
    
    #except TemplateNotFound:
        #return render_template('home/page-404.html'), 404

@app.route('/dashboard')
@login_required
def dashboard():

    #try:
        return render_template('home/dashboard.html')
    
    #except TemplateNotFound:
        #return render_template('home/page-404.html'), 404

@app.route('/login', methods=["GET","POST"])
def login():

    if not current_user.is_authenticated:
        if session['attempt'] <= 0:
            #troll song redirection on youtube
            return redirect('https://www.youtube.com/watch?v=gkTb9GP9lVI')
        try:
            f = LoginForm()
            if not f.is_submitted():
                f.next.data = request.args.get("next")
            elif f.validate_on_submit():
                user = f.get_authenticated_user()
                if user:
                    login_user(user)
                    next = f.next.data or url_for("dashboard")
                    return redirect(next)
                else:
                    session['attempt'] -= 1
                    return render_template('home/login.html', msg='Wrong user or password: left ' + str(session['attempt'] + 1) + ' attempt(s)' ,form=f)
            return render_template('home/login.html', form=f)

        except TemplateNotFound:
            return render_template('home/page-404.html'), 404
    else:
        return redirect(url_for('dashboard'))

@app.route('/logout')
def logout():
    logout_user()
    return redirect(url_for('dashboard'))
    
@app.route('/heatmap')
@login_required
def heatmap():
    #data = 20
    return render_template('home/map-google.html')

def get_segment( request ): 

    try:

        segment = request.path.split('/')[-1]

        if segment == '':
            segment = 'index'

        return segment    

    except:
        return None  

class LoginForm(FlaskForm):
    username = StringField('Username')
    password = PasswordField('Password')
    next = HiddenField()
    def get_authenticated_user(self):
        user = User.query.get(self.username.data)
        if user is None:
            return None
        m = sha256()
        m.update(self.password.data.encode())
        passwd = m.hexdigest()
        return user if passwd == user.password else None

# Error handling

@app.route('/not_found')
def not_found():
    #abort(404)
    return render_template('home/page-404.html'), 404

@app.errorhandler(403)
def forbidden(e):
    return render_template('home/page-403.html'), 403

@app.errorhandler(404)
def page_not_found(e):
    #return render_template('home/page-404.html'), 404
    redirect(url_for('not_found'))

"""
# app.errorhandler(404) with rickroll video redirection on youtube
@app.errorhandler(404)
def page_not_found(e):
    return redirect('https://www.youtube.com/watch?v=dQw4w9WgXcQ')
"""

@app.errorhandler(500)
def internal_server_error(e):
    return render_template('home/page-500.html'), 500