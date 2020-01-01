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

#define b 3
#define B 7
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
    Parcela parcele[b];
} Baket;

int read(FILE* file, unsigned int adr, Baket* baket);
int write(FILE* file, unsigned int adr, Baket* baket);
int create();

#endif