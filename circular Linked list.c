#include <stdio.h>
#include <stdlib.h>

struct node
{
    int data;
    struct node *next;
};

struct node *head = NULL;


/* Insert a node at a given position */
void insert(int pos, int value)
{
    struct node *newNode, *temp;
    int i;

    newNode = (struct node *)malloc(sizeof(struct node));

    if (newNode == NULL)
    {
        printf("Memory allocation failed\n");
        return;
    }

    newNode->data = value;

    /* Insertion in an empty list */
    if (head == NULL)
    {
        if (pos == 1)
        {
            head = newNode;
            newNode->next = head;
        }
        else
        {
            printf("Invalid position\n");
            free(newNode);
        }

        return;
    }

    /* Insert at first position */
    if (pos == 1)
    {
        temp = head;

        while (temp->next != head)
        {
            temp = temp->next;
        }

        newNode->next = head;
        temp->next = newNode;
        head = newNode;

        return;
    }

    /* Move to the node before required position */
    temp = head;

    for (i = 1; i < pos - 1 && temp->next != head; i++)
    {
        temp = temp->next;
    }

    /* Check invalid position */
    if (i != pos - 1)
    {
        printf("Invalid position\n");
        free(newNode);
        return;
    }

    /* Insert the new node */
    newNode->next = temp->next;
    temp->next = newNode;
}


/* Delete a node from a given position */
void del(int pos)
{
    struct node *temp, *prev;
    int i;

    if (head == NULL)
    {
        printf("List is empty\n");
        return;
    }

    /* Delete the first node */
    if (pos == 1)
    {
        /* Only one node exists */
        if (head->next == head)
        {
            free(head);
            head = NULL;
            return;
        }

        temp = head;

        /* Find the last node */
        while (temp->next != head)
        {
            temp = temp->next;
        }

        prev = head;
        head = head->next;
        temp->next = head;

        free(prev);
        return;
    }

    /* Delete node from other positions */
    temp = head;

    for (i = 1; i < pos && temp->next != head; i++)
    {
        temp = temp->next;
    }

    /* Invalid position */
    if (i != pos)
    {
        printf("Invalid position\n");
        return;
    }

    /* Find previous node */
    prev = head;

    while (prev->next != temp)
    {
        prev = prev->next;
    }

    prev->next = temp->next;
    free(temp);
}


/* Display the circular linked list */
void display()
{
    struct node *temp;

    if (head == NULL)
    {
        printf("List is empty\n");
        return;
    }

    temp = head;

    printf("Circular Linked List: ");

    do
    {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    while (temp != head);

    printf("(back to HEAD)\n");
}


/* Main function */
int main()
{
    int n, value, pos, i;

    printf("Enter number of nodes: ");
    scanf("%d", &n);

    /* Create initial circular linked list */
    for (i = 1; i <= n; i++)
    {
        printf("Enter value for node %d: ", i);
        scanf("%d", &value);

        insert(i, value);
    }

    printf("\nOriginal List:\n");
    display();

    /* Insertion */
    printf("\nEnter position to insert: ");
    scanf("%d", &pos);

    printf("Enter value to insert: ");
    scanf("%d", &value);

    insert(pos, value);

    printf("\nAfter Insertion:\n");
    display();

    /* Deletion */
    printf("\nEnter position to delete: ");
    scanf("%d", &pos);

    del(pos);

    printf("\nAfter Deletion:\n");
    display();

    return 0;
}