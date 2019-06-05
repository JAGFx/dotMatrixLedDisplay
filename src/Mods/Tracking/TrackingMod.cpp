//
// Created by CLion.
// @author: SMITH Emmanuel <hey@emmanuel-smith.me>
// @site: https://emmanuel-smith.me
// Date: 09-Mar-19
// Time: 14:59
//

#include "TrackingMod.h"
#include "../../Engine/Orchestrator.h"
#include "../../Engine/Commons.h"

// -------------------------------------
// -- IMod

void TrackingMod::updateDisplay( MD_Parola *matrix ) {
    //Serial.println( "============= START" );
    if ( needToRefresh() ) {
        lastMillis = millis();
    
        UTC::updateChipDate( gps->date, gps->time );
        connectedToGPSSatellites = ( gps->satellites.value() > 0 );
        
        //Serial.println( "Plop" );
        //Serial.println(gps.altitude.meters());

//        String message = "###";
        
        // --- Test STR
        /*// - Altitude
        Serial.print( ">> Altitude : " );
        Serial.println( displayAltitude( gps->altitude ) );
        // - DDate
        Serial.print( ">> DDate : " );
        Serial.println( displayDDate() );
        // - TTime
        Serial.print( ">> TTime : " );
        Serial.println( displayTTime() );
        // - Latitude
        Serial.print( ">> Latitude : " );
        //Serial.println( String( gps->location.lat(), 6 ) );
        Serial.println( displayLatitude( gps->location ) );
        // - Longitude
        Serial.print( ">> Longitude : " );
        //Serial.println( String( gps->location.lng(), 6 ) );
        Serial.println( displayLongitude( gps->location ) );
        // - Speed
        Serial.print( ">> Speed : " );
        Serial.println( displaySpeed( gps->speed ) );
        // - Satellites
        Serial.print( ">> Satellites : " );
        Serial.println( displaySatellites( gps->satellites ) );*/
        // --- ./ Test STR
        
        switch ( currentDisplayMode ) {
            case Altitude:
                //Serial.println(">> Alt");
                //Serial.println(gps.altitude.isValid());
                //if(gps.altitude.isValid())
                currentMessage = displayAltitude( gps->altitude );
                break;
            case DDate:
                /*currentMessage = String( String( gps->date.year() ) + '-'
                                  + String( gps->date.month() ) + '-'
                                  + String( gps->date.day() )
                );*/
                currentMessage = displayDDate();
                break;
            case TTime:
                //currentMessage = String( String( gps->time.hour() ) + ':' + String( gps->time.minute() ) );
                currentMessage = displayTTime();
                break;
            case Latitude:
                currentMessage = displayLatitude( gps->location );
                break;
            case Longitude:
                currentMessage = displayLongitude( gps->location );
                break;
            case Speed:
                currentMessage = displaySpeed( gps->speed );
                break;
            case Satellites:
                currentMessage = displaySatellites( gps->satellites );
                break;
        }
    
        //Serial.println( currentMessage );
    
        manageIterations( matrix, currentMessage );
        //delay( 1500 );
    }
    
    //Serial.println( "============== END" );
}

void TrackingMod::init( MD_Parola *matrix ) {
    gps = new TinyGPSPlus;
}

void TrackingMod::reset( MD_Parola *matrix ) {

}

bool TrackingMod::needToRefresh() {
    unsigned long currentMillis = millis();
    
    /*Serial.println("------------");
    Serial.println(currentMillis);
    Serial.println(lastMillis);
    Serial.println("------------");*/
    
    return currentMillis - lastMillis >= REFRESH_DELAY_MS;
}

String TrackingMod::currentData() {
    return currentMessage;
}

bool TrackingMod::instanceOfMod( IMod::ModeType type ) {
    return type == ModeType::Tracking;
}
// -------------------------------------


// -------------------------------------
// -- Mod management

TinyGPSPlus *TrackingMod::getTrackingObj() {
    return gps;
}

void TrackingMod::updateRawData( int rawData ) {
    //Serial.print( "================ New data: " );
    //Serial.println( rawData );
    gps->encode( rawData );
}

void TrackingMod::manageIterations( MD_Parola *matrix, String message ) {
    textEffect_t effectIn  = PA_PRINT;
    textEffect_t effectOut = PA_PRINT;
    uint8_t      speed     = 0;
    
    if ( currentIteration == 0 ) {
        effectIn = PA_GROW_UP;
        speed    = Orchestrator::DEFAULT_SCROLL_SPEED;
    }
    
    if ( currentIteration == MAX_ITERATION - 1 ) {
        effectOut = PA_GROW_DOWN;
        speed     = Orchestrator::DEFAULT_SCROLL_SPEED;
    }
    
    matrix->displayText( ( char * ) message.c_str(),
                         Orchestrator::DEFAULT_SCROLL_ALIGN,
                         speed,
                         REFRESH_DELAY_MS,
                         effectIn,
                         effectOut );
    
    currentIteration = ( ++currentIteration ) % MAX_ITERATION;
    
    if ( currentIteration == 0 )
        currentDisplayMode = static_cast<GPSDisplayMod>(( currentDisplayMode + 1 ) % GPSDisplayMod::NumOfMod);
}

// -------------------------------------


// -------------------------------------
// -- Text drawing

String TrackingMod::displayAltitude( TinyGPSAltitude dataAlti ) {
    return ( connectedToGPSSatellites )
           ? String( "Alt: " + String( dataAlti.meters() ) + "m" )
           : String( "Alt: -.-m" );
}

String TrackingMod::displayDDate() {
    return String( UTC::getYear() + '-'
                   + UTC::getMonth() + '-'
                   + UTC::getDay()
    );
}

String TrackingMod::displayTTime() {
    return String( UTC::getHour() + ':' + UTC::getMinute() + ':' + UTC::getSecond() );
}

String TrackingMod::displayLatitude( TinyGPSLocation dataLat ) {
    return ( connectedToGPSSatellites )
           ? Position::getLatitudeAsDMS( dataLat.lat() )
           : Position::emptyLatitudeAsDMS();
}

String TrackingMod::displayLongitude( TinyGPSLocation dataLong ) {
    return ( connectedToGPSSatellites )
           ? Position::getLongitudeAsDMS( dataLong.lng() )
           : Position::emptyLongitudeAsDMS();
}

String TrackingMod::displaySpeed( TinyGPSSpeed dataSpeed ) {
    return ( connectedToGPSSatellites )
           ? String( String( dataSpeed.kmph(), 1 ) + " kmh" )
           : String( "-.- kmh" );
}

String TrackingMod::displaySatellites( TinyGPSInteger dataSats ) {
    return String( "Sat: " + String( dataSats.value() ) );
}

// -------------------------------------
