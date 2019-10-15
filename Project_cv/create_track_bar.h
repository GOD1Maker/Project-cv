#ifndef CREATE_TRACK_BAR_H
#define CREATE_TRACK_BAR_H
#define WINDOW_NAME1 "【滑动条的创建&线性混合示例】"

const int g_nMaxAlphaValue = 100;//Alpha值的最大值
int g_nAlphaValueSlider;//滑动条对应的变量
double g_dAlphaValue;
double g_dBetaValue;

//声明存储图像的变量
Mat g_srcImage1;
Mat g_srcImage2;
Mat g_dstImage;

//		描述：响应滑动条的回调函数
void on_Trackbar( int, void* )
{
    //求出当前alpha值相对于最大值的比例
    g_dAlphaValue = (double) g_nAlphaValueSlider/g_nMaxAlphaValue ;
    //则beta值为1减去alpha值
    g_dBetaValue = ( 1.0 - g_dAlphaValue );

    //根据alpha和beta值进行线性混合
    addWeighted( g_srcImage1, g_dAlphaValue, g_srcImage2, g_dBetaValue, 0.0, g_dstImage);

    //显示效果图
    imshow( WINDOW_NAME1, g_dstImage );
}
#endif // CREATE_TRACK_BAR_H
