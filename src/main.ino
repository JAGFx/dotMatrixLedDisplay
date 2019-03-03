//
// @author: SMITH Emmanuel <hey@emmanuel-smith.me>
// @site: https://emmanuel-smith.me
// Date: 24-Feb-19
// Time: 02:57 PM
//

#include <MD_Parola.h>
#include "QueueH.h"
#include "Engine/Orchestrator.h"
#include "Mods/Message/MessageMod.h"

#define HARDWARE_TYPE MD_MAX72XX::ICSTATION_HW
#define MAX_DEVICES 4
#define CLK_PIN   14
#define DATA_PIN  12
#define CS_PIN    15

Orchestrator orchestrator = Orchestrator( HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES );

void resetQueue() {
    if ( orchestrator.getCurrentMod()->instanceOfMod( IMod::ModeType::MessageMod ) ) {
        MessageMod *messageMod = ( MessageMod * ) orchestrator.getCurrentMod();
        
        messageMod->clearQueue();
        messageMod->addInQueue( new MessageItem( "Norway is coming soon !", PA_SCROLL_LEFT, 0 ) );
        messageMod->addInQueue( new MessageItem( "\\o/", PA_DISSOLVE, 2000 ) );
        messageMod->addInQueue( new MessageItem( "\\o/", PA_DISSOLVE, PA_FADE, 2000 ) );
        // --- FIXME Sprite do not draw correctly
        //messageMod->addInQueue( new MessageItem( "tchou", PA_SPRITE, 2000, MessageItem::SPRITES::CHEVRON ) );
        // ---
        messageMod->addInQueue( new MessageItem( "Hellow", PA_MESH, 2000 ) );
    }
}

void setup() {
    Serial.begin( 115200 );
    orchestrator.begin();
    
    orchestrator.setCurrentMod( new MessageMod );
    
    resetQueue();
    
    //Serial.print( "First: " );
    //Serial.println( orchestrator.newSlideAreAvailable() );
}

void loop() {
    
    if ( orchestrator.getCurrentMod()->instanceOfMod( IMod::ModeType::MessageMod )
         && !orchestrator.getCurrentMod()->needToRefresh() ) {
        
        Serial.println( "Reset" );
        resetQueue();
        Serial.println( "======================" );
    }
    
    orchestrator.updateDisplay();
}