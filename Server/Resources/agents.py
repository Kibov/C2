#TODO
import os
from random import choice
from string import ascii_lowercase

import flask
from flask import request
from flask_restful import Resource
from database.dbconnection import get_db_connection

class agents(Resource):

    def get(self):

        try:
            if request.remote_addr != '127.0.0.1':
                return {"Error": "Access denied"}, 403

            conn = get_db_connection()
            cursor = conn.cursor()
            cursor.execute("SELECT implant_hostname,implant_username,ip_address FROM implants")
            rows = cursor.fetchall()

            csv_string = ""

            if rows:
                for row in rows:
                    csv_string += ",".join(map(str, row)) + "\n"

            conn.close()





        except Exception as e:
            return {"Error": str(e)}, 500


    def post(self):

        try:
            hostname = request.form.get("name")
            username = ''.join(choice(ascii_lowercase) for i in range(8))
            ipaddress = request.remote_addr

            conn = get_db_connection()
            cursor = conn.cursor()
            cursor.execute("INSERT INTO implants (implant_hostname, implant_username, ip_address) VALUES (?, ?, ?)", (hostname, username, ipaddress))
            conn.commit()
            conn.close()
            return 201

        except Exception as e:
            return {"Error": str(e)}, 500