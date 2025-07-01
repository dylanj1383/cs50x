#include <stdio.h>
#include <cs50.h>

int main(void){
    //hexadecimal numbers have the digits 0 through F
    //they are denoted tih 0x#####, so we can differenciate between decimal and hexadecimal
    //memory adresses are hexadecimal  

    int n = 5;

    // &  (not &&, which means and); the address of a variable
    // *; the dereferences operator; it means "go to this adress"
    //note that the * char is also used to indicate declaring a pointer, as shown below; kinda monkey to use the same symbol
    // %p allows you to print a pointer;


    // int *p = &n; //declare a pointer variable called p. It is a pointer to an int, so we say int *p.

    
    //personally i like this syntax; int*, since it shows that it is a pionter to an int and 
    int* p = &n;


    //The value of this variable is the adress of n, given by &n. 

    printf("The adress of n is %p\n", p);
    printf("The adress of n is %p\n", &n);
    printf("The value of n is %i\n", n);
    printf("The value of n is %i\n", *p);
    printf("The value of n is %i\n", *&n);

    string s = "Hi!";

    printf("%p\n", &s); 
    printf("%p\n", s); //note that these are different. THe string type is actually a pointer istelf.
                        // so printed &s is the memory adress of that pointer
    printf("%p\n", &s[0]); //note that this is the same as printing s. So string is rlly the adress of the first character
    printf("%p\n", &s[1]); //note that this is one more than s[0], and so on for the rest
    printf("%p\n", &s[2]);
    printf("%p\n", &s[3]);
    printf("%c\n", s[3]); //remember this is the nul character


    //NOW, since strings are rlly just a pointer to a character adress in memory 
    //(with the follwoing adresses being the next) chars int he string until the /0 character
    //we can define strings in this way
    char* st = "HI!";

    //cs50 has been doing this for us with:
    // typedef char* string; //note that typedef doesn't have to be used for structs, which is the only way we've seen before

    printf("%s\n", st);


    printf("%c\n", st[0]);
    printf("%c\n", st[1]);
    printf("%c\n", st[2]);
    printf("%c\n", st[3]); //nul character signifying the end of a string


    //the above can also be done with pointer arithemtic

    printf("%c\n", *st); //print what is in the adress st
    printf("%c\n", *(st+1)); //print what is in the adress 1 more than st, Note we are adding decimal numbers.
    printf("%c\n", *(st+0x2)); // We could also add hexadecimals with the 0x### syntax
    printf("%c\n", *(st+3)); //nul character signifying the end of a string


    //using pointer arithmetic, I can also start somewhere other than the 1st char of the string

    printf("%s\n", st+1);


    //strings actually being pointers to a char explains why we cant compare strings with ==

    // char* a = "Hello";
    // char* b = "Hello"; //note that right now a and b actually have the same memory adress because the c compiler saves space and puts them together
    char* a = get_string("S1: ");

    char* b = get_string("S2: ");

    printf("a is a pointer with value %p and b is a pointer with value %p\n", a, b);
    printf("%i\n", a==b);
}