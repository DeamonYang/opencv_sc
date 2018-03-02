

#include <opencv2/opencv.hpp>  
#include "stdio.h"
#define P_WIDTH 640
#define P_HIGHT 480
#define PIC_LEN 640*480
#define FILE_NAME ".\\material\\1.yuv"


using namespace cv;

static void on_mouse(int event, int x, int y, int flags, void *param);
static void mark_save_pic(char *buf, int x, int y, int width, int hight);
static char *rdpic(char* buf, unsigned int pic_len);

int mainppppppp()
{
	char filename[100] =  "F:/sc_opencv/0.jpg";
	IplImage *jpg_pic = cvLoadImage(filename,CV_LOAD_IMAGE_ANYCOLOR );
	cvShowImage("material",jpg_pic);

	//IplImage *sour = cvCreateImage(Size(640, 480), IPL_DEPTH_8U, 1);

	//char sdata[PIC_LEN * 2];
	unsigned char pdata[PIC_LEN];

	//int i;


 //
 //


	///*读取的图像为 YUYV 8888 排列 故取奇数点数据获取图像的灰度*/
	//for (i = 0; i < PIC_LEN; i++)
	//{
	//	pdata[i] = sdata[2 * i];
	//}
	///*创建图像*/
	//sour->imageData = (char*)pdata;
	///*命名窗口*/
	//cvNamedWindow("material");
	///*显示原始灰度图像*/
	//cvShowImage("material", sour);


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

		mark_save_pic((char*)param, x, y, P_WIDTH, P_HIGHT);

		rdpic((char*)param, PIC_LEN);
	}
	/*当右键松开时候调过当前图片*/
	if (event == CV_EVENT_RBUTTONUP)
	{
		rdpic((char*)param, PIC_LEN);

	}
}



/********************************************************
*描述：读取图片 每调用一次读取下一幅图片 读取YUV422 图片
*		并将图片转化为灰度图片
*备注：图片的文件名 符合  x.yuyv 方式 其中x=(1,2,3.....)
*参数：buf 图片缓冲区指针   pic_len 图片长度
*返回值：图片缓冲区指针 若读取图片失败返回 NULL
********************************************************/
static char *rdpic(char *buf, unsigned int pic_len)
{
	int i;
	/*从第一幅图片开始读取*/
	static unsigned int pic_id = 2;

	char fname[20];

	FILE* fd;

	unsigned  int rlen;

	static IplImage *sour = cvCreateImage(Size(640, 480), IPL_DEPTH_8U, 1);

	char temp[PIC_LEN * 2];

	sour->imageData = buf;
	/*获得图片文件名*/
	sprintf(fname, ".\\material\\%d.yuv", pic_id);

	/*只读方式打开文件名*/
	fd = fopen(fname, "r");

	if (fd == NULL)
	{
		printf("open pic file error\r\n");

		cvDestroyWindow("material");

		return NULL;
	}

	/*读取图片数据*/
	rlen = fread(temp, sizeof(char), pic_len * 2, fd);

	for (i = 0; i < pic_len; i++)
	{
		buf[i] = temp[2 * i];
	}


	cvShowImage("material", sour);
	cvMoveWindow("material", 0, 0);

#ifdef MYDEBUG
	printf("real len is %d\n", rlen);
#endif

	fclose(fd);

	pic_id = pic_id + 1;
	return buf;
}

/*************************************************************
*描述：标记图片的中心位置 并且保存对应的裁剪区域图片
*参数： buf 输入图片的数据  (x,y)鼠标的坐标值
*		图片尺寸为 width*hight
**************************************************************/
static void mark_save_pic(char *buf, int x, int y, int width, int hight)
{
#define LIN_W 5
	int i, j;
	int lin_start, lin_end;
	FILE *fd, *fs;
	static int pic_id = 1;
	char file_name[20];

	static IplImage *sour = cvCreateImage(Size(640, 480), IPL_DEPTH_8U, 1);
	sour->imageData = (char*)buf;


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

	/*将所有训练数据写入一个YUV文件 方便matlab 训练*/
	fs = fopen(".\\DATA\\test_data.yuv", "a");//追加方式打开文件 存储训练数据结果
	if (fs == NULL)
	{
		printf("open test_data.yuv error\n");
	}
	else
	{
		fwrite(buf, sizeof(char), PIC_LEN, fs);
	}
	fclose(fs);


	/*添加标记*/
	for (i = 0; i < hight - 1; i++)
	{
		for (j = lin_start; j < lin_end; j++)
		{
			buf[i*width + j] = 0; //标记为白色
		}

	}


	/*销毁之前的窗口*/
	if (pic_id > 0)
	{
		sprintf(file_name, "%d.yuv", pic_id - 1);
		cvDestroyWindow(file_name);
	}

	sprintf(file_name, "%d.yuv", pic_id);
	cvShowImage(file_name, sour);
	/*移动窗口到指定位置*/
	cvMoveWindow(file_name, 0, 500);

	/*存储图片并且明名 存储对应的坐标值*/
	sprintf(file_name, ".\\DATA\\%d_%d.yuv", pic_id, x);
	pic_id = pic_id + 1;

	/*保存图片 并且文件名遵循 中心位置_图片编号.yuv 格式*/
	fd = fopen(file_name, "w");
	if (fd == NULL)
	{
		printf("save pic error\n");
	}
	else
	{
		fwrite(buf, sizeof(char), PIC_LEN, fd);
	}
	fclose(fd);




	fs = fopen(".\\DATA\\result.txt", "a+");//追加方式打开文件 存储训练数据结果
	if (fs == NULL)
	{
		printf("save result error\n");
	}
	else
	{
		sprintf(file_name, "%d\r\n", x);

		fwrite(file_name, sizeof(char), strlen(file_name), fs);
	}
	fclose(fs);


}


/*打印帮助信息*/
static void printinf(void)
{
	printf("训练神经网络 标记图片处理软件,输入图片放置于根目录PIC_DATA文件夹下\n");

	printf("图片的文件名 符合  x.yuyv 方式 其中x=(1,2,3.....) \n");

	printf("鼠标左键为标记当前x坐标，并进入下一副图片\r\n");

	printf("鼠标右键为跳过当前图片（不符合要求的图片略去）\r\n");

}
