/*
 * ffillwhole.cpp
 */

#include "ffill.h"

Mat prev, image0, image, gray, mask, colored, matched;
// Mat image0: each original ct image
// Mat colored: floodfilled image1
// Shape Matching uses Mat prev & matched & colored & image0.
Mat matched_mask, filled_mask;

int ffillMode = 1;
int connectivity = 4;
int isColor = true;
bool useMask = false;
int newMaskVal = 255;
Point seedLeft;
Point seedRight;
static int seedCount = 0;
int loDiff = 20, upDiff = 20; // upDiff = 10; 
/* Regarding upDiff... 
 After certain stage where the region is big enough and 
 clearly distinguishable from surroundings,
 color is filled to the extent when upDiff=30.
 But when the sinus gets mingled with other vacant spaces,
 floodfill doesn't detect correct region. In this case, upDiff=10 yields better result.
*/

Scalar blue(255, 0, 0);

static void colorFlood(Point seed){
    int lo = ffillMode == 0 ? 0 : loDiff;
    int up = ffillMode == 0 ? 0 : upDiff;
    int flags = connectivity + (newMaskVal << 8) +
                (ffillMode == 1 ? FLOODFILL_FIXED_RANGE : 0);

    // Region colored blue
    int b = 255;
    int g = 0;
    int r = 0; 

    Rect ccomp; 
    //new region was colored light gray : Scalar(r*0.299 + g*0.587 + b*0.114)

    Scalar newVal = isColor ? blue : Scalar(r*0.299 + g*0.567 + b*0.114);
    Mat dst = isColor ? image : gray;
    
    matched_mask = Scalar::all(0);

    int area; // # of pixels repainted?

    if( useMask )
    {
        threshold(mask, mask, 1, 255, THRESH_BINARY); 
        // 3rd arg was originally 128
        area = floodFill(dst, mask, seed, newVal, &ccomp, Scalar(lo, lo, lo),
                  Scalar(up, up, up), flags);
        
	imshow( "mask", mask ); // shows mask geting updated.
        
    }
    else
    {
        area = floodFill(dst, seed, newVal, &ccomp, Scalar(lo, lo, lo),
                  Scalar(up, up, up), flags);
    }
    
    dst.copyTo(colored);

    imshow("current", colored);
    cout << area << " pixels were repainted\n";
}

static Mat fillHoles(Mat holey){
  Mat filled = holey.clone();

  // CONTOUR ??
  vector<vector<Point> > contours; 
  vector<Vec4i> hierarchy; 
  findContours(holey, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE);
  //cout << "contours size: " << contours.size() <<endl;

  for(int i = 0; i<contours.size();i++){
    drawContours(filled, contours, i, blue, 4, 8, hierarchy, 2);
  }

  // MORPHOLOGY - CLOSE
  Mat elem;

  for(int i = 0; i < SIZE; i++){ 
    elem = getStructuringElement(MORPH_ELLIPSE, Size(2*i+1, 2*i+1), Point(i, i));
    morphologyEx(holey, filled, MORPH_CLOSE, elem);    
  }

  return filled;
}

void floodfill(Point left, Point right, string filedir, int begin, int end)
{
		seedLeft = left;
		seedRight = right;
    int ctnum;
    ostringstream ss;
    string filename;
    bool wannaExit = false;

    for(ctnum = begin; ctnum < end; ctnum++){
      // Iterate CT images

      bool nextpic = false;
      ss.str(""); // flush the stream
      // image file name format: ct.026.jpg
      ss << filedir << "ct." << setw(3) << setfill('0') << ctnum << ".jpg";
      filename = ss.str();
      cout << filename << endl;
    
      image0 = imread(filename, 1);

    	if( image0.empty() )
    	{
      	  cout << "Image empty\n";
        	return;
    	}
 
    	image0.copyTo(image); 

    	cvtColor(image0, gray, COLOR_BGR2GRAY);
    	mask.create(image0.rows+2, image0.cols+2, CV_8UC1);
    
    	namedWindow( "current", 0 );
    	createTrackbar( "lo_diff", "current", &loDiff, 255, 0 );
    	createTrackbar( "up_diff", "current", &upDiff, 255, 0 );
    
    	if(prev.empty()){
      	namedWindow("prev", 0);
    	}
    	else{
       	imshow("prev", prev);
    	}
    
    	namedWindow("matched", 0);
    	namedWindow("matched_mask", 0);    
    	namedWindow("filled_mask", 0);

     	colorFlood(seedLeft);
      colorFlood(seedRight);
   
      imshow("current", isColor ? image : gray);
        
			// debug
			while (1) {
				char c = (char)waitKey(0);
				if (c == 'n') break;
   		}
			// gubed

			nextpic = true;
      if (!prev.empty()){
      	if (useMask){
       		// ?      
				}
       	matched = ShapeMatching(prev, colored, image0);
	     	imshow("matched", matched);

       	inRange(matched, blue, blue, matched_mask);
       	filled_mask = fillHoles(matched_mask);
       	imshow("matched_mask", matched_mask);
       	imshow("filled_mask", filled_mask);
	   	}

	     if(nextpic){
   		 		prev = image.clone();
					if (!matched.empty()){
        		prev = matched.clone();
      		}
					mask = Scalar::all(0);             
      	}
    }//end for
    
		return;
}
