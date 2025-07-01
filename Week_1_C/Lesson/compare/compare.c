#include <stdio.h>
#include <cs50.h>

int main(void) {
    int x = get_int("Enter an integer x: ");
    int y = get_int("Enter another integer y: ");

    if (x<y) {
        printf("x is less than y. x is %i, y is %i\n", x, y);
    }
    else if (x>y){
        printf("x is greater than y. x is %i, y is %i\n", x, y);
    }
    else{
        printf("x is equal to y. x and y are both %i\n", x);
    }
    
    printf("now I will increase x by 1 and increase y by 10\n");
    x++;
    y+=10;
    printf("x and y are now %i and %i respectively\n", x, y);
}