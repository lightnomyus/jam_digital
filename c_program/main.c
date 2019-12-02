#include <stdio.h>
#include <stdlib.h>
#include "fsm.h"

int main()
{

    FILE *fin1, *fin2, *fin3;
    int debounce_1[500];
    int mode_in[3000];
    int set_in[3000];

    int i = 0;
    int state_debounce1 = TUNGGU_ON;
    int state_debounce2 = TUNGGU_ON;

    int state_rs1 = TUNGGU_ON_RS;
    int state_rs2 = TUNGGU_ON_RS;

    int state_jam = 0;
    int max_number1 = 0;
    int max_number2 = 0;
    int max_number3 = 0;


    int output, output1;
    int mode_clean = 0;
    int set_clean= 0;
    int mode_db;
    int set_db;
    int select;
    int year=2019, month=10, date=28, hour=22, minute=57, second=0;

    fin1 = fopen("input_debounce.txt","r");
    
    while(!feof(fin1))
    {   
        fscanf(fin1, "%d", &debounce_1[i++]);
    }
    max_number1 = i-1;
    fclose(fin1);

    fin2 = fopen("input_mode_in.txt","r");  
    i=0;
    while(!feof(fin2))
    {   
        fscanf(fin2, "%d", &mode_in[i++]);
    }
    fclose(fin2);
    max_number2 = i-1;

    i=0;
    fin3 = fopen("input_set_in.txt","r");
    while(!feof(fin3))
    {   
        fscanf(fin3, "%d", &set_in[i++]);
    }
    fclose(fin3);
    max_number3 = i-1;


    output = 0;
    output1 = 0;
    mode_clean = 0;
    set_clean = 0;
    //printf("output awal: %d\n",output);

    printf("Input mode: \n");
    printf("1. debounce-0\n");
    printf("2. jam display waktu\n");
    printf("3. debounce dan jam\n");
    scanf("%d",&select);

    switch(select){
        case 1:
        {
               //Test FSM Debounce
            for (i=0;i<max_number1;i++)
            {   
                fsm_debounce(debounce_1[i],&state_debounce1,&output);
                fsm_rising_edge(output,&state_rs1,&output1);
                printf("time: %d;input: %d;output debounce: %d;output rising edge: %d;state: %d\n",i,debounce_1[i],output,output1,state_debounce1);
            }
            break;
    
        }
        case 2:
        {
                for (i=0;i<max_number2;i++)
                    {   
                        
                        fsm_jam(mode_in[i],set_in[i], &state_jam, &minute, &hour, &date, &month, &year);
                        printf("time: %d;mode_in: %d; set_in: %d;state: %d;minute: %d;hour: %d;date: %d;month: %d;year: %d\n ",i,mode_in[i],set_in[i],
                        state_jam, minute,hour,date,month,year );
                        month++;
                    }
                break;
        }
        case 3:
        {
            // TES TOTAL
          for (i=0;i<max_number2;i++)
            {   
                fsm_lengkap(mode_in[i],set_in[i],&state_jam,&state_debounce1,&state_debounce2,&state_rs1,&state_rs2,&minute,&hour,&date,&month,&year,&mode_clean,&set_clean,&mode_db,&set_db);
                printf("time: %d;mode_in: %d;set_in : %d;mode_clean: %d; set_clean: %d;state: %d;minute: %d;hour: %d;date: %d;month: %d;year: %d\n ",i,mode_in[i],set_in[i],mode_clean,set_clean,
                state_jam, minute,hour,date,month,year );
            }
            break;

        }

    }

  return 0;
}
