from cs50 import get_string


def main():
    # Main code

    while True:
        # Ask the user for a credit card number
        number = get_string("Number: ")

        if int(number) > 0:
            break

    # Calculate checksum
    Sum = calculateCheckSum(number)

    # Calculate the number of digits
    Dig = len(number)

    # Get the card first 2 digits
    fDig = int(number[:2])

    if Sum % 10 == 0 and Dig == 15 and (fDig == 34 or fDig == 37):
        print("AMEX")

    elif Sum % 10 == 0 and Dig == 16 and fDig in range(51, 56):
        print("MASTERCARD")

    elif Sum % 10 == 0 and (Dig == 16 or Dig == 13) and str(fDig)[0] == '4':
        print("VISA")

    else:
        print("INVALID")


def calculateCheckSum(number):
    # Function to calculate checkSum
    Sum = 0

    # Gets only half of the digits
    for digit in number[::-1][1::2]:
        digit = str(int(digit) * 2)
        for char in digit:
            Sum += int(char)

    # Sums the other half of digits
    for digit in number[::-1][::2]:
        Sum += int(digit)

    return Sum


# Run the main code
if __name__ == "__main__":
    main()
