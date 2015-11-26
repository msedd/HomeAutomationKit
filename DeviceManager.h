/*
 * DeviceManager.h
 *
 *  Created on: 14.02.2013
 *      Author: mse
 */

#ifndef DEVICEMANAGER_H_
#define DEVICEMANAGER_H_

#include "Sensor.h"
#include "Actor.h"
#include "CList.h"

#define CALLBACK_SIGNATURE void (*callback)(Protocol)

class DeviceManager {
public:
	DeviceManager(CALLBACK_SIGNATURE);
	virtual ~DeviceManager();

	void addSensor(int deviceID, Sensor* sensor);
	void addActor(int deviceID, Actor* actor);
	void onLoop();
	void setValue(int,int);
    void handleProtocolMessage(uint8_t[]);
    uint8_t* transformToProtocolMessage(Protocol protocol);
private:
	CList sensorList;
	CList actorList;
    SENSOR_CALLBACK_SIGNATURE;
    
    void sendFirmwareResponse();
};

#endif /* DEVICEMANAGER_H_ */
