

#include <opencv2/opencv.hpp>  
#include "stdio.h"
#define P_WIDTH 640
#define P_HIGHT 480
#define PIC_LEN 640*480
#define FILE_NAME ".\\material\\1.yuv"

 
using namespace cv;

void on_mouse(int event, int x, int y, int flags, void *param);
void mark_save_pic(char *buf, int x, int y, int width, int hight);
char *rdpic(char* buf, unsigned int pic_len);

int main1111()
{
	IplImage *sour = cvCreateImage(Size(640, 480), IPL_DEPTH_8U, 1);

	char sdata[PIC_LEN * 2];
	unsigned char pdata[PIC_LEN];

	int i;

	FILE * fd = NULL;

	fd = fopen(FILE_NAME,"r");

	if (fd == NULL)
	{
		printf("openfile error");
	}
 
	i = fread(sdata, sizeof(char), PIC_LEN * 2, fd);

	printf("file len is %d",i);

	/*��ȡ��ͼ��Ϊ YUYV 8888 ���� ��ȡ���������ݻ�ȡͼ��ĻҶ�*/
	for (i = 0; i < PIC_LEN; i++)
	{
		pdata[i] = sdata[2 * i];
	}
	/*����ͼ��*/
	sour->imageData = (char*)pdata;  
	/*��������*/
	cvNamedWindow("material");
	/*��ʾԭʼ�Ҷ�ͼ��*/
	cvShowImage("material",sour);


	/*����¼�ע��ص�����*/
	cvSetMouseCallback("material", on_mouse, pdata);

	fclose(fd);

	waitKey(0);
 
	return 0;
}


/*���ص�����*/
void on_mouse(int event, int x, int y, int flags, void *param)
{
	/*������ɿ�ʱ��Ϊѡȡ��ǰx����Ϊ���ĵ�*/
	if (event == CV_EVENT_LBUTTONUP)
	{
		printf("mouse position is(%d,%d)\r\n",x,y);

		mark_save_pic((char*)param, x, y, P_WIDTH, P_HIGHT);

		rdpic((char*)param, PIC_LEN);
	}
	/*���Ҽ��ɿ�ʱ�������ǰͼƬ*/
	if (event == CV_EVENT_RBUTTONUP)
	{
		rdpic((char*)param, PIC_LEN);
		
	}
}



/********************************************************
*��������ȡͼƬ ÿ����һ�ζ�ȡ��һ��ͼƬ ��ȡYUV422 ͼƬ
*		����ͼƬת��Ϊ�Ҷ�ͼƬ
*��ע��ͼƬ���ļ��� ����  x.yuyv ��ʽ ����x=(1,2,3.....)
*������buf ͼƬ������ָ��   pic_len ͼƬ���� 
*����ֵ��ͼƬ������ָ�� ����ȡͼƬʧ�ܷ��� NULL
********************************************************/
char *rdpic(char *buf,unsigned int pic_len)
{
	int i;
	/*�ӵ�һ��ͼƬ��ʼ��ȡ*/
	static unsigned int pic_id = 2;

	char fname[20];
	
	FILE* fd;

	unsigned  int rlen;

	static IplImage *sour = cvCreateImage(Size(640, 480), IPL_DEPTH_8U, 1);

	char temp[PIC_LEN * 2];

	sour->imageData = buf;
	/*���ͼƬ�ļ���*/
	sprintf(fname,".\\material\\%d.yuv",pic_id);

	/*ֻ����ʽ���ļ���*/
	fd = fopen(fname, "r");

	if (fd == NULL)
	{
		printf("open pic file error\r\n");

		cvDestroyWindow("material");

		return NULL;
	}

	/*��ȡͼƬ����*/
	rlen = fread(temp, sizeof(char), pic_len*2, fd);

	for (i = 0; i < pic_len; i++)
	{
		buf[i] = temp[2 * i];
	}

 
	cvShowImage("material", sour);
	cvMoveWindow("material",0,0);

#ifdef MYDEBUG
	printf("real len is %d\n",rlen);
#endif

	fclose(fd);

	pic_id = pic_id + 1;
	return buf;	
}

/************************************************************* 
*���������ͼƬ������λ�� ���ұ����Ӧ�Ĳü�����ͼƬ
*������ buf ����ͼƬ������  (x,y)��������ֵ 
*		ͼƬ�ߴ�Ϊ width*hight
**************************************************************/
void mark_save_pic(char *buf, int x, int y,int width,int hight)
{
#define LIN_W 5
	int i,j;
	int lin_start, lin_end;
	FILE *fd,*fs;
	static int pic_id = 1;
	char file_name[20];

	static IplImage *sour = cvCreateImage(Size(640, 480), IPL_DEPTH_8U, 1);
	sour->imageData = (char*)buf;


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

	/*������ѵ������д��һ��YUV�ļ� ����matlab ѵ��*/
	fs = fopen(".\\DATA\\test_data.yuv", "a");//׷�ӷ�ʽ���ļ� �洢ѵ�����ݽ��
	if (fs == NULL)
	{
		printf("open test_data.yuv error\n");
	}
	else
	{
		fwrite(buf, sizeof(char), PIC_LEN, fs);
	}
	fclose(fs);


	/*��ӱ��*/
	for (i = 0; i < hight - 1; i++)
	{
		for (j = lin_start; j < lin_end; j ++)
		{
			buf[i*width+j] = 0; //���Ϊ��ɫ
		}
		
	}

	
	/*����֮ǰ�Ĵ���*/
	if (pic_id > 0)
	{
		sprintf(file_name, "%d.yuv", pic_id-1);
		cvDestroyWindow(file_name);
	}

	sprintf(file_name, "%d.yuv", pic_id);
	cvShowImage(file_name, sour);
	/*�ƶ����ڵ�ָ��λ��*/
	cvMoveWindow(file_name,0,500);

	/*�洢ͼƬ�������� �洢��Ӧ������ֵ*/
	sprintf(file_name,".\\DATA\\%d_%d.yuv",pic_id,x);
	pic_id = pic_id + 1;

	/*����ͼƬ �����ļ�����ѭ ����λ��_ͼƬ���.yuv ��ʽ*/
	fd = fopen(file_name,"w");
	if (fd == NULL)
	{
		printf("save pic error\n");
	}
	else
	{
		fwrite(buf,sizeof(char),PIC_LEN,fd);
	}
	fclose(fd);




	fs = fopen(".\\DATA\\result.txt", "a+");//׷�ӷ�ʽ���ļ� �洢ѵ�����ݽ��
	if (fs == NULL)
	{
		printf("save result error\n");
	}
	else
	{
		sprintf(file_name,"%d\r\n",x);

		fwrite(file_name, sizeof(char), strlen(file_name), fs);
	}
	fclose(fs);


}


/*��ӡ������Ϣ*/
void printinf(void)
{
	printf("ѵ�������� ���ͼƬ�������,����ͼƬ�����ڸ�Ŀ¼PIC_DATA�ļ�����\n");

	printf("ͼƬ���ļ��� ����  x.yuyv ��ʽ ����x=(1,2,3.....) \n");

	printf("������Ϊ��ǵ�ǰx���꣬��������һ��ͼƬ\r\n");

	printf("����Ҽ�Ϊ������ǰͼƬ��������Ҫ���ͼƬ��ȥ��\r\n");

}
