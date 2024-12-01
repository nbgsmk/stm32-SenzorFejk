/*
 * SenzorCommon.hpp
 *
 *  Created on: Nov 30, 2024
 *      Author: peca
 */

#ifndef SRC_SENSORCOMMON_HPP_
#define SRC_SENSORCOMMON_HPP_

#include <iostream>
#include <vector>


typedef struct {
	std::vector<uint8_t> Q;						// Question: senzor prima ovo pitanje
	uint16_t delaymS;							// vreme dok pripremi odgovor
	std::vector< std::vector<uint8_t> > AA;		// Answer: vector mogucih odgovora { svaki put drugacija koncentracija, temperatura, checksum itd }
} QandA_t;


////////////////////////////////
//
//	ACTIVE / PASSIVE MODE
//
////////////////////////////////

/*
 *
 * 4.1.1 SWITCH TO AUTO REPORTING MODE
 *
 */
QandA_t setActiveMode = {
		Q = { 0xff, 0x01, 0x78, 0x40, 0x00, 0x00, 0x00, 0x00, 0x47 },
		delaymS = 43,
		A = { }				// ne ocekuje se nikakav odgovor
};


/*
 *
 * 4.1.2 SWITCH TO QUERY MODE
 *
 */
QandA_t setPassiveMode = {
		Q = { 0xff, 0x01, 0x78, 0x41, 0x00, 0x00, 0x00, 0x00, 0x46 },
		delaymS = 43,
		A = { }				// ne ocekuje se nikakav odgovor
};




//////////////////////////////////////////////
//
// 4.5 QUERY TEMPERATURE AND RELATIVE HUMIDITY
//
//////////////////////////////////////////////

/*
 *
 * 4.5.1 Query Temperature and Relative Humidity (Method 1)
 * 0xD2
 *
 */
QandA_t getTempAndRh_D2 = {
		Q = { 0xD2 },
		delaymS = 43,
		A = {
				{ 0x07, 0x3B, 0x21, 0x07 },		// 0x073B => 18.51 °C; 0x2107 => 84.55 % relative humidity, both with fixed 2 decimals
				{ 0x04, 0xD2, 0x16, 0x2E }		// 0x04D2 => 12.34 °C; 0x162E => 56.78 % relative humidity, both with fixed 2 decimals
		}
};

/*
 *
 * 4.5.1 Query Temperature and Relative Humidity (Method 1)
 * 0xD6
 *
 */
QandA_t getTempAndRh_D6 = {
		Q = { 0xD6 },
		delaymS = 43,
		A = {
				{ 0x07, 0x3B, 0x21, 0x07, 0x96 },	// 0x073B => 18.51 °C; 0x2107 => 84.55 % relative humidity, both with fixed 2 decimals
													// Checksum (-(0x07+0x3B+0x21+0x07))&0xFF = 0x96
				{ 0x04, 0xD2, 0x16, 0x2E, 0xE6 }	// 0x04D2 => 12.34 °C; 0x162E => 56.78 % relative humidity, both with fixed 2 decimals
		}
};




/////////////////////////
//
// 4.6 QUERY SOFTWARE VERSION
//
/////////////////////////
QandA_t getSoftwareVersion = {
		Q = { 0xD3 },
		delaymS = 43,
		A = {
				{ 0x20, 0x23, 0x11, 0x08, 0x14, 0x54 },		// 0x202311081454, After conversion to BCD code, 202311081454
				{ 0x19, 0x70, 0x05, 0x25, 0x04, 0x44 }
		}
};



////////////////
//
// 4.8 LED CONTROL
//
////////////////

/*
 *
 * 4.8.1 SWITCH ON LED
 *
 */
QandA_t setLedOn = {
		Q = { 0xff, 0x01, 0x88, 0x00, 0x00, 0x00, 0x00, 0x00, 0x77 },
		delaymS = 43,
		A = {
				{ 0x0f, 0x4B }		// u prevodu "OK"
		}
};


/*
 *
 * 4.8.1 SWITCH OFF LED
 *
 */
QandA_t setLedOff = {
		Q = { 0xff, 0x01, 0x89, 0x00, 0x00, 0x00, 0x00, 0x00, 0x76 },
		delaymS = 43,
		A = {
				{ 0x0f, 0x4B }		// u prevodu "OK"
		}
};


/*
 *
 * 4.8.3 LED RUNNING STATUS
 *
 */
QandA_t getLedStat = {
		Q = { 0xff, 0x01, 0x8A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x75 },
		delaymS = 43,
		A = {																// 0xff, 0x8A = header
				{ 0xff, 0x8A, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x75 },	// 0x01 = on;  0x75 checksum = (-(0x8A+0x01+0x00+0x00+0x00+0x00+0x00))&0xFF
				{ 0xff, 0x8A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x76 }	// 0x00 = off; 0x76 checksum = (-(0x8A+0x00+0x00+0x00+0x00+0x00+0x00))&0xFF
		}
};


QandA_t setLedOff = {
		Q = {0x23, 0x32, 0x45},
		delaymS = 43,
		A = {
				{ 0x23, 0x32, 0x45 },
				{ 0x23, 0x32, 0x45 },
				{ 0x23, 0x32, 0x45 }
		}
};






//	void ledOn(void);
//	void ledBlink_Rpi(uint32_t ticksOn, uint32_t ticksOff);


#endif /* SRC_SENSORCOMMON_HPP_ */
