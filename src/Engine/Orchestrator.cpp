//
// @author: SMITH Emmanuel <hey@emmanuel-smith.me>
// @site: https://emmanuel-smith.me
// Date: 24-Feb-19
// Time: 02:57 PM
//

#include "Orchestrator.h"


Orchestrator::Orchestrator( MD_MAX72XX::moduleType_t mod, uint8_t dataPin, uint8_t clkPin, uint8_t csPin,
                            uint8_t numDevices ) : matrix( MD_Parola( mod, dataPin, clkPin, csPin, numDevices ) ) {
    matrix.setIntensity( Orchestrator::DEFAULT_LED_INTENSITY );
}

// -------------------------------------
// -- Matrix

MD_Parola Orchestrator::getMatrix() {
    //Serial.println( "Get matrix" );
    return matrix;
}

void Orchestrator::begin() {
    matrix.begin();
    Serial.println( "Matrix begin" );
}

void Orchestrator::updateDisplay() {
    if ( matrix.displayAnimate() ) {
        Serial.println( "Plop" );
        currentMod->updateDisplay( &matrix );
        matrix.displayReset();
    }
}

void Orchestrator::initMod() {
    currentMod->init( &matrix );
}

void Orchestrator::resetMod() {
    currentMod->reset( &matrix );
}

// -------------------------------------


// -------------------------------------
// -- Mod management

IMod *Orchestrator::getCurrentMod() {
    return currentMod;
}

void Orchestrator::setCurrentMod( IMod *currentMod ) {
    Orchestrator::currentMod = currentMod;
}

// -------------------------------------

