from sys import argv, exit
from cs50 import SQL


def main():
    # Main code

    # Check for command line arguments
    if len(argv) != 2:
        print("Usage: python roster.py house")
        exit(1)

    # Open SQL database
    db = SQL('sqlite:///students.db')

    # Create query
    sqlQuery = 'SELECT first, middle, last, birth ' \
        'FROM students ' \
        f'WHERE house=\"{argv[1]}\" ' \
        'ORDER BY last ASC, first ASC;'

    # Retrieve database information
    table = db.execute(sqlQuery)

    # Print each student information
    for row in table:
        first = row['first']
        middle = row['middle'] + ' ' if row['middle'] != None else ''
        last = row['last']
        birth = row['birth']

        print(f'{first} {middle}{last}, born {birth}')


# Run main code
if __name__ == '__main__':
    main()
