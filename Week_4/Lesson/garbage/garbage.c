#include <stdio.h>

int main(void){
    int scores[1024];

    //right now everythign is garbage

    for (int i = 0; i < 1024; i++){
        printf("%i\n", scores[i]);
    }

    //note that if I have a program that is very verbose, printing a lot of stuff to screen
    //you can pipe the output to something called less which will show you only one screen full at a time

    // done as follows: 
    // ./garbage | less
}