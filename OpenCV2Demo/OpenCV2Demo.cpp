
#include "stdafx.h"


#include <opencv2\opencv.hpp>
using namespace cv;

#include <iostream>
#include <string>
using namespace std;


int main()
{
	string filepath;
	std::cout << "输入文件：" << std::endl;
	std::cin >> filepath;
	cv::Mat image = cv::imread(filepath);
	if (image.empty())
	{
		std::cout << "文件读取失败。" << std::endl;
		return -1;
	}
	cv::imshow("原始图像", image);
	cv::waitKey();
	if ( 3 != image.channels() )
	{
		std::cout << "图像是黑白的。" << std::endl;
	}
	else
	{
		std::cout << "图像是彩色的。" << std::endl;
		cv::cvtColor(image, image, CV_BGR2GRAY);
		cv::imshow("灰度化的黑白图像", image);
		cv::waitKey();
	}
	cv::adaptiveThreshold(image, image, 150, THRESH_BINARY, 1, 5, 2);
	cv::imshow("自适应二值化的黑白图像", image);
	cv::waitKey();

	image = 255 - image;
	cv::imshow("翻转的二值化图像", image);
	cv::waitKey();





    return 0;
}

