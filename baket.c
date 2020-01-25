#include "baket.h"

void create_baket(File *file, int i){
        Baket *baket;
        memset(baket, 0, sizeof(Baket));

        for (int j = 0; j < b; j++){
            strcpy(baket[i].slogovi[j].evidencioni_broj, "");
            strcpy(baket[i].slogovi[j].naziv_katastarske_opstine, "");
            strcpy(baket[i].slogovi[j].tip_parcele, "");
            baket[i].slogovi[j].povrsina_parcele = 0;
            baket[i].slogovi[j].status_flag = FREE;
        }
        baket[i].adresa = i;
        baket[i].slobodni = b;
        baket[i].prekoracioci = 0;
        fwrite(&baket[i], sizeof(Baket), 1, file);
}