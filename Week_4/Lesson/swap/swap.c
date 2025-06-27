#include <stdio.h>
#include <stdlib.h>

// void swap(int a, int b);
void swap(int* a, int* b);

int main(void){
    int a = 10;
    int b = 20;

    printf("Before, a is %i and b is %i\n", a, b);
    // swap(a, b);
    swap(&a, &b);
    printf("After, a is %i and b is %i\n", a, b);

}

//note that this only swaps a and b within the scope of the function
//for primitive data types, they are passed by value, so a copy is made
// void swap(int a, int b){
//     int temp = b;
//     b = a;
//     a = temp;
// }


//how memoory is allocated for a program
 /*
Think of below as the computers memory
the top store smachine code, then globals, then the heap works its way down. The stack starts at the bottom and works its way up: 


 MACHINE CODE
 GLOBALS
 HEAP (Malloc)
 |
 v


 ^
 |
 STACK (function calls, making copies for local vars)]


 note that the heap and stack build towards each other
 this is ok as long as u dong let either get out of control, so much that they exceed the memory of the computer
 make sure to free ur mallocs to keep the heap reasonable to avoid heap overflow
 and ensure ur recursive calls have base cases to keep the stack reasonable and avoid stack overflow

 stack/heap overflow are both buffer overflow
 */


 //so, to swap as intended, we want to pass by reference (aka pass by adress)
void swap(int* a, int* b){
    int temp = *a; //  go to a and find whats in nit
    *a = *b; //put whats in b to whats in a
    *b = temp;
}