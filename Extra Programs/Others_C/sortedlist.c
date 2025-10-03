// A sorted linked list.

#include<stdio.h>
#include<stdlib.h>

// Node structure.
typedef struct node
{
	int number;
	struct node *next;
}node;

// Read the number of nodes in the linked list.
int get_int(void)
{
	int n = 0;
	do
	{
		printf("Enter the number of nodes: ");
		scanf("%d", &n);
	}while(n < 0);
	return n;
}

void free_mem(node *start)
{
	node *tmp = NULL;

	// Free all the memory allocated till the allocation failed.
	node *ptr = start;

	while(ptr != NULL)
	{
		tmp = ptr->next;
		free(ptr);
		ptr = tmp;
	}
}

int main(void)
{
	// Get the size of the linked list.
	int size = get_int();

	node *start = NULL, *end = NULL;

	for(int i = 0; i < size; i++)
	{
		node *n = malloc(sizeof(node));

		// If memory allocation failed,
		if (n == NULL)
		{
			// If the list is empty.
			if (start == NULL)
			{
				printf("Failed allocating inital memory\n");
				return 1;
			}
			else
				break;
		}

		// Get the number at the node.
		printf("Enter the number: ");
		scanf("%d", &(n->number));

		// Let the current node point to NULL, initially.
		n->next = NULL;

		// If list is empty.
		if (start == NULL)
		{
			// Just append the node to the list.
			start = n;

			// End also points to the new node.
			end = n;
		}
		
		// Else, if the number belongs to the start of the list, prepend it.
		else if (start->number > n->number)
		{
			// Set the new node to point to the first node.
			n->next = start;

			// Change start to point to the new node.
			start = n;

			// No need to change end pointer of the list.
		}

		// Find the position in the list for the new node's number.
		else
		{
			/* Don't think of looping through the list starting from the second node.
			 * If size = 3 and input [1,2,3]. Will cause memory leak
			 * Reason: After the first node is added, 2 > 1 but start->next == NULL
			 * This means you lost access to the last 2 elements.
			 */

			// Loop through the list.

			for(node *ptr = start; ptr != NULL; ptr = ptr->next)
			{
				// If it's the end of the list, just append.
				if(ptr->next == NULL)
				{
					// Append the new node at the end of the list.
					ptr->next = n;

					// Ensure end points to the new node.
					end = n;

					break;// Essential, avoids infinite loop.
				}

				/* If the number in the new node's number is smaller than the next nodes number, 
				 * insert in-between the current(ptr) and the next node(ptr->next).
				 */

				if(n->number < ptr->next->number)
				{
					// Set the next field of the new node to point to the next node(ptr->next).
					n->next = ptr->next;
					// Set the current node(ptr) to point to the new node(n)
					ptr->next = n;

					break;

					// No need to change the end pointer of the list.
				}
			}
		}
	}

	// Printing the linked list, only if length > 0.
	node *ptr = start;
	while(ptr != NULL)
	{
		printf("%d\n", ptr->number);
		ptr = ptr->next;
	}

	// Free the allocated memory.
	free_mem(start);

	return 0;
}
