from sys import argv, exit
from cs50 import SQL
import csv


def main():
    # Main code

    # Check for command line arguments
    if len(argv) != 2:
        print("Usage: python import.py data.csv")
        exit(1)

    # Empty list for csv information
    students = []

    # Open CSV file
    with open(argv[1], 'r') as csvFile:
        reader = csv.DictReader(csvFile)

        for row in reader:
            student = {}
            name = row['name'].split(' ')

            # Check if there is a middle name
            if len(name) == 2:
                student['first'] = name[0]
                student['middle'] = None
                student['last'] = name[-1]
            else:
                student['first'] = name[0]
                student['middle'] = name[1]
                student['last'] = name[-1]

            student['house'] = row['house']
            student['birth'] = int(row['birth'])

            # Append the student data to list
            students.append(student)

    # Opens SQL database
    db = SQL('sqlite:///students.db')

    for student in students:
        # Assign variables for each value
        first = f"\'{student['first']}\'"
        middle = f"\'{student['middle']}\'" if student['middle'] != None else 'NULL'
        last = f"\'{student['last']}\'"
        house = f"\'{student['house']}\'"
        birth = student['birth']

        # Create query
        sqlQuery = 'INSERT INTO students ' \
            '(first, middle, last, house, birth) ' \
            f'VALUES ({first}, {middle}, {last}, {house}, {birth});'

        # Insert into the database
        db.execute(sqlQuery)


# Run main code
if __name__ == "__main__":
    main()
