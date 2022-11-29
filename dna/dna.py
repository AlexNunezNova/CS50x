import csv
import sys
import numpy


def main():

    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        print("Invalid input. Please use a valid CSV file and a valid text file")

    # TODO: Read database file into a variable
    # set a variable and remember headers separately
    peopleDB = []
    strHeaders = []

    # open database and create list
    with open(sys.argv[1], "r") as file:
        reader = csv.reader(file)
        counter = 0
        for line in reader:
            # take headers apart, omitting the "name" label
            # these will be the STR to analyse later
            if counter == 0:
                strHeaders = line[1:len(line)]
                counter += 1
            # the rest, put it in a 2 dimension list
            else:
                peopleDB.append(line)

    # TODO: Read DNA sequence file into a variable
    # set a variable
    sequence = []

    # open sequence and copy to list, eliminating line change at the end
    with open(sys.argv[2], "r") as file:
        sequence = file.readline().rstrip("\n")

    # TODO: Find longest match of each STR in DNA sequence
    # create a loop for every STR and use provided function below
    # store the result in a list and convert to strings
    strMatch = []
    for i in range(len(strHeaders)):
        strMatch.append(str(longest_match(sequence, strHeaders[i])))

    # TODO: Check database for matching profiles
    # look each line in the database
    for i in range(len(peopleDB)):
        # set a test array with the row results of each person (omit the name column)
        testlist = peopleDB[i][1:len(peopleDB[i])]
        # if there is a match, print the name
        if (testlist) == strMatch:
            print(f"{peopleDB[i][0]}")
            exit()

    # if there is not match after the loop, print message
    print("No match")
    exit()


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
