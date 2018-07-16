#include <opencv2/opencv.hpp>

const float divisor = 2;

void haar_2d(cv::Mat &src, int level)
{
	int levelCount = 1;
	int width = src.cols;
	int height = src.rows;

	cv::Mat tmp = cv::Mat::ones(width, height, CV_32FC1);
	cv::Mat wavelet = cv::Mat::ones(width, height, CV_32FC1);
	cv::Mat imgtmp = src.clone();
	imgtmp.convertTo(imgtmp, CV_32FC1);

	// do wavelet transform
	while(levelCount <= level)
	{
		// first do horizontal direction transformation
		for(int i = 0; i < height; i++)
                {
                        for(int j = 0; j < width / 2; j++)
                        {
                                tmp.at<float>(i, j) = (imgtmp.at<float>(i, 2 * j) + imgtmp.at<float>(i, 2 * j + 1)) / divisor;
                                tmp.at<float>(i, j + width / 2) = (imgtmp.at<float>(i, 2 * j) - imgtmp.at<float>(i, 2 * j + 1)) / divisor;
                        }
                }
                imshow("horizontal", tmp);
                cv::waitKey(0);

		// then do vertical direction transformation
		for(int i = 0; i < height / 2; i++)
                {   
                        for(int j = 0; j < width; j++)
                        {   
                                wavelet.at<float>(i, j) = (tmp.at<float>(2 * i, j) + tmp.at<float>(2 * i + 1, j)) / divisor;
                                wavelet.at<float>(i + height / 2, j) = (tmp.at<float>(2 * i, j) - tmp.at<float>(2 * i + 1, j)) / divisor;
                        }   
                }   
                imshow("vertical", wavelet);
                cv::waitKey(0);

		imgtmp = wavelet;

                width /= 2;
                height /= 2;
                levelCount++;
	}

	wavelet.convertTo(wavelet, CV_8UC1);
        imshow("wavelet", wavelet);
        cv::waitKey(0);

	src = wavelet;
}
void haar_2d_inverse(cv::Mat &src, int level)
{

	int levelCount = 1;
	int width = src.cols;
	int height = src.rows;

	cv::Mat tmp = cv::Mat::ones(width, height, CV_32FC1);
	cv::Mat wavelet = cv::Mat::ones(width, height, CV_32FC1);
	cv::Mat imgtmp = src.clone();
	imgtmp.convertTo(imgtmp, CV_32FC1);

	//cout << "before resize: " << height << " "  << width << endl;
        height = height / pow(2, level);
        width = width / pow(2, level);
        //cout << "after resize: " << height << " " << width << endl;

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
                cv::waitKey(0);
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
                cv::waitKey(0);
                width *= 2;

                imgtmp = wavelet;
                /*width *= 2;
                height *= 2;*/
                levelCount++;
        }

        wavelet.convertTo(wavelet, CV_8UC1);
        imshow("reconstruct", wavelet);
        cv::waitKey(0);

	src = wavelet;
}

