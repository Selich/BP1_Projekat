#ifndef OPTIONS_H_INCLUDED
#define OPTIONS_H_INCLUDED

#define MAX_EB 7
#define MIN_EB 0

#define MAX_NAZIV_KO
#define MIN_NAZIV_KO

#define MAX_P_PARCELE
#define MIN_P_PARCELE

#define MAX_TIP_PARCELE
#define MIN_TIP_PARCELE

typedef struct {
    char* atribute;
    unsigned int min;
    unsigned int max;
} Ogranicenje;





#endif