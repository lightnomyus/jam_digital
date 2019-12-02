/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "fsm.h"

void fsm_debounce(int input, int *state, int *variable) {
  static int counter = 0;
    switch (*state) {
        case TUNGGU_ON:
    {
            if (input == 1)
            {
                *variable = 1;
                *state = TUNGGU_BOUNCE_ON;
            }
            else
            {
                *state = TUNGGU_ON;
            }
      break;
    }
    case TUNGGU_BOUNCE_ON:
        {
      counter++;
            if ((input == 1) && (counter >= MAX_COUNT)){
                *state = TUNGGU_OFF;
        counter = 0;
            }
            else
            {
                *state = TUNGGU_BOUNCE_ON;
            }
            break;
        }
        case TUNGGU_OFF:
        {
            if (input == 0) {
                *variable = 0;
                *state = TUNGGU_BOUNCE_OFF;
            }
            else
            {
                *state = TUNGGU_OFF;
            }
            break;
        }
        case TUNGGU_BOUNCE_OFF:
        {

            counter++;
            if ((input == 0) && (counter >= MAX_COUNT)){
                *state = TUNGGU_ON;
        counter = 0;
            }
            else
            {
                *state = TUNGGU_BOUNCE_OFF;
            }
            break;
        }

        default:
        {

        }
    }

}

void fsm_rising_edge(int input, int *state, int *variable)
{
    switch (*state){
        case TUNGGU_ON_RS:
        {
            if (input==1)
            {
                *variable = 1;
                *state = ON_RS;
            }
            else 
            {   
                *variable = 0;
                *state = TUNGGU_ON_RS;
                
            }
            break;
        }

        case ON_RS:
        {
            if (input==1)
            {
                *variable = 0;
                *state = ON_RS;
            }
            else
            {
                *state = TUNGGU_ON_RS;
            }
            break;
        }
        default:
        {
            *state = TUNGGU_ON_RS;
            *variable = 0;
        }

    }

}

void fsm_jam(int mode_clean, int set_clean, int *state, int *minute_now, int *hour_now, int *date_now, int *month_now, int *year_now)
{
    if(mode_clean==1 && set_clean==0)
    {

            if (*state==S_TIME)
            {
                *state=S_DATE;
            }
            else if (*state==S_DATE)
            {
                *state=S_TIME;
            }
            else if (*state==S_TIME_HOUR || *state==S_DATE_HOUR)
            {
                if(*hour_now>=23)
                {
                    *hour_now=0;
                } else{
                    *hour_now+=1;
                }
            }
            else if(*state==S_TIME_MINUTE || *state==S_DATE_MINUTE)
            {
                if(*minute_now>=59)
                {
                    *minute_now=0;
                } else{
                    *minute_now+=1;
                }
            }
            else if(*state==S_TIME_DAY || *state==S_DATE_DAY)
            {
                if(*month_now==2)
                {
                    if( (*year_now%4==0 && *year_now%100 != 0) || *year_now%400==0)//kabisat
                    {
                        if(*date_now>=29)
                        {
                            *date_now=1;
                        } else
                        {
                            *date_now+=1;
                        }
                    } else//bkn kabisat
                    {
                        if(*date_now>=28)
                        {
                            *date_now=1;
                        } else
                        {
                            *date_now+=1;
                        }
                    }

                } else if(*month_now==4 || *month_now==6 || *month_now==9 || *month_now==11)
                {
                    if(*date_now>=30)
                    {
                        *date_now=1;//reset ke tangal 1 krn batasnya 30 hari
                    } else
                    {
                        *date_now+=1;
                    }

                } else if(*month_now==1 || *month_now==3 || *month_now==5 || *month_now==7 || *month_now==8 || *month_now==10 || *month_now==12)
                {
                    if(*date_now>=31)
                    {
                        *date_now=1;//reset ke tangal 1 krn batasnya 31 hari
                    } else
                    {
                        *date_now+=1;
                    }
                }
            }
            else if(*state==S_TIME_MONTH || *state==S_DATE_MONTH)
            {
                if(*month_now>=12)
                {
                    *month_now=1;
                } else
                {
                    if( (*month_now==3 || *month_now==5 || *month_now==8 || *month_now==10) && *date_now>=31){
                        *date_now=30;
                    }
                    else if(*month_now==1 && *date_now>=31){
                        *date_now=28;//maksimal bulan 2, tanpa case kabisat tdk apa-apa, ini hanya set month
                    }
                    *month_now+=1;
                }
            }


    }
    else if(mode_clean==0 && set_clean==1)
    {
        switch (*state)
        {
        case S_TIME:
            *state=S_TIME_HOUR;
            break;
        case S_TIME_HOUR:
            *state=S_TIME_MINUTE;
            break;
        case S_TIME_MINUTE:
            *state=S_TIME_DAY;
            break;
        case S_TIME_DAY:
            *state=S_TIME_MONTH;
            break;
        case S_TIME_MONTH:
            *state=S_TIME;
            break;
        case S_DATE:
            *state=S_DATE_HOUR;
            break;
        case S_DATE_HOUR:
            *state=S_DATE_MINUTE;
            break;
        case S_DATE_MINUTE:
            *state=S_DATE_DAY;
            break;
        case S_DATE_DAY:
            *state=S_DATE_MONTH;
            break;
        case S_DATE_MONTH:
            *state=S_DATE;
            break;
        default:
            break;
        }
    }
}

void fsm_lengkap(int mode_in, int set_in, int *state, int *minute_now, int *hour_now, int *date_now, int *month_now, int *year_now) {
    int mode_clean;
    int set_clean;
    int debounce_mode;
    int debounce_set;
    fsm_debounce(mode_in, &debounce_mode, &mode_clean);
    fsm_debounce(set_in, &debounce_set, &set_clean);
    fsm_jam(mode_clean, set_clean, state, minute_now, hour_now, date_now, month_now, year_now);
}
/**
 * initialize all states
 */
void fsm_jam_init(int *state){
    *state = S_TIME_HOUR;
}
