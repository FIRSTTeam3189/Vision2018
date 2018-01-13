/*
 * CameraConfig.h
 *
 *  Created on: Jan 11, 2018
 *      Author: nvidia
 */

#ifndef CAMERACONFIG_H_
#define CAMERACONFIG_H_

#include <iostream>
#include "Common.h"

struct Config {
	Int32 hueLow = 0;
	Int32 hueHigh = 255;
	Int32 valueLow = 0;
	Int32 valueHigh = 255;
	Int32 satLow = 0;
	Int32 satHigh = 255;
};
constexpr auto HUE_LOW_KEY="hue_low";
constexpr auto HUE_HIGH_KEY="hue_high";
constexpr auto VALUE_LOW_KEY="value_low";
constexpr auto VALUE_HIGH_KEY="value_high";
constexpr auto SAT_LOW_KEY="sat_low";
constexpr auto SAT_HIGH_KEY="sat_high";
std::ostream& operator<<(std::ostream& s,const Config&);

#endif /* CAMERACONFIG_H_ */
