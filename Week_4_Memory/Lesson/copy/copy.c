#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h> //needed for malloc

int main(void){
    char* s = get_string("s: ");


    // char* t = s; //this didn't actually create a copy as we indented; now t and s both point to the same memory adress


    // t[0] = toupper(t[0]);

    // printf("s: %s\n", s);
    // printf("t: %s\n", t);


    //malloc: a function in c to which you pass in how many bytes of memory you want and it will hand you back some memory
    //it will return the adress of the first byte in memory for the sequence of bytes you requested

    //free is the opposite; when you are done with this memory, you can "give it back to the computer"

    //lets copy t the way we wnat now
    char* t = malloc(strlen(s)+1); //add one more byte for the null char. Rn everything is garbage at this memory

    //if something went wrong with malloc, it will return NULL (not nul) which is the adress 0
    if (t == NULL){
        return 1;
    }

    for (int i = 0, n = strlen(s); i <= n; i++){ //we do <= to n to capture the nul char at the end
        t[i] = s[i];
    }

    //we can also just do this (builtin)
    strcpy(t, s); //strcpy(destination, source)


    //lets be sure to not touch memory we don't want to
    if (strlen(t) > 0){
        t[0] = t[0] = toupper(t[0]);
    }

    printf("s: %s\n", s);
    printf("t: %s\n", t);

    //every malloc should be paired with a free
    //by default you give back all memoery when the program is finished
    //but some programs run continuously, so best to follow this practice


    //once we are done with t, free it
    free(t); //the compiler knows how many bytes I originaly asked for


    //we can use valgrind to check for memeory leaks
    //do valgrind ./compiled_file_name 
    
}