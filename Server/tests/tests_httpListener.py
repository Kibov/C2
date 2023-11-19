import unittest
from Listeners.HttpListener import HTTPListener

class SingletonTest(unittest.TestCase):

    def test_singleton_instance(self):
        instance1 = HTTPListener("test", "1337")
        instance2 = HTTPListener("t", "1338")
        self.assertIs(instance1, instance2)

if __name__ == '__main__':
    unittest.main()