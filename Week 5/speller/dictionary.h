// Declares a dictionary's functionality
#ifndef __DICTIONARY_H__
#define __DICTIONARY_H__

// To use the boolean values.
#include <stdbool.h>

// Maximum length for a word
#define LENGTH 45

// Prototypes
bool check(const char *word);
unsigned int hash(const char *word);
bool load(const char *dictionary);
unsigned int size(void);
bool unload(void);

#endif // DICTIONARY_H

// Include guards help fight redundancy that is caused due to including dictionary.h in the other two.
