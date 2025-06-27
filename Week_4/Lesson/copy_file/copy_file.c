#include <stdio.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char* argv[]){
    if (argc != 3){
        printf("Invalid number of command line arguments\n");
        return 1;
    }
    FILE* src = fopen(argv[1], "rb"); //rb = read in binary
    FILE* dst = fopen(argv[2], "wb"); //wb = write in binary

    BYTE b;

    while(fread(&b, sizeof(b), 1, src) != 0){
        fwrite(&b, sizeof(b), 1, dst);
    }

    fclose(src);
    fclose(dst);
}