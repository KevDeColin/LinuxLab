#include "cannyReader.h"
#include "cannyDraw.h"
#include<string.h>
/*
*     eg: string imagePath = "D:/Program/linux期末/CannyDrawVideo/image/1.jpg";
*           outPath="D:"
*     ->header:D:/Program/linux期末/CannyDrawVideo/image
*     ->name:1
*     ->postfix:jpg
*     ->输出到：outPath+name+jpg->D:/image or video/1.jpg
*/
void CannyReader::readCannyPath(string Path,string outPath,int precise) {
    //image的后缀
    string imagePostfixes[4] = { "jpg","jpeg","bmp","png" };
    //找到最后的一个/
    std::size_t find = Path.find_last_of("/");
    //构造header
    string header = Path.substr(0, find);
    cout << "header:" << header << endl;
    //找到最后的一个.
    std::size_t findPostfix = Path.find_last_of(".");
    //构造文件名
    string name = Path.substr(find+1, findPostfix-find-1);
    cout << "name:" << name << endl;
    //构造后缀
    string postfix = Path.substr(findPostfix + 1);
    cout << "postfix:" << postfix << endl;
    bool flag = false;
    //判断高低精度
    string Precise;
    if (precise == 1) {
        Precise = "high_precise_";
    }
    else {
        Precise = "low_precise_";
    }
    for (string imagePostfix : imagePostfixes) {
        if (imagePostfix == postfix) {
            //文件组合命名
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
        //文件组合命名
        string videoPath = header + '/'+name + '.'+postfix;
        string outVideoPath = outPath + "/video/" + Precise+name + ".avi";
        cout << "outVideoPath:" << outVideoPath << endl;
        //CannyDraw::convertVideoToCanny(videoPath, outVideoPath,precise);
        CannyDraw::convertVideoToCanny(videoPath, outPath,precise);
    }
}
