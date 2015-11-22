# HomeAutomationKit
Arduino library for home automation and other device control tasks.

A simple Example:

![Image of hardware setup](https://raw.githubusercontent.com/msedd/HomeAutomationKit/development/example_setup.jpg)

```c++
	#include <Button.h>
	#include <DeviceManager.h>
	#include <LED.h>
	
	DeviceManager* deviceManager;
	
	void setup() {
	  deviceManager = new DeviceManager();
	  Button* b1 = new Button(1000, 6, handleActorEvent);
	  Button* b2 = new Button(1001, 7, handleActorEvent);
	  
	  LED* led1 = new LED(2000,2);
	  LED* led2 = new LED(2001,3);
	  LED* led3 = new LED(2002,4);
	  LED* led4 = new LED(2003,5);
	  
	  deviceManager->addSensor(b1->getID(), b1);
	  deviceManager->addSensor(b2->getID(), b2);
	  deviceManager->addActor(led1->getID(),led1);
	  deviceManager->addActor(led2->getID(),led2);
	  deviceManager->addActor(led3->getID(),led3);
	  deviceManager->addActor(led4->getID(),led4);
	}
	void loop()
	{
	  if(sensorID == 1000)
	    deviceManager->setValue(2000,value);
	  else
	    deviceManager->setValue(2001,value);
	}
	void handleActorEvent(int sensorID, int value) {
	  deviceManager->setValue(2000,value);
	}
```

### Protocol
```
Typ Id    Size  Value
00  0000  00    0000...00



**Type**

0x00 get firmware
0x01 get firmware response
0x10 set value request
0x20 get value request
0x21 get value response
0x30 broadcast devices meta data request
0x31 broadcast devices response
```