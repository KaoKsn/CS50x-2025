#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
/* Implementing the nodes(the rectangles) **/
typedef struct node
{
    int number;
    struct node *next;
} node;

int main(int argc, char *argv[])
{
    /*
        ***** First Implementation *******

        node *fptr = NULL;
        node firstnode;
        fptr = &firstnode;

        firstnode.number = 1;
        (*fptr).number = 1; // fptr -> number = 1;
        fptr->next = NULL;

        node secondnode;

        firstnode.next = &secondnode;
        secondnode.number = 2;

        secondnode.next = NULL;

        node thirdnode;
        secondnode.next = &thirdnode;

        thirdnode.number = 3;
        thirdnode.next = NULL;
    */

    /******* Sir's Implementation **********/
    node *list = NULL;

    for (int i = 0; i < 3; i++)
    {
        node *nodeptr = malloc(sizeof(node));

        nodeptr->number = get_int("Number: \n");
        //      nodeptr->next = NULL; A great way to orphan the previous nodes.

        nodeptr->next = list;
        list = nodeptr;

    } /* We get a linked list in the opposite direction to what was intended */

    /* *** Printing the values in the list.
    node *ptr = list; // Point to the address of the last node which is stored in list

    for (int i = 0; ptr != NULL; i++)
    {
        printf("Element %d: %d\n", i + 1, ptr->number);
        ptr = ptr->next;
     Prints in the opposite direction. Starts from the latest input
    } ***** */

    /*
    ptr = list; Points to the address of last element entered
    printf("%d\n",(ptr->next)->number);  This line prints the second last element
    ptr = NULL;
    */

    /* Trying to create a correct form of linked list
    node *listheader = NULL;
    int listsize = get_int("Enter the size of the list: ");
    node *nextnode = NULL;
    for (int i = 0; i < listsize; i++)
    {
        node *n = malloc(sizeof(node));
        if(i!=0)
            nextnode->next = n;
        n->number = get_int("Number: ");

        if(i==0)
            listheader = n;

        if(i != listsize - 1)
        {
            nextnode = malloc(sizeof(node));
            nextnode->number = get_int("Number: ");
            n->next = nextnode;
            i++;
        }
        else
        {
            n->next = NULL;
            nextnode = n;  So that adding becomes easy
        }
    }
*/

    // A better implementation.
    node *listheader = NULL;
    int size = get_int("Enter the size of list: ");

    for(int i = 0;i<size;i++)
    {
        node *n = malloc(sizeof(node));
        if(n == NULL)
        {
            // TODO: we need to free anything that was allocated.
            // *Could have failed after some successful allocations
            return 1;
        }
        n->number = get_int("Number: ");
        n->next = NULL;

        // If there are no nodes yet.
        if(listheader == NULL)
        {
            listheader = n;
        }

        else
        {
            // Travel through the list untill you find the last node and then append.
            for(node *ptr = listheader; ptr != NULL; ptr = ptr->next)
            {
                // If the current node is the last node ,
                if(ptr->next == NULL)
                {
                    ptr->next = n;
                    break; // Essential else causes an infinite loop.
                }
            }
        }
    }
    //Printing the new list
    node *ptr2 = listheader;
    while(ptr2 != NULL)
    {
        printf("%d\n",ptr2->number);
        ptr2 = ptr2->next;
    }

    // Free memory
    ptr2 = listheader;
    while(ptr2 != NULL)
    {
        node *temp = ptr2->next;
        free(ptr2);
        ptr2 = temp;
    }
    return 0;
}
