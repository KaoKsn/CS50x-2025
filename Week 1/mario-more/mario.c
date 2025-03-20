/* Write a C program to implement the super mario pyramid with height taken as the user input */
#include <cs50.h>
#include <stdio.h>

void print_pyramid(int);

int main(void)
{
    /* Reading the height of the required pyramid */
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);

    /* Printing the required pyramid */
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < height; j++)
        {
            if (j >= height - i - 1) /* Start printing from the column = height - row - 1*/
            {
                printf("#");
            }
            else /* For any other column print a whitespace */
            {
                printf(" ");
            }
        }
        /* Printing the symmetric blocks */
        printf("  "); /* Two whitespace between the symmetrical elements */
        for (int k = 0; k <= i; k++)
        {
            printf("#");
        }
        printf("\n");
    }
}
