/*************************************************************************
 * Arduino Library for Home Automation and Device Control
 * Distributed under Apache 2 License (http://www.apache.org/licenses/)
 * Visit http://marko-seifert.de/blog/?page_id=1042 for more information.
 * (C) Marko Seifert (DeveloperPodcast)
 *************************************************************************/

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
void DeviceManager::handleProtocolMessage(uint8_t *msg){
    
    
    if(true){
        Serial.print("msg: 0x");
        for(int i = 0; i< PROTOCOL_SIZE; i++){
            Serial.print(msg[i],HEX);
        }
        Serial.print("\n");
    }

    Protocol protocol; //Re-make the struct
    memcpy(&protocol, msg, PROTOCOL_SIZE);
    
    Serial.print("type: 0x");
    Serial.print(protocol.type,HEX);
    Serial.print("\n");
    
    Serial.print("id: 0x");
    Serial.print(protocol.id,HEX);
    Serial.print("\n");
    
    Serial.print("deviceType: 0x");
    Serial.print(protocol.deviceType,HEX);
    Serial.print("\n");
    
    Serial.print("data: ");
    Serial.print(protocol.data);
    Serial.print("\n");
    Serial.print("data: 0x");
    Serial.print(protocol.data[0],HEX);
    Serial.print("\n");
    
    switch (protocol.type){
        case ProtocolTypes::FIRMWARE_REQ:
            Serial.println("receive FIRMWARE_REQ -> send FIRMWARE_RES");
            sendFirmwareResponse();
            break;
        case ProtocolTypes::SET_DEVICE_VALUE:
            Serial.println("SET_DEVICE_VALUE");
            setValue(protocol.id, protocol.data[0]);
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
    
    Serial.print("type: 0x");
    Serial.print(protocol.type,HEX);
    Serial.print("\n");
    
    Serial.print("id: 0x");
    Serial.print(protocol.id,HEX);
    Serial.print("\n");
    
    Serial.print("deviceType: 0x");
    Serial.print(protocol.deviceType,HEX);
    Serial.print("\n");
    
    Serial.print("data: ");
    Serial.print(protocol.data);
    Serial.print("\n");
    Serial.print("data: 0x");
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

void DeviceManager::transformToProtocolMessage(uint8_t* buffer, Protocol* protocol){
    
    if(true){
        Serial.print("type: 0x");
        Serial.print(protocol->type,HEX);
        Serial.print("\n");
        
        Serial.print("id: 0x");
        Serial.print(protocol->id,HEX);
        Serial.print("\n");
        
        Serial.print("deviceType: 0x");
        Serial.print(protocol->deviceType,HEX);
        Serial.print("\n");
        
        Serial.print("data: ");
        Serial.print(protocol->data);
        Serial.print("\n");
        Serial.print("data: 0x");
        Serial.print(protocol->data[0],HEX);
        Serial.print("\n");
    }
    
    memset(buffer,0,PROTOCOL_SIZE);
    memcpy(buffer, protocol, PROTOCOL_SIZE);
    
    if(true){
        Serial.print("msg: 0x");
        for(int i = 0; i< PROTOCOL_SIZE; i++){
            Serial.print(buffer[i],HEX);
        }
        Serial.print("\n");
    }
}

uint8_t* DeviceManager::transformToProtocolMessage(Protocol protocol){
    
    if(true){
    Serial.print("type: 0x");
    Serial.print(protocol.type,HEX);
    Serial.print("\n");
    
    Serial.print("id: 0x");
    Serial.print(protocol.id,HEX);
    Serial.print("\n");
    
    Serial.print("deviceType: 0x");
    Serial.print(protocol.deviceType,HEX);
    Serial.print("\n");
    
    Serial.print("data: ");
    Serial.print(protocol.data);
    Serial.print("\n");
    Serial.print("data: 0x");
    Serial.print(protocol.data[0],HEX);
    Serial.print("\n");
    }
    
    uint8_t msg[PROTOCOL_SIZE];
    memset(msg,0,PROTOCOL_SIZE);
    memcpy(msg, &protocol, PROTOCOL_SIZE);
    
    if(true){
    Serial.print("msg: 0x");
    for(int i = 0; i< sizeof(msg); i++){
        Serial.print(msg[i],HEX);
    }
    Serial.print("\n");
    }
    return msg;
}
