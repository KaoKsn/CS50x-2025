#include <stdio.h>
#include <stdlib.h>

typedef char *string;

char *get_string(char *input_string);

int main(void)
{
    string name = get_string("Enter your name: ");
    if (name == NULL)
    {
        printf("Dynamic Memory Allocation Failed!...\n");
        return 1;
    }
    printf("Hello, %s\n", name);
    free(name);

    return 0;
}

char *get_string(char *input_string)
{
    char buffer_char;
    char *read_string = NULL;

    int length;

    // Prompting the user from input string.
    printf("%s", input_string);

    // Reading the prompt of the user.
    for (length = 0; scanf("%c", &buffer_char) == 1 && buffer_char != '\n'; length++)
    {
        if (length == 0)
        {
            read_string = malloc(sizeof(char));
            if (read_string == NULL)
            {
                return NULL;
            }
            read_string[length] = buffer_char;
        }
        else
        {
            char *temp = realloc(read_string, sizeof(char) * (length + 1));
            // If reallocation failed.
            if (temp == NULL)
            {
                char temp_string[101]; // Fall Back...
                for (int i = 0; i < length; i++)
                {
                    temp_string[i] = read_string[i];
                }
                temp_string[length] = buffer_char;
                length++;
                while (scanf("%c", &buffer_char) == 1 && buffer_char != '\n' && length < 100)
                {
                    temp_string[length] = buffer_char;
                    length++;
                }
                temp_string[length] = '\0';
                printf("Hello, %s\n", temp_string);

                free(read_string);
                exit(0);
            }
            else
            {
                read_string = temp;
                read_string[length] = buffer_char;
            }
        }
    }

    // Adding the null terminator to convert it to a valid string in C.
    char *temp = realloc(read_string, sizeof(char) * (length + 1));
    // If reallocation failed.
    if (temp == NULL)
    {
        char read_string_static[length + 1];
        // Since read_string has no null terminator it is bad to use strcpy().
        for (int i = 0; i < length; i++)
        {
            read_string_static[i] = read_string[i];
        }
        read_string_static[length] = '\0';

        printf("Hello, %s\n", read_string_static);

        // free read_string
        free(read_string);
        exit(0);
        // return read_string_static; -> Will not exist once the stack frame is removed.
    }
    else
    {
        read_string = temp;
        temp = NULL;
        read_string[length] = '\0';
    }

    // Returning the read string.
    return read_string;
}
