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
    MessageItem( char *textToDisplay, const textEffect_t &effect, const uint16_t &delayAtEnd );
    
    MessageItem( char *textToDisplay, const textEffect_t &effectIn, const textEffect_t &effectOut,
                 const uint16_t &delayAtEnd );
    
    ~MessageItem();
    
    char *getText();
    
    textEffect_t getEffectIn();
    
    textEffect_t getEffectOut();
    
    uint16_t getDelayAtEnd();

protected:
    char         *textToDisplay = nullptr;
    textEffect_t effectIn       = PA_SCROLL_LEFT;
    textEffect_t effectOut      = PA_SCROLL_LEFT;
    uint16_t     delayAtEnd     = 0;
};


#endif //DISPLAYTEXTDOTMATRIX_TEXTSLIDE_H
