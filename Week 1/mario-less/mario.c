/* Write a C program to implement the super mario pyramid with height as the user input */
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
    while (height < 1);

    /* Printing the required pyramid */
    print_pyramid(height);
}

/* Implementation of pyramid printing
    as a seperate function to improve
    * Readability
    * Modularity
*/
void print_pyramid(int height)
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < height; j++)
        {
            if (j >= height - 1 - i)
            {
                printf("#");
            }
            else
            {
                printf(" ");
            }
        }
        printf("\n");
    }
}
