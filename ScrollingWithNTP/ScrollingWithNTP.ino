gma#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>
#include <NTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

#define DEBUG 0
 
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



//For NTP
const char *ssid     = "DataSoft_WiFi";
const char *password = "support123";

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "bd.pool.ntp.org", 21600, 60000);




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



//global timer variables
unsigned long previousMillis = 0;
long interval = 1000;


void setup ()
{
    P_R_I_N_T(115200);
    
    setup_wifi();
  
    timeClient.begin();    

     //SPI Begin
    P.begin();
    //  P.displayText(curMessage, scrollAlign, scrollSpeed, scrollPause, scrollEffect, scrollEffect);
    P.displayText(curMessage, scrollAlign, scrollSpeed,  scrollEffect, scrollEffect);// NO SCROLL PAUSE, NO FLICKERING
    
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
    
    updateClock();
    
}//END OF LOOP



void updateClock(){
  
  unsigned long currentMillis = millis();

  if(currentMillis - previousMillis > interval) {
   previousMillis = currentMillis;


      //For NTP
      timeClient.update();
      P_R_I_N_T(timeClient.getFormattedTime());    

    
//    sprintf(newMessage, " %d:%d:%d", now.Hour(), now.Minute(), now.Second());
    sprintf(newMessage, "%s", timeClient.getFormattedTime().substring(0, 5).c_str()); //sprintf() is expecting a character array, NOT a String! So use c_str() to convert it to char array.
    P_R_I_N_T(newMessage);
    newMessageAvailable = true;
  }
}



void setup_wifi() {
   delay(100);
  // We start by connecting to a WiFi network
    Serial.print("Connecting to ");
    P_R_I_N_T(ssid);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
    {
      delay(500);
      Serial.print(".");
    }
  randomSeed(micros());
  P_R_I_N_T("");
  P_R_I_N_T("WiFi connected");
  P_R_I_N_T("IP address: ");
  P_R_I_N_T(WiFi.localIP());  
}
