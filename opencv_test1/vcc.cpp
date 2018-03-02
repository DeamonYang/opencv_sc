/////*************************************************************************************************
////*功能描述采集摄像头视频并存储为AVI视频
////*分辨率为 640*480
////*************************************************************************************************/
////
////#include <iostream>  
////#include<opencv2/opencv.hpp>  
////#include "pic.h"
////
////
////using namespace std;
////using namespace cv;
////
////#define BUF_LEN 640*480*3
////
////#define PIC_LEN 1024*15
////
////
////int main ()
////{
////	IplImage temp;
////	IplImage * img;
//////	VideoCapture capture(0);
////	Mat src;
////	Mat data;
////	vector<uchar> buf;
////	char rvbuf(PIC_LEN);
////	vector<int> parm(2) ;
////	char filename[20];
////
////	int i = 1;
////	//capture.set(CV_CAP_PROP_FRAME_WIDTH,320);
////	//capture.set(CV_CAP_PROP_FRAME_HEIGHT, 240);
////
////	
////
////	while (i)
////	{
//////		capture >> src;
////
////		parm[0] = CV_IMWRITE_JPEG_QUALITY;
////		parm[1] = 80;
//////		imencode(".jpg", src, buf, parm);
////		printf("%d", (int)buf.size());
////
////		//sprintf(filename, "%d.jpg", i++);
////
////		//imwrite(filename, src, parm);
////	 
////
////		cout << buf.size()<<endl;
////
////		//vector<uchar> pic(buf.size());
////
////		//for (i = 0; i < buf.size(); i++)
////		//{
////		//	pic[i] = buf[i];
////		//}
////
////		vector<uchar> pic(9811);
////	 
////
////		for (i = 0; i < 9811; i++)
////		{
////			pic[i] = my_pic[i];
////		}
////
////		data = imdecode(pic, CV_LOAD_IMAGE_COLOR);
////
////		imshow("decode",data);
////		
////// 		cvtColor(src, data, CV_BGR2YUV_I420);
////
////		temp = (IplImage)src;
////
////
////
////		img = cvCloneImage(&temp);
////
////		//cvShowImage("cpic",img);
////
////		//imshow("test", src);
//// 
////		waitKey(3);
////	}
////
////	return 0;
////}









/*************************************************************************************************
*功能描述采集摄像头视频并存储为AVI视频
*分辨率为 640*480
*************************************************************************************************/

#include <iostream>  
#include<opencv2/opencv.hpp>  
#include "pic.h"


using namespace std;
using namespace cv;

#define BUF_LEN 640*480*3

#define PIC_LEN 1024*15


int mainvvvvv()
{
	IplImage temp;
	IplImage * img;
	//	VideoCapture capture(0);
	Mat src;
	Mat data;
	vector<uchar> buf;
	char rvbuf(PIC_LEN);
	//vector<int> parm(2);
	//char filename[20];

	int i = 1;
	//capture.set(CV_CAP_PROP_FRAME_WIDTH,320);
	//capture.set(CV_CAP_PROP_FRAME_HEIGHT, 240);



	while (i)
	{
		//		capture >> src;

		//parm[0] = CV_IMWRITE_JPEG_QUALITY;
		//parm[1] = 80;
		//		imencode(".jpg", src, buf, parm);
		printf("%d", (int)buf.size());

		//sprintf(filename, "%d.jpg", i++);

		//imwrite(filename, src, parm);


		cout << buf.size() << endl;

		//vector<uchar> pic(buf.size());

		//for (i = 0; i < buf.size(); i++)
		//{
		//	pic[i] = buf[i];
		//}

		vector<uchar> pic(9811);


		for (i = 0; i < 9811; i++)
		{
			pic[i] = my_pic[i];
		}

		data = imdecode(pic, CV_LOAD_IMAGE_COLOR);

		imshow("decode", data);

 

		waitKey(3);
	}

	return 0;
}