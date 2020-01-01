#include <stdio.h>
#include "options.h"

int remove(){
    return 1;
}

Option options[] = {
    { 1, remove }
};

int menu(char option){

    for(int i = 0; i < 2; i++)
       printf("%d. %s\n", options[i].num, options[i].name);

    (*options[atoi(option)].name)

}


int main(){

    char option;

    do
        menu(option);
    while ((option = getc(stdin)) != '0')

}