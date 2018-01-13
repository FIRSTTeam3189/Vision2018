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
#include "json.hpp"
#include "VisionConfigurator.h"

using namespace cv;
using json = nlohmann::json;

int threshold_value = 150;
int threshold_type = 2;
int max_BINARY_value = 255;
//Oh Yes daddy i like that code you have here
int const max_type = 4;
int const max_value = 255;
void Threshold_Demo( int, void* );
const char* trackbar_type = "Type: \n 0: Binary \n 1: Binary Inverted \n 2: Truncate \n 3: To Zero \n 4: To Zero Inverted";
const char* trackbar_value = "Value";

int main(int argc, char** argv) {
	VideoCapture cap;
	open_jetson_video_capture(cap, JetsonVideoMode::k1280x720x30);
	cap.set(CV_CAP_PROP_AUTO_EXPOSURE, 0);


	json config = gen_config(cap);


	return 0;

}

void Threshold_Demo(int newValue, void*) {
	std::cout << "Changed threshold value to: " << newValue << std::endl;
}
