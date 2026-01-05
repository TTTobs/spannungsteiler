#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "functions.h"
#define RMIN 10000
#define MAX_ERROR 10

int calculation_fun(float Uin, float Uout, int selection, struct combination error[], int E_COUNT, int possible_R)
{

    //---------------------------E-ROWS--------------------
    float E12_Value[12] =
    {
        1.0, 1.2, 1.5, 1.8, 2.2, 2.7, 3.3, 3.9,
        4.7, 5.6, 6.8, 8.2
    };

    float E24_Value[24] =
    {
        1.0, 1.1, 1.2, 1.3, 1.5, 1.6, 1.8, 2.0,
        2.2, 2.4, 2.7, 3.0, 3.3, 3.6, 3.9, 4.3,
        4.7, 5.1, 5.6, 6.2, 6.8, 7.5, 8.2, 9.1
    };

    float E48_Value[48] =
    {
        1.00, 1.05, 1.10, 1.15, 1.21, 1.27, 1.33,
        1.40, 1.47, 1.54, 1.62, 1.69, 1.78, 1.87,
        1.96, 2.05, 2.15, 2.26, 2.37, 2.49, 2.61,
        2.74, 2.87, 3.01, 3.16, 3.32, 3.48, 3.65,
        3.83, 4.02, 4.22, 4.42, 4.64, 4.87, 5.11,
        5.36, 5.62, 5.90, 6.19, 6.49, 6.81, 7.15,
        7.50, 7.87, 8.25, 8.66, 9.09, 9.53 };
    //------------------------------------------------------
    float *E_SEL;

    /*
    Index for documenting how many combinations are actually valid.
    mult_var_R is multiplied by 10 every time the end of the E is reached.
    looping through every possible combination and only storing it when
    RMIN and MAX_ERROR are achieved
    */
    int index = 0;
    float mult_var_R1 = 1;

    switch(selection)
    {
        case 0:
            //all ready behaves like an address so no need for &
            E_SEL = E12_Value;
            break;
        case 1:
            E_SEL = E24_Value;
            break;
        case 2:
            E_SEL = E48_Value;
            break;
        default:
            return -1;
    };

    for (int i = 0; i < possible_R; i++)
    {
            //i%E_COUNT == 0 means the end of the E_ROW is reached
            if (i > 0 && i % E_COUNT == 0) mult_var_R1 *= 10;

            //i % E_COUNT as i goes to possible_R so you dont need more count vars
            float curr_R1 = E_SEL[i % E_COUNT] * mult_var_R1;

            //reset for R2
            float mult_var_R2 = 1;

            for (int j = 0; j < possible_R; j++)
            {
                if (j > 0 && j % E_COUNT == 0) mult_var_R2 *= 10;
                float curr_R2 = E_SEL[j % E_COUNT] * mult_var_R2;

                if ((curr_R1 + curr_R2) < RMIN) continue;

                //error calculation
                float Ucalc = Uin * (curr_R2 / (curr_R1 + curr_R2));
                float error_calc = fabsf((Ucalc - Uout) / Uout * 100.0f);

                //storing struct
                if (error_calc < MAX_ERROR)
                {
                    error[index++] = (struct combination){curr_R1, curr_R2, error_calc};
                }
            }
    }
    return index;
}

void sortieren(struct combination arr_to_sort[],int anzahl)
{
    int i;
    int j;

    for(i=0;i<anzahl-1;i++)
    {
        for(j = i+1;j<anzahl;j++)
        {
            if(arr_to_sort[i].error>arr_to_sort[j].error)
            {
                struct combination temp = arr_to_sort[i];
                arr_to_sort[i] = arr_to_sort[j];
                arr_to_sort[j] = temp;
            }
        }
    }
}


void user_input(float *add_Uout, float *add_Uin, int *add_selection)
{
    while(true)
    {
        printf("Uin: ");
        if(!scanf("%f", add_Uin) || (*add_Uin <= 0.1 || *add_Uin > 10000))
        {
            scanf("%*[^\n]");
            printf("Useless Input\n");
            continue;
        }
        break;
    }

    while(true)
    {
        printf("Uout: ");
        if(!scanf("%f", add_Uout) || (*add_Uout <= 0 || *add_Uout > *add_Uin))
        {
            scanf("%*[^\n]");
            printf("Useless Input\n");
            continue;
        }
        break;
    }

    while(true)
    {
        printf("Selection 0...E12, 1...E24, 2...E48: ");
        if(!scanf("%d", add_selection) || (*add_selection < 0 || *add_selection > 2))
        {
            scanf("%*[^\n]");
            printf("Useless Input\n");
            continue;
        }
        break;
    }
}

void guo(struct combination results[], int count, float Uin, float Uout)
{

    //--------------------------------------------------------------
    //Console Output
    //--------------------------------------------------------------
    line('=',50);
    printf("\n%d Solutions within 10%% Error\nBest 5:\n",count);
    line('=',50);
    printf("\n");
    for (int i = 0; i < 5; i++)
    {
        if(results[i].R1 < 1000)
        {
            printf("%d: R1=%7.0f ",i+1,results[i].R1);
        }
        else
        {
            printf("%d: R1=%7.0f k ",i+1,results[i].R1/1000);
        }
        if(results[i].R2 < 1000)
        {
            printf("R2=%7.0f ",results[i].R2);
        }
        else
        {
            printf("R2=%7.0f k ",results[i].R2/1000);
        }
        printf("Error=%6.3f%%\n",results[i].error);
    }

    line('=',50);
    printf("\n");
    line(32,15);
    printf("____\n");
    printf("Uin ");
    line(196, 10);
    printf("%c",180);
    printf("____");
    printf("%c",195);
    line(196, 3);
    printf("%c",194);
    line(196, 3);
    printf(" Uout");
    printf("\n");
    printf("%0.1f V",Uin);
    printf("\t\t");
    if(results[0].R1 < 1000)
    {
        printf("%0.1f",results[0].R1);
    }
    else
    {
        printf("%0.1f k",results[0].R1/1000);
    }
    line(32,1);
    printf("%c",179);
    line(32,4);
    printf("%0.1f V \n",Uout);
    line(32,22);
    printf("%c%c%c\n",218,193,191);
    line(32,22);
    printf("%c%c%c",179,32,179);
    if(results[0].R2 < 1000)
    {
        printf("%0.1f\n",results[0].R2);
    }

    else
    {
        printf("%0.1f k\n",results[0].R2/1000);
    }

    line(32,22);
    printf("%c%c%c\n",192,194,217);
    line(32,23);
    printf("%c\n",179);
    printf("GND ");
    line(196, 19);
    printf("%c",193);
    line(196, 3);
    printf(" GND\n");
    //--------------------------------------------------------------
}
void line(char c, int n)
{
    //just draws a line
    for(int i = 0; i<n; i++)
    {
        printf("%c",c);
    }
}



