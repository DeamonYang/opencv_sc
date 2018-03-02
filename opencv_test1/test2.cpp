#include <opencv2/opencv.hpp>
#include<core/core.hpp>
#include<highgui/highgui.hpp>
#include<imgproc/imgproc.hpp>

#include <iostream>

using namespace std;
using namespace cv;

int minh, maxh, mins, maxs, minv, maxv;
void helptext()
{
	cout << "B——黑色\n";
	cout << "H——灰色\n";
	cout << "W——白色\n";
	cout << "R——红色\n";
	cout << "O——橙色\n";
	cout << "Y——黄色\n";
	cout << "G——绿色\n";
	cout << "L——蓝色\n";
	cout << "P——紫色\n";
	cout << "输入要求识别的颜色对应的字母:";
}

void deal(char color)
{
	switch (color){
	case 'B':
		minh = 0;
		maxh = 180;
		mins = 0;
		maxs = 255;
		minv = 0;
		maxv = 46;
		break;
	case 'H':
		minh = 0;
		maxh = 180;
		mins = 0;
		maxs = 43;
		minv = 46;
		maxv = 220;
		break;
	case 'W':
		minh = 0;
		maxh = 180;
		mins = 0;
		maxs = 30;
		minv = 221;
		maxv = 255;
		break;
	case 'R':
		minh = 0;
		maxh = 10;
		mins = 43;
		maxs = 255;
		minv = 46;
		maxv = 255;
		break;
	case 'O':
		minh = 11;
		maxh = 25;
		mins = 43;
		maxs = 255;
		minv = 46;
		maxv = 255;
		break;
	case 'Y':
		minh = 26;
		maxh = 25;
		mins = 43;
		maxs = 255;
		minv = 46;
		maxv = 255;
		break;
	case 'G':
		minh = 35;
		maxh = 77;
		mins = 43;
		maxs = 255;
		minv = 46;
		maxv = 255;
		break;
	case 'L':
		minh = 100;
		maxh = 124;
		mins = 43;
		maxs = 255;
		minv = 46;
		maxv = 255;
		break;
	case 'P':
		minh = 125;
		maxh = 155;
		mins = 43;
		maxs = 255;
		minv = 46;
		maxv = 255;
		break;
	default:
		cout << "输入错误" << endl;
		exit(0);
	}
}

int main001()
{
	VideoCapture capture(0);
	capture.set(CAP_PROP_FRAME_HEIGHT,240);
	capture.set(CAP_PROP_FRAME_WIDTH, 320);
	Mat img = imread("bktet.png");
	Mat special;
	int tim = 1;
	helptext();

	char color;
	cin >> color;
	deal(color);
	while (1)
	{
		Mat frame;              //存储每一帧的图像
		capture >> frame;       //读取当前帧
//		frame = img;
		Mat fhsv;
		cvtColor(frame, fhsv, COLOR_BGR2HSV);   //将图像转换为HSV模型

		inRange(fhsv, Scalar(minh, mins, minv), Scalar(maxh, maxs, maxv), special);          //找寻在要求区间内的颜色

		//imshow("bf", special);

//		开操作 (去除一些噪点)
		Mat element = getStructuringElement(MORPH_RECT, Size(5, 5));
		morphologyEx(special, special, MORPH_OPEN, element);
		
		imshow("Original", frame); //show the original image
		imshow("af", special);

		//morphologyEx(special, special, MORPH_CLOSE, element);

		//imshow("con", special);


		Mat canny_output;
		int thresh = 30;
		Canny(special, canny_output, thresh, thresh * 3, 3);

//		vector<vector<Point>> contours;

		vector<Mat> contours;
		vector<Vec4i> hierarchy;
//		Mat hierarchy;

		///*查找轮廓*/
		findContours(canny_output, contours, hierarchy, CV_RETR_EXTERNAL , CV_CHAIN_APPROX_SIMPLE, Point(0, 0));
		
		/*计算轮廓矩*/
		vector<Moments>mu(contours.size());
		for (int i = 0; i < contours.size(); i++)
		{
			mu[i] = moments(contours[i],false);
		}

		/*计算图形的形心*/
		vector<Point2f>mc(contours.size());
		for (int i = 0; i < contours.size(); i++)
		{
			mc[i] = Point2d(mu[i].m10 / mu[i].m00, mu[i].m01 / mu[i].m00);
		}

		/*绘制中心*/
		//画轮廓及其质心并显示      
		Mat drawing = Mat::zeros(canny_output.size(), CV_8UC3);
		for (int i = 0; i< contours.size(); i++)
		{
			Scalar color = Scalar(255, 0, 0);
			drawContours(drawing, contours, i, color, 2, 8, hierarchy, 0, Point());
			circle(drawing, mc[i], 5, Scalar(0, 0, 255), -1, 8, 0);
			rectangle(drawing, boundingRect(contours.at(i)), cvScalar(0, 255, 0));
			char tam[100];
			sprintf(tam, "(%0.0f,%0.0f)", mc[i].x, mc[i].y);
			putText(drawing, tam, Point(mc[i].x, mc[i].y), FONT_HERSHEY_SIMPLEX, 0.4, cvScalar(255, 0, 255), 1);
		}
		namedWindow("Contours", CV_WINDOW_AUTOSIZE);
		imshow("Contours", drawing);


		if (waitKey(30) >= 0)
			break; 
	}

	while (1)
	{
		if (waitKey(30000) >= 0)break;
	}
	return 0;
}














//#include <iostream>
//#include "opencv2/highgui/highgui.hpp"
//#include "opencv2/imgproc/imgproc.hpp"
//
//using namespace cv;
//using namespace std;
//
//int main(int argc, char** argv)
//{
//	VideoCapture cap(0); //capture the video from web cam
//
//	if (!cap.isOpened())  // if not success, exit program
//	{
//		cout << "Cannot open the web cam" << endl;
//		return -1;
//	}
//
//	namedWindow("Control", CV_WINDOW_AUTOSIZE); //create a window called "Control"
//
//	int iLowH = 100;
//	int iHighH = 140;
//
//	int iLowS = 90;
//	int iHighS = 255;
//
//	int iLowV = 90;
//	int iHighV = 255;
//
//	//Create trackbars in "Control" window
//	cvCreateTrackbar("LowH", "Control", &iLowH, 179); //Hue (0 - 179)
//	cvCreateTrackbar("HighH", "Control", &iHighH, 179);
//
//	cvCreateTrackbar("LowS", "Control", &iLowS, 255); //Saturation (0 - 255)
//	cvCreateTrackbar("HighS", "Control", &iHighS, 255);
//
//	cvCreateTrackbar("LowV", "Control", &iLowV, 255); //Value (0 - 255)
//	cvCreateTrackbar("HighV", "Control", &iHighV, 255);
//
//	while (true)
//	{
//		Mat imgOriginal;
//
//
//
//		//while (1)
//		//{
//
//			bool bSuccess = cap.read(imgOriginal); // read a new frame from video
//
//			if (!bSuccess) //if not success, break loop
//			{
//				cout << "Cannot read a frame from video stream" << endl;
//				break;
//			}
//
//		//	imshow("Original", imgOriginal); //show the original image
//
//		//	waitKey(300);
//
//		//}
//
//
//
//
//		Mat imgHSV;
//		vector<Mat> hsvSplit;
//		cvtColor(imgOriginal, imgHSV, COLOR_BGR2HSV); //Convert the captured frame from BGR to HSV
//
//		//因为我们读取的是彩色图，直方图均衡化需要在HSV空间做
//		split(imgHSV, hsvSplit);
//		//equalizeHist(hsvSplit[2], hsvSplit[2]);
//		//merge(hsvSplit, imgHSV);
//		
//		
//		Mat imgThresholded;
//
//		inRange(imgHSV, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), imgThresholded); //Threshold the image
//
//		//开操作 (去除一些噪点)
//		//Mat element = getStructuringElement(MORPH_RECT, Size(5, 5));
//		//morphologyEx(imgThresholded, imgThresholded, MORPH_OPEN, element);
//
//		//闭操作 (连接一些连通域)
////		morphologyEx(imgThresholded, imgThresholded, MORPH_CLOSE, element);
//
//		imshow("Thresholded Image", imgThresholded); //show the thresholded image
//		imshow("Original", imgOriginal); //show the original image
//
//		char key = (char)waitKey(300);
//		if (key == 27)
//			break;
//	}
//
//	return 0;
//
//}