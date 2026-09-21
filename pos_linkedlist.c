
#include <stdio.h>
#include <stdlib.h>

struct node {
	int data;
	struct node *next;
};

struct node *create_list(int n)
{
	struct node *head = NULL, *tail = NULL, *new_node;
	int i;

	for (i = 1; i <= n; i++) {
		new_node = malloc(sizeof(*new_node));
		if (new_node == NULL) {
			printf("Memory allocation failed.\n");
			exit(EXIT_FAILURE);
		}
		printf("Enter data for node %d: ", i);
		scanf("%d", &new_node->data);
		new_node->next = NULL;

		if (head == NULL)
			head = new_node;
		else
			tail->next = new_node;
		tail = new_node;
	}
	return head;
}

void display(struct node *head)
{
	if (head == NULL) {
		printf("List is empty.\n");
		return;
	}

	while (head != NULL) {
		printf("%d -> ", head->data);
		head = head->next;
	}
	printf("NULL\n");
}

struct node *insert_at_position(struct node *head, int data, int position)
{
	struct node *new_node, *current;
	int i;

	if (position < 1) {
		printf("Invalid position.\n");
		return head;
	}

	new_node = malloc(sizeof(*new_node));
	if (new_node == NULL) {
		printf("Memory allocation failed.\n");
		exit(EXIT_FAILURE);
	}
	new_node->data = data;

	if (position == 1) {
		new_node->next = head;
		return new_node;
	}

	current = head;
	for (i = 1; current != NULL && i < position - 1; i++)
		current = current->next;

	if (current == NULL) {
		printf("Position out of range.\n");
		free(new_node);
		return head;
	}

	new_node->next = current->next;
	current->next = new_node;
	return head;
}

struct node *delete_at_position(struct node *head, int position)
{
	struct node *temp;
	int i;

	if (position < 1 || head == NULL) {
		printf("Invalid position or empty list.\n");
		return head;
	}
	if (position == 1) {
		temp = head;
		head = head->next;
		free(temp);
		return head;
	}

	temp = head;
	for (i = 1; temp->next != NULL && i < position - 1; i++)
		temp = temp->next;
	if (temp->next == NULL) {
		printf("Position out of range.\n");
		return head;
	}
	{
		struct node *removed = temp->next;
		temp->next = removed->next;
		free(removed);
	}
	return head;
}

void sort_list(struct node *head)
{
	struct node *i, *j;
	int temp;

	for (i = head; i != NULL; i = i->next)
		for (j = i->next; j != NULL; j = j->next)
			if (i->data > j->data) {
				temp = i->data;
				i->data = j->data;
				j->data = temp;
			}
}

int main(void)
{
	struct node *head = NULL, *temp;
	int choice, n, data, position;

	do {
		printf("\n--- Linked List Menu ---\n");
		printf("1. Create list\n");
		printf("2. Display list\n");
		printf("3. Insert at position\n");
		printf("4. Delete at position\n");
		printf("5. Sort list\n");
		printf("6. Exit\n");
		printf("Enter your choice: ");
		if (scanf("%d", &choice) != 1)
			return 1;

		switch (choice) {
		case 1:
			while (head != NULL) {
				temp = head;
				head = head->next;
				free(temp);
			}
			printf("Enter number of nodes: ");
			scanf("%d", &n);
			if (n < 0) {
				printf("Invalid number of nodes.\n");
				head = NULL;
			} else {
				head = create_list(n);
			}
			break;
		case 2:
			display(head);
			break;
		case 3:
			printf("Enter data to insert: ");
			scanf("%d", &data);
			printf("Enter position (1-based): ");
			scanf("%d", &position);
			head = insert_at_position(head, data, position);
			break;
		case 4:
			printf("Enter position to delete: ");
			scanf("%d", &position);
			head = delete_at_position(head, position);
			break;
		case 5:
			sort_list(head);
			printf("List sorted successfully.\n");
			break;
		case 6:
			while (head != NULL) {
				temp = head;
				head = head->next;
				free(temp);
			}
			printf("Exiting program.\n");
			break;
		default:
			printf("Invalid choice.\n");
		}
	} while (choice != 6);

	return 0;
}
 