/*
 * test.cpp
 */

#include <stdio.h>
#include "shapematch.h"

using namespace std;

int main(int argc, char** argv) {	
  Mat src1 = imread(argv[1], 1);  // source 1
  Mat src2 = imread(argv[2], 1);  // source 2
  Mat src3 = imread(argv[3], 1);  // result

  namedWindow("src1", CV_WINDOW_AUTOSIZE);
  imshow("src1", src1);

  namedWindow("src2", CV_WINDOW_AUTOSIZE);
  imshow("src2", src2);
	
  Mat result = ShapeMatching(src1, src2, src3);
	
  namedWindow("result", CV_WINDOW_AUTOSIZE);
  imshow("result", result);

  waitKey(0);
  return(0);
}
