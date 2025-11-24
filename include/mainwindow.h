#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include <QTimer>
#include <QImage>  // 添加 QImage 头文件
#include <QPainter>  // 添加 QPainter 头文件
#include <QDateTime>
#include <QSerialPort>
#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QFrame>
#include <QScrollArea>
#include <QSet>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QPointF>
#include <QPushButton>
#include <QWheelEvent>
#include <QMouseEvent>

#include <QGeoPositionInfoSource>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUrl>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QPainter>
#include <QGraphicsScene>
#include <QGraphicsRectItem>

#include <QtMqtt/qmqttclient.h>
#include <QScrollBar>
#include "camera.h"

namespace Ui {
class MainWindow;
}

class MyTask; // 前向声明

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();   

private slots:
    void on_btnStart_clicked();
    void on_btnPause_clicked();
    void handleTaskFinished();
    void updateData();
    void onNewDataAvailable(); // 新增槽函数，当有新数据可用时调用
    void checkForFileUpdates(); // 新增槽函数，用于检查文件更新
    void onRowClicked(int row, int column);
    // 新增槽函数，用于切换显示不同的浓度信息
    void showN();
    void showP();
    void showK();
    void updateDateTime(); // 更新日期和时间的方法
    void readSerialData();
    void on_btnDelete_clicked();
    void startDrawing();
    void updateTrajectory(const QList<QPointF>& points);
    //void connectSuccessSlot();
    void recvMessageSlot(const QByteArray &ba, const QMqttTopicName &topic);
    //void on_subButton_clicked();
    void onClientConnected();
    //void on_btnCamera_clicked();  // 点击按钮时打开相机窗口

private:
    void resetTask();
    void updateMap(); // 更新地图
    void openSerial();
    void deleteRowFromCSV();
    void deleteRowFromCSV(const QStringList &rowData);
    int selectedRow;  // 用于存储当前选中的行号
    void saveDataToCSV(const QString &data);
    void deleteRowFromCSV(int rowToDelete);
    void loadCSVToTable();
//    void updateDataTable(const QString &data);
    void saveDataToCSV(double nValue, double pValue, double kValue, double jValue, double wValue);
//    void sendToserial();
    void resizeEvent(QResizeEvent *event);
    int getColumnForCurrentSubstance();
    void updateCSVCell(int row, int column, const QString& newValue);
    void parseRMC(const QString &data);  // 解析 GNRMC 语句
    void openPosition();
    void readPositionData();
    void parseAndSaveData(const QString &data);
   // void drawMap();
    void setupMapView();
    void drawTrajectoryWithColor(const QList<QStringList>& dataRows, const QString& currentSubstance,
                                             double lowerLimit1, double lowerLimit2, double lowerLimit3, double upperLimit3);
    void initMapView();

    QGraphicsView* view;
    QString convertToDegrees(const QString &raw, const QString &direction); // 经纬度转换
    Ui::MainWindow *ui;
    QThread *taskThread;
    MyTask *task;
    QTimer *dataUpdateTimer;
    QTimer *fileCheckTimer;
    QImage mapImage;
    QPainter painter;
    QTimer *dateTimeUpdateTimer; // 定时器用于更新日期和时间
    QSerialPort *m_pSerial;
    QSerialPort *m_pPosition;
    QSet<QString> receivedDataSet;
    QString accumulatedData;  // 用于存储接收到的完整数据
    QList<QStringList> cachedData;// 用于缓存CSV数据
    QMqttClient *client;
    QGraphicsScene *scene;      // 场景
    bool dragging;              // 是否拖动
    QPoint lastMousePos;       // 上一次鼠标位置
    QPushButton *btnCamera;  // 相机按钮
    QWidget *cameraWidget;    // 用于显示相机画面的 widget
    //Camera *cameraModule;     // Camera 模块实例

    int mapWidth;
    int mapHeight;

    QString currentSubstance;  // 新增成员变量
    // 新增浓度范围成员变量
        const double lowerLimit1 = 2;
        const double lowerLimit2 = 4;
        const double lowerLimit3 = 6;
        const double upperLimit3 = 8;

protected:
    void mousePressEvent(QMouseEvent *event) override;    // 拖动开始
    void mouseMoveEvent(QMouseEvent *event) override;     // 拖动中
    void mouseReleaseEvent(QMouseEvent *event) override;  // 拖动结束
    void wheelEvent(QWheelEvent *event) override;         // 缩放
};

#endif // MAINWINDOW_H


/*#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include "mytask.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnStart_clicked();
    void handleTaskFinished();

private:
    Ui::MainWindow *ui;
    QThread *taskThread;
    MyTask *task;

    void resetTask(); // 新增的重置任务函数
    void readCSVAndUpdateUI(const QString &filePath);
};

#endif // MAINWINDOW_H*/
