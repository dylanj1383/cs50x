#include <stdio.h>
#include <cs50.h>

int main(int argc, string argv[]){
    if (argc != 2){
        printf("Missing command line argument or too many arguments!\n");
        return 1; //any number other than 0. the developer knows that 1 means no cmd line arg
        //you can do echo $? in the line after ur program completed to see the status code it exited with
    }
    printf("hello %s\n", argv[1]);
}