//
// Created by CLion.
// @author: SMITH Emmanuel <hey@emmanuel-smith.me>
// @site: https://emmanuel-smith.me
// Date: 09-Mar-19
// Time: 14:59
//

#ifndef DOTMATRIXLEDDISPLAY_TRACKINGMOD_H
#define DOTMATRIXLEDDISPLAY_TRACKINGMOD_H

#include <TinyGPS++.h>
#include "../../Engine/IMod.h"

class TrackingMod : public IMod {
public:
    
    static const unsigned long REFRESH_DELAY_MS = 1000;
    
    enum GPSDisplayMod {
        Altitude,
        DDate,
        TTime,
        Latitude,
        Longitude,
        Speed,
        Satellites,
        NumOfMod
    };
    
    // IMod
    virtual void updateDisplay( MD_Parola *matrix );
    
    virtual void init( MD_Parola *matrix );
    
    virtual void reset( MD_Parola *matrix );
    
    virtual bool needToRefresh();
    
    virtual bool instanceOfMod( ModeType type );
    // ---
    
    // Mod management
    TinyGPSPlus *getTrackingObj();
    
    void updateRawData( int rawData );
    // ----

protected:
    // Mod management
    TinyGPSPlus *gps = nullptr;
    
    GPSDisplayMod currentDisplayMode = GPSDisplayMod::Altitude;
    unsigned long lastMillis         = 0;
    // ----
};


#endif //DOTMATRIXLEDDISPLAY_TRACKINGMOD_H
