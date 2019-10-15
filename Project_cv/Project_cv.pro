#-------------------------------------------------
#
# Project created by QtCreator 2019-02-15T16:01:09
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Project_cv
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
INCLUDEPATH +=/usr/local/include/opencv4
LIBS += -L/usr/local/lib -lopencv_stitching -lopencv_superres -lopencv_videostab -lopencv_aruco -lopencv_bgsegm -lopencv_bioinspired -lopencv_ccalib -lopencv_dnn -lopencv_dpm -lopencv_fuzzy -lopencv_line_descriptor -lopencv_optflow -lopencv_plot -lopencv_reg -lopencv_saliency -lopencv_stereo -lopencv_structured_light -lopencv_rgbd -lopencv_surface_matching -lopencv_tracking -lopencv_datasets -lopencv_face -lopencv_xfeatures2d -lopencv_shape -lopencv_video -lopencv_ximgproc -lopencv_calib3d -lopencv_features2d -lopencv_flann -lopencv_xobjdetect -lopencv_objdetect -lopencv_ml -lopencv_xphoto -lopencv_highgui -lopencv_videoio -lopencv_imgcodecs -lopencv_photo -lopencv_imgproc -lopencv_core


SOURCES += \
        main.cpp \
        mainwindow.cpp \
        opencv.cpp \
    dialog.cpp \
    chapter1.cpp \
    chapter2.cpp \
    chapter3.cpp \
    chapter4.cpp \
    chapter5.cpp \
    chapter6.cpp \
    chapter7.cpp \
    chapter8.cpp \
    chapter9.cpp \
    chapter10.cpp \
    menu.cpp


HEADERS += \
        mainwindow.h \
    opencv.h \
    dialog.h \
    chapter1.h \
    chapter2.h \
    chapter3.h \
    imwrite.h \
    camshiftdemo.h \
    opticflow.h \
    pointtracking.h \
    create_track_bar.h \
    use_mouse.h \
    chapter4.h \
    draw_image.h \
    chapter5.h \
    use_pointer_access_pixel.h \
    use_iterator_access_pixel.h \
    use_at_access_pixel.h \
    image_blending.h \
    multi_channel_image_blending.h \
    change_contrast_and_bright.h \
    chapter6.h \
    threshold.h \
    chapter7.h \
    chapter8.h \
    convex_hull_2.h \
    approx_poly_dp.h \
    contour_moment.h \
    water_shed.h \
    inpaint.h \
    chapter9.h \
    calc_back_project.h \
    match_template.h \
    chapter10.h \
    harris_corner_detection.h \
    shi_tomasi.h \
    corner_subpix.h

FORMS += \
        mainwindow.ui \
    dialog.ui \
    chapter1.ui \
    chapter2.ui \
    chapter3.ui \
    chapter4.ui \
    chapter5.ui \
    chapter6.ui \
    chapter7.ui \
    chapter8.ui \
    chapter9.ui \
    chapter10.ui

RESOURCES += \
    background.qrc

