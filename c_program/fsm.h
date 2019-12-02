#ifndef FSM_H
#define FSM_H

#ifdef __cplusplus
extern "C" {
#endif

#define TUNGGU_ON 0
#define TUNGGU_BOUNCE_ON 1
#define TUNGGU_OFF 2
#define TUNGGU_BOUNCE_OFF 3
#define MAX_COUNT 3

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


void fsm_debounce(int input, int *state, int *variable);
void fsm_rising_edge(int input, int *state, int *variable);
void fsm_jam(int mode_clean, int set_clean, int *state, int *minute_now, int *hour_now, int *date_now, int *month_now, int *year_now);
void updateTime(int *state, int *minute, int *hour, int *date, int *month, int *year);
void fsm_lengkap(int mode_in, int set_in, int *state,int *state_db1,int *state_db2,int *state_rs1,int *state_rs2, int *minute_now, int *hour_now, int *date_now, int *month_now, int *year_now,int *mode_clean,int *set_clean,int *mode_db, int*set_db);


#ifdef __cplusplus
}
#endif

#endif /* NEWFILE_H */

