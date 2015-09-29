
#include "stdafx.h"


// opencv ͷ�ļ�
#include <opencv2\opencv.hpp>
// ����ʹ��cv�����ռ�  
// ����������ʹ�ú����ʡ�������cv::
using namespace cv;	

// C++��׼��ͷ�ļ�
#include <iostream>		// cin cout endl
#include <string>		// string
// ����ʹ��cv�����ռ�  
// ����������ʹ�ú����ʡ�������std::
using namespace std;
// �ڴ�����û��ʡ�������ռ���Ϊ��ָ���ĸ�����������opencv�� �ĸ���c++��



// �������е�cv�����ռ�ĺ������弰�����Ϣ��Ϣ��������opencv�Ĺٷ������ĵ����Ժ�������������ϸ˵��
// �ٷ��ֲ��ַ��http://docs.opencv.org/



// �������з�����
// ��ʾ�����ļ�ʱ��ק�ļ������ڽ��� �س���ȡ�ļ�




int main()
{
	string filepath;				//	����һ���ַ�������
	std::cout << "�����ļ���" << std::endl;		// �����ʾ�������ļ�����������ˢ��
	std::cin >> filepath;			// ��ȡ�û����벢���浽����filepath��

	// ��filepath�е��ļ������浽image
	// ��opencv�г���Mat����ͼƬ
	cv::Mat image = cv::imread(filepath);	

	// ���image�ǲ��ǿյ�  ��imread��ȡʧ��ʱ�᷵��һ���յ�Mat
	if (image.empty())
	{
		std::cout << "�ļ���ȡʧ�ܡ�" << std::endl;
		return -1;
	}

	// ��ʾͼ��
	// imshow(ͼ�񴰿�����,Ҫ��ʾ��ͼ��)
	cv::imshow("ԭʼͼ��", image);
	// �ȴ�ͼ�񴰿��ϵİ���
	// ֻ��ʹ��waitKey������imshow�Ĵ�����ʾ������  ����ֻ�����һ����ɫ�Ĵ���
	cv::waitKey();
	
	// ����һ��Mat���͵ı���iamgeINV ��������ͼ��
	cv::Mat iamgeINV;
	// ��bit�Ծ����󷴣���תͼ�񣩣����ࣩ
	// bitwise_not(����ͼ��,���ͼ��)
	// ��image��ת�󱣴浽iamgeINV��
	cv::bitwise_not(image, iamgeINV);
	cv::imshow("��ת��ԭʼͼ��", iamgeINV);
	cv::waitKey();

	cv::Mat imageGray;	// ����һ��׼����������Ҷȵ�image��Mat���ڰף��Ҷȣ��Ͳ�ɫͼ��ʹ��ͬ��������Mat��
	// ���imageͼ���ǲ��ǵ�ͨ����
	// �ڰ�ͼ���ǵ�ͨ����  ��ɫͼ��һ������ͨ����RGB������������ ��ʱ��ͨ����ARGB��A����alpha����
	// Mat.channels() �᷵��Mat��ͨ����
	if ( 1 == image.channels() )
	{
		std::cout << "ͼ���Ǻڰ׵ġ�" << std::endl;
		imageGray = image.clone();	// ��image��¡һ�ݱ��浽imageGray��
	}
	else
	{
		std::cout << "ͼ���ǲ�ɫ�ġ�" << std::endl;
		// ת����ɫimageͼ�񵽺ڰ�imageGrayͼ��
		// cvtColor(����ͼ��,���ͼ��,ת��ģʽ)
		// CV_BGR2GRAY ��ʾ��BGRת����GRAY���Ҷȣ�
		// ע�� opencvĬ�ϵĲ�ɫͼ��洢˳����BGR�����̺죩
		cv::cvtColor(image, imageGray, CV_BGR2GRAY);
		cv::imshow("�ҶȻ��ĺڰ�ͼ��", imageGray);
		cv::waitKey();
	}

	// ���Ҷ�ͼ��ת�ĵڶ����������ڱ�װױ�ڣ�
	// 255 - imageGray  �����imageGray��ÿһ�����ض����� 255-����ֵ �Ĳ���
	// ��imageGray��ÿһ��������255������Ľ��ԭ�����浽imageGrayINV��
	cv::Mat imageGrayINV = 255 - imageGray;
	cv::imshow("��ת�ĻҶ�ͼ��", imageGrayINV);
	cv::waitKey();
	// ��C++�е�opencv����ʹ��C++���ز�����������  ʹ�Ӽ��˳��Ȳ����������ر�ĺ���
	// ���� ��ͼ������ش�0-255ת����0-1����ֱ�� Mat/255

	cv::Mat imageThreshold;
	// ��imageGray��185Ϊ��ֵ�����ޣ���ֵ��Ϊ0��255
	// threshold(����ͼ��,���ͼ��,��ֵ,���������ֵ,������)
	cv::threshold(imageGray, imageThreshold, 185, 255, THRESH_BINARY);
	cv::imshow("��ֵ���ĺڰ�ͼ��", imageThreshold);
	cv::waitKey();

	imageThreshold = 255 - imageThreshold;
	cv::imshow("��ת�Ķ�ֵ��ͼ��", imageThreshold);
	cv::waitKey();


	cv::Mat imageEqualizeHist;
	cv::equalizeHist(imageGray, imageEqualizeHist);
	cv::imshow("ֱ��ͼ���⻯�ĻҶ�ͼ��", imageEqualizeHist);
	cv::waitKey();



	cv::Mat imageAdaptiveThreshold;
	// ��imageGray����Ӧ��ֵ���󱣴浽imageAdaptiveThreshold
	// adaptiveThreshold(����ͼ��,���ͼ��,���������ֵ,�����㷨,������,�˴�С��ͬʱ�����������������С��,�����㷨�Ĳ���)
	cv::adaptiveThreshold(imageGray, imageAdaptiveThreshold, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 5, 2);
	cv::imshow("����Ӧ��ֵ���ĺڰ�ͼ��", imageAdaptiveThreshold);
	cv::waitKey();

	imageAdaptiveThreshold = 255 - imageAdaptiveThreshold;
	cv::imshow("��ת������Ӧ��ֵ��ͼ��", imageAdaptiveThreshold);
	cv::waitKey();






    return 0;
}

