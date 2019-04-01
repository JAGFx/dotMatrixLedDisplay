//
// Created by CLion.
// @author: SMITH Emmanuel <hey@emmanuel-smith.me>
// @site: https://emmanuel-smith.me
// Date: 01-Apr-19
// Time: 21:04
//

#ifndef DOTMATRIXLEDDISPLAY_COMMONS_H
#define DOTMATRIXLEDDISPLAY_COMMONS_H

#include <Timezone.h>
#include <TinyGPS++.h>

class UTC {
public:
    static void updateChipDate( TinyGPSDate gpsDate, TinyGPSTime gpsTime );
    
    static const String getHour();
    
    static const String getMinute();
    
    static const String getSecond();
    
    static const String getYear();
    
    static const String getMonth();
    
    static const String getDay();

private:
    
    static time_t getAdjustedTime();
};


#endif //DOTMATRIXLEDDISPLAY_COMMONS_H
