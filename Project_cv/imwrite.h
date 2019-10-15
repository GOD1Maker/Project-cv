#ifndef IMWRITE_H
#define IMWRITE_H
#include<vector>
#include<iostream>
#include"opencv.h"
using namespace std;
using namespace cv;
//创建带alpha的通道Mat
void createAlphaMat(Mat &mat)
{
    for(int i = 0; i < mat.rows; ++i) {
        for(int j = 0; j < mat.cols; ++j) {
            Vec4b&rgba = mat.at<Vec4b>(i, j);
            rgba[0]= UCHAR_MAX;
            rgba[1]= saturate_cast<uchar>((float (mat.cols - j)) / ((float)mat.cols) *UCHAR_MAX);
            rgba[2]= saturate_cast<uchar>((float (mat.rows - i)) / ((float)mat.rows) *UCHAR_MAX);
            rgba[3]= saturate_cast<uchar>(0.5 * (rgba[1] + rgba[2]));
        }
    }
}
#endif // IMWRITE_H
