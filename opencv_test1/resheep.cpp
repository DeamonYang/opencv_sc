
#include <iostream>  
#include <opencv2/opencv.hpp>  
#include "stdio.h"
#define P_WIDTH 640
#define P_HIGHT 480
#define PIC_LEN 640*480
#define FILE_NAME ".\\material\\1.yuv"


using namespace cv;
using namespace std;

#define PIC_NUM 10
#define WIDTH 20

int main()
{
	static int num = 1;
	int parm[2];
	parm[0] = CV_IMWRITE_JPEG_QUALITY;
	parm[1] = 90;
	char filename[100] = "F:/sc_opencv/0.jpg";
	IplImage *jpg_pic = cvLoadImage(filename, CV_LOAD_IMAGE_ANYCOLOR);

	int i, j;    


	for (i = 0; i < PIC_NUM; i++)
	{
		sprintf(filename,"F:/sc_opencv/%d.jpg",i);
		/*��ͼƬ*/
		jpg_pic = cvLoadImage(filename, CV_LOAD_IMAGE_ANYCOLOR);
		cvShowImage("ori",jpg_pic);
		for (j = 0; j < 480 / WIDTH; j++)
		{
			cvSetImageROI(jpg_pic, CvRect(0, j * WIDTH, 640, WIDTH));
			sprintf(filename, "F:/sc_opencv/resheep/%drr.jpg", num++);
			cvSaveImage(filename, jpg_pic, parm);
			cvShowImage("resheep",jpg_pic);
			waitKey(20);
		}
	}
	return 0;
}
