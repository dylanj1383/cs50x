#include <stdio.h>
#include <cs50.h>

int main(int argc, string argv[]){
    if (argc <= 1){
        printf("No name provided.\n");
    }
    else{ 
        printf("Nice to meet you, %s!\n", argv[1]); //argv[0] contains ./greet
    }
}