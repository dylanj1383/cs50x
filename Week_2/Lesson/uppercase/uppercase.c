#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main(void){
    string s = get_string("Enter a string: ");

    printf("Output: ");
    // int increment;
    for (int i = 0, n = strlen(s); i < n; i++){
        // increment = ('a' <= s[i] && s[i] <= 'z') ? 'A'-'a' : 0;
        // printf("%c", s[i]+increment);

        printf("%c", toupper(s[i]));
    }
    printf("\n");
}