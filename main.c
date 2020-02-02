#include <stdio.h>
#include <regex.h>
#include "file.h"
#include "util.h"

void menu(int option, File* file){
    switch(option){
        case 1:
          make(file);
          break;
        case 2:
          open(file);
          break;
        case 3:
          show(file);
          break;
        case 4:
          write(file);
          break;
        case 5:
          read(file);
          break;
        case 6:
          lrem(file);
          break;
        case 7: 
          view1(file);
          break;
        case 8: 
          view2(file);
          break;
        case 9: 
          to_csv(file);
          break;
        case 0:
            break;
        default:
            printf("Izaberite validnu opciju\n");
            break;
    }
}

void clear(){
#if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
  system("clear");
#endif

#if defined(_WIN32) || defined(_WIN64)
  system("cls");
#endif
}

int main(){

    int option;
    File *file = (File*) malloc(sizeof(File));
    file->fp = NULL;
    file->name = "";
    file->is_open = 0;


    //if(!DEBUG) clear();
    do {
      printf("\n  -----------------------------------");
      printf("\n | 1. Formiranje prazne datoteke");
      printf("     |");
      printf("\n | 2. Otvaranje datoteke");
      printf("\t     |");
      printf("\n | 3. Prikaz aktivne datoteke");
      printf("\t     |");
      printf("\n | 4. Upis novog sloga");
      printf("\t\t     |");
      printf("\n | 5. Prikaz svih slogova");
      printf("\t     |");
      printf("\n | 6. Logicko brisanje");
      printf("\t\t     |");
      printf("\n | 7. View 1");
      printf("\t\t\t     |");
      printf("\n | 8. View 2");
      printf("\t\t\t     |");
      printf("\n | 9. To CSV");
      printf("\t\t\t     |");
      printf("\n |-----------------------------------|");
      printf("\n | 0. Kraj");
      printf("\t\t\t     |");
      printf("\n  -----------------------------------");
      printf("\n");
      printf("\nOdaberite opciju:\t\t      ");
      scanf("%d", &option);

     // clear();
      menu(option,file);

    } while (option != 0);

    return 0;

}
