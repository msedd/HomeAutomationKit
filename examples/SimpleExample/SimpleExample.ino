#include <Button.h>
#include <DeviceManager.h>
#include <LED.h>
#include <Device.h>

DeviceManager* deviceManager;

void setup() {

  Serial.begin(9600); 

  deviceManager = new DeviceManager(handleSensorEvent);
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

int counter = 0;
Protocol protocol;
void loop()
{
  deviceManager->onLoop();


  protocol.deviceType = DeviceTypes::NO_TYPE_AVAILABLE;
  memset(protocol.data,0,sizeof(protocol.data));

  uint8_t* buff;

  if(Serial.available() > 0){
    char c = Serial.read();
    Serial.print(c);
    switch (c){
    case 'f':
      protocol.type = ProtocolTypes::FIRMWARE_REQ;
      protocol.id = 0x0000;
      buff = deviceManager->transformToProtocolMessage(protocol);
      PrintHex8(buff,sizeof(buff));
      deviceManager->handleProtocolMessage(buff);
      break;
    case '1':
      break;

    case '2':
      break;

    case '3':
      break;

    case '4':
      break;

    default:
      return;
    }
  }
}

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




