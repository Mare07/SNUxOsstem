/*
 * shapematch.cpp
 */

#include "shapematch.h"

Mat ShapeMatching(Mat previous, Mat target, Mat original, int *left, int *right) {
  // original is original(before floodfill) image of target
	Mat diffImage;
	absdiff(previous, target, diffImage); // get difference

	Mat result = target.clone();
	*left = 0;
	*right = 0;

	int i, j;
	for (j = 0; j < diffImage.rows; ++j)
	  for (i = 0; i < diffImage.cols; ++i) {
      Vec3b pix = diffImage.at<Vec3b>(j, i);

      if ((pix[0] >= 230) && (pix[1] >= 230) && (pix[2] >= 230)) {
        Vec3b originalPix = original.at<Vec3b>(j, i);
        result.at<Vec3b>(j, i) = originalPix;
      	if (i <= (diffImage.cols / 2)) { // left
					(*left)++;
				} else { // right
					(*right)++;
				}
			}
		}

  medianBlur(result, result, 3);

  return result;
}
