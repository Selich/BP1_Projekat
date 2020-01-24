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

#define MIN_FILENAME 3
#define MAX_FILENAME 20

#define START_STRING ""
#define START_NUMBER 0

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
    unsigned int adresa;
    unsigned int slobodni;
    unsigned int prekoracioci;
} Baket;

typedef struct {
    FILE* fp;
    char* name;
    short is_open;
} File;

int read(File* file, unsigned int adr, Baket* baket);
int write(File* file, unsigned int adr, Baket* baket);
int create();
int open(File* file);
void add(File* file);
void view(File* file);

#endif