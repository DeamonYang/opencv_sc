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

int mainaaaa ()
{
	static int num = 1;
	int parm[2];
	parm[0] = CV_IMWRITE_JPEG_QUALITY;
	parm[1] = 90;
	char filename[100] = "F:/sc_opencv/0.jpg";
	IplImage *jpg_pic = cvLoadImage(filename, CV_LOAD_IMAGE_GRAYSCALE);
	IplImage *hsv = cvCreateImage(cvGetSize(jpg_pic), jpg_pic->depth, jpg_pic->nChannels);
	IplImage *gry = cvCreateImage(cvGetSize(jpg_pic), jpg_pic->depth, jpg_pic->nChannels);
	CvMat *outputImage;

	int i, j;


	for (i = RD_STR; i < RD_STR + PIC_NUM; i++)
	{
		sprintf(filename, "F:/sc_opencv/seldata/%d.jpg", i);
		/*打开图片*/
		jpg_pic = cvLoadImage(filename, CV_LOAD_IMAGE_GRAYSCALE);
		cvShowImage("ori", jpg_pic);
 
		cvThreshold(jpg_pic, gry, 100, 255, CV_ADAPTIVE_THRESH_GAUSSIAN_C);
		cvShowImage("gry", gry);
		

		CvMemStorage* mem_storage = cvCreateMemStorage(0);
		CvSeq *first_contour = NULL, *c = NULL;
		cvFindContours(gry, mem_storage, &first_contour);

		for (int k = 0; first_contour != 0; first_contour = first_contour->h_next, k++)
		{
			double length = cvArcLength(first_contour);
			if (length < 100)
			{
				cvSeqRemove(first_contour,0);
				continue;
			}
		}



		waitKey(0);


		//cvCvtColor(jpg_pic, hsv, CV_BGR2HSV);

		//int width = hsv->width;
		//int height = hsv->height;
		//for (i = 0; i < height; i++)
		//	for (j = 0; j < width; j++)
		//	{
		//		CvScalar s_hsv = cvGet2D(hsv, i, j);//获取像素点为（j, i）点的HSV的值   
		//		/*
		//		opencv 的H范围是0~180，红色的H范围大概是(0~8)∪(160,180)
		//		S是饱和度，一般是大于一个值,S过低就是灰色（参考值S>80)，
		//		V是亮度，过低就是黑色，过高就是白色(参考值220>V>50)。
		//		*/
		//		CvScalar s;
		//		if (!(((s_hsv.val[0]>0) && (s_hsv.val[0]<8)) || (s_hsv.val[0]>120) && (s_hsv.val[0]<180)))
		//		{
		//			s.val[0] = 0;
		//			s.val[1] = 0;
		//			s.val[2] = 0;
		//			cvSet2D(hsv, i, j, s);
		//		}


		//	}
		//outputImage = cvCreateMat(hsv->height, hsv->width, CV_8UC3);
		//Mat imghsv = cvarrToMat(hsv);
		//Mat pic;
		//cvtColor(imghsv, pic, CV_HSV2BGR);

		//Mat element = getStructuringElement(MORPH_RECT, Size(10, 10));
		//morphologyEx(pic, pic, MORPH_OPEN, element);
		//morphologyEx(pic, pic, MORPH_CLOSE, element);




		//imshow("pic", pic);

		//cvNamedWindow("filter");
		//cvShowImage("filter", hsv);
		


	}
	return 0;
}


////#include <iostream>  
////#include <opencv2/opencv.hpp>  
////#include "stdio.h"
////#define P_WIDTH 640
////#define P_HIGHT 480
////#define PIC_LEN 640*480
////#define FILE_NAME ".\\material\\1.yuv"
////
////using namespace cv;
////using namespace std;
////
////#define PIC_NUM 50
////#define WIDTH 10
////
////#define STEP 8
////
////#define RD_STR 573
////
////int main()
////{
////	static int num = 1;
////	int parm[2];
////	parm[0] = CV_IMWRITE_JPEG_QUALITY;
////	parm[1] = 90;
////	char filename[100] = "F:/sc_opencv/0.jpg";
////	IplImage *jpg_pic = cvLoadImage(filename, CV_LOAD_IMAGE_ANYCOLOR);
////	IplImage *hsv = cvCreateImage(cvGetSize(jpg_pic),jpg_pic->depth,jpg_pic->nChannels);
////	CvMat *outputImage;
////
////	int i, j;
////
////
////	for (i = RD_STR; i < RD_STR + PIC_NUM; i++)
////	{
////		sprintf(filename, "F:/sc_opencv/seldata/%d.jpg", i);
////		/*打开图片*/
////		jpg_pic = cvLoadImage(filename, CV_LOAD_IMAGE_ANYCOLOR);
////		cvShowImage("ori", jpg_pic);
////
////		
////
////		cvCvtColor(jpg_pic,hsv,CV_BGR2HSV);
////
////		int width = hsv->width;
////		int height = hsv->height;
////		for (i = 0; i < height; i++)
////			for (j = 0; j < width; j++)
////			{
////				CvScalar s_hsv = cvGet2D(hsv, i, j);//获取像素点为（j, i）点的HSV的值   
////				/*
////				opencv 的H范围是0~180，红色的H范围大概是(0~8)∪(160,180)
////				S是饱和度，一般是大于一个值,S过低就是灰色（参考值S>80)，
////				V是亮度，过低就是黑色，过高就是白色(参考值220>V>50)。
////				*/
////				CvScalar s;
////				if (!(((s_hsv.val[0]>0) && (s_hsv.val[0]<8)) || (s_hsv.val[0]>120) && (s_hsv.val[0]<180)))
////				{
////					s.val[0] = 0;
////					s.val[1] = 0;
////					s.val[2] = 0;
////					cvSet2D(hsv, i, j, s);
////				}
////
////
////			}
////		outputImage = cvCreateMat(hsv->height, hsv->width, CV_8UC3);
////		Mat imghsv = cvarrToMat(hsv);
////		Mat pic;
////		cvtColor(imghsv, pic,CV_HSV2BGR);
////
////		Mat element =  getStructuringElement(MORPH_RECT,Size(10,10));
////		morphologyEx(pic, pic, MORPH_OPEN ,element);
////		morphologyEx(pic, pic, MORPH_CLOSE , element);
////
////
////		 
////
////		imshow("pic",pic);
////
////		cvNamedWindow("filter");
////		cvShowImage("filter", hsv);
////		waitKey(1);
////
////
////		//for (j = 0; j < 480 / WIDTH - STEP; j = j + STEP)
////		//{
////
////		//	cvSetImageROI(jpg_pic, CvRect(0, j * WIDTH, 640, WIDTH));
////		//	sprintf(filename, "F:/sc_opencv/resheep/%drr.jpg", num++);
////		//	cvSaveImage(filename, jpg_pic, parm);
////		//	cvShowImage("resheep", jpg_pic);
////		//	waitKey(1);
////		//}
////	}
////	return 0;
////}