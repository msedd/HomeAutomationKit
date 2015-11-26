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

  //testStruct();


  if(protocolEvent.id == 1000)
    deviceManager->setValue(2000,0);
  else
    deviceManager->setValue(2001,1);
}


void testStruct(){

  //0 x 33 11F0 0e 524742204c4544204d6f64756c20 0004 
  Protocol meta;

  meta.type = 0x33;
  meta.id = 0x11F0;
  meta.deviceType = 0x0004;

  memset(meta.data,0,sizeof(meta.data));
  sprintf(meta.data, "%s", "Marko");
  //meta.data = "dsasddsasddsasdww";

  //Sending Side
  uint8_t b[sizeof(meta)];
  memcpy(b, &meta, sizeof(meta));

  PrintHex8(b,sizeof(b));
  Serial.print("\n");

  //Receiving Side
  Protocol tmp; //Re-make the struct
  memcpy(&tmp, b, sizeof(tmp));

  Serial.print(tmp.type,HEX);
  Serial.print("\n");

  Serial.print(tmp.id,HEX);
  Serial.print("\n");

  Serial.print(tmp.deviceType,HEX);
  Serial.print("\n");

  Serial.print(tmp.data);
  Serial.print("\n");

}

void PrintHex8(uint8_t *data, uint8_t length) // prints 8-bit data in hex with leading zeroes
{

  Serial.print(length); 
  Serial.print("\n"); 
  Serial.print("0x"); 
  for (int i=0; i<length; i++) { 
    if (data[i]<0x10) {
      Serial.print("0");
    } 
    Serial.print(data[i],HEX); 
    Serial.print(" "); 
  }
}



