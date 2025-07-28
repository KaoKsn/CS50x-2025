/* A C program to get a sorted linked list from the get go. */
#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int number;
    struct node *next;
} node;

int main(void)
{
    int size = 0;
    printf("Enter the size of the linked list: ");
    scanf("%d", &size);

    node *list = NULL;

    for (int i = 0; i < size; i++)
    {
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return 1; /* An optimization: free any other node */
        }

        printf("Element %d: ", i + 1);
        scanf("%d", &(n->number));
        n->next = NULL;

        // If there are no elements in the list yet.
        if (list == NULL)
        {
            list = n;
        }
        // If the number is the smallest i.e belongs to the beginning of the list
        else if (n->number < list->number)
        {
            n->next = list;
            list = n;
        }
        else
        {
            for (node *ptr = list; ptr != NULL; ptr = ptr->next)
            {
                // Append the the end of the list.
                //  Reaching the end of the the list by this logic means middle append is not the
                //  case.
                if (ptr->next == NULL)
                {
                    ptr->next = n;
                    break; // Essential to not suffer a segfault.
                }

                // Append in the middle of the list.
                else if (n->number < ptr->next->number)
                {
                    n->next = ptr->next;
                    ptr->next = n;
                    break; // To avoid segfault.
                }
            }
        }
    }

    // Print the linked list
    for (node *ptr = list; ptr != NULL; ptr = ptr->next)
    {
        printf("%d\t", (ptr->number));
    }
    printf("\n");

    // Free the list
    while (list != NULL)
    {
        node *temp = list;
        list = list->next;
        free(temp);
    }
}
