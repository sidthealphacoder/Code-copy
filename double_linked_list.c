
#include <stdio.h>
#include <stdlib.h>

struct node
{
    int data;
    struct node *prev;
    struct node *next;
};

struct node *head = NULL;

/* 1. Create a doubly linked list */
void create()
{
    struct node *newNode, *temp;
    int n, value, i;

    printf("Enter number of nodes: ");
    scanf("%d", &n);

    if (n < 0)
    {
        printf("Invalid number of nodes\n");
        return;
    }

    /* Clear the previous list */
    while (head != NULL)
    {
        temp = head;
        head = head->next;
        free(temp);
    }

    for (i = 1; i <= n; i++)
    {
        printf("Enter value for node %d: ", i);
        scanf("%d", &value);

        newNode = (struct node *)malloc(sizeof(struct node));

        if (newNode == NULL)
        {
            printf("Memory allocation failed\n");
            return;
        }

        newNode->data = value;
        newNode->prev = NULL;
        newNode->next = NULL;

        if (head == NULL)
        {
            head = newNode;
        }
        else
        {
            temp = head;

            while (temp->next != NULL)
            {
                temp = temp->next;
            }

            temp->next = newNode;
            newNode->prev = temp;
        }
    }

    printf("List created successfully\n");
}

/* 2. Delete a node by position */
void del()
{
    struct node *temp;
    int pos, i;

    if (head == NULL)
    {
        printf("List is empty\n");
        return;
    }

    printf("Enter position to delete: ");
    scanf("%d", &pos);

    if (pos < 1)
    {
        printf("Invalid position\n");
        return;
    }

    temp = head;

    for (i = 1; i < pos && temp != NULL; i++)
    {
        temp = temp->next;
    }

    if (temp == NULL)
    {
        printf("Invalid position\n");
        return;
    }

    if (temp->prev != NULL)
    {
        temp->prev->next = temp->next;
    }
    else
    {
        head = temp->next;
    }

    if (temp->next != NULL)
    {
        temp->next->prev = temp->prev;
    }

    free(temp);

    printf("Node deleted successfully\n");
}

/* 3. Display the list */
void display()
{
    struct node *temp;

    if (head == NULL)
    {
        printf("List is empty\n");
        return;
    }

    temp = head;

    printf("Doubly Linked List: ");

    while (temp != NULL)
    {
        printf("%d <-> ", temp->data);
        temp = temp->next;
    }

    printf("NULL\n");
}

/* 4. Insert a node by position */
void insert()
{
    struct node *newNode, *temp;
    int pos, value, i;

    printf("Enter position to insert: ");
    scanf("%d", &pos);

    printf("Enter value: ");
    scanf("%d", &value);

    if (pos < 1)
    {
        printf("Invalid position\n");
        return;
    }

    newNode = (struct node *)malloc(sizeof(struct node));

    if (newNode == NULL)
    {
        printf("Memory allocation failed\n");
        return;
    }

    newNode->data = value;
    newNode->prev = NULL;
    newNode->next = NULL;

    /* Insert at first position */
    if (pos == 1)
    {
        newNode->next = head;

        if (head != NULL)
        {
            head->prev = newNode;
        }

        head = newNode;

        printf("Node inserted successfully\n");
        return;
    }

    temp = head;

    for (i = 1; i < pos - 1 && temp != NULL; i++)
    {
        temp = temp->next;
    }

    if (temp == NULL)
    {
        printf("Invalid position\n");
        free(newNode);
        return;
    }

    newNode->next = temp->next;
    newNode->prev = temp;

    if (temp->next != NULL)
    {
        temp->next->prev = newNode;
    }

    temp->next = newNode;

    printf("Node inserted successfully\n");
}

/* 5. Sort in ascending order */
void sort()
{
    struct node *temp, *ptr;
    int swap;

    if (head == NULL || head->next == NULL)
    {
        printf("List is already sorted\n");
        return;
    }

    temp = head;

    while (temp->next != NULL)
    {
        ptr = temp->next;

        while (ptr != NULL)
        {
            if (temp->data > ptr->data)
            {
                swap = temp->data;
                temp->data = ptr->data;
                ptr->data = swap;
            }

            ptr = ptr->next;
        }

        temp = temp->next;
    }

    printf("List sorted in ascending order\n");
}

/* 6. Display the list in reverse */
void reverseDisplay()
{
    struct node *temp;

    if (head == NULL)
    {
        printf("List is empty\n");
        return;
    }

    temp = head;

    while (temp->next != NULL)
    {
        temp = temp->next;
    }

    printf("Reverse Doubly Linked List: ");

    while (temp != NULL)
    {
        printf("%d <-> ", temp->data);
        temp = temp->prev;
    }

    printf("NULL\n");
}

/* 7. Main menu */
int main()
{
    int choice;

    do
    {
        printf("\n===== DOUBLY LINKED LIST =====\n");
        printf("1. Create\n");
        printf("2. Delete\n");
        printf("3. Display\n");
        printf("4. Insert\n");
        printf("5. Sort\n");
        printf("6. Display in Reverse\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1)
        {
            printf("Invalid input\n");
            break;
        }

        switch (choice)
        {
            case 1:
                create();
                break;

            case 2:
                del();
                break;

            case 3:
                display();
                break;

            case 4:
                insert();
                break;

            case 5:
                sort();
                break;

            case 6:
                reverseDisplay();
                break;

            case 7:
                printf("Exiting program...\n");
                break;

            default:
                printf("Invalid choice\n");
        }

    } while (choice != 7);

    return 0;
}
