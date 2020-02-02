#ifndef UTIL_H_INCLUDED
#define UTIL_H_INCLUDED
#include "file.h"
#include <math.h>

#define DEBUG 1


#define uint unsigned int

#define EB 1
#define NAZIV 2
#define TIP 3
#define POVRSINA 4

#define ASC 1
#define DESC 2

#define CCKK 1
#define ASCII_REGEX "[\x00-\x7F]+"

#define H_p 7.0
#define H_v 10.0
#define H_n ceil(log10(B * 1.0))
#define H_t floor(H_p - H_n / 2.0)
#define pow2(var) var * var


void print_menu();
void error_print(char* msg, char* file_name);
void success_print(char* msg, char* file_name);
void slog_print(int rbr, Baket *baket);
void baket_print(Baket *baket);
FILE* safe_open(char* path, char* mode);

unsigned int safe_number_input(char* name, int min, int max);
char* safe_string_input(char* input, int min, int max);

void add_to_baket(Baket *baket, Parcela parcela, int i);
Parcela input_parcela();

int search_prekoracioci(FILE* opened_file, Baket *baket, int adresa, unsigned int ev);
void write_baket(FILE *file, Baket *baket, int adr);
void sort(Parcela arr[], int n, int with, int order_by);
// void read_baket(File *file, int adr, Baket *baket);
Baket search(FILE *opened_file, uint adresa);

uint transform(uint key, int method);
int transform_centralnih_cifara_kljuca(unsigned int key);
FILE *create_baket(char *name);
short is_file_opened(File *file);
int is_out_of_range(unsigned int adr);

#endif
