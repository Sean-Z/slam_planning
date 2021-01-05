QT -= gui

CONFIG += c++11 console
CONFIG -= app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        main.cpp \
        node.cpp \
        plan.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

INCLUDEPATH += D:\opencv\build\include

LIBS += D:\opencv\build_qt\bin\libopencv_core342.dll
LIBS += D:\opencv\build_qt\bin\libopencv_highgui342.dll
LIBS += D:\opencv\build_qt\bin\libopencv_imgcodecs342.dll
LIBS += D:\opencv\build_qt\bin\libopencv_imgproc342.dll
LIBS += D:\opencv\build_qt\bin\libopencv_features2d342.dll
LIBS += D:\opencv\build_qt\bin\libopencv_calib3d342.dll

# more correct variant, how set includepath and libs for mingw
# add system variable: OPENCV_SDK_DIR=D:/opencv/opencv-build/install
# read http://doc.qt.io/qt-5/qmake-variable-reference.html#libs

#INCLUDEPATH += $$(OPENCV_SDK_DIR)/include

#LIBS += -L$$(OPENCV_SDK_DIR)/x86/mingw/lib \
#        -lopencv_core342        \
#        -lopencv_highgui342     \
#        -lopencv_imgcodecs342   \
#        -lopencv_imgproc342     \
#        -lopencv_features2d342  \
#        -lopencv_calib3d342

HEADERS += \
    node.h \
    plan.h

INCLUDEPATH += D:\boost_1_70_0
LIBS += -LD:\boost_1_70_0\stage\lib
