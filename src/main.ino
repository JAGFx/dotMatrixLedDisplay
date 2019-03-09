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
#include "Mods/Tracking/TrackingMod.h"

// -------------------------------------------------
// --- Switch activeMod

#define SWITCH_MOD_MIN 25
#define DEBOUNCE_DELAY_MS 250

volatile IMod::ModeType activeMod  = IMod::ModeType::MessageMod;
volatile bool           changedMod = false;
volatile unsigned long  lastMillis = 0;

portMUX_TYPE mux = portMUX_INITIALIZER_UNLOCKED;

void IRAM_ATTR

handleSwitchMod() {
    portENTER_CRITICAL_ISR( &mux );
    unsigned long currentMillis = millis();
    
    if ( currentMillis - lastMillis >= DEBOUNCE_DELAY_MS ) {
        activeMod  = static_cast<IMod::ModeType>(( activeMod + 1 ) % IMod::ModeType::NumOfMod);
        changedMod = true;
        lastMillis = currentMillis;
        
        // FIXME Crash when you change th current mod from "Tracking"
        
        /*Serial.println( "################## SWITCH MOD !!!" );
        Serial.println( activeMod );
        Serial.println( "################## activeMod" );*/
    }
    
    portEXIT_CRITICAL_ISR( &mux );
}

// --- ./Switch activeMod
// -------------------------------------------------

#define HARDWARE_TYPE MD_MAX72XX::ICSTATION_HW
#define MAX_DEVICES 4
#define CLK_PIN   14
#define DATA_PIN  12
#define CS_PIN    15

Orchestrator orchestrator = Orchestrator( HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES );

void resetData() {
    orchestrator.resetMod();
    
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
    
    } else if ( orchestrator.getCurrentMod()->instanceOfMod( IMod::ModeType::Tracking ) ) {
        //Serial.println( ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Graph mode reset queue" );
        TrackingMod *trackingMod = ( TrackingMod * ) orchestrator.getCurrentMod();
        const char  *gpsStream   =
                            "$GPRMC,045103.000,A,3014.1984,N,09749.2872,W,0.67,161.46,030913,,,A*7C\r\n"
                            "$GPGGA,045104.000,3014.1985,N,09749.2873,W,1,09,1.2,211.6,M,-22.5,M,,0000*62\r\n"
                            "$GPRMC,045200.000,A,3014.3820,N,09748.9514,W,36.88,65.02,030913,,,A*77\r\n"
                            "$GPGGA,045201.000,3014.3864,N,09748.9411,W,1,10,1.2,200.8,M,-22.5,M,,0000*6C\r\n"
                            "$GPRMC,045251.000,A,3014.4275,N,09749.0626,W,0.51,217.94,030913,,,A*7D\r\n"
                            "$GPGGA,045252.000,3014.4273,N,09749.0628,W,1,09,1.3,206.9,M,-22.5,M,,0000*6F\r\n";
        trackingMod->updateRawData( gpsStream );
    }
}

void initOrchestrator() {
    delete orchestrator.getCurrentMod();
    orchestrator.setCurrentMod( nullptr );
    
    switch ( activeMod ) {
        case IMod::ModeType::MessageMod:
            orchestrator.setCurrentMod( new MessageMod );
            //Serial.println( ">>> MESSAGE MOD" );
            break;
    
        case IMod::ModeType::Graph:
            orchestrator.setCurrentMod( new GraphMod );
            //Serial.println( ">>> GRAPH MOD" );
            break;
    
        case IMod::ModeType::Tracking:
            orchestrator.setCurrentMod( new TrackingMod );
            //Serial.println( ">>> TRACKING MOD" );
            break;
    }
    
    orchestrator.initMod();
    resetData();
    
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
            resetData();
            //Serial.println( "======================" );
        }
        
        orchestrator.updateDisplay();
    }
}
