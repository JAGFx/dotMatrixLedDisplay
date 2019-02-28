#include <MD_Parola.h>
#include "QueueH.h"
#include "Engine/Orchestrator.h"

#define HARDWARE_TYPE MD_MAX72XX::ICSTATION_HW
#define MAX_DEVICES 4
#define CLK_PIN   14
#define DATA_PIN  12
#define CS_PIN    15

Orchestrator orchestrator = Orchestrator( HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES );

void resetQueue() {
    orchestrator.clearQueue();
    orchestrator.addInQueue( new TextSlide( "Norway is comming soon !", PA_SCROLL_LEFT, 0 ) );
    orchestrator.addInQueue( new TextSlide( "\\o/", PA_DISSOLVE, 2000 ) );
    orchestrator.addInQueue( new TextSlide( "\\o/", PA_DISSOLVE, 2000 ) );
    // TODO Add text slide with distinct in and out effect
    // Fixme add 2 textSlide if effect "PA_DISSOLVE" was selected
}

void setup() {
    Serial.begin( 9600 );
    orchestrator.begin();
    
    resetQueue();
    
    Serial.print( "First: " );
    Serial.println( orchestrator.newSlideAreAvailable() );
}

void loop() {
    
    if ( !orchestrator.newSlideAreAvailable() ) {
        
        Serial.println( "Reset" );
        resetQueue();
        Serial.println( "======================" );
    }
    
    orchestrator.updateDisplay();
}