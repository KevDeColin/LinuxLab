#pragma once
//ÎÄ¼şÁ÷
#include <iostream>
#include <fstream>
//opencv¿â
#include <opencv2/opencv.hpp>
#include<opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

class CannyReader {
public:
	static void readCannyPath(string Path,string outPath,int precise);
};