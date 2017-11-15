/*
 * shapematch.cpp
 */

#include "shapematch.h"

Mat ShapeMatching(Mat previous, Mat target, Mat original) {
  // original is original(before floodfill) image of target
	Mat diffImage;
	absdiff(previous, target, diffImage); // get difference

	int i, j;
	for (j = 0; j < diffImage.rows; ++j)
	  for (i = 0; i < diffImage.cols; ++i) {
      Vec3b pix = diffImage.at<Vec3b>(j, i);
      
      if ((pix[0] >= 200) && (pix[1] <= 20) && (pix[2] <= 20)) {
        Vec3b originalPix = original.at<Vec3b>(j, i);
        target.at<Vec3b>(j, i) = originalPix;
      }
		}

  medianBlur(target, target, 3);

  return target;
}
