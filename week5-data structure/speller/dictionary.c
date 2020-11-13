// Implements a dictionary's functionality
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include <ctype.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 10000;

// Hash table
node *table[N];

// Hash table size
unsigned int hashSize = 0;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // Creates a lowercase copy of the word
    char *lowerWord = lowerCase(word);
    if (lowerWord == NULL)
    {
        free(lowerWord);
        return false;
    }

    // Calculate hash for word and free lower case copy
    int hashNum = hash(lowerWord);
    free(lowerWord);

    // Go to the linked list location
    node *cursor = table[hashNum];

    while (cursor != NULL)
    {
        if (strcasecmp(word, cursor->word) == 0)
        {
            return true;
        }
        else
        {
            cursor = cursor->next;
        }
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // Reference: SDBM hash function
    // Site: http://www.cse.yorku.ca/~oz/hash.html

    unsigned long hashNum = 0;

    for (int i = 0, c = tolower(word[i]); c != '\0'; i++, c = word[i])
    {
        hashNum = c + (hashNum << 6) + (hashNum << 16) - hashNum;
    }

    return hashNum % N;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Opens the dictionary and checks for errors
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }

    // Variable to hold dictionary entry
    char entry[LENGTH + 1];

    while (fscanf(file, "%s", entry) != EOF)
    {
        // Runs the hash function
        int wordHash = hash(entry);

        // Allocates a new node
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return false;
        }

        // Copy the entry into the new node
        strcpy(n->word, entry);
        n->next = NULL;

        // Checks if the table is already pointing to a node
        if (table[wordHash] == NULL)
        {
            table[wordHash] = n;
        }
        else
        {
            n->next = table[wordHash];
            table[wordHash] = n;
        }

        // Keep counting the words
        hashSize++;
    }

    // Closes the file
    fclose(file);

    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // Returns the variable hashSize
    return hashSize;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // Loop through all linked lists
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];
        node *tmp = cursor;

        // Go inside the whole list
        while (cursor != NULL)
        {
            cursor = cursor->next;
            free(tmp);
            tmp = cursor;
        }
    }

    return true;
}

// Function to lower the case of a string
char *lowerCase(const char *word)
{
    char *lower = malloc(strlen(word) + 1);

    if (lower == NULL)
    {
        return NULL;
    }

    // Based on Lecture 4 note
    for (int i = 0, n = strlen(word); i < n + 1; i++)
    {
        lower[i] = tolower(word[i]);
    }

    return lower;
}
