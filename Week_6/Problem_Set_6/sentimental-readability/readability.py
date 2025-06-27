s: str = input("Text: ")

##more efficient from a coding perspective:
# num_sentences = sum([1 for char in s if char in ".?!"])
# num_spaces = sum([1 for char in s if char == " "])
# num_letters = sum([1 for char in s if char.lower() in "abcdefghijklmnopqrstuvwxyz"])


##more efficient from an algorithm/runtime perpsective:
num_sentences, num_spaces, num_letters = 0, 0, 0
for char in s:
    if char in ".?!":
        num_sentences += 1
    elif char == " ":
        num_spaces += 1
    elif char.lower() in "abcdefghijklmnopqrstuvwxyz":
        num_letters += 1

num_words = num_spaces + 1

L = num_letters/num_words * 100
S = num_sentences/num_words * 100
index = 0.0588 * L - 0.296 * S - 15.8

if (index < 1):
    print("Before Grade 1")
elif (index > 16):
    print("Grade 16+")
else:
    print(f"Grade {round(index)}")