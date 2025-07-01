#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int round_int(float f);

int main(void){
    // where L is the average number of letters per 100 words in the text, and S is the average number of sentences per 100 words in the text.
    // float index = 0.0588 * L - 0.296 * S - 15.8
    string text = get_string("Text: ");

    int spaces = 1;
    int terminatings = 0;
    int letters = 0;

    int n = strlen(text);
    

    for (int i = 0; i < n; i++){
        if (text[i] == ' '){
            spaces++;
        }
        else if (text[i] == '.' || text[i] == '?' || text[i] == '!'){
            terminatings++;
        }
        else if (isalpha(text[i])){
            letters++;
        }
    }

    float L = (letters*100.0)/spaces; //average letters/100 words
    float S = (terminatings*100.0)/spaces; //average sentences/100 words

    float index = 0.0588 * L - 0.296 * S - 15.8;
    int grade = round_int(index);

    if (grade < 1){
        printf("Before Grade 1\n");
    }
    else if (grade > 16){
        printf("Grade 16+\n");
    }
    else{
        printf("Grade %i\n", grade);
    }

}

int round_int(float f){
    int intf = (int) f;
    if (f < intf+0.5){
        return intf;
    }
    return intf + 1;
}