#define DEBUG 1
 
#if DEBUG
#define P_R_I_N_T(x) Serial.println(x)
#else
#define P_R_I_N_T(x)
#endif

int start_num=30;  // Number to countdown from
unsigned long mTime;



void setup() {
  Serial.begin(115200);
}

void loop() {
  
  //long startTime = millis();
  if((millis()/1000) < start_num){
      P_R_I_N_T(start_num -(millis()/1000));
  }
  else {
    // reached zero, flash the display
      flash();
  }
    
  //while( (millis() - startTime) < 2000) {
  //displayNumber(1217);
  //}
  //delay(1000);  
}


void flash(){
  mTime = millis();
    while(millis() < mTime+200) {
      P_R_I_N_T("DONE");  // display 0 for 0.2 second
    }
    mTime=millis();    
    while(millis() < mTime+200) {
      P_R_I_N_T("OFF");  // Turn display off for 0.2 second
    }
}




