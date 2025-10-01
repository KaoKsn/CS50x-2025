// A singly linked list.

#include</usr/include/stdio.h>
#include<string.h>
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
	printf("Enter the number of nodes: ");
	scanf("%d", &n);
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
	int size = get_int();

	node *list = NULL, *start = NULL;

	for(int i = 0; i < size; i++)
	{
		node *n = malloc(sizeof(node));

		if (n == NULL)
		{
			// If the list is empty.
			if (list == NULL)
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

		// If list is empty.
		if (list == NULL)
		{
			start = n;
			list = n;
		}
		else
		{
			// The previous blocks next field should point to the address of the current block.
			list->next = n;
			// Then, list shall point to the newly created block.
			list = n;
		}
	}
	// Set the last node to point to NULL.
	list->next = NULL;

	// Printing the linked list, only if length > 0.
	node *ptr = start;
	while(ptr!=NULL)
	{
		printf("%d\n", ptr->number);
		ptr = ptr->next;
	}

	// Free the allocated memory.
	free_mem(start);

	return 0;
}
