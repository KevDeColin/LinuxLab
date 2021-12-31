#pragma once
#include <iostream>
#include <fstream>//文件流
#include <opencv2/opencv.hpp>//opencv库
#include<opencv2/imgcodecs.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include"mediaInfo.h"
using namespace std;
using namespace cv;

class ImageTransformer
{
public:
	ImageTransformer();

public:
	/***
	 * 把Mat图片变量转换成字符输出到控制台。
	 * 输入图片变量。
	 */
	static string convertMatToAlphabetic(Mat image);

	/***
	 * 把图片转换成字符输出到控制台。
	 * 输入图片路径,使用“\\”。
	 */
	static bool convertMatToAlphabetic(string imagePath);

	/**
	 * 视频转字符
	 * 输入视频路径,使用“\\”。
	 */
	static void convertVideoToAlphabetic(string videoPath, mediaInfo& pages,int& framenum);
};


