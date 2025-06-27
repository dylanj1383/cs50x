#include <stdio.h>
#include <stdlib.h>
// #include <cs50.h>

//lets implement the get functions that cs50 provides ourselves
//we can do this with the scanf function builtin to c
int get_int(char* prompt);
char get_char(char* prompt);
float get_float(char* prompt);
double get_double(char* prompt);
long get_long(char* prompt);

char* get_string(char* prompt);


int main(void){
    int n = get_int("n: ");
    printf("int n is: %i\n", n);

    //note that running these after one another doesnt work cuz when i hit enter 
    //its still stored in the scanf buffer so it immediately is hit enter for the char too. 
    //we can worka round this by saying " %c" or " %i" instead of just "%c" or "%i" as the format string
    //for scan f. However, a better solution would be to clear the buffer evertime after scanning something
    //since if we enter something other than what the computer expects for any of these the remnants 
    //will still be in the buffer and won't be removed by the space

    char c = get_char("c: ");
    printf("char c is %c\n", c);

    float f = get_float("f: ");
    printf("float f is %f\n", f);

    double d = get_double("d: ");
    printf("double d is %lf\n", f);

    long l = get_long("l: ");
    printf("long l is %li\n", l);

}


int get_int(char* prompt){
    printf("%s", prompt);
    int n;
    scanf(" %i", &n); //takes in a format string and an adress of where to put it
    //note that we have to pass the adress. if we pass n it will pass by value and not by reference
    //so our n in the scope of this function will not actually change
    return n;
}

char get_char(char* prompt){
    printf("%s", prompt);
    char c;
    scanf(" %c", &c);
    return c;
}

float get_float(char* prompt){
    printf("%s", prompt);
    float f;
    scanf(" %f", &f);
    return f;
}

double get_double(char* prompt){
    printf("%s", prompt);
    double d;
    scanf(" %lf", &d);
    return d;
}

long get_long(char* prompt){
    printf("%s", prompt);
    long l;
    scanf(" %li", &l);
    return l;
}

char* get_string(char* prompt){
    printf("%s", prompt);

    // char* s;
    // scanf(" %s", s); //we pass in s itself since s is already a memory adress (pointer)
    //note that this is dangerous. s is a pionter to an adress in mempory, but we haven't allocated memory
    //for the length of the whole string (we dont know how long it will be)
    //so we are accessing memory that "isn't ours"; we could be overwriting some important memory

    //if we knew the length of the string, we could say:
    // char* s = malloc(n);
    // or 
    // char s[n]; , which is effectively the same

    char* s = malloc(100);
    //note we can't use char s[100]; here since that creates memory for the stack, which goes away once the function is returned
    scanf(" %s", s);
    return s;
}