#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

// User defined functions
int validateKey(string key);
string lowerString(string text);
string substitute(string plain, string key);

// Main routine
int main(int argc, string argv[])
{
    if (argc == 2)
    {
        // Converts the key to lowercase
        string key = lowerString(argv[1]);
        int keyStatus = validateKey(key);

        if (keyStatus == 0)
        {
            string plain = get_string("plaintext: ");
            string cipher = substitute(plain, key);
            printf("ciphertext: %s\n", cipher);
            return 0;
        }
        else if (keyStatus == 1)
        {
            printf("Key must contain 26 character.\n");
            return 1;
        }
        else if (keyStatus == 2)
        {
            printf("Key must only contain alphabetic characters.\n");
            return 1;
        }
        else if (keyStatus == 3)
        {
            printf("Key must not contain repeated characters.\n");
            return 1;
        }
    }

    printf("./substitution KEY\n");
    return 1;
}

// Validate the key
int validateKey(string key)
{
    // Key must have 26 characters
    if (strlen(key) != 26)
    {
        return 1;
    }

    for (int i = 0, n = strlen(key); i < n; i++)
    {
        // Key must not contain digits
        if (isdigit(key[i]) ||  !(isalpha(key[i])))
        {
            return 2;
        }

        // Check for repeated characters
        for (int j = i + 1; j < n; j++)
        {
            if (key[i] == key[j])
            {
                return 3;
            }
        }
    }

    return 0;
}

// Lower case all characters in a string
string lowerString(string text)
{
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        text[i] = tolower(text[i]);
    }

    return text;
}

// Cipher the text using substitution method
string substitute(string text, string key)
{
    // Flag to know if a character is originally upper case
    bool upperCase;
    int c;

    for (int i = 0, n = strlen(text); i < n; i++)
    {
        // Only modifies alphabetic characters
        if (isalpha(text[i]))
        {
            upperCase = isupper(text[i]);
            c = tolower(text[i]);
            c = c - 97;
            text[i] = key[c];

            // Match the original case
            if (upperCase)
            {
                text[i] = toupper(text[i]);
            }
        }
    }

    return text;
}