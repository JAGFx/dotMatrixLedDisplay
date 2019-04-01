//
// Created by CLion.
// @author: SMITH Emmanuel <hey@emmanuel-smith.me>
// @site: https://emmanuel-smith.me
// Date: 01-Apr-19
// Time: 21:04
//

#include "Commons.h"


void UTC::updateChipDate( TinyGPSDate gpsDate, TinyGPSTime gpsTime ) {
    int  Year   = gpsDate.year();
    byte Month  = gpsDate.month();
    byte Day    = gpsDate.day();
    byte Hour   = gpsTime.hour();
    byte Minute = gpsTime.minute();
    byte Second = gpsTime.second();
    
    setTime( Hour, Minute, Second, Day, Month, Year );
}

const String UTC::getHour() {
    return ( hour( getAdjustedTime() ) < 0 )
           ? "0" + String( hour( getAdjustedTime() ) )
           : String( hour( getAdjustedTime() ) );
}

const String UTC::getMinute() {
    return ( minute( getAdjustedTime() ) < 0 )
           ? "0" + String( minute( getAdjustedTime() ) )
           : String( minute( getAdjustedTime() ) );
}

const String UTC::getSecond() {
    return ( second( getAdjustedTime() ) < 0 )
           ? "0" + String( second( getAdjustedTime() ) )
           : String( second( getAdjustedTime() ) );
}


const String UTC::getYear() {
    return String( year( getAdjustedTime() ) );
}

const String UTC::getMonth() {
    return ( month( getAdjustedTime() ) < 0 )
           ? "0" + String( month( getAdjustedTime() ) )
           : String( month( getAdjustedTime() ) );
}

const String UTC::getDay() {
    return ( day( getAdjustedTime() ) < 0 )
           ? "0" + String( day( getAdjustedTime() ) )
           : String( day( getAdjustedTime() ) );
}

time_t UTC::getAdjustedTime() {
    //Central European Time (Frankfurt, Paris)  120 = +2 hours in daylight saving time (summer).
    TimeChangeRule CEST = { "CEST", Last, Sun, Mar, 2, 120 };
    //Central European Time (Frankfurt, Paris)  60  = +1 hour in normal time (winter)
    TimeChangeRule CET  = { "CET ", Last, Sun, Oct, 3, 60 };
    Timezone       CE( CEST, CET );
    
    time_t utc = now();  // read the time in the correct format to change via the TimeChangeRules
    return CE.toLocal( utc );
}
