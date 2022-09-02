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
//    img.setPixel(x,y,qRgb(255,255,0));
//    ui->frame->setPixmap(QPixmap::fromImage(img));
}



void MainWindow::showMousePosition(QPoint &pos)
{
    auto pt = orig_to_user(pos.x(), pos.y());
    ui->mouse_movement->setText(" X : "+QString::number(pt.x())+", Y : "+QString::number(pt.y()));
}

void MainWindow::Mouse_Pressed()
{
    auto pt = orig_to_user(ui->frame->x, ui->frame->y);
    ui->mouse_pressed->setText(" X : "+QString::number(pt.x())+", Y : "+QString::number(pt.y()));
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
          auto pa = orig_to_user(p1.x(), p1.y());
          auto pb = orig_to_user(p2.x(), p2.y());
          int x1 = pa.x();
          int y1 = pa.y();
          int x2 = pb.x();
          int y2 = pb.y();

          _dda_line(x1, y1, x2, y2);
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
    int grid_size = ui->grid_size->value();
    int midx = x * grid_size + height_total/2;
    int midy = y * grid_size + height_total/2;

    for (int i = midx - grid_size/2; i <= midx + grid_size/2; i++){
        for (int j = midy - grid_size/2; j <= midy + grid_size/2; j++){
            if (i < height_total && j < height_total && i > 0 && j > 0 ) img.setPixel(i, j, color);
        }
    }
    ui->frame->setPixmap(QPixmap::fromImage(img));
}

void MainWindow::_dda_line(int x1, int y1, int x2, int y2) {
    float dx, dy;
    float x, y;
    float Dx, Dy;

    // Base Case
    if(x1 == x2 && y1 == y2){
        draw_pt(x1, y1, qRgb(0, 255, 0));
        return;
    }
    dx = x2 - x1;  // total span in x
    dy = y2 - y1;  // total span in y
    x = x1;
    y = y1;

    // incremental steps in x and y
    if(abs(dx) > abs(dy))
    {
        Dx = (dx > 0)? 1: -1;
        Dy = dy / abs(dx);
    }
    else
    {
        Dx = dx / abs(dy);
        Dy = (dy > 0)? 1: -1;
    }

    // to get the number of iterations correctly
    if(dx < 0) dx = -dx;
    if(dy < 0) dy = -dy;

    int ix, iy, end = (dx > dy)? dx: dy;  // integer x and y co-ordinates
    for(int k = 0; k <= end; k++)
    {
        ix = (x == 0) ? 0 : (int)(x + 0.5*abs(x)/x);
        iy = (y == 0) ? 0 : (int)(y + 0.5*abs(y)/y);
        draw_pt(ix, iy, qRgb(0, 255, 0));
        x += Dx, y += Dy;
    }
}

void MainWindow::_dda_line_debug(int x1, int y1, int x2, int y2) {
    float dx, dy;
    float x, y;
    float Dx, Dy;
    if(x1 == x2 && y1 == y2){
        return;
    }
    dx = x2 - x1;  // total span in x
    dy = y2 - y1;  // total span in y
    x = x1;
    y = y1;

    if(abs(dx) > abs(dy)) {
        Dx = (dx > 0)? 1: -1;
        Dy = dy / abs(dx);
    }
    else
    {
        Dx = dx / abs(dy);
        Dy = (dy > 0)? 1: -1;
    }

    if(dx < 0) dx = -dx;
    if(dy < 0) dy = -dy;

    int ix, iy, end = (dx > dy)? dx: dy;
    for(int k = 0; k <= end; k++) {
        ix = (x == 0) ? 0 : (int)(x + 0.5*abs(x)/x);
        iy = (y == 0) ? 0 : (int)(y + 0.5*abs(y)/y);
        x += Dx, y += Dy;
    }
}


void MainWindow::_bresenham(int x1, int y1, int x2, int y2) {
    if(y1 == y2)
        {
            int start = std::min(x1, x2), end = std::max(x1, x2);
            for(int i = start; i <= end; i++) draw_pt(i, y1, qRgb(255,255,0));
            return;
        }

        // Case for vertical line
        if(x1 == x2)
        {
            int start = std::min(y1, y2), end = std::max(y1, y2);
            for(int j = start; j <= end; j++) draw_pt(x1, j, qRgb(255,255,0));
            return;
        }

        int dx = x2 - x1, dy = y2 - y1, p;

        // Case for |m| <= 1
        if(abs(dy) <= abs(dx))
        {
            if(x1 > x2) std::swap(x1, x2), std::swap(y1, y2), dx = -dx, dy = -dy;

            int j = (dy > 0)? y1: (y1 + 1);
            p = 2 * dy - dx;
            draw_pt(x1, y1, qRgb(255,255,0));  // Plotting initial point ...
            for(int i = x1 + 1; i <= x2; i++)
            {
                if(dy > 0)
                {
                    if(p < 0) p += 2 * dy;
                    else p += 2 * dy - 2 * dx, j++;
                }
                else
                {
                    if(p > 0) p += 2 * dy;
                    else p += 2 * dy + 2 * dx, j--;
                }

                draw_pt(i, j, qRgb(255,255,0));
            }
        }

        // Case for |m| > 1
        else
        {
            if(y1 > y2) std::swap(x1, x2), std::swap(y1, y2), dx = -dx, dy = -dy;

            int i = (dx > 0)? x1: (x1 + 1);
            p = 2 * dx - dy;
            draw_pt(x1, y1, qRgb(255,255,0));  // Plotting initial point ...
            for(int j = y1 + 1; j <= y2; j++)
            {
                if(dx > 0)
                {
                    if(p < 0) p += 2 * dx;
                    else p += 2 * dx - 2 * dy, i++;
                }
                else
                {
                    if(p > 0) p += 2 * dx;
                    else p += 2 * dx + 2 * dy, i--;
                }

                draw_pt(i, j, qRgb(255,255,0));
            }
        }

}

void MainWindow::_bresenham_debug(int x1, int y1, int x2, int y2) {
        if(y1 == y2) {
            int start = std::min(x1, x2), end = std::max(x1, x2);
            for(int i = start; i <= end; i++);
            return;
        }

        if(x1 == x2) {
            int start = std::min(y1, y2), end = std::max(y1, y2);
            for(int j = start; j <= end; j++);
            return;
        }

        int dx = x2 - x1, dy = y2 - y1, p;

        // Case for |m| <= 1
        if(abs(dy) <= abs(dx)) {
            if(x1 > x2) std::swap(x1, x2), std::swap(y1, y2), dx = -dx, dy = -dy;

            int j = (dy > 0)? y1: (y1 + 1);
            p = 2 * dy - dx;
            for(int i = x1 + 1; i <= x2; i++) {
                if(dy > 0) {
                    if(p < 0) p += 2 * dy;
                    else p += 2 * dy - 2 * dx, j++;
                }
                else {
                    if(p > 0) p += 2 * dy;
                    else p += 2 * dy + 2 * dx, j--;
                }
            }
        }

        // Case for |m| > 1
        else {
            if(y1 > y2) std::swap(x1, x2), std::swap(y1, y2), dx = -dx, dy = -dy;

            int i = (dx > 0)? x1: (x1 + 1);
            p = 2 * dx - dy;
            for(int j = y1 + 1; j <= y2; j++) {
                if(dx > 0) {
                    if(p < 0) p += 2 * dx;
                    else p += 2 * dx - 2 * dy, i++;
                }
                else {
                    if(p > 0) p += 2 * dx;
                    else p += 2 * dx + 2 * dy, i--;
                }
            }
        }

}


void MainWindow::on_dda_clicked()
{
    if(ui->draw_line->isChecked()){
          auto pa = orig_to_user(p1.x(), p1.y());
          auto pb = orig_to_user(p2.x(), p2.y());
          int x1 = pa.x();
          int y1 = pa.y();
          int x2 = pb.x();
          int y2 = pb.y();
          _dda_line(x1, y1, x2, y2);

          timer.start();
          _dda_line_debug(x1, y1, x2, y2);
          auto time = timer.nsecsElapsed();
          ui->time_show->setText(QString::number(time));
    }
}


void MainWindow::on_bresenham_line_clicked()
{
    if(ui->draw_line->isChecked()){
          auto pa = orig_to_user(p1.x(), p1.y());
          auto pb = orig_to_user(p2.x(), p2.y());
          int x1 = pa.x();
          int y1 = pa.y();
          int x2 = pb.x();
          int y2 = pb.y();
          _bresenham(x1, y1, x2, y2);

          timer.start();
          _bresenham_debug(x1, y1, x2, y2);
          auto time = timer.nsecsElapsed();
          ui->time_show->setText(QString::number(time));
    }
}

