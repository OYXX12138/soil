/*#include "Camera.h"
#include <QCameraInfo>
#include <QMessageBox>
#include <QVBoxLayout>  // 用于布局
#include <QDebug>

Camera::Camera(QWidget *parent)
    : QObject(parent), camera(nullptr), viewfinder(new QCameraViewfinder(parent)), imageCapture(nullptr)
{
}

Camera::~Camera()
{
    if (camera) {
        camera->stop();
        delete camera;
    }
}

void Camera::startCameraInWidget(QWidget *widget)
{
    // 获取可用的相机列表
    QList<QCameraInfo> cameras = QCameraInfo::availableCameras();
    if (cameras.isEmpty()) {
        QMessageBox::critical(widget, "Error", "No camera found");
        return;
    }

    // 初始化相机，使用第一个可用相机
    camera = new QCamera(cameras.first(), widget);

    // 设置 viewfinder
    viewfinder->setMinimumSize(widget->size());  // 设置大小以适应 widget
    viewfinder->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);  // 自动扩展到整个 widget

    // 设置布局
    QVBoxLayout *layout = new QVBoxLayout(widget);
    widget->setLayout(layout);
    layout->addWidget(viewfinder);  // 添加 viewfinder 到 layout 中

    // 启动相机
    camera->setViewfinder(viewfinder);
    camera->start();

    // 调试信息，确认相机是否启动
    if (camera->state() == QCamera::ActiveState) {
        qDebug() << "Camera is active";
    } else {
        qDebug() << "Camera failed to start";
    }
}
*/
