#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // Ask the user to enter a height
    int height;

    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);

    // Prints the pyramid until the specified height
    for (int i = 1; i <= height; i++)
    {
        // For loop to add spaces
        for (int k = 0; k < height - i; k++)
        {
            printf(" ");
        }

        // For loop to print the hashes
        for (int j = 0; j < i; j++)
        {
            printf("#");
        }

        printf("\n");
    }
}