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

int read(File* file, unsigned int adr, Baket* baket){ 

    Baket temp;
    if(is_file_opened(file)){
        rewind(file->fp);
        for(int adr = 0; adr < B; adr++){
            fread(&temp, sizeof(Baket), 1, file->fp);
            baket_print(adr, temp);
        }
    }

}

int write(File* file, unsigned int adr, Baket* baket){ 

    if(!is_out_of_range(adr)){
        if(fseek(file->fp, (adr-1)*sizeof(Baket), SEEK_SET)) 
            error_print("fseek",file->name);
        if(!fwrite(baket, sizeof(Baket), 1, file->fp))
            error_print("fwrite",file->name);
    }
}
void add(File* file) {

    Baket baket;
    Parcela p;
    memset(&p, 0, sizeof(Parcela));

    p.status_flag = IN_USE;

    printf("\nEvidencioni broj: ");
    strcpy(p.evidencioni_broj, safe_string_input(MIN_EB,MAX_EB));
    printf("\nNaziv katastarske opstine: ");
    strcpy(p.naziv_katastarske_opstine, safe_string_input(MIN_NAZIV_KO,MAX_NAZIV_KO));
    printf("\nEvidencioni broj: ");
    p.povrsina_parcele = safe_number_input(MIN_P_PARCELE, MAX_P_PARCELE);
    printf("\nTip parcele: ");
    strcpy(p.tip_parcele, safe_string_input(MAX_TIP_PARCELE,MAX_TIP_PARCELE));


}