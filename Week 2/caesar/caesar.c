#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int validateAndConvertKey(string);
void encryptText(string, int);

/* Use atoi() */
/* Take key as a command line argument (key is a non negative integer) */
int main(int argc, string argv[])
{
    /* Make sure that there are only 2 command line arguments */
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    else
    {
        int key = validateAndConvertKey(argv[1]);

        /* Read the plaintext from the user */
        string plaintext = get_string("plaintext:  ");

        encryptText(plaintext, key);
        return 0;
    }
}

int validateAndConvertKey(string argv)
{
    int key = 0, length = strlen(argv);

    /* Make sure that every character of the second argument is a whole number */
    for (int i = 0, k = 0; i < length; i++)
    {
        if (argv[i] < '0' || argv[i] > '9')
        {
            printf("Key is a non negative integer!\n"); /* Any negative number will be rejected due
                                                           to (-) */
            exit(1);
        }
    }

    /* Convert argv[1] from 'string' to 'int' */
    key = atoi(argv);

    /* Change the key to a value between 0 and 25 */
    if (key >= 26)
    {
        key %= 26;
    }
    return key;
}

void encryptText(string plaintext, int key)
{
    int length = strlen(plaintext);

    char ciphertext[length+1]; /* strlen() doesn't account '\0' */

    /* Methods :
       !! Modifying ciphertext doesn't modify plaintext!!
        1. char ciphertext[length] and ciphertext[length]='\0' (Best to use for this problem set
           according to the syllabus)
        2. string ciphertext = (char *) malloc(length * sizeof(char));
           free(ciphertext); (Generally the best)

        !! Modifying ciphertext will modify plaintext
        3. string ciphertext = plaintext;
    */

    for (int i = 0, index = 0; i < length; i++)
    {
        if (isalpha(plaintext[i]))
        {
            int x = plaintext[i] + key;

            if ((x > 'Z' && isupper(plaintext[i])) || (x > 'z' && islower(plaintext[i])))
            {
                x -= 26;
                ciphertext[index] = x;
                index++;
                continue;
            }
            ciphertext[index] = plaintext[i] + key;
        }
        else
        {
            ciphertext[index] = plaintext[i];
        }
        index++;
    }
    ciphertext[length] = '\0';
    printf("ciphertext: %s\n", ciphertext);
}
