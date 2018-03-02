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
	cout << "B������ɫ\n";
	cout << "H������ɫ\n";
	cout << "W������ɫ\n";
	cout << "R������ɫ\n";
	cout << "O������ɫ\n";
	cout << "Y������ɫ\n";
	cout << "G������ɫ\n";
	cout << "L������ɫ\n";
	cout << "P������ɫ\n";
	cout << "����Ҫ��ʶ�����ɫ��Ӧ����ĸ:";
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
		cout << "�������" << endl;
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
		Mat frame;              //�洢ÿһ֡��ͼ��
		capture >> frame;       //��ȡ��ǰ֡
//		frame = img;
		Mat fhsv;
		cvtColor(frame, fhsv, COLOR_BGR2HSV);   //��ͼ��ת��ΪHSVģ��

		inRange(fhsv, Scalar(minh, mins, minv), Scalar(maxh, maxs, maxv), special);          //��Ѱ��Ҫ�������ڵ���ɫ

		//imshow("bf", special);

//		������ (ȥ��һЩ���)
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

		///*��������*/
		findContours(canny_output, contours, hierarchy, CV_RETR_EXTERNAL , CV_CHAIN_APPROX_SIMPLE, Point(0, 0));
		
		/*����������*/
		vector<Moments>mu(contours.size());
		for (int i = 0; i < contours.size(); i++)
		{
			mu[i] = moments(contours[i],false);
		}

		/*����ͼ�ε�����*/
		vector<Point2f>mc(contours.size());
		for (int i = 0; i < contours.size(); i++)
		{
			mc[i] = Point2d(mu[i].m10 / mu[i].m00, mu[i].m01 / mu[i].m00);
		}

		/*��������*/
		//�������������Ĳ���ʾ      
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
//		//��Ϊ���Ƕ�ȡ���ǲ�ɫͼ��ֱ��ͼ���⻯��Ҫ��HSV�ռ���
//		split(imgHSV, hsvSplit);
//		//equalizeHist(hsvSplit[2], hsvSplit[2]);
//		//merge(hsvSplit, imgHSV);
//		
//		
//		Mat imgThresholded;
//
//		inRange(imgHSV, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), imgThresholded); //Threshold the image
//
//		//������ (ȥ��һЩ���)
//		//Mat element = getStructuringElement(MORPH_RECT, Size(5, 5));
//		//morphologyEx(imgThresholded, imgThresholded, MORPH_OPEN, element);
//
//		//�ղ��� (����һЩ��ͨ��)
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