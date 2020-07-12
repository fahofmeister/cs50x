#include <stdio.h>
#include <cs50.h>
#include <math.h>
#include <string.h>

// Global variables
int nLetters = 0;
int nWords = 0;
int nSentences = 0;

// User defined functions
void checkText(string text);
float calcIndex(void);

// Main routine
int main(void)
{
    string text = get_string("Text: ");
    checkText(text);
    int index = round(calcIndex());

    // printf("%i letter(s)\n", nLetters);
    // printf("%i word(s)\n", nWords);
    // printf("%i sentence(s)\n", nSentences);

    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}

void checkText(string text)
{
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        // Checks the current character
        if (text[i] >= 'A' && text[i] <= 'z')
        {
            nLetters++;
        }
        else if (text[i] == ' ')
        {
            nWords++;
        }
        else if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            nSentences++;
        }

        // Adds the final word when reaches the end of text
        if (n == i + 1)
        {
            nWords++;
        }
    }
}

// Calculates the Coleman-Liau index
float calcIndex(void)
{
    float L = (float) nLetters / (float) nWords * 100;
    float S = (float) nSentences / (float) nWords * 100;

    return 0.0588 * L - 0.296 * S - 15.8;
}