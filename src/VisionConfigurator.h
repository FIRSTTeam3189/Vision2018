/*
 * VisionConfigurator.h
 *
 *  Created on: Jan 11, 2018
 *      Author: nvidia
 */

#ifndef VISIONCONFIGURATOR_H_
#define VISIONCONFIGURATOR_H_
#include "Common.h"
//Jamess turned Devv into a communist
using namespace cv;

constexpr auto ORIGINAL_WINDOW_STR = "Original";
constexpr auto MODIFIED_WINDOW_STR = "Modified Image";
constexpr auto TRACKBAR_WINDOW_STR = "Config";

json gen_config(VideoCapture& videoStream);

#endif /* VISIONCONFIGURATOR_H_ */
