/*************************************************************************
 * Arduino Library for Home Automation and Device Control
 * Distributed under Apache 2 License (http://www.apache.org/licenses/)
 * Visit http://marko-seifert.de/blog/?page_id=1042 for more information.
 * (C) Marko Seifert (DeveloperPodcast)
 *************************************************************************/

#include <Button.h>
#include <DeviceManager.h>
#include <LED.h>
#include <Device.h>
#include <Wire.h>
#include <SPI.h>
#include <boards.h>
#include <RBL_nRF8001.h>
#include <RBL_services.h>

DeviceManager* deviceManager;

void setup() {

  ble_set_pins(9,8);
  ble_set_name("HOMATIK");
  ble_begin();

  Serial.begin(9600); 

  deviceManager = new DeviceManager(handleSensorEvent);
  Button* b1 = new Button(0x1000, "Simple Button", 6, handleSensorEvent);
  Button* b2 = new Button(0x1001, "Simple Button", 7, handleSensorEvent);

  LED* led1 = new LED(0x2000,"RGB LED Modul", 2);
  LED* led2 = new LED(0x2001,"RGB LED Modul", 3);

  deviceManager->addSensor(b1->getDeviceID(), b1);
  deviceManager->addSensor(b2->getDeviceID(), b2);
  deviceManager->addActor(led1->getDeviceID(),led1);
  deviceManager->addActor(led2->getDeviceID(),led2);
}

uint8_t readBuffer[PROTOCOL_SIZE];
uint8_t writeBuffer[PROTOCOL_SIZE];

void loop()
{
  deviceManager->onLoop();

  // Bluetooth LE device connected
  if ( ble_connected()){
    // protocol message available
    if(ble_available() == PROTOCOL_SIZE){
      for(int i = 0; i< PROTOCOL_SIZE; i++){
        // fill the buffer
        readBuffer[i] = ble_read();
      }
      deviceManager->handleProtocolMessage(readBuffer);
    }
    //ble_write(speed);
    ble_do_events();
  }
  else{
    // advertising
    ble_do_events();
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
  
  deviceManager->transformToProtocolMessage(writeBuffer,&protocolEvent);

  if ( ble_connected()){
    // protocol message available
    if(ble_available() == PROTOCOL_SIZE){
      for(int i = 0; i< PROTOCOL_SIZE; i++){
        ble_write(writeBuffer[i]);
      }
    }
    //ble_write(speed);
    ble_do_events();
  }
}





