from flask import request
from flask_restful import Resource
from Listeners.HttpListener import HTTPListener

http_listener = HTTPListener("HTTPListener", 8080)

class Listeners(Resource):

    def get(self):
        http_listener.start()
        return "Listener started", 200

    def post(self):
        http_listener.stop()
        return "Listener stopped", 200