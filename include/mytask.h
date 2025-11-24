#ifndef MYTASK_H
#define MYTASK_H

#include <QObject>
#include <QStringList>
#include <QFileInfo>
#include <QDateTime>
#include <QImage>
#include <QPainter>

class MyTask : public QObject
{
    Q_OBJECT
public:
    explicit MyTask(QObject *parent = nullptr);

   // void saveNewDataToFinalCSV(const QList<QStringList>& newRows);
    void appendDataToCSV(const QStringList& newRow);
    void setFileName(const QString &fileName);
    QStringList getCurrentData() const;
    int currentIndex;
    QList<QStringList> dataRows;
    bool isUpdated;  // 添加这个变量来标记文件是否已更新
    bool dataExists(const QStringList& newRow);
signals:
    void taskFinished();
    void newDataAvailable(); // 新增信号，当有新数据可用时发射

public slots:
    void run();
    void checkForUpdates(); // 新增槽函数，用于检查文件更新
    void saveToNewCSV();
private:
    void processCSV();
    //void saveToDatabase(); // 新增函数，用于保存数据到数据库
    QString fileName;
    QDateTime lastModified;
    QDateTime previousModifiedTime;  // 添加此变量

};

#endif // MYTASK_H

/******只显示第一行*******/
/*#ifndef MYTASK_H
#define MYTASK_H

#include <QObject>
#include <QStringList>

class MyTask : public QObject
{
    Q_OBJECT
public:
    explicit MyTask(QObject *parent = nullptr);

    void setFileName(const QString &fileName);
    QStringList getCurrentData() const;
    double getN() const;
    double getP() const;
    double getK() const;
    double getOC() const;
    double getPH() const;
    double getFrequency() const;

signals:
    void taskFinished();

public slots:
    void run();

private:
    QString fileName;
    double N, P, K, OC, PH, frequency;

    void processCSV();
};

#endif // MYTASK_H*/
