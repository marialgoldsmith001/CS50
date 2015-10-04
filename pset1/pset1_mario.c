/* Marial Guierrez
*  Pset1
*  Mario */

#include <stdio.h>
#include <cs50.h>

int main(void)

{
    int height;
    int space;
    int hash;
    int rows;
// CONDITION
    /* To reject a negative input or an input greater than 23 */
    do
    {
        printf("Height:\n");
        height = GetInt();
    }
    while (height < 0 || height > 23);

// Pyramid
    for(rows = 1 ; rows <= height ; rows++)
    {
        // Loop for the space pyramid
        for(space = (height - rows) ; space > 0 ; space--)
        {
            printf(" ");
        }
        // Loop for the hash pyramid
        for (hash = 1 ; hash <= (rows + 1) ; hash++)
        {
            printf("#");
        }
        printf("\n");
    }
}
