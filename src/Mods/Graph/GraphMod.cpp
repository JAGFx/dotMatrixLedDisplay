//
// Created by CLion.
// @author: SMITH Emmanuel <hey@emmanuel-smith.me>
// @site: https://emmanuel-smith.me
// Date: 02-Mar-19
// Time: 10:05
//

#include "GraphMod.h"

// -------------------------------------
// -- IMod

void GraphMod::updateDisplay( MD_Parola *matrix ) {
    
    if ( needToRefresh() ) {
        restart = false;
        
        while ( !animationFinished ) {
            uint8_t originalColumnCount = matrix->getGraphicObject()->getColumnCount();
            
            matrix->getGraphicObject()->setPoint( baselineRow, columnCount - 1, bPoint );
            
            Serial.println( "=== START" );
            Serial.println( columnCount );
            Serial.println( currentState );
            Serial.println( originalColumnCount );
            Serial.println( restart );
            Serial.println( animationFinished );
            Serial.println( bPoint );
            /*Serial.println( COL_SIZE );
            Serial.println( ROW_SIZE );*/
            Serial.println( "=========================" );
            
            switch ( currentState ) {
                case STATE_START: // straight line from the right side
                    Serial.println( "----------------- STATE_START" );
                    
                    if ( columnCount == originalColumnCount / 2 + COL_SIZE )
                        currentState = STATE_FIRST_STROKE;
                    columnCount--;
                    break;
                
                case STATE_FIRST_STROKE: // first stroke
                    Serial.println( "----------------- STATE_FIRST_STROKE" );
                    if ( baselineRow != 0 ) {
                        baselineRow--;
                        columnCount--;
                    } else currentState = STATE_DOWN_STROKE;
                    break;
                
                case STATE_DOWN_STROKE: // down stroke
                    Serial.println( "----------------- STATE_DOWN_STROKE" );
                    if ( baselineRow != ROW_SIZE - 1 ) {
                        baselineRow++;
                        columnCount--;
                    } else currentState = STATE_UP_STROKE;
                    break;
                
                case STATE_UP_STROKE: // second up stroke
                    Serial.println( "----------------- STATE_UP_STROKE" );
                    if ( baselineRow != BASELINE_ROW ) {
                        baselineRow--;
                        columnCount--;
                    } else currentState = STATE_LAST_STROKE;
                    break;
                
                case STATE_LAST_STROKE: // straight line to the left
                    Serial.println( "----------------- STATE_LAST_STROKE" );
                    if ( columnCount == 0 ) {
                        bPoint       = !bPoint;
                        currentState = STATE_START;
                    } else columnCount--;
                    break;
                
                default:
                    Serial.println( "----------------- DEFAULT" );
                    currentState      = STATE_START;
                    animationFinished = true;
                    restart           = true;
                    break;
            }
            
            Serial.println( "=== END" );
            Serial.println( currentState );
            Serial.println( "=========================" );
            
            //delay( 25 );
        }
    }
    
    //delay(25);
}

void GraphMod::init( MD_Parola *matrix ) {
    uint8_t originalColumnCount = matrix->getGraphicObject()->getColumnCount();
    
    matrix->getGraphicObject()->clear();
    matrix->getGraphicObject()->control( MD_MAX72XX::UPDATE, MD_MAX72XX::ON );
    
    columnCount = originalColumnCount - 1;
    baselineRow = BASELINE_ROW;
    restart     = false;
    bPoint      = true;
    
    currentState = STATE_START;
}

void GraphMod::reset( MD_Parola *matrix ) {
    init( matrix );
}

bool GraphMod::needToRefresh() {
    return !restart;
}

bool GraphMod::instanceOfMod( IMod::ModeType type ) {
    return type == IMod::ModeType::Graph;
}


// -------------------------------------
