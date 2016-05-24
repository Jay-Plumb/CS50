/**
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>

#include "dictionary.h"
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
// prototype
int hash(const char *word);
int hash2(const char* word);


// struct for node
typedef struct node {
    char word[LENGTH + 1]; // Largest word in dictionary plus escape character'\0'
    struct node* next;
} node;

node* hashtable[BUCKET];
int count = 0;
/**
 * Returns true if word is in dictionary else false.
 */
 
 // Too long
bool check(const char* word)
{
    // Check if the word is in the hashtable, scan through linked list
    // map the word to index number using the hash function
    
    int hashIndex = hash(word);
    //printf("-----------\n");
    //printf("%d\n", hashIndex);
   /// printf("-----------\n");
    node* trav = hashtable[hashIndex];
    while (trav != NULL) {
       if ( strcasecmp(trav->word, word) == 0 ) {
           return true;
       } else {
           trav = trav->next;
       }
    }
    return false;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    // Local variables
    char word[LENGTH+1];
    // Using a linked-list to load dictionary into memory
    FILE* fp = fopen(dictionary, "r"); // Read in the text file
    if (fp == NULL) {
        printf("Could not open %s\n", dictionary);
        return false;
    } 

    // loop through each word in text file
    while(fscanf(fp,"%s\n", word) != EOF) {

        // Work out hash of word
        int hashIndex = hash(word);
        // TODO: create new node and store word data 
        node* newNode = malloc(sizeof(node)); 
        
        if (newNode == NULL) {
            printf("Could not create a new node");
            return false;
        }
        // Copy data inside of node
        strcpy(newNode->word, word);
        
        // Go to hashtable bucket and link node to corresponding bucket
        if (hashtable[hashIndex] == NULL) {
            hashtable[hashIndex] = newNode;
            newNode->next = NULL;
        } else {
            // Collision occurs so we append a new node to the front
            newNode->next = hashtable[hashIndex];
            hashtable[hashIndex] = newNode;
        }
        
         count++;
    }

    fclose(fp);
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    // TODO
    return count;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    
    // Loop over all array cells 
    for (int i = 0; i < BUCKET; i++) {
        
        if (hashtable[i] != NULL) {
    
            node* cursor = hashtable[i];
            while (cursor != NULL) {
                node* temp = cursor;
                cursor = cursor->next;
                free(temp);
            }
            
        }
    }
    
    return true;
}


// Replace this with a better hash
int hash(const char *word) 
{
    int len = strlen(word);
    int hash = 0;

    for(int i = 0; i < len; i++)
    {
        int x = word[i];
        if (x > 64 && x < 91)
        {
            hash += word[i] + 32;
        }
        else
        {
            hash += word[i];
        }
    }
    
    return hash % BUCKET; 
}

/*
unsigned int hash(const char* word)
{
    unsigned int count;
    unsigned int hashValue = 0;
    for(count = 0; word[count] != '\0'; count++)
        hashValue = word[count] + (hashValue << 6) + (hashValue << 16) - hashValue;
 
    return (hashValue % BUCKET);
}
*/
int hash2(const char *word)
{
    // start hash at the prime number 5381
    unsigned long hash = 5381;
    int c;

    // iterate through each letter of the word
    while ((c = *word++))
        //bitwise left shift 5, add hash, add c
        hash = ((hash << 5) + hash) + c;

    // make sure our hash is in the array
    return hash % BUCKET;
}
