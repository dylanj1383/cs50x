#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int get_sum(string s);

int main(void){
    string p1 = get_string("Player 1: ");
    string p2 = get_string("Player 2: ");

    int s1 = get_sum(p1);
    int s2 = get_sum(p2);

    if (s1 > s2){
        printf("Player 1 wins!\n");
    }
    else if (s1 < s2){
        printf("Player 2 wins!\n");
    }
    else{
        printf("Tie!\n");
    }
}

int get_sum(string s){
    int sum = 0;
    for (int i = 0, n = strlen(s); i < n; i++){
        if (isupper(s[i])){
            sum += POINTS[s[i]-'A'];
        }
        else if (islower(s[i])){
            sum += POINTS[s[i]-'a'];
        }
    }
    return sum;
}