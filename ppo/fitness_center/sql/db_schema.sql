CREATE TABLE IF NOT EXISTS Events
(
    user_id INT NOT NULL,
    event_id INT NOT NULL,
    PRIMARY KEY (user_id, event_id)
);

CREATE TABLE IF NOT EXISTS UpdateSubscriptionEvents
(
    user_id INT NOT NULL,
    event_id INT NOT NULL,
    end_date TIMESTAMP NOT NULL,
    PRIMARY KEY (user_id, event_id),
    FOREIGN KEY (user_id, event_id) REFERENCES Events (user_id, event_id)
);

DO $$ BEGIN
    CREATE TYPE TurnstileEventsType AS ENUM ('enter', 'exit');
EXCEPTION
    WHEN duplicate_object THEN null;
END $$;

CREATE TABLE IF NOT EXISTS TurnstileEvents
(
    user_id INT NOT NULL,
    event_id INT NOT NULL,
    event_timestamp TIMESTAMP NOT NULL,
    event_type TurnstileEventsType NOT NULL,
    PRIMARY KEY (user_id, event_id),
    FOREIGN KEY (user_id, event_id) REFERENCES Events(user_id, event_id)
);
