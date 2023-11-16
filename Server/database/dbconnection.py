import sqlite3

def get_db_connection():
    conn = sqlite3.connect(r'/home/kibov/C2Server/c2data.db')
    conn.row_factory = sqlite3.Row
    return conn