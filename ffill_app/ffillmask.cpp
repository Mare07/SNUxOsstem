#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/highgui.hpp"

#include <iostream>
#include <sstream>
#include <iomanip>
#include "../ShapeMatching/shapematch.h"
#include "../ShapeMatching/shapematch.cpp"

#define BEGIN 110 //was 86
#define END 191

using namespace cv;
using namespace std;

static void metahelp(){
  cout << "Press key \"h\" in order to see instructions." << endl;
}

static void help()
{
    cout << "\nThis program demonstrated the floodFill() function\n"
            "Call:\n"
            "./ffilldemo [image_name -- Default: ../data/fruits.jpg]\n" << endl;

    cout << "Hot keys: \n"
            "\tESC - quit the program\n"
            "\tc - switch color/grayscale mode\n"
            "\tm - switch mask mode\n"
            "\tn - move on to next image\n"
            "\tr - restore the original image\n"
            "\ts - use null-range floodfill\n"
            "\tf - use gradient floodfill with fixed(absolute) range\n"
            "\tg - use gradient floodfill with floating(relative) range\n"
            "\t4 - use 4-connectivity mode\n"
            "\t8 - use 8-connectivity mode\n" << endl;
}

Mat prev, image0, image, gray, mask, matched, orig;
//Mat prev & matched & orig for shape matching.

int ffillMode = 1;
int loDiff = 20, upDiff = 20; 
/* 
 After certain stage where the region is clearly visible
 and distinguishable from surroundings,
 color is filled to the extent when upDiff=30.
*/
int connectivity = 4;
int isColor = true;
bool useMask = false;
int newMaskVal = 255;


static void onMouse( int event, int x, int y, int, void* )
{
    if( event != EVENT_LBUTTONDOWN )
        return;

    Point seed = Point(x,y);
   
    cout << "You clicked " << seed << endl;

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

    Scalar newVal = isColor ? Scalar(b, g, r) : Scalar(r*0.299 + g*0.567 + b*0.114);
    Mat dst = isColor ? image : gray;
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
    
    imshow("image", dst);
    cout << area << " pixels were repainted\n";
}


int main( int argc, char** argv )
{
    cv::CommandLineParser parser (argc, argv,
        "{help h | | show help message}{@image|../data/fruits.jpg| input image}"
    );
    // left: argv / middle: default value / right: description (?) 
    
    
    if (parser.has("help"))
    {
        parser.printMessage();
        return 0;
    }
    string filedir = parser.get<string>("@image");
    int ctnum;
    ostringstream ss;
    string filename;
    bool wannaExit = false;
    

    for(ctnum = BEGIN; ctnum < END; ctnum++){
     bool nextpic = false;
     ss.str(""); // flush the stream
      //cout << "ctnum:" << ctnum << endl;
      ss << filedir << "ct." << setw(3) << setfill('0') << ctnum << ".jpg";
      filename = ss.str();
      cout << filename << endl;
    
    image0 = imread(filename, 1);

    if( image0.empty() )
    {
        cout << "Image empty\n";
        parser.printMessage();
        return 0;
    }
    metahelp();
    //help();
    image0.copyTo(image);
    cvtColor(image0, gray, COLOR_BGR2GRAY);
    mask.create(image0.rows+2, image0.cols+2, CV_8UC1);
    orig.create(image0.rows+2, image0.cols+2, CV_8UC1);
    image0.copyTo(orig);
    namedWindow( "image", 0 );
    createTrackbar( "lo_diff", "image", &loDiff, 255, 0 );
    createTrackbar( "up_diff", "image", &upDiff, 255, 0 );

    setMouseCallback( "image", onMouse, 0 );
    if(prev.empty()){
       namedWindow("prevmask", 0);
    }
    else{
       imshow("prevmask", prev);
    }
    //why is prev initialized to black???? i stored mask into it.
    namedWindow("matched", 0);
    namedWindow("orig", 0);

    while(1)
    {
        imshow("image", isColor ? image : gray);
        imshow("orig", orig);

        char c = (char)waitKey(0);
        if( c == 27 )//esc key
        {
            wannaExit = true;
            cout << "Exiting ...\n";
            break;
        }
        switch( c )
        {
        case 'c':
            if( isColor )
            {
                cout << "Grayscale mode is set\n";
                cvtColor(image0, gray, COLOR_BGR2GRAY);
                mask = Scalar::all(0);
                isColor = false;
            }
            else
            {
                cout << "Color mode is set\n";
                image0.copyTo(image);
                mask = Scalar::all(0);
                isColor = true;
            }
            break;
        case 'h':
            help();
            break;
        case 'm':
            if( useMask )
            {
                destroyWindow( "mask" );
                useMask = false;
            }
            else
            {
                namedWindow( "mask", 0 );
                mask = Scalar::all(0); // background black
                imshow("mask", mask);
                useMask = true;
            }
            break;
        case 'n': //added
            nextpic = true;
            if(!prev.empty()){
            matched = ShapeMatching(prev, mask, orig);
            imshow("matched", matched);
            }
            cout << "Next image: ";
            break;
        case 'r':
            cout << "Original image is restored\n";
            image0.copyTo(image);
            cvtColor(image, gray, COLOR_BGR2GRAY);
            mask = Scalar::all(0);
            break;
        case 's':
            cout << "Simple floodfill mode is set\n";
            ffillMode = 0;
            break;
        case 'f':
            cout << "Fixed Range floodfill mode is set\n";
            ffillMode = 1;
            break;
        case 'g':
            cout << "Gradient (floating range) floodfill mode is set\n";
            ffillMode = 2;
            break;
        case '4':
            cout << "4-connectivity mode is set\n";
            connectivity = 4;
            break;
        case '8':
            cout << "8-connectivity mode is set\n";
            connectivity = 8;
            break;
        }

      if(nextpic){
        // cout << "Breaking to move onto next ct image.." << endl;
        if(useMask){
          prev = mask.clone();
          mask = Scalar::all(0);      
        }
        break;//break again from the outer loop and change the ct image.
      }
    }//end fwhile


  if(wannaExit){
    return 0; //exit now.
  }
}
    return 0;
}
