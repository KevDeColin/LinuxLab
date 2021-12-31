#pragma once
#include <iostream>
#include <fstream>//�ļ���
#include <opencv2/opencv.hpp>//opencv��
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
	 * ��MatͼƬ����ת�����ַ����������̨��
	 * ����ͼƬ������
	 */
	static string convertMatToAlphabetic(Mat image);

	/***
	 * ��ͼƬת�����ַ����������̨��
	 * ����ͼƬ·��,ʹ�á�\\����
	 */
	static bool convertMatToAlphabetic(string imagePath);

	/**
	 * ��Ƶת�ַ�
	 * ������Ƶ·��,ʹ�á�\\����
	 */
	static void convertVideoToAlphabetic(string videoPath, mediaInfo& pages,int& framenum);
};


