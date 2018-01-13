
#pragma once

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <string>
#include <type_traits>
#include <sstream>

/*
 * The JetsonVideoMode describes what the resolution and frames per second that the camera
 * captures pictures.
 *
 * Lemme smash \(*.*\)   <--  <--
 *
 * We have the width by height by frame rate per one second. (k{width}x{height}x{framerate per 1 second})
 *                                ^
 *                                 \
 */
enum class JetsonVideoMode {
//                                  ^
//                                  |
	k1280x720x30=0,
	k1280x720x60=1,
	k1280x720x120=2,
//								     ^
//                                   |
	k1920x1080x30=3,
	k1920x1080x60=4,

	k2592x1944x30=5,
	k2592x1458x30=6
	//                                ^
	//							      |
};

struct VideoMode {
	int width;
	int height;
	int fps;
};
/**
 * A wrapper to provide an easier interface to access the onboard camera of the Jetson.
 * This class provides methods for manipulating the default camera settings.
 *                                    ^
 *									  |
 * BECKY BECKY BEEEECCCKKKKKYYYYY ->
 */
class JetsonVideoCapture {
public:
	/**
	 *
	 */
	JetsonVideoCapture(JetsonVideoMode mode, const std::string& configLocation);
	JetsonVideoCapture(JetsonVideoMode mode);
	void set_autoexposure(bool on);
	void set_exposure(double exp);
	void set_white_balance(double wb);
	void set_brightness(double bright);
	void set_contrast(double con);

	cv::VideoCapture& get_video_capture();
	cv::VideoCapture& operator>>(cv::Mat& mat);
	cv::VideoCapture& operator>>(cv::UMat& mat);

private:
	cv::VideoCapture cap;
};
/*
 * opens the video capture for the onboard csi camera on the Jetson with the JetsonVideoMode specified.
 */

void open_jetson_video_capture(cv::VideoCapture& videocapture, JetsonVideoMode jetsonvideocapture);


/*
 * Overloads the stream output operator to pretty print the video mode structure.
 */
std::ostream& operator<<(std::ostream& s, const VideoMode& mode);

/*
 * Parse the Jetson video mode and convert it into a video mode
 * with a width, height, and fps.
 */
VideoMode convert_JetsonVideoMode(JetsonVideoMode mode);
