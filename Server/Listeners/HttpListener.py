from flask import Flask, request
from flask_restful import Api, Resource
from multiprocessing import Process
from Resources.Tasks import Tasks


class HTTPListener:
    def __init__(self):
        self.app = Flask(__name__)
        self.api = Api(self.app)
        self.api.add_resource(Tasks, '/tasks', endpoint='tasks')
        self.server_process = None

    def start(self):
        if self.server_process is None:
            self.server_process = Process(target=self.app.run)
            self.server_process.start()
            print("HTTP server started.")
        else:
            print("HTTP server is already running.")

    def stop(self):
        if self.server_process:
            print("Stopping HTTP server...")
            self.server_process.terminate()
            self.server_process.join()
            self.server_process = None
            print("HTTP server stopped.")
        else:
            print("HTTP server is not running.")