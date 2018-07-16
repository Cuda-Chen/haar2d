//#include <iostream>
#include <opencv2/opencv.hpp>

#include "dwt.hpp"

using namespace std;
using namespace cv;

int main()
{
	Mat img = imread("cameraman.bmp", 0);
	int level = 3;

	haar_2d(img, level);
	haar_2d_inverse(img, level);

	imshow("result", img);
	waitKey(0);

	return 0;
}

