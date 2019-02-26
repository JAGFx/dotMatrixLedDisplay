//
// Created by emsm on 24-Feb-19.
//

#include "TextSlide.h"

TextSlide::TextSlide( String *textToDisplay, const textEffect_t &effect, const uint16_t &delayAtEnd ) : textToDisplay(
        textToDisplay ), effect( effect ), delayAtEnd( delayAtEnd ) {}

TextSlide::~TextSlide() {
    delete getText();
}

String *TextSlide::getText() {
    return textToDisplay;
}

textEffect_t TextSlide::getEffect() {
    return effect;
}

uint16_t TextSlide::getDelayAtEnd() {
    return delayAtEnd;
}