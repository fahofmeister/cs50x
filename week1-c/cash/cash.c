#include <stdio.h>
#include <cs50.h>
#include <math.h>

// Global variables
int cents;
int nCoins;

// User defined function
void calcCoins(int coinValue);

// Main code
int main(void)
{
    // Ask the user for the change owed
    float dollars;

    do
    {
        dollars = get_float("Change owed: ");
    }
    while (dollars < 0);

    // Convert cents to dollars
    cents = round(dollars * 100);

    // Checks the number of coins for each coin value available
    calcCoins(25);
    calcCoins(10);
    calcCoins(5);
    calcCoins(1);

    printf("%i\n", nCoins);
}

// Function to calculate the number of coins
void calcCoins(int coinValue)
{
    while (cents >= coinValue)
    {
        cents -= coinValue;
        nCoins++;
    }
}