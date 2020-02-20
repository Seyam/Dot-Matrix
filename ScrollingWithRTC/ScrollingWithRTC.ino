#include <Wire.h>
#include <RtcDS3231.h>
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
textEffect_t scrollEffect = PA_PRINT;
textPosition_t scrollAlign = PA_CENTER;
//uint16_t scrollPause = 1000; // in milliseconds // NOT REQUIRED FOR PRINT


// Global message buffers shared by Serial and Scrolling functions
#define  BUF_SIZE  75
char curMessage[BUF_SIZE] = { "" };
//char newMessage[BUF_SIZE] = { "Hello! Enter new message?" };
char newMessage[BUF_SIZE] = { "00:00" };
bool newMessageAvailable = true;


//For RTC
RtcDS3231<TwoWire> Rtc(Wire);

//int hh=22,mm=00;



//global timer variables
unsigned long previousMillis = 0;
long interval = 1000;


void setup ()
{
    Serial.begin(115200);
    Serial.println("READY");
    Rtc.Begin();

    RtcDateTime compiled = RtcDateTime(__DATE__, __TIME__);
    if (!Rtc.IsDateTimeValid())
    {
        Serial.println("RTC lost confidence in the DateTime!");
        Rtc.SetDateTime(compiled);
    }

    RtcDateTime now = Rtc.GetDateTime();
    
    Rtc.Enable32kHzPin(false);
    Rtc.SetSquareWavePin(DS3231SquareWavePin_ModeNone);


   //SPI Begin
  P.begin();
//  P.displayText(curMessage, scrollAlign, scrollSpeed, scrollPause, scrollEffect, scrollEffect);
  P.displayText(curMessage, scrollAlign, scrollSpeed,  scrollEffect, scrollEffect);// NO SCROLL PAUSE, NO FLICKERING

//initially read current datetime and plus offset our countdown mm variable by the current minute

    now = Rtc.GetDateTime();

//    scrollPause = 55000;
//    hh = 22+now.Hour();
//    mm = 60+now.Minute();
    
//    Serial.println("Minute: "+mm);
    
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
//    readSerial();
    
}//END OF LOOP



void setTimer(){
  
  unsigned long currentMillis = millis();

  if(currentMillis - previousMillis > interval) {
   previousMillis = currentMillis;
//   Serial.println("Ticking every 1 seconds"); //3=interval
//   Serial.println(previousMillis);


   //    server.handleClient(); //Handling of incoming requests
    RtcDateTime now = Rtc.GetDateTime();
//                  now = Rtc.GetDateTime();
    //Print RTC time to Serial Monitor
    
    Serial.print("\nDate:");
    Serial.print(now.Year(), DEC);
    Serial.print('/');
    Serial.print(now.Month(), DEC);
    Serial.print('/');
    Serial.print(now.Day(), DEC);
    Serial.print(" Time:");
    Serial.print(now.Hour(), DEC);
    Serial.print(':');
    Serial.print(now.Minute(), DEC);
    Serial.print(':');
    Serial.println(now.Second(), DEC); 

    

    
    
//    sprintf(newMessage, " %d:%d:%d", now.Hour(), now.Minute(), now.Second());
    sprintf(newMessage, "%d:%d", now.Hour(), now.Minute());
    Serial.println(newMessage);
    newMessageAvailable = true;
   
  }
}
