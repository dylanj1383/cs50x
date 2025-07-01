#include <stdio.h>
#include <stdlib.h> //for malloc
#include <stdint.h> //needed for uint8_t
 
const int BLOCKSIZE = 512;

int is_jpeg_signature(uint8_t* a);
char* get_filename(int n);

int main(int argc, char *argv[])
{
    if (argc != 2){
        printf("Please supply exactly 1 command line argument, the name of a forensic image file\n");
        return 1;
    }
    
    FILE* forensic_image = fopen(argv[1], "r");
    if (forensic_image == NULL){
        printf("Could not open forensic image with filename: %s\n", argv[1]);
        return 1;
    }

    int n = 0;


    uint8_t* a = malloc(BLOCKSIZE); //a pointer to a uint8. We will allocate 512 bytes so we can read in blocks

    FILE* image = NULL;


    while (fread(a, sizeof(*a), BLOCKSIZE, forensic_image) != 0){
        //if start of jpeg signature; close the current file and open a new one
        if (is_jpeg_signature(a)){
            if (image != NULL){
                fclose(image);
            }
            char* s = get_filename(n);
            image = fopen(s, "w");
            free(s);


            n++;
        }

        if (image != NULL){
            //always add this block to the current file
            fwrite(a, sizeof(*a), BLOCKSIZE, image);
        }
    }

    if (image != NULL){
        fclose(image);
    }

    free(a);
    fclose(forensic_image);
}


int is_jpeg_signature(uint8_t* a){
    // 0xff 0xd8 0xff 
    //The fourth byte is either  0xe0, 0xe1, 0xe2, ... 0xec, 0xed, 0xee, or 0xef.
    // Put another way, the fourth byte’s first four bits are 1110.
    //a byte bitwise anded with 1111 0000 will give 1110 0000 if and only if it is as described above
    //                         &1110 xxxx ==> 1110 0000 --^
    //1111 0000 = 0xf0
    //1110 0000 = 0xe0


    if (*a == 0xff && 
        *(a+1) == 0xd8 && 
        *(a+2) == 0xff && 
        (*(a+3) & 0xf0) == 0xe0)
    {   
        return 1;
    }

    return 0;
}

char* get_filename(int n){
    char* s = malloc(8); // "000.jpg" + '\0' = 8 bytes
    sprintf(s, "%03d.jpg", n);
    return s;
}