#ifndef MEDIAINFO_H
#define MEDIAINFO_H
#include<string>
#include<vector>
struct mediaInfo{
    std::vector<std::string>frame;//每一帧对应的字符串
    double fps;//原始视频的帧速率,如果是图像就填鸽1
    //灰度矩阵的行与列
    int row;
    int col;
};
#endif // MEDIAINFO_H
