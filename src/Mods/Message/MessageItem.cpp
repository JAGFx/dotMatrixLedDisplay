//
// @author: SMITH Emmanuel <hey@emmanuel-smith.me>
// @site: https://emmanuel-smith.me
// Date: 24-Feb-19
// Time: 02:57 PM
//

#include "MessageItem.h"

MessageItem::MessageItem( char *textToDisplay, const textEffect_t &effect, const uint16_t &delayAtEnd )
        : textToDisplay( textToDisplay ), effectIn( effect ), effectOut( effect ), delayAtEnd( delayAtEnd ) {}

MessageItem::MessageItem( char *textToDisplay, const textEffect_t &effectIn, const textEffect_t &effectOut,
                          const uint16_t &delayAtEnd )
        : textToDisplay( textToDisplay ), effectIn( effectIn ), effectOut( effectOut ), delayAtEnd( delayAtEnd ) {}

MessageItem::~MessageItem() {
    //delete getText();
}

char *MessageItem::getText() {
    return textToDisplay;
}

textEffect_t MessageItem::getEffectIn() {
    return effectIn;
}

textEffect_t MessageItem::getEffectOut() {
    return effectOut;
}

uint16_t MessageItem::getDelayAtEnd() {
    return delayAtEnd;
}