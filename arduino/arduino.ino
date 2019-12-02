#define modeEvtPin 13
#define setEvtPin 15

extern "C" {
    #include "fsm.h"//include library fsm
}

uint64_t previousMillis = 0;
const uint64_t interval = 1000;

int fsm_state;
int debounce_state=0;
int inputModeEvt;
int inputSetEvt;
int year=2020, month=1, date=29, hour=23, minute=59, second=56;

void bacaInputModeEvt()
{
    int debounce_mode=0;
    inputModeEvt = !(digitalRead(modeEvtPin));
    int mode_clean=0;
    fsm_debounce(inputModeEvt, &debounce_mode, &mode_clean); 
    fsm_jam(mode_clean, 0, &fsm_state, &minute, &hour, &date, &month, &year);
}

void bacaInputSetEvt()
{
    inputSetEvt = !(digitalRead(setEvtPin));
    int debounce_mode=0;
    int mode_clean=0;
    fsm_debounce(inputSetEvt, &debounce_mode, &mode_clean);
    fsm_jam(0, mode_clean, &fsm_state, &minute, &hour, &date, &month, &year);
}

void updateTime()
{
    second+=1;
    //date+=1;
    if(second==60){
        minute+=1;
        second=0;
    }
    if(minute==60){
        hour+=1;
        minute=0;
    }
    if(hour==24){
        date+=1;
        hour=0;
        minute=0;
        second=0;
    }
    if((year%4==0 && year%100 != 0) || year%400==0){
        //tahun kabisat
        if(month==2 && date==30){
            month+=1;
            date=1;
        }
    }else{
        if(month==2 && date==29){
            month+=1;
            date=1;
        }
    }
    if(month==4 || month==6 || month==9 || month==11){
        if(date==31){
            month+=1;
            date=1;
        }
    } else if(month==1 || month==3 || month==5 || month==7 || month==8 || month==10 || month==12){
        if(date==32){
            month+=1;
            date=1;
        }
    }
    if(month==13){
        year+=1;
        month=1;
        date=1;
    }
    if(fsm_state==S_DATE){
        Serial.print("Date : ");
        Serial.print(date);
        Serial.print(" : ");
        Serial.print(month);
        Serial.print(" : ");
        Serial.print(year);
        Serial.print("\n");
    } else if(fsm_state==S_TIME){
        Serial.print("Time : ");
        Serial.print(hour);
        Serial.print(" : ");
        Serial.print(minute);
        Serial.print(" : ");
        Serial.print(second);
        Serial.print("\n");
    } else{
        print_editing();
    }
}
void setup() {
    pinMode(modeEvtPin, INPUT_PULLUP);
    pinMode(setEvtPin, INPUT_PULLUP);
    Serial.begin(9600);
    attachInterrupt(digitalPinToInterrupt(modeEvtPin), bacaInputModeEvt, CHANGE);//interrupt tombol MODE_EVT
    attachInterrupt(digitalPinToInterrupt(setEvtPin), bacaInputSetEvt, CHANGE);//interrupt tombol SET_EVT
    fsm_jam_init(&fsm_state);//inisiasi state awal
}

void loop() {
    uint64_t currentMillis = millis();
    if (currentMillis - previousMillis >= interval){
        previousMillis = currentMillis;
        updateTime();//prosedur update time menggunakan timer setiap 1 detik
    }
    delay(200);
}

void print_editing()
{
        Serial.print("Editing Mode, Date:");
        Serial.print(date);
        Serial.print(" : ");
        Serial.print(month);
        Serial.print(" : ");
        Serial.print(year);
        Serial.print(", Time:");
        Serial.print(hour);
        Serial.print(" : ");
        Serial.print(minute);
        Serial.print("\n");
}
