// 🔧 Switch Practice Problem: Command Menu Interpreter
// Problem:

// Write a program that simulates a simple command-line tool. The user inputs a single character command, and the program does the following:

// Input	Command	Description
// a	Add	Print "Add command selected."
// d	Delete	Print "Delete command selected."
// u	Update	Print "Update command selected."
// s	Save or Submit	Print "Saving..." and fall through to Submit.
// S	Submit	Print "Submitting data..."
// any other char	Unknown	Print "Unknown command."

#include <stdio.h>
#include <cs50.h>

int main(void){
    char c = get_char("Enter command line: ");

    switch(c){
        case 'a':
            printf("Add command selected\n");
            break;
        case 'd':
            printf("Delete command selected\n");
            break;
        case 'u':
            printf("Update command selected\n");
            break;
        case 's':
            printf("Saving...\n");
            //no break. We als want to submit whenevr we save
        case 'S':
            printf("Submitting data...\n");
            break;
        default:
            printf("Unkown command\n");
            break;
    }
}