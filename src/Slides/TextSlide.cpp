//
// Created by emsm on 24-Feb-19.
//

#include "TextSlide.h"

TextSlide::TextSlide( char *textToDisplay, const textEffect_t &effect, const uint16_t &delayAtEnd )
        : textToDisplay( textToDisplay ), effectIn( effect ), effectOut( effect ), delayAtEnd( delayAtEnd ) {}

TextSlide::TextSlide( char *textToDisplay, const textEffect_t &effectIn, const textEffect_t &effectOut,
                      const uint16_t &delayAtEnd )
        : textToDisplay( textToDisplay ), effectIn( effectIn ), effectOut( effectOut ), delayAtEnd( delayAtEnd ) {}

TextSlide::~TextSlide() {
    //delete getText();
}

char *TextSlide::getText() {
    return textToDisplay;
}

textEffect_t TextSlide::getEffectIn() {
    return effectIn;
}

textEffect_t TextSlide::getEffectOut() {
    return effectOut;
}

uint16_t TextSlide::getDelayAtEnd() {
    return delayAtEnd;
}