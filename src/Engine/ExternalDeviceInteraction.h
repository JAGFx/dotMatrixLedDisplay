//
// Created by CLion.
// @author: SMITH Emmanuel <hey@emmanuel-smith.me>
// @site: https://emmanuel-smith.me
// Date: 12-May-19
// Time: 16:52
//

#ifndef DOTMATRIXLEDDISPLAY_EXTERNALDEVICEINTERACTION_H
#define DOTMATRIXLEDDISPLAY_EXTERNALDEVICEINTERACTION_H

#include <BluetoothSerial.h>
#include "Settings.h"

class ExternalDeviceInteraction {
public:
    void init();
    
    // Send(1) or received(0)|Mod|ActionID
    // 0x0|00|00
    enum BLE_ACTIONS {
        SWITCH_MODE     = BT_CODE_SWITCH_MOD,
        CURRENT_MODE    = BT_CODE_CURRENT_MOD,
        CURRENT_DATA    = BT_CODE_CURRENT_DATA,
        MESSAGE_ADD_MSG = BT_CODE_MESSAGE_ADD_MSG,
        NONE            = BT_CODE_NONE
    };
    
    void sendData( String data );
    
    BluetoothSerial *getBLESerial();


private:
    String          buffer;
    BluetoothSerial bleSerial;
};


#endif //DOTMATRIXLEDDISPLAY_EXTERNALDEVICEINTERACTION_H
