#ifndef CUSTOMGRAPHICSVIEW_H
#define CUSTOMGRAPHICSVIEW_H

#include <QGraphicsView>
#include <QWheelEvent>
#include <QMouseEvent>
#include <QScrollBar>
#include <QPainter>
#include <QGraphicsScene>
#include <QGraphicsRectItem>

class CustomGraphicsView : public QGraphicsView {
    Q_OBJECT

public:
    explicit CustomGraphicsView(QWidget *parent = nullptr);
    void setScaleFactor(qreal scaleFactor);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;

private:
    bool dragging; // 是否正在拖动
    QPoint lastMousePos; // 上一次鼠标位置
    qreal scaleFactor; // 缩放因子
};

#endif // CUSTOMGRAPHICSVIEW_H
