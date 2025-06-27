#include <stdio.h>
#include <cs50.h>
#include <string.h>

int main(void){
    FILE* file = fopen("phonebook.csv", "a"); 
    //the w is saying write mode. This will overwrite the first line if i call the program many times
    //if we use a instead it will append

    //it is always best practice to check if there was an issue allocating memory or opening a file
    if (file == NULL){
        return 1;
    }

    char* name = get_string("Name: ");
    char* number = get_string("Number: ");


    fprintf(file, "%s, %s\n", name, number);

    fclose(file);
}