#include "cannyReader.h"
#include "cannyDraw.h"
#include<string.h>
/*
*     eg: string imagePath = "D:/Program/linux��ĩ/CannyDrawVideo/image/1.jpg";
*           outPath="D:"
*     ->header:D:/Program/linux��ĩ/CannyDrawVideo/image
*     ->name:1
*     ->postfix:jpg
*     ->�������outPath+name+jpg->D:/image or video/1.jpg
*/
void CannyReader::readCannyPath(string Path,string outPath,int precise) {
    //image�ĺ�׺
    string imagePostfixes[4] = { "jpg","jpeg","bmp","png" };
    //�ҵ�����һ��/
    std::size_t find = Path.find_last_of("/");
    //����header
    string header = Path.substr(0, find);
    cout << "header:" << header << endl;
    //�ҵ�����һ��.
    std::size_t findPostfix = Path.find_last_of(".");
    //�����ļ���
    string name = Path.substr(find+1, findPostfix-find-1);
    cout << "name:" << name << endl;
    //�����׺
    string postfix = Path.substr(findPostfix + 1);
    cout << "postfix:" << postfix << endl;
    bool flag = false;
    //�жϸߵ;���
    string Precise;
    if (precise == 1) {
        Precise = "high_precise_";
    }
    else {
        Precise = "low_precise_";
    }
    for (string imagePostfix : imagePostfixes) {
        if (imagePostfix == postfix) {
            //�ļ��������
            string imagePath = header + '/'+name +'.'+ postfix;
            string outImagePath = outPath + "/image/" +Precise+name + ".jpg";
            cout << "outImagePath:" << outImagePath << endl;
            //CannyDraw::convertImageToCanny(imagePath, outImagePath,precise);
            CannyDraw::convertImageToCanny(imagePath, outPath,precise);
            flag = true;
            break;
        }
    }
    if (!flag) {
        //�ļ��������
        string videoPath = header + '/'+name + '.'+postfix;
        string outVideoPath = outPath + "/video/" + Precise+name + ".avi";
        cout << "outVideoPath:" << outVideoPath << endl;
        //CannyDraw::convertVideoToCanny(videoPath, outVideoPath,precise);
        CannyDraw::convertVideoToCanny(videoPath, outPath,precise);
    }
}
