#include <math.h>
#include "constraints.h"
#include "util.h"
#include <regex.h>



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

void slog_print(int rbr, Baket *baket){
    printf("\n");
    printf("\n\tParcela: \t\t\t\t %d", rbr);
    printf("\n\t-------- \t\t\t\t---");
    printf("\n\t  Evidencioni broj:\t\t\t %d", baket->slogovi[rbr].evidencioni_broj);
    printf("\n\t  Naziv katasterske opstine:\t\t%s", baket->slogovi[rbr].naziv_katastarske_opstine);
    printf("\n\t  Povrsina parcele:\t\t\t %d", baket->slogovi[rbr].povrsina_parcele);
    printf("\n\t  Tip parcele:\t\t\t\t%s", baket->slogovi[rbr].tip_parcele);
}
void baket_print(int adr, Baket *baket){
    printf("\nBaket %d",  baket->adresa);
    printf("\nBroj prekoracilaca %d", baket->prekoracioci);
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


unsigned int safe_number_input(char *name, int min, int max){
  unsigned int input;
  printf("\nUnesite %s:\t", name);
  printf("\nMin: %d", min);
  printf("\tMax: %d", max);
  printf("\n---------------------------");
  printf("\n");
  scanf("%u", &input);
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
    regex_t re;
    regmatch_t pm;
    char *input;
    printf("\nUnesite %s:\t", name);
    printf("\nMin size: %d", min);
    printf("\tMax size: %d", max);
    printf("\nIskljucivo ASCII karakteri!");
    printf("\n---------------------------");
    printf("\n");
    gets(input);
    regcomp(&re, ASCII_REGEX, 0);
    return input;

    // if(strlen(input) > max || strlen(input) < min)

    // if(regexec(&re, input, 1, &pm, REG_EXTENDED))

}
void write_baket(File* file, int adr, Baket* baket){
  if(adr < 1 || adr > B) {
    error_print("Invalid adress", file->name);
    return;
  }

  if(fseek(file->fp, (adr - 1) * sizeof(Baket), SEEK_SET)){
    error_print("Positioning error", file->name);
    return;
  }
  if(!fwrite(baket, sizeof(Baket), 1, file->fp))
    error_print("Write error", file->name);
}

void read_baket(File *file, int adr, Baket* baket){
  if(adr < 1 || adr > B) {
    error_print("Invalid adress", file->name);
    return;
  }

  if(fseek(file->fp, (adr - 1) * sizeof(Baket), SEEK_SET)){
    error_print("Positioning error", file->name);
    return;
  }

  if(!fread(baket, sizeof(Baket), 1, file->fp))
    error_print("Read error", file->name);


}
Baket search(FILE* opened_file, int adresa){
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

int transform(unsigned int key, int method){
    int result;
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

int transform_centralnih_cifara_kljuca(unsigned int key) {


  int p = 7;
  int v = 10;
  unsigned int cifre[14];
  unsigned int temp = 0;

  unsigned long long long_key = (unsigned long long)key * key;
  int t = floor(7/ 2);
  for(int i = 0; i < 14; i++){
    cifre[i] = (unsigned int)long_key % 10;
    long_key /= 10;
  }
  printf("\nKEY:\n");
  for(int i = p*2 - 1 - t; i >= t + 1;i--){
    temp += cifre[i] * pow(v,i - t - 1);
    printf("%d",cifre[i]);
  }
  printf("\nTEMP: %u", temp);
  temp *= (B/v);
  temp += 1;
  return temp;



}
