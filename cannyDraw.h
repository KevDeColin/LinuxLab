#pragma once
//ÎÄ¼þÁ÷
#include <iostream>
#include <fstream>
//opencv¿â
#include <opencv2/opencv.hpp>
#include<opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

class CannyDraw {
public:
	CannyDraw();
	static void convertVideoToCanny(std::string videoPath, string outPath,int precise);
	static Mat convertMatToCanny(Mat image);
	static bool convertImageToCanny(string imagePath, string outPath,int precise);
	static void convertHighToLowVideo(Mat& image);
};
