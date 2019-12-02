/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   newfile.h
 * Author: waskita
 *
 * Created on November 20, 2019, 7:06 AM
 */

#ifndef FSM_H
#define FSM_H

#define TUNGGU_ON 0
#define TUNGGU_BOUNCE_ON 1
#define TUNGGU_OFF 2
#define TUNGGU_BOUNCE_OFF 3
#define MAX_COUNT 200

#define TUNGGU_ON_RS 0 
#define ON_RS 1
#define OFF_RS 2

#define S_TIME      0
#define S_DATE      1

#define S_YEAR      11
#define S_MONTH     12
#define S_DAY       13
#define S_HOUR      14
#define S_MINUTE    15

#define S_TIME_YEAR     21
#define S_TIME_MONTH    22
#define S_TIME_DAY      23
#define S_TIME_HOUR     24
#define S_TIME_MINUTE   25

#define S_DATE_YEAR     31
#define S_DATE_MONTH    32
#define S_DATE_DAY      33
#define S_DATE_HOUR     34
#define S_DATE_MINUTE   35
//int year=2004, month=12, date=31, hour=23, minute=59, second=56;
void fsm_debounce(int input, int *state, int *variable);
void fsm_rising_edge(int input, int *state, int *variable);
void fsm_jam(int mode_clean, int set_clean, int *state, int *minute_now, int *hour_now, int *date_now, int *month_now, int *year_now);
void fsm_lengkap(int mode_in, int set_in, int *state, int *minute_now, int *hour_now, int *date_now, int *month_now, int *year_now);
void fsm_jam_init(int *state);

#endif /* NEWFILE_H */
