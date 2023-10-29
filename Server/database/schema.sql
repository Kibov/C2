--Used to register implants to the C2 server
DROP TABLE IF EXISTS implants;

CREATE TABLE implants (
    implant_id       INTEGER PRIMARY KEY,
    implant_hostname TEXT,
    implant_username TEXT,
    implant_shell    CHAR(1),
    ip_address       TEXT,
    last_seen        TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP
);


--Stores results of the tasks executed
DROP TABLE IF EXISTS results;

CREATE TABLE results (
    result_id           INTEGER PRIMARY KEY,
    created             TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP,
    result              TEXT,
    tasks_task_id       INTEGER,
    FOREIGN KEY (tasks_task_id) REFERENCES tasks (task_id)
);


--Used for sending tasks to execute to a specific implant_id
DROP TABLE IF EXISTS tasks;

CREATE TABLE tasks (
    task_id             INTEGER PRIMARY KEY,
    created             TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP,
    command             TEXT,
    executed           CHAR(1),
    implants_implant_id INTEGER,
    FOREIGN KEY (implants_implant_id) REFERENCES implants (implant_id)
);

-- Add unique indexes for the primary keys
CREATE UNIQUE INDEX idx_implant_id ON implants (implant_id);
CREATE UNIQUE INDEX idx_result_id ON results (result_id);
CREATE UNIQUE INDEX idx_task_id ON tasks (task_id);