#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>
#include <QImage>
#include <iostream>
#include <QMouseEvent>
#include <QPainter>
#include <QPaintDevice>
#include <QPoint>
#include <QThread>

class Sleeper : public QThread
{
public:
    static void usleep(unsigned long usecs){QThread::usleep(usecs);}
    static void msleep(unsigned long msecs){QThread::msleep(msecs);}
    static void sleep(unsigned long secs){QThread::sleep(secs);}
};

const int height_total = 700;

QPoint MainWindow::orig_to_user (int x, int y){
    int grid_size = ui->grid_size->value();
    int user_x = x;
    int user_y = y;

    int xsgn=(user_x > height_total/2) ? +1 : -1;
    int ysgn=(user_y > height_total/2) ? +1 : -1;

    user_x = (user_x - height_total/2 + grid_size/2*xsgn )/grid_size;
    user_y = (user_y - height_total/2 + grid_size/2*ysgn )/grid_size;

    return QPoint(user_x, user_y);
}


QImage img=QImage(700,700,QImage::Format_RGB888);
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->x_axis->hide();
    ui->y_axis->hide();
    this->to_do = 1;
    connect(ui->frame,SIGNAL(Mouse_Pos()),this,SLOT(Mouse_Pressed()));
    connect(ui->frame,SIGNAL(sendMousePosition(QPoint&)),this,SLOT(showMousePosition(QPoint&)));
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::point(int x,int y)
{
      auto pt = orig_to_user(x,y);
      draw_pt(pt.x(), pt.y(), qRgb(255,255,0));
}



void MainWindow::showMousePosition(QPoint &pos)
{
    auto pt = orig_to_user(pos.x(), pos.y());
    ui->mouse_movement->setText(" X : "+QString::number(pt.x())+", Y : "+QString::number(pt.y()));
}

void MainWindow::Mouse_Pressed()
{
    auto pt = orig_to_user(ui->frame->x, ui->frame->y);
    if (to_do == 5){
        point(ui->frame->x,ui->frame->y);
        if (!list_scan.empty() && list_scan.front()==pt){
            this->to_do = 1;
            _scan_fill(list_scan);
        }
        list_scan.push_back(pt);
    } else if (to_do == 6){
        this->count--;
        list_scan.push_back(QPoint(ui->frame->x, ui->frame->y));
        if (count == 0){
            _boundary_fill(list_scan);
                this->to_do = 1;
        }

    } else if (to_do == 7) {
        _flood_fill(ui->frame->x, ui->frame->y);
        this->to_do = 1;
    } else if (to_do == 8 || to_do == 11) {
        point(ui->frame->x,ui->frame->y);
        polygon.push_back({pt.x(), pt.y()});
        if (polygon.size() >= 2) {
            int n = polygon.size()-1;
            _dda_line_scanfill(polygon[n].first, polygon[n].second, polygon[n-1].first, polygon[n-1].second);
        }
    } else if (to_do == 12) {
        point(ui->frame->x,ui->frame->y);
        polygon.push_back({pt.x(), pt.y()});
        if (polygon.size() % 2 == 0) {
            int n = polygon.size()-1;
            _dda_line_scanfill(polygon[n].first, polygon[n].second, polygon[n-1].first, polygon[n-1].second);
        }
    }

    else {
        point(ui->frame->x,ui->frame->y);
    }
    ui->mouse_pressed->setText(" X : "+QString::number(pt.x())+", Y : "+QString::number(pt.y()));
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
    p1.setX(ui->frame->x);
    p1.setY(ui->frame->y);
}

void MainWindow::on_set_point2_clicked()
{
    p2.setX(ui->frame->x);
    p2.setY(ui->frame->y);
}

//void MainWindow::on_Draw_clicked(){
//{
//    int r0=ui->circle_radius->value();
//    QPainter painter(&img);
//    QPen pen;
//    pen.setWidth(1);
//    pen.setColor(Qt::red);
//    if(ui->draw_circle->isChecked()){
//        p1.setX(ui->frame->x);
//        p1.setY(ui->frame->y);
//        painter.setPen(pen);
//        painter.drawEllipse(p1,r0,r0);
//    }
//    if(ui->draw_line->isChecked()){
//          painter.setPen(Qt::red);
//          painter.drawLine(p1,p2);
//    }
//    ui->frame->setPixmap(QPixmap::fromImage(img));
//}

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
        for (int i = 0; i < height_total; i++){
            for (int j = 0; j < height_total; j++){
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

void MainWindow::draw_pt(int x, int y, QRgb color) {
//    std::cout << "LOOL" << std::endl;
    int grid_size = ui->grid_size->value();
    int midx = x * grid_size + height_total/2;
    int midy = y * grid_size + height_total/2;

    int red_c = ui->red_color_spinbox->value();
    int green_c = ui->green_color_spinbox->value();
    int blue_c = ui->blue_color_spinbox->value();

    color = qRgb(red_c, green_c, blue_c);

    for (int i = midx - grid_size/2; i < midx + grid_size/2; i++){
        for (int j = midy - grid_size/2; j < midy + grid_size/2; j++){
            if (i < height_total && j < height_total && i > 0 && j > 0 ) img.setPixel(i, j, color);
        }
    }
    ui->frame->setPixmap(QPixmap::fromImage(img));
}

#include "line_algos.h"
#include "circle_algos.h"
#include "ellipse_algos.h"
#include "scanfill.h"
#include "seedfill.h"
#include "transformations.h"
#include "beizer.h"
#include"clipping.h"




void MainWindow::on_scanline_2_clicked()
{
    list_scan.resize(0);
    for (auto i : polygon){
        list_scan.push_back({(int)i.first, (int)i.second});
    }

    if (list_scan.size() < 3) return;
    list_scan.push_back(list_scan.front());
    this->xmin = this->xmax = list_scan[0].x();
    this->xmin = this->xmax = list_scan[0].y();

    for(int i=0;i<list_scan.size() -1;i++) {
        xmin = std::min(xmin, list_scan[i].x());
        xmax = std::max(xmax, list_scan[i].x());
        ymin = std::min(ymin, list_scan[i].y());
        ymax = std::max(ymax, list_scan[i].y());
    }

    int s = ymin + 1;
    ui->frame->repaint();
    Sleeper::msleep(50);
    while(s <= ymax) {
        ints(s);
        sort(s);
        s++;
    }
    list_scan.pop_back();
}

void MainWindow::ints(int z){
    int x1, x2, y1, y2, temp;
    c_scan = 0;
    for(int i=0;i<list_scan.size()-1;i++){
        x1=list_scan[i].x();
        y1=list_scan[i].y();
        x2=list_scan[i+1].x();
        y2=list_scan[i+1].y();
        if(y2<y1) {
            temp=x1;
            x1=x2;
            x2=temp;
            temp=y1;
            y1=y2;
            y2=temp;
        }
        if(z<=y2 && z>=y1)
        {
            if((y1-y2)==0)
            x=x1;
            else // used to make changes in x. so that we can fill our polygon after cerain distance
            {
                x=((x2-x1)*(z-y1))/(y2-y1);
                x=x+x1;
            }
            if(x<=xmax && x>=xmin)
            inter[c_scan++]=x;
        }
    }
}

void MainWindow::sort(int z){ //SORT FUNCTION {
    int temp,j,i;

        for(i=0;i<list_scan.size()-1;i++) {
            ui->red_color_spinbox->setValue(0);
            ui->green_color_spinbox->setValue(255);
            ui->blue_color_spinbox->setValue(255);
            _dda_line_scanfill(list_scan[i].x(),list_scan[i].y(),list_scan[i+1].x(),list_scan[i+1].y()); // used to make hollow outlines of a polygon

        }

        for(i=0; i<c_scan;i+=2)
        {
            ui->frame->repaint();
            Sleeper::msleep(50);
            ui->red_color_spinbox->setValue(255);
            ui->green_color_spinbox->setValue(0);
            ui->blue_color_spinbox->setValue(0);
            _dda_line_scanfill(inter[i],z,inter[i+1],z);  // Used to fill the polygon ....
        }
}


void MainWindow::animateClock() {
    int R = 20, lH = R - 7, lM = R - 5, lS = R - 3;
    int k = ui->grid_size->value(), xc = 0, yc = 0;


    QTime curTime = QDateTime::currentDateTime().time();
    int HH, MM, SS;
    HH = curTime.hour() % 12, MM = curTime.minute(), SS = curTime.second();




    QPoint HHand((int)(xc + sin((HH / 12.0) * 2 * M_PI) * lH + 0.5), (int)(yc + cos((HH / 12.0) * 2 * M_PI) * lH + 0.5)),
           MHand((int)(xc + sin((MM / 60.0) * 2 * M_PI) * lM + 0.5), (int)(yc + cos((MM / 60.0) * 2 * M_PI) * lM + 0.5)),
           SHand((int)(xc + sin((SS / 60.0) * 2 * M_PI) * lS + 0.5), (int)(yc + cos((SS / 60.0) * 2 * M_PI) * lS + 0.5));


    while(isClockAnimating)
    {
        // Clearing Screen ...
        for (int i = 0; i < height_total; i++){
            for (int j = 0; j < height_total; j++){
                img.setPixel(j,i,qRgb(0,0,0));
            }
        }

        _polar_circle_clock(xc, yc, R);


        ui->red_color_spinbox->setValue(0);
        ui->green_color_spinbox->setValue(255);
        ui->blue_color_spinbox->setValue(255);
        _dda_line_scanfill(xc, yc, HHand.x(), HHand.y());
        ui->red_color_spinbox->setValue(255);
        ui->green_color_spinbox->setValue(0);
        ui->blue_color_spinbox->setValue(255);
        _dda_line_scanfill(xc, yc, MHand.x(), MHand.y());
        ui->red_color_spinbox->setValue(255);
        ui->green_color_spinbox->setValue(255);
        ui->blue_color_spinbox->setValue(0);
        _dda_line_scanfill(xc, yc, SHand.x(), SHand.y());

        std::cout << HH << ":" << MM << ":" << SS << "  -->  ";
        std::cout << "(" << HHand.x() << "," << HHand.y() << ") : (" << MHand.x() << "," << MHand.y() << ") : (" << SHand.x() << "," << SHand.y() << ")" << std::endl;

        // Advance time
        SS = (SS + 1) % 60;
        if(!SS) MM = (MM + 1) % 60;
        if(!MM) HH = (HH + 1) % 12;

        HHand = {(int)(xc + sin((HH / 12.0) * 2 * M_PI) * lH + 0.5), (int)(yc - cos((HH / 12.0) * 2 * M_PI) * lH + 0.5)},
        MHand = {(int)(xc + sin((MM / 60.0) * 2 * M_PI) * lM + 0.5), (int)(yc - cos((MM / 60.0) * 2 * M_PI) * lM + 0.5)},
        SHand = {(int)(xc + sin((SS / 60.0) * 2 * M_PI) * lS + 0.5), (int)(yc - cos((SS / 60.0) * 2 * M_PI) * lS + 0.5)};

        ui->frame->setPixmap(QPixmap::fromImage(img));
        ui->frame->repaint();
        Sleeper::msleep((int)(1000));
    }

    // Clear Screen at end ...
    for (int i = 0; i < height_total; i++){
        for (int j = 0; j < height_total; j++){
            img.setPixel(j,i,qRgb(0,0,0));
        }
    }
}
void MainWindow::on_clock_clicked()
{
    isClockAnimating = ! isClockAnimating;

    if (isClockAnimating){
        animateClock();

    }


}

