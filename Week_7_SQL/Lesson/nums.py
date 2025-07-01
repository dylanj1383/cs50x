import csv

with open("numbers.csv", "r") as file:
    # reader = csv.reader(file)
    # next(reader) # ignores the header
    
    # for line in reader:
    #     r = line[1]  ##this relies on [1] being random and [2] being rand+5
    #     rplus5 = line[2]
    #     print(f"random: {r}; random+5: {rplus5}")
    dict_reader = csv.DictReader(file) ##with this, I can use the column headers as keys
    ##dictionary reader assumes that header contains the keys; so we don't need to call next

    distribution = {
        "x<=0.5" : 0,
        "0.5<x<=1": 0,
        "x>=1": 0
    }

    for line in dict_reader:
        r = float(line["Random_Number"])
        rplus5 = float(line["Random_Number_Plus_5"])
        # print(f"random: {r}; random+5: {rplus5}") 

        if (r<=0.5):
            distribution["x<=0.5"] += 1
        elif (r<=1):
            distribution["0.5<x<=1"] += 1
        else:
            distribution["x>=1"] += 1


print("Occurences:")
for range in distribution:
    print(f"{range}: {distribution[range]}")


    