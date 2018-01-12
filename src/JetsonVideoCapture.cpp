/*
 * JetsonVideoCapture.cpp
 *
 *  Created on: Jan 12, 2018
 *      Author: nvidia
 */
#include "JetsonVideoCapture.h"

/*
 * Converts JestsonVideoMode into a string that can be used as a source
 * of the onboard Jetson camera for opencv video capture class
 *
 * @param mode: The jetson video mode to convert into a standard VideoMode struct
 * @return: The string to use as the source for the openCV VideoCapture class
 */
std::string _get_jetson_csi_cam_string(JetsonVideoMode mode){
	auto videoMode = convert_JetsonVideoMode(mode);

	//Constructing the string for the Jetson onboard csi cam
	//Make the Jetson onboard hardware handle the bayer conversion and output it as a bgr format stream
	std::stringstream ss;
	ss<<"nvcamerasrc ! video/x-raw(memory:NVMM), width=(int)"<<videoMode.width;
	ss<<", height=(int)"<< videoMode.height;
	ss<<",format=(string)I420, framerate=(fraction)"<<videoMode.fps;
	ss<<"/1 ! nvvidconv flip-method=0 ! video/x-raw, format=(string)BGRx ! videoconvert ! video/x-raw, format=(string)BGR ! appsink";

	return ss.str();
}

void open_jetson_video_capture(cv::VideoCapture& videocapture, JetsonVideoMode jetsonvideocapture){
	auto source = _get_jetson_csi_cam_string(jetsonvideocapture);
	videocapture.open(source);
}


std::ostream& operator<<(std::ostream& s, const VideoMode& mode)  {
	s << "width: "<< mode.width << " height: " << mode.height << " FPS: " << mode.fps << std::endl;
	return s;
}

 VideoMode convert_JetsonVideoMode(JetsonVideoMode mode){
	VideoMode videoMode{0,0,0};
	//Parses the video mode for the resolution.
	switch(mode){
	case JetsonVideoMode::k1280x720x30:
	case JetsonVideoMode::k1280x720x60:
	case JetsonVideoMode::k1280x720x120:
		videoMode.width = 1280;
		videoMode.height = 720;
		break;
	case JetsonVideoMode::k1920x1080x30:
	case JetsonVideoMode::k1920x1080x60:
		videoMode.width = 1920;
		videoMode.height = 1080;
		break;
	case JetsonVideoMode::k2592x1944x30:
		videoMode.width = 2592;
		videoMode.height = 1944;
		break;
	case JetsonVideoMode::k2592x1458x30:
		videoMode.width = 2592;
		videoMode.height = 1458;
		break;
	default :
		std::cout<<"unknown video mode, defaulting to 1280x720";
		videoMode.width = 1280;
		videoMode.height = 720;
	}

	/*
	 * find out the frame rate of the Jetson video mode.
	 *
	 */
	switch(mode) {
	case JetsonVideoMode::k1280x720x120:
		videoMode.fps = 120;
		break;
	case JetsonVideoMode::k1280x720x30:
	case JetsonVideoMode::k1920x1080x30:
	case JetsonVideoMode::k2592x1458x30:
	case JetsonVideoMode::k2592x1944x30:
		videoMode.fps = 30;
		break;
	case JetsonVideoMode::k1280x720x60:
	case JetsonVideoMode::k1920x1080x60:
		videoMode.fps = 60;
		break;

	default:
		std::cout<<"unknown video mode, defaulting to 30 fps";
		videoMode.fps = 30;
	}

	return videoMode;
}

 JetsonVideoCapture::JetsonVideoCapture(JetsonVideoMode mode, const std::string& configLocation){
	 auto source = _get_jetson_csi_cam_string(mode);
	 cap = cv::VideoCapture(source);
 }

 JetsonVideoCapture::JetsonVideoCapture(JetsonVideoMode mode = JetsonVideoMode::k1280x720x30) : JetsonVideoCapture(mode, ""){

 }
