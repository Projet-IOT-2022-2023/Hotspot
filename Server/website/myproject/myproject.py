# -*- encoding: utf-8 -*-

import os.path
from flask_minify  import Minify
from flask_login import LoginManager
from flask_sqlalchemy import SQLAlchemy
from apps import app

DEBUG = app.config['DEBUG'] 

if not DEBUG:
    Minify(app=app, html=True, js=False, cssless=False)

app.logger.info('DEBUG            = ' + str( DEBUG )                 )
app.logger.info('Page Compression = ' + 'FALSE' if DEBUG else 'TRUE' )
app.logger.info('ASSETS_ROOT      = ' + app.config['ASSETS_ROOT']    )


def mkpath(p):
        """
         renvoie chemin complet du répertoire p passé en paramètre
        """
        return os.path.normpath(
                os.path.join(
                        os.path.dirname(__file__), p))

app.config['SQLALCHEMY_TRACK_MODIFICATIONS'] = True
app.config['SQLALCHEMY_DATABASE_URI'] = ('sqlite:///'
+mkpath('./users.db'))

db = SQLAlchemy(app)
login_manager = LoginManager(app)
login_manager.login_view = "login"

if __name__ == "__main__":
    app.run(host='0.0.0.0')
