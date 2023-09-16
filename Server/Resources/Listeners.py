from flask import request
from flask_restful import Resource



class Listeners(Resource):
    def get(self):
        return "ok", 200
    def post(self):
        return "ok", 200