#include "file.h"
#include "constraints.h"


void error_print(char* msg, char* file_name){
    sprintf("\nError: %s", msg);
    if(file_name) sprintf("\nFile: %s", file_name);
}
void success_print(char* msg, char* file_name){
    sprintf("\nSuccess: %s", msg);
    if(file_name) sprintf("\nFile: %s", file_name);
}

int safe_open(char* path, char* mode){
    FILE* fp = fopen(path, mode);
    if(!fp){
        error_print("Not found", NULL);
        return;
    }
    return fp;
}

int safe_number_input(int min, int max){
    int input;
    do {
        printf("\nMin: %d", min);
        printf("\tMax: %d", max);
        fflush(stdin);
        scanf("%lu", &input);

        if(input > max || input < min)
            error_print("Out of bounds", NULL);
    } while(input > max || input < min);
    return input;
}
char* safe_string_input(int min, int max){
    char* input;
    do {
        printf("\nMin: %d", min);
        printf("\tMax: %d", max);
        fflush(stdin);
        gets(&input);

        if(strlen(input) > max || strlen(input < min))
            error_print("Out of bounds", NULL);
    } while(strlen(input) > max || strlen(input) < min);
    return input;
}