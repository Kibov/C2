from CoreC2.CoreC2 import coreC2
from Listeners.HttpListener import HTTPListener


if __name__ == "__main__":
    http_listener = HTTPListener()
    c2 = coreC2()
    c2.start()
    http_listener.start()
            #http_listener.stop()
    
