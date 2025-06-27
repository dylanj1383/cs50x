#include <stdio.h>
#include <cs50.h>
#include <string.h>

int main(void){
    string names[] = {"dylan", "bob", "monkey"};
    string numbers[] = {"1231231234", "4324324321", "5435435442"};
    int n = 3;

    string name = get_string("Name: ");

    for (int i = 0; i < n; i++){
        if(strcmp(names[i], name) == 0){
            printf("%s's number is %s\n", name, numbers[i]);
            return 0;

        }
    }

    printf("could not find name: %s\n", name);
    return 1;
}   