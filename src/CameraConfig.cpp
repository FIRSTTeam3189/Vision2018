/*
 * CameraConfig.cpp
 *
 *  Created on: Jan 11, 2018
 *      Author: nvidia
 */
#include "CameraConfig.h"
#include "Common.h"
std::ostream& operator<<(std::ostream& s, const Config& config){
	s << "[" << config.hueLow << ", " << config.hueHigh << "]\n";
	s << "[" << config.satLow << ", " << config.satHigh << "]\n";
	s << "[" << config.valueLow << ", " << config.valueHigh << "]\n";
	return s;
}
