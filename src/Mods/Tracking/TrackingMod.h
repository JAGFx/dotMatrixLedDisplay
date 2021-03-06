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
    static const uint8_t       MAX_ITERATION    = 10;
    
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
    
    virtual String currentData();
    
    virtual bool instanceOfMod( ModeType type );
    // ---
    
    // Mod management
    TinyGPSPlus *getTrackingObj();
    
    void updateRawData( int rawData );
    // ----

protected:
    // Mod management
    TinyGPSPlus *gps = nullptr;
    
    GPSDisplayMod currentDisplayMode       = GPSDisplayMod::Altitude;
    unsigned long lastMillis               = 0;
    uint8_t       currentIteration         = 0;
    bool          connectedToGPSSatellites = false;
    String        currentMessage           = String();
    
    void manageIterations( MD_Parola *matrix, String message );
    // ----
    
    // Text drawing
    String displayAltitude( TinyGPSAltitude dataAlti );
    
    String displayDDate();
    
    String displayTTime();
    
    String displayLatitude( TinyGPSLocation dataLat );
    
    String displayLongitude( TinyGPSLocation dataLong );
    
    String displaySpeed( TinyGPSSpeed dataSpeed );
    
    String displaySatellites( TinyGPSInteger dataSats );
    // ----
};


#endif //DOTMATRIXLEDDISPLAY_TRACKINGMOD_H
