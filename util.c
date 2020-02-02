#include <math.h>
#include <ctype.h>
#include <regex.h>
#include <string.h>
#include "constraints.h"
#include "util.h"




void find_baket(Baket *baket,  FILE** temp, int adresa){
  printf("\nTrazimo odgovarajuci baket...\n");

  fseek(*temp, sizeof(Baket) * adresa, SEEK_SET);
  fread(baket, sizeof(Baket), 1, *temp);

  printf("\nPronasli!\n");

  printf("\nBaket %d", baket->adresa);
  printf("\nBroj prekoracilaca %d", baket->prekoracioci);
  printf("\nSlobodnih %d", baket->slobodni);
  for(int i = 0; i < b; i++)
    if(!baket->slogovi[i].status_flag) slog_print(i, baket);

}


void add_to_baket(Baket *baket, Parcela parcela, int i){
    baket->slogovi[i].evidencioni_broj = parcela.evidencioni_broj;
    baket->slogovi[i].status_flag = IN_USE;
    baket->slogovi[i].povrsina_parcele = parcela.povrsina_parcele;
    strcpy(baket->slogovi[i].naziv_katastarske_opstine, parcela.naziv_katastarske_opstine);
    strcpy(baket->slogovi[i].tip_parcele, parcela.tip_parcele);
    baket->slobodni--;
}


void write_baket(FILE* file, Baket *baket, int adress){
    fseek(file, sizeof(Baket) * adress,SEEK_SET);
    fwrite(baket, sizeof(Baket),1, file);
}


int search_prekoracioci(FILE* opened_file, Baket *baket, int adresa, unsigned int ev){
    printf("\nTrazimo prekoracioce!\n");
    for (int i = 0; i <= B; i++)
    {
        int current_address = (i * k + adresa) % B;

        Baket temp_baket = search(opened_file, current_address);

        for (int j = 0; j < b; j++)
        {
            if (temp_baket.slogovi[j].status_flag == FREE)
                return 1;
            if (temp_baket.slogovi[i].evidencioni_broj == ev)
            {
                if (temp_baket.slogovi[i].status_flag)
                {
                    error_print("Slog vec postoji", NULL);
                    return 1;
                }
                else
                {
                    temp_baket.slogovi[i].status_flag = IN_USE;

                    write_baket(opened_file, &temp_baket, current_address);
                    temp_baket.prekoracioci++;
                    write_baket(opened_file, baket, adresa);

                    success_print("Status je sada aktivan", NULL);
                    break;
                }
            }
        }
    }
}


short is_file_opened(File* file){
    if (!file->is_open){
        error_print("No active file!", NULL);
        return 0;
    }
    return 1;
}
int is_out_of_range(unsigned int adr){
    if(adr < 1 || adr > B) {
        printf("\n Out of range error");
        return 1;
    }

    return 0;

}
void error_print(char* msg, char* file_name){
    printf("\nError: %s\n", msg);
    if(file_name) printf("File: %s", file_name);
}


void success_print(char* msg, char* file_name){
    printf("\nSuccess: %s\n", msg);
    if(file_name) printf("File: %s", file_name);
}
// TODO : selection


void sort_by();

void slog_print(int rbr, Baket *baket){
    printf("\n");
    printf("\n\tParcela: \t\t\t\t %d", rbr);
    printf("\n\t-------- \t\t\t\t---");
    printf("\n\t  Evidencioni broj:\t\t\t %d", baket->slogovi[rbr].evidencioni_broj);
    printf("\n\t  Naziv katasterske opstine:\t\t%s", baket->slogovi[rbr].naziv_katastarske_opstine);
    printf("\n\t  Povrsina parcele:\t\t\t %d", baket->slogovi[rbr].povrsina_parcele);
    printf("\n\t  Tip parcele:\t\t\t\t%s", baket->slogovi[rbr].tip_parcele);
}
void baket_print(Baket *baket){
    printf("\nBaket %d",  baket->adresa);
    printf("\nBroj prekoracilaca %d", baket->prekoracioci);
    printf("\nSlobodnih %d", baket->slobodni);
    for(int i = 0; i < b; i++)
        if(!baket->slogovi[i].status_flag) slog_print(i, baket);
    printf("\n-----------------------------------\n");
}

FILE* safe_open(char* path, char* mode){
    FILE* fp = (FILE*) fopen(path, mode);
    if(!fp){
        error_print("Not found", NULL);
        return NULL;
    }
    return fp;
}
int is_number(char *s) {
    while (*s) {
        if (isdigit(*s++) == 0) return 0;
    }

    return 1;
}


uint safe_number_input(char *name, int min, int max){
  int err;
  uint input;
  do
  {
      printf("\nUnesite %s:\t", name);
      printf("\nMin: %d", min);
      printf("\tMax: %d", max);
      printf("\n---------------------------\n");
      scanf("%d", &input);
      if (input > max || input < min)
          error_print("Enter a valid number", NULL);

  } while (input > max || input < min );
  printf("\n%u\n", input);

  return input;
}


Parcela input_parcela(){
  Parcela parcela;
  strcpy(parcela.naziv_katastarske_opstine, safe_string_input("Naziv katastarske opstine", MIN_NAZIV, MAX_NAZIV));
  strcpy(parcela.tip_parcele, safe_string_input("Tip parcele", MIN_TIP, MAX_TIP));
  parcela.povrsina_parcele = safe_number_input("Povrsina parcele", MIN_POVRSINA, MAX_POVRSINA);
  return parcela;
}

char* safe_string_input(char* name, int min, int max){
    char* input = (char*) malloc(sizeof(char) * max);
    printf("\nUnesite %s:\t", name);
    printf("\nMin size: %d", min);
    printf("\tMax size: %d", max);
    printf("\nIskljucivo ASCII karakteri!");
    printf("\n---------------------------");
    printf("\n");
    scanf("%s",input);
    return input;
}
void sort(Parcela arr[], int n, int with, int order_by) { 
    int i, key, j; 
    switch(with){
        case EB: {
            switch (order_by) {
            case ASC:{
                for (i = 1; i < n; i++) { 
                    key = arr[i].evidencioni_broj; 
                    j = i - 1; 
            
                    while (j >= 0 && arr[j].evidencioni_broj > key) { 
                        arr[j + 1] = arr[j]; 
                        j = j - 1; 
                    } 
                    arr[j + 1].evidencioni_broj = key; 
                } 
                break;
            }
            case DESC:{
                for (i = 1; i < n; i++) { 
                    key = arr[i].evidencioni_broj; 
                    j = i - 1; 
            
                    while (j >= 0 && arr[j].evidencioni_broj < key) { 
                        arr[j + 1] = arr[j]; 
                        j = j - 1; 
                    } 
                    arr[j + 1].evidencioni_broj = key; 
                } 
                break;

            }
            default:
            {

                for (i = 1; i < n; i++) { 
                    key = arr[i].evidencioni_broj; 
                    j = i - 1; 
            
                    while (j >= 0 && arr[j].evidencioni_broj > key) { 
                        arr[j + 1] = arr[j]; 
                        j = j - 1; 
                    } 
                    arr[j + 1].evidencioni_broj = key; 
                } 
                break;
            }
            }
        }
       case POVRSINA:{
           switch (order_by) {
           case ASC:{

                for (i = 1; i < n; i++) { 
                    key = arr[i].povrsina_parcele; 
                    j = i - 1; 
            
                    while (j >= 0 && arr[j].povrsina_parcele > key) { 
                        arr[j + 1] = arr[j]; 
                        j = j - 1; 
                    } 
                    arr[j + 1].povrsina_parcele = key; 
                } 
               break;
           }
           case DESC:{
                for (i = 1; i < n; i++) { 
                    key = arr[i].povrsina_parcele; 
                    j = i - 1; 
            
                    while (j >= 0 && arr[j].povrsina_parcele < key) { 
                        arr[j + 1] = arr[j]; 
                        j = j - 1; 
                    } 
                    arr[j + 1].povrsina_parcele = key; 
                } 
               break;
           }

           default:
           {
                for (i = 1; i < n; i++) { 
                    key = arr[i].povrsina_parcele; 
                    j = i - 1; 
            
                    while (j >= 0 && arr[j].povrsina_parcele > key) { 
                        arr[j + 1] = arr[j]; 
                        j = j - 1; 
                    } 
                    arr[j + 1].povrsina_parcele = key; 
                } 
               break;
           }
           }
       }
    }
} 

Baket search(FILE* opened_file, uint adresa){
    Baket baket;
    printf("\nTrazimo odgovarajuci baket...\n");

    fseek(opened_file, sizeof(Baket) * adresa, SEEK_SET);
    if(!fread(&baket, sizeof(Baket), 1, opened_file)){
      error_print("Nije pronadjen baket na adresi",NULL);
    } else {
      if(DEBUG){
        printf("\nPronasli!\n");
        printf("\nBaket %d", baket.adresa);
        printf("\nBroj prekoracilaca %d", baket.prekoracioci);
        printf("\nSlobodnih %d", baket.slobodni);

        for(int i = 0; i < b; i++)
          if(!baket.slogovi[i].status_flag) slog_print(i, &baket);

      }
      return baket;

    }
}
uint transform(uint key, int method){
    uint result;
    switch(method){
        case CCKK:
            result =  transform_centralnih_cifara_kljuca(key);
            break;
        default:
            result =  transform_centralnih_cifara_kljuca(key);
            break;
    }

    printf("\nADRESA: %d\n", result);

    return result;
}

int transform_centralnih_cifara_kljuca(uint key) {

    uint br_cifara = 7;
    uint osnova = 10;
    uint n = ceil(log10((double)B));
    uint t = floor((double)br_cifara - (double)n / 2.0);
    unsigned long int k2 = key * key;
    int A =
     (int)floor(k2 / pow((double)osnova, (double)t)) %
     (int)floor(pow((double)osnova, (double)n));

    A = ((A * B) / pow((double)osnova, (double)n));

    return A;
}
