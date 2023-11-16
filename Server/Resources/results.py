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
            cursor.execute("SELECT * FROM results")
            rows = cursor.fetchall()

            csv_string = ""

            if rows:
                for row in rows:
                    csv_string += ",".join(map(str, row)) + "\n"

            conn.close()
            return csv_string, 200


        except Exception as e:
            print(str(e))
            return {"Error": str(e)}, 500

    def post(self):

        try:

            data = request.get_data().decode().split(',,')
            task_id = data[0]
            result = data[1]
            print(f'{task_id},\n{result},\n{data}')
            conn = get_db_connection()
            cursor = conn.cursor()
            cursor.execute("INSERT INTO results (tasks_task_id, result) VALUES (?, ?)", (task_id, result))
            #Set the executer = 1 to the most recent task
            cursor.execute("UPDATE tasks SET executed = 1 WHERE task_id = ?", (task_id,))
            conn.commit()
            conn.close()
            return "Result added", 201

        except Exception as e:
            print(str(e))
            return {"Error": str(e)}, 500