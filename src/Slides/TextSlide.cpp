//
// Created by emsm on 24-Feb-19.
//

#include "TextSlide.h"

TextSlide::TextSlide( char *textToDisplay, const textEffect_t &effect, const uint16_t &delayAtEnd )
        : textToDisplay( textToDisplay ), effect( effect ), delayAtEnd( delayAtEnd ) {}

TextSlide::~TextSlide() {
    //delete getText();
}

char *TextSlide::getText() {
    return textToDisplay;
}

textEffect_t TextSlide::getEffect() {
    return effect;
}

uint16_t TextSlide::getDelayAtEnd() {
    return delayAtEnd;
}