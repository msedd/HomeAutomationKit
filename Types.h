/*************************************************************************
 * Arduino Library for Home Automation and Device Control
 * Distributed under Apache 2 License (http://www.apache.org/licenses/)
 * Visit http://marko-seifert.de/blog/?page_id=1042 for more information.
 * (C) Marko Seifert (DeveloperPodcast)
 *************************************************************************/

#ifndef DEVICETYPES_H_
#define DEVICETYPES_H_

#define PROTOCOL_SIZE 24

const char FIRMWARE_NAME_VERSION[19]= "HOMATIK:1.0.23    ";

class DeviceTypes  {
public:
    
    enum type
    {
        NO_TYPE_AVAILABLE=0x0000,
        LED=0x0001,
        LED_DIMMABLE=0x0002,
        RGB_LED_PREDEFINED_COLOR=0x0003,
        RGB_LED_PREDEFINED_DIMMABLE=0x0004
    };
    
};

#endif /* DEVICETYPES_H_ */

#ifndef PROTOCOLTYPES_H_
#define PROTOCOLTYPES_H_

class ProtocolTypes  {
public:
    
    enum type
    {
        FIRMWARE_REQ = 0x00,
        FIRMWARE_RES = 0x01,
        SET_DEVICE_VALUE = 0x10,
        DEVICE_VALUE_REQ = 0x20,
        DEVICE_VALUE_RES = 0x21,
        ACTIVATE_VALUE_BROADCAST = 0x22,
        DEVICE_VALUE_BROADCAST = 0x23,
        ACTIVATE_DEVICE_BROADCAST = 0x32,
        DEVICE_BROADCAST = 0x33

    };
    
};

#endif /* PROTOCOLTYPES_H_ */