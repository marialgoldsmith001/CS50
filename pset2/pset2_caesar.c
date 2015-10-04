/* Marial Gutierrez
*  PSET2
*  Caesar */

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int main(int argc, string argv[])
{
    // make user provide 2 arguments
    if (argc != 2)
    {
        printf("error!\n");
        return 1;
    }
    else
    {
    // get the message you would like to encrypt from user
        string message = GetString();
        int k = atoi(argv[1]);

        // force argv to be a number between 1 and 26
        if (k > 25)
            k = k % 26;

        // go through each char of the message
        for (int i = 0, n = strlen(message); i < n ; i++)
        {
            // CONDITIONS

            // This needs to happen only if message is a letter
            if (isalpha(message[i]))
            {

                // If letter is lower case
                if (islower(message[i]))
                {
                    int lowercase = (((int) message[i] + k));
                    if (lowercase > 122)
                        lowercase = lowercase - 26;
                    printf("%c" , (char) lowercase);
                }

                // if letter is upper case
                else if (isupper(message[i]))
                {
                    int uppercase = (((int) message[i] + k));
                    if (uppercase > 90)
                        uppercase = uppercase - 26;
                    printf("%c", (char) uppercase);
                }
            }

            // if letter is a symbol or space
            else
            {
                printf("%c", message[i]);
            }
        }
        printf("\n");
    }
}
