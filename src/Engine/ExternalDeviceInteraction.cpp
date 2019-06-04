//
// Created by CLion.
// @author: SMITH Emmanuel <hey@emmanuel-smith.me>
// @site: https://emmanuel-smith.me
// Date: 12-May-19
// Time: 16:52
//

#include "ExternalDeviceInteraction.h"

void ExternalDeviceInteraction::init() {
    bleSerial.begin( BT_NAME );
}

void ExternalDeviceInteraction::sendData( String data ) {
    bleSerial.println( data );
}

BluetoothSerial *ExternalDeviceInteraction::getBLESerial() {
    return &bleSerial;
}
