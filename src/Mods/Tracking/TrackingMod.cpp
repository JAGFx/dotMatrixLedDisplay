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
        
        //Serial.println( "Plop" );
        //Serial.println(gps.altitude.meters());
        
        String message = "###";
        
        // --- Test STR
        // - Altitude
        Serial.print( ">> Altitude : " );
        Serial.println( String( String( gps->altitude.meters(), 0 ) + 'm' ) );
        // - DDate
        Serial.print( ">> DDate : " );
        Serial.println( String( UTC::getYear() + '-'
                                + UTC::getMonth() + '-'
                                + UTC::getDay()
                        )
        );
        // - TTime
        Serial.print( ">> TTime : " );
        Serial.println( String( UTC::getHour() + ':' + UTC::getMinute() ) );
        // - Latitude
        Serial.print( ">> Latitude : " );
        //Serial.println( String( gps->location.lat(), 6 ) );
        Serial.println( Position::getLatitudeAsDMS( gps->location.lat() ) );
        // - Longitude
        Serial.print( ">> Longitude : " );
        //Serial.println( String( gps->location.lng(), 6 ) );
        Serial.println( Position::getLongitudeAsDMS( gps->location.lng() ) );
        // - Speed
        Serial.print( ">> Speed : " );
        Serial.println( String( String( gps->speed.kmph(), 1 ) + " kmh" ) );
        // - Satellites
        Serial.print( ">> Satellites : " );
        Serial.println( String( "Sat: " + String( gps->satellites.value() ) ) );
        // --- ./ Test STR
        
        switch ( currentDisplayMode ) {
            case Altitude:
                //Serial.println(">> Alt");
                //Serial.println(gps.altitude.isValid());
                //if(gps.altitude.isValid())
                message = String( String( gps->altitude.meters() ) + "m" );
                break;
            case DDate:
                /*message = String( String( gps->date.year() ) + '-'
                                  + String( gps->date.month() ) + '-'
                                  + String( gps->date.day() )
                );*/
                message = String( UTC::getYear() + '-'
                                  + UTC::getMonth() + '-'
                                  + UTC::getDay()
                );
                break;
            case TTime:
                //message = String( String( gps->time.hour() ) + ':' + String( gps->time.minute() ) );
                message = String( UTC::getHour() + ':' + UTC::getMinute() );
                break;
            case Latitude:
                message = Position::getLatitudeAsDMS( gps->location.lat() );
                break;
            case Longitude:
                message = Position::getLongitudeAsDMS( gps->location.lng() );
                break;
            case Speed:
                message = String( String( gps->speed.kmph(), 1 ) + " kmh" );
                break;
            case Satellites:
                message = String( "Sat: " + String( gps->satellites.value() ) );
                break;
        }
        
        //Serial.println( message );
    
        manageIterations( &matrix, message );
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
    textEffect_t effectIn = ( currentIteration == 0 )
                            ? PA_GROW_UP
                            : PA_PRINT;
    
    textEffect_t effectOut = ( currentIteration == MAX_ITERATION - 1 )
                             ? PA_GROW_DOWN
                             : PA_PRINT;
    
    matrix->displayText( ( char * ) message.c_str(),
                         Orchestrator::DEFAULT_SCROLL_ALIGN,
                         Orchestrator::DEFAULT_SCROLL_SPEED,
                         REFRESH_DELAY_MS,
                         effectIn,
                         effectOut );
    
    currentIteration = currentIteration++ % MAX_ITERATION;
    
    if ( currentIteration == 0 )
        currentDisplayMode = static_cast<GPSDisplayMod>(( currentDisplayMode + 1 ) % GPSDisplayMod::NumOfMod);
}

// -------------------------------------
