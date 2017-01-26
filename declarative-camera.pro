TEMPLATE=app
TARGET=declarative-camera

QT += quick qml multimedia widgets

linux:!android {
    INCLUDEPATH += /usr/local/include
    LIBS += -L/usr/local/lib
    LIBS += -lopencv_shape -lopencv_stitching -lopencv_objdetect\
    -lopencv_superres -lopencv_videostab -lopencv_calib3d -lopencv_features2d\
    -lopencv_highgui -lopencv_videoio -lopencv_imgcodecs -lopencv_video\
    -lopencv_photo -lopencv_ml -lopencv_imgproc -lopencv_flann -lopencv_core
}

android {
    QT += androidextras
    INCLUDEPATH += /home/apps/OpenCV-android-sdk/sdk/native/jni/include
    LIBS += -L/home/apps/OpenCV-android-sdk/sdk/native/3rdparty/libs/armeabi-v7a\
        -L/home/apps/OpenCV-android-sdk/sdk/native/libs/armeabi-v7a
    LIBS += -lopencv_calib3d -lopencv_flann -lopencv_imgproc -lopencv_objdetect -lopencv_stitching -lopencv_videoio\
        -lopencv_core -lopencv_highgui -lopencv_photo -lopencv_superres -lopencv_videostab\
        -lopencv_features2d -lopencv_imgcodecs -lopencv_ml -lopencv_shape -lopencv_video\
        -lIlmImf -llibjasper -llibjpeg -llibpng -llibtiff -llibwebp -ltbb -ltegra_hal
#-lopencv_androidcamera -lopencv_contrib -lopencv_java -lopencv_legacy -lopencv_ocl -lopencv_ts
}

SOURCES += qmlcamera.cpp \
    mainqml.cpp \
    imageprovider.cpp
RESOURCES += declarative-camera.qrc

QMAKE_INFO_PLIST = Info.plist

target.path = $$[QT_INSTALL_EXAMPLES]/multimedia/declarative-camera
INSTALLS += target

HEADERS += \
    mainqml.h \
    imageprovider.h

DISTFILES += \
    android/AndroidManifest.xml \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradlew \
    android/res/values/libs.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew.bat

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android

