import unittest
from CoreC2.CoreC2 import coreC2

class ListenersTest(unittest.TestCase):

    def setUp(self):
        self.app = coreC2().app
        self.app.testing = True  # Enable testing mode
        self.client = self.app.test_client()
        # Other setup if needed

    def tearDown(self):
        # Stop the application and perform any cleanup
        pass

    def test_get_listener(self):
        response = self.client.get('/listener')
        self.assertEqual(response.status_code, 200)
        self.assertIn('OK', response.get_data(as_text=True))

    def test_post_listener(self):
        response = self.client.post('/listener')
        self.assertEqual(response.status_code, 200)
        self.assertIn('Turning off HTTP', response.get_data(as_text=True))

if __name__ == '__main__':
    unittest.main()
