# Imports
from flask import Flask, jsonify, url_for,request,abort
from influxdb_client import InfluxDBClient
from influxdb_client.client.write_api import SYNCHRONOUS

#-----------------INFLUXDB-----------------


token="eJt5hsSMZZJvzWZEFkrH-suU9A4zoqxwoC42alqcBryDdCqcW_cz5HX3HuJs9W0g0ziA2Tl1-hXL65x-maZ2cA=="
org="Polytech"
bucket="buttons"
url="http://localhost:8086"
secretKey = "kP9g9Qc4xcIPBJzr"


# On crée une instance de l'application Flask
app = Flask(__name__)

#------------------ BUTTONS ------------------
    

# GET requests will be blocked
@app.route('/buttons', methods=['POST'])
def post():
    """Envoi donées bouton"""

    if request.json :

        # récupération des champs obligatoires
        try :
            #key = request.json['key']
            #if key == secretKey:
            message = request.json['message']
            with InfluxDBClient(url=url, token=token, org=org) as client:
                write_api = client.write_api(write_options=SYNCHRONOUS)
                data ="starEngineOrleans buttonPressedvalue=" + str(message)
                write_api.write(bucket, org, data)
                client.close()
            #else:
                #abort(400) # bad request

        except (KeyError, TypeError, ValueError):
            abort(400) # bad request

        response=jsonify({
                'status':'ok',
                'message':message,
        })

        response.status_code=201
        return response
    else :
        # données non transmises en json : mauvais format
        abort(415)

if __name__=='__main__' :
    app.run(host='0.0.0.0')
