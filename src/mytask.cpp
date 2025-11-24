#include "mytask.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QCoreApplication>

MyTask::MyTask(QObject *parent) : QObject(parent), currentIndex(0) {}

void MyTask::setFileName(const QString &fileName) {
    this->fileName = fileName;
    QFileInfo fileInfo(fileName);

    isUpdated=false;
    lastModified = fileInfo.lastModified(); // 初始化文件的最后修改时间
    qDebug() << "File name set to:" << fileName; // 打印文件路径
}

QStringList MyTask::getCurrentData() const {
    qDebug()<<"getCurrentData,dataRows.size()"<<dataRows.size();
    if (currentIndex < dataRows.size()) {
        return dataRows[currentIndex];
    } else {
        return QStringList();
    }
}

void MyTask::run() {
    processCSV();
    emit taskFinished();
}

void MyTask::processCSV() {
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "无法打开文件: " << file.errorString();
        return;
    }

    QTextStream in(&file);
    QString headerLine = in.readLine();
    qDebug() << "Header line:" << headerLine;

    dataRows.clear();
    while (!in.atEnd()) {
        QString dataLine = in.readLine().trimmed();  // 去除首尾空格
        if (!dataLine.isEmpty()) {  // 检查行是否为空
            QStringList values = dataLine.split(",");
            if (values.size() >= 1) {
                dataRows.append(values);
//                qDebug()<<"getCurrentData,values"<<values;
            } else {
                qDebug() << "Invalid number of values in CSV";
            }
        }
    }
    qDebug() << "Total rows read:" << dataRows.size();
    qDebug()<<"getCurrentData,dataRows.size()"<<dataRows.size();
    file.close();
    emit newDataAvailable();
}

void MyTask::checkForUpdates() {
    QFileInfo fileInfo(fileName);
    QDateTime lastModified = fileInfo.lastModified();

    if (lastModified > previousModifiedTime) {
        qDebug() << "checkForUpdates1" ;
        previousModifiedTime = lastModified;
        processCSV();

        if (!dataRows.isEmpty()) {
            QStringList newRow = dataRows.last();
            if (!dataExists(newRow)) {
                appendDataToCSV(newRow);
            }
            isUpdated=true;
        }
        else{
            isUpdated=false;
        }

        saveToNewCSV();
        emit newDataAvailable();
    }
}

void MyTask::saveToNewCSV() {
    QString appDirPath = QCoreApplication::applicationDirPath();
    QString newFileName = appDirPath + "/cutton_final.csv";

    QFile file(newFileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qWarning() << "无法打开文件进行写入: " << file.errorString();
        return;
    }

    QTextStream out(&file);
    out << "OC,PP,NN,KK,PH\n"; // 写入标题行

    // 仅在 dataRows 不为空时写入数据
        if (!dataRows.isEmpty()) {
            for (const QStringList& row : dataRows) {
                if (!row.isEmpty()) {  // 检查行是否为空
                    out << row.join(",") << "\n";
                }
            }
        }

    file.close();
    qDebug() << "Data saved to:" << newFileName;
}

void MyTask::appendDataToCSV(const QStringList& newRow) {
    QString appDirPath = QCoreApplication::applicationDirPath();
    QString newFileName = appDirPath + "/cutton_final.csv";

    QFile file(newFileName);
    bool fileExists = file.exists();
    if (!file.open(QIODevice::Append | QIODevice::Text)) {
        qWarning() << "无法打开文件进行写入: " << file.errorString();
        return;
    }

    QTextStream out(&file);
    if (!fileExists) {
        out << "OC,PP,NN,KK,PH\n";
    }

    out << newRow.join(",") << "\n";
    file.close();
    qDebug() << "New data appended to:" << newFileName;
}

bool MyTask::dataExists(const QStringList& newRow) {
    // 检查新数据行是否已经存在
    for (const QStringList& row : dataRows) {
        if (row == newRow) {
            return true;  // 找到相同的行
        }
    }
    return false;  // 新数据行不存在
}
