#include <stdio.h>
#include "file.h"

int remove(){
    return 1;
}

int printMenu(){
    printf("\n1. Formiranje prazne datoteke ");
    printf("\n2. Otvaranje datoteke ");
    printf("\n3. Prikaz aktivne datoteke ");
    printf("\n4. Upis novog sloga ");
    printf("\n5. Prikaz svih slogova  ");
    printf("\n6. Logicko brisanje aktuelnog sloga ");
    printf("\n7. Prikaz svih vozova koji imaju duzinu kompozocije manju od zadatog broja ");
    printf("\n0. Kraj ");
    printf("\n\nOdaberite opciju: ");
    printf("\n");
}

int menu(char option, Datoteka datoteka){

    printMenu();

    switch(option){
    case 1: create(); 
        break;
    case 2: open(&datoteka); 
        break;
    case 3: 
        if (datoteka.Otvorena)
            printf("Aktivna datoteka: %s \n\n", datoteka.NazivDatoteke);
        else
            printf("Nema aktivne datoteke.\n\n");
        break;
    case 4: addSlog(&datoteka);
        break;
    case 5: readFile(&datoteka);
        break;
    case 6: lremove(&datoteka);
        break;
    case 7: view(&datoteka);
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
    Datoteka datoteka;

    do
        menu(option, datoteka);
    while ((option = getc(stdin)) != '0')

}