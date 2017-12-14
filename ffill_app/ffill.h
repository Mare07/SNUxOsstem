#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/highgui.hpp"

#include <iostream>
#include <sstream>
#include <iomanip>
#include "../ShapeMatching/shapematch.h"
#include "../ShapeMatching/shapematch.cpp"

static void help();
static void metahelp();
static void onMouse(int, int, int, int, void*);
static void colorFlood(Point);
