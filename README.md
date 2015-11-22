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
Typ(1B)Id(2B)Size(1B)Value(Size*B)[DeviceType(2B)]
```


#### Types

```
0x00 get the controller firmware (request)
0x01 the controller firmware (response)
0x10 set the device value (command)
0x20 get the device value (request)
0x21 the device value (response)
0x22 activate broadcast for the device value (command)
0x23 the device value (broadcast)
0x32 activate broadcast for the devices meta data (command)
0x33 the device meta data (broadcast)
```
#### IDs
```
0x0000 all
0x0001 device 1
...
0xffff device 65535
```
#### Device Type
```
0x0000 no type available
0x0001 Lighting Fixtures
0x0002 Tuneable White Lighting Fixtures
0x0003 RGB Lighting Fixtures
0x0004 RGBW Lighting Fixtures
...
0xffff
```
#### Example
```c++
// request the firmware meta data
0 x 00 0000 00
// or short
0 x 00

// the firmware meta data answer
// HOMATIK:1.0.23
0 x 01 0000 0e 484f4d4154494b3a312e302e3233

// set the value of a rgb led to red
0 x 10 1000 03 ff0000

// request the value of an simple switch
0 x 20 2000 00
// the answer 1 = H, 0 = L
0 x 21 2000 01 01

// a broadcast message of an simple switch
0 x 23 2000 01 00

// a broadcast message of the device meta data
// name = "RGB LED Modul"
// device type = "RGB Lighting Fixtures"
0 x 33 11F0 0e 524742204c4544204d6f64756c20 0003

```