CREATE TABLE transactions (
    id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, 
    user_id INTEGER NOT NULL, 
    symbol TEXT NOT NULL, 
    amount INTEGER NOT NULL, 
    unit_price REAL NOT NULL,
    time DATETIME DEFAULT CURRENT_TIMESTAMP,
    FOREIGN KEY (user_id) REFERENCES users(id)
);

CREATE TABLE owned_stocks (
    user_id INTEGER NOT NULL,
    symbol TEXT NOT NULL,
    amount INTEGER NOT NULL,
    PRIMARY KEY (user_id, symbol)
);