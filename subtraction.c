#include "apc.h"

int subtraction(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR)
{
    // Validate input pointers
    if (!head1 || !head2 || !headR)
        return FAILURE;

    // Start subtraction from the tail
    Dlist *n1 = *tail1; // 1s digit of operand1
    Dlist *n2 = *tail2; // 1s digit of operand2

    int borrow = 0;

    // Iterate through all digits
    while (n1 || n2)
    {
        // Subtract digits and the borrow
        int diff = (n1 ? n1->data : 0) - (n2 ? n2->data : 0) - borrow;

        // If result is negative, borrow 10 from the next position
        if (diff < 0)
        {
            diff += 10;
            borrow = 1;
        }
        else
        {
            borrow = 0;
        }

        // Add result digit to the result list
        if (insert_first(headR, tailR, diff) == FAILURE)
            return FAILURE;

        // Move to more significant digits
        if (n1) n1 = n1->prev;
        if (n2) n2 = n2->prev;
    }

    // Remove leading zeros
    while (*headR && (*headR)->data == 0 && (*headR)->next)
    {
        Dlist *temp = *headR;
        *headR = (*headR)->next;
        (*headR)->prev = NULL;
        free(temp);
    }

    return SUCCESS;
}