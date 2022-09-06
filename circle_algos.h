#include<cmath>
#include<cstdlib>
#ifndef CIRCLE_ALGOS_H
#define CIRCLE_ALGOS_H



void MainWindow::on_polar_circle_clicked()
{
    auto pa = orig_to_user(p1.x(), p1.y());
    auto r = ui->circle_radius->value();
    int x1 = pa.x();
    int y1 = pa.y();
    _polar_circle(x1, y1, r);
    timer.start();
    _polar_circle_debug(x1, y1, r);
    auto time = timer.nsecsElapsed();
    ui->time_show->setText(QString::number(time));
}

void MainWindow::_polar_circle(int xc, int yc, int r){
    if ( r <= 0 ) return;
    else {
        std::cout << "r" << std::endl;
        for (int i = 0; ((float)i)/r <= 0.79; i++){
            float theta = ((float)i)/r;
            float xa = r*std::cos(theta);
            float ya = r*std::sin(theta);
            int ixa = (xa == 0) ? 0 : (int)(xa + 0.5*abs(xa)/xa);
            int iya = (ya == 0) ? 0 : (int)(ya + 0.5*abs(ya)/ya);
            draw_pt(xc+ixa, yc+iya, qRgb(0, 0, 255));
            draw_pt(xc-ixa, yc+iya, qRgb(0, 0, 255));
            draw_pt(xc+ixa, yc-iya, qRgb(0, 0, 255));
            draw_pt(xc-ixa, yc-iya, qRgb(0, 0, 255));
            draw_pt(xc+iya, yc+ixa, qRgb(0, 0, 255));
            draw_pt(xc-iya, yc+ixa, qRgb(0, 0, 255));
            draw_pt(xc+iya, yc-ixa, qRgb(0, 0, 255));
            draw_pt(xc-iya, yc-ixa, qRgb(0, 0, 255));
            ui->frame->repaint();
            Sleeper::msleep(50);
        }
        ui->frame->setPixmap(QPixmap::fromImage(img));
    }
}

void MainWindow::_polar_circle_debug(int xc, int yc, int r){
    if ( r <= 0 ) return;
    else {
        std::cout << "r" << std::endl;
        for (int i = 0; ((float)i)/r <= 6.3; i++){
            float theta = ((float)i)/r;
            float x = xc + r*std::cos(theta);
            float y = yc + r*std::sin(theta);
            int ix = (x == 0) ? 0 : (int)(x + 0.5*abs(x)/x);
            int iy = (y == 0) ? 0 : (int)(y + 0.5*abs(y)/y);
        }
    }
}

void MainWindow::on_bresenham_cicle_clicked()
{
    auto pa = orig_to_user(p1.x(), p1.y());
    auto r = ui->circle_radius->value();
    int x1 = pa.x();
    int y1 = pa.y();
    _bresenham_circle(x1, y1, r);
    timer.start();
    _bresenham_circle_debug(x1, y1, r);
    auto time = timer.nsecsElapsed();
    ui->time_show->setText(QString::number(time));
}

void MainWindow::_bresenham_circle(int xc, int yc, int r){
    if ( r <= 0 ) return;
    int x = 0;
    int y = r;
    int p = 1 - r;
    draw_pt(xc+r, yc, qRgb(0, 255, 255));
    draw_pt(xc, yc+r, qRgb(0, 255, 255));
    draw_pt(xc-r, yc, qRgb(0, 255, 255));
    draw_pt(xc, yc-r, qRgb(0, 255, 255));
    ui->frame->repaint();
    Sleeper::msleep(50);
    ui->frame->setPixmap(QPixmap::fromImage(img));
    while (x < y) {
        if (p < 0) {
            x += 1;
            p = p + 2*x + 1;
        } else {
            x += 1;
            y -= 1;
            p = p + 2*x + 1 - 2*y;
        }
        draw_pt(x+xc, y+yc, qRgb(0, 255, 255));
        draw_pt(x+xc, -y+yc, qRgb(0, 255, 255));
        draw_pt(-x+xc, y+yc, qRgb(0, 255, 255));
        draw_pt(-x+xc, -y+yc, qRgb(0, 255, 255));
        draw_pt(y+xc, x+yc, qRgb(0, 255, 255));
        draw_pt(y+xc, -x+yc, qRgb(0, 255, 255));
        draw_pt(-y+xc, x+yc, qRgb(0, 255, 255));
        draw_pt(-y+xc, -x+yc, qRgb(0, 255, 255));
        ui->frame->repaint();
        Sleeper::msleep(50);
        ui->frame->setPixmap(QPixmap::fromImage(img));
    }
    ui->frame->setPixmap(QPixmap::fromImage(img));
}

void MainWindow::_bresenham_circle_debug(int xc, int yc, int r){
    if ( r <= 0 ) return;
    int x = 0;
    int y = r;
    int p = 1 - r;
    while (x < y) {
        if (p < 0) {
            x += 1;
            p = p + 2*x + 1;
        } else {
            x += 1;
            y -= 1;
            p = p + 2*x + 1 - 2*y;
        }
    }
}


#endif // CIRCLE_ALGOS_H
