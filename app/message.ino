#include <Adafruit_Sensor.h>
#include <ArduinoJson.h>



int readVoltage(){
  return voltage;   // in the 'app.ino' file
}


// modify this thing to send in the sensor voltage and 

bool readMessage(int messageId, char *payload)
{
    int voltagetosend = readVoltage();    
    
    
    StaticJsonBuffer<MESSAGE_MAX_LEN> jsonBuffer;
    JsonObject &root = jsonBuffer.createObject();
    
    root["deviceId"] = DEVICE_ID;
    root["messageId"] = messageId;
    root["voltage"] = voltagetosend;


    // writing JSON to char*
    root.printTo(payload, MESSAGE_MAX_LEN);
    return false;
}

void parseTwinMessage(char *message)
{
    StaticJsonBuffer<MESSAGE_MAX_LEN> jsonBuffer;
    JsonObject &root = jsonBuffer.parseObject(message);
    if (!root.success())
    {
        Serial.printf("Parse %s failed.\r\n", message);
        return;
    }

    if (root["desired"]["interval"].success())
    {
        interval = root["desired"]["interval"];
    }
    else if (root.containsKey("interval"))
    {
        interval = root["interval"];
    }
}











