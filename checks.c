#include "checks.h"
#include "file.h"
#include "util.h"

short is_file_opened(File* file){
    if (!file->is_open){
        error_print("Not opened", file->name);
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