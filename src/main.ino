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

#define DEBOUNCE_DELAY_MS 250

Orchestrator           orchestrator = Orchestrator( HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES );

// --- Switch activeMod
enum AVAILABLE_MOD {
    MESSAGE_MOD,
    GRAPH_MOD,
    NUM_OF_MOD
};
volatile AVAILABLE_MOD activeMod    = MESSAGE_MOD;
volatile bool          changedMod   = false;
volatile unsigned long lastMillis   = 0;

portMUX_TYPE mux = portMUX_INITIALIZER_UNLOCKED;
// --- ./Switch activeMod

void resetQueue() {
    if ( orchestrator.getCurrentMod()->instanceOfMod( IMod::ModeType::MessageMod ) ) {
        //Serial.println( ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Message mode reset queue" );
        MessageMod *messageMod = ( MessageMod * ) orchestrator.getCurrentMod();
        
        messageMod->clearQueue();
        messageMod->addInQueue( new MessageItem( "Norway is coming soon !", PA_SCROLL_LEFT, 0 ) );
        messageMod->addInQueue( new MessageItem( "\\o/", PA_DISSOLVE, 2000 ) );
        messageMod->addInQueue( new MessageItem( "\\o/", PA_DISSOLVE, PA_FADE, 2000 ) );
        // --- FIXME Sprite do not draw correctly
        //messageMod->addInQueue( new MessageItem( "tchou", PA_SPRITE, 2000, MessageItem::SPRITES::CHEVRON ) );
        // ---
        messageMod->addInQueue( new MessageItem( "Hellow", PA_MESH, 2000 ) );
    
    } else if ( orchestrator.getCurrentMod()->instanceOfMod( IMod::ModeType::MessageMod ) ) {
        //Serial.println( ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Graph mode reset queue" );
        //GraphMod *graphMod = ( GraphMod * ) orchestrator.getCurrentMod();
        orchestrator.resetMod();
    }
}

void IRAM_ATTR

handleSwitchMod() {
    portENTER_CRITICAL_ISR( &mux );
    unsigned long currentMillis = millis();
    
    if ( currentMillis - lastMillis >= DEBOUNCE_DELAY_MS ) {
        activeMod  = static_cast<AVAILABLE_MOD>(( activeMod + 1 ) % NUM_OF_MOD);
        changedMod = true;
        lastMillis = currentMillis;
        
        /*Serial.println( "################## SWITCH MOD !!!" );
        Serial.println( activeMod );
        Serial.println( "################## activeMod" );*/
    }
    
    portEXIT_CRITICAL_ISR( &mux );
}

void initOrchestrator() {
    delete orchestrator.getCurrentMod();
    orchestrator.setCurrentMod( nullptr );
    
    switch ( activeMod ) {
        case MESSAGE_MOD:
            orchestrator.setCurrentMod( new MessageMod );
            resetQueue();
            //Serial.println( ">>> MESSAGE MOD" );
            break;
        
        case GRAPH_MOD:
            orchestrator.setCurrentMod( new GraphMod );
            //Serial.println( ">>> GRAPH MOD" );
            break;
    }
    
    orchestrator.initMod();
    resetQueue();
    
    changedMod = false;
}

void setup() {
    Serial.begin( 115200 );
    
    // --- Switch activeMod
    pinMode( SWITCH_MOD_MIN, INPUT_PULLUP );
    attachInterrupt( digitalPinToInterrupt( SWITCH_MOD_MIN ), handleSwitchMod, FALLING );
    // --- ./Switch activeMod
    
    orchestrator.begin();
    
    initOrchestrator();
}

void loop() {
    if ( changedMod ) {
        initOrchestrator();
        //Serial.println("#### LOOP ####");
    } else {
        if ( !orchestrator.getCurrentMod()->needToRefresh() ) {
            //Serial.println( "Reset" );
            orchestrator.resetMod();
            
            if ( orchestrator.getCurrentMod()->instanceOfMod( IMod::ModeType::MessageMod ) ) {
                // -------------------------------------
                // -- MessageMod
                
                resetQueue();
                
                // -------------------------------------
            }
    
            //Serial.println( "======================" );
        }
        
        orchestrator.updateDisplay();
    }
}
