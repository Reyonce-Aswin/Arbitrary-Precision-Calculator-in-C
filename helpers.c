#include "apc.h"

/* Insert a new node at the head of the list */
int insert_first(Dlist **head, Dlist **tail, int data)
{
    Dlist *new = malloc(sizeof(Dlist));
    if(new == NULL)
        return FAILURE;
    new -> data = data;
    new -> prev = NULL;
    new -> next = NULL;

    // Set both head and tail if the list is empty
    if(*head == NULL && *tail == NULL)
    {
        *head = new;
        *tail = new;
        return SUCCESS;
    }
    else
    {
        new -> next = *head;
        (*head) -> prev = new;
        *head = new;
        return SUCCESS;
    }
}

/* Insert new node at the tail of the list */
int insert_last(Dlist **head, Dlist **tail, int data)
{
    Dlist *new = malloc(sizeof(Dlist));
    if(new == NULL)
        return FAILURE;
    new -> data = data;
    new -> prev = NULL;
    new -> next = NULL;
    
    //check if list is empty
    if(*head == NULL && *tail == NULL)
    {
        *head = new;
        *tail = new;
    }
    else
    {
        new -> prev = *tail;
        (*tail) -> next = new;
        *tail = new;
    }
    return SUCCESS;
}

/* Delete list and free memory */
int delete_list(Dlist **head, Dlist **tail)
{
    if (*head == NULL)
        return FAILURE;

    Dlist *temp;

    while (*head != NULL)
    {
        temp = *head;
        *head = (*head)->next;

        if (*head != NULL)
            (*head)->prev = NULL;

        free(temp);
    }

    *tail = NULL;

    return SUCCESS;
}

/* Free all memory used by a list*/
void free_list(Dlist **head, Dlist **tail)
{
    Dlist *temp = *head;
    while (temp)
    {
        Dlist *next = temp->next;
        free(temp);
        temp = next;
    }
    *head = *tail = NULL;
}

/* Convert string args to integer lists */
void digit_to_list(Dlist **head1,Dlist **tail1,Dlist **head2,Dlist **tail2,char *argv[]) 
{
    // Validate input digits
    for (int i = 0; argv[1][i]; i++)
    {
        if (!isdigit(argv[1][i])) { 
	    	printf("Invalid input\n"); 
			return; 
		}
	}
    for (int i = 0; argv[3][i]; i++) 
    {
        if (!isdigit(argv[3][i])) { 
			printf("Invalid input\n"); 
			return; 
		}
	}
    // For Operand 1
    for (int i = 0; argv[1][i]; i++)
    {
        int digit = argv[1][i] - '0';
        insert_last(head1, tail1, digit);
    }

    // For Operand 2
    for (int i = 0; argv[3][i]; i++)
    {
        int digit = argv[3][i] - '0';
        insert_last(head2, tail2, digit);
    }
}

/* Compare two lists numerically */
int list_compare(Dlist *head1, Dlist *head2)
{
    int len1 = 0, len2 = 0;
    Dlist *t1 = head1, *t2 = head2;

    /* Count length of both lists */
    while (t1) { 
        len1++; 
        t1 = t1->next; 
    }
    while (t2) { 
        len2++; 
        t2 = t2->next; 
    }

    /* Compare lengths */
    if (len1 > len2) return 1;
    if (len2 > len1) return -1;

    /* If lengths are equal, compare digits from MSD to LSD */
    t1 = head1;
    t2 = head2;

    while (t1 && t2)
    {
        if (t1->data > t2->data) return 1;
        if (t2->data > t1->data) return -1;

        t1 = t1->next;
        t2 = t2->next;
    }

    /* both numbers are same */
    return 0;
}

/* Print the digits in the linked list */
void print_list(Dlist *head)
{
    if (!head)
    {
        printf("0\n");
        return;
    }

    while (head)
    {
        printf("%d", head->data);
        head = head->next;
    }
    printf("\n");
}