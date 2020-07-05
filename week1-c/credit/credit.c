#include <stdio.h>
#include <cs50.h>

// User defined functions
int calculateCheckSum(long number);
int checkDigits(long number);
int getFirstDigits(long number);

// Main code
int main(void)
{
    // Ask the user for a credit card number
    long number;

    do
    {
        number = get_long("Number: ");
    }
    while (number <= 0);

    // Calculate checksum
    int sum = calculateCheckSum(number);

    // Calculate the number of digits
    int dig = checkDigits(number);

    // Get the card first 2 digits
    int fDig = getFirstDigits(number);

    // Checks the card issuer
    if (sum % 10 == 0 && dig == 15 && (fDig == 34 || fDig == 37))
    {
        printf("AMEX\n");
    }
    else if (sum % 10 == 0 && dig == 16 && fDig >= 51 && fDig <= 55)
    {
        printf("MASTERCARD\n");
    }
    else if (sum % 10 == 0 && (dig == 16 || dig == 13) && fDig / 10 == 4)
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    }

}

// Fuction to calculate checkSum
int calculateCheckSum(long number)
{
    int nDigits = 0;
    int sum = 0;
    int digit, temp;

    while (number > 0)
    {
        // Extracts the last digit
        digit = number % 10;

        if (nDigits % 2 == 0)
        {
            sum += digit;
        }
        else
        {
            temp = digit * 2;

            // Sums the digits to the total
            while (temp > 0)
            {
                sum += temp % 10;
                temp /= 10;
            }
        }

        // Removes last digit and tracks current position
        number /= 10;
        nDigits++;
    }

    return sum;
}

// Function to check the number of digits
int checkDigits(long number)
{
    int digits = 0;

    while (number > 0)
    {
        number /= 10;
        digits++;
    }

    return digits;
}

// Function to get first 2 digits
int getFirstDigits(long number)
{
    while (number / 100 > 0)
    {
        number /= 10;
    }

    return number;
}