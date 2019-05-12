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
    Serial.println( "Bluetooth Device is Ready to Pair" );
}

ExternalDeviceInteraction::BLE_ACTIONS ExternalDeviceInteraction::getAction() {
    BLE_ACTIONS command = NONE;
    if ( bleSerial.available() > 0 ) {
        
        buffer  = bleSerial.readString(); //Read what we recevive
        command = ( BLE_ACTIONS ) strtol( buffer.c_str(), 0, 16 );
        
        /*Serial.print( "Received:" );
        Serial.println( command );*/
        bleSerial.print( "OK" );
        bleSerial.println( command );
        
    } /*else
        Serial.println( "---- BLE NOK" );*/
    
    return command;
}

void ExternalDeviceInteraction::sendData( String data ) {
    bleSerial.println( data );
}
