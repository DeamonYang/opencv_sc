

#include <opencv2/opencv.hpp>  
#include "stdio.h"
#define P_WIDTH 640
#define P_HIGHT 480
#define PIC_LEN 640*20
#define PIC_CHN 3
#define FILE_NAME ".\\material\\1.yuv"


using namespace cv;

static void on_mouse(int event, int x, int y, int flags, void *param);
static void mark_save_pic(void *buf, int x, int y, int width, int hight);
static void *rdpic(void* buf, unsigned int pic_len);

int mainrrrr()
{
	char filename[100] =  "F:/sc_opencv/resheep/1rr.jpg";
	IplImage *jpg_pic = cvLoadImage(filename,CV_LOAD_IMAGE_ANYCOLOR );
	cvShowImage("material",jpg_pic);
	static unsigned int pic_id = 3;

	//while (1)
	//{
	//	

	//	char fname[100];

	//	sprintf(fname, "F:/sc_opencv/resheep/%drr.jpg", pic_id++);

	//	jpg_pic = cvLoadImage(fname, CV_LOAD_IMAGE_ANYCOLOR);
	//	
	//	cvShowImage("material", jpg_pic);

	//	printf("%s",fname);

	//	waitKey(10);
	//
	//}




	/*����¼�ע��ص�����*/
	cvSetMouseCallback("material", on_mouse, jpg_pic);

	waitKey(0);

	return 0;
}


/*���ص�����*/
static void on_mouse(int event, int x, int y, int flags, void *param)
{
	/*������ɿ�ʱ��Ϊѡȡ��ǰx����Ϊ���ĵ�*/
	if (event == CV_EVENT_LBUTTONUP)
	{
		printf("mouse position is(%d,%d)\r\n", x, y);

		mark_save_pic(param, x, y, P_WIDTH, P_HIGHT);

		rdpic( param, PIC_LEN);
	}
	/*���Ҽ��ɿ�ʱ��������ǰͼƬ*/
	if (event == CV_EVENT_RBUTTONUP)
	{
		rdpic( param, PIC_LEN);
	}
}



/********************************************************
*��������ȡͼƬ ÿ����һ�ζ�ȡ��һ��ͼƬ ��ȡYUV422 ͼƬ
*		����ͼƬת��Ϊ�Ҷ�ͼƬ
*��ע��ͼƬ���ļ��� ����  x.yuyv ��ʽ ����x=(1,2,3.....)
*������buf ͼƬ������ָ��   pic_len ͼƬ����
*����ֵ��ͼƬ������ָ�� ����ȡͼƬʧ�ܷ��� NULL
********************************************************/
static void *rdpic(void *pic, unsigned int pic_len)
{
	int i;
	/*�ӵ�һ��ͼƬ��ʼ��ȡ*/
	static unsigned int pic_id = 3;

	char fname[100];

	FILE* fd;

	unsigned  int rlen;

 
	cvDestroyWindow("material");

	sprintf(fname, "F:/sc_opencv/resheep/%drr.jpg",pic_id++);

	static IplImage *sour = (IplImage *)pic;
	
 
	pic = cvLoadImage(fname, CV_LOAD_IMAGE_ANYCOLOR);//CV_LOAD_IMAGE_GRAYSCALE);

	cvShowImage("material", pic);

	cvMoveWindow("material", 600, 600);

	cvSetMouseCallback("material", on_mouse, pic);

	waitKey(1);

	printf("pic id : %d\r\n",pic_id);

	return pic;
}

/*************************************************************
*���������ͼƬ������λ�� ���ұ����Ӧ�Ĳü�����ͼƬ
*������ buf ����ͼƬ������  (x,y)��������ֵ
*		ͼƬ�ߴ�Ϊ width*hight
**************************************************************/
static void mark_save_pic(void *buf, int x, int y, int width, int hight)
{
#define LIN_W 5

#define SCAL 0.5
	int i, j;
	int lin_start, lin_end;
	FILE *fd, *fs;
	static int pic_id = 1;
	char file_name[20];

	/*��ȡ��ǰͼƬ*/
	IplImage *sour = (IplImage *)buf;

	char *ppic = sour->imageData;
	


	/*�������λ���ʵ���������ߵĳ���*/
	if (x > LIN_W)
	{
		lin_start = x - LIN_W;
	}
	else
	{
		lin_start = 0;
	}

	if (x < width - LIN_W)
	{
		lin_end = x + LIN_W;
	}
	else
	{
		lin_end = width;
	}


	IplImage *rsz ;
	IplImage *mrsz;
	CvSize sz;

	sz.height = sour->height*SCAL;
	sz.width = sour->width*SCAL;

	rsz = cvCreateImage(sz,sour->depth,sour->nChannels);
	
 
	cvResize(buf, rsz, CV_INTER_CUBIC);
	 
	/*������ѵ������д��һ��YUV�ļ� ����matlab ѵ��  F:\sc_opencv\resheep\train */
	fs = fopen(".\\DATA\\test_data.yuv", "ab+");//׷�ӷ�ʽ���ļ� �洢ѵ�����ݽ��
	if (fs == NULL)
	{
		printf("open test_data.yuv error\n");
	}
	else
	{
		fwrite(rsz->imageData, sizeof(char), rsz->imageSize, fs);
	}
	fclose(fs);

	/*�洢��ǵ��е�*/
	char f_buf[200];
	sprintf(f_buf, "%3d ,", (int)(x*SCAL));
	fs = fopen(".\\DATA\\test_data_res.txt", "ab+");//׷�ӷ�ʽ���ļ� �洢ѵ�����ݽ��
	if (fs == NULL)
	{
		printf("open test_data.yuv error\n");
	}
	else
	{
		fwrite(f_buf, sizeof(char), strlen(f_buf), fs);
	}
	fclose(fs);

	/*����jpg�ļ�*/
	int parm[2];
	char filename[100];
	static int num = 0;
	parm[0] = CV_IMWRITE_JPEG_QUALITY;
	parm[1] = 90;
	sprintf(filename, "F:/sc_opencv/resheep/train/%d.jpg", num++);
	cvSaveImage(filename, rsz, parm);

	printf("pass pic %d",num);






	/*��ͼ���� ���´���һ��*/
	mrsz = cvCreateImage(sz, sour->depth, sour->nChannels);
	cvFlip(rsz,mrsz,1);

//	cvShowImage("rsz", rsz);
//	cvShowImage("mrsz",mrsz);


	/*������ѵ������д��һ��YUV�ļ� ����matlab ѵ��  F:\sc_opencv\resheep\train */
	fs = fopen(".\\DATA\\test_data.yuv", "ab+");//׷�ӷ�ʽ���ļ� �洢ѵ�����ݽ��
	if (fs == NULL)
	{
		printf("open test_data.yuv error\n");
	}
	else
	{
		fwrite(mrsz->imageData, sizeof(char), mrsz->imageSize, fs);
	}
	fclose(fs);

	/*�洢��ǵ��е�*/
	sprintf(f_buf, "%3d ,", (int)(mrsz->width - x*SCAL));

	fs = fopen(".\\DATA\\test_data_res.txt", "ab+");//׷�ӷ�ʽ���ļ� �洢ѵ�����ݽ��
	if (fs == NULL)
	{
		printf("open test_data.yuv error\n");
	}
	else
	{
		fwrite(f_buf, sizeof(char), strlen(f_buf), fs);
	}
	fclose(fs);

	/*����jpg�ļ�*/
	parm[0] = CV_IMWRITE_JPEG_QUALITY;
	parm[1] = 90;
	sprintf(filename, "F:/sc_opencv/resheep/train/%d.jpg", num++);
	cvSaveImage(filename, mrsz, parm);

	printf("pass pic %d", num);


 

}


/*��ӡ������Ϣ*/
static void printinf(void)
{
	printf("ѵ�������� ���ͼƬ�������,����ͼƬ�����ڸ�Ŀ¼PIC_DATA�ļ�����\n");

	printf("ͼƬ���ļ��� ����  x.yuyv ��ʽ ����x=(1,2,3.....) \n");

	printf("������Ϊ��ǵ�ǰx���꣬��������һ��ͼƬ\r\n");

	printf("����Ҽ�Ϊ������ǰͼƬ��������Ҫ���ͼƬ��ȥ��\r\n");

}
