#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// User defined functions
string caesarCipher(int key, string text);

// Main routine
int main(int argc, string argv[])
{
    if (argc == 2)
    {
        // Checks for alphabetic arguments
        bool keyOk = true;
        for (int i = 0, n = strlen(argv[1]); i < n; i++)
        {
            if (isalpha(argv[1][i]))
            {
                keyOk = false;
            }
        }

        if (keyOk)
        {
            int key = atoi(argv[1]);
            string plain = get_string("plaintext: ");
            string cipher = caesarCipher(key, plain);
            printf("ciphertext: %s\n", cipher);
            return 0;
        }
    }

    printf("Usage: ./caesar key\n");
    return 1;
}

string caesarCipher(int key, string text)
{
    int c = 0;
    int shift = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (isalpha(text[i]))
        {
            if (isupper(text[i]))
            {
                shift = 65; // ASCII for letter A
            }
            else if (islower(text[i]))
            {
                shift = 97; // ASCII for letter a
            }
            // Shift alphabet index
            c = (text[i] - shift);
            // Adds the key
            c = c + key % 26;
            // Normalize the position, if after 26
            c = c % 26;
            // Converts back to ASCII position
            text[i] = c + shift;
        }
    }
    return text;
}