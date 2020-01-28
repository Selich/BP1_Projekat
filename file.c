#include "file.h"
#include "constraints.h"
#include "checks.h"
#include "util.h"
#include "baket.h"
#include <regex.h>



void input(){
  char naziv[MAX_NAZIV];
  char tip_parcele[MAX_TIP];
  int povrsina;

  printf("Naziv opstine: \t");
  scanf("%s", naziv);

  printf("Tip parcele: \t");
  scanf("%s", tip_parcele);

  printf("Povrsina parcele: \t");
  scanf("%d", &povrsina);
}

// 1. formiranje prazne datoteke (sa B baketa i b faktorom baketiranja) pri čemu korisnik zadaje
// naziv nove datoteke
void make(File* file){

    char *name = malloc(sizeof(char)*MAX_FILENAME);
    int option;

    printf("Unesite naziv datoteke: ");
    scanf("%s", name);
    FILE* fp = fopen(name, "rb");

    if (fp) {
        printf("Datoteka je vec formirana. \n");
        printf("\t 1. Otvorite postojecu. \n");
        printf("\t 2. Napravite novu sa istim imenom. \n");
        printf("\t 0. Exit. \n");
        scanf("%d", &option);
        if(option == 1){
            // temp = (File*) malloc(sizeof(File));
            file->is_open = 1;
            file->name = name;
            file->fp = fp;
            // file = temp;
            success_print("File opened",NULL);
            return;
        } else if (!option){
            return;
        }
    }

    FILE* new = fopen(name, "wb+");
    printf("\nKreiramo novu datoteku...\n");
    Baket baketi[B];
    for(int i = 0; i < B; i++){
        for (int j = 0; j < b; j++){
          baketi[i].slogovi[j].evidencioni_broj = 0;
          strcpy(baketi[i].slogovi[j].naziv_katastarske_opstine, "NULL");
          strcpy(baketi[i].slogovi[j].tip_parcele, "NULL");
          baketi[i].slogovi[j].povrsina_parcele = 0;
          baketi[i].slogovi[j].status_flag = FREE;
        }
        baketi[i].adresa = i;
        baketi[i].slobodni = b;
        baketi[i].prekoracioci = 0;

        fwrite(&baketi[i], sizeof(Baket), 1, new);
    }

    file->is_open = 1;
    file->name = name;
    file->fp = new;

    success_print("File created", file->name);
    fclose(new);

}
// 2. izbor aktivne datoteke zadavanjem njenog naziva
void open(File* file) {

    char *name = malloc(sizeof(char)*MAX_FILENAME);
    FILE* fp;

    if (file->is_open){
        int option;
        printf("Datoteka %s je trenutno otvorena.\n", file->name);
        printf("Ukoliko zelite da nastavite rad sa vec otvorenom datotekom pritisnite '0'.\n");
        printf("Ako zelite da otvorite novu, pritisnite bilo koj taster");
        scanf("%d",&option);
        if(!option)
            return;
        else{
            file->is_open = 0;
        }
    }
    printf("Unesite naziv datoteke: ");
    printf("\nMin size: %d", MIN_FILENAME);
    printf("\tMax size: %d", MAX_FILENAME);
    printf("\nIskljucivo ASCII karakteri!");
    printf("\n---------------------------");
    printf("\n");
    scanf("%s",name);
    printf("%s",name);

    if(fp = safe_open(name, "rb")){
        file->is_open = 1;
        file->fp = fp;
        file->name = name;
        success_print("File opened", file->name);
    }
}


// 3. prikaz naziva aktivne datoteke [meni i prve tri tačke 
void show(File* file){
    file->is_open
    ? printf("\nDatoteka: %s.\n", file->name)
    : printf("\nNije otvorena nijedna datoteka!\n");
}


// 4. upis novog sloga u aktivnu datoteku direktnim unosom podataka u realnom vremenu (3*)
// TODO: Prekoracioci
void write(File* file){

    if(!is_file_opened(file)) return;

    Baket baket;
    FILE* opened_file = fopen(file->name, "rb+");
    unsigned int ev;
    int adresa;int check_if_in_use(){

}

    ev = safe_number_input("EV", MIN_EB, MAX_EB);

    adresa = transform(ev, CCKK);

    baket = search(opened_file, adresa);




    printf("\n\nProveravamo da li je moguce upisati slog...\n");

    for (int i = 0; i < b; i++) {

        if(baket.slogovi[i].evidencioni_broj == (int)ev) {
            printf("\n IN_IF\n");
            switch (baket.slogovi[i].status_flag) {
                case IN_USE:
                    error_print("Vec postoji", NULL);
                    return;
                case FREE:
                    baket.slogovi[i].status_flag = IN_USE;
                    baket.slobodni--;
                    fseek(opened_file, sizeof(Baket) * adresa,SEEK_SET);
                    fwrite(&baket, sizeof(Baket),1, opened_file);
                    success_print("Status je sada aktivan", file->name);
                    break;
                default:
                    error_print("Nekonzistentno stanje statusa", file->name);
                    break;
            }
        }
    }

    printf("\nMozemo upisati slog!\n");

    Parcela parcela = input_parcela();

    if (baket.slobodni) {
        printf("\nPostoje baketi sa slobodnim slogovima\n");
        for (int i = 0; i < B; i++) {
            if (baket.slogovi[i].status_flag == FREE) {

                if(DEBUG) printf("\nUnutar slobodnog sloga %d", i);

                baket.slogovi[i].status_flag = IN_USE;
                baket.slogovi[i].povrsina_parcele = parcela.povrsina_parcele;
                strcpy(baket.slogovi[i].naziv_katastarske_opstine, parcela.naziv_katastarske_opstine);
                strcpy(baket.slogovi[i].tip_parcele, parcela.tip_parcele);
                baket.slobodni--;

                if(DEBUG){
                    printf("\nBaket %d", baket.adresa);
                    printf("\nBroj prekoracilaca %d", baket.prekoracioci);
                    printf("\nSlobodnih %d", baket.slobodni);

                    for(int i = 0; i < b; i++){
                        if(baket.slogovi[i].status_flag == FREE) slog_print(i, &baket);
                        if(baket.slogovi[i].status_flag == IN_USE) slog_print(i, &baket);
                    }
                }

                fseek(opened_file, sizeof(Baket) * adresa, SEEK_SET);
                fwrite(&baket, sizeof(Baket), 1, opened_file);

                return;
            }
        }

    }
    file->fp = opened_file;

    fclose(opened_file);

    /*
    if (baket->prekoracioci) {

        for (int i = 1; i <= B; ++i){
            int adr = get_adr(adresa,i);
            Baket* temp = search(file,adr);
            short krajTrazenja = 0;
            for (int j = 0; j < b; ++j) {
                Parcela *slog = &(baket->slogovi[i]);
                if (slog->status_flag == FREE) return;
                if (slog->status_flag == input_slog.evidencioni_broj){
                    switch (slog->status_flag) {
                    case IN_USE:
                        error_print("Vec postoji", NULL);
                        return;
                    case FREE:
                        slog->status_flag = IN_USE;
                        temp = search(file,adr);
                        input_baket->prekoracioci++;
                        input_baket = search(file,adr);
                        success_print("Status je sada aktivan", file->name);
                        return;
                    default:
                        error_print("Nekonzistentno stanje statusa", file->name);
                        break;
                    }
                }
            }
        }
    }
    */
}
// 5. prikaz svih slogova aktivne datoteke zajedno sa adresom baketa i rednim brojem sloga u baketu (2*)
void read(File* file){

    if(!is_file_opened(file)) return;

    Baket* temp = (Baket*) malloc(sizeof(Baket));
    FILE* file_temp = file->fp;
    // FILE* file_temp = fopen(file->name, "rb");
    rewind(file_temp);

    if(is_file_opened(file)){
        for(int adr = 0; adr < B; adr++){

            fseek(file_temp, sizeof(Baket) * adr, SEEK_SET);
            fread(temp, sizeof(Baket), 1, file_temp);

            printf("\nBaket %d", temp->adresa);
            printf("\nBroj prekoracilaca %d", temp->prekoracioci);
            printf("\nSlobodnih %d", temp->slobodni);

            for(int i = 0; i < b; i++){
                if(temp->slogovi[i].status_flag) slog_print(i, temp);
                if(!temp->slogovi[i].status_flag) slog_print(i, temp);

            }

            printf("\n-----------------------------------\n");
        }
    }

}



// 6. logičko brisanje svih aktuelnih slogova iz aktivne datoteke (2*)
void lremove(File *file){

    if(!is_file_opened(file)){
      error_print("No active file!", NULL);
      return;
    }
    Baket baket;
    FILE *opened_file = file->fp;
    unsigned int ev;
    int adresa;

    ev = safe_number_input("EV", MIN_EB, MAX_EB);

    adresa = transform(ev, CCKK);

    baket = search(opened_file, adresa);

    printf("\nTrazimo odgovarajuci baket...\n");


    for(int i = 0; i < b; i++) {
      if(baket.slogovi[i].evidencioni_broj == (int)ev && baket.slogovi[i].status_flag) {
            printf("\nNadjen odgovarajuci baket!\n");
            baket.slogovi[i].status_flag = FREE;
            baket.slobodni++;
            fseek(opened_file, sizeof(Baket) *adresa, SEEK_SET);
            fwrite(&baket, sizeof(Baket), 1, opened_file);
            return;
        }
    }
    /*
     if (baket->prekoracioci) {
            for (int i = 1; i <= B; ++i){
            unsigned short adr = (i * k + adresa) % B;
            Baket* temp = search(file,adr);
                for (int j = 0; j < b; ++j) {
                     Parcela *slog = &(baket->slogovi[i]);
                     if (slog->evidencioni_broj == ev_broj && slog->status_flag == IN_USE){
                             slog->status_flag = FREE;

                            temp = search(file,adr);
                            temp->prekoracioci--;
                            temp = search(file,adr);

                            break;
                    }
                }
            }
        }
    success_print("Slog je obrisan", file->name);
    */
}


// TODO: Acs sorting order print
// TODO: CSV
