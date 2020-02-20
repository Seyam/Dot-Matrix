#include <Wire.h>
#include <RtcDS3231.h>
//#include <ESP8266WiFi.h>
//#include <ESP8266WebServer.h>

RtcDS3231<TwoWire> Rtc(Wire);
//ESP8266WebServer server(80);

//const char* ssid = "DataSoft_WiFi";
//const char* password =  "support123";

int hh=0,mm=0;

void setup ()
{
    Serial.begin(115200);
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
    
//    WiFi.begin(ssid, password);  //Connect to the WiFi network
// 
//    while (WiFi.status() != WL_CONNECTED) {  //Wait for connection
//      delay(500);
//      Serial.println("Waiting to connect...");
//    }
//    
//    Serial.print("IP address: ");
//    Serial.println(WiFi.localIP());  //Print the local IP
//  
//    server.on("/", handle_index);
//    
//    server.begin(); //Start the server
}

void loop () 
{
//    server.handleClient(); //Handling of incoming requests
    RtcDateTime now = Rtc.GetDateTime();
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
    Serial.print(now.Second(), DEC);
    
    delay(1000); // one second
}

void handle_index() {
//  server.send(200, "text/plain", "This is an index page.");
}
