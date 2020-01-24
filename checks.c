#include "checks.h"
#include "file.h"


// int is_file_open(File *file){
//     {
//         return;
//     }

// }
int is_out_of_range(unsigned int adr){
    if(adr < 1 || adr > B) {
        printf("\n Out of range error");
        return 1;
    }

    return 0;

}