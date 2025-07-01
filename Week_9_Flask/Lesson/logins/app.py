from flask import Flask, render_template, request, session, redirect
from flask_session import Session


app = Flask(__name__) 


# enables sessions; turns cookies on for this web app, but not permanent
app.config["SESSION_PERMAMENT"] = False
app.config["SESSION_TYPE"] = "filesystem" #use the local files to keep track of who's logged in 
Session(app) # start the session

session
# ^ is like a per-user global variable


@app.route("/")
def index():
    return render_template("index.html", name=session.get("name"))

@app.route("/login", methods=["GET", "POST"])
def login():
    if request.method == "POST":
        session["name"] = request.form.get("name")
        return redirect("/") # we can send a 300 series status code
    return render_template("login.html")


@app.route("/logout")
def logout():
    session.clear()
    return redirect("/")