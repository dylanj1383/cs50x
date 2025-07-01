from flask import Flask, render_template, request
from cs50 import SQL


app = Flask(__name__) 

SPORTS = [
    "Basketball",
    "Soccer", 
    "Swimming", 
    "Ultimate Frisbee",
    "Hockey",
]

REGISTRANTS = {} # note that if the server crashes or restarts, all the data will go away. 
# instead, we shuold store the info in a proper database (e.g. sql databse or csv or sometihng)
# db = SQL(yadayada)

@app.route("/")
def index():
    return render_template("index.html", sports=SPORTS)

@app.route("/register", methods=["POST"])
def register():

    # client side validation alone is not enough - use server side validation 
    # if not request.form.get("name") or request.form.get("sport") not in SPORTS:
    #     return render_template("failure.html")

    name = request.form.get("name")
    
    if not name:
        return render_template("error.html", message="Missing name")
    
    sport = request.form.get("sport")

    if not sport:
        return render_template("error.html", message="Missing sport")
    
    if sport not in SPORTS:
        return render_template("error.html", message="Invalid sport")


    REGISTRANTS[name] = sport #doesnt allow two ppl with the same name


    return render_template("success.html")

@app.route("/registrants")
def registrants():
    return render_template("registrants.html", registrants=REGISTRANTS)