import csv
import sys


def main():
    if len(sys.argv) != 3:
        print("Command line argumeents: 1) CSV file containing the STR counts. 2) text file containing the DNA sequence to identify.")
        return 1 

    ##read files
    rows = []
    with open(sys.argv[1], 'r') as csv_file:
        csv_reader = csv.reader(csv_file)

        for row in csv_reader:
            rows.append(row)

    with open(sys.argv[2], 'r') as text_file:
        DNAsequence = text_file.read()


    ##update the str counts for this dna sequence
    STRcounts = {} 

    #header: name,AGATC,TTTTTTCT,AATG,TCTAG,GATA,TATC,GAAA,TCTG
    STRs = rows[0][1:]

    for STR in STRs:
        STRcounts[STR] = longest_match(DNAsequence, STR)
    ##str counts[STR] now has the longes tmatch for STR
    
    ##iterate through the rest of the database to see if there is a match
    for row in rows[1:]:
        for i, STR in enumerate(STRs):
            if int(row[i+1]) != STRcounts[STR]: ##if there is a mistmatch at any point, this row cant be the match
                break
        else:
            ##if we made it through without breaking, this row was the match
            print(row[0])
            break


    else:
        ##if we searched the whole csv_reader without breaking, there was no match
        print("No match")

    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1
            
            # If there is no match in the substring
            else:
                break
        
        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
