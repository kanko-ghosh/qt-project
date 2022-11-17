#ifndef LINE_ALGOS_H
#define LINE_ALGOS_H

void MainWindow::_dda_line(int x1, int y1, int x2, int y2) {
    float dx, dy;
    float x, y;
    float Dx, Dy;

    // Base Case
    if(x1 == x2 && y1 == y2){
        draw_pt(x1, y1, qRgb(0, 255, 0));
        ui->frame->repaint();
        Sleeper::msleep(50);
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
        ui->frame->repaint();
        Sleeper::msleep(50);
        x += Dx, y += Dy;
    }
}

void MainWindow::_dda_line_scanfill(int x1, int y1, int x2, int y2) {
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

    int end = (dx > dy)? dx: dy;
    for(int k = 0; k <= end; k++) {
        int ix = (x == 0) ? 0 : (int)(x + 0.5*abs(x)/x);
        int iy = (y == 0) ? 0 : (int)(y + 0.5*abs(y)/y);
        x += Dx, y += Dy;
    }
}


void MainWindow::_bresenham(int x1, int y1, int x2, int y2) {
    if(y1 == y2)
        {
            int start = std::min(x1, x2), end = std::max(x1, x2);
            for(int i = start; i <= end; i++) {
                draw_pt(i, y1, qRgb(255,255,0));
                ui->frame->repaint();
                Sleeper::msleep(50);
            }
            return;
        }

        // Case for vertical line
        if(x1 == x2)
        {
            int start = std::min(y1, y2), end = std::max(y1, y2);
            for(int j = start; j <= end; j++) {
                draw_pt(x1, j, qRgb(255,255,0));
                ui->frame->repaint();
                Sleeper::msleep(50);
            }
            return;
        }

        int dx = x2 - x1, dy = y2 - y1, p;

        // Case for |m| <= 1
        if(abs(dy) <= abs(dx))
        {
            if(x1 > x2) std::swap(x1, x2), std::swap(y1, y2), dx = -dx, dy = -dy;

            int j = (dy > 0)? y1: (y1 + 1);
            p = 2 * dy - dx;
            draw_pt(x1, y1, qRgb(255,255,0));
            ui->frame->repaint();
            Sleeper::msleep(50);
            // Plotting initial point ...
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
                ui->frame->repaint();
                Sleeper::msleep(50);
            }
        }

        // Case for |m| > 1
        else
        {
            if(y1 > y2) std::swap(x1, x2), std::swap(y1, y2), dx = -dx, dy = -dy;

            int i = (dx > 0)? x1: (x1 + 1);
            p = 2 * dx - dy;
            draw_pt(x1, y1, qRgb(255,255,0));
            ui->frame->repaint();
            Sleeper::msleep(50);
            // Plotting initial point ...
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
                ui->frame->repaint();
                Sleeper::msleep(50);
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
            if(x1 > x2) {
                std::swap(x1, x2);
                std::swap(y1, y2);
                dx = -dx;
                dy = -dy;
            }
            
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
            if(y1 > y2) {
                std::swap(x1, x2);
                std::swap(y1, y2);
                dx = -dx;dy = -dy;
            }

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


void MainWindow::on_bresenham_line_clicked()
{
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



#endif // LINE_ALGOS_H
