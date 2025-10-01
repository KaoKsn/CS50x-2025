// A linked list in the reverse order.

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

void free_mem(node *list)
{
	node *tmp = NULL;

	// Free all the memory allocated till the allocation failed.
	node *ptr = list;

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

	node *list = NULL;
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

		// First let n->next point to the address of the previously created block.
		n->next = list;
		// Then, list shall point to the newly created block.
		list = n;

		// Only problem: the list is in the opposite order of creation.
	}

	// Printing the linked list, only if length > 0.
	node *ptr = list;
	while(ptr!=NULL)
	{
		printf("%d\n", ptr->number);
		ptr = ptr->next;
	}

	// Free the allocated memory.
	free_mem(list);

	return 0;
}
