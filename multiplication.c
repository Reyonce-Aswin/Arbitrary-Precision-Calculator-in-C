#include "apc.h"

int multiplication(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR)
{
    /* Validate input */
    if (!*head1 || !*head2)
        return FAILURE;

    // Check for multiplication by zero
    if (((*head1)->data == 0 && (*head1)->next == NULL) || ((*head2)->data == 0 && (*head2)->next == NULL))
    {
        insert_last(headR, tailR, 0);
        return SUCCESS;
    }

    Dlist *t2 = *tail2;
    int pos = 0;

    /* Multiply each digit of second number */
    while (t2)
    {
        Dlist *t1 = *tail1;
        Dlist *temp_head = NULL;
        Dlist *temp_tail = NULL;
        int carry = 0;

        /* Step 1: Multiply first number with one digit of second number */
        while (t1)
        {
            int mul = (t1->data * t2->data) + carry;
            carry = mul / 10;

            if (insert_first(&temp_head, &temp_tail, mul % 10) == FAILURE)
                return FAILURE;
            t1 = t1->prev;
        }

        if (carry)
            if (insert_first(&temp_head, &temp_tail, carry) == FAILURE)
                return FAILURE;

        /* Step 2: Add positional zeros (LSD shift) */
        for (int i = 0; i < pos; i++)
            if (insert_last(&temp_head, &temp_tail, 0) == FAILURE)
                return FAILURE;

        /* Step 3: Use addition() to add partial product to the running total */
        Dlist *new_headR = NULL;
        Dlist *new_tailR = NULL;

        // Add current result (headR) and partial product (temp_head)
        if (addition(headR, tailR, &temp_head, &temp_tail, &new_headR, &new_tailR) == FAILURE)
            return FAILURE;

        /* Step 4: Replace old result list with the new sum */
        delete_list(headR, tailR);
        *headR = new_headR;
        *tailR = new_tailR;

        /* Cleanup temporary partial product list */
        delete_list(&temp_head, &temp_tail);

        pos++;
        t2 = t2->prev;
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