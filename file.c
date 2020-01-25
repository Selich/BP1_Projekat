#include "file.h"
#include "constraints.h"
#include "checks.h"
#include "util.h"
#include "baket.h"

int create(){
    File file;

    printf("\nUnesite naziv datoteke: ");
    file.name = safe_string_input(MIN_FILENAME, MAX_FILENAME);

    FILE* fp = fopen(file.name, "wb");

    if(!file.fp) {
        for(int i=1; i<=B; i++)
            create_baket(&file, i);

    }
    success_print("File created", file.name);
    fclose(file.fp);
    return 0;
}

void lremove(File *file){
    if(is_file_opened(file)){
        unsigned int ev_broj = safe_number_input(MIN_EB, MAX_EB);
        int adresa = transform(ev_broj, CCKK);
        Baket* baket = search(file, adresa);

        for(int i = 0; i < b; i++) {
            Parcela *slog = &(baket->slogovi[i]);
            if(slog->evidencioni_broj == ev_broj && slog->status_flag == IN_USE) {
                    slog->status_flag = FREE;
                    baket->slobodni++;

                    baket = search(file, adresa);
                    break;
            }
        }
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
    }
}

int read(File* file){ 

    Baket temp;
    if(is_file_opened(file)){
        rewind(file->fp);
        for(int adr = 0; adr < B; adr++){
            fread(&temp, sizeof(Baket), 1, file->fp);
            baket_print(adr, temp);
        }
    }

}

int write(File* file){ 
    if(is_file_opened(file)){
        Parcela input_slog;
        Baket* input_baket;

        int ev_broj = safe_number_input(MIN_EB, MAX_EB);
        int adresa = transform(ev_broj, CCKK);

        input_slog.evidencioni_broj = ev_broj;

        Baket* baket = search(file, adresa);

        for (int i = 0; i < b; i++) {
            Parcela *slog = &(baket->slogovi[i]);
            if(slog->evidencioni_broj == ev_broj) {
                switch (slog->status_flag) {
                    case IN_USE:
                        error_print("Vec postoji", NULL);
                        return;
                    case FREE:
                        slog->status_flag = IN_USE;
                        baket->slobodni--;
                        success_print("Status je sada aktivan", file->name);
                        break;
                    default:
                        error_print("Nekonzistentno stanje statusa", file->name);
                        break;
                }
            }
        }
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
    }

}
void add(File* file) {

    Baket baket;
    Parcela p;
    memset(&p, 0, sizeof(Parcela));

    p.status_flag = IN_USE;

    // printf("\nEvidencioni broj: ");
    // strcpy(p.evidencioni_broj, safe_string_input(MIN_EB,MAX_EB));
    // printf("\nNaziv katastarske opstine: ");
    // strcpy(p.naziv_katastarske_opstine, safe_string_input(MIN_NAZIV_KO,MAX_NAZIV_KO));
    // printf("\nEvidencioni broj: ");
    // p.povrsina_parcele = safe_number_input(MIN_P_PARCELE, MAX_P_PARCELE);
    // printf("\nTip parcele: ");
    // strcpy(p.tip_parcele, safe_string_input(MAX_TIP_PARCELE,MAX_TIP_PARCELE));


}