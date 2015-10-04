/* Marial Gutierrez
 * pset 3
 * helpers.c */

/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>
#include <stdio.h>
#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    //find the initial and last number in all the arrays
    int i_number = 0;
    int l_number = n-1;

    while (i_number <= l_number)
    {
        //find the middle number
        int m_number = (i_number + l_number)/2;
        //conditions to find the wanted value
        if (values[m_number] == value)
        {
            return true;
        }
        else if (values[m_number] < value)
        {
            i_number = m_number+1;
        }
        else if (values[m_number] > value)
        {
            l_number = m_number-1;
        }
    } 
    return false;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    for (int j=0; j<n ;)
    {
        for (int i=0; i<n-1 ; i++)
        {
            while (values[i] > values[i+1])
            {
                int higher_number= values[i+1];
                values[i+1] = values[i];
                values[i] = higher_number;
            }
        }
    j++;
    }
}
//LINEAR
/*
    for (int i=0; i<n ; i++)
    {
        if (values[i] == value)
        {
            return true;
        }
    }
*/
