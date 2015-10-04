/*
Marial Gutierrez
Pset1:
Greedy
*/

#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    int counter = 0;

    /* To get change from user */

    printf("Change:\n");
    float change = GetFloat();

    /* Condition for negative numbers */

    for (;change < 0;)
    {
        printf("Retry:\n");
        change = GetFloat();
    }
    /* Convert dollars to coins */

    int x = (roundf(change * 100));

    /* We address the result
     to each coin value and substract until zero is obtained */

    for (;x >= 25;)
    {
        x = x - 25;
        counter = counter + 1;
    }

    for (;x >= 10;)
    {
        x = x - 10;
        counter = counter + 1;
    }

    for (;x >= 5;)
    {
        x = x - 5;
        counter = counter + 1;
    }

    for (;x >= 1;)
    {
        x = x - 1;
        counter = counter + 1;
    }

    printf("%d\n", counter);

}
