#pragma once
//�ļ���
#include <iostream>
#include <fstream>
//opencv��
#include <opencv2/opencv.hpp>
#include<opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

class CannyReader {
public:
	static void readCannyPath(string Path,string outPath,int precise);
};