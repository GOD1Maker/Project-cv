#ifndef OPENCV_H
#define OPENCV_H

#include <QMainWindow>
#include <opencv2/opencv.hpp>
#include <QTimer>

class Opencv : public QMainWindow
{
    Q_OBJECT
public:
    explicit Opencv(QWidget *parent = nullptr);
    static void PhotoShow();
    static void PhotoErosion();
    static void PhotoBlur();
    static void PhotoCanny();
    static void PlayVideo();
    static void UseCamera();
    static void UsePrintf();
    static void UseImwrite();
    static void CamShiftDemo();
    static void OpticFlow();
    static void PointTracking();
    static void LoadShowOutput();
    static void CreateTrackBar();
    static void UseMouse();
    static void DrawImage();
    static void UsePointerAccessPixel();
    static void UseIteratorAccessPixel();
    static void UseAtAccessPixel();
    static void ImageBlending();
    static void MultiChannelImageBlending();
    static void ChangeContrastAndBright();
    static void DFT();
    static void BoxFilter();
    static void GuassianBlur();
    static void MedianBlur();
    static void BilateralFilter();
    static void Dilate();
    static void DilationEx();
    static void Opening();
    static void Closing();
    static void Gradient();
    static void TopHat();
    static void BlackHat();
    static void FloodFill();
    static void PyrUp();
    static void PyrDown();
    static void Threshold();
    static void Sobel_();
    static void Laplacian_();
    static void Scharr_();
    static void HoughLines_();
    static void HoughLinesP_();
    static void HoughCircles_();
    static void Remap_();
    static void EqualizeHist();
    static void FindContours();
    static void ConvexHull();
    static void ConvexHull2();
    static void MinAreaRect();
    static void MinEnclosingCircle();
    static void ApproxPolyDP();
    static void ContourMoment();
    static void WaterShed();
    static void Inpaint();
    static void HS_Histogram();
    static void Histogram2();
    static void Histogram3();
    static void CalcBackProject();
    static void MatchTemplate();
    static void HarrisCorner();
    static void HarrisCorner2();
    static void ShiTomasi();
    static void CornerSubPix();





signals:
private:



public slots:
};

#endif // OPENCV_H
