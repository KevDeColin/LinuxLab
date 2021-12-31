#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#define HIGHRESO 1
#define LOWRESO 0
#include <QMainWindow>
#include<string>
#include<QDateTime>
#include"mediaInfo.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    friend void addQuickState(const QString& state,MainWindow*);
public:
    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void mousePressEvent(QMouseEvent *event);
    void addQuickState(const QString& state);
    void resetTime();
    void addLog(const QString&);
    void savePic(const mediaInfo&,int frameId);
public slots:
    void on_Xbutton_clicked();
    void on_huidu_clicked();
    void on_canny_clicked();
    void on_highreso_clicked();
    void on_lowreso_clicked();
    void on_chooseFile_clicked();
    void on_transform_clicked();
    void on_logEdit_textChanged();
private:
    int reso;
    int PixelSize=10;
    std::string filePath;
    int option=1;
    QPoint dragPosition;
    Ui::MainWindow *ui;
    mediaInfo func();
    bool transformed =false;
    int fileType =0;//1代表图片,2代表视频
    QDateTime current_date_time =QDateTime::currentDateTime();
    QString current_date;
    QString tmpPath;
    QString saveAs="";
};
#endif // MAINWINDOW_H
