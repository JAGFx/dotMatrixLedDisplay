//
// @author: SMITH Emmanuel <hey@emmanuel-smith.me>
// @site: https://emmanuel-smith.me
// Date: 24-Feb-19
// Time: 02:57 PM
//

#include <MD_Parola.h>
#include <HardwareSerial.h>
#include "QueueH.h"
#include "Engine/Orchestrator.h"
#include "Engine/ExternalDeviceInteraction.h"
#include "Mods/Message/MessageMod.h"
#include "Mods/Graph/GraphMod.h"
#include "Mods/Tracking/TrackingMod.h"

// -------------------------------------------------
// --- Switch activeMod

#define SWITCH_MOD_PIN 25
#define DEBOUNCE_DELAY_MS 250

volatile IMod::ModeType activeMod  = IMod::ModeType::Message;
volatile bool           changedMod = false;
volatile unsigned long  lastMillis = 0;

portMUX_TYPE mux                          = portMUX_INITIALIZER_UNLOCKED;

void IRAM_ATTR

handleSwitchMod() {
    portENTER_CRITICAL_ISR( &mux );
    unsigned long currentMillis = millis();
    
    if ( currentMillis - lastMillis >= DEBOUNCE_DELAY_MS ) {
        activeMod  = static_cast<IMod::ModeType>(( activeMod + 1 ) % IMod::ModeType::NumOfMod);
        changedMod = true;
        lastMillis = currentMillis;
        
        /*Serial.println( "################## SWITCH MOD !!!" );
        Serial.println( activeMod );
        Serial.println( "################## activeMod" );*/
    }
    
    portEXIT_CRITICAL_ISR( &mux );
}

// --- ./Switch activeMod
// -------------------------------------------------



// -------------------------------------------------
// --- BLE parse action

ExternalDeviceInteraction edi;
bool                      actionInProcess = false;

void handleBLEAction( esp_spp_cb_event_t event, esp_spp_cb_param_t *param ) {
    switch ( event ) {
        case ESP_SPP_INIT_EVT:
            Serial.println( "Bluetooth Device is Ready to Pair" );
            break;
        
        case ESP_SPP_SRV_OPEN_EVT:
            Serial.println( "Client Connected has address:" );
            break;
        
        case ESP_SPP_DATA_IND_EVT:
            Serial.println( "Data received" );
            ExternalDeviceInteraction::BLE_ACTIONS command = ExternalDeviceInteraction::BLE_ACTIONS::NONE;
            
            char buf[1024];
            snprintf( buf, ( size_t ) param->data_ind.len, ( char * ) param->data_ind.data );
            command = ( ExternalDeviceInteraction::BLE_ACTIONS ) strtol( buf, 0, 16 );
            
            Serial.println( strtol( buf, 0, 16 ) );
            
            if ( command != ExternalDeviceInteraction::BLE_ACTIONS::NONE && !actionInProcess ) {
                actionInProcess = true;
                
                switch ( command ) {
                    case ExternalDeviceInteraction::BLE_ACTIONS::SWITCH_MODE:
                        handleSwitchMod();
                        actionInProcess = false;
                        break;
                    
                    case ExternalDeviceInteraction::BLE_ACTIONS::CURRENT_MODE:
                        edi.sendData( String( activeMod ) );
                        actionInProcess = false;
                        break;
                }
            }
            
            break;
    }
}

// --- ./BLE parse action
// -------------------------------------------------



#define HARDWARE_TYPE MD_MAX72XX::ICSTATION_HW
#define MAX_DEVICES 8
#define CLK_PIN   14
#define DATA_PIN  12
#define CS_PIN    15

#define GPS_ESP_SERIAL 2
#define GPS_SERIAL_BAUD 0

Orchestrator orchestrator = Orchestrator( HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES );

HardwareSerial gpsSerial( GPS_ESP_SERIAL );

void resetData() {
    orchestrator.resetMod();
    
    if ( orchestrator.getCurrentMod()->instanceOfMod( IMod::ModeType::Message ) ) {
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
        if ( gpsSerial.available() > 0 )
            trackingMod->updateRawData( gpsSerial.read() );
    }
}

void initOrchestrator() {
    delete orchestrator.getCurrentMod();
    orchestrator.setCurrentMod( nullptr );
    
    switch ( activeMod ) {
        case IMod::ModeType::Message:
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
    pinMode( SWITCH_MOD_PIN, INPUT_PULLUP );
    attachInterrupt( digitalPinToInterrupt( SWITCH_MOD_PIN ), handleSwitchMod, FALLING );
    // --- ./Switch activeMod
    
    gpsSerial.begin( GPS_SERIAL_BAUD ); // RX, TX
    //https://quadmeup.com/arduino-esp32-and-3-hardware-serial-ports/
    
    edi.getBLESerial()->register_callback( handleBLEAction );
    edi.init();
    // https://circuitdigest.com/microcontroller-projects/using-classic-bluetooth-in-esp32-and-toogle-an-led
    // https://www.dfrobot.com/blog-1204.html
    
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
