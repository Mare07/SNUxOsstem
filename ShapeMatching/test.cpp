/*
 * test.cpp
 */

#include <stdio.h>
#include "shapematch.h"

using namespace std;

int main(int argc, char** argv) {	
  Mat src1 = imread(argv[1], 1);  // source 1
  Mat src2 = imread(argv[2], 1);  // source 2
  Mat src3 = imread(argv[3], 1);  // original image

	Mat dst;
	flip(src1, dst, 1);
  
	namedWindow("src1", CV_WINDOW_AUTOSIZE);
  imshow("src1", dst);

  namedWindow("src2", CV_WINDOW_AUTOSIZE);
  imshow("src2", src2);
	
  Mat result = ShapeMatching(dst, src2, src3);
  // result = source 2 changed, after comparing with source 1	
  namedWindow("result", CV_WINDOW_AUTOSIZE);
  imshow("result", result);

  waitKey(0);
  return(0);
}
