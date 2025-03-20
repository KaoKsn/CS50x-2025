/* Substitution Cipher */
#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SUCCESS 0
#define FAILURE 1

int validateKey(string);
void encryptText(string, string);

int main(int argc, string argv[])
{
    /* Check if only two arguments are passed in the command line */
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return FAILURE;
    }
    else
    {
        /* Check the validity of the key passed */
        int validity = validateKey(argv[1]);
        if (validity == FAILURE)
        {
            return FAILURE;
        }
        else
        {
            /* Get plaintext */
            string plaintext = get_string("plaintext:  ");

            /* Write the ciphertext */
            encryptText(plaintext, argv[1]);
        }
    }
    return SUCCESS;
}

int validateKey(string argv)
{
    /* Checking length of the key */
    int length = strlen(argv);

    if (length != 26)
    {
        printf("Invalid Key, length is not 26!\n");
        return FAILURE;
    }

    bool seen[26] = {false};
    for (int i = 0; i < length; i++)
    {
        /* Check for special characters */
        if (ispunct(argv[i]))
        {
            printf("Invalid Key, special characters found!\n");
            return FAILURE;
        }

        /* Check for redundancy */

        int index = tolower(argv[i]) - 'a'; /* 0 - 25 */

        if (seen[index])
        {
            printf("Invalid Key, redundancy detected\n");
            return FAILURE;
        }
        seen[index] = true;
    }
    return SUCCESS;
}

void encryptText(string plaintext, string key)
{
    int length = strlen(plaintext);
    char ciphertext[length + 1];

    for (int i = 0; i < length; i++)
    {
        if (isalpha(plaintext[i]))
        {
            ciphertext[i] = key[tolower(plaintext[i]) - 'a']; /* 0 - 25 => substitutes(a/A - z/Z) */
            /* To convert every character ciphertext to the case of character in plaintext */
            if (isupper(plaintext[i]))
            {
                ciphertext[i] = toupper(ciphertext[i]);
            }
            else
            {
                ciphertext[i] = tolower(ciphertext[i]);
            }
        }
        else
        {
            ciphertext[i] = plaintext[i];
        }
    }

    ciphertext[length] = '\0';

    printf("ciphertext: %s\n", ciphertext);
}
