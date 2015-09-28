
#include "stdafx.h"


#include <opencv2\opencv.hpp>
using namespace cv;

#include <iostream>
#include <string>
using namespace std;


int main()
{
	string filepath;
	std::cout << "�����ļ���" << std::endl;
	std::cin >> filepath;
	cv::Mat image = cv::imread(filepath);
	if (image.empty())
	{
		std::cout << "�ļ���ȡʧ�ܡ�" << std::endl;
		return -1;
	}
	cv::imshow("ԭʼͼ��", image);
	cv::waitKey();
	if ( 3 != image.channels() )
	{
		std::cout << "ͼ���Ǻڰ׵ġ�" << std::endl;
	}
	else
	{
		std::cout << "ͼ���ǲ�ɫ�ġ�" << std::endl;
		cv::cvtColor(image, image, CV_BGR2GRAY);
		cv::imshow("�ҶȻ��ĺڰ�ͼ��", image);
		cv::waitKey();
	}
	cv::adaptiveThreshold(image, image, 150, THRESH_BINARY, 1, 5, 2);
	cv::imshow("����Ӧ��ֵ���ĺڰ�ͼ��", image);
	cv::waitKey();

	image = 255 - image;
	cv::imshow("��ת�Ķ�ֵ��ͼ��", image);
	cv::waitKey();





    return 0;
}

