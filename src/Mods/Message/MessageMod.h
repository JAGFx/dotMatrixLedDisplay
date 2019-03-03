//
// @author: SMITH Emmanuel <hey@emmanuel-smith.me>
// @site: https://emmanuel-smith.me
// Date: 01-Mar-19
// Time: 08:53 PM
//

#ifndef DOTMATRIXLEDDISPLAY_MESSAGEMOD_H
#define DOTMATRIXLEDDISPLAY_MESSAGEMOD_H

#include "MessageItem.h"
#include "../../Engine/IMod.h"
#include <QueueH.h>

class MessageMod : public IMod {
    static const uint8_t MAX_SLIDE_IN_QUEUE = 10;

public:
    MessageMod();
    
    // Mod management
    void addInQueue( MessageItem *textSlide );
    
    void clearQueue();
    
    void updateCurrentMessageItem();
    // ----
    
    
    // IMod
    virtual bool needToRefresh();
    
    virtual void updateDisplay( MD_Parola *matrix );
    
    virtual bool instanceOfMod( ModeType type );
    // ----

protected:
    // Project management
    QueueH < MessageItem * > queue               = QueueH < MessageItem * >( MAX_SLIDE_IN_QUEUE );
    MessageItem              *currentMessageItem = nullptr;
    MessageItem              *prevTextSlide      = nullptr;
    // ----
};


#endif //DOTMATRIXLEDDISPLAY_MESSAGEMOD_H
