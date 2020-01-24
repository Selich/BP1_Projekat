#ifndef FILE_H_INCLUDED
#define FILE_H_INCLUDED

// Staticka rasuta
// lineaarno trazzenje lokacija
// fiksni korak k


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_NAZIV 30
#define MAX_EB 7
#define MAX_TIP 20
#define MAX_POVRSINA 1000000000
#define MAX_FILENAME 1000

// faktor baketiranja - b
#define b 3
// broj baketa - B
#define B 7
// fiksni korak - k
#define k 3

#define FREE 0
#define IN_USE 1

typedef struct {
    char evidencioni_broj[MAX_EB];
    char naziv_katastarske_opstine[MAX_NAZIV];
    unsigned int povrsina_parcele;
    char tip_parcele[MAX_TIP];
    int status_flag;
} Parcela;

typedef struct {
    Parcela slogovi[b];
} Baket;

typedef struct {
    FILE* fp;
    char* name;
} File;

int read(File* file, unsigned int adr, Baket* baket);
int write(File* file, unsigned int adr, Baket* baket);
int create();

#endif