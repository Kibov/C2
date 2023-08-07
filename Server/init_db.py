import sqlite3

connection = sqlite3.connect('c2data.db')

with open('schema.sql') as f:
    connection.executescript(f.read())

cur = connection.cursor()

cur.execute("INSERT INTO tasks (implant_id, command) VALUES (?, ?)", ('implant1', 'ping'))
cur.execute("INSERT INTO tasks (implant_id, command) VALUES (?, ?)", ('implant1', 'dir'))
cur.execute("INSERT INTO tasks (implant_id, command) VALUES (?, ?)", ('implant1', 'ls'))

connection.commit()
connection.close()