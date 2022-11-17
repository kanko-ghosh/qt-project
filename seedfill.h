#ifndef SEEDFILL_H
#define SEEDFILL_H

void MainWindow::on_boundary_fill_clicked()
{
    this->to_do = 6;
    count = 2;
    list_scan.resize(0);
}


void MainWindow::_boundary_fill(std::vector<QPoint> list_scan){
    auto boundarypt = list_scan[0];
    auto seedpt = list_scan[1];

    auto boundary_color = img.pixel(boundarypt);

    QColor target_color = QColor(ui->red_color_spinbox->value(), ui->green_color_spinbox->value(), ui->blue_color_spinbox->value());
    QColor seed_color = img.pixelColor(seedpt.x(), seedpt.y());
    if (seed_color == target_color) return;

//    img.setPixel(1, 1, target_color);
    _rec_boundary (seedpt.x(), seedpt.y(), target_color, boundary_color);
}

void MainWindow::_rec_boundary (int x, int y, QColor target_color, QRgb boundary_color){

    auto k = ui->grid_size->value();
    auto pt = QPoint(x, y);
    auto cur_color = img.pixelColor(pt);
    if (cur_color == target_color || cur_color == boundary_color || x > 699 || y > 699 || x < 0 || y < 0) return;
    else {
//        std::cout<< "LOL: " <<cur_color.red() << " " << cur_color.green() << " " << cur_color.blue() << " -> ";
//        std::cout << target_color << std::endl;
        std::cout<< target_color.red() << " " << target_color.green() << " " << target_color.blue() << " -> ";
        std::cout << x << " " << y << std::endl;
        auto pt = orig_to_user(x, y);

        draw_pt(pt.x(), pt.y(), qRgb(0, 0, 0));
        ui->frame->repaint();
        Sleeper::msleep(10);
        _rec_boundary(x+k, y, target_color, boundary_color);
        _rec_boundary(x-k, y, target_color, boundary_color);
        _rec_boundary(x, y+k, target_color, boundary_color);
        _rec_boundary(x, y-k, target_color, boundary_color);
    }
}


void MainWindow::on_flood_fill_clicked()
{
    this->to_do = 7;
}

void MainWindow::_flood_fill(int x, int y){
    QColor target_color = QColor(ui->red_color_spinbox->value(), ui->green_color_spinbox->value(), ui->blue_color_spinbox->value());
    QColor seed_color = img.pixelColor(x, y);
    if (seed_color == target_color) return;
    _rec_flood (x, y, seed_color);
}

void MainWindow::_rec_flood (int x, int y, QColor seed_color){
    if (x > 699 || y > 699 || x < 0 || y < 0) return;
    auto k = ui->grid_size->value();
    auto pt = QPoint(x, y);
    auto cur_color = img.pixelColor(pt);
    if (cur_color != seed_color ) return;
    else {
//        std::cout<< "LOL: " <<cur_color.red() << " " << cur_color.green() << " " << cur_color.blue() << " -> ";
////        std::cout << target_color << std::endl;
//        std::cout<< target_color.red() << " " << target_color.green() << " " << target_color.blue() << " -> ";
//        std::cout << x << " " << y << std::endl;
        auto pt = orig_to_user(x, y);

        draw_pt(pt.x(), pt.y(), qRgb(0, 0, 0));
        ui->frame->repaint();
        Sleeper::msleep(10);
        _rec_flood(x+k, y, seed_color);
        _rec_flood(x-k, y, seed_color);
        _rec_flood(x, y+k, seed_color);
        _rec_flood(x, y-k, seed_color);
    }
}



#endif // SEEDFILL_H
