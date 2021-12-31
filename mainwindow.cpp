#include "mainwindow.h"
#include"play.h"
#include "ui_LinuxFinal6666.h"
#include"cannyDraw.h"
#include"cannyReader.h"

#include<opencv2/imgproc/types_c.h>

#include "mediaInfo.h"
#include <QApplication>
#include <QMouseEvent>
#include<QMessageBox>
#include<QFileDialog>
#include<QPainter>
#include<iostream>
#include<stdlib.h>
#include<QFile>
#include <opencv2/opencv.hpp>
#include<opencv2/imgproc/imgproc.hpp>
extern int factor;
extern MainWindow* window;
extern QApplication* app;
cv::Size aSize;
void image_to_video(const QString dirPath,const QString&videoName,int size,double fps){
    cv::Mat tmp;
    //
    //0x21
    std::cout<<fps<<" ";
    //fps=30;
    VideoWriter output(videoName.toStdString(),VideoWriter::fourcc('M', 'J', 'P', 'G'),fps,aSize, true);
    if(!output.isOpened()){
        std::cout<<"发生错误";
        return ;
    }
    std::string outputPath = dirPath.toStdString();
    std::string picName;
    for(int i =0;i<size;++i){
        picName = outputPath + "/"+std::to_string(i)+".png";
        tmp = cv::imread(picName);
        output<<tmp;
        //imshow("Canny Draw Video Player", tmp);

        app->processEvents();
        addQuickState(QString::fromStdString("正在合并:"+std::to_string(i)+"/"+std::to_string(size)),window);
    }
    addQuickState("",window);
}
void MainWindow::addLog(const QString&s){
    resetTime();
    ui->logEdit->setText(ui->logEdit->toPlainText()+"["+current_date+"]"+s+'\n');
}
void MainWindow::resetTime(){
    current_date_time =QDateTime::currentDateTime();
    current_date=current_date_time.toString("hh:mm:ss");
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    ,reso(HIGHRESO)
    , ui(new Ui::MainWindow)
{

    tmpPath = QDir::currentPath()+"/tmp";
    ui->setupUi(this);

    ui->Xbutton->installEventFilter(this);
    QFile file(":/666.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet = file.readAll();
    file.close();
    this->setStyleSheet(styleSheet);
    resetTime();
    ui->logEdit->setText("["+current_date+"]程序运行\n");
    ui->logEdit->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->logEdit->setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_Xbutton_clicked(){
    if(!ui->quickState->text().isEmpty())
        return ;
    QDir dir(tmpPath);
    if(dir.exists()){
         dir.removeRecursively();
    }
    this->close();
}
void MainWindow::on_huidu_clicked(){
    if(option!=1&&ui->quickState->text()=="")
    addLog("工作模式:灰度");
    option=1;
}
void MainWindow::on_canny_clicked(){
    if(option!=2&&ui->quickState->text()=="")
    addLog("工作模式:Canny");
    option=2;
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{

    dragPosition=event->globalPos()-frameGeometry().topLeft();
}
void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    move(event->globalPos()-dragPosition);
}
void MainWindow::on_chooseFile_clicked(){
    QString tmp=QFileDialog::getOpenFileName(this,"打开文件","","images(*.png *.jpeg *.bmp);;video files(*.avi *.mp4 *.wmv);;");
    filePath=tmp.toStdString();
    if(filePath!=""){
           if(tmp.contains(".png")||tmp.contains(".jpeg")||tmp.contains(".bmp")||tmp.contains(".jpg")){
               factor=1;
               fileType=1;}
           else if(tmp.contains(".avi")||tmp.contains(".mp4")||tmp.contains(".wmv")){
               factor=4;
            fileType=2;
           }
           addLog("选中文件:"+tmp);
        saveAs="";}
    else{
        addLog("未选中文件");
    }
}
mediaInfo MainWindow::func(){
    mediaInfo info;
    if(option==1){
        play transformer{filePath};
        transformer.startpaly();
        info=transformer.getpages();
    }
    return info;
}
void MainWindow::on_transform_clicked(){

    if(filePath==""){
        QMessageBox::critical(this,  "","未选择文件", QMessageBox::Yes, QMessageBox::Yes);
       addLog("由于未选择文件导致转换终止");
        return;
    }
    addLog("转换工作已开始");
    mediaInfo info = func();
    addLog("转换工作已完成");
    transformed=1;
    QMessageBox::information(this,  "666","工作已完成，请选择保存路径", QMessageBox::Yes, QMessageBox::Yes);
    if(fileType==1)
    saveAs=QFileDialog::getSaveFileName(this,"保存到","" ,"images(*.png)");
    else if(fileType==2){
        saveAs=QFileDialog::getSaveFileName(this,"保存到","" ,"images(*.avi)");
    }
    if(saveAs!=""){
        QString videoSaveAs=saveAs;
        //save the file
        if(fileType==1){
            if(!saveAs.contains(".png"))
                saveAs+=".png";
            //savePic
            if(option==1)
            savePic(info,0);
            else
                CannyReader::readCannyPath(filePath,saveAs.toStdString(),reso);
        }
        else if(fileType==2){
            if(!saveAs.contains(".avi"))
                saveAs+=".avi";
            videoSaveAs=saveAs;
           if(option!=1){
                CannyReader::readCannyPath(filePath,saveAs.toStdString(),reso);
               addLog("文件已保存"+saveAs);
               return ;
           }
           QDir dir(tmpPath);
           if(!dir.exists()){
                if(!dir.mkdir(tmpPath)){
                    QMessageBox::critical(this,"错误","创建临时文件夹错误");
                    addLog("创建临时文件夹出错,任务已终止");
                }
           }
           for(int i =0;i<info.frame.size();++i){
               //完成临时图片的保存
               std::string item= std::to_string(i);
                saveAs=tmpPath+"/"+QString::fromStdString(item)+".png";

                app->processEvents();
                addQuickState(QString::fromStdString("正在存入:"+std::to_string(i)+"/"+std::to_string(info.frame.size())));
                savePic(info,i);
           }
           addQuickState("");
           //调用ffmpeg合并
           addLog("正在将临时文件合并成视频");
           image_to_video(tmpPath,videoSaveAs,info.frame.size(),info.fps);

          addQuickState("");

           //清除临时图片
           dir.removeRecursively();
        }
        addLog("文件已保存");
    }
    else{
        addLog("未选择保存路径");
    }
}
void MainWindow::on_logEdit_textChanged(){
    ui->logEdit->moveCursor(QTextCursor::End);
}
void MainWindow::savePic(const mediaInfo & info,int frameId){
    QString strToWrite = QString::fromStdString(info.frame[frameId]);
    QFont font;
    //linux字体
    //font.setFamily("Consolas");
    //设置显示字体的大小
    font.setPixelSize(PixelSize);
    QFontMetrics fm(font);
    int charWidth = fm.width(QString::fromStdString(info.frame[frameId]))/info.row;
    int charHeight =fm.lineSpacing()*info.row;
    aSize = cv::Size(charWidth,charHeight);
    //指定图片大小为字体的大小
    QSize size(charWidth, charHeight);
    QImage image(size,QImage::Format_Mono );
    image.fill(qRgb(255, 255, 255));
    //为这个QImage构造一个QPainter
    QPainter painter(&image);
    QPen pen = painter.pen();
    pen.setColor( QColor(0, 0, 0));
    painter.setPen(pen);
    painter.setFont(font);
    //将Hello写在Image的左上角
    painter.drawText(image.rect(), Qt::AlignLeft|Qt::AlignTop, strToWrite);
    image.save(saveAs, "PNG", 100);
}
void MainWindow::on_highreso_clicked(){
    if(reso==HIGHRESO||ui->quickState->text()!="")
        return;
    reso=HIGHRESO;
    addLog("精细度:高");
    if(fileType==1){

        factor=1;
    }
    else{
        factor=4;
    }
}
void MainWindow::on_lowreso_clicked(){
    if(reso==LOWRESO||ui->quickState->text()!="")
        return;
    reso=LOWRESO;
    addLog("精细度:低");
    if(fileType==1){
      factor = 4;
    }
    else{
       factor = 8;
    }
}
void MainWindow::addQuickState(const QString& state)
{
    ui->quickState->setText(state);
}
void addQuickState(const QString& state,MainWindow*window){
    window->addQuickState(state);
}
