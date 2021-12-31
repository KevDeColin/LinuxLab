#include "ImageTransformer.h"
#include<QString>
#include<QApplication>
int height,width;
int factor=1;
class MainWindow;
extern MainWindow* window;
extern QApplication* app;
void addQuickState(const QString& state,MainWindow*window);
ImageTransformer::ImageTransformer()
{
}

string ImageTransformer::convertMatToAlphabetic(Mat image)
{
	//�ַ�������
//	unsigned char codeLib[8] = { 'M','A','v','|','-','.' };
	unsigned char codeLib[12] = { 'M','@','#','$','&','%','|','!',';','^','\'',' '};
	//ƴ���ַ���
	string string_Frame = "";

	if (image.empty())
	{//��ȡʧ��
		cout << "check the frame of video >>> " << endl;
        return std::string{false};
	}
	Mat image_gray;
	cvtColor(image, image_gray, COLOR_BGR2GRAY);//ת��Ϊ��ͨ��ͼ

	Mat image_gray_sm, image_update;
	//�����Ҷ�ͼ��С
    resize(image_gray, image_gray_sm, Size(width,height), 0, 0, INTER_LINEAR);

	//��ȡ���
	image_update = image_gray_sm;
	int row = image_update.rows;//�У������ظߣ�
	int col = image_update.cols;//�����������ؿ�//1080 1920

	for (int i = 0; i < row; i++)
	{//������

		for (int j = 0; j < col; j++)
		{//�����У�����ǵ�ͨ��colsֻ��һ��

			float percent = (float)image_update.at<unsigned char>(i, j) / 256;//�жϵ�ǰλ�����ص�Ҷ�ֵ

			string_Frame += codeLib[(int)(percent * sizeof(codeLib))];//ƴ���ַ�
		}
		string_Frame += "\n";
	}
	//���֡�ַ���
	//cout << string_Frame << endl;
	return string_Frame;
}

bool ImageTransformer::convertMatToAlphabetic(string imagePath)
{
	Mat image = imread(imagePath);
	//�ַ�������
	unsigned char codeLib[4] = { ' ','@','|',' ' };
	//ƴ���ַ���
	string string_Frame = "";

	if (image.empty())
	{//��ȡʧ��
		cout << "check the frame of video >>> " << endl;
		return false;
	}
	Mat image_gray;
	cvtColor(image, image_gray, COLOR_BGR2GRAY);//ת��Ϊ��ͨ��ͼ
	imshow("gray", image_gray);
	waitKey(0);
	Mat image_gray_sm, image_update;
    resize(image_gray, image_gray_sm, Size(width,height), 0, 0, INTER_LINEAR);
	
	//��ȡ���
	image_update = image_gray_sm;
	int row = image_update.rows;//�У������ظߣ�
	int col = image_update.cols;//�����������ؿ�//1080 1920
	//cout << row << " " << col << " " << endl;
	for (int i = 0; i < row; i++)
	{//������

		for (int j = 0; j < col; j++)
		{//�����У�����ǵ�ͨ��colsֻ��һ��

			float percent = (float)image_update.at<unsigned char>(i, j) / 256;//�жϵ�ǰλ�����ص�Ҷ�ֵ
			if ((int)(percent * sizeof(codeLib)) < 0 || (int)(percent * sizeof(codeLib)) > 3) {
				cout << (int)image_update.at<unsigned char>(i, j) << " ";
				cout << i << " " << j << " " << (int)(percent * sizeof(codeLib));
			}
			string_Frame += codeLib[(int)(percent * sizeof(codeLib))];//ƴ���ַ�
		}
		string_Frame += "\n";
	}
	//���֡�ַ���
	cout << string_Frame;
	return true;
}

void ImageTransformer::convertVideoToAlphabetic(string videoPath, mediaInfo& pages,int& framenum)
{
	VideoCapture video(videoPath);
	framenum=video.get(CAP_PROP_FRAME_COUNT);
    pages.fps=video.get(CAP_PROP_FPS);//liyuyi
//CV_CAP_PROP_FPS
    pages.row = video.get(CAP_PROP_FRAME_HEIGHT)/(factor*2);
    pages.col = video.get(CAP_PROP_FRAME_WIDTH)/factor;

    width=pages.col;
    height=pages.row;

	if (!video.isOpened())
	{
		cout << "loading video failed >>> " << endl;
	}

	Mat frame;
	int i = 0;
	while (true)
	{
		if (!video.read(frame)) {
			cout << "readVideoFrameError >>> " << endl;
			break;
		}
		pages.frame.push_back(ImageTransformer::convertMatToAlphabetic(frame));
		i++;
        app->processEvents();
        addQuickState("Computing:"+QString::fromStdString(std::to_string(i)+"/"+std::to_string(framenum)),window);
	}
    addQuickState("",window);

	video.release();
	return;
}
