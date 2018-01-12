#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;

int main(int argc, char** argv) {
	Mat image;
	image = imread("hello.jpg", 1);

	if (!image.data) {
		std::cout << "Failed to load the image" << std::endl;
		return -1;
	}

	namedWindow("Display Image", WINDOW_AUTOSIZE);
	imshow("Display Image", image);

	waitKey(0);
	return 0;
}
