#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>
#include <QImage>
#include <iostream>
#include <QMouseEvent>
#include <QPainter>
#include <QPaintDevice>
#include <QPoint>

const int height_total = 700;

QImage img=QImage(700,700,QImage::Format_RGB888);
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->x_axis->hide();
    ui->y_axis->hide();
    connect(ui->frame,SIGNAL(Mouse_Pos()),this,SLOT(Mouse_Pressed()));
    connect(ui->frame,SIGNAL(sendMousePosition(QPoint&)),this,SLOT(showMousePosition(QPoint&)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::point(int x,int y)
{
    img.setPixel(x,y,qRgb(255,255,0));
    ui->frame->setPixmap(QPixmap::fromImage(img));
}


void MainWindow::showMousePosition(QPoint &pos)
{
    int grid_size = ui->grid_size->value();
    ui->mouse_movement->setText(" X : "+QString::number((pos.x() - height_total/2)/grid_size)+", Y : "+QString::number((pos.y() - height_total/2)/grid_size));
}
void MainWindow::Mouse_Pressed()
{
    int grid_size = ui->grid_size->value();
    ui->mouse_pressed->setText(" X : "+QString::number((ui->frame->x - height_total/2)/grid_size)+", Y : "+QString::number((ui->frame->y - height_total/2)/grid_size));
    point(ui->frame->x,ui->frame->y);
//    ui->x_axis->move(0,ui->frame->y);
//    ui->y_axis->move(ui->frame->x,0);
}

void MainWindow::on_show_axes_clicked()
{
    if(ui->show_axes->isChecked())
    {
        int grid_size = ui->grid_size->value();
        ui->x_axis->setGeometry(QRect(0, height_total/2 - grid_size/2, 700, grid_size));
        ui->y_axis->setGeometry(QRect(height_total/2 - grid_size/2, 0, grid_size, 700));
        ui->x_axis->show();
        ui->y_axis->show();
    }
    else{
        ui->x_axis->hide();
        ui->y_axis->hide();
    }
}
void MainWindow::on_set_point1_clicked()
{
    if(ui->draw_line->isChecked()){
        p1.setX(ui->frame->x);
        p1.setY(ui->frame->y);
    }
}

void MainWindow::on_set_point2_clicked()
{
    if(ui->draw_line->isChecked()){
        p2.setX(ui->frame->x);
        p2.setY(ui->frame->y);
    }
}

void MainWindow::on_Draw_clicked()
{
    int r0=ui->circle_radius->value();
    QPainter painter(&img);
    QPen pen;
    pen.setWidth(1);
    pen.setColor(Qt::red);
    if(ui->draw_circle->isChecked()){
        p1.setX(ui->frame->x);
        p1.setY(ui->frame->y);
        painter.setPen(pen);
        painter.drawEllipse(p1,r0,r0);
    }
    if(ui->draw_line->isChecked()){
        painter.setPen(Qt::red);
        painter.drawLine(p1,p2);
    }
    ui->frame->setPixmap(QPixmap::fromImage(img));
}

void MainWindow::on_pushButton_clicked()
{
    for(int j=0;j<img.height();j++)
    {
        for(int i=0;i<img.width();i++)
        {
            img.setPixel(i,j,qRgb(0,0,0));
        }
    }
    ui->frame->setPixmap(QPixmap::fromImage(img));
}

void MainWindow::on_show_grid_clicked()
{
    int grid_size = ui->grid_size->value();
    int midx = height_total/2;
    std::cout << "Reached";
    if (ui->show_grid->isChecked()){
        for (int i = midx + grid_size/2; i < height_total; i+=grid_size){
            for (int j = 0; j < height_total; j++){
                img.setPixel(i,j,qRgb(255,255,255));
            }
        }
        for (int i = midx + grid_size/2 - grid_size; i > 0; i-=grid_size){
            for (int j = 0; j < height_total; j++){
                img.setPixel(i,j,qRgb(255,255,255));
            }
        }
        for (int i = midx + grid_size/2; i < height_total; i+=grid_size){
            for (int j = 0; j < height_total; j++){
                img.setPixel(j,i,qRgb(255,255,255));
            }
        }
        for (int i = midx + grid_size/2 - grid_size; i > 0; i-=grid_size){
            for (int j = 0; j < height_total; j++){
                img.setPixel(j,i,qRgb(255,255,255));
            }
        }
        ui->frame->setPixmap(QPixmap::fromImage(img));
    } else {
        for (int i = 0; i <= height_total; i++){
            for (int j = 0; j <= height_total; j++){
                img.setPixel(j,i,qRgb(0,0,0));
            }
        }
        ui->frame->setPixmap(QPixmap::fromImage(img));
    }
}


void MainWindow::on_grid_size_valueChanged(int arg1)
{
    int grid_size = ui->grid_size->value();
    int midx = img.height()/2;
    if (ui->show_grid->isChecked()){
        for (int i = 0; i < img.width(); i++){
            for (int j = 0; j < img.height(); j++){
                img.setPixel(j,i,qRgb(0,0,0));
            }
        }
        for (int i = midx + grid_size/2; i < img.width(); i+=grid_size){
            for (int j = 0; j < img.height(); j++){
                img.setPixel(i,j,qRgb(255,255,255));
            }
        }
        for (int i = midx + grid_size/2 - grid_size; i > 0; i-=grid_size){
            for (int j = 0; j < img.height(); j++){
                img.setPixel(i,j,qRgb(255,255,255));
            }
        }
        for (int i = midx + grid_size/2; i < img.width(); i+=grid_size){
            for (int j = 0; j < img.height(); j++){
                img.setPixel(j,i,qRgb(255,255,255));
            }
        }
        for (int i = midx + grid_size/2 - grid_size; i > 0; i-=grid_size){
            for (int j = 0; j < img.height(); j++){
                img.setPixel(j,i,qRgb(255,255,255));
            }
        }
        ui->frame->setPixmap(QPixmap::fromImage(img));
    }

    if (ui->show_axes->isChecked()){
        ui->x_axis->setGeometry(QRect(0, img.height()/2 - grid_size/2, 700, grid_size));
        ui->y_axis->setGeometry(QRect(img.width()/2 - grid_size/2, 0, grid_size, 700));
        ui->x_axis->show();
        ui->y_axis->show();
    }
}
