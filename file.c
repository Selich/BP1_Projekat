#include "file.h"
#include "file.h"
#include "constraints.h"


int safe_open(char* path, char* mode){
    FILE* fp = fopen(path, mode);
    if(fp == NULL){
        printf("\nError: File '%s' not created", path);
        return;
    }
    return fp;
}

Baket create_baket(){
        Baket baket;
        memset(&baket, 0, sizeof(Baket));
        for(int i=0; i< b; i++)
            baket.slogovi[i].status_flag = FREE;
        return baket;
}

int is_out_of_range(unsigned int adr){
    if(adr < 1 || adr > B) {
        printf("\n Out of range error");
        return 1;
    }

    return 0;

}

void error_print(char* err_type, char* file_name){
    sprintf("\nError: %s", err_type);
    sprintf("\nFile: %s", file_name);

}
int create(){
    File file;

    printf("\nUnesite naziv datoteke: ");
    fflush(stdin);
    gets(file.name);
    // system("cls");

    file.fp = safe_open(file.name, "wb");

    if(!file.fp) {
        Baket baket = create_baket();
        for(int i=1; i<=B; i++)
            UpisiBaket(&file, i, &baket);

        printf("\n *** Datoteka '%s' je uspesno kreirana. *** \n", dat.ime);
    }

    fclose(file.fp);

    return 0;
}

int read(File* file, unsigned int adr, Baket* baket){ 

    if(!is_out_of_range(adr)){
        if(fseek(file->fp, (adr-1)*sizeof(Baket), SEEK_SET)) 
            error_print("fseek",file->name);
        if(!fread(baket, sizeof(Baket), 1, file->fp))
            error_print("fwrite",file->name);
    }
}

int write(File* file, unsigned int adr, Baket* baket){ 

    if(!is_out_of_range(adr)){
        if(fseek(file->fp, (adr-1)*sizeof(Baket), SEEK_SET)) 
            error_print("fseek",file->name);
        if(!fwrite(baket, sizeof(Baket), 1, file->fp))
            error_print("fwrite",file->name);
    }
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
void add(File* file) {

    Baket baket;
    Parcela p;
    memset(&p, 0, sizeof(Parcela));

    p.status_flag = IN_USE;

    printf("\nEvidencioni broj: ");
    p.evidencioni_broj = safe_string_input(0,7);
    printf("\nNaziv katastarske opstine: ");
    p.naziv_katastarske_opstine = safe_string_input(0,7);
    printf("\nEvidencioni broj: ");
    p.povrsina_parcele = safe_number_input(0,7);
    printf("\nTip parcele: ");
    p.tip_parcele = safe_string_input(0,7);


}