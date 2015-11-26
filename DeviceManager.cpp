/*
 * DeviceManager.cpp
 *
 *  Created on: 14.02.2013
 *      Author: mse
 */

#include "DeviceManager.h"

DeviceManager::DeviceManager(CALLBACK_SIGNATURE) {
    this->callback = callback;
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
    
    switch (protocol.type){
        case ProtocolTypes::FIRMWARE_REQ:
            Serial.println("receive FIRMWARE_REQ -> send FIRMWARE_RES");
            sendFirmwareResponse();
            break;
        case ProtocolTypes::ACTIVATE_DEVICE_BROADCAST:
            Serial.println("ACTIVATE_DEVICE_BROADCAST");
            break;
        case ProtocolTypes::ACTIVATE_VALUE_BROADCAST:
            Serial.println("ACTIVATE_VALUE_BROADCAST");
            break;
        case ProtocolTypes::DEVICE_VALUE_REQ:
            Serial.println("DEVICE_VALUE_REQ");
            break;
        default:
            Serial.print("unsuported protocol message type:");
            Serial.print(protocol.type,HEX);
            Serial.print("\n");
            break;
            
    }
    
    Serial.print(protocol.type,HEX);
    Serial.print("\n");
    
    Serial.print(protocol.id,HEX);
    Serial.print("\n");
    
    Serial.print(protocol.deviceType,HEX);
    Serial.print("\n");
    
    Serial.print(protocol.data);
    Serial.print("\n");
    Serial.print(protocol.data[0],HEX);
    Serial.print("\n");
}

void DeviceManager::sendFirmwareResponse(){
    
    Protocol protocol;
    protocol.deviceType=DeviceTypes::NO_TYPE_AVAILABLE;
    protocol.id = 0x0000;
    //memset(protocol.data,0,sizeof(protocol.data));
    //protocol.data = FIRMWARE_NAME_VERSION;
    memcpy(protocol.data, &FIRMWARE_NAME_VERSION, sizeof(FIRMWARE_NAME_VERSION));
    protocol.type=ProtocolTypes::FIRMWARE_RES;
    
    
    callback(protocol);
    
}

uint8_t* DeviceManager::transformToProtocolMessage(Protocol protocol){
    
    uint8_t msg[sizeof(protocol)];
    memset(msg,0,sizeof(msg));
    memcpy(msg, &protocol, sizeof(protocol));
    return msg;
}
