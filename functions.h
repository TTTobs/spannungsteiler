#ifndef FUNCTIONS_H
#define FUNCTIONS_H

struct combination {
    float R1;
    float R2;
    float error;
};

int calculation_fun(float, float ,int , struct combination error[], int , int );

void sortieren(struct combination arr_to_sort[],int);

void user_input(float* , float* , int* );

void guo(struct combination results[], int , float, float);

void line(char, int);

#endif
