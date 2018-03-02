#include<opencv2/opencv.hpp>  
#include<iostream>  

using namespace std;
using namespace cv;

int main11(int argc, char **argv)
{
	Mat gray;
	CvMat simg;
	VideoCapture capture(0);
	namedWindow("hhh", CV_WINDOW_AUTOSIZE);
	while (true)
	{
		Mat frame;
		/*获取图像数据*/
		capture >> frame;

		

		/*将图像灰度化*/
		cvtColor(frame, gray, CV_BGR2GRAY);

		simg = gray;

//		bin = cvMat(simg.rows,simg.cols,0);
		CvMat*bin = cvCreateMat(simg.rows,simg.cols,simg.type);

		/*ADAPTIVE_THRESH_GAUSSIAN_C  ADAPTIVE_THRESH_MEAN_C */
		cvAdaptiveThreshold(&simg, bin, 255, ADAPTIVE_THRESH_GAUSSIAN_C, CV_THRESH_BINARY,7);

		

		imshow("frame", frame);

		imshow("gray", gray);

;
		cvShowImage("atbin",bin);

	/*	Mat af;

		GaussianBlur(*bin, af, Size(5, 5), 0, 0);
		imshow("af", af);*/

		cvThreshold(&simg, bin, 100, 512, CV_THRESH_BINARY);
		cvShowImage("bin", bin);



		waitKey(50);
	}
	return 0;
}