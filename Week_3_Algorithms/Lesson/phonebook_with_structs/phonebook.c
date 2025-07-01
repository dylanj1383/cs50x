#include <stdio.h>
#include <cs50.h>
#include <string.h>

typedef struct{
    string name;
    string number;
} person;

int main(void){
    person people[3];

    //can use a loop to do the following more cleanly
    people[0].name = "dylan";
    people[0].number = "+1 333 333 3333";

    people[1].name = "dingus";
    people[1].number = "+1 888 888 8888";

    people[2].name = "dingi";
    people[2].number = "+1 777 777 7777";


    string name = get_string("Name: ");

    for (int i = 0; i < 3; i++){
        if (strcmp(people[i].name, name) == 0){
            printf("%s's phone number is %s\n", name, people[i].number);
            return 0;
        }
    }
    printf("Person with name %s not found\n", name);
    return 1;
}   
