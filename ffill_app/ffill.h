#ifndef _ffill_h
#define _ffill_h

#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/highgui.hpp"

#include <iostream>
#include <sstream>
#include <iomanip>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>

#include "shapematch.h"
//#include "shapematch.cpp"

#define SIZE 20

using namespace cv;
using namespace std;

//static void help();
//static void metahelp();
//static void onMouse(int, int, int, int, void*);
static void colorFlood(Point);
static Mat fillHoles(Mat);
void floodfill(Point, Point, string, int, int);

#endif
