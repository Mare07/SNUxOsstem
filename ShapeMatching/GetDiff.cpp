/*
 * GetDiff.cpp
 */

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace cv;
using namespace std;

Mat src1, src2;
Mat src_gray1, src_gray2;
int thresh = 100;
int max_thresh = 255;
RNG rng(12345);

void get_diff(void);

int main(int argc, char** argv) {	
  src1 = imread(argv[1], 1);
	src2 = imread(argv[2], 1);

	char* source_window1 = "Source1";
	namedWindow(source_window1, CV_WINDOW_AUTOSIZE);
	imshow(source_window1, src1);
	char* source_window2 = "Source2";
	namedWindow(source_window2, CV_WINDOW_AUTOSIZE);
	imshow(source_window2, src2);
	
	get_diff();
		
	waitKey(0);
	return(0);
}

void get_diff() {
	resize(src1, src1, Size(256, 256));
	resize(src2, src2, Size(256, 256));

	Mat diffImage;
	absdiff(src1, src2, diffImage);
	Mat foregroundMask = Mat::zeros(diffImage.rows, diffImage.cols, CV_8UC1);

	float threshold = 50.0f;
	float dist;

	int i, j;
	for (j = 0; j < diffImage.rows; ++j)
	  for (i = 0; i < diffImage.cols; ++i) {
		  Vec3b pix = diffImage.at<Vec3b>(j, i);

			dist = (pix[0]*pix[0] + pix[1]*pix[1] + pix[2]*pix[2]);
			dist = sqrt(dist);

			if (dist > threshold) {
			  foregroundMask.at<unsigned char>(j, i) = 255;
			}
		}

	namedWindow("Result", CV_WINDOW_AUTOSIZE);
	imshow("Result", foregroundMask);
}
