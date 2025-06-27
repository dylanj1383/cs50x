#include <stdio.h>
#include <cs50.h>
#include <string.h>

bool linear_search_int(int n, int len, int numbers[]);
bool linear_search_str(string s, int len, string strings[]);

int main(void){
    // int numbers[] = {20, 500, 10, 5, 1, 50};

    // int n = get_int("Number: ");

    // bool found = linear_search_int(n, 7, numbers);
    // if (found){
    //     printf("Found!\n");
    //     return 0;
    // }
    // else{
    //     printf("Not Found.\n");
    //     return 1;
    // }

    string strings[] = {"battleship", "boot", "iron", "cannon", "thimble", "top hat"};

    string s = get_string("Number: ");

    bool found = linear_search_str(s, 6, strings);
    if (found){
        printf("Found!\n");
        return 0;
    }
    else{
        printf("Not Found.\n");
        return 1;
    }

}

bool linear_search_int(int n, int len, int numbers[]){
    for (int i = 0; i < len; i++){
        if (numbers[i] == n){
            return true;
        }
    }
    return false;
}


bool linear_search_str(string s, int n, string strings[]){
    for (int i = 0; i < n; i++){
        // if (strings[i]==s){
        if (strcmp(strings[i], s) == 0){
            return true;
        }
    }
    return false;
}