#include <stdio.h>
#include <cs50.h>

int get_height();
void print_n_chars(char c, int n);

int main(void){
    int height = get_height();

    for (int i = 0; i < height; i++){
        print_n_chars(' ', height-i-1);
        print_n_chars('#', i+1);
        printf("  ");
        print_n_chars('#', i+1);
        printf("\n");
    }
}

int get_height(){
    int h = get_int("Height: ");

    if (1 <= h && h <= 8){
        return h;
    }
    return get_height();
}

void print_n_chars(char c, int n){
    for (int i = 0; i < n; i++){
        printf("%c", c);
    }
}