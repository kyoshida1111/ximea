#include <iostream>
#include <stdio.h>
#include <opencv2\\opencv.hpp>
#include <opencv2\\highgui\\highgui.hpp>
#include "C:\\XIMEA\\Examples\\xiApiPlusOcv\\xiApiPlusOcv.hpp"
#include <vector>

using namespace cv;
using namespace std;
int main(int argc, char* argv[])
{
	CascadeClassifier cascade;
	//cascade.load("C:\\Users\\yoshida\\source\\repos\\xiApiPlusOcv\\Hand.Cascade.1.xml");
	cascade.load("C:\\XIMEA\\Examples\\xiApiPlusOcv\\haarcascade_frontalface_alt.xml"); 
	//cascade.load("C:\\Users\\yoshida\\source\\repos\\xiApiPlusOcv\\haarcascade_frontalface_alt.xml");
	vector<Rect> faces;

	try
	{
		// Sample for XIMEA OpenCV
		xiAPIplusCameraOcv cam;

		// Retrieving a handle to the camera device
		printf("Opening first camera...\n");
		cam.OpenFirst();
		
		// Set exposure
		cam.SetExposureTime(10000); //10000 us = 10 ms
		// Note: The default parameters of each camera might be different in different API versions
		
		printf("Starting acquisition...\n");
		cam.StartAcquisition();
		
		printf("First pixel value \n");
		XI_IMG_FORMAT format = cam.GetImageDataFormat();
		//#define EXPECTED_IMAGES 40
		//for (int images=0;images < EXPECTED_IMAGES;images++)
		for (;;)
		{
			Mat cv_mat_image = cam.GetNextImageOcvMat();
			if (format == XI_RAW16 || format == XI_MONO16) 
				normalize(cv_mat_image, cv_mat_image, 0, 65536, NORM_MINMAX, -1, Mat()); // 0 - 65536, 16 bit unsigned integer range
			//cascade.detectMultiScale(cv_mat_image, faces, 1.1, 3, 0, Size(20, 20));
			//for (int i = 0; i < faces.size(); i++) {
			//	rectangle(cv_mat_image, Point(faces[i].x, faces[i].y), Point(faces[i].x + faces[i].width, faces[i].y + faces[i].height), Scalar(0, 0, 255), 3, CV_AA);
			//}
			/*Mat bin_image;
			threshold(cv_mat_image, bin_image, 160, 255, THRESH_BINARY);
			cv::imshow("Image from camera",bin_image);
			*/
			cv::imshow("Image from camera", cv_mat_image);
			cvWaitKey(20);
			//printf("\t%d\n",cv_mat_image.at<unsigned char>(0,0));
		}
		
		cam.StopAcquisition();
		cam.Close();
		printf("Done\n");
		
		cvWaitKey(5000);
	}
	catch(xiAPIplus_Exception& exp)
	{
		printf("Error:\n");
		exp.PrintError();
#ifdef WIN32
		Sleep(2000);
#endif
		cvWaitKey(2000);
		return -1;
	}
	
	return 0;
}

