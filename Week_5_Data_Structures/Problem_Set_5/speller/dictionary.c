// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 65536;
unsigned int DICT_LEN = 0;
FILE* dict_file = NULL;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    //traverse the linked list whose head is table[i]

    for(node* ptr = table[hash(word)]; ptr != NULL; ptr = ptr->next){
        if (ptr == NULL){
            return false;
        }
        if (strcasecmp(ptr->word, word)==0){
            return true;
        }
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    unsigned int hash = 0;

    //iterate through the word and sum the ascii of the lowercase of that char

    for (int i = 0; word[i] != '\0'; i++){
        hash = hash * 31 + tolower(word[i]); //apparently multiplying by a prime helps
    }
    return hash%N; //mod by N to ensure its less than N
}


// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    dict_file = fopen(dictionary, "r");

    if (dict_file == NULL){
        return false;
    }

    char word[LENGTH+1];

    while (fscanf(dict_file, "%s\n", word) != EOF){
        node* n = malloc(sizeof(node));

        if (n == NULL){
            return false;
        }

        //put word into (*n).word
        strcpy(n->word, word);

        n->next = table[hash(word)];
        table[hash(word)] = n;

        DICT_LEN++;
    }

    fclose(dict_file);

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return DICT_LEN;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++){
        node* ptr = table[i];
        while (ptr!=NULL){
            node* n = ptr->next;
            free(ptr);
            ptr = n;
        }
    }

    return true;
}
