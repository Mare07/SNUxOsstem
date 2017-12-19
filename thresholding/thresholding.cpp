#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>

using namespace cv;


int main( int argc, char** argv )
{

 char* imageName = argv[1];
 for(int i = 0 ; i < 399 ; i++){
    std::string imageN;
    if(i < 10){
  imageN = "image/ct.00" + std::to_string(i) + ".jpg";        
    } else if( i < 100 ) {
   imageN = "image/ct.0" + std::to_string(i) + ".jpg"; 
    } else {
  imageN = "image/ct." + std::to_string(i) + ".jpg"; 
}

 Mat image;
 image = imread( imageN, 1 );

 Mat gray_image;
  threshold( image, gray_image, 40, 255,3 );

 std::string saveName = "new"+imageN;
 imwrite( saveName, gray_image );

}
 

 return 0;
}
