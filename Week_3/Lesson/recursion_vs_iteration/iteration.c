#include <stdio.h>
#include <cs50.h>


int main(void){
    int n = get_int("Number of layers: ");

    for (int i = 1; i<=n; i++){
        //print i blocks
        for (int j = 0; j<i; j++){
            printf("#");
        }
        printf("\n");
    }
}

