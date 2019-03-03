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
#include "Mods/Graph/GraphMod.h"

#define HARDWARE_TYPE MD_MAX72XX::ICSTATION_HW
#define MAX_DEVICES 4
#define CLK_PIN   14
#define DATA_PIN  12
#define CS_PIN    15

#define SWITCH_MOD_MIN 25

Orchestrator orchestrator = Orchestrator( HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES );

// --- Switch mod
volatile bool mod        = false;
volatile bool changedMod = false;

portMUX_TYPE mux = portMUX_INITIALIZER_UNLOCKED;
// --- ./Switch mod

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

void IRAM_ATTR

handleSwitchMod() {
    portENTER_CRITICAL_ISR( &mux );
    Serial.println( "################## SWITCH MOD !!!" );
    Serial.println( mod );
    Serial.println( "################## mod" );
    /*delete orchestrator.getCurrentMod();
    
    
    
    orchestrator.getMatrix().displayReset();
    orchestrator.initMod();*/
    
    mod        = !mod;
    changedMod = true;
    
    portEXIT_CRITICAL_ISR( &mux );
}

void initOrchestrator() {
    //orchestrator.getMatrix().displaySuspend(true);
    // FIXME correct crash when change the mod
    delete orchestrator.getCurrentMod();
    
    if ( !mod ) {
        orchestrator.setCurrentMod( new MessageMod );
        resetQueue();
    } else
        orchestrator.setCurrentMod( new GraphMod );
    
    orchestrator.initMod();
    resetQueue();
    
    //orchestrator.getMatrix().displayReset(true);
    
    changedMod = false;
}

void setup() {
    Serial.begin( 115200 );
    pinMode( SWITCH_MOD_MIN, INPUT_PULLUP );
    attachInterrupt( digitalPinToInterrupt( SWITCH_MOD_MIN ), handleSwitchMod, FALLING );
    
    orchestrator.begin();
    
    initOrchestrator();
    
    //orchestrator.setCurrentMod( new MessageMod );
    //orchestrator.setCurrentMod( new GraphMod );
    //orchestrator.initMod();
    
    //resetQueue();
    
    //Serial.print( "First: " );
    //Serial.println( orchestrator.newSlideAreAvailable() );
}

void loop() {
    
    if ( changedMod )
        initOrchestrator();
    else {
        if ( !orchestrator.getCurrentMod()->needToRefresh() ) {
            Serial.println( "Reset" );
            orchestrator.resetMod();
            
            if ( orchestrator.getCurrentMod()->instanceOfMod( IMod::ModeType::MessageMod ) ) {
                // -------------------------------------
                // -- MessageMod
                
                resetQueue();
                
                // -------------------------------------
            }
            
            Serial.println( "======================" );
        }
        
        orchestrator.updateDisplay();
    }
}
