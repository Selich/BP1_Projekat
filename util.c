#include "file.h"
#include "math.h"
#include "constraints.h"
#include "util.h"


void error_print(char* msg, char* file_name){
    sprintf("\nError: %s", msg);
    if(file_name) sprintf("\nFile: %s", file_name);
}
void success_print(char* msg, char* file_name){
    sprintf("\nSuccess: %s", msg);
    if(file_name) sprintf("\nFile: %s", file_name);
}

void slog_print(int rbr, Baket baket){
    printf("\n\tParcela %d:\n", rbr + 1);
    printf("\n\tEvidencioni broj:\t%u", baket.slogovi[rbr].evidencioni_broj);
    printf("\n\tNaziv katasterske opstine:\t\t%s", baket.slogovi[rbr].naziv_katastarske_opstine);
    printf("\n\tPovrsina parcele:\t\t%s", baket.slogovi[rbr].povrsina_parcele);
    printf("\n\tTip parcele:\t\t%s", baket.slogovi[rbr].tip_parcele);
}
void baket_print(int adr, Baket baket){
    printf("\n-Baket %d", adr);
    printf("\n-Broj prekoracilaca %d", baket.prekoracioci);
    for(int i = 0; i < b; i++)
        if(!baket.slogovi[i].status_flag) slog_print(i, baket);
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

Baket search(File *file, int adr){
    Baket baket;
    fseek(file->fp, sizeof(Baket) * adr, SEEK_SET);
    fread(&baket, sizeof(Baket), 1, file->fp);
    return baket;
}

int transform(unsigned int key, int method){
    switch(method){
        case CCKK: 
            return transform_centralnih_cifara_kljuca(key);
        default:
            return transform_centralnih_cifara_kljuca(key);
    }
}

int transform_centralnih_cifara_kljuca(unsigned int key) {

    unsigned int A = ifloor(k / pow(H_v, H_t)) % ifloor(pow(H_v, H_n));
    return ((A * B) / pow(H_v, H_n));
}