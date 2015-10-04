/* Marial Gutierrez
 * pset2
 * Initials.c */

#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main(void)
{

    // To get name from user and make sure it capitalizes de first letter

    int i = 0;
    string s = GetString();
    char a = toupper(s[i]);
    printf("%c", a);

    // Condition to make "C" print every first letter after "space"

    for (i = 0; i < strlen(s); i++)
    {
        if (s[i] == (' '))
        {
            a = toupper(s[i + 1]);
            printf("%c", a);
        }
    }
    printf("\n");
}
