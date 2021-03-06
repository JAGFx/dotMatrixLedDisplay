//
// @author: SMITH Emmanuel <hey@emmanuel-smith.me>
// @site: https://emmanuel-smith.me
// Date: 01-Mar-19
// Time: 09:00 PM
//

#ifndef DOTMATRIXLEDDISPLAY_MOD_H
#define DOTMATRIXLEDDISPLAY_MOD_H

#include <MD_Parola.h>

class IMod {
public:
    enum ModeType {
        Message,
        Graph,
        Tracking,
        NumOfMod
    };
    
    virtual void updateDisplay( MD_Parola *matrix ) = 0;
    
    virtual void init( MD_Parola *matrix ) = 0;
    
    virtual void reset( MD_Parola *matrix ) = 0;
    
    virtual bool needToRefresh() = 0;
    
    virtual String currentData() = 0;
    
    virtual bool instanceOfMod( ModeType ) = 0;
    
};


#endif //DOTMATRIXLEDDISPLAY_MOD_H
