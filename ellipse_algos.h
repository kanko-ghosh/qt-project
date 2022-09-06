#ifndef ELLIPSE_ALGOS_H
#define ELLIPSE_ALGOS_H


void MainWindow::on_polar_ellipse_clicked()
{
    auto pa = orig_to_user(p1.x(), p1.y());
    auto rx = ui->radius_x->value();
    auto ry = ui->radius_y->value();
    int x1 = pa.x();
    int y1 = pa.y();
    _polar_ellipse(x1, y1, rx, ry);
    timer.start();
    _polar_ellipse_debug(x1, y1, rx, ry);
    auto time = timer.nsecsElapsed();
    ui->time_show->setText(QString::number(time));
}


void MainWindow::_polar_ellipse(int xc, int yc, int rx, int ry){
    int r_l = std::max(rx, ry);
//    for (int i = 0; ((float)i)/r_l <= 6.3; i++){
//        float theta = ((float)i)/r_l;
//        float x = xc + rx*std::cos(theta);
//        float y = yc + ry*std::sin(theta);
//        int ix = (x == 0) ? 0 : (int)(x + 0.5*abs(x)/x);
//        int iy = (y == 0) ? 0 : (int)(y + 0.5*abs(y)/y);
//        draw_pt(ix, iy, qRgb(0, 255, 255));
//        ui->frame->repaint();
//        Sleeper::msleep(50);
//    }
        for (int i = 0; ((float)i)/r_l <= 1.7; i++){
            float theta = ((float)i)/r_l;
            float xa = rx*std::cos(theta);
            float ya = ry*std::sin(theta);
            int ixa = (xa == 0) ? 0 : (int)(xa + 0.5*abs(xa)/xa);
            int iya = (ya == 0) ? 0 : (int)(ya + 0.5*abs(ya)/ya);
            draw_pt(xc+ixa, yc+iya, qRgb(0, 255, 255));
            draw_pt(xc-ixa, yc+iya, qRgb(0, 255, 255));
            draw_pt(xc+ixa, yc-iya, qRgb(0, 255, 255));
            draw_pt(xc-ixa, yc-iya, qRgb(0, 255, 255));
            ui->frame->repaint();
            Sleeper::msleep(50);
        }
}

void MainWindow::_polar_ellipse_debug(int xc, int yc, int rx, int ry){
    int r_l = std::max(rx, ry);
    std::cout << "r" << std::endl;
    for (int i = 0; ((float)i)/r_l <= 6.3; i++){
        float theta = ((float)i)/r_l;
        float x = xc + rx*std::cos(theta);
        float y = yc + ry*std::sin(theta);
        int ix = (x == 0) ? 0 : (int)(x + 0.5*abs(x)/x);
        int iy = (y == 0) ? 0 : (int)(y + 0.5*abs(y)/y);
    }
}

void MainWindow::on_bresenham_ellipse_clicked()
{
    auto pa = orig_to_user(p1.x(), p1.y());
    auto rx = ui->radius_x->value();
    auto ry = ui->radius_y->value();
    int x1 = pa.x();
    int y1 = pa.y();
    _bresenham_ellipse(x1, y1, rx, ry);
    timer.start();
    _bresenham_ellipse_debug(x1, y1, rx, ry);
    auto time = timer.nsecsElapsed();
    ui->time_show->setText(QString::number(time));
}

void MainWindow::_bresenham_ellipse(int xc, int yc, int rx, int ry){
    draw_pt(xc+rx, yc, qRgb(0, 0, 255));
    draw_pt(xc, yc+ry, qRgb(0, 0, 255));
    draw_pt(xc-rx, yc, qRgb(0, 0, 255));
    draw_pt(xc, yc-ry, qRgb(0, 0, 255));
    ui->frame->repaint();
    Sleeper::msleep(50);
    int x = 0;
    int y = ry;
    int p = 4*ry*ry - 4*rx*rx*ry + rx*rx;
    while (ry*ry*x < rx*rx*y) {
        if (p < 0) {
            p += 4*ry*ry*(2*x+3);
            x += 1;
        } else {
            p += 4*ry*ry*(2*x+3) + 8*rx*rx*(1-y);
            x += 1;
            y -= 1;
        }
        draw_pt(x+xc, y+yc, qRgb(0, 0, 255));
        draw_pt(x+xc, -y+yc, qRgb(0, 0, 255));
        draw_pt(-x+xc, y+yc, qRgb(0, 0, 255));
        draw_pt(-x+xc, -y+yc, qRgb(0, 0, 255));
        ui->frame->repaint();
        Sleeper::msleep(50);
    }

    x = rx;
    y = 0;
    p = 4*rx*rx - 4*ry*ry*rx + ry*ry;
    while (ry*ry*x > rx*rx*y) {
        if (p < 0) {
            p += 4*rx*rx*(2*y+3);
            y += 1;
        } else {
            p += 4*rx*rx*(2*y+3) + 8*ry*ry*(1-x);
            y += 1;
            x -= 1;
        }
        draw_pt(x+xc, y+yc, qRgb(0, 0, 255));
        draw_pt(x+xc, -y+yc, qRgb(0, 0, 255));
        draw_pt(-x+xc, y+yc, qRgb(0, 0, 255));
        draw_pt(-x+xc, -y+yc, qRgb(0, 0, 255));
        ui->frame->repaint();
        Sleeper::msleep(50);
    }
    ui->frame->setPixmap(QPixmap::fromImage(img));
}

void MainWindow::_bresenham_ellipse_debug(int xc, int yc, int rx, int ry){
    int x = 0;
    int y = ry;
    int p = 4*ry*ry - 4*rx*rx*ry + rx*rx;
    while (ry*ry*x < rx*rx*y) {
        if (p < 0) {
            p += 4*ry*ry*(2*x+3);
            x += 1;
        } else {
            p += 4*ry*ry*(2*x+3) + 8*rx*rx*(1-y);
            x += 1;
            y -= 1;
        }
    }
    x = rx;
    y = 0;
    p = 4*rx*rx - 4*ry*ry*rx + ry*ry;
    while (ry*ry*x > rx*rx*y) {
        if (p < 0) {
            p += 4*rx*rx*(2*y+3);
            y += 1;
        } else {
            p += 4*rx*rx*(2*y+3) + 8*ry*ry*(1-x);
            y += 1;
            x -= 1;
        }
    }
}




#endif // ELLIPSE_ALGOS_H
