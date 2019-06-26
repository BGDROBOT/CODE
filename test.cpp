#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>                        //头文件引用
#include <opencv2/opencv.hpp>
#include <math.h>
using namespace cv;

using namespace std;



int main()

{
	Mat frame;
	VideoCapture capture(0);                  //调用摄像头
	//VideoCapture capture("视频文件路径");          //使用视频或图片文件 
		while (true)
	{
		capture >> frame;

		int LH = 60;
		int LS = 120;
		int LV = 245;
		                                         //蓝色红色为H 60-180 只检测 红 蓝  HSV通道       H 0-60为黄绿       60-120蓝色   120-180红色
		int HH = 180;
		int HS = 255;
		int HV = 255;

		Mat hsvimg;
		cvtColor(frame, hsvimg, COLOR_BGR2HSV);        //HSV通道 颜色检测

		vector<Mat> hsvsplit;
		split(hsvimg, hsvsplit);
		equalizeHist(hsvsplit[2], hsvsplit[2]);
		merge(hsvsplit, hsvimg);

		Mat thresholdimg;
		inRange(hsvimg, Scalar(LH, LS, LV), Scalar(HH, HS, HV), thresholdimg);       //图像二值化处理



		imshow("Camera", thresholdimg);

		int key = cvWaitKey(10);   //延时
		if (key == 27)             //按Esc键退出
		{
			break;
		}
	}
	return 0;
}
