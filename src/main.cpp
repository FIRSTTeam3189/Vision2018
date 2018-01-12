#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <cstdlib>
#include "JetsonVideoCapture.h"

using namespace cv;

int main(int argc, char** argv) {
	VideoCapture cap;
	open_jetson_video_capture(cap, JetsonVideoMode::k1920x1080x30);
	cap.set(CV_CAP_PROP_AUTO_EXPOSURE, 0);

	namedWindow("Display Image", WINDOW_AUTOSIZE);

	std::cout<<convert_JetsonVideoMode(JetsonVideoMode::k1920x1080x60);
	while (waitKey(10) < 0) {
		Mat img;
		cap >> img;
		if (!img.data) {
			std::cout << "Failed to grab a frame." << std::endl;
			break;
		}

		imshow("Display Image", img);
	}

	return 0;
}

