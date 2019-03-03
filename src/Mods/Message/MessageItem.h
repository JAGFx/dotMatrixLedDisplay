//
// @author: SMITH Emmanuel <hey@emmanuel-smith.me>
// @site: https://emmanuel-smith.me
// Date: 24-Feb-19
// Time: 02:57 PM
//

#ifndef DISPLAYTEXTDOTMATRIX_TEXTSLIDE_H
#define DISPLAYTEXTDOTMATRIX_TEXTSLIDE_H

#include <MD_Parola.h>


class MessageItem {
public:
    enum SPRITES {
        NONE,
        ROCKET,
        INVADER,
        CHEVRON,
        HEART,
        ARROW1,
        STEAMBOAT,
        FBALL,
        ROLL2,
        PMAN2,
        LINES,
        ROLL1,
        SAILBOAT,
        ARROW2,
        WAVE,
        PMAN1
    };
    
    MessageItem( char *textToDisplay, const textEffect_t &effect, const uint16_t &delayAtEnd );
    
    MessageItem( char *textToDisplay, const textEffect_t &effect, const uint16_t &delayAtEnd, const SPRITES &sprite );
    
    MessageItem( char *textToDisplay, const textEffect_t &effectIn, const textEffect_t &effectOut,
                 const uint16_t &delayAtEnd );
    
    ~MessageItem();
    
    char *getText();
    
    textEffect_t getEffectIn() const;
    
    textEffect_t getEffectOut() const;
    
    uint16_t getDelayAtEnd() const;
    
    SPRITES getSprite() const;

protected:
    char         *textToDisplay = nullptr;
    textEffect_t effectIn       = PA_SCROLL_LEFT;
    textEffect_t effectOut      = PA_SCROLL_LEFT;
    uint16_t     delayAtEnd     = 0;
    SPRITES      sprite         = NONE;
};


#endif //DISPLAYTEXTDOTMATRIX_TEXTSLIDE_H
