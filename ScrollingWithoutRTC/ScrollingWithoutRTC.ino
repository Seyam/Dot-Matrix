#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>


#define DEBUG 1
 
#if DEBUG
#define P_R_I_N_T(x) Serial.println(x)
#else
#define P_R_I_N_T(x)
#endif




// Define the number of devices we have in the chain and the hardware interface
// NOTE: These pin numbers will probably not work with your hardware and may
// need to be adapted
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 4
#define CLK_PIN   D5  //D5
#define DATA_PIN  D7  //D7
#define CS_PIN    D8  //D8



// HARDWARE SPI
MD_Parola P = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);
// SOFTWARE SPI
//MD_Parola P = MD_Parola(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);



uint8_t scrollSpeed = 35;    // default frame delay value, the lower, the faster
textEffect_t scrollEffect = PA_SCROLL_LEFT;
textPosition_t scrollAlign = PA_CENTER; //PA_LEFT

uint16_t scrollPause = 2000; // in milliseconds //DISPLAYFLICKERING OCCURS AT THIS INTERVAL


// Global message buffers shared by Serial and Scrolling functions
#define  BUF_SIZE  75
char curMessage[BUF_SIZE] = { "" };
//char newMessage[BUF_SIZE] = { "Hello! Enter new message?" };
char newMessage[BUF_SIZE] = { "" };
bool newMessageAvailable = true;



int hh = 30, mm = 1;



//global timer variables
unsigned long previousMillis = 0;
long interval = 60000;


void setup ()
{
  Serial.begin(115200);
  Serial.println("READY");

  setDisplay();

  //SPI Begin
  P.begin();
  P.displayText(curMessage, scrollAlign, scrollSpeed, scrollPause, scrollEffect, scrollEffect);
    
}//SETUP ENDS




void loop () 
{

  //For Animation
  if (P.displayAnimate())
  {
//    P_R_I_N_T("Got animate command");
    
    if (newMessageAvailable)
    {
//      P_R_I_N_T("New Msg Found");
      strcpy(curMessage, newMessage);
      newMessageAvailable = false;
    }
    P.displayReset();
  }

    
    setTimer();
    
}//END OF LOOP



void setTimer(){
  
  unsigned long currentMillis = millis();

  if(currentMillis - previousMillis > interval) {
   previousMillis = currentMillis;
   Serial.println("Ticking every 60 seconds"); //3=interval
   
   mm = mm-1;
   
   if(mm == -1){
      mm = 59;
      hh = hh-1;      
   }
   if(hh == 0 && mm == 0){
      Serial.println("DONE");
      clearDisplay();

   }
    
    setDisplay();
   
  }
}

void setDisplay(){
  
    if(hh < 10 && mm < 10){
      sprintf(newMessage, "  0%d:0%d", hh, mm);
      Serial.println(newMessage);
      newMessageAvailable = true;
    }else if(hh<10 && mm>10){
      sprintf(newMessage, "0%d:%d", hh, mm);
      Serial.println(newMessage);
      newMessageAvailable = true;
    }else if(hh>10 && mm<10){
      sprintf(newMessage, " %d:0%d", hh, mm);
      Serial.println(newMessage);
      newMessageAvailable = true;
    }else{
      sprintf(newMessage, "%d:%d", hh, mm);
      Serial.println(newMessage);
      newMessageAvailable = true;
    }  
}

void clearDisplay(){
    sprintf(newMessage, " 0%d:0%d", hh, mm);
    newMessageAvailable = true;
}
