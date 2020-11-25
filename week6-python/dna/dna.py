from sys import argv, exit
import csv


def main():
    # Main code

    # Check for command line arguments
    if len(argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")
        exit(1)

    # Empty dictionary for database
    database = {}

    # Opens the CSV file
    with open(argv[1], 'r') as csvFile:
        reader = csv.DictReader(csvFile)
        dnaSTR = reader.fieldnames[1:]

        for row in reader:
            # Creates the first-level information on the name
            name = row['name']
            database[name] = {}

            for dna in dnaSTR:
                # The second-level information is the DNA STR
                database[name][dna] = int(row[dna])

    # Opens the DNA sequence file
    with open(argv[2], 'r') as dnaFile:
        dnaSequence = dnaFile.read()

    STRCount = {}

    # Counts the STR in the dna sequence
    for dna in dnaSTR:
        STRCount[dna] = countDNA(dnaSequence, dna)

    # Checks if there is a DNA match in the database
    for name in database.keys():
        if database[name] == STRCount:
            print(name)
            exit(0)

    print("No match")
    exit(0)


def countDNA(sequence, dna):
    # Counts dna STR in the sequence
    import re

    # Creates an iterator to search the dna patterns
    dnaIter = re.finditer(dna, sequence)

    # Saves the start and end positions of the pattern
    position = []
    for match in dnaIter:
        position.append(match.span())

    # For each (start, end) tuple, counts the longest run
    counter = 0
    maxCounter = 0
    for start, end in position:

        # Count for an initial position
        if counter == 0 or prevEnd == start:
            counter += 1

        # Resets the counter
        else:
            counter = 1

        # Keep track of the longest run
        if counter > maxCounter:
            maxCounter = counter

        prevEnd = end

    return maxCounter


# Run the main code
if __name__ == "__main__":
    main()
