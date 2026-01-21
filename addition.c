#include "apc.h"

int addition(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR)
{
	/* Definition goes here */
    // Validate input pointers 
    if (!head1 || !head2 || !headR)
        return FAILURE;

    // Pointers to the end of both lists
    Dlist *n1 = *tail1; // Start from least significant digit
    Dlist *n2 = *tail2;

    int carry = 0;

    // Continue as long as there are digits or a carry left
    while (n1 || n2 || carry)
    {
        // Calculate sum of the digits and the current carry
        int sum = (n1 ? n1->data : 0) + (n2 ? n2->data : 0) + carry;

        // Determine new carry and digit to store
        carry = sum / 10;
        sum = sum % 10;

        // Insert results at the beginning of the result list
        if (insert_first(headR, tailR, sum) == FAILURE)
            return FAILURE;
		
        // Move to the previous digits
		if (n1) n1 = n1->prev;
    	if (n2) n2 = n2->prev;
    }
    return SUCCESS;
}