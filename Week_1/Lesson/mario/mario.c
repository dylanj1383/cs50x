#include <stdio.h>

void print_line(char c, int n);
void print_col(char c, int n);
void print_block(char c, int rows, int cols);

int main(void){
    // printf("????\n");
    print_line('?', 4);
    print_col('#', 3);
    print_block('#', 5, 6);
}

void print_line(char c, int n){
    for (int i = 0; i<n; i++){
        printf("%c", c);
    }
    printf("\n");
}

void print_col(char c, int n){
    for (int i = 0; i < n; i++){
        printf("%c\n", c);
    }
}

void print_block(char c, int rows, int cols){
    for (int i = 0; i < rows; i++){
        // for (int j = 0; j < cols; j++){
        //     printf("%c", c);
        // }
        // printf("\n");
        print_line(c, cols);
    }
}