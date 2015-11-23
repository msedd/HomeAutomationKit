/*
 * Device.h
 *
 *  Created on: 14.02.2013
 *      Author: mse
 */

#ifndef DEVICETYPE_H_
#define DEVICETYPE_H_

class DeviceType  {
public:
    enum types
    {
        NO_TYPE_AVAILABLE=0x0000,
        LED=0x0001,
        LED_DIMMABLE=0x0002,
        RGB_LED_PREDEFINED_COLOR=0x0003,
        RGB_LED_PREDEFINED_DIMMABLE=0x0004
    };
};

#endif /* DEVICETYPE_H_ */
