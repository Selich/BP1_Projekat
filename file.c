#include "file.h"

int create(){

    FILE* file = fopen(gets(stdin), "wb");
    if(!file) {
        printf("\nError: Could not open file!\n");
        return 1;
    }


}

int read(FILE* f, unsigned int adr, Baket* baket){ 

}

int write(FILE* f, unsigned int adr, Baket* baket){ 

}