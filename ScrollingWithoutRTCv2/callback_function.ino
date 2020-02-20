//-----------------------Callback function-------------------------------------//

void callback(char* topic, byte* payload, unsigned int length) {
 
  Serial.print("Message arrived in topic: ");
  Serial.println(topic);
  
//-------------------------------------Getting config data---------------------//

  if(strcmp(topic, "dsiot/ra/timer") == 0){
    
    StaticJsonDocument<256> doc;
    deserializeJson(doc, payload, length);
  
    String devId = doc["did"];
    int HH = doc["hour"];
    Serial.println(devId);
    Serial.println(HH);
   
      
    if( devId == did){
        if( HH >=1 && HH <= 48){ //sleep time within 2 hours
          Serial.println("TIME UPDATED");
          
          //update or reset variables
          hh = HH;
          mm = 0;
//          now = 0;
          lastMsgTime = millis();

          setDisplay(); 
          
          delay(2000);
          char buffer[256];
          doc["status"] = "success";
          size_t n = serializeJson(doc, buffer);
          client.publish("ra/response",buffer, n);
        }
        else{
          Serial.println("INVALID TIME");
          char buffer[256];
          doc["status"] = "failed";
          size_t n = serializeJson(doc, buffer);
          client.publish("ra/response",buffer, n);
          delay(1000);
        }
    }else if( did == "DB000" ){
        if(HH >=1 && HH <= 48){ //sleep time within 2 hours
          Serial.println("TIME UPDATED");
          
          //update or reset variables
          hh = HH;
          mm = 0;
//          now = 0;
          lastMsgTime = millis();
          
          delay(2000);
          char buffer[256];
          doc["status"] = "success";
          size_t n = serializeJson(doc, buffer);
          client.publish("ra/response",buffer, n);
        }
        else{
          Serial.println("INVALID TIME");
          char buffer[256];
          doc["status"] = "failed";
          size_t n = serializeJson(doc, buffer);
          client.publish("ra/response", buffer, n);
          delay(1000);
        }
    }else{
         //do nothing
         Serial.println("DID Mismatched");          
    }
 }//strcomp ends





   if(strcmp(topic, "dsiot/ra/timer/error") == 0){
    
    StaticJsonDocument<256> doc;
    deserializeJson(doc, payload, length);
  
    String devId = doc["did"];
    int cmd = doc["cmd"];
    Serial.println(devId);
    Serial.println(cmd);
   
      
    if( devId == did){
        if( cmd == 1){ //sleep time within 2 hours
          Serial.println("Show Error");
          
          setErrorDisplay();
          
          delay(100);
        }
        else{
          Serial.println("INVALID COMMAND");          
        }
    }else{
         //do nothing
         Serial.println("DID Mismatched");          
    }
 }//strcomp ends
     
}//Callback ends
