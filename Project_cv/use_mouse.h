#ifndef USE_MOUSE_H
#define USE_MOUSE_H
#define WINDOW_NAME2 "【程序窗口】"        //为窗口标题定义的宏
#include <opencv2/opencv.hpp>
using namespace cv;

//		描述：全局变量的声明
Rect g_rectangle;
bool g_bDrawingBox = false;//是否进行绘制
RNG g_rng(12345);


//		描述：自定义的矩形绘制函数
void DrawRectangle( cv::Mat& img, cv::Rect box )
{
    cv::rectangle(img,box.tl(),box.br(),cv::Scalar(g_rng.uniform(0, 255), g_rng.uniform(0,255), g_rng.uniform(0,255)));//随机颜色
}

//		描述：鼠标回调函数，根据不同的鼠标事件进行不同的操作
void on_MouseHandle(int event, int x, int y,int flags, void* param)
{

    Mat& image = *(cv::Mat*) param;
    switch( event)
    {
        //鼠标移动消息
    case EVENT_MOUSEMOVE:
        {
            if( g_bDrawingBox )//如果是否进行绘制的标识符为真，则记录下长和宽到RECT型变量中
            {
                g_rectangle.width = x-g_rectangle.x;
                g_rectangle.height = y-g_rectangle.y;
            }
        }
        break;

        //左键按下消息
    case EVENT_LBUTTONDOWN:
        {
            g_bDrawingBox = true;
            g_rectangle =Rect( x, y, 0, 0 );//记录起始点
        }
        break;

        //左键抬起消息
    case EVENT_LBUTTONUP:
        {
            g_bDrawingBox = false;//置标识符为false
            //对宽和高小于0的处理
            if( g_rectangle.width < 0 )
            {
                g_rectangle.x += g_rectangle.width;
                g_rectangle.width *= -1;
            }

            if( g_rectangle.height < 0 )
            {
                g_rectangle.y += g_rectangle.height;
                g_rectangle.height *= -1;
            }
            //调用函数进行绘制
            DrawRectangle( image, g_rectangle );
        }
        break;

    }
}






#endif // USE_MOUSE_H
