QT       += core gui
#windows
INCLUDEPATH += D:\OPENCV4\opencv\opencv-build\install\include
#INCLUDEPATH += /usr/local/include \
#                /usr/local/include/opencv
#                /usr/local/include/opencv2

#windows
LIBS += D:\OPENCV4\opencv\opencv-build\install\x64\mingw\lib\libopencv_*.a
LIBS += D:\OPENCV4\opencv\opencv-build\lib\libopencv_*.a
#LIBS += /usr/local/lib/libopencv_* \


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ImageTransformer.cpp \
    cannyDraw.cpp \
    cannyReader.cpp \
    main.cpp \
    mainwindow.cpp \
    play.cpp

HEADERS += \
    ImageTransformer.h \
    cannyDraw.h \
    cannyReader.h \
    mainwindow.h \
    mediaInfo.h \
    play.h

FORMS += \
    LinuxFinal6666.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=

RESOURCES += \
    666.qrc
