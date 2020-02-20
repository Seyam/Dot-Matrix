#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>


#define DEBUG 1
 
#if DEBUG
#define P_R_I_N_T(x) Serial.println(x)
#else
#define P_R_I_N_T(x)
#endif

int start_num = 120;  // Number to countdown from
unsigned long mTime;



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
textPosition_t scrollAlign = PA_LEFT;
uint16_t scrollPause = 2000; // in milliseconds


// Global message buffers shared by Serial and Scrolling functions
#define  BUF_SIZE  75
char curMessage[BUF_SIZE] = { "" };
//char newMessage[BUF_SIZE] = { "Hello! Enter new message?" };
char newMessage[BUF_SIZE] = { "We Repair mobiles Here!!!" };
bool newMessageAvailable = true;



void setup()
{
  Serial.begin(115200);
  Serial.println("READY");
  
  //SPI Begin
  P.begin();
  P.displayText(curMessage, scrollAlign, scrollSpeed, scrollPause, scrollEffect, scrollEffect);

  
}



void loop()
{
  //For Animation
  if (P.displayAnimate())
  {
    P_R_I_N_T("Got animate command");
    
    if (newMessageAvailable)
    {
      P_R_I_N_T("New Msg Found");
      strcpy(curMessage, newMessage);
      newMessageAvailable = false;
    }
    P.displayReset();
  }

//  setTimer();
//readSerial();
}//LOOP ENDS



void setTimer(){
  //long startTime = millis();
  if((millis()/1000) < start_num){
    
    P_R_I_N_T(start_num -(millis()/1000));

    static char *cp = newMessage;

    double temp = 11.1;
    sprintf(newMessage, "%s", temp);
    Serial.println(newMessage);
      
//      newMessage = "Hour"
      cp = newMessage;
      newMessageAvailable = true;

      
//      strcpy(curMessage, (start_num -(millis()/1000)));
//      newMessage = (start_num -(millis()/1000));
  }
  else {
    // reached zero, flash the display
    P_R_I_N_T("Done");

  }
}








void readSerial(void)
{
  static char *cp = newMessage;

  while (Serial.available())
  {
    *cp = (char)Serial.read();
    if ((*cp == '\n') || (cp - newMessage >= BUF_SIZE-2)) // end of message character or full buffer
    {
      *cp = '\0'; // end the string
      // restart the index for next filling spree and flag we have a message waiting
      cp = newMessage;
      newMessageAvailable = true;
    }
    else  // move char pointer to next position
      cp++;
  }
}
