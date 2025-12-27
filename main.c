#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

int main()
{
    system("color 70");
    while(true)
    {
        //----------------------------------------------------------------
        //user input
        //----------------------------------------------------------------
        float Uin;
        float Uout;
        int selection;

        user_input(&Uout, &Uin, &selection);
        //----------------------------------------------------------------
        //defining the required storage for the results arr
        //----------------------------------------------------------------
        int E_COUNT;
        switch(selection)
        {
            case 0:
                E_COUNT = 12;
                break;
            case 1:
                E_COUNT = 24;
                break;
            case 2:
                E_COUNT = 48;
                break;
            default:
                return -1;
        }
        int possible_R = E_COUNT * 6;
        int max_size = possible_R * possible_R;
        struct combination results[max_size];
        //--------------------------------------------------------------
        //calculation and sorting of the error and the r1/r2 combination
        //--------------------------------------------------------------
        //safe index to count for future processing
        int count = calculation_fun(Uin, Uout, selection, results, E_COUNT, possible_R);
        sortieren(results, count);
        //--------------------------------------------------------------
        //Console Output
        //--------------------------------------------------------------
        guo(results,count,Uin, Uout);
        //--------------------------------------------------------------
        //repeat request
        //--------------------------------------------------------------
        char rep;
        while(true)
        {
            printf("Repeat calculation? (y/n): ");
            if(!scanf(" %c", &rep) || (rep!='n' && rep!='y'))
            {
                scanf("%*[^\n]");
                printf("Useless Input\n");
                continue;
            }
            break;
        }
        if(rep == 'n') break;
        system("cls");
        //-------------------------------------------------------------
    }
    return 0;
}
