//------------------------------------------------While client not conncected---------------------------------//

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) 
  {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    //if your MQTT broker has clientID,username and password
    //please change following line to if (client.connect(clientId,userName,passWord))

    
    if (client.connect(clientId.c_str()))
    {
      Serial.println("connected");
//      delay(1500);
     //once connected to MQTT broker, subscribe command if any
     //----------------------Subscribing to required topics-----------------------//
      client.subscribe("dsiot/ra/timer");
      delay(500);
      client.subscribe("dsiot/ra/timer/error");
      delay(500);
    }else{     
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again");
      mqttTryCounter++;
      Serial.println(mqttTryCounter);
      // Wait 5 seconds before retrying
      delay(5000);
    }


    if(mqttTryCounter==3){      
      Serial.println("Reconnect attempt Finish");
      mqttTryCounter=0;
//      break;
      return loop();
    }
  }//while loop
}//end reconnect()
