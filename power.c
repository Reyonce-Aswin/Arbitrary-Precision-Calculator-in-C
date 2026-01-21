#include "apc.h"

int power(Dlist **head, Dlist **tail, int exp, Dlist **headR, Dlist **tailR)
{
    /* Reject negative exponent */
    if (exp < 0)
        return FAILURE;

    /* Handle 0 ^ 0 */
    if (exp == 0)
    {
        if ((*head)->data == 0 && (*head)->next == NULL)
            return FAILURE;   // undefined

        insert_last(headR, tailR, 1);
        return SUCCESS;
    }

    /* result = 1 */
    insert_last(headR, tailR, 1);

    for (int i = 0; i < exp; i++)
    {
        Dlist *newH = NULL, *newT = NULL;

        multiplication(headR, tailR,
                       head, tail,
                       &newH, &newT);

        free_list(headR, tailR);
        *headR = newH;
        *tailR = newT;
    }

    return SUCCESS;
}