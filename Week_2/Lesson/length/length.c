#include <stdio.h>
#include <cs50.h>

int string_length(string s);

int main(void){
    string name = get_string("Name: ");

    printf("The name %s has a length of %i\n", name, string_length(name));
}

int string_length(string s){
    int n = 0;

    while (s[n] != '\0'){
        n++;
    }
    return n;
}