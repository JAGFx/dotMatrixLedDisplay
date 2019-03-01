//
// Created by emsm on 01-Mar-19.
//

#ifndef DOTMATRIXLEDDISPLAY_MOD_H
#define DOTMATRIXLEDDISPLAY_MOD_H

#include <MD_Parola.h>

class IMod {
public:
    enum ModeType {
        MessageMod
    };
    
    virtual void updateDisplay( MD_Parola &matrix ) = 0;
    
    virtual bool needToRefresh() = 0;
    
    virtual bool instanceOfMod( ModeType ) = 0;
    
};


#endif //DOTMATRIXLEDDISPLAY_MOD_H
