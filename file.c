#include "file.h"
#include "constraints.h"
#include "checks.h"
#include "util.h"
#include "baket.h"

int create(){
    File file;

    printf("\nUnesite naziv datoteke: ");
    gets(file.name);

    FILE* fp = fopen(file.name, "wb");

    if(!file.fp) {
        for(int i=1; i<=B; i++)
            create_baket(&file, i);

        success_print("File created", file.name);
    }

    fclose(file.fp);

    return 0;
}

int read(File* file, unsigned int adr, Baket* baket){ 

    if(!is_out_of_range(adr)){
        if(fseek(file->fp, (adr-1)*sizeof(Baket), SEEK_SET)) 
            error_print("fseek",file->name);
        if(!fread(baket, sizeof(Baket), 1, file->fp))
            error_print("fwrite",file->name);
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