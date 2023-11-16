from flask import request
from flask_restful import Resource
from Listeners.HttpListener import HTTPListener

http_listener = HTTPListener("test", 8080)

class Listeners(Resource):

    def get(self):
        print("start http server")
        http_listener.start()
        return "OK", 200

    def post(self):
        print("stopping http server")
        http_listener.stop()
        return "Turning off HTTP", 200