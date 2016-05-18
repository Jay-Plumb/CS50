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
// Prototypes
bool binarySearch(int value, int values[], int left, int right);
/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    /*
    if (value < 1) {
        return false;
    }else {
        for (int i = 0; i < n; i++) {
            if (value == values[i]) {
                return true;
            }
        }
        return false;
    }
    
    */
    
    
    // Search using binary search
    return binarySearch(value, values, 0, n-1);
   
}

bool binarySearch(int value, int values[], int left, int right) {
    
    if (left <= right) {
        int middle = (left + right) / 2;
        
        if (value == values[middle]) {
            return true;
        } else if (value < values[middle]) {
            right = middle - 1;
            return binarySearch(value, values, left, right);
        } else if (value > values[middle]) {
            left = middle + 1;
            return binarySearch(value, values, left, right);
        }
    }
    return false;  
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    // Bubble sort
    for (int i = 0; i < n - 1; i++) {
        for (int j = i+1; j < n; j++) {
            // Swap if element i is bigger than element j
           if (values[i] > values[j]) {
               int temp = values[i];
               values[i] = values[j];
               values[j] = temp;
           } 
        }
    }
    //printTest(values, n);
}

void printTest(int values[], int n) 
{
    for (int i = 0; i < n; i++) 
    {
        printf("%d ", values[i]);
    }
}

