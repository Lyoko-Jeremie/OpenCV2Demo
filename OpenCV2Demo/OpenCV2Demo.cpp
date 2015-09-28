
#include "stdafx.h"


// opencv 头文件
#include <opencv2\opencv.hpp>
// 声明使用cv命名空间  
// 在这里声明使用后可以省略下面的cv::
using namespace cv;	

// C++标准库头文件
#include <iostream>		// cin cout endl
#include <string>		// string
// 声明使用cv命名空间  
// 在这里声明使用后可以省略下面的std::
using namespace std;
// 在代码中没有省略命名空间是为了指出哪个函数是属于opencv的 哪个是c++的



// 下面所有的cv命名空间的函数定义及相关信息信息都可以在opencv的官方在线文档中以函数名搜索到详细说明
// 官方手册地址：http://docs.opencv.org/



// 程序运行方法：
// 显示输入文件时拖拽文件到窗口界面 回车读取文件




int main()
{
	string filepath;				//	声明一个字符串变量
	std::cout << "输入文件：" << std::endl;		// 输出提示“输入文件：”并换行刷新
	std::cin >> filepath;			// 读取用户输入并保存到变量filepath中

	// 打开filepath中的文件并保存到image
	// 在opencv中常用Mat保存图片
	cv::Mat image = cv::imread(filepath);	

	// 检查image是不是空的  当imread读取失败时会返回一个空的Mat
	if (image.empty())
	{
		std::cout << "文件读取失败。" << std::endl;
		return -1;
	}

	// 显示图像
	// imshow(图像窗口名称,要显示的图像)
	cv::imshow("原始图像", image);
	// 等待图像窗口上的按键
	// 只有使用waitKey才能让imshow的窗口显示出内容  否则只会出现一个灰色的窗口
	cv::waitKey();
	
	// 声明一个Mat类型的变量iamgeINV 用来保存图像
	cv::Mat iamgeINV;
	// 按bit对矩阵求反（反转图像）
	// bitwise_not(输入图像,输出图像)
	// 将image反转后保存到iamgeINV中
	cv::bitwise_not(image, iamgeINV);
	cv::imshow("翻转的原始图像", iamgeINV);
	cv::waitKey();

	cv::Mat imageGray;	// 创建一个准备用来保存灰度的image的Mat（黑白（灰度）和彩色图像使用同样的类型Mat）
	// 检查image图像是不是三通道的
	// 黑白图象是单通道的  彩色图像一般是三通道（RGB（红绿蓝）） 有时四通道（ARGB（A代表alpha））
	if ( 1 == image.channels() )
	{
		std::cout << "图像是黑白的。" << std::endl;
		imageGray = image.clone();	// 将image克隆一份保存到imageGray中
	}
	else
	{
		std::cout << "图像是彩色的。" << std::endl;
		// 转换彩色image图像到黑白imageGray图象
		// cvtColor(输入图像,输出图像,转换模式)
		// CV_BGR2GRAY 表示从BGR转换到GRAY（灰度）
		// 注意 opencv默认的彩色图像存储顺序是BGR（蓝绿红）
		cv::cvtColor(image, imageGray, CV_BGR2GRAY);
		cv::imshow("灰度化的黑白图像", imageGray);
		cv::waitKey();
	}

	// 将灰度图像反转的第二个方法（黑变白白变黑）
	// 255 - imageGray  代表对imageGray的每一个像素都进行 255-像素值 的操作
	// 将imageGray的每一个像素用255减过后的结果原样保存到imageGrayINV中
	cv::Mat imageGrayINV = 255 - imageGray;
	cv::imshow("翻转的灰度图像", imageGrayINV);
	cv::waitKey();
	// 在C++中的opencv可以使用C++重载操作符的特性  使加减乘除等操作符带上特别的含义
	// 比如 将图像的像素从0-255转换到0-1可以直接 Mat/255

	cv::Mat imageThreshold;
	// 将imageGray以185为阈值（门限）二值化为0和255
	// threshold(输入图像,输出图像,阈值,处理后的最大值,处理函数)
	cv::threshold(imageGray, imageThreshold, 185, 255, THRESH_BINARY);
	cv::imshow("二值化的黑白图像", imageThreshold);
	cv::waitKey();

	imageThreshold = 255 - imageThreshold;
	cv::imshow("翻转的二值化图像", imageThreshold);
	cv::waitKey();

	cv::Mat imageAdaptiveThreshold;
	// 将imageGray自适应二值化后保存到imageAdaptiveThreshold
	// adaptiveThreshold(输入图像,输出图像,处理后的最大值,均衡算法,处理函数,核大小（同时参与计算的像素区域大小）,均衡算法的参数)
	cv::adaptiveThreshold(imageGray, imageAdaptiveThreshold, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 5, 2);
	cv::imshow("自适应二值化的黑白图像", imageAdaptiveThreshold);
	cv::waitKey();

	imageAdaptiveThreshold = 255 - imageAdaptiveThreshold;
	cv::imshow("翻转的自适应二值化图像", imageAdaptiveThreshold);
	cv::waitKey();



    return 0;
}

