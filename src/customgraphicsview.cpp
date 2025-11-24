#include "customgraphicsview.h"

CustomGraphicsView::CustomGraphicsView(QWidget *parent)
    : QGraphicsView(parent), dragging(false), scaleFactor(1.0) {
    setRenderHint(QPainter::Antialiasing);
}

void CustomGraphicsView::setScaleFactor(qreal scaleFactor) {
    this->scaleFactor = scaleFactor;
}

void CustomGraphicsView::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        dragging = true; // 开始拖动
        lastMousePos = event->pos(); // 保存当前位置
        setCursor(Qt::ClosedHandCursor); // 更改鼠标光标
    }
    QGraphicsView::mousePressEvent(event); // 调用基类事件处理
}

void CustomGraphicsView::mouseMoveEvent(QMouseEvent *event) {
    if (dragging) {
        // 计算鼠标移动的距离
        QPoint delta = event->pos() - lastMousePos;
        // 移动视图
        horizontalScrollBar()->setValue(horizontalScrollBar()->value() - delta.x());
        verticalScrollBar()->setValue(verticalScrollBar()->value() - delta.y());
        lastMousePos = event->pos(); // 更新最后的位置
    }
    QGraphicsView::mouseMoveEvent(event); // 调用基类事件处理
}

void CustomGraphicsView::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        dragging = false; // 停止拖动
        unsetCursor(); // 恢复光标
    }
    QGraphicsView::mouseReleaseEvent(event); // 调用基类事件处理
}

void CustomGraphicsView::wheelEvent(QWheelEvent *event) {
    // 缩放因子，调整缩放速度
    qreal factor = (event->angleDelta().y() > 0) ? 1.1 : 0.9;
    scale(factor, factor); // 进行缩放
    QGraphicsView::wheelEvent(event); // 调用基类事件处理
}

