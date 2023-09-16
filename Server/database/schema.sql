--Used to register implants to the C2 server
DROP TABLE IF EXISTS implants;

CREATE TABLE implants (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    implant_id TEXT NOT NULL,
    ip_address TEXT NOT NULL,
    hostname TEXT,
    operating_system TEXT,
    last_seen TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP
);
--Used for sending tasks to execute to a specific implant_id
DROP TABLE IF EXISTS tasks;

CREATE TABLE tasks (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    created TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP,
    implant_id TEXT NOT NULL,
    command TEXT NOT NULL,
    executed INTEGER DEFAULT 0
);

--Stores results of the tasks executed 
DROP TABLE IF EXISTS results;

CREATE TABLE results (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    created TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP,
    implant_id TEXT NOT NULL,
    result TEXT NOT NULL
);

