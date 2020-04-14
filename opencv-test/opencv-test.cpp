#include <iostream>
#include <cv.h>
#include <highgui.h>
#include <cxcore.h>
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup") //去除console窗口

int main()
{
    IplImage *scr = cvLoadImage("HappyFish.jpg");

    cvNamedWindow("ShowImage", 0);

    cvShowImage("ShowImage", scr);
    cvWaitKey(0);
    cvReleaseImage(&scr);

    return 0;
}