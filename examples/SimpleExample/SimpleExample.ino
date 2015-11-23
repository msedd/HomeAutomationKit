#include <Button.h>
#include <DeviceManager.h>
#include <LED.h>
#include <DeviceType.h>

DeviceManager* deviceManager;

void setup() {
  deviceManager = new DeviceManager();
  Button* b1 = new Button(0x1000, "Simple Button", 6, handleActorEvent);
  Button* b2 = new Button(0x1001, "Simple Button", 7, handleActorEvent);

  LED* led1 = new LED(0x2000,"RGB LED Modul", 2);
  LED* led2 = new LED(0x2001,"RGB LED Modul", 3);
  LED* led3 = new LED(0x2002,"RGB LED Modul", 4);
  LED* led4 = new LED(0x2003,"RGB LED Modul", 5);

  deviceManager->addSensor(b1->getID(), b1);
  deviceManager->addSensor(b2->getID(), b2);
  deviceManager->addActor(led1->getID(),led1);
  deviceManager->addActor(led2->getID(),led2);
  deviceManager->addActor(led3->getID(),led3);
  deviceManager->addActor(led4->getID(),led4);
}
void loop()
{
  deviceManager->onLoop();
}

void handleActorEvent(int sensorID, int value) {

  if(sensorID == 1000)
    deviceManager->setValue(2000,value);
  else
    deviceManager->setValue(2001,value);
}






