#include <Button.h>
#include <DeviceManager.h>
#include <LED.h>
#include <Device.h>

DeviceManager* deviceManager;

void setup() {

  Serial.begin(9600); 

  deviceManager = new DeviceManager();
  Button* b1 = new Button(0x1000, "Simple Button", 6, handleSensorEvent);
  Button* b2 = new Button(0x1001, "Simple Button", 7, handleSensorEvent);

  LED* led1 = new LED(0x2000,"RGB LED Modul", 2);
  LED* led2 = new LED(0x2001,"RGB LED Modul", 3);
  LED* led3 = new LED(0x2002,"RGB LED Modul", 4);
  LED* led4 = new LED(0x2003,"RGB LED Modul", 5);

  deviceManager->addSensor(b1->getDeviceID(), b1);
  deviceManager->addSensor(b2->getDeviceID(), b2);
  deviceManager->addActor(led1->getDeviceID(),led1);
  deviceManager->addActor(led2->getDeviceID(),led2);
  deviceManager->addActor(led3->getDeviceID(),led3);
  deviceManager->addActor(led4->getDeviceID(),led4);

}

uint8_t buff[PROTOCOL_SIZE];
int counter = 0;

void loop()
{
  deviceManager->onLoop();
  
  if(Serial.available() > 0){
    buff[counter] = Serial.read();
    counter++;  
  }
  
  
  if(counter == PROTOCOL_SIZE){
    deviceManager->handleProtocolMessage(buff); 
    //PrintHex8(buff,sizeof(buff)); 
    Serial.print("handleProtocolMessage\n  ");
    counter = 0;
    memset(buff,0,PROTOCOL_SIZE);
  }



}

void handleSensorEvent(Protocol protocolEvent) {

  Serial.print(protocolEvent.type,HEX);
  Serial.print("\n");

  Serial.print(protocolEvent.id,HEX);
  Serial.print("\n");

  Serial.print(protocolEvent.deviceType,HEX);
  Serial.print("\n");

  Serial.print(protocolEvent.data);
  Serial.print("\n");
  Serial.print(protocolEvent.data[0],HEX);
  Serial.print("\n");


  if(protocolEvent.id == 1000)
    deviceManager->setValue(2000,0);
  else
    deviceManager->setValue(2001,1);
}



