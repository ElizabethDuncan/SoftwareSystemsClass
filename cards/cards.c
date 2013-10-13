/* Elizabeth Duncan
 * Software Systems Fall 2012
 * Homework 01
 */

#include<stdio.h>
#include<stdlib.h>

/* This function assigns card value
 * K - J is 10. A is 11. All other values are themselves.
 */
int assignCard ( char card_name[]) {
    int val = 0;
    switch (card_name[0]) { 
            case 'K':
            case 'Q':
            case 'J':
                val = 10;
                return val;
            case 'A':
                val = 11;
                return val;
            case 'X':
                return val;
            default:
                val = atoi(card_name);
                if ((val < 2) || (val > 10)) {
                    puts("I don't understand that value!");
        }
    }
    return val;
}

/*All changes of the "card count" are done with this function
 *A card value of 2-6 increase the count.
 *While a card value of 10 decreases the count.
*/
int changeCount(int val, int count) {
if(val == 1) {
    return count;
    }
if ((val >= 2) && (val <= 6)) {
            count++;
            return count;
        } else if (val == 10 || val == 11) { 
            count--;
            return count;
        } 
        return count;
}
/*This function prints out all the information the user needs to know*/
void printInfo(int count) {
    printf("Current count: %i\n",count);
}
/*This is the main function, what is run
*/
int main () {
    char card_name[3];
    int count = 0;
    int val = 0;
    while (card_name[0] != 'x') {
        puts("Enter the card name: ");
        scanf("%2s", card_name);
        val = assignCard(card_name);
        count = changeCount(val, count);
        printInfo(count);
    }
    return 0;
}
    

