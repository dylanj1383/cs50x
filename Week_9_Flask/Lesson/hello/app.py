from flask import Flask, render_template, request

app = Flask(__name__) # turn this file into an web app and refer to it with app

# decorator means u can wrap one function inside another 

# turn the following function into a route that can be served by the server to the router

# @app.route("/") #the argument is / so whenever we are in the default, call index
# # the function is called index and returns hellow world
# def index():
#     # name = request.args["name"] if "name" in request.args else "monkey"
#     # name = request.args.get("name", "monkey") #does the same thing. Gets name if accessible, else gives monkey

#     #  index.html should be in a folder called templates
#     # return render_template("index.html", name=name)  #placeholder is what is being replaced in the template

#     return render_template("index.html") #render template handles layout and all that aswell


# @app.route("/greet", methods=["POST", "GET"])
# def greet():
#     # name = request.args.get("name", "monkey")  #<- this assumes the command was coming via get, not post 
#     # post requests, rather, are coming from request.form 

#     name = request.form.get("name", "monkey")
#     return render_template("greet.html", name=name)


# same thing as above but more concise
@app.route("/", methods=["GET", "POST"])
def index():
    if request.method == "POST":
        # name = request.form.get("name", "monkey")
        name = request.form.get("name") #if we get rid of the default value, we can put it in the template instead
        return render_template("greet.html", name=name)
    else:
        return render_template("index.html")