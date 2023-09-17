from flask import Flask, request
from flask_restful import Api
from multiprocessing import Process
from Resources.Listeners import Listeners

class coreC2():
    def __init__(self):
        self.app = Flask("Core")
        self.api = Api(self.app)
        self.api.add_resource(Listeners, '/listener', endpoint='listener')
        self.server_process = None
        
    def start(self):
        if self.server_process is None:
            self.server_process = Process(target=self.run_server)
            self.server_process.start()
            print("C2 server started.")
        else:
            print("C2 server is already running.")

    def run_server(self):
        self.app.run(host='127.0.0.1', port='8888', debug=True, use_reloader=False)

    def stop(self):
        if self.server_process:
            print("Stopping C2 server...")
            self.server_process.terminate()
            self.server_process = None
            print("C2 server stopped.")
        else:
            print("C2 server is not running.")