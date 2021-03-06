#include <iostream>

#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

int main()
{
	Mat img = imread("cameraman.bmp", 0);
	int width = img.cols;
	int height = img.rows;

	
	int level = 1; // level of decomposition (restruction)
	int levelCount = 1;
	const float divisor = 2;
	Mat tmp = Mat::ones(width, height, CV_32FC1);
	Mat wavelet = Mat::ones(width, height, CV_32FC1);
	Mat imgtmp = img.clone();
	imgtmp.convertTo(imgtmp, CV_32FC1);

	// do wavelet transformation
	while(levelCount <= level)
	{
		//width /= 2;
		for(int i = 0; i < height; i++)
		{
			for(int j = 0; j < width / 2; j++)
			{
				tmp.at<float>(i, j) = (imgtmp.at<float>(i, 2 * j) + imgtmp.at<float>(i, 2 * j + 1)) / divisor;
				tmp.at<float>(i, j + width / 2) = (imgtmp.at<float>(i, 2 * j) - imgtmp.at<float>(i, 2 * j + 1)) / divisor;
			}
		}
		imshow("horizontal", tmp);
		waitKey(0);

		//width /= 2;

		//height /= 2;
		for(int i = 0; i < height / 2; i++)
		{
			for(int j = 0; j < width; j++)
			{
				wavelet.at<float>(i, j) = (tmp.at<float>(2 * i, j) + tmp.at<float>(2 * i + 1, j)) / divisor;
				wavelet.at<float>(i + height / 2, j) = (tmp.at<float>(2 * i, j) - tmp.at<float>(2 * i + 1, j)) / divisor;
			}
		}
		imshow("vertical", wavelet);
		waitKey(0);

		imgtmp = wavelet;

		width /= 2;
		height /= 2;
		levelCount++;
	}

	wavelet.convertTo(wavelet, CV_8UC1);
	imshow("wavelet", wavelet);
	waitKey(0);

	// reset the variables I will use later
	width = img.cols;
	height = img.rows;
	levelCount = 1;
	tmp = Mat::ones(width, height, CV_32FC1);
	wavelet.convertTo(wavelet, CV_32FC1);
	imgtmp = wavelet.clone();
	wavelet = Mat::ones(width, height, CV_32FC1);

	cout << "before resize: " << height << " "  << width << endl;
	height = height / pow(2, level);
	width = width / pow(2, level);
	cout << "after resize: " << height << " " << width << endl;

	// do inverse wavelet transformatin
	while(levelCount <= level)
	{
		for(int i = 0; i < height; i++)
		{
			for(int j = 0; j < width; j++)
			{
				tmp.at<float>(2 * i, j) = imgtmp.at<float>(i, j) + imgtmp.at<float>(i + height, j);
				tmp.at<float>(2 * i + 1, j) = imgtmp.at<float>(i, j) - imgtmp.at<float>(i + height, j);
			}
		}
		imshow("vertical inverse", tmp);
		waitKey(0);
		height *= 2;

		for(int i = 0; i < height; i++)
		{
			for(int j = 0; j < width; j++)
			{
				wavelet.at<float>(i, 2 * j) = tmp.at<float>(i, j) + tmp.at<float>(i, j + width);
				wavelet.at<float>(i, 2 * j + 1) = tmp.at<float>(i, j) - tmp.at<float>(i, j + width);
			}
		}
		imshow("horizontal inverse", wavelet);
		waitKey(0);
		width *= 2;

		imgtmp = wavelet;
		/*width *= 2;
		height *= 2;*/
		levelCount++;
	}	

	wavelet.convertTo(wavelet, CV_8UC1);
	imshow("reconstruct", wavelet);
	waitKey(0);

	return 0;
}

