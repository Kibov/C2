from flask import Flask, request
from flask_restful import Api
from multiprocessing import Process
from Resources.Tasks import Tasks
from threading import Lock

class SingletonMeta(type):
    #Thread safe Singleton
    _instances = {}

    _lock: Lock = Lock()

    def __call__(cls, *args, **kwargs):
        with cls._lock:
            if cls not in cls._instances:
                instance = super().__call__(*args, **kwargs)
                cls._instances[cls] = instance
        return cls._instances[cls]


class HTTPListener(metaclass=SingletonMeta):

    def __init__(self, name: str, port: str):
        self.name = name
        self.port = port
        self.app = Flask(name)
        self.api = Api(self.app)
        self.api.add_resource(Tasks, '/tasks', endpoint='tasks')
        self.server_process = None

    def start(self):
        if self.server_process is None:
            self.server_process = Process(target=self.run_server)
            self.server_process.start()
            print(f"{self.name} - HTTP server started.")
        else:
            print("HTTP server is already running.")

    def run_server(self):
        self.app.run(host='127.0.0.2', port=self.port, debug=True, use_reloader=False)

    def stop(self):
        if self.server_process:
            print("Stopping HTTP server...")
            self.server_process.terminate()
            self.server_process = None
            print("HTTP server stopped.")
        else:
            print("HTTP server is not running.")
