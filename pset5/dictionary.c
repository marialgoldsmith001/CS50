/****************************************************************************
 * Marial Gutierrez
 * dictionary.c
 * Problem Set 5
 * NOTE: Hash Function was taken from http://reddit.com/r/cs50/comments/1x6vc8/pset6_trie_vs_hashtable/
 * for optimization credits should be given to the student "Brenda" and her husband.
 ***************************************************************************/
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "dictionary.h"

//size counter
int dsize = 0;

// Linked List
typedef struct node
{
    char word[LENGTH+1];
    struct node* next;
}
node;

//Hashtable
node* table[HASH_SIZE];

//Hashfunction
int hash_func(const char* word)
{
    unsigned int hash = 0;
    for(int i=0, n=strlen(word) ; i <n; i++)
        hash = (hash << 2)^ word[i];
    return hash % HASH_SIZE;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{    
    // open file
    FILE* file = fopen( dictionary, "r");
    if (file == NULL)
        return false;
        
    // Store the word
    char readword[LENGTH+1];
        
    while (fscanf(file, "%s", readword) != EOF)
    {
        // Make memory for the word and put it in the node
        node* new = malloc(sizeof(node));
        strcpy(new->word, readword);
        
        //place in the correct place of the array
        unsigned int index = hash_func(readword);
        if (table[index] == NULL)
        {
            table[index] = new;
            new-> next = NULL;
        }
        else
        {
            new-> next = table[index];
            table[index] = new;
        }
        
        //increase words found
        dsize++;
    }
    
    // Get out if errors found reading te file
    if (ferror(file))
    {
        fclose(file);
        printf("Error reading %s\n", dictionary);
        unload();
        return false;
    }
    
    // Close File
    fclose(file);
    return true;
}        

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    char lower[LENGTH +1];
    int length = strlen(word);

    // Convert upper cases into lower cases
    for (int i = 0; i <= length +1 ; i++)
        lower[i] = tolower(word[i]);
    lower[length+1]= '\0';
    
    //Find where word should be
    unsigned int index = hash_func(lower);
    
    //if index gets to last hashtable, return false
    if(table[index] == NULL)
        return false;
    
    //pointer that compares to word
    node* pointer = table[index];

    //compare to word
    while( pointer != NULL)
    {
        if (strcmp(lower, pointer->word) ==0) 
            return true;
        pointer = pointer->next;
    }
    
    // if word is not found
    return false;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    if (dsize >0)
        return dsize;
    else
        return 0;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    unsigned int index =0;

    while (index < HASH_SIZE)
    {
        if (table[index] == NULL)
        {
            index++;
        }
        else
        {
            while(table[index] != NULL)
            {
                node *pointer = table[index];
                table[index] = pointer->next;
                free(pointer);
            }
            index++;
        }
    }
    return true;
}
