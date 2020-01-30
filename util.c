#include <math.h>
#include "constraints.h"
#include "util.h"
#include <regex.h>
#include <string.h>



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
        for (int i = 0; i <= B; i++){
            int current_address = (i * k + adresa) % B;

            Baket temp_baket = search(opened_file, current_address);

            for (int j = 0; j < b; j++){
                if(temp_baket.slogovi[j].status_flag == FREE)
                    return 1;
                if (temp_baket.slogovi[i].evidencioni_broj == ev){
                    if (temp_baket.slogovi[i].status_flag) {
                      error_print("Slog vec postoji", NULL);
                      return 1;
                    } else {
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
void baket_print(int adr, Baket *baket){
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


unsigned int safe_number_input(char *name, int min, int max){
  unsigned int input;
  do{
    printf("\nUnesite %s:\t", name);
    printf("\nMin: %d", min);
    printf("\tMax: %d", max);
    printf("\n---------------------------");
    printf("\n");
    scanf("%u", &input);
    if(input > max && input < min)
        error_print("Enter a valid number", NULL);

  } while (input > max && input < min);
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
