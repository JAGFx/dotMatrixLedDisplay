//
// Created by emsm on 24-Feb-19.
//

#ifndef DISPLAYTEXTDOTMATRIX_TEXTSLIDE_H
#define DISPLAYTEXTDOTMATRIX_TEXTSLIDE_H

#include <MD_Parola.h>

class TextSlide {
public:
    TextSlide( char *textToDisplay, const textEffect_t &effect, const uint16_t &delayAtEnd );
    
    ~TextSlide();
    
    char *getText();
    
    textEffect_t getEffect();
    
    uint16_t getDelayAtEnd();

protected:
    char         *textToDisplay = nullptr;
    textEffect_t effect         = PA_SCROLL_LEFT;
    uint16_t     delayAtEnd     = 0;
};


#endif //DISPLAYTEXTDOTMATRIX_TEXTSLIDE_H
