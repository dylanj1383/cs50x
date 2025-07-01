from cs50 import SQL

db = SQL("sqlite:///numbers.db")

threshold = float(input("Enter threshold: ")) 

rows = db.execute("SELECT COUNT(*) as n FROM numbers WHERE Random_Number < ?", threshold) #replcae the ? with threshold

##count always returns 1 row

row = rows[0]

print(row["n"]) ##each row is a dictionary

