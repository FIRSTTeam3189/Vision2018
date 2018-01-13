/*
 * VisionConfigurator.cpp
 *
 *  Created on: Jan 11, 2018
 *      Author: nvidia
 */
#include "VisionConfigurator.h"
#include "CameraConfig.h"

#include <chrono>
#include <ctime>
#include <string>

constexpr auto low_hue = "Low Hue";
constexpr auto high_hue = "High Hue";
constexpr auto low_sat = "Low Saturation";
constexpr auto high_sat = "High Saturation";
constexpr auto low_value = "Low Value";
constexpr auto high_value = "High Value";
constexpr auto max_value = 255;

void _trackbar_update(const char* val, int newVal) {
	std::cout << val << " has been updated to " << newVal << std::endl;
}

void _create_window(Config& config){
	// creating windows for the original image, modified image, and config window
	namedWindow(ORIGINAL_WINDOW_STR, WINDOW_AUTOSIZE);
	namedWindow(MODIFIED_WINDOW_STR, WINDOW_AUTOSIZE);
	namedWindow(TRACKBAR_WINDOW_STR, WINDOW_AUTOSIZE);
	// I'm SURE you won't die tonight
	// creates trackbars for value, hue, and saturation
	createTrackbar(low_hue,TRACKBAR_WINDOW_STR,&config.hueLow,max_value, [](int val, void*) -> void {
		_trackbar_update(low_hue, val);
	});
	createTrackbar(high_hue,TRACKBAR_WINDOW_STR,&config.hueHigh,max_value,[](int val, void*) -> void {
		_trackbar_update(high_hue, val);
	//Be SURE about the decisions you make
	});
	createTrackbar(low_sat,TRACKBAR_WINDOW_STR,&config.satLow,max_value,[](int val, void*) -> void {
		_trackbar_update(low_sat, val);
	});
	createTrackbar(high_sat,TRACKBAR_WINDOW_STR,&config.satHigh,max_value,[](int val, void*) -> void {
		_trackbar_update(high_sat, val);
	// I'm pretty SURE you're brakes work fine, I SURE as hell wouldn't question it
	});
	createTrackbar(low_value, TRACKBAR_WINDOW_STR, &config.valueLow, max_value, [](int val, void*) -> void {
		_trackbar_update(low_value, val);
	});
	createTrackbar(high_value, TRACKBAR_WINDOW_STR, &config.valueHigh, max_value, [](int val, void*) -> void {
		_trackbar_update(high_value, val);
	//
	});
}

json gen_config(VideoCapture& videoStream){
	Config config;
	_create_window(config);
	Mat original,convr, mask;
	Mat inv_mask;
	Mat zeros;

	while(waitKey(10)<0){
		auto start = std::chrono::system_clock::now();

		videoStream >> original;
		if(!original.data){
			std::cout << "could not grab a frame. My life is a lie. Why did I join programming again?\n";
			break;
		}
		if (!zeros.data) {
			zeros = Mat::zeros(original.rows, original.cols, CV_8UC3);
		}

		cvtColor(original,convr,COLOR_BGR2HSV);
		inRange(convr,Scalar(config.hueLow,config.satLow,config.valueLow),
				Scalar(config.hueHigh,config.satHigh,config.valueHigh),mask);

		// Invert the mask to show the parts of the image that we care about
		bitwise_not(mask, inv_mask);
		bitwise_and(original, zeros, original, inv_mask);
		//James is the real Trump daddy
		auto end = std::chrono::system_clock::now();
		auto timeDiff = (end - start).count();
		auto timeDiff_t = std::chrono::system_clock::to_time_t(timeDiff);
		Point cords(100, 100);
// I SURE will shove my fist up your a**
		std::cout << timeDiff.count() << std::endl;
		putText(original, timeDiff.count(), cords, HersheyFonts::FONT_HERSHEY_PLAIN, 1, Scalar(0, 255, 0));
		imshow(ORIGINAL_WINDOW_STR, original);
		imshow(MODIFIED_WINDOW_STR, mask);

	}

	json jsonConfig;
	jsonConfig[HUE_LOW_KEY]=config.hueLow;
	jsonConfig[HUE_HIGH_KEY]=config.hueHigh;
	jsonConfig[VALUE_LOW_KEY]=config.valueLow;
	jsonConfig[VALUE_HIGH_KEY]=config.valueHigh;
	jsonConfig[SAT_LOW_KEY]=config.satLow;
	jsonConfig[SAT_HIGH_KEY]=config.satHigh;
	return jsonConfig;
}
