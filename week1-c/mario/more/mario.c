#include <stdio.h>
#include <cs50.h>

// User-defined functions
void printScenario(string str, int n);

// Main code
int main(void)
{
    // Ask the user to enter a height
    int height;

    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);

    // Prints both pyramids until the specified height
    for (int i = 1; i <= height; i++)
    {
        printScenario(" ", height - i);
        printScenario("#", i);
        printScenario(" ", 2);
        printScenario("#", i);

        printf("\n");
    }
}

// Function to print a string n times
void printScenario(string str, int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%s", str);
    }
}