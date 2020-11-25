from cs50 import get_float


def main():
    # Main code

    # Global variables
    global cents
    global nCoins

    while True:
        # Ask the user for the change owed
        dollars = get_float("Change owed: ")

        if dollars > 0:
            break

    # Convert cents to dollars
    cents = int(dollars * 100)
    nCoins = 0

    # Checks the number of coins for each coin available
    calcCoins(25)
    calcCoins(10)
    calcCoins(5)
    calcCoins(1)

    print(str(nCoins))


def calcCoins(coinValue):
    # Function to calculate the number of coins
    global cents
    global nCoins

    while cents >= coinValue:
        cents -= coinValue
        nCoins += 1


# Run the main function
if __name__ == "__main__":
    main()