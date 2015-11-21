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

class DeviceManager {
public:
	DeviceManager();
	virtual ~DeviceManager();

	void addSensor(int deviceID, Sensor* sensor);
	void addActor(int deviceID, Actor* actor);
	void onLoop();
	void setValue(int,int);
private:
	CList sensorList;
	CList actorList;
};

#endif /* DEVICEMANAGER_H_ */
