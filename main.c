#include <stdio.h>
#include "file.h"

int printMenu(){
    printf("\n1. Formiranje prazne datoteke ");
    printf("\n2. Otvaranje datoteke ");
    printf("\n3. Prikaz aktivne datoteke ");
    printf("\n4. Upis novog sloga ");
    printf("\n5. Prikaz svih slogova  ");
    printf("\n6. Logicko brisanje aktuelnog sloga ");
    printf("\n7. Prikaz svih parcela koji imaju povrsinu manju od");
    printf("\n0. Kraj ");
    printf("\n\nOdaberite opciju: ");
    printf("\n");
}

int menu(char option, File file){

    printMenu();

    switch(option){
    case 1: create(); 
        break;
    case 2: open(&file); 
        break;
    case 3: 
        file.is_open 
            ? printf("%s\n", file.name)
            : printf("Nema aktivnog file-a.\n");
        break;
    case 4: add(&file);
        break;
    case 5: read(&file);
        break;
    case 6: lremove(&file);
        break;
    case 7: view(&file);
        break;
    case 0:
        break;
    default:
        printf("Izaberite validnu opciju\n");
        break;
    }
}


int main(){

    char option;
    File file;

    do
        menu(option, file);
    while ((option = getc(stdin)) != '0');

}