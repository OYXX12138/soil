/*#ifndef CAMERA_H
#define CAMERA_H

#include <QObject>
#include <QWidget>        // QWidget 头文件
#include <QCamera>        // QCamera 头文件
#include <QCameraViewfinder>  // QCameraViewfinder 头文件
#include <QCameraImageCapture>  // QCameraImageCapture 头文件

class Camera : public QObject
{
    Q_OBJECT
public:
    explicit Camera(QWidget *parent = nullptr); // 构造函数声明
    ~Camera();

    void startCameraInWidget(QWidget *widget);  // 在 widget 中显示相机

private:
    QCamera *camera;
    QCameraViewfinder *viewfinder;
    QCameraImageCapture *imageCapture;
};

#endif // CAMERA_H*/
