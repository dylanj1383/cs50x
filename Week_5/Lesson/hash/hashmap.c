#include <stdio.h>

//lets say we wanted a dict of ppl
typedef struct node{
    char* name;
    char* number;
    struct node* ptr;
} node;

int main(void){
    node* dictionary[26]; //we've made a dict now. thats it. (except for making insertion/lookup functions, etc)
}