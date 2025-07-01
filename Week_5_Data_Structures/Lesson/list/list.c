#include <stdio.h>
#include <stdlib.h>

int main(void){
    // int list[3];

    // list[0] = 1;
    // list[1] = 2;
    // list[2] = 3;

    // for (int i = 0; i < 3; i++){
    //     printf("%i\n", list[i]);
    // }


    //same thing but with pointers:
    int* list = malloc(3 *sizeof(int));

    if (list == NULL){
        return 1;
    }

    list[0] = 1;
    list[1] = 2;
    list[2] = 3;

    //time passes and i want a 4th integer
    // int* tmp = malloc(4*sizeof(int));

    // if (tmp == NULL){
    //     free(list); //it is always best practice to free everything before exiting program
    //     //we don't need to free tmp, since the allocation was unsucessful. However, 
    //     //we successfully allocated in list, which we must now free, or else we have a memory leak technically
    //     return 1;
    // }

    // for (int i = 0; i < 3; i++){
    //     tmp[i] = list[i];
    // }

    // tmp[3] = 4;

    // free(list);

    // list = tmp;

    // //print list now

    // for (int i = 0; i < 4; i++){
    //     printf("%i\n", list[i]);
    // }

    // free(list); //note i dont have to free(tmp) jere. list and temp are pointers that piont ot the same adress in memory


    //we dont need to completed allocate somewhere else (see above). 
    //If there is space, we can just reallocate our exisitng memroy
    //we do this with realloc. We pass the adress we want to reallocate and how much total memory we want
    list = realloc(list, 4*sizeof(int)); 
    //if there is existing bytes to the left of list, it will use that

    //if there isn't, then realloc will do the hard lifting we did above; it will copy the data in list to a location
    //in memory that does have enough space, and then free the old block

    //only if it can't find any space will it return null

    if (list == NULL){
        return 1;
    }

    list[3] = 4;

    // //print list now

    for (int i = 0; i < 4; i++){
        printf("%i\n", list[i]);
    }
}