#include "apc.h"

int division(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR)
{
    /* 1. Validation input pointers */
    if (!*head1 || !*head2)
        return FAILURE;

    // Division by Zero (N / 0)
    if ((*head2)->data == 0 && (*head2)->next == NULL) {
        printf("Division by zero error\n");
        return FAILURE;
    }

    // Zero divided by N (0 / N)
    if ((*head1)->data == 0 && (*head1)->next == NULL) {
        insert_first(headR, tailR, 0);
        return SUCCESS;
    }

    // N1 < N2: Result is 0
    if (list_compare(*head1, *head2) < 0) {
        insert_first(headR, tailR, 0);
        return SUCCESS;
    }
    
    // N1 == N2: Result is 1
    if (list_compare(*head1, *head2) == 0) {
        insert_first(headR, tailR, 1);
        return SUCCESS;
    }

    /* 2. Initialization for Long Division Simulation */
    Dlist *n1 = *head1;
    Dlist *headRem = NULL;
    Dlist *tailRem = NULL;
    
    /* 3. Main Long Division Loop */
    while (n1) 
    {
        // Append the next digit of the dividend to current remainder
        if (insert_last(&headRem, &tailRem, n1->data) == FAILURE) {
            delete_list(&headRem, &tailRem);
            return FAILURE;
        }
        
        // Remove leading zeros from remainder to maintain correct comparison
        while (headRem && headRem->data == 0 && headRem->next) 
        {
            Dlist *temp = headRem;
            headRem = headRem->next;
            headRem->prev = NULL;
            free(temp);
        }

        int q_digit = 0;
        
        // While Remainder >= Divisor, perform subtraction
        while (list_compare(headRem, *head2) >= 0)
        {
            Dlist *tempHead = NULL;
            Dlist *tempTail = NULL;

            // Reuse the subtraction function
            if (subtraction(&headRem, &tailRem, head2, tail2, &tempHead, &tempTail) == SUCCESS)
            {
                // Delete old remainder and update with the new difference
                delete_list(&headRem, &tailRem);
                headRem = tempHead;
                tailRem = tempTail;
                q_digit++;
            }
            else
            {
                delete_list(&headRem, &tailRem);
                return FAILURE;
            }
        }
        
        // Append quotient digit to result list (ignoring leading zeros)
        if (q_digit > 0 || *headR != NULL) 
        {
            if (insert_last(headR, tailR, q_digit) == FAILURE)
            {
                delete_list(&headRem, &tailRem);
                return FAILURE;
            }
        }

        n1 = n1->next;
    }

    delete_list(&headRem, &tailRem);

    // If result is empty (e.g., 0.x cases), set it to 0
    if (*headR == NULL)
    {
        if (insert_first(headR, tailR, 0) == FAILURE)
            return FAILURE;
    }

    return SUCCESS;
}