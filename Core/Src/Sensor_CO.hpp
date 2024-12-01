/*
 * Senzor_O2.hpp
 *
 *  Created on: Nov 30, 2024
 *      Author: peca
 */

#ifndef SRC_SENSOR_O2_HPP_
#define SRC_SENSOR_O2_HPP_


#include "SensorCommon.hpp"

//////////////////////////////////////
//
// 4.2 QUERY SENSOR MODULE PARAMETERS
//
//////////////////////////////////////


/*
 *
 * 4.2.1 QUERY SENSOR MODULE PARAMETERS
 * (Method 1)
 * D1
 *
 */
QandA_t getSensorProperties_D1 = {
		Q = { 0xD1 },
		delaymS = 43,
		A = {
			/*
			 * Example: 0x19 0x03 0xE8 0x02 0x00 0x00 0x00 0x30 0xE3
				0x19 			type "CO"
				0x03 0xE8		Range only in units of concentration-1: 0x3e8 = 1000
				0x02 			Units: for concentration-2 is mg/m3 and for concentration-1 is ppm
				0x00 0x00 0x00	reserved
				0x30			0x30 >> 4 = 0x03 -> 3 decimals, divide results by 1000
				0xE3			checksum = (-(0x03+0xE8+0x02+0x00+0x00+0x00+0x30))&0xFF = 0xE3

				(*)				result:	unit for conc-1 = ppm;
				 	 	 	 			unit for conc-2 = mg/m3;
				 	 	 	 			range=1000ppm;
				 	 	 	 			decimals = 3
			 */
			//  0   |    1     2    |   3     |  4     5     6    |     7      |     8
			// tip, | range conc-1, |  unit,  |                 , |  decimals, | checksum
			{ 0x19,     0x03, 0xE8,    0x02,    0x00, 0x00, 0x00,      0x30,       0xE3 },	// conc-1 range/unit is 1000 ppm;  conc-2 unit is mg/m3;  3 decimal places
			{ 0x19,     0x04, 0xD2,    0x04,    0x00, 0x00, 0x00,      0x20,       0x06 },	// conc-1 range/unit is 1234 ppb;  conc-2 unit is ug/m3;  2 decimal places
			{ 0x19,     0x16, 0x2E,    0x08,    0x00, 0x00, 0x00,      0x10,       0xA4 },	// conc-1 range/unit is 5678 %vol; conc-2 unit is 10g/m3; 1 decimal place
		}
};




/*
 *
 * 4.2.1 QUERY SENSOR MODULE PARAMETERS
 * (Method 2)
 * D7
 *
 */
QandA_t getSensorProperties_D7 = {
		Q = { 0xD7 },
		delaymS = 43,
		A = {
			/*
			 * Example: 0xFF 0xD7 0x19 0x03 0xE8 0x02 0x30 0x00 0xF3
				0xFF 0xD7		command header
				0x19 			type "CO"
				0x03 0xE8		Range only in units of concentration-1: 0x3e8 = 1000
				0x02 			Units: for concentration-2 is mg/m3 and for concentration-1 is ppm
				0x30			0x30 >> 4 = 0x03 -> 3 decimals, divide results by 1000
				0x00			reserved
				0xF3			Checksum (-(0xD7+0x19+0x03+0xE8+0x02+0x30+0x00))&0xFF = 0xF3

				(*)				result:	unit for conc-1 = ppm;
				 	 	 	 			unit for conc-2 = mg/m3;
				 	 	 	 			range=1000ppm;
				 	 	 	 			decimals = 3
			 */
			//  0    1    |    2   |    3     4    |   5      |     6      |   7    |     8
			//   header   |   tip, | range conc-1  |  unit,   | decimals,  |        | checksum
			{ 0xFF, 0xD7,    0x19,     0x03, 0xE8,    0x02,       0x30,      0x00,    0xE3 },	// conc-1 range/unit is 1000 ppm;  conc-2 unit is mg/m3;  3 decimal places
			{ 0xFF, 0xD7,    0x19,     0x04, 0xD2,    0x04,       0x20,      0x00,    0x18 },	// conc-1 range/unit is 1234 ppb;  conc-2 unit is ug/m3;  2 decimal places
			{ 0xFF, 0xD7,    0x19,     0x16, 0x2E,    0x08,       0x10,      0x00,    0xB4 },	// conc-1 range/unit is 5678 %vol; conc-2 unit is 10g/m3; 1 decimal place
		}
};




///////////////////////////////////////
//
// 4.3 QUERY CURRENT GAS CONCENTRATION
//
///////////////////////////////////////

///////////////////////////////////////
//
// 4.4 QUERY GAS CONCENTRATION, TEMPERATURE AND RELATIVE HUMIDITY
//
///////////////////////////////////////






#endif /* SRC_SENSOR_O2_HPP_ */
