/*
 * main.c
 *
 *  Created on: Jan 25, 2023
 *      Author: Notandi
 */

#include "LEDlib.h"


int main(){
	LedInit();

	while(1){
		LedOn();
		LedOff();
		LedToggle();
		LedToggle();
	}
}
