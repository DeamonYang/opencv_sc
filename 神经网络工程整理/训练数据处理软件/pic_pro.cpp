/*******************************************************************************
*描述：	标记图像中的红色线的位置，将位置保存在test_data_res.txt ,
*		将所有的图片数据写入一个文件 test_data.yuv
*注意：	运行以后鼠标左键为跳过当前图片，图片数据不会被写入test_data.yuv文件
*		单击鼠标右键会标记当前光标所在位置的坐标的横坐标写入test_data_res.txt 
*		图片分辨率为640*10 保存的图片为320*5  文件格式为jpeg
********************************************************************************/

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

	/*鼠标事件注册回调函数*/
	cvSetMouseCallback("material", on_mouse, jpg_pic);

	waitKey(0);

	return 0;
}


/*鼠标回调函数*/
static void on_mouse(int event, int x, int y, int flags, void *param)
{
	/*当左键松开时候为选取当前x坐标为中心点*/
	if (event == CV_EVENT_LBUTTONUP)
	{
		printf("mouse position is(%d,%d)\r\n", x, y);

		mark_save_pic(param, x, y, P_WIDTH, P_HIGHT);

		rdpic( param, PIC_LEN);
	}
	/*当右键松开时候跳过当前图片*/
	if (event == CV_EVENT_RBUTTONUP)
	{
		rdpic( param, PIC_LEN);
	}
}



/********************************************************
*描述：读取图片 每调用一次读取下一幅图片 读取YUV422 图片
*		并将图片转化为灰度图片
*备注：图片的文件名 符合  x.yuyv 方式 其中x=(1,2,3.....)
*参数：buf 图片缓冲区指针   pic_len 图片长度
*返回值：图片缓冲区指针 若读取图片失败返回 NULL
********************************************************/
static void *rdpic(void *pic, unsigned int pic_len)
{
	int i;
	/*从第一幅图片开始读取*/
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
*描述：标记图片的中心位置 并且保存对应的裁剪区域图片
*参数： buf 输入图片的数据  (x,y)鼠标的坐标值
*		图片尺寸为 width*hight
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

	/*获取当前图片*/
	IplImage *sour = (IplImage *)buf;

	char *ppic = sour->imageData;
	


	/*根据鼠标位置适当调整标记线的长度*/
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
	 
	/*将所有训练数据写入一个YUV文件 方便matlab 训练  F:\sc_opencv\resheep\train */
	fs = fopen(".\\DATA\\test_data.yuv", "ab+");//追加方式打开文件 存储训练数据结果
	if (fs == NULL)
	{
		printf("open test_data.yuv error\n");
	}
	else
	{
		fwrite(rsz->imageData, sizeof(char), rsz->imageSize, fs);
	}
	fclose(fs);

	/*存储标记的中点*/
	char f_buf[200];
	sprintf(f_buf, "%3d ,", (int)(x*SCAL));
	fs = fopen(".\\DATA\\test_data_res.txt", "ab+");//追加方式打开文件 存储训练数据结果
	if (fs == NULL)
	{
		printf("open test_data.yuv error\n");
	}
	else
	{
		fwrite(f_buf, sizeof(char), strlen(f_buf), fs);
	}
	fclose(fs);

	/*储存jpg文件*/
	int parm[2];
	char filename[100];
	static int num = 0;
	parm[0] = CV_IMWRITE_JPEG_QUALITY;
	parm[1] = 90;
	sprintf(filename, "F:/sc_opencv/resheep/train/%d.jpg", num++);
	cvSaveImage(filename, rsz, parm);

	printf("pass pic %d",num);






	/*将图像镜像 重新储存一边*/
	mrsz = cvCreateImage(sz, sour->depth, sour->nChannels);
	cvFlip(rsz,mrsz,1);

//	cvShowImage("rsz", rsz);
//	cvShowImage("mrsz",mrsz);


	/*将所有训练数据写入一个YUV文件 方便matlab 训练  F:\sc_opencv\resheep\train */
	fs = fopen(".\\DATA\\test_data.yuv", "ab+");//追加方式打开文件 存储训练数据结果
	if (fs == NULL)
	{
		printf("open test_data.yuv error\n");
	}
	else
	{
		fwrite(mrsz->imageData, sizeof(char), mrsz->imageSize, fs);
	}
	fclose(fs);

	/*存储标记的中点*/
	sprintf(f_buf, "%3d ,", (int)(mrsz->width - x*SCAL));

	fs = fopen(".\\DATA\\test_data_res.txt", "ab+");//追加方式打开文件 存储训练数据结果
	if (fs == NULL)
	{
		printf("open test_data.yuv error\n");
	}
	else
	{
		fwrite(f_buf, sizeof(char), strlen(f_buf), fs);
	}
	fclose(fs);

	/*储存jpg文件*/
	parm[0] = CV_IMWRITE_JPEG_QUALITY;
	parm[1] = 90;
	sprintf(filename, "F:/sc_opencv/resheep/train/%d.jpg", num++);
	cvSaveImage(filename, mrsz, parm);

	printf("pass pic %d", num);


 

}


/*打印帮助信息*/
static void printinf(void)
{
	printf("训练神经网络 标记图片处理软件,输入图片放置于根目录PIC_DATA文件夹下\n");

	printf("图片的文件名 符合  x.yuyv 方式 其中x=(1,2,3.....) \n");

	printf("鼠标左键为标记当前x坐标，并进入下一副图片\r\n");

	printf("鼠标右键为跳过当前图片（不符合要求的图片略去）\r\n");

}
