#include <MD_Parola.h>
#include "QueueH.h"
#include "Engine/Orchestrator.h"

#define HARDWARE_TYPE MD_MAX72XX::ICSTATION_HW
#define MAX_DEVICES 4
#define CLK_PIN   14
#define DATA_PIN  12
#define CS_PIN    15

//MD_Parola P = MD_Parola( HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES );

/*#define    BUF_SIZE    75
char curMessage[BUF_SIZE] = { "" };*/

/*uint8_t DEFAULT_SCROLL_SPEED = 35;    // default
// frame delay value
textPosition_t DEFAULT_SCROLL_ALIGN = PA_CENTER;*/

Orchestrator orchestrator = Orchestrator( HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES );
/*TextSlide *currentTextSlide;
TextSlide *prevTextSlide;*/

/*void resetQueue() {
    orchestrator.clearQueue();
    orchestrator.addInQueue( new TextSlide( new String( "Norway is comming soon !" ), PA_SCROLL_LEFT, 0 ));
    orchestrator.addInQueue( new TextSlide( new String( "\\o/" ), PA_DISSOLVE, 2000 ));
}*/

void setup() {
    Serial.begin( 9600 );
    orchestrator.begin();
    //P.setIntensity( 1 );
    
    orchestrator.resetQueue();
    
    Serial.print( "First: " );
    Serial.println( orchestrator.newSlideAreAvailable() );
}

void loop() {
    /*if ( orchestrator.getMatrix().displayAnimate()) {
        Serial.print( "Is available ?" );
        Serial.println( orchestrator.newSlideAreAvailable());
        
        if ( orchestrator.newSlideAreAvailable()) {
            prevTextSlide = currentTextSlide;
            delete prevTextSlide;
            currentTextSlide = orchestrator.getNextSlide();
            
            currentTextSlide->getText()->toCharArray( curMessage, currentTextSlide->getText()->length() + 1 );
            
            Serial.print( "Message: " );
            Serial.println( curMessage );
            
            //strcpy( curMessage, currentTextSlide.c_str() );
            orchestrator.getMatrix()
                        .displayText( curMessage, orchestrator.getScrollAlign(), orchestrator.getScrollSpeed(),
                                       currentTextSlide->getDelayAtEnd(), currentTextSlide->getEffect(),
                                       currentTextSlide->getEffect());
            
            Serial.println( "======================" );
            
        } else {
            Serial.println( "Reset" );
            resetQueue();
            Serial.println( "======================" );
        }
        
        orchestrator.getMatrix().displayReset();
    } else {
        //Serial.println( "Nope" );
    }*/
    
    orchestrator.updateDisplay();
}