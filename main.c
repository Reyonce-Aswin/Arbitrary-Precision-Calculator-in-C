/*
Name: Reyonce Aswin T
Student ID: 25021_181

Description:
    This project is a console-based Arbitrary Precision Calculator developed for Linux terminal environments.
    It is designed to perform mathematical operations on numbers of unlimited length, overcoming the limitations of standard data types in C.

    The calculator represents large integers using doubly linked lists, enabling precise computation on very large values without loss of accuracy.
    Users can input large numbers through command-line arguments and perform operations such as addition, subtraction, multiplication, and division.

    The application validates all inputs to ensure only valid numeric data is processed and handles edge cases such as zero, negative numbers, and varying operand lengths.
    Each arithmetic operation is implemented manually using linked list traversal, closely simulating real-world arithmetic logic.

    The program displays results accurately regardless of operand size and follows a modular design for better readability and maintainability.
    This project demonstrates a strong understanding of **data structures, pointer manipulation, and low-level arithmetic implementation in C, making it a reliable tool for high-precision calculations.
*/

#include "apc.h"

int main(int argc, char *argv[])
{
    /* Declare the pointers */
    Dlist *head1=NULL, *tail1=NULL;
    Dlist *head2=NULL, *tail2=NULL; 
    Dlist *headR=NULL, *tailR=NULL;

    /* Validate input count */
    if (argc != 4)
    {
        printf("Usage: %s <operand1> <operator> <operand2>\n", argv[0]);
        return -1;
    }

    // 1. Identify Signs
    int sign1 = 1, sign2 = 1;
    char *op1 = argv[1];
    char *op2 = argv[3];

    if (op1[0] == '-') {
        sign1 = -1;
        argv[1]++; // Move pointer past the '-' for digit_to_list
    }
    if (op2[0] == '-') {
        sign2 = -1;
        argv[3]++; // Move pointer past the '-' for digit_to_list
    }

    /* Store operands into lists (absolute values) */
    digit_to_list(&head1, &tail1, &head2, &tail2, argv);
    char operator = argv[2][0];

    switch (operator)
    {
        case '+':
            // (-A) + (-B) = -(A + B)
            if (sign1 == -1 && sign2 == -1) {
                printf("-");
                addition(&head1, &tail1, &head2, &tail2, &headR, &tailR);
            }
            // (-A) + B = B - A
            else if (sign1 == -1 && sign2 == 1) {
                int cmp = list_compare(head2, head1);
                if (cmp < 0) { 
					printf("-"); 
					subtraction(&head1, &tail1, &head2, &tail2, &headR, &tailR); 
				}
                else if (cmp > 0) { 
					subtraction(&head2, &tail2, &head1, &tail1, &headR, &tailR); 
				}
                else { insert_first(&headR, &tailR, 0); }
            }
            // A + (-B) = A - B
            else if (sign1 == 1 && sign2 == -1) {
                int cmp = list_compare(head1, head2);
                if (cmp < 0) { 
					printf("-"); 
					subtraction(&head2, &tail2, &head1, &tail1, &headR, &tailR); 
				}
                else if (cmp > 0) { 
					subtraction(&head1, &tail1, &head2, &tail2, &headR, &tailR); 
				}
                else { 
					insert_first(&headR, &tailR, 0); 
				}
            }
            // A + B
            else {
                addition(&head1, &tail1, &head2, &tail2, &headR, &tailR);
            }
            print_list(headR);
            break;

        case '-':
            // A - B logic with signs
            
            // (-A) - (-B) = B - A
            if (sign1 == -1 && sign2 == -1) { // -A - (-B) -> B - A
                int cmp = list_compare(head2, head1);
                if (cmp < 0) { 
					printf("-"); 
					subtraction(&head1, &tail1, &head2, &tail2, &headR, &tailR); 
				}
                else if (cmp > 0) { 
					subtraction(&head2, &tail2, &head1, &tail1, &headR, &tailR); 
				}
                else { 
					insert_first(&headR, &tailR, 0); }
            }
			// (-A) - B = -(A + B)
            else if (sign1 == -1 && sign2 == 1) { // -A - B -> -(A + B)
                printf("-");
                addition(&head1, &tail1, &head2, &tail2, &headR, &tailR);
            }
			// A - (-B) = A + B
            else if (sign1 == 1 && sign2 == -1) { // A - (-B) -> A + B
                addition(&head1, &tail1, &head2, &tail2, &headR, &tailR);
            }
            else { // A - B (Both positive)
                int cmp = list_compare(head1, head2);
                if (cmp < 0) { 
                    printf("-"); 
                    subtraction(&head2, &tail2, &head1, &tail1, &headR, &tailR); 
                }
                else if (cmp > 0) { 
                    subtraction(&head1, &tail1, &head2, &tail2, &headR, &tailR); 
                }
                else { 
                    insert_first(&headR, &tailR, 0); 
                }
            }
            print_list(headR);
            break;

        case '*':	
            // Sign is negative if signs are different
            if (sign1 != sign2) {
                // Check if result is 0 before printing '-'
                if (!(head1->data == 0 && head1->next == NULL) && !(head2->data == 0 && head2->next == NULL))
                    printf("-");
            }
            multiplication(&head1, &tail1, &head2, &tail2, &headR, &tailR);
            print_list(headR);
            break;

        case '/':	
            // Sign is negative if signs are different
            if (sign1 != sign2) {
                // Only print '-' if N1 >= N2 and N1 is not 0
                if (list_compare(head1, head2) >= 0 && (head1)->data != 0)
                    printf("-");
            }
            division(&head1, &tail1, &head2, &tail2, &headR, &tailR);
            print_list(headR);
            break;
        case '^':
            int exp = atoi(argv[3]); 
            
            if (power(&head1, &tail1, exp, &headR, &tailR) == FAILURE)
            {
                printf("Invalid power operation\n");
                return FAILURE;
            }
            if (sign1 == -1 && (exp % 2 == 1)){
                printf("-");
            }
            print_list(headR);
            break;
        default:
            printf("Invalid Input:-( Try again...\n");
    }

    free_list(&head1, &tail1);
    free_list(&head2, &tail2);
    free_list(&headR, &tailR);
    
    return 0;
}