// Implements a dictionary's functionality

#include "dictionary.h"
// Required due to the use of 'LENGTH' secondly, it ensures that you accendtly don't change
// definitions.

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

typedef unsigned int uint;

// Represents a node in a hash table
typedef struct node
{
    // LENGTH = 45
    char word[LENGTH + 1];
    struct node *next;
} node;

// Table size.
const unsigned int N = 45;

// Hash table
node *table[N];

// Number of words in the dictionary aka the size of the dictionary.
uint dict_size = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // First character of char *word
    uint word_length = strlen(word);

    // Looking for identical string in the list.
    for (node *ptr = table[word_length]; ptr != NULL; ptr = ptr->next)
    {
        if (!strcasecmp(ptr->word, word))
        {
            return true;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // Method 2: The hash value is the length of the string.
    return strlen(word);
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Open the dictionary in read mode
    FILE *ptr = fopen(dictionary, "r");
    if (ptr == NULL)
    {
        printf("Couldn't load the dictionary into memory...!\n");
        return false;
    }

    // buffer to read the strings from dictionary
    char buffer[LENGTH + 1]; // Essential to avoid memory corruption via overflows.

    // Start reading the file for strings untill the EOF is encountered.
    while (fscanf(ptr, "%s", buffer) != EOF)
    {
        dict_size++;
        // For every string create a node.
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            // Free all the allocated memory given to previous strings and close the file ptr.
            return false;
        }

        // Set the word of the node = string read.
        strcpy(n->word, buffer);
        n->next = NULL;

        // Call the hash function for every string read and add elements to the list.
        uint hash_value = hash(n->word);

        // If the list is empty
        if (table[hash_value] == NULL)
        {
            table[hash_value] = n;
        }
        // If list already has nodes,
        else
        {
            // Make the current node as the first node.
            n->next = table[hash_value];
            table[hash_value] = n;
        }
    }

    // Close the file
    fclose(ptr);

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    if (dict_size == 0)
        return 0;
    else
        return dict_size;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < 45; i++)
    {
        node *ptr =
            table[i]; // Automatically ignores all array elements that do not have any element.
        while (ptr != NULL)
        {
            node *temp = ptr;
            ptr = ptr->next;
            free(temp);
        }
    }
    return true;
}
