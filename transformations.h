#ifndef TRANSFORMATIONS_H
#define TRANSFORMATIONS_H

void MainWindow::init_matrix(){
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            if (i == j) this->matrix[i][j] = 1;
            else this->matrix[i][j] = 0;
        }
    }

    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
//            this->matrix[i][j] = temp[i][j];
            std::cout << matrix[i][j] << " ";
        } std::cout << std::endl;
    }
}

void MainWindow::draw_poly(std::vector<QPoint> list_pts){


    for (int i = 0; i < list_pts.size()-1; i++){
        _dda_line_scanfill(list_pts[i].x(), list_pts[i].y(), list_pts[i+1].x(), list_pts[i+1].y());
    }
    _dda_line_scanfill(list_pts[0].x(), list_pts[0].y(), list_pts[list_pts.size()-1].x(), list_pts[list_pts.size()-1].y());
}

void MainWindow::draw_poly(std::vector<std::pair<float, float> > list_pts){


    for (int i = 0; i < list_pts.size()-1; i++){
        float x1 = list_pts[i].first;
        float y1 = list_pts[i].second;
        float x2 = list_pts[i+1].first;
        float y2 = list_pts[i+1].second;

        _dda_line_scanfill(round(x1), round(y1), round(x2), round(y2));
    }
    float x1 = list_pts[0].first;
    float y1 = list_pts[0].second;
    float x2 = list_pts[list_pts.size()-1].first;
    float y2 = list_pts[list_pts.size()-1].second;
    _dda_line_scanfill(round(x1), round(y1), round(x2), round(y2));
}


void MainWindow::on_transform_clicked() {

    if (this->to_do == 1) {
        this->to_do = 8;
        this->polygon.resize(0);
        init_matrix();
        return;
    }
    this->to_do = 1;
    if (polygon.size() > 2) {
        _dda_line_scanfill(round(polygon[0].first), round(polygon[0].second), round(polygon.back().first), round(polygon.back().second));
    }
}




void MainWindow::on_translation_clicked()
{

    float trans[3][3] = {{1, 0, (float)ui->translation_x->value()},{0, 1, (float)ui->tranlation_y->value()},{0, 0, 1}};

    timer.start();

    float temp[3][3] = {{0, 0, 0},{0, 0, 0},{0, 0, 0}};
    for (int i = 0; i<9; i++){
        for(int j = 0; j<3; j++){
            temp[i/3][j] += trans[i/3][i%3] * this->matrix[i%3][j];
        }
    }
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            this->matrix[i][j] = temp[i][j];
        }
    }

    auto time = timer.nsecsElapsed();
    ui->time_show->setText(QString::number(time/1000) + "." + QString::number(time%1000));
    // int r = ui->red_color_spinbox->value();
    // int g = ui->green_color_spinbox->value();
    // int b = ui->blue_color_spinbox->value();
    // ui->red_color_spinbox->setValue(0);
    // ui->green_color_spinbox->setValue(0);
    // ui->blue_color_spinbox->setValue(0);
    // draw_poly(this->list_scan);  //black color
    // ui->red_color_spinbox->setValue(r);
    // ui->green_color_spinbox->setValue(g);
    // ui->blue_color_spinbox->setValue(b);

    float next[3][this->polygon.size()];
    float res[3][this->polygon.size()];
    for (int i = 0; i < this->polygon.size(); i++){
        next[0][i] = this->polygon[i].first;
        next[1][i] = this->polygon[i].second;
        next[2][i] = 1;
        res[0][i] = 0;
        res[1][i] = 0;
        res[2][i] = 0;
    }

    for (int i = 0; i<9; i++){
        for(int j = 0; j<this->polygon.size(); j++){
            res[i/3][j] += this->matrix[i/3][i%3] * next[i%3][j];
        }
    }

    std::vector<std::pair<float, float> > output;
    for (int i = 0; i < this->polygon.size(); i++){
        output.push_back({res[0][i]/res[2][i], res[1][i]/res[2][i]});
    }

    draw_poly(output);  //colored
    polygon = output;
}


void MainWindow::on_rotation_clicked()
{

    int angle = ui->rotation_angle->value();
    if (angle > 180){
        angle -= 360;
    }

    float value = (((float)(angle))*3.14159265)/180;

    auto pt = orig_to_user(ui->frame->x, ui->frame->y);
    init_matrix();


    timer.start();

    float arr[3][3][3] = {
        {{1, 0, (-1)*(float)pt.x()},{0, 1, (-1)*(float)pt.y()},{0, 0, 1}} ,
        {{std::cos(value), -1*std::sin(value), 0},{std::sin(value), std::cos(value), 0},{0, 0, 1}},
        {{1, 0, (float)pt.x()},{0, 1, (float)pt.y()},{0, 0, 1}}
    };

    for (int k = 0; k < 3; k++){
        float temp[3][3] = {{0, 0, 0},{0, 0, 0},{0, 0, 0}};
        for (int i = 0; i<9; i++){
            for(int j = 0; j<3; j++){
                temp[i/3][j] += arr[k][i/3][i%3] * this->matrix[i%3][j];
            }
        }
        for (int i = 0; i<3; i++){
            for(int j = 0; j<3; j++){
                this->matrix[i][j] = temp[i][j];
            }
        }
    }

    auto time = timer.nsecsElapsed();
    ui->time_show->setText(QString::number(time/1000) + "." + QString::number(time%1000));

//    int r = ui->red_color_spinbox->value();
//    int g = ui->green_color_spinbox->value();
//    int b = ui->blue_color_spinbox->value();
//    ui->red_color_spinbox->setValue(0);
//    ui->green_color_spinbox->setValue(0);
//    ui->blue_color_spinbox->setValue(0);
//    draw_poly(this->polygon);  //black color
//    ui->red_color_spinbox->setValue(r);
//    ui->green_color_spinbox->setValue(g);
//    ui->blue_color_spinbox->setValue(b);

    float next[3][this->polygon.size()];
    float res[3][this->polygon.size()];
    for (int i = 0; i < this->polygon.size(); i++){
        next[0][i] = this->polygon[i].first;
        next[1][i] = this->polygon[i].second;
        next[2][i] = 1;
        res[0][i] = 0;
        res[1][i] = 0;
        res[2][i] = 0;
    }

    std::cout << "3" << std::endl;

    for (int i = 0; i<9; i++){
        for(int j = 0; j<this->polygon.size(); j++){
            res[i/3][j] += this->matrix[i/3][i%3] * next[i%3][j];
        }
    }

    std::vector<std::pair<float, float> > output;
    for (int i = 0; i < this->polygon.size(); i++){
        output.push_back({res[0][i]/res[2][i], res[1][i]/res[2][i]});
    }

    draw_poly(output);  //colored
    polygon = output;
}


void MainWindow::on_scaling_clicked()
{
    auto pt = orig_to_user(ui->frame->x, ui->frame->y);
    init_matrix();

    timer.start();

    float arr[3][3][3] = {
        {{1, 0, (-1)*(float)pt.x()},{0, 1, (-1)*(float)pt.y()},{0, 0, 1}} ,
        {{(float)ui->scale_x->value(), 0, 0},{0, (float)ui->scale_y->value(), 0},{0, 0, 1}},
        {{1, 0, (float)pt.x()},{0, 1, (float)pt.y()},{0, 0, 1}}
    };

    for (int k = 0; k < 3; k++){
        float temp[3][3] = {{0, 0, 0},{0, 0, 0},{0, 0, 0}};
        for (int i = 0; i<9; i++){
            for(int j = 0; j<3; j++){
                temp[i/3][j] += arr[k][i/3][i%3] * this->matrix[i%3][j];
            }
        }
        for (int i = 0; i<3; i++){
            for(int j = 0; j<3; j++){
                this->matrix[i][j] = temp[i][j];
            }
        }
    }

    auto time = timer.nsecsElapsed();
    ui->time_show->setText(QString::number(time/1000) + "." + QString::number(time%1000));
    // int r = ui->red_color_spinbox->value();
    // int g = ui->green_color_spinbox->value();
    // int b = ui->blue_color_spinbox->value();
    // ui->red_color_spinbox->setValue(0);
    // ui->green_color_spinbox->setValue(0);
    // ui->blue_color_spinbox->setValue(0);
    // draw_poly(this->list_scan);  //black color
    // ui->red_color_spinbox->setValue(r);
    // ui->green_color_spinbox->setValue(g);
    // ui->blue_color_spinbox->setValue(b);

    float next[3][this->polygon.size()];
    float res[3][this->polygon.size()];
    for (int i = 0; i < this->polygon.size(); i++){
        next[0][i] = this->polygon[i].first;
        next[1][i] = this->polygon[i].second;
        next[2][i] = 1;
        res[0][i] = 0;
        res[1][i] = 0;
        res[2][i] = 0;
    }

    for (int i = 0; i<9; i++){
        for(int j = 0; j<this->polygon.size(); j++){
            res[i/3][j] += this->matrix[i/3][i%3] * next[i%3][j];
        }
    }

    std::vector<std::pair<float, float> > output;
    for (int i = 0; i < this->polygon.size(); i++){
        output.push_back({res[0][i]/res[2][i], res[1][i]/res[2][i]});
    }

    draw_poly(output);  //colored
    polygon = output;
}


void MainWindow::on_shear_clicked()
{
    auto pt = orig_to_user(ui->frame->x, ui->frame->y);
    init_matrix();

    timer.start();

    float arr[3][3][3] = {
        {{1, 0, (-1)*(float)pt.x()},{0, 1, (-1)*(float)pt.y()},{0, 0, 1}} ,
        {{1, -(float)ui->shear_x->value(), 0},{-(float)ui->shear_y->value(), 1, 0},{0, 0, 1}},
        {{1, 0, (float)pt.x()},{0, 1, (float)pt.y()},{0, 0, 1}}
    };

    for (int k = 0; k < 3; k++){
        float temp[3][3] = {{0, 0, 0},{0, 0, 0},{0, 0, 0}};
        for (int i = 0; i<9; i++){
            for(int j = 0; j<3; j++){
                temp[i/3][j] += arr[k][i/3][i%3] * this->matrix[i%3][j];
            }
        }
        for (int i = 0; i<3; i++){
            for(int j = 0; j<3; j++){
                this->matrix[i][j] = temp[i][j];
            }
        }
    }


    auto time = timer.nsecsElapsed();
    ui->time_show->setText(QString::number(time/1000) + "." + QString::number(time%1000));
    // int r = ui->red_color_spinbox->value();
    // int g = ui->green_color_spinbox->value();
    // int b = ui->blue_color_spinbox->value();
    // ui->red_color_spinbox->setValue(0);
    // ui->green_color_spinbox->setValue(0);
    // ui->blue_color_spinbox->setValue(0);
    // draw_poly(this->list_scan);  //black color
    // ui->red_color_spinbox->setValue(r);
    // ui->green_color_spinbox->setValue(g);
    // ui->blue_color_spinbox->setValue(b);

    float next[3][this->polygon.size()];
    float res[3][this->polygon.size()];
    for (int i = 0; i < this->polygon.size(); i++){
        next[0][i] = this->polygon[i].first;
        next[1][i] = this->polygon[i].second;
        next[2][i] = 1;
        res[0][i] = 0;
        res[1][i] = 0;
        res[2][i] = 0;
    }

    std::cout << "3" << std::endl;

    for (int i = 0; i<9; i++){
        for(int j = 0; j<this->polygon.size(); j++){
            res[i/3][j] += this->matrix[i/3][i%3] * next[i%3][j];
        }
    }

    std::vector<std::pair<float, float> > output;
    for (int i = 0; i < this->polygon.size(); i++){
        output.push_back({res[0][i]/res[2][i], res[1][i]/res[2][i]});
    }

    draw_poly(output);  //colored
    polygon = output;
}


void MainWindow::on_reflection_clicked()
{

    auto pa = orig_to_user(p1.x(), p1.y());
    auto pb = orig_to_user(p2.x(), p2.y());
    float x1 = (float)pa.x();
    float y1 = (float)pa.y();
    float x2 = (float)pb.x();
    float y2 = (float)pb.y();



    timer.start();

    float m = (y1-y2)/(x1-x2);
    float c = y1 - (y1-y2)*x1/(x1-x2);

    float value = atan(m);

    float arr[5][3][3] = {
        {{1, 0, 0},{0, 1, -1*c},{0, 0, 1}},
        {{std::cos((-1)*value), -1*std::sin((-1)*value), 0},{std::sin((-1)*value), std::cos((-1)*value), 0},{0, 0, 1}},
        {{1, 0, 0},{0, -1, 0},{0, 0, 1}},
        {{std::cos(value), -1*std::sin(value), 0},{std::sin(value), std::cos(value), 0},{0, 0, 1}},
        {{1, 0, 0},{0, 1, c},{0, 0, 1}},
    };

    for (int k = 0; k < 5; k++){
        float temp[3][3] = {{0, 0, 0},{0, 0, 0},{0, 0, 0}};
        for (int i = 0; i<9; i++){
            for(int j = 0; j<3; j++){
                temp[i/3][j] += arr[k][i/3][i%3] * this->matrix[i%3][j];
            }
        }
        for (int i = 0; i<3; i++){
            for(int j = 0; j<3; j++){
                this->matrix[i][j] = temp[i][j];
            }
        }
    }

    auto time = timer.nsecsElapsed();
    ui->time_show->setText(QString::number(time/1000) + "." + QString::number(time%1000));
    // int r = ui->red_color_spinbox->value();
    // int g = ui->green_color_spinbox->value();
    // int b = ui->blue_color_spinbox->value();
    // ui->red_color_spinbox->setValue(0);
    // ui->green_color_spinbox->setValue(0);
    // ui->blue_color_spinbox->setValue(0);
    // draw_poly(this->list_scan);  //black color
    // ui->red_color_spinbox->setValue(r);
    // ui->green_color_spinbox->setValue(g);
    // ui->blue_color_spinbox->setValue(b);

    float next[3][this->polygon.size()];
    float res[3][this->polygon.size()];
    for (int i = 0; i < this->polygon.size(); i++){
        next[0][i] = this->polygon[i].first;
        next[1][i] = this->polygon[i].second;
        next[2][i] = 1;
        res[0][i] = 0;
        res[1][i] = 0;
        res[2][i] = 0;
    }


    for (int i = 0; i<9; i++){
        for(int j = 0; j<this->polygon.size(); j++){
            res[i/3][j] += this->matrix[i/3][i%3] * next[i%3][j];
        }
    }

    std::vector<std::pair<float, float> > output;
    for (int i = 0; i < this->polygon.size(); i++){
        output.push_back({res[0][i]/res[2][i], res[1][i]/res[2][i]});
    }

    draw_poly(output);  //colored
    polygon = output;
}




#endif // TRANSFORMATIONS_H
