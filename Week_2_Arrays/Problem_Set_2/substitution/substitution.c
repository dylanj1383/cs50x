#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

const int ALPHALEN = 26;

bool isvalidkey(string key);


int main(int argc, string argv[]){
    if (argc != 2){
        printf("Please provide key as a command line argument\n");
        return 1;
    }

    string key = argv[1];

    if (!isvalidkey(key)){
        printf("Invalid key provided\n");
        return 1;
    }

    string plaintext = get_string("plaintext: ");

    for (int i = 0, n = strlen(plaintext); i < n; i++){
        if (isalpha(plaintext[i])){
            if (isupper(plaintext[i])){
                plaintext[i] = toupper(key[tolower(plaintext[i])-'a']);
            }
            else{
                plaintext[i] = key[plaintext[i]-'a'];
            }
        }
    }


    printf("ciphertext: %s\n", plaintext);
}

bool isvalidkey(string key){
    //returns if a key is valid and converts it to lowercase at the same time
    if (strlen(key) != ALPHALEN){
        printf("wrong length");
        return false;
    }

    // static int seen[ALPHALEN]; //need to use static so it is default to zeros???
    int seen[ALPHALEN] = {0};

    for (int i = 0; i < ALPHALEN; i++){
        if (!isalpha(key[i])){
            printf("nonalpha");
            return false;
        }
        key[i] = tolower(key[i]);

        if (seen[key[i]-'a'] == 1){
            return false;
        }
        
        seen[key[i]-'a'] = 1;
    }

    return true;
}