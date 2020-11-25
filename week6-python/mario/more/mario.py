from cs50 import get_int


def main():

    # Ask the user to enter a height
    while True:
        height = get_int("Height: ")

        if height in range(1, 9):
            break

    # Prints both pyramid until the specified height
    for i in range(1, height + 1):
        printScenario(" ", height - i)
        printScenario("#", i)
        printScenario(" ", 2)
        printScenario("#", i)

        print()


# User-defined functions
# Function to print a string n times
def printScenario(string, n):

    for i in range(n):
        print(string, end="")


# Run the main function
if __name__ == "__main__":
    main()
