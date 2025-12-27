#ifndef FUNCTIONS_H
#define FUNCTIONS_H

struct combination {
    float R1;
    float R2;
    float error;
};

int calculation_fun(float Uin, float Uout,int selection, struct combination error[], int E_COUNT, int possible_R);

void sortieren(struct combination arr_to_sort[],int anzahl);

void user_input(float* add_Uout, float* add_Uin, int* add_selection);

void guo(struct combination results[], int , float, float);

void line(char, int);

#endif
