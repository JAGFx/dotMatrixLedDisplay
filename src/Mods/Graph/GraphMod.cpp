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
            columnCount = columnCount % getOriginalColumnCount();
            matrix->getGraphicObject()->setPoint( baselineRow, columnCount - 1, bPoint );
    
            /*Serial.println( "=== START" );
            Serial.println( columnCount );
            Serial.println( originalColumnCount );*/
            /*Serial.println( currentState );
            Serial.println( originalColumnCount );
            Serial.println( restart );
            Serial.println( animationFinished );
            Serial.println( bPoint );
            *//*Serial.println( COL_SIZE );
            Serial.println( ROW_SIZE );*//*
            Serial.println( "=========================" );*/
            
            switch ( currentState ) {
                case STATE_START: // straight line from the right side
                    //Serial.println( "----------------- STATE_START" );
    
                    if ( columnCount == getOriginalColumnCount() / 2 + COL_SIZE )
                        currentState = STATE_FIRST_STROKE;
                    columnCount--;
                    break;
                
                case STATE_FIRST_STROKE: // first stroke
                    //Serial.println( "----------------- STATE_FIRST_STROKE" );
                    if ( baselineRow != 0 ) {
                        baselineRow--;
                        columnCount--;
                    } else currentState = STATE_DOWN_STROKE;
                    break;
                
                case STATE_DOWN_STROKE: // down stroke
                    //Serial.println( "----------------- STATE_DOWN_STROKE" );
                    if ( baselineRow != ROW_SIZE - 1 ) {
                        baselineRow++;
                        columnCount--;
                    } else currentState = STATE_UP_STROKE;
                    break;
                
                case STATE_UP_STROKE: // second up stroke
                    //Serial.println( "----------------- STATE_UP_STROKE" );
                    if ( baselineRow != BASELINE_ROW ) {
                        baselineRow--;
                        columnCount--;
                    } else currentState = STATE_LAST_STROKE;
                    break;
                
                case STATE_LAST_STROKE: // straight line to the left
                    //Serial.println( "----------------- STATE_LAST_STROKE" );
                    if ( columnCount == 0 ) {
                        if ( !bPoint ) {
                            animationFinished = true;
                            restart           = true;
                        } else {
                            bPoint       = !bPoint;
                            currentState = STATE_START;
                        }
                    } else columnCount--;
                    break;
            }
    
            //Serial.println( "=== END" );
            //Serial.println( currentState );
            //Serial.println( "=========================" );
    
            delay( SPEED_ANIMATION_MS / 8 );
        }
    }
    
    delay( SPEED_ANIMATION_MS );
}

void GraphMod::init( MD_Parola *matrix ) {
    originalColumnCount = matrix->getGraphicObject()->getColumnCount();
    //Serial.println(originalColumnCount);
    
    matrix->getGraphicObject()->clear();
    matrix->getGraphicObject()->control( MD_MAX72XX::UPDATE, MD_MAX72XX::ON );
    
    currentState      = STATE_START;
    baselineRow       = BASELINE_ROW;
    columnCount       = getOriginalColumnCount() - 1;
    bPoint            = true;
    restart           = false;
    animationFinished = false;
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
