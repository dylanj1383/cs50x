#include <stdio.h>

typedef struct node{
    char* number; //we wantt o access someones number. A non null numnber indicates the end of a name
    struct node* children[26];
} node;

int main(void){
    //all we need is a root node and we can start building the trie


    // the only problem is that there is a massive amount of memory, even if most of the array values are not used. 
}