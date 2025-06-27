import cs50

while True:
    n = cs50.get_int("n: ")
    if 1 <= n <= 8:
        break

for i in range(1, n+1):
    print(" "*(n-i) + "#"*i + "  " + "#"*i)
