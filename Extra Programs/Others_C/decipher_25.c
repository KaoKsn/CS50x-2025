#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char* string;

void decryptText(string);

int main(int argc, string argv[])
{
    /* Make sure that there are only 2 command line arguments */
    if (argc != 2)
    {
        printf("Usage: ./caesar plaintext\n");
        return 1;
    }
    else
    {

        /* Read the ciphertext from the user */
        char* ciphertext = argv[1]; 

        decryptText(ciphertext);
        return 0;
    }
}

void decryptText(char* ciphertext)
{
    int length = strlen(ciphertext);

    char plaintext[length+1]; /* strlen() doesn't account '\0' */

    /* Methods :
       !! Modifying ciphertext doesn't modify plaintext!!
        1. char ciphertext[length] and ciphertext[length]='\0' (Best to use for this problem set
           according to the syllabus)
        2. string ciphertext = (char *) malloc(length * sizeof(char));
           free(ciphertext); (Generally the best)

        !! Modifying ciphertext will modify plaintext
        3. string ciphertext = plaintext;
    */
	for(int key = 1; key < 26; key++)
	{
	    for (int i = 0, index = 0; i < length; i++)
	    {
		if (isalpha(ciphertext[i]))
		{
		    int x = ciphertext[i] - key;

		    if ((x < 'A' && isupper(ciphertext[i])) || (x < 'a' && islower(ciphertext[i])))
		    {
			x += 26;
			plaintext[index] = x;
			index++;
			continue;
		    }
		    plaintext[index] = ciphertext[i] - key;
		}
		else
		{
		    plaintext[index] = ciphertext[i];
		}
		index++;
	    }
	    plaintext[length] = '\0';
	    printf("Key %d: plaintext: %s\n", key, plaintext);
	}
}
