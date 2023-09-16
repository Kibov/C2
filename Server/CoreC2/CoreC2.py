from flask import Flask, request
from flask_restful import Api
from multiprocessing import Process
from Resources.Listeners import Listeners

class coreC2():
    def __init__(self):
        self.app = Flask("C2")
        self.api = Api(self.app)
        self.api.add_resource(Listeners, '/listeners', endpoint='listeners')
        self.server_process = None

    def start(self):
        if self.server_process is None:
            self.server_process = Process(target=self.run_server)
            self.server_process.start()
            
    def run_server(self):
        self.app.run(host='127.0.0.1', port='8888', debug=True)
        print("C2 server process has terminated.")