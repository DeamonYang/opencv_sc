/*************************************************************************************************
*功能描述采集摄像头视频并存储为AVI视频
*分辨率为 640*480
*************************************************************************************************/

#include <iostream>  
#include <opencv2/highgui/highgui.hpp>  
#include <opencv2/core/core.hpp>  

using namespace std;
using namespace cv;
VideoCapture cam;
int maincap()
{
	IplImage * img;
	cam.open(0);
	cam.set(CV_CAP_PROP_FRAME_WIDTH, 640);
	cam.set(CV_CAP_PROP_FRAME_HEIGHT, 480);
	if (!cam.isOpened())
	{
		cout << "Open filed!!\n";
		return 0;
	}
	Mat src;
	VideoWriter vid;
	vid.open("cam.avi", CV_FOURCC('X', 'V', 'I', 'D'), 25, Size(640, 480), true);




	while (true)
	{
		cam >> src;
		img = cvCloneImage(&(IplImage)src);

		cvShowImage("cpic",img);

		imshow("test", src);
		if (src.empty())
		{
			break;
		}
		vid << src;
		waitKey(3);
	}
}