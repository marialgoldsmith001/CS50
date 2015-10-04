/* Marial Gutierrez
*  pset 2
*  Vigenere.c */

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int main(int argc, string argv[])
{

    // make validation of only 2 arguments
    if (argc != 2)
    {
        printf("error!\n");
        return 1;
    }

    // make validation of letters only on the key
    int length = strlen(argv[1]);
    for (int a = 0 ; a < length ; a++)
        if (!isalpha(argv[1][a]))
        {
            printf("error\n");
            return 1;
        }

    // Get secret message from user
    string k = argv[1];
    string message = GetString();
    int j = 0;

    // CONDITIONS

    // Go through each char of the message given
    for (int i = 0; i < strlen(message); i++)
    {

        /* Once it gets to the last letter of the key,
        go back to the first letter of the key*/
        if (j >= strlen(k))
        {
            j = 0;
        }

        // Validate that message input will be only letters
        if (isalpha(message[i]))
        {
            // Validate message for lower case letters
            if (islower(message[i]))
            {
                // validate k[j] for lower case letters
                if (islower(k[j]))
                {
                    int c= (message[i]
                     - 'a' + (k[j] - 'a')) % 26 + 'a';/
                    printf("%c", c);
                    j++;
                }
                // validate k[j] for upper case letters
                else if (isupper(k[j]))
                {
                    int c = (message[i] - 'a' + (k[j] - 'A')) % 26 + 'a';
                    printf("%c", c);
                    j++;
                }
            }
            // Validate message for upper case letters
            else if (isupper(message[i]))
            {
                // validating k[j] for lower case letters
                if (islower(k[j]))
                {
                    int c = (message[i] - 'A' + (k[j] - 'a')) % 26 + 'A';
                    printf("%c", c);
                    j++;
                }
                // validating k[j] for upper case letters
                if (isupper (k[j]))
                {
                    int c = (message[i] - 'A' + (k[j] - 'A')) % 26 + 'A';
                    printf("%c", c);
                    j++;
                }
            }
        }
        else
        {
            printf("%c", message[i]);
        }
    }
    printf("\n");
}
