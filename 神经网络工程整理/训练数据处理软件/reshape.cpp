/***************************************************************************
*将F:/sc_opencv/seldata/ 下的文件剪切
*为640*10分辨率
****************************************************************************/

#include <iostream>  
#include <opencv2/opencv.hpp>  
#include "stdio.h"
#define P_WIDTH 640
#define P_HIGHT 480
#define PIC_LEN 640*480
#define FILE_NAME ".\\material\\1.yuv"


using namespace cv;
using namespace std;

#define PIC_NUM 50
#define WIDTH 10

#define STEP 8

#define RD_STR 573

int main3333()
{
	static int num = 1;
	int parm[2];
	parm[0] = CV_IMWRITE_JPEG_QUALITY;
	parm[1] = 90;
	char filename[100] = "F:/sc_opencv/0.jpg";
	IplImage *jpg_pic = cvLoadImage(filename, CV_LOAD_IMAGE_ANYCOLOR);

	int i, j;    


	for (i = RD_STR; i < RD_STR + PIC_NUM; i++)
	{
		sprintf(filename,"F:/sc_opencv/seldata/%d.jpg",i);
		/*打开图片*/
		jpg_pic = cvLoadImage(filename, CV_LOAD_IMAGE_ANYCOLOR);
		cvShowImage("ori",jpg_pic);
		for (j = 0; j < 480 / WIDTH - STEP; j = j + STEP)
		{
			/*设置显示区域*/
			cvSetImageROI(jpg_pic, CvRect(0, j * WIDTH, 640, WIDTH));
			sprintf(filename, "F:/sc_opencv/resheep/%drr.jpg", num++);
			cvSaveImage(filename, jpg_pic, parm);
			cvShowImage("resheep",jpg_pic);
			waitKey(1);
		}
	}
	return 0;
}
