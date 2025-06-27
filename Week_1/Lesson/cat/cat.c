#include <stdio.h>
#include <cs50.h> //like imports in python

void repeat_meows(int n); // convention is to put main functin first. But u need to define any functions u will alter use
int get_valid_input_with_recursion(void);
int get_valid_input_with_while(void);
int get_valid_input_with_do_while(void);

int main(void){
    // for loop
    for (int i = 0; i < 3; i++){
        printf("meow\n");   
    }

    //while loop
    int i = 0;
    while (i < 3){
        printf("meow\n");
        i++;
    }
    printf("\n");

    //repeat forever
    // while (1){
    //     printf("repeating forever\n");
    // }

    int n;
    // n = get_valid_input_with_while();
    // n = get_valid_input_with_recursion();
    n = get_valid_input_with_do_while();
    repeat_meows(n);
}

int get_valid_input_with_recursion(void){
    int n = get_int("Enter a number of additional times to meow: ");
    if (n < 0){
        return get_valid_input_with_recursion();
    }
    return n;
}

int get_valid_input_with_while(void){
    int n = -1;
    while (n < 0){
        n = get_int("Enter a number of additional times to meow: ");
    }
    return n;
}

int get_valid_input_with_do_while(void){
    int n;
    do {
         n = get_int("Enter a number of additional times to meow: ");
    }
    while (n < 0);
    return n;
}


void repeat_meows(int n){
    for (int i = 0; i < n; i++){
        printf("meow\n");
    }
}
