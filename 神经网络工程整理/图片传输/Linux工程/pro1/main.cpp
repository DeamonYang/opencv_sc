#include<iostream>  
#include "opencv2/opencv.hpp"
#include "udp.h"
#include "stdio.h"


using namespace cv;
using namespace std;

int send_pic_client()
 {
        char testbuf[50] = "Hello pp";
        VideoCapture capture(0);
        Point center = Point(300, 300);
        Mat tempic;
        Mat channels[3];
		vector<uchar> buf;
		vector<int> parm(2) ;
        IplImage *pimg;
        IplImage cimg;
		int buf_len;
        udp_init();

        while (1)
        {

                Mat frame;
                capture >> frame;
		imshow("pic",frame);				
				parm[0] = CV_IMWRITE_JPEG_QUALITY;
				parm[1] = 80;
				imencode(".jpg", frame, buf, parm);

//              pimg = &IplImage(frame);

                cimg = IplImage(frame);

                pimg = &cimg;

//              cvShowImage("pimg",pimg);

                #define DATA_LEN 50*1024
                char testdate[DATA_LEN];
				buf_len = buf.size();
                for(long i = 0;i < buf_len;i ++)
                        testdate[i] =  buf[i];
				
//                udp_send(buf,buf.size());
              udp_send(testdate,buf_len );

                printf("%d",buf_len);

                printf("send ok\r\n");

                waitKey(50);
        }

        dup_exit();

 
        waitKey(120000);

}



int main(void)
{
        cout << "pic send client\r\n";

        send_pic_client();

}
