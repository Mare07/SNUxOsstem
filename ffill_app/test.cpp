/*
 * test.cpp
 */

#include "ffill.h"

int main() {
	Point left = Point(133, 131);
	Point right = Point(250, 121);
	string filedir = "/home/hyewon/share/ct_coronal/";
	int begin = 109;
	int end = 120;

	floodfill(left, right, filedir, begin, end);

	return 0;
}

