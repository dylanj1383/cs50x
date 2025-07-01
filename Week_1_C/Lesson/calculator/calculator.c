#include <stdio.h>
#include <cs50.h>

int main(void){
    int x = get_int("x: ");
    int y = get_int("y: ");

    printf("Ans: %.2f\n", (float) x/y); //casts to a float
    //%.2f means print a float formatted to 2 dps 
}