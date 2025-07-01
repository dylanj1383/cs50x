#include <stdio.h>

int main(void){
    int x;

    if (1 > 0) {
        x = 5;
    }
    else {
        x = 6;
    }

    int y = (1>0)? 5 : 6; //functionally equivalent to the code above

    printf("x and y are %i and %i respecitvely\n", x, y);
}