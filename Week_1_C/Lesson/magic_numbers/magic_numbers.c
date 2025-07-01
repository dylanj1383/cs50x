#include <stdio.h>

//to avoid magic numbers (random constants) in ur code - which is bad practice
#define PI 3.141592653 //dont put semicolon. 
#define DECKSIZE 52 
#define NAME "dylan"

//the compiler literally goes through and replaces the stuff on left with stuff on right

int main(void){
    printf("pi is %f, decksize is %i, name is %s\n", PI, DECKSIZE, NAME);
}