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

uint8_t FIRMWARE_REQ_MESSAGE[] = {0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0};
uint8_t SET_DEVICE_VALUE_MESSAGE1[] = {0x10,0x00,0x20,0x00,0x00,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
uint8_t SET_DEVICE_VALUE_MESSAGE2[] = {0x10,0x01,0x20,0x00,0x00,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
uint8_t SET_DEVICE_VALUE_MESSAGE3[] = {0x10,0x02,0x20,0x00,0x00,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
uint8_t SET_DEVICE_VALUE_MESSAGE4[] = {0x10,0x03,0x20,0x00,0x00,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
void loop()
{
  deviceManager->onLoop();

  if(Serial.available() > 0){
    char c = Serial.read();
    if(c == 'f'){
      deviceManager->handleProtocolMessage(FIRMWARE_REQ_MESSAGE);
    }else if(c == '1') {
      deviceManager->handleProtocolMessage(SET_DEVICE_VALUE_MESSAGE1);
    }else if(c == '2') {
      deviceManager->handleProtocolMessage(SET_DEVICE_VALUE_MESSAGE2);
    }else if(c == '3') {
      deviceManager->handleProtocolMessage(SET_DEVICE_VALUE_MESSAGE3);
    }else if(c == '4') {
      deviceManager->handleProtocolMessage(SET_DEVICE_VALUE_MESSAGE4);
    }
  }
}

void handleSensorEvent(Protocol protocolEvent) {

  Serial.print("-------------------\n");
  Serial.print("Receiving Event\n");
  Serial.print("-------------------\n");
  Serial.print(protocolEvent.type,HEX);
  Serial.print("\n");

  Serial.print(protocolEvent.id,HEX);
  Serial.print("\n");

  Serial.print(protocolEvent.deviceType,HEX);
  Serial.print("\n");

  Serial.print(protocolEvent.data);
  Serial.print("\n");
  Serial.print(protocolEvent.data[0],HEX);
  Serial.print(protocolEvent.data[1],HEX);
  Serial.print(protocolEvent.data[2],HEX);
  Serial.print("\n");
  Serial.print("-------------------\n");

  if(protocolEvent.id == 0x1000)
    deviceManager->setValue(0x2001,1);
  else
    deviceManager->setValue(0x2001,0);
}




