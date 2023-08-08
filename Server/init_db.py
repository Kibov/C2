import sqlite3

connection = sqlite3.connect('c2data.db')

with open('schema.sql') as f:
    connection.executescript(f.read())

cur = connection.cursor()

cur.execute("INSERT INTO tasks (implant_id, command) VALUES (?, ?)", ('implant1', 'ping'))
cur.execute("INSERT INTO tasks (implant_id, command) VALUES (?, ?)", ('implant3', 'dir'))
cur.execute("INSERT INTO tasks (implant_id, command) VALUES (?, ?)", ('implant4', 'ls'))
cur.execute("INSERT INTO tasks (implant_id, command, executed) VALUES (?, ?, ?)", ('implant2', 'ls', 1))

connection.commit()
connection.close()