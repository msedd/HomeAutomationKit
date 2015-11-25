/*
 * DeviceManager.cpp
 *
 *  Created on: 14.02.2013
 *      Author: mse
 */

#include "DeviceManager.h"

DeviceManager::DeviceManager() {

}

DeviceManager::~DeviceManager() {

}
void DeviceManager::addActor(int deviceID, Actor* actor) {
	actorList.append(deviceID, actor);
}
void DeviceManager::addSensor(int deviceID, Sensor* sensor) {
	sensorList.append(deviceID, sensor);
}
void DeviceManager::onLoop() {

	int size = sensorList.getSize();

	for (int i = 0; i < size; i++) {
		Sensor* sensor = (Sensor*) sensorList.getElemet(i);
		sensor->readAndDispatch();
	}

}
void DeviceManager::setValue(int id, int value) {

	char buffer[100];
	Actor* actor = (Actor*) actorList.getElemetByKey(id);
	if (actor == 0) {
		sprintf(buffer, "Kein Actor mit der ID= %d registriert.", id);
		Serial.println(buffer);
	} else {
		sprintf(buffer, "Setze Wert: %d für Actor mit der ID= %d.",value, id);
		Serial.println(buffer);
		actor->writeValue(value);
	}

}
void DeviceManager::handleProtocolMessage(uint8_t msg[]){

    Protocol protocol; //Re-make the struct
    memcpy(&protocol, msg, sizeof(msg));
}

uint8_t* DeviceManager::transformToProtocolMessage(Protocol protocol){
    
    uint8_t msg[sizeof(protocol)];
    memcpy(msg, &protocol, sizeof(protocol));
    return msg;
}
