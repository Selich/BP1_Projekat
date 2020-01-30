#include "file.h"
#include "constraints.h"
#include "checks.h"
#include "util.h"
#include "baket.h"
#include <regex.h>


// 1. formiranje prazne datoteke (sa B baketa i b faktorom baketiranja) pri čemu korisnik zadaje
// naziv nove datoteke
void make(File* file){

    char *name = (char*) malloc(sizeof(char) * MAX_FILENAME);
    char path[20+MAX_FILENAME];
    int option;

    strcpy(path, "./files/");

    printf("Unesite naziv datoteke: ");
    scanf("%s", name);

    strcat(path, name);
    printf("%s", path);

    FILE* fp = fopen(path, "rb");

    if (fp) {
        printf(" Datoteka je vec formirana. \n");
        printf("\t 1. Otvorite postojecu. \n");
        printf("\t 2. Napravite novu sa istim imenom. \n");
        printf("\t 0. Exit. \n");
        scanf("%d", &option);
        if(option == 1){
            file->is_open = 1;
            file->name = name;
            file->fp = fp;
            success_print("File opened",NULL);
            return;
        } else if (!option){
            return;
        }
    }

    FILE* new = fopen(path, "wb+");
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

}
// 2. izbor aktivne datoteke zadavanjem njenog naziva
void open(File* file) {

    // char name[MAX_FILENAME];
    char path[MAX_FILENAME + 20];
    strcpy(path, "./files/");

    if (file->is_open){
        int option;
        error_print("Otvorena datoteka", file->name);
        printf("\n");
        printf("\n\t0. Nastavite dalje sa otvorenom datotekom");
        printf("\n\t1. Otvorite novu datoteku.\n");
        scanf("%d",&option);
        if(!option){ return; }
    }

    char *name = safe_string_input("naziv datoteke", MIN_FILENAME, MAX_FILENAME);

    strcat(path, name);

    FILE *fp = fopen(path, "rb+");
    if(!fp) {
        error_print("File does not exist", name);
        return;
    }
    file->is_open = 1;
    file->name = name;
    file->fp = fp;
    success_print("File opened", file->name);
}

// 3. prikaz naziva aktivne datoteke [meni i prve tri tačke 
void show(File* file){
    file->is_open
    ? printf("\nFile: %s\n", file->name)
    : printf("\nNije otvorena nijedna datoteka!\n");
}



// 4. upis novog sloga u aktivnu datoteku direktnim unosom podataka u realnom vremenu (3*)
// TODO: Prekoracioci
void write(File* file){

    if(!is_file_opened(file)) return;

    char path[MAX_FILENAME + 20];
    strcpy(path, "./files/");
    strcat(path, file->name);


    unsigned int ev;
    int adresa;
    Baket baket;

    ev = safe_number_input("EV", MIN_EB, MAX_EB);

    adresa = transform(ev, CCKK);

    baket = search(file->fp, adresa);


    printf("\n\nProveravamo da li je moguce upisati slog...\n");

    for (int i = 0; i < b; i++) {

        if(baket.slogovi[i].evidencioni_broj == ev) {
            printf("\n IN_IF\n");
            switch (baket.slogovi[i].status_flag) {
                case IN_USE:
                    error_print("Vec postoji", NULL);
                    return;
                case FREE:
                    baket.slogovi[i].status_flag = IN_USE;
                    baket.slobodni--;
                    fseek(file->fp, sizeof(Baket) * adresa,SEEK_SET);
                    fwrite(&baket, sizeof(Baket),1, file->fp);
                    success_print("Status je sada aktivan", file->name);
                    break;
                default:
                    error_print("Nekonzistentno stanje statusa", file->name);
                    break;
            }
        }
    }
    if(baket.prekoracioci) 
        if(search_prekoracioci(file->fp, &baket, adresa, ev))
            return;

    printf("\nMozemo upisati slog!\n");

    Parcela parcela = input_parcela();

    if (baket.slobodni) {
        printf("\nPostoje baketi sa slobodnim slogovima\n");
        for (int i = 0; i < B; i++) {
            if (baket.slogovi[i].status_flag == FREE) {

                if(DEBUG) printf("\nUnutar slobodnog sloga %d", i);
                add_to_baket(&baket, parcela, i);

                if (DEBUG)
                    baket_print(adresa, &baket);

                write_baket(file->fp, &baket, adresa);

                return;
            }
        }

    }

    // if (baket.prekoracioci) {

    //     for (int i = 1; i <= B; ++i){
    //         int adr = get_adr(adresa,i);
    //         Baket temp = search(file,adr);
    //         short krajTrazenja = 0;
    //         for (int j = 0; j < b; ++j) {
    //             Parcela *slog = &baket.slogovi[i]);
    //             if (slog->status_flag == FREE) return;
    //             if (slog->evidencioni_broj == parcela.evidencioni_broj){
    //                 switch (slog->status_flag) {
    //                     case IN_USE:
    //                         error_print("Vec postoji", NULL);
    //                         return;
    //                     case FREE:
    //                         slog->status_flag = IN_USE;
    //                         temp = search(file,adr);
    //                         baket.prekoracioci++;
    //                         baket = search(file,adr);
    //                         success_print("Status je sada aktivan", file->name);
    //                         return;
    //                     default:
    //                         error_print("Nekonzistentno stanje statusa", file->name);
    //                         break;
    //                 }
    //             }
    //         }
    //     }
    // }
}
// 5. prikaz svih slogova aktivne datoteke zajedno sa adresom baketa i rednim brojem sloga u baketu (2*)
void read(File* file){

    if(!is_file_opened(file)) return;

    Baket* temp = (Baket*) malloc(sizeof(Baket));
    FILE* file_temp = file->fp;
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
void lrem(File *file){

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
// 7. učitavanje tačno onih slogova u dinamičku strukturu podataka u kojima vrednost obeležja
// površina parcele prelazi zadatu donju granicu, 
// sortiranje tih podataka unutar strukture
// podataka prema rastućoj vrednosti obeležja površina parcele 
//i prikaz članova tako uređene
// strukture podataka (5*)

void view1(File* file){
    unsigned int ev;
    int povrsina;
    int adresa;
    Baket baket;
    Parcela *slogovi = (Parcela*)malloc(sizeof(Parcela));
    int array_size = 0;

    if(!is_file_opened(file))
        return;

    printf("\nUnesite povrsinu:\n");
    scanf("%d", &povrsina);

    for(int adr = 0; adr < B; adr++){
        fseek(file->fp, sizeof(Baket) * adr, SEEK_SET);
        fread(&baket, sizeof(Baket), 1, file->fp);
        for (int j = 0; j < b; j++){
            if (baket.slogovi[j].povrsina_parcele > povrsina && baket.slogovi[j].status_flag == IN_USE) {
                printf("\nBaket = %d\n", baket.slogovi[j].povrsina_parcele);
                // array_size = sizeof(slogovi) / sizeof(slogovi[0]);
                array_size++;
                Parcela new_slog;
                slogovi = (Parcela *) realloc(slogovi, array_size * sizeof(Parcela));
                slogovi[array_size - 1] = new_slog;
            }
        }
    }
    printf("\nOut of for loop ");

    //sort(slogovi, array_size);

    for (int rbr = 0; rbr < array_size; rbr++) {
        printf("\n");
        printf("\n\tParcela: \t\t\t\t %d", rbr);
        printf("\n\t-------- \t\t\t\t---");
        printf("\n\t  Evidencioni broj:\t\t\t %d", slogovi[rbr].evidencioni_broj);
        printf("\n\t  Naziv katasterske opstine:\t\t%s", slogovi[rbr].naziv_katastarske_opstine);
        printf("\n\t  Povrsina parcele:\t\t\t %d", slogovi[rbr].povrsina_parcele);
        printf("\n\t  Tip parcele:\t\t\t\t%s", slogovi[rbr].tip_parcele);
        printf("\n"); 
    }


}
void view2(File* file){
    unsigned int ev;
    int povrsina;
    int adresa;
    Baket baket;
    Parcela *slogovi = (Parcela*)malloc(sizeof(Parcela));
    int array_size = 0;

    if(!is_file_opened(file))
        return;

    printf("\nUnesite povrsinu:\n");
    scanf("%d", &povrsina);

    for(int adr = 0; adr < B; adr++){
        fseek(file->fp, sizeof(Baket) * adr, SEEK_SET);
        fread(&baket, sizeof(Baket), 1, file->fp);
        for (int j = 0; j < b; j++){
            if (baket.slogovi[j].povrsina_parcele <= povrsina && baket.slogovi[j].status_flag == IN_USE) {
                printf("\nBaket = %d\n", baket.slogovi[j].povrsina_parcele);
                // array_size = sizeof(slogovi) / sizeof(slogovi[0]);
                array_size++;
                Parcela new_slog;
                slogovi = (Parcela *) realloc(slogovi, array_size * sizeof(Parcela));
                slogovi[array_size - 1] = new_slog;
            }
        }
    }
    printf("\nOut of for loop ");

    //sort(slogovi, array_size);

    for (int rbr = 0; rbr < array_size; rbr++) {
        printf("\n");
        printf("\n\tParcela: \t\t\t\t %d", rbr);
        printf("\n\t-------- \t\t\t\t---");
        printf("\n\t  Evidencioni broj:\t\t\t %d", slogovi[rbr].evidencioni_broj);
        printf("\n\t  Naziv katasterske opstine:\t\t%s", slogovi[rbr].naziv_katastarske_opstine);
        printf("\n\t  Povrsina parcele:\t\t\t %d", slogovi[rbr].povrsina_parcele);
        printf("\n\t  Tip parcele:\t\t\t\t%s", slogovi[rbr].tip_parcele);
        printf("\n"); 
    }


}

void to_csv(File* file){
    int i, count, id, micro, dcn, ds, rd;
    char *filename = file->name;

    if(is_file_opened(file))
        return;

    printf("\nCreating %s.csv file", file->name);
    strcat(filename,".csv");

    FILE* fp = fopen(filename,"w+");
    Baket temp;

    fprintf(fp, "Evidencioni Broj, Naziv, Tip, Povrsina");
    for(int adr = 0; adr < B; adr++){

        fseek(fp, sizeof(Baket) * adr, SEEK_SET);
        fread(&temp, sizeof(Baket), 1, fp);

        for(int i = 0; i < b; i++){
            if(temp.slogovi[i].status_flag == IN_USE) 
                fprintf(fp,"\n%u,%s,%s,%u",
                temp.slogovi[i].evidencioni_broj,
                temp.slogovi[i].naziv_katastarske_opstine,
                temp.slogovi[i].tip_parcele,
                temp.slogovi[i].povrsina_parcele
                );
        }

     }

    success_print("Datoteka je kreirana", filename);
}




// TODO: Acs sorting order print
// TODO: CSV
