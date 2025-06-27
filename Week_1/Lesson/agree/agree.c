#include <stdio.h>
#include <cs50.h>

int main(void){
    char c = get_char("Do you agree to the terms and conditions above (y/n)? ");

    if (c=='y' || c=='Y'){
        printf("Terms agreed. Proceeding...\n");
    }
    else if (c=='n'|| c=='N'){
        printf("Terms rejected. Returning to home...\n");
    }
    else{
        printf("Invalid input. Recieved \"%c\". Please rerun and try again.\n", c);
    }
}