#include "opencv.h"
#include "imwrite.h"
#include "iostream"
#include "camshiftdemo.h"
#include "opticflow.h"
#include "pointtracking.h"
#include "create_track_bar.h"
#include "use_mouse.h"
#include "draw_image.h"
#include "use_pointer_access_pixel.h"
#include "use_iterator_access_pixel.h"
#include "use_at_access_pixel.h"
#include "image_blending.h"
#include "multi_channel_image_blending.h"
#include "change_contrast_and_bright.h"
#include "threshold.h"
#include "convex_hull_2.h"
#include "approx_poly_dp.h"
#include "contour_moment.h"
#include "water_shed.h"
#include "inpaint.h"
#include "calc_back_project.h"
#include "match_template.h"
#include "harris_corner_detection.h"
#include "shi_tomasi.h"
#include "corner_subpix.h"
#include<QApplication>
#include"qdebug.h"
using namespace std;
using namespace cv;
Opencv::Opencv(QWidget *parent) : QMainWindow(parent)
{

}
void Opencv::PhotoShow()
{
    Mat srcImage = imread("/Users/liuyuchen/QT_application/Project_cv/lena.png");
    //显示原图
    imshow("Original", srcImage);
    waitKey(0);
}
void Opencv::PhotoErosion()
{
    //载入原图
    Mat srcImage = imread("/Users/liuyuchen/QT_application/Project_cv/lena.png");
    //显示原图
    imshow("Original", srcImage);
    //进行腐蚀操作
    Mat element = getStructuringElement(MORPH_RECT, Size(15, 15));
    Mat dstImage;
    erode(srcImage, dstImage, element);
    //显示效果图
    imshow("Result", dstImage);
    waitKey(0);
}
void Opencv::PhotoBlur()
{

    Mat srcImage=imread("/Users/liuyuchen/QT_application/Project_cv/lena.png");
    //【2】显示原始图
    imshow( "Original", srcImage );
    //【3】进行均值滤波操作
    Mat dstImage;
    blur( srcImage, dstImage, Size(7, 7));
    //【4】显示效果图
    imshow( "Result" ,dstImage );
    waitKey( 0 );
}
void Opencv::PhotoCanny()
{

    Mat srcImage = imread("/Users/liuyuchen/QT_application/Project_cv/lena.png");  //工程目录下应该有一张名为lena.jpg的素材图
    imshow("Original", srcImage); 	//显示原始图
    Mat dstImage,edge,grayImage;	//参数定义

    //【1】创建与src同类型和大小的矩阵(dst)
    dstImage.create( srcImage.size(), srcImage.type() );
    //此句代码的OpenCV3版为：
    cvtColor( srcImage, grayImage, COLOR_BGR2GRAY );
    //【3】先用使用 3x3内核来降噪
    blur( grayImage, edge, Size(3,3) );
    //【4】运行Canny算子
    Canny( edge, edge, 3, 9,3 );
    //【5】显示效果图
    imshow("Result", edge);
    waitKey(0);
}
void Opencv::PlayVideo()
{
    //【1】读入视频
    VideoCapture capture("/Users/liuyuchen/QT_application/Project_cv/1.avi");

    //【2】循环显示每一帧
    while(1)
    {
        Mat frame;//定义一个Mat变量，用于存储每一帧的图像
        capture>>frame;  //读取当前帧

        //若视频播放完成，退出循环
        if (frame.empty())
        {
            break;
        }

        imshow("读取视频",frame);  //显示当前帧
        waitKey(30);  //延时30ms
    }
}
void Opencv::UseCamera()
{
    //【1】从摄像头读入视频
        VideoCapture capture(0);

        //【2】循环显示每一帧
        while(1)
        {
            Mat frame;  //定义一个Mat变量，用于存储每一帧的图像
            capture>>frame;  //读取当前帧
            imshow("读取视频",frame);  //显示当前帧
            waitKey(30);  //延时30ms
        }
}
void Opencv::UseImwrite()
{
    //创建带alpha通道的Mat
        Mat mat(480, 640, CV_8UC4);
        createAlphaMat(mat);
        vector<int>compression_params;

        compression_params.push_back(IMWRITE_PNG_COMPRESSION);
        compression_params.push_back(9);

        //显示图片
        try{
            imwrite("透明Alpha值图.png", mat, compression_params);
            imshow("生成的png图",mat);
            fprintf(stdout,"PNG图片文件的alpha数据保存完毕~\n可以在工程目录下查看由imwrite函数生成的图片\n");
            waitKey(0);
        }
        catch(runtime_error& ex) {
            fprintf(stderr,"图像转换成PNG格式发生错误：%s\n", ex.what());
        }

}
void Opencv::CamShiftDemo()
{
    VideoCapture cap;
        Rect trackWindow;
        int hsize = 16;
        float hranges[] = {0,180};
        const float* phranges = hranges;

        cap.open(0);

        if( !cap.isOpened() )
        {
            cout << "不能初始化摄像头\n";
        }

        namedWindow( "Histogram", 0 );
        namedWindow( "CamShift Demo", 0 );
        setMouseCallback( "CamShift Demo", onMouse, 0 );
        createTrackbar( "Vmin", "CamShift Demo", &vmin, 256, 0 );
        createTrackbar( "Vmax", "CamShift Demo", &vmax, 256, 0 );
        createTrackbar( "Smin", "CamShift Demo", &smin, 256, 0 );

        Mat frame, hsv, hue, mask, hist, histimg = Mat::zeros(200, 320, CV_8UC3), backproj;
        bool paused = false;

        for(;;)
        {
            if( !paused )
            {
                cap >> frame;
                if( frame.empty() )
                    break;
            }

            frame.copyTo(image);

            if( !paused )
            {
                cvtColor(image, hsv, COLOR_BGR2HSV);

                if( trackObject )
                {
                    int _vmin = vmin, _vmax = vmax;

                    inRange(hsv, Scalar(0, smin, MIN(_vmin,_vmax)),
                        Scalar(180, 256, MAX(_vmin, _vmax)), mask);
                    int ch[] = {0, 0};
                    hue.create(hsv.size(), hsv.depth());
                    mixChannels(&hsv, 1, &hue, 1, ch, 1);

                    if( trackObject < 0 )
                    {
                        Mat roi(hue, selection), maskroi(mask, selection);
                        calcHist(&roi, 1, 0, maskroi, hist, 1, &hsize, &phranges);
                        //此句代码的OpenCV3版为：
                        normalize(hist, hist, 0, 255, NORM_MINMAX);
                        //此句代码的OpenCV2版为：
                        //normalize(hist, hist, 0, 255, CV_MINMAX);

                        trackWindow = selection;
                        trackObject = 1;

                        histimg = Scalar::all(0);
                        int binW = histimg.cols / hsize;
                        Mat buf(1, hsize, CV_8UC3);
                        for( int i = 0; i < hsize; i++ )
                            buf.at<Vec3b>(i) = Vec3b(saturate_cast<uchar>(i*180./hsize), 255, 255);

                        //此句代码的OpenCV3版为：
                        cvtColor(buf, buf, COLOR_HSV2BGR);
                        //此句代码的OpenCV2版为：
                        //cvtColor(buf, buf, CV_HSV2BGR);

                        for( int i = 0; i < hsize; i++ )
                        {
                            int val = saturate_cast<int>(hist.at<float>(i)*histimg.rows/255);
                            rectangle( histimg, Point(i*binW,histimg.rows),
                                Point((i+1)*binW,histimg.rows - val),
                                Scalar(buf.at<Vec3b>(i)), -1, 8 );
                        }
                    }

                    calcBackProject(&hue, 1, 0, hist, backproj, &phranges);
                    backproj &= mask;
                    RotatedRect trackBox = CamShift(backproj, trackWindow,

                    //此句代码的OpenCV3版为：
                    TermCriteria( TermCriteria::EPS | TermCriteria::COUNT, 10, 1 ));
                    //此句代码的OpenCV2版为：
                    //TermCriteria( CV_TERMCRIT_EPS | CV_TERMCRIT_ITER, 10, 1 ));

                    if( trackWindow.area() <= 1 )
                    {
                        int cols = backproj.cols, rows = backproj.rows, r = (MIN(cols, rows) + 5)/6;
                        trackWindow = Rect(trackWindow.x - r, trackWindow.y - r,
                            trackWindow.x + r, trackWindow.y + r) &
                            Rect(0, 0, cols, rows);
                    }

                    if( backprojMode )
                        cvtColor( backproj, image, COLOR_GRAY2BGR );

                    //此句代码的OpenCV3版为：
                    ellipse( image, trackBox, Scalar(0,0,255), 3, LINE_AA );
                    //此句代码的OpenCV2版为：
                    //ellipse( image, trackBox, Scalar(0,0,255), 3, CV_AA );

                }
            }
            else if( trackObject < 0 )
                paused = false;

            if( selectObject && selection.width > 0 && selection.height > 0 )
            {
                Mat roi(image, selection);
                bitwise_not(roi, roi);
            }

            imshow( "CamShift Demo", image );
            imshow( "Histogram", histimg );

            char c = (char)waitKey(10);
            if( c == 27 )
                break;
            switch(c)
            {
            case 'b':
                backprojMode = !backprojMode;
                break;
            case 'c':
                trackObject = 0;
                histimg = Scalar::all(0);
                break;
            case 'h':
                showHist = !showHist;
                if( !showHist )
                    destroyWindow( "Histogram" );
                else
                    namedWindow( "Histogram", 1 );
                break;
            case 'p':
                paused = !paused;
                break;
            default:
                ;
            }
        }
}
void Opencv::OpticFlow()
{
    Mat frame;
        Mat result;

        VideoCapture capture("/Users/liuyuchen/QT_application/Project_cv/1.avi");

        if(capture.isOpened())	// 摄像头读取文件开关
        {
            while(true)
            {
                capture >> frame;

                if(!frame.empty())
                {
                    tracking(frame, result);
                }
                else
                {
                    printf(" --(!) No captured frame -- Break!");
                    break;
                }

                int c = waitKey(50);
                if( (char)c == 27 )
                {
                    break;
                }
            }
        }

}
void Opencv::PointTracking()
{
    VideoCapture cap;

        //此句代码的OpenCV2版为：
        //TermCriteria termcrit(CV_TERMCRIT_ITER|CV_TERMCRIT_EPS, 20, 0.03);
        //此句代码的OpenCV3版为：
        TermCriteria termcrit(TermCriteria::MAX_ITER|TermCriteria::EPS, 20, 0.03);
        Size subPixWinSize(10,10), winSize(31,31);

        const int MAX_COUNT = 500;
        bool needToInit = false;
        bool nightMode = false;


        cap.open(0);

        if( !cap.isOpened() )
        {
            cout << "Could not initialize capturing...\n";
        }

        namedWindow( "LK Demo", 1 );
        setMouseCallback( "LK Demo", on_Mouse, 0 );

        Mat gray, prevGray, image;
        vector<Point2f> points[2];

        for(;;)
        {
            Mat frame;
            cap >> frame;
            if( frame.empty() )
                break;

            frame.copyTo(image);
            cvtColor(image, gray, COLOR_BGR2GRAY);

            if( nightMode )
                image = Scalar::all(0);

            if( needToInit )
            {
                // 自动初始化
                goodFeaturesToTrack(gray, points[1], MAX_COUNT, 0.01, 10, Mat(), 3, false, 0.04);
                cornerSubPix(gray, points[1], subPixWinSize, Size(-1,-1), termcrit);
                addRemovePt = false;
            }
            else if( !points[0].empty() )
            {
                vector<uchar> status;
                vector<float> err;
                if(prevGray.empty())
                    gray.copyTo(prevGray);
                calcOpticalFlowPyrLK(prevGray, gray, points[0], points[1], status, err, winSize,
                    3, termcrit, 0, 0.001);
                size_t i, k;
                for( i = k = 0; i < points[1].size(); i++ )
                {
                    if( addRemovePt )
                    {
                        if( norm(point - points[1][i]) <= 5 )
                        {
                            addRemovePt = false;
                            continue;
                        }
                    }

                    if( !status[i] )
                        continue;

                    points[1][k++] = points[1][i];
                    circle( image, points[1][i], 3, Scalar(0,255,0), -1, 8);
                }
                points[1].resize(k);
            }

            if( addRemovePt && points[1].size() < (size_t)MAX_COUNT )
            {
                vector<Point2f> tmp;
                tmp.push_back(point);

                //此句代码的OpenCV2版为：
                //cornerSubPix( gray, tmp, winSize, cvSize(-1,-1), termcrit);
                //此句代码的OpenCV3版为：
                cornerSubPix( gray, tmp, winSize, Size(-1,-1), termcrit);
                points[1].push_back(tmp[0]);
                addRemovePt = false;
            }

            needToInit = false;
            imshow("LK Demo", image);

            char c = (char)waitKey(10);
            if( c == 27 )
                break;
            switch( c )
            {
            case 'r':
                needToInit = true;
                break;
            case 'c':
                points[0].clear();
                points[1].clear();
                break;
            case 'n':
                nightMode = !nightMode;
                break;
            }

            std::swap(points[1], points[0]);
            cv::swap(prevGray, gray);
        }
}
void Opencv::LoadShowOutput()
{
        Mat girl=imread("/Users/liuyuchen/QT_application/Project_cv/girl.jpg"); //载入图像到Mat
        namedWindow("【1】动漫图"); //创建一个名为 "【1】动漫图"的窗口
        imshow("【1】动漫图",girl);//显示名为 "【1】动漫图"的窗口

        //	描述：二、初级图像混合
        //--------------------------------------------------------------------------------------------------
        //载入图片
        Mat image= imread("/Users/liuyuchen/QT_application/Project_cv/dota.jpg");
        Mat logo= imread("/Users/liuyuchen/QT_application/Project_cv/dota_logo.jpg");

        //载入后先显示
        namedWindow("【2】原画图");
        imshow("【2】原画图",image);

        namedWindow("【3】logo图");
        imshow("【3】logo图",logo);

        // 定义一个Mat类型，用于存放，图像的ROI
        Mat imageROI;
        //方法一
        imageROI= image(Rect(800,350,logo.cols,logo.rows));
        //方法二
        //imageROI= image(Range(350,350+logo.rows),Range(800,800+logo.cols));

        // 将logo加到原图上
        addWeighted(imageROI,0.5,logo,0.3,0.0,imageROI);

        //显示结果
        namedWindow("【4】原画+logo图");
        imshow("【4】原画+logo图",image);

        //-----------------------------------【三、图像的输出】--------------------------------------
        //	描述：将一个Mat图像输出到图像文件
        //-----------------------------------------------------------------------------------------------
        //输出一张jpg图片到工程目录下
        imwrite("由imwrite生成的图片.jpg",image);

        waitKey();

}
void Opencv::CreateTrackBar()
{
    //加载图像 (两图像的尺寸需相同)
        g_srcImage1 = imread("/Users/liuyuchen/QT_application/Project_cv/CreateTrackBar1.jpg");
        g_srcImage2 = imread("/Users/liuyuchen/QT_application/Project_cv/CreateTrackBar.jpg");
        if( !g_srcImage1.data ) { printf("读取第一幅图片错误，请确定目录下是否有imread函数指定图片存在~! \n");}
        if( !g_srcImage2.data ) { printf("读取第二幅图片错误，请确定目录下是否有imread函数指定图片存在~！\n");}

        //设置滑动条初值为70
        g_nAlphaValueSlider = 70;

        //创建窗体
        namedWindow(WINDOW_NAME2, 1);

        //在创建的窗体中创建一个滑动条控件
        char TrackbarName[50];
        sprintf( TrackbarName, "透明值 %d", g_nMaxAlphaValue );

        createTrackbar( TrackbarName, WINDOW_NAME2, &g_nAlphaValueSlider, g_nMaxAlphaValue, on_Trackbar );

        //结果在回调函数中显示
        on_Trackbar( g_nAlphaValueSlider, 0 );

        //按任意键退出
        waitKey(0);
}
void Opencv::UseMouse()
{
        //【1】准备参数
        g_rectangle = Rect(-1,-1,0,0);
        Mat srcImage(600, 800,CV_8UC3), tempImage;
        srcImage.copyTo(tempImage);
        g_rectangle = Rect(-1,-1,0,0);
        srcImage = Scalar::all(0);

        //【2】设置鼠标操作回调函数
        namedWindow( WINDOW_NAME2 );
        setMouseCallback(WINDOW_NAME2,on_MouseHandle,(void*)&srcImage);

        //【3】程序主循环，当进行绘制的标识符为真时，进行绘制
        while(1)
        {
            srcImage.copyTo(tempImage);//拷贝源图到临时变量
            if( g_bDrawingBox ) DrawRectangle( tempImage, g_rectangle );//当进行绘制的标识符为真，则进行绘制
            imshow( WINDOW_NAME2, tempImage );
            if( waitKey( 10 ) == 27 ) break;//按下ESC键，程序退出
        }
}

void Opencv::DrawImage()
{
    // 创建空白的Mat图像
    Mat atomImage = Mat::zeros( WINDOW_WIDTH, WINDOW_WIDTH, CV_8UC3 );
    Mat rookImage = Mat::zeros( WINDOW_WIDTH, WINDOW_WIDTH, CV_8UC3 );

    // ---------------------<1>绘制化学中的原子示例图------------------------

    //【1.1】先绘制出椭圆
    DrawEllipse( atomImage, 90 );
    DrawEllipse( atomImage, 0 );
    DrawEllipse( atomImage, 45 );
    DrawEllipse( atomImage, -45 );

    //【1.2】再绘制圆心
    DrawFilledCircle( atomImage, Point( WINDOW_WIDTH/2, WINDOW_WIDTH/2) );

    // ----------------------------<2>绘制组合图-----------------------------
    //【2.1】先绘制出椭圆
    DrawPolygon( rookImage );

    // 【2.2】绘制矩形
    rectangle( rookImage,
        Point( 0, 7*WINDOW_WIDTH/8 ),
        Point( WINDOW_WIDTH, WINDOW_WIDTH),
        Scalar( 0, 255, 255 ),
        -1,
        8 );

    // 【2.3】绘制一些线段
    DrawLine( rookImage, Point( 0, 15*WINDOW_WIDTH/16 ), Point( WINDOW_WIDTH, 15*WINDOW_WIDTH/16 ) );
    DrawLine( rookImage, Point( WINDOW_WIDTH/4, 7*WINDOW_WIDTH/8 ), Point( WINDOW_WIDTH/4, WINDOW_WIDTH ) );
    DrawLine( rookImage, Point( WINDOW_WIDTH/2, 7*WINDOW_WIDTH/8 ), Point( WINDOW_WIDTH/2, WINDOW_WIDTH ) );
    DrawLine( rookImage, Point( 3*WINDOW_WIDTH/4, 7*WINDOW_WIDTH/8 ), Point( 3*WINDOW_WIDTH/4, WINDOW_WIDTH ) );

    // ---------------------------<3>显示绘制出的图像------------------------
    imshow( WINDOW_NAME3, atomImage );
    moveWindow( WINDOW_NAME3, 0, 200 );
    imshow( WINDOW_NAME4, rookImage );
    moveWindow( WINDOW_NAME4, WINDOW_WIDTH, 200 );

    waitKey( 0 );
}
void Opencv::UsePointerAccessPixel()
{
    //【1】创建原始图并显示
        Mat srcImage = imread("/Users/liuyuchen/QT_application/Project_cv/UsePointerAccessPixel.jpg");
        imshow("原始图像",srcImage);

        //【2】按原始图的参数规格来创建创建效果图
        Mat dstImage;
        dstImage.create(srcImage.rows,srcImage.cols,srcImage.type());//效果图的大小、类型与原图片相同

        //【3】记录起始时间
        double time0 = static_cast<double>(getTickCount());

        //【4】调用颜色空间缩减函数
        colorReduce(srcImage,dstImage,32);

        //【5】计算运行时间并输出
        time0 = ((double)getTickCount() - time0)/getTickFrequency();
        cout<<"\t此方法运行时间为： "<<time0<<"秒"<<endl;  //输出运行时间

        //【6】显示效果图
        imshow("效果图",dstImage);
        waitKey(0);
}
void Opencv::UseIteratorAccessPixel()
{
    //【1】创建原始图并显示
    Mat srcImage = imread("/Users/liuyuchen/QT_application/Project_cv/UseIteratorAccessPixel.jpg");
    imshow("原始图像",srcImage);

    //【2】按原始图的参数规格来创建创建效果图
    Mat dstImage;
    dstImage.create(srcImage.rows,srcImage.cols,srcImage.type());//效果图的大小、类型与原图片相同


    //【3】记录起始时间
    double time0 = static_cast<double>(getTickCount());

    //【4】调用颜色空间缩减函数
    colorReduce2(srcImage,dstImage,32);

    //【5】计算运行时间并输出
    time0 = ((double)getTickCount() - time0)/getTickFrequency();
    cout<<"此方法运行时间为： "<<time0<<"秒"<<endl;  //输出运行时间

    //【6】显示效果图
    imshow("效果图",dstImage);
    waitKey(0);
}
void Opencv::UseAtAccessPixel()
{
    //【1】创建原始图并显示
    Mat srcImage = imread("/Users/liuyuchen/QT_application/Project_cv/UseAtAccessPixel.jpg");
    imshow("原始图像",srcImage);

    //【2】按原始图的参数规格来创建创建效果图
    Mat dstImage;
    dstImage.create(srcImage.rows,srcImage.cols,srcImage.type());//效果图的大小、类型与原图片相同

    //【3】记录起始时间
    double time0 = static_cast<double>(getTickCount());

    //【4】调用颜色空间缩减函数
    colorReduce3(srcImage,dstImage,32);

    //【5】计算运行时间并输出
    time0 = ((double)getTickCount() - time0)/getTickFrequency();
    cout<<"此方法运行时间为： "<<time0<<"秒"<<endl;  //输出运行时间

    //【6】显示效果图
    imshow("效果图",dstImage);
    waitKey(0);
}
void Opencv::ImageBlending()
{

    if(ROI_AddImage( )&& LinearBlending( )&&ROI_LinearBlending( ))
    {
        cout<<endl<<"\n运行成功，得出了需要的图像";
    }

    waitKey(0);
}
void Opencv::MultiChannelImageBlending()
{

        if(MultiChannelBlending( ))
        {
            cout<<endl<<"\n运行成功，得出了需要的图像~! ";
        }

        waitKey(0);
}
void Opencv::ChangeContrastAndBright()
{
    // 读入用户提供的图像
    g_srcImage = imread( "/Users/liuyuchen/QT_application/Project_cv/ChangeContrastAndBright.jpg");
    if( !g_srcImage.data ) { printf("读取g_srcImage图片错误~！ \n");}
    g_dstImage1 = Mat::zeros( g_srcImage.size(), g_srcImage.type() );

    //设定对比度和亮度的初值
    g_nContrastValue=80;
    g_nBrightValue=80;

    //创建窗口
    namedWindow("【效果图窗口】", 1);

    //创建轨迹条
    createTrackbar("对比度：", "【效果图窗口】",&g_nContrastValue, 300,ContrastAndBright );
    createTrackbar("亮   度：", "【效果图窗口】",&g_nBrightValue, 200,ContrastAndBright );

    //调用回调函数
    ContrastAndBright(g_nContrastValue,0);
    ContrastAndBright(g_nBrightValue,0);

    //按下“q”键时，程序退出
    while(char(waitKey(1)) != 'q') {}
}
void Opencv::DFT()
{
    //【1】以灰度模式读取原始图像并显示
        Mat srcImage = imread("/Users/liuyuchen/QT_application/Project_cv/DFT.jpg", 0);
        if(!srcImage.data ) { printf("读取图片错误，请确定目录下是否有imread函数指定图片存在~！ \n");}
        imshow("原始图像" , srcImage);

        //【2】将输入图像延扩到最佳的尺寸，边界用0补充
        int m = getOptimalDFTSize( srcImage.rows );
        int n = getOptimalDFTSize( srcImage.cols );
        //将添加的像素初始化为0.
        Mat padded;
        copyMakeBorder(srcImage, padded, 0, m - srcImage.rows, 0, n - srcImage.cols, BORDER_CONSTANT, Scalar::all(0));

        //【3】为傅立叶变换的结果(实部和虚部)分配存储空间。
        //将planes数组组合合并成一个多通道的数组complexI
        Mat planes[] = {Mat_<float>(padded), Mat::zeros(padded.size(), CV_32F)};
        Mat complexI;
        merge(planes, 2, complexI);

        //【4】进行就地离散傅里叶变换
        dft(complexI, complexI);

        //【5】将复数转换为幅值，即=> log(1 + sqrt(Re(DFT(I))^2 + Im(DFT(I))^2))
        split(complexI, planes); // 将多通道数组complexI分离成几个单通道数组，planes[0] = Re(DFT(I), planes[1] = Im(DFT(I))
        magnitude(planes[0], planes[1], planes[0]);// planes[0] = magnitude
        Mat magnitudeImage = planes[0];

        //【6】进行对数尺度(logarithmic scale)缩放
        magnitudeImage += Scalar::all(1);
        log(magnitudeImage, magnitudeImage);//求自然对数

        //【7】剪切和重分布幅度图象限
        //若有奇数行或奇数列，进行频谱裁剪
        magnitudeImage = magnitudeImage(Rect(0, 0, magnitudeImage.cols & -2, magnitudeImage.rows & -2));
        //重新排列傅立叶图像中的象限，使得原点位于图像中心
        int cx = magnitudeImage.cols/2;
        int cy = magnitudeImage.rows/2;
        Mat q0(magnitudeImage, Rect(0, 0, cx, cy));   // ROI区域的左上
        Mat q1(magnitudeImage, Rect(cx, 0, cx, cy));  // ROI区域的右上
        Mat q2(magnitudeImage, Rect(0, cy, cx, cy));  // ROI区域的左下
        Mat q3(magnitudeImage, Rect(cx, cy, cx, cy)); // ROI区域的右下
        //交换象限（左上与右下进行交换）
        Mat tmp;
        q0.copyTo(tmp);
        q3.copyTo(q0);
        tmp.copyTo(q3);
        //交换象限（右上与左下进行交换）
        q1.copyTo(tmp);
        q2.copyTo(q1);
        tmp.copyTo(q2);

        //【8】归一化，用0到1之间的浮点值将矩阵变换为可视的图像格式
        normalize(magnitudeImage, magnitudeImage, 0, 1, NORM_MINMAX);

        //【9】显示效果图
        imshow("频谱幅值", magnitudeImage);
        waitKey();

}
void Opencv::BoxFilter()
{
    // 载入原图
        Mat image=imread("/Users/liuyuchen/QT_application/Project_cv/lena.png");

        //创建窗口
        namedWindow( "方框滤波【原图】" );
        namedWindow( "方框滤波【效果图】");

        //显示原图
        imshow( "方框滤波【原图】", image );

        //进行方框滤波操作
        Mat out;
        boxFilter( image, out, -1,Size(5, 5));

        //显示效果图
        imshow( "方框滤波【效果图】" ,out );

        waitKey( 0 );
}
void Opencv::GuassianBlur()
{
    // 载入原图
        Mat image=imread("/Users/liuyuchen/QT_application/Project_cv/lena.png");

        //创建窗口
        namedWindow( "高斯滤波【原图】" );
        namedWindow( "高斯滤波【效果图】");

        //显示原图
        imshow( "高斯滤波【原图】", image );

        //进行高斯滤波操作
        Mat out;
        GaussianBlur( image, out, Size( 5, 5 ), 0, 0 );

        //显示效果图
        imshow( "高斯滤波【效果图】" ,out );

        waitKey( 0 );
}
void Opencv::MedianBlur()
{
    // 载入原图
        Mat image=imread("/Users/liuyuchen/QT_application/Project_cv/lena.png");

        //创建窗口
        namedWindow( "中值滤波【原图】" );
        namedWindow( "中值滤波【效果图】");

        //显示原图
        imshow( "中值滤波【原图】", image );

        //进行中值滤波操作
        Mat out;
        medianBlur ( image, out, 7);

        //显示效果图
        imshow( "中值滤波【效果图】" ,out );

        waitKey( 0 );

}
void Opencv::BilateralFilter()
{
    // 载入原图
        Mat image=imread("/Users/liuyuchen/QT_application/Project_cv/lena.png");

        //创建窗口
        namedWindow( "双边滤波【原图】" );
        namedWindow( "双边滤波【效果图】");

        //显示原图
        imshow( "双边滤波【原图】", image );

        //进行双边滤波操作
        Mat out;
        bilateralFilter ( image, out, 25, 25*2, 25/2 );

        //显示效果图
        imshow( "双边滤波【效果图】" ,out );

        waitKey( 0 );
}
void Opencv::Dilate()
{
    //载入原图
        Mat image = imread("/Users/liuyuchen/QT_application/Project_cv/lena.png");

        //创建窗口
        namedWindow("【原图】膨胀操作");
        namedWindow("【效果图】膨胀操作");

        //显示原图
        imshow("【原图】膨胀操作", image);

        //进行膨胀操作
        Mat element = getStructuringElement(MORPH_RECT, Size(15, 15));
        Mat out;
        dilate(image, out, element);

        //显示效果图
        imshow("【效果图】膨胀操作", out);

        waitKey(0);
}
void Opencv::DilationEx()
{
    //载入原始图
        Mat image = imread("/Users/liuyuchen/QT_application/Project_cv/lena.png");
        //创建窗口
        namedWindow("【原始图】膨胀");
        namedWindow("【效果图】膨胀");
        //显示原始图
        imshow("【原始图】膨胀", image);
        //定义核
        Mat element = getStructuringElement(MORPH_RECT, Size(15, 15));
        //进行形态学操作
        morphologyEx(image, image, MORPH_DILATE, element);
        //显示效果图
        imshow("【效果图】膨胀", image);

        waitKey(0);
}
void Opencv::Opening()
{
    //载入原始图
        Mat image = imread("/Users/liuyuchen/QT_application/Project_cv/lena.png");
        //创建窗口
        namedWindow("【原始图】开运算");
        namedWindow("【效果图】开运算");
        //显示原始图
        imshow("【原始图】开运算", image);
        //定义核
        Mat element = getStructuringElement(MORPH_RECT, Size(15, 15));
        //进行形态学操作
        morphologyEx(image, image, MORPH_OPEN, element);
        //显示效果图
        imshow("【效果图】开运算", image);

        waitKey(0);
}
void Opencv::Closing()
{
    //载入原始图
        Mat image = imread("/Users/liuyuchen/QT_application/Project_cv/lena.png");
        //创建窗口
        namedWindow("【原始图】闭运算");
        namedWindow("【效果图】闭运算");
        //显示原始图
        imshow("【原始图】闭运算", image);
        //定义核
        Mat element = getStructuringElement(MORPH_RECT, Size(15, 15));
        //进行形态学操作
        morphologyEx(image, image, MORPH_CLOSE, element);
        //显示效果图
        imshow("【效果图】闭运算", image);

        waitKey(0);
}
void Opencv::Gradient()
{
    //载入原始图
        Mat image = imread("/Users/liuyuchen/QT_application/Project_cv/lena.png");
        //创建窗口
        namedWindow("【原始图】形态学梯度");
        namedWindow("【效果图】形态学梯度");
        //显示原始图
        imshow("【原始图】形态学梯度", image);
        //定义核
        Mat element = getStructuringElement(MORPH_RECT, Size(15, 15));
        //进行形态学操作
        morphologyEx(image, image, MORPH_GRADIENT, element);
        //显示效果图
        imshow("【效果图】形态学梯度", image);

        waitKey(0);
}
void Opencv::TopHat()
{
    //载入原始图
        Mat image = imread("/Users/liuyuchen/QT_application/Project_cv/lena.png");
        //创建窗口
        namedWindow("【原始图】顶帽运算");
        namedWindow("【效果图】顶帽运算");
        //显示原始图
        imshow("【原始图】顶帽运算", image);
        //定义核
        Mat element = getStructuringElement(MORPH_RECT, Size(15, 15));
        //进行形态学操作
        morphologyEx(image, image, MORPH_TOPHAT, element);
        //显示效果图
        imshow("【效果图】顶帽运算", image);

        waitKey(0);
}
void Opencv::BlackHat()
{
    //载入原始图
        Mat image = imread("/Users/liuyuchen/QT_application/Project_cv/lena.png");
        //创建窗口
        namedWindow("【原始图】黑帽运算");
        namedWindow("【效果图】黑帽运算");
        //显示原始图
        imshow("【原始图】黑帽运算", image);
        //定义核
        Mat element = getStructuringElement(MORPH_RECT, Size(15, 15));
        //进行形态学操作
        morphologyEx(image, image, MORPH_BLACKHAT, element);
        //显示效果图
        imshow("【效果图】黑帽运算", image);

        waitKey(0);
}
void Opencv::FloodFill()
{
    Mat src = imread("/Users/liuyuchen/QT_application/Project_cv/lena.png");
        imshow("【原始图】",src);
        Rect ccomp;
        floodFill(src, Point(50,300), Scalar(155, 255,55), &ccomp, Scalar(20, 20, 20),Scalar(20, 20, 20));
        imshow("【效果图】",src);
        waitKey(0);
}
void Opencv::PyrUp()
{
    //载入原始图
        Mat srcImage = imread("/Users/liuyuchen/QT_application/Project_cv/lena.png");
        Mat tmpImage,dstImage;//临时变量和目标图的定义
        tmpImage=srcImage;//将原始图赋给临时变量

        //显示原始图
        imshow("【原始图】", srcImage);
        //进行向上取样操作
        pyrUp( tmpImage, dstImage, Size( tmpImage.cols*2, tmpImage.rows*2 ) );
        //显示效果图
        imshow("【效果图】", dstImage);

        waitKey(0);

}
void Opencv::PyrDown()
{
    //载入原始图
    Mat srcImage = imread("/Users/liuyuchen/QT_application/Project_cv/lena.png");
    Mat tmpImage,dstImage;//临时变量和目标图的定义
    tmpImage=srcImage;//将原始图赋给临时变量

    //显示原始图
    imshow("【原始图】", srcImage);
    //进行向下取样操作
    pyrDown( tmpImage, dstImage, Size( tmpImage.cols/2, tmpImage.rows/2 ) );
    //显示效果图
    imshow("【效果图】", dstImage);

    waitKey(0);

}
void Opencv::Threshold()
{
    //【1】读入源图片
    g_srcImage3 = imread("/Users/liuyuchen/QT_application/Project_cv/Threshold.jpg");
    if(!g_srcImage3.data ) { printf("读取图片错误，请确定目录下是否有imread函数指定的图片存在~！ \n");}
    imshow("原始图",g_srcImage3);

    //【2】存留一份原图的灰度图
    cvtColor( g_srcImage3, g_grayImage, COLOR_RGB2GRAY );

    //【3】创建窗口并显示原始图
    namedWindow( WINDOW_NAME5, WINDOW_AUTOSIZE );

    //【4】创建滑动条来控制阈值
    createTrackbar( "模式",
        WINDOW_NAME5, &g_nThresholdType,
        4, on_Threshold );

    createTrackbar( "参数值",
        WINDOW_NAME5, &g_nThresholdValue,
        255, on_Threshold );

    //【5】初始化自定义的阈值回调函数
    on_Threshold( 0, 0 );

    // 【6】轮询等待用户按键，如果ESC键按下则退出程序
    while(1)
    {
        int key;
        key = waitKey( 20 );
        if( (char)key == 27 ){ break; }
    }
}
void Opencv::Sobel_()
{
    //【0】创建 grad_x 和 grad_y 矩阵
        Mat grad_x, grad_y;
        Mat abs_grad_x, abs_grad_y,dst;

        //【1】载入原始图
        Mat src = imread("/Users/liuyuchen/QT_application/Project_cv/lena.png");

        //【2】显示原始图
        imshow("【原始图】sobel边缘检测", src);

        //【3】求 X方向梯度
        Sobel( src, grad_x, CV_16S, 1, 0, 3, 1, 1, BORDER_DEFAULT );
        convertScaleAbs( grad_x, abs_grad_x );
        imshow("【效果图】 X方向Sobel", abs_grad_x);

        //【4】求Y方向梯度
        Sobel( src, grad_y, CV_16S, 0, 1, 3, 1, 1, BORDER_DEFAULT );
        convertScaleAbs( grad_y, abs_grad_y );
        imshow("【效果图】Y方向Sobel", abs_grad_y);

        //【5】合并梯度(近似)
        addWeighted( abs_grad_x, 0.5, abs_grad_y, 0.5, 0, dst );
        imshow("【效果图】整体方向Sobel", dst);

        waitKey(0);
}
void Opencv::Laplacian_()
{
    //【0】变量的定义
        Mat src,src_gray,dst, abs_dst;

        //【1】载入原始图
        src = imread("/Users/liuyuchen/QT_application/Project_cv/lena.png");

        //【2】显示原始图
        imshow("【原始图】图像Laplace变换", src);

        //【3】使用高斯滤波消除噪声
        GaussianBlur( src, src, Size(3,3), 0, 0, BORDER_DEFAULT );

        //【4】转换为灰度图
        cvtColor( src, src_gray, COLOR_RGB2GRAY );

        //【5】使用Laplace函数
        Laplacian( src_gray, dst, CV_16S, 3, 1, 0, BORDER_DEFAULT );

        //【6】计算绝对值，并将结果转换成8位
        convertScaleAbs( dst, abs_dst );

        //【7】显示效果图
        imshow( "【效果图】图像Laplace变换", abs_dst );

        waitKey(0);

}
void Opencv::Scharr_()
{
    //【0】创建 grad_x 和 grad_y 矩阵
        Mat grad_x, grad_y;
        Mat abs_grad_x, abs_grad_y,dst;

        //【1】载入原始图
        Mat src = imread("/Users/liuyuchen/QT_application/Project_cv/lena.png");

        //【2】显示原始图
        imshow("【原始图】Scharr滤波器", src);

        //【3】求 X方向梯度
        Scharr( src, grad_x, CV_16S, 1, 0, 1, 0, BORDER_DEFAULT );
        convertScaleAbs( grad_x, abs_grad_x );
        imshow("【效果图】 X方向Scharr", abs_grad_x);

        //【4】求Y方向梯度
        Scharr( src, grad_y, CV_16S, 0, 1, 1, 0, BORDER_DEFAULT );
        convertScaleAbs( grad_y, abs_grad_y );
        imshow("【效果图】Y方向Scharr", abs_grad_y);

        //【5】合并梯度(近似)
        addWeighted( abs_grad_x, 0.5, abs_grad_y, 0.5, 0, dst );

        //【6】显示效果图
        imshow("【效果图】合并梯度后Scharr", dst);

        waitKey(0);
}
void Opencv::HoughLines_()
{
    //【1】载入原始图和Mat变量定义
        Mat srcImage = imread("/Users/liuyuchen/QT_application/Project_cv/HoughLines.jpg");
        Mat midImage,dstImage;//临时变量和目标图的定义

        //【2】进行边缘检测和转化为灰度图
        Canny(srcImage, midImage, 50, 200, 3);//进行一此canny边缘检测
        cvtColor(midImage,dstImage, COLOR_GRAY2BGR);//转化边缘检测后的图为灰度图

        //【3】进行霍夫线变换
        vector<Vec2f> lines;//定义一个矢量结构lines用于存放得到的线段矢量集合
        HoughLines(midImage, lines, 1, CV_PI/180, 150, 0, 0 );

        //【4】依次在图中绘制出每条线段
        for( size_t i = 0; i < lines.size(); i++ )
        {
            float rho = lines[i][0], theta = lines[i][1];
            Point pt1, pt2;
            double a = cos(theta), b = sin(theta);
            double x0 = a*rho, y0 = b*rho;
            pt1.x = cvRound(x0 + 1000*(-b));
            pt1.y = cvRound(y0 + 1000*(a));
            pt2.x = cvRound(x0 - 1000*(-b));
            pt2.y = cvRound(y0 - 1000*(a));
            line( dstImage, pt1, pt2, Scalar(55,100,195), 1, LINE_AA);
        }

        //【5】显示原始图
        imshow("【原始图】", srcImage);

        //【6】边缘检测后的图
        imshow("【边缘检测后的图】", midImage);

        //【7】显示效果图
        imshow("【效果图】", dstImage);

        waitKey(0);
}
void Opencv::HoughLinesP_()
{
    //【1】载入原始图和Mat变量定义
    Mat srcImage = imread("/Users/liuyuchen/QT_application/Project_cv/HoughLines.jpg");
    Mat midImage,dstImage;//临时变量和目标图的定义

    //【2】进行边缘检测和转化为灰度图
    Canny(srcImage, midImage, 50, 200, 3);//进行一此canny边缘检测
    cvtColor(midImage,dstImage, COLOR_GRAY2BGR);//转化边缘检测后的图为灰度图

    //【3】进行霍夫线变换
    vector<Vec4i> lines;//定义一个矢量结构lines用于存放得到的线段矢量集合
    HoughLinesP(midImage, lines, 1, CV_PI/180, 80, 50, 10 );

    //【4】依次在图中绘制出每条线段
    for( size_t i = 0; i < lines.size(); i++ )
    {
        Vec4i l = lines[i];
        line( dstImage, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(186,88,255), 1, LINE_AA);
    }

    //【5】显示原始图
    imshow("【原始图】", srcImage);

    //【6】边缘检测后的图
    imshow("【边缘检测后的图】", midImage);

    //【7】显示效果图
    imshow("【效果图】", dstImage);

    waitKey(0);
}
void Opencv::HoughCircles_()
{
    //【1】载入原始图、Mat变量定义
        Mat srcImage = imread("/Users/liuyuchen/QT_application/Project_cv/HoughCircles.jpg");
        Mat midImage,dstImage;//临时变量和目标图的定义

        //【2】显示原始图
        imshow("【原始图】", srcImage);

        //【3】转为灰度图并进行图像平滑
        cvtColor(srcImage,midImage, COLOR_BGR2GRAY);//转化边缘检测后的图为灰度图
        GaussianBlur( midImage, midImage, Size(9, 9), 2, 2 );

        //【4】进行霍夫圆变换
        vector<Vec3f> circles;
        HoughCircles( midImage, circles, HOUGH_GRADIENT,1.5, 10, 200, 100, 0, 0 );

        //【5】依次在图中绘制出圆
        for( size_t i = 0; i < circles.size(); i++ )
        {
            //参数定义
            Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
            int radius = cvRound(circles[i][2]);
            //绘制圆心
            circle( srcImage, center, 3, Scalar(0,255,0), -1, 8, 0 );
            //绘制圆轮廓
            circle( srcImage, center, radius, Scalar(155,50,255), 3, 8, 0 );
        }

        //【6】显示效果图
        imshow("【效果图】", srcImage);

        waitKey(0);
}
void Opencv::Remap_()
{
    //【0】变量定义
        Mat srcImage, dstImage;
        Mat map_x, map_y;

        //【1】载入原始图
        srcImage = imread( "/Users/liuyuchen/QT_application/Project_cv/Remap.jpg", 1 );
        if(!srcImage.data ) { printf("读取图片错误，请确定目录下是否有imread函数指定的图片存在~！ \n");}
        imshow("原始图",srcImage);

        //【2】创建和原始图一样的效果图，x重映射图，y重映射图
        dstImage.create( srcImage.size(), srcImage.type() );
        map_x.create( srcImage.size(), CV_32FC1 );
        map_y.create( srcImage.size(), CV_32FC1 );

        //【3】双层循环，遍历每一个像素点，改变map_x & map_y的值
        for( int j = 0; j < srcImage.rows;j++)
        {
            for( int i = 0; i < srcImage.cols;i++)
            {
                //改变map_x & map_y的值.
                map_x.at<float>(j,i) = static_cast<float>(i);
                map_y.at<float>(j,i) = static_cast<float>(srcImage.rows - j);
            }
        }

        //【4】进行重映射操作
        remap( srcImage, dstImage, map_x, map_y, INTER_LINEAR, BORDER_CONSTANT, Scalar(0,0, 0) );

        //【5】显示效果图
        imshow( "【程序窗口】", dstImage );
        waitKey();
}
void Opencv::EqualizeHist()
{
    // 【1】加载源图像
        Mat srcImage, dstImage;
        srcImage = imread( "/Users/liuyuchen/QT_application/Project_cv/EqualizeHist.jpg", 1 );
        if(!srcImage.data ) { printf("读取图片错误，请确定目录下是否有imread函数指定图片存在~！ \n");}

        // 【2】转为灰度图并显示出来
        cvtColor( srcImage, srcImage, COLOR_BGR2GRAY );
        imshow( "原始图", srcImage );

        // 【3】进行直方图均衡化
        equalizeHist( srcImage, dstImage );

        // 【4】显示结果
        imshow( "经过直方图均衡化后的图", dstImage );

        // 等待用户按键退出程序
        waitKey(0);
}
void Opencv::FindContours()
{
    // 【1】载入原始图，且必须以二值图模式载入
        Mat srcImage=imread("/Users/liuyuchen/QT_application/Project_cv/FindContours.jpg", 0);
        imshow("原始图",srcImage);

        //【2】初始化结果图
        Mat dstImage = Mat::zeros(srcImage.rows, srcImage.cols, CV_8UC3);

        //【3】srcImage取大于阈值119的那部分
        srcImage = srcImage > 119;
        imshow( "取阈值后的原始图", srcImage );

        //【4】定义轮廓和层次结构
        vector<vector<Point> > contours;
        vector<Vec4i> hierarchy;

        //【5】查找轮廓
        findContours( srcImage, contours, hierarchy,RETR_CCOMP, CHAIN_APPROX_SIMPLE );

        // 【6】遍历所有顶层的轮廓， 以随机颜色绘制出每个连接组件颜色
        int index = 0;
        for( ; index >= 0; index = hierarchy[index][0] )
        {
            Scalar color( rand()&255, rand()&255, rand()&255 );
            drawContours( dstImage, contours, index, color, FILLED, 8, hierarchy );
        }

        //【7】显示最后的轮廓图
        imshow( "轮廓图", dstImage );

        waitKey(0);
}
void Opencv::ConvexHull()
{
    //初始化变量和随机值
    Mat image(600, 600, CV_8UC3);
    RNG& rng = theRNG();

    //循环，按下ESC,Q,q键程序退出，否则有键按下便一直更新
    while(1)
    {
        //参数初始化
        char key;//键值
        int count = (unsigned)rng%100 + 3;//随机生成点的数量
        vector<Point> points; //点值

        //随机生成点坐标
        for(int i = 0; i < count; i++ )
        {
            Point point;
            point.x = rng.uniform(image.cols/4, image.cols*3/4);
            point.y = rng.uniform(image.rows/4, image.rows*3/4);

            points.push_back(point);
        }

        //检测凸包
        vector<int> hull;
        convexHull(Mat(points), hull, true);

        //绘制出随机颜色的点
        image = Scalar::all(0);
        for(int i = 0; i < count; i++ )
            circle(image, points[i], 3, Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255)), FILLED, LINE_AA);

        //准备参数
        int hullcount = (int)hull.size();//凸包的边数
        Point point0 = points[hull[hullcount-1]];//连接凸包边的坐标点

        //绘制凸包的边
        for(int  i = 0; i < hullcount; i++ )
        {
            Point point = points[hull[i]];
            line(image, point0, point, Scalar(255, 255, 255), 2, LINE_AA);
            point0 = point;
        }

        //显示效果图
        imshow("凸包检测示例", image);

        //按下ESC,Q,或者q，程序退出
        key = (char)waitKey();
        if( key == 27 || key == 'q' || key == 'Q' )
            break;
    }
}
void Opencv::ConvexHull2()
{
    // 加载源图像
        g_srcImage4 = imread( "/Users/liuyuchen/QT_application/Project_cv/ConvexHull2.jpg", 1 );

        // 将原图转换成灰度图并进行模糊降
        cvtColor( g_srcImage4, g_grayImage2, COLOR_BGR2GRAY );
        blur( g_grayImage2, g_grayImage2, Size(3,3) );

        // 创建原图窗口并显示
        namedWindow( WINDOW_NAME6, WINDOW_AUTOSIZE );
        imshow( WINDOW_NAME6, g_srcImage4 );

        //创建滚动条
        createTrackbar( " 阈值:", WINDOW_NAME6, &g_nThresh, g_maxThresh, on_ThreshChange );
        on_ThreshChange( 0, 0 );//调用一次进行初始化

        waitKey(0);
}
void Opencv::MinAreaRect()
{
    //初始化变量和随机值
        Mat image(600, 600, CV_8UC3);
        RNG& rng = theRNG();

        //循环，按下ESC,Q,q键程序退出，否则有键按下便一直更新
        while(1)
        {
            //参数初始化
            int count = rng.uniform(3, 103);//随机生成点的数量
            vector<Point> points;//点值

            //随机生成点坐标
            for(int  i = 0; i < count; i++ )
            {

                Point point;
                point.x = rng.uniform(image.cols/4, image.cols*3/4);
                point.y = rng.uniform(image.rows/4, image.rows*3/4);

                points.push_back(point);
            }

            //对给定的 2D 点集，寻找最小面积的包围矩形
            RotatedRect box = minAreaRect(Mat(points));
            Point2f vertex[4];
            box.points(vertex);

            //绘制出随机颜色的点
            image = Scalar::all(0);
            for( int i = 0; i < count; i++ )
                circle( image, points[i], 3, Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255)), FILLED, LINE_AA );


            //绘制出最小面积的包围矩形
            for( int i = 0; i < 4; i++ )
                line(image, vertex[i], vertex[(i+1)%4], Scalar(100, 200, 211), 2, LINE_AA);

            //显示窗口
            imshow( "矩形包围示例", image );

            //按下ESC,Q,或者q，程序退出
            char key = (char)waitKey();
            if( key == 27 || key == 'q' || key == 'Q' ) // 'ESC'
                break;
        }
}
void Opencv::MinEnclosingCircle()
{
    //初始化变量和随机值
        Mat image(600, 600, CV_8UC3);
        RNG& rng = theRNG();

        //循环，按下ESC,Q,q键程序退出，否则有键按下便一直更新
        while(1)
        {
            //参数初始化
            int count = rng.uniform(3, 103);//随机生成点的数量
            vector<Point> points;//点值

            //随机生成点坐标
            for(int  i = 0; i < count; i++ )
            {

                Point point;
                point.x = rng.uniform(image.cols/4, image.cols*3/4);
                point.y = rng.uniform(image.rows/4, image.rows*3/4);

                points.push_back(point);
            }

            //对给定的 2D 点集，寻找最小面积的包围圆
            Point2f center;
            float radius = 0;
            minEnclosingCircle(Mat(points), center, radius);

            //绘制出随机颜色的点
            image = Scalar::all(0);
            for( int i = 0; i < count; i++ )
                circle( image, points[i], 3, Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255)), FILLED, LINE_AA );


            //绘制出最小面积的包围圆
            circle(image, center, cvRound(radius), Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255)), 2, LINE_AA);

            //显示窗口
            imshow( "圆形包围示例", image );

            //按下ESC,Q,或者q，程序退出
            char key = (char)waitKey();
            if( key == 27 || key == 'q' || key == 'Q' ) // 'ESC'
                break;
        }

}
void Opencv::ApproxPolyDP()
{
    //【1】载入3通道的原图像
    g_srcImage_a = imread( "/Users/liuyuchen/QT_application/Project_cv/approxPolyDP.jpg", 1 );
    if(!g_srcImage_a.data ) { printf("读取图片错误，请确定目录下是否有imread函数指定的图片存在~！ \n");}

    //【2】得到原图的灰度图像并进行平滑
    cvtColor( g_srcImage_a, g_grayImage_a, COLOR_BGR2GRAY );
    blur( g_grayImage_a, g_grayImage_a, Size(3,3) );

    //【3】创建原始图窗口并显示
    namedWindow( WINDOW_NAME_a, WINDOW_AUTOSIZE );
    imshow( WINDOW_NAME_a, g_srcImage_a );

    //【4】设置滚动条并调用一次回调函数
    createTrackbar( " 阈值:", WINDOW_NAME_a, &g_nThresh2, g_nMaxThresh, on_ContoursChange );
    on_ContoursChange( 0, 0 );

    waitKey(0);
}
void Opencv::ContourMoment()
{
    // 读入原图像, 返回3通道图像数据
    g_srcImage_b = imread( "/Users/liuyuchen/QT_application/Project_cv/ContourMoment.jpg", 1 );

    // 把原图像转化成灰度图像并进行平滑
    cvtColor( g_srcImage_b, g_grayImage_b, COLOR_BGR2GRAY );
    blur( g_grayImage_b, g_grayImage_b, Size(3,3) );

    // 创建新窗口
    namedWindow( WINDOW_NAME_c, WINDOW_AUTOSIZE );
    imshow( WINDOW_NAME_c, g_srcImage_b );

    //创建滚动条并进行初始化
    createTrackbar( " 阈值", WINDOW_NAME_c, &g_nThresh3, g_nMaxThresh2, on_ThreshChange2 );
    on_ThreshChange2( 0, 0 );

    waitKey(0);
}
void Opencv::WaterShed()
{
    //【1】载入原图并显示，初始化掩膜和灰度图
        g_srcImage_c = imread("/Users/liuyuchen/QT_application/Project_cv/WaterShed.jpg", 1);
        imshow( WINDOW_NAME_e, g_srcImage_c );
        Mat srcImage,grayImage;
        g_srcImage_c.copyTo(srcImage);
        cvtColor(g_srcImage_c, g_maskImage, COLOR_BGR2GRAY);
        cvtColor(g_maskImage, grayImage, COLOR_GRAY2BGR);
        g_maskImage = Scalar::all(0);

        //【2】设置鼠标回调函数
        setMouseCallback( WINDOW_NAME_e, on_Mouse3, 0 );

        //【3】轮询按键，进行处理
        while(1)
        {
            //获取键值
            int c = waitKey(0);

            //若按键键值为ESC时，退出
            if( (char)c == 27 )
                break;

            //按键键值为2时，恢复源图
            if( (char)c == '2' )
            {
                g_maskImage = Scalar::all(0);
                srcImage.copyTo(g_srcImage_c);
                imshow( "image", g_srcImage_c );
            }

            //若检测到按键值为1或者空格，则进行处理
            if( (char)c == '1' || (char)c == ' ' )
            {
                //定义一些参数
                int i, j, compCount = 0;
                vector<vector<Point> > contours;
                vector<Vec4i> hierarchy;

                //寻找轮廓
                findContours(g_maskImage, contours, hierarchy, RETR_CCOMP, CHAIN_APPROX_SIMPLE);

                //轮廓为空时的处理
                if( contours.empty() )
                    continue;

                //拷贝掩膜
                Mat maskImage(g_maskImage.size(), CV_32S);
                maskImage = Scalar::all(0);

                //循环绘制出轮廓
                for( int index = 0; index >= 0; index = hierarchy[index][0], compCount++ )
                    drawContours(maskImage, contours, index, Scalar::all(compCount+1), -1, 8, hierarchy, INT_MAX);

                //compCount为零时的处理
                if( compCount == 0 )
                    continue;

                //生成随机颜色
                vector<Vec3b> colorTab;
                for( i = 0; i < compCount; i++ )
                {
                    int b = theRNG().uniform(0, 255);
                    int g = theRNG().uniform(0, 255);
                    int r = theRNG().uniform(0, 255);

                    colorTab.push_back(Vec3b((uchar)b, (uchar)g, (uchar)r));
                }

                //计算处理时间并输出到窗口中
                double dTime = (double)getTickCount();
                watershed( srcImage, maskImage );
                dTime = (double)getTickCount() - dTime;
                printf( "\t处理时间 = %gms\n", dTime*1000./getTickFrequency() );

                //双层循环，将分水岭图像遍历存入watershedImage中
                Mat watershedImage(maskImage.size(), CV_8UC3);
                for( i = 0; i < maskImage.rows; i++ )
                    for( j = 0; j < maskImage.cols; j++ )
                    {
                        int index = maskImage.at<int>(i,j);
                        if( index == -1 )
                            watershedImage.at<Vec3b>(i,j) = Vec3b(255,255,255);
                        else if( index <= 0 || index > compCount )
                            watershedImage.at<Vec3b>(i,j) = Vec3b(0,0,0);
                        else
                            watershedImage.at<Vec3b>(i,j) = colorTab[index - 1];
                    }

                    //混合灰度图和分水岭效果图并显示最终的窗口
                    watershedImage = watershedImage*0.5 + grayImage*0.5;
                    imshow( WINDOW_NAME_f, watershedImage );
            }
        }
}
void Opencv::Inpaint()
{
    //载入原始图并进行掩膜的初始化
        Mat srcImage = imread("/Users/liuyuchen/QT_application/Project_cv/Inpaint.jpg", -1);
        if(!srcImage.data ) { printf("读取图片错误，请确定目录下是否有imread函数指定图片存在~！ \n");}
        srcImage0 = srcImage.clone();
        srcImage1 = srcImage.clone();
        inpaintMask = Mat::zeros(srcImage1.size(), CV_8U);

        //显示原始图参考
        imshow(WINDOW_NAME_g, srcImage0);
        //显示原始图
        imshow(WINDOW_NAME_h, srcImage1);
        //设置鼠标回调消息
        setMouseCallback( WINDOW_NAME_h, On_Mouse2, 0 );

        //轮询按键，根据不同的按键进行处理
        while (1)
        {
            //获取按键键值
            char c = (char)waitKey();

            //键值为ESC，程序退出
            if( c == 27 )
                break;

            //键值为2，恢复成原始图像
            if( c == '2' )
            {
                inpaintMask = Scalar::all(0);
                srcImage.copyTo(srcImage1);
                imshow(WINDOW_NAME_h, srcImage1);
            }

            //键值为1或者空格，进行图像修补操作
            if( c == '1' || c == ' ' )
            {
                Mat inpaintedImage;
                inpaint(srcImage1, inpaintMask, inpaintedImage, 3, INPAINT_TELEA);
                imshow(WINDOW_NAME_i, inpaintedImage);
            }
        }

}
void Opencv::HS_Histogram()
{
    //【1】载入源图，转化为HSV颜色模型
        Mat srcImage, hsvImage;
        srcImage=imread("/Users/liuyuchen/QT_application/Project_cv/HS_Histogram.jpg");
        cvtColor(srcImage,hsvImage, COLOR_BGR2HSV);

        //【2】参数准备
        //将色调量化为30个等级，将饱和度量化为32个等级
        int hueBinNum = 30;//色调的直方图直条数量
        int saturationBinNum = 32;//饱和度的直方图直条数量
        int histSize[ ] = {hueBinNum, saturationBinNum};
        // 定义色调的变化范围为0到179
        float hueRanges[] = { 0, 180 };
        //定义饱和度的变化范围为0（黑、白、灰）到255（纯光谱颜色）
        float saturationRanges[] = { 0, 256 };
        const float* ranges[] = { hueRanges, saturationRanges };
        MatND dstHist;
        //参数准备，calcHist函数中将计算第0通道和第1通道的直方图
        int channels[] = {0, 1};

        //【3】正式调用calcHist，进行直方图计算
        calcHist( &hsvImage,//输入的数组
            1, //数组个数为1
            channels,//通道索引
            Mat(), //不使用掩膜
            dstHist, //输出的目标直方图
            2, //需要计算的直方图的维度为2
            histSize, //存放每个维度的直方图尺寸的数组
            ranges,//每一维数值的取值范围数组
            true, // 指示直方图是否均匀的标识符，true表示均匀的直方图
            false );//累计标识符，false表示直方图在配置阶段会被清零

        //【4】为绘制直方图准备参数
        double maxValue=0;//最大值
        minMaxLoc(dstHist, 0, &maxValue, 0, 0);//查找数组和子数组的全局最小值和最大值存入maxValue中
        int scale = 10;
        Mat histImg = Mat::zeros(saturationBinNum*scale, hueBinNum*10, CV_8UC3);

        //【5】双层循环，进行直方图绘制
        for( int hue = 0; hue < hueBinNum; hue++ )
            for( int saturation = 0; saturation < saturationBinNum; saturation++ )
            {
                float binValue = dstHist.at<float>(hue, saturation);//直方图组距的值
                int intensity = cvRound(binValue*255/maxValue);//强度

                //正式进行绘制
                rectangle( histImg, Point(hue*scale, saturation*scale),
                    Point( (hue+1)*scale - 1, (saturation+1)*scale - 1),
                    Scalar::all(intensity),FILLED );
            }

            //【6】显示效果图
            imshow( "素材图", srcImage );
            imshow( "H-S 直方图", histImg );

            waitKey();
}
void Opencv::Histogram2()
{
    //【1】载入原图并显示
    Mat srcImage = imread("/Users/liuyuchen/QT_application/Project_cv/Histogram2.jpg", 0);
    imshow("原图",srcImage);
    if(!srcImage.data) {cout << "fail to load image" << endl;}

    //【2】定义变量
    MatND dstHist;       // 在cv中用CvHistogram *hist = cvCreateHist
    int dims = 1;
    float hranges[] = {0, 255};
    const float *ranges[] = {hranges};   // 这里需要为const类型
    int size = 256;
    int channels = 0;

    //【3】计算图像的直方图
    calcHist(&srcImage, 1, &channels, Mat(), dstHist, dims, &size, ranges);    // cv 中是cvCalcHist
    int scale = 1;

    Mat dstImage(size * scale, size, CV_8U, Scalar(0));
    //【4】获取最大值和最小值
    double minValue = 0;
    double maxValue = 0;
    minMaxLoc(dstHist,&minValue, &maxValue, 0, 0);  //  在cv中用的是cvGetMinMaxHistValue

    //【5】绘制出直方图
    int hpt = saturate_cast<int>(0.9 * size);
    for(int i = 0; i < 256; i++)
    {
        float binValue = dstHist.at<float>(i);           //   注意hist中是float类型    而在OpenCV1.0版中用cvQueryHistValue_1D
        int realValue = saturate_cast<int>(binValue * hpt/maxValue);
        rectangle(dstImage,Point(i*scale, size - 1), Point((i+1)*scale - 1, size - realValue), Scalar(255));
    }
    imshow("一维直方图", dstImage);
    waitKey(0);
}
void Opencv::Histogram3()
{
    //【1】载入素材图并显示
        Mat srcImage;
        srcImage=imread("/Users/liuyuchen/QT_application/Project_cv/Histogram3.jpg");
        imshow( "素材图", srcImage );

        //【2】参数准备
        int bins = 256;
        int hist_size[] = {bins};
        float range[] = { 0, 256 };
        const float* ranges[] = { range};
        MatND redHist,grayHist,blueHist;
        int channels_r[] = {0};

        //【3】进行直方图的计算（红色分量部分）
        calcHist( &srcImage, 1, channels_r, Mat(), //不使用掩膜
            redHist, 1, hist_size, ranges,
            true, false );

        //【4】进行直方图的计算（绿色分量部分）
        int channels_g[] = {1};
        calcHist( &srcImage, 1, channels_g, Mat(), // do not use mask
            grayHist, 1, hist_size, ranges,
            true, // the histogram is uniform
            false );

        //【5】进行直方图的计算（蓝色分量部分）
        int channels_b[] = {2};
        calcHist( &srcImage, 1, channels_b, Mat(), // do not use mask
            blueHist, 1, hist_size, ranges,
            true, // the histogram is uniform
            false );

        //-----------------------绘制出三色直方图------------------------
        //参数准备
        double maxValue_red,maxValue_green,maxValue_blue;
        minMaxLoc(redHist, 0, &maxValue_red, 0, 0);
        minMaxLoc(grayHist, 0, &maxValue_green, 0, 0);
        minMaxLoc(blueHist, 0, &maxValue_blue, 0, 0);
        int scale = 1;
        int histHeight=256;
        Mat histImage = Mat::zeros(histHeight,bins*3, CV_8UC3);

        //正式开始绘制
        for(int i=0;i<bins;i++)
        {
            //参数准备
            float binValue_red = redHist.at<float>(i);
            float binValue_green = grayHist.at<float>(i);
            float binValue_blue = blueHist.at<float>(i);
            int intensity_red = cvRound(binValue_red*histHeight/maxValue_red);  //要绘制的高度
            int intensity_green = cvRound(binValue_green*histHeight/maxValue_green);  //要绘制的高度
            int intensity_blue = cvRound(binValue_blue*histHeight/maxValue_blue);  //要绘制的高度

            //绘制红色分量的直方图
            rectangle(histImage,Point(i*scale,histHeight-1),
                Point((i+1)*scale - 1, histHeight - intensity_red),
                Scalar(255,0,0));

            //绘制绿色分量的直方图
            rectangle(histImage,Point((i+bins)*scale,histHeight-1),
                Point((i+bins+1)*scale - 1, histHeight - intensity_green),
                Scalar(0,255,0));

            //绘制蓝色分量的直方图
            rectangle(histImage,Point((i+bins*2)*scale,histHeight-1),
                Point((i+bins*2+1)*scale - 1, histHeight - intensity_blue),
                Scalar(0,0,255));

        }

        //在窗口中显示出绘制好的直方图
        imshow( "图像的RGB直方图", histImage );
        waitKey(0);

}
void Opencv::CalcBackProject()
{
    //【1】读取源图像，并转换到 HSV 空间
    g_srcImage_d = imread( "/Users/liuyuchen/QT_application/Project_cv/backProject.jpg", 1 );
    if(!g_srcImage_d.data ) { printf("读取图片错误，请确定目录下是否有imread函数指定图片存在~！ \n");}
    cvtColor( g_srcImage_d, g_hsvImage, COLOR_BGR2HSV );

    //【2】分离 Hue 色调通道
    g_hueImage.create( g_hsvImage.size(), g_hsvImage.depth() );
    int ch[ ] = { 0, 0 };
    mixChannels( &g_hsvImage, 1, &g_hueImage, 1, ch, 1 );

    //【3】创建 Trackbar 来输入bin的数目
    namedWindow( WINDOW_NAME_j , WINDOW_AUTOSIZE );
    createTrackbar("色调组距 ", WINDOW_NAME_j , &g_bins, 180, on_BinChange );
    on_BinChange(0, 0);//进行一次初始化

    //【4】显示效果图
    imshow( WINDOW_NAME_j , g_srcImage_d );

    // 等待用户按键
    waitKey(0);
}
void Opencv::MatchTemplate()
{
    //【1】载入原图像和模板块
        g_srcImage_e = imread( "/Users/liuyuchen/QT_application/Project_cv/match_template1.jpg", 1 );
        g_templateImage = imread( "/Users/liuyuchen/QT_application/Project_cv/match_template2.jpg", 1 );

        //【2】创建窗口
        namedWindow( WINDOW_NAME_k, WINDOW_AUTOSIZE );
        namedWindow( WINDOW_NAME_l, WINDOW_AUTOSIZE );

        //【3】创建滑动条并进行一次初始化
        createTrackbar( "方法", WINDOW_NAME_k, &g_nMatchMethod, g_nMaxTrackbarNum, on_Matching );
        on_Matching( 0, 0 );

        waitKey(0);
}
void Opencv::HarrisCorner()
{
    //以灰度模式载入图像并显示
        Mat srcImage = imread("/Users/liuyuchen/QT_application/Project_cv/HarrisCorner.jpg", 0);
        imshow("原始图", srcImage);

        //进行Harris角点检测找出角点
        Mat cornerStrength;
        cornerHarris(srcImage, cornerStrength, 2, 3, 0.01);

        //对灰度图进行阈值操作，得到二值图并显示
        Mat harrisCorner;
        threshold(cornerStrength, harrisCorner, 0.00001, 255, THRESH_BINARY);
        imshow("角点检测后的二值效果图", harrisCorner);

        waitKey(0);
}
void Opencv::HarrisCorner2()
{
    //【1】载入原始图并进行克隆保存
    g_srcImage_j = imread( "/Users/liuyuchen/QT_application/Project_cv/HarrisCorner2.jpg", 1 );
    if(!g_srcImage_j.data ) { printf("读取图片错误，请确定目录下是否有imread函数指定的图片存在~！ \n");}
    imshow("原始图",g_srcImage_j);
    g_srcImage_k=g_srcImage_j.clone( );

    //【2】存留一张灰度图
    cvtColor( g_srcImage_k, g_grayImage_c, COLOR_BGR2GRAY );

    //【3】创建窗口和滚动条
    namedWindow( WINDOW_NAME_1, WINDOW_AUTOSIZE );
    createTrackbar( "阈值: ", WINDOW_NAME_1, &thresh, max_thresh, on_CornerHarris );

    //【4】调用一次回调函数，进行初始化
    on_CornerHarris( 0, 0 );

    waitKey(0);
}
void Opencv::ShiTomasi()
{
    //【1】载入源图像并将其转换为灰度图
        g_srcImage_f = imread("/Users/liuyuchen/QT_application/Project_cv/ShiTomasi.jpg", 1 );
        cvtColor( g_srcImage_f, g_grayImage_e, COLOR_BGR2GRAY );

        //【2】创建窗口和滑动条，并进行显示和回调函数初始化
        namedWindow( WINDOW_NAME_3, WINDOW_AUTOSIZE );
        createTrackbar( "最大角点数", WINDOW_NAME_3, &g_maxCornerNumber, g_maxTrackbarNumber, on_GoodFeaturesToTrack );
        imshow( WINDOW_NAME_3, g_srcImage_f );
        on_GoodFeaturesToTrack( 0, 0 );

        waitKey(0);
}
void Opencv::CornerSubPix()
{
    //【1】载入源图像并将其转换为灰度图
    g_srcImage_g = imread("/Users/liuyuchen/PycharmProjects/cv_test/calib/1.jpg", 1 );
    cvtColor( g_srcImage_g, g_grayImage_d, COLOR_BGR2GRAY );

    //【2】创建窗口和滑动条，并进行显示和回调函数初始化
    namedWindow( WINDOW_NAME_4, WINDOW_AUTOSIZE );
    createTrackbar( "最大角点数", WINDOW_NAME_4, &g_maxCornerNumber2, g_maxTrackbarNumber2, on_GoodFeaturesToTrack2 );
    imshow( WINDOW_NAME_4, g_srcImage_g );
    on_GoodFeaturesToTrack2( 0, 0 );

    waitKey(0);
}
