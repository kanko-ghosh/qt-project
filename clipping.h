#ifndef CLIPPING_H
#define CLIPPING_H


char getReg(int xleft, int xright, int ytop, int ybottom, QPoint pnt){

    /**
     * up: b1000
     * down: b0100
     * left: b0010
     * right: b0001
     */

    char r = 0;
    if(pnt.y() > ytop) r |= 8;
    if(pnt.y() <= ybottom) r |= 4;
    if(pnt.x() <= xleft) r |= 2;
    if(pnt.x() > xright) r |= 1;

    return r;
}


void MainWindow::on_draw_lines_clicked()
{
    if (this->to_do == 1) {
        this->to_do = 12;
        this->polygon.resize(0);
        init_matrix();
        return;
    }
    this->to_do = 1;
}


bool test_liang_barsky(float p, float q, float &t1, float &t2)
{
    float r;
    bool retVal = true;

    if(p < 0.0) {
        r = q / p ;

        // line portion is outside the clipping edg
        if (r > t2) retVal = false;
        else if (r > t1) t1 = r;
    }
    else if(p > 0.0)
    {
        // line leaving point ...
        r = q / p ;

        // line portion is outside
        if (r < t1) retVal = false;
        else if (r < t2) t2 = r;
    }
    else
    {
        if(q < 0.0) retVal = false;
    }

    return retVal;
}

void MainWindow::on_line_clipping_clicked()
{
    to_do = 1;
    auto pa = orig_to_user(p1.x(), p1.y());
    auto pb = orig_to_user(p2.x(), p2.y());
    int xleft = pa.x();
    int ytop = pa.y();
    int xright = pb.x();
    int ybottom = pb.y();

    //top left - bottom right
    if(xleft > xright) std::swap(xleft, xright);
    if(ybottom > ytop) std::swap(ybottom, ytop);


    //clear
    if(xright - xleft < 2 || ytop - ybottom < 2) {
        for (int i = 0; i < height_total; i++){
            for (int j = 0; j < height_total; j++){
                img.setPixel(j,i,qRgb(0,0,0));
            }
        }
        ui->time_show->setText(QString::number(0));
        ui->frame->setPixmap(QPixmap::fromImage(img));

        return;
    }

    std::vector<std::pair<QPoint, QPoint> >  newList;
    char region1, region2;

//    std::cout << " -> ";
//    for (auto elem : polygon){
//        std:: cout << elem.first << " "  << elem.second << " ";
//    } std::cout << std::endl;

    timer.start();

    for (int i = 0; i < polygon.size()-1; i+=2) {
        QPoint pnt1 (polygon[i].first, polygon[i].second);
        QPoint pnt2 (polygon[i+1].first, polygon[i+1].second);

        region1 = getReg(xleft, xright, ytop, ybottom, pnt1);
        region2 = getReg(xleft, xright, ytop, ybottom, pnt2);


        if (region1 != 0 && region2 == 0) {
            std::swap(pnt1, pnt2);
            std::swap(region1, region2);
        }

        if (region1 == 0 && region2 == 0){
            //both inside
            newList.push_back({pnt1, pnt2});

        }
        else if (region1 == 0) {
            // p1 inside, p2 outside
            if (pnt1.x() == pnt2.x()) {
                //vertical line
                QPoint newpt2;
                if (region2 & 8) {
                    newpt2 = QPoint(pnt1.x(), ytop-1);
                } else {
                    newpt2 = QPoint(pnt1.x(), ybottom+1);
                }
                newList.push_back({pnt1, newpt2});
                continue;
            }

            float m = ((float)(pnt2.y() - pnt1.y()))/(pnt2.x() - pnt1.x());
            float c = pnt1.y() - m * pnt1.x();

            int x;
            int y;

            if (region2 & 8){
                y = ytop - 1;
                x = (y - c) / m ;
            }
            if (region2 & 4){
                y = ybottom + 1;
                x = (y - c) / m ;
            }
            if (x > xleft && x < xright) {
                //actual cut
                newList.push_back({pnt1, {x, y}});
                continue; //else do this somewhere else :/
            }

            if (region2 & 2){
                x = xleft + 1;
                y = m*x + c ;
            }

            if (region2 & 1) {
                x = xright - 1;
                y = m*x + c ;
            }

            if (y > ytop && y < ybottom) {
                //actual cut
                newList.push_back({pnt1, {x, y}});
                continue; //else do this somewhere else :/
            }

        } else {
            //both outside

            if (region1 & region2) {
                //both in one side
                continue;
            }

            //cliping hoke rahega..
            if (pnt1.x() == pnt2.x()){
                //vertical line
                auto p1 = QPoint(pnt1.x(), ytop-1);
                auto p2 = QPoint(pnt1.x(), ybottom+1);
                newList.push_back({p1, p2});
                continue;
            }

            float m = ((float)(pnt2.y() - pnt1.y()))/(pnt2.x() - pnt1.x());
            float c = pnt1.y() - m * pnt1.x();

            int x, y;
            QPoint p1, p2;
            bool p1Found = false;
            bool p2Found = false;

            if ((region1 & 8) && !p1Found){
                y = ytop-1;
                x = (y-c)/m;

                if(xleft < x && x < xright) {
                    p1 = {x, y};
                    p1Found = true;
                }
            }

            if ((region1 & 4) && !p1Found){
                y = ybottom+1;
                x = (y-c)/m;

                if(xleft < x && x < xright) {
                    p1 = {x, y};
                    p1Found = true;
                }
            }

            if ((region1 & 2) && !p1Found){
                x = xleft+1;
                y = m*x + c;

                if(ybottom < y && y < ytop) {
                    p1 = {x, y};
                    p1Found = true;
                }
            }

            if ((region1 & 1) && !p1Found){
                x = xright-1;
                y = m*x + c;

                if(ybottom < y && y < ytop) {
                    p1 = {x, y};
                    p1Found = true;
                }
            }

            if (!p1Found) continue; //exit without cutting borders from inside

            if ((region2 & 8) && !p2Found){
                y = ytop-1;
                x = (y-c)/m;

                if(xleft < x && x < xright) {
                    p2 = {x, y};
                    p2Found = true;
                }
            }

            if ((region2 & 4) && !p2Found){
                y = ybottom+1;
                x = (y-c)/m;

                if(xleft < x && x < xright) {
                    p2 = {x, y};
                    p2Found = true;
                }
            }

            if ((region2 & 2) && !p2Found){
                x = xleft+1;
                y = m*x + c;

                if(ybottom < y && y < ytop) {
                    p2 = {x, y};
                    p2Found = true;
                }
            }

            if ((region2 & 1) && !p2Found){
                x = xright-1;
                y = m*x + c;

                if(ybottom < y && y < ytop) {
                    p2 = {x, y};
                    p2Found = true;
                }
            }

            if (!p1Found) continue; //exit without cutting borders from inside

            newList.push_back({p1, p2});
        }
    }

    auto time = timer.nsecsElapsed();
    ui->time_show->setText(QString::number(time));

    for (int i = 0; i < height_total; i++){
        for (int j = 0; j < height_total; j++){
            img.setPixel(j,i,qRgb(0,0,0));
        }
    }

    _dda_line_scanfill(xleft, ytop, xleft, ybottom);
    _dda_line_scanfill(xright, ytop, xright, ybottom);
    _dda_line_scanfill(xright, ytop, xleft, ytop);
    _dda_line_scanfill(xright, ybottom, xleft, ybottom);

//    std::cout << " -> ";
//    for (auto elem : newList){
//        std:: cout << elem.first << " "  << elem.second << " ";
//    } std::cout << std::endl;

    for (int i = 0; i < newList.size(); i++){
        _dda_line_scanfill(round(newList[i].first.x()), round(newList[i].first.y()), round(newList[i].second.x()), round(newList[i].second.y()));
    }

}
void MainWindow::on_line_clipping_2_clicked()
{


    to_do = 1;
    auto pa = orig_to_user(p1.x(), p1.y());
    auto pb = orig_to_user(p2.x(), p2.y());
    int xleft = pa.x();
    int ytop = pa.y();
    int xright = pb.x();
    int ybottom = pb.y();

    //top left - bottom right
    if(xleft > xright) std::swap(xleft, xright);
    if(ybottom > ytop) std::swap(ybottom, ytop);


    //clear
    if(xright - xleft < 2 || ytop - ybottom < 2) {
        for (int i = 0; i < height_total; i++){
            for (int j = 0; j < height_total; j++){
                img.setPixel(j,i,qRgb(0,0,0));
            }
        }
        ui->frame->setPixmap(QPixmap::fromImage(img));
        ui->time_show->setText(QString::number(0));
        return;
    }

    timer.start();

    std::vector<std::pair<std::pair<float, float>, std::pair<float, float>> >  newList;
    for (int i = 0; i < polygon.size()-1; i+=2) {
        auto pnt1 = polygon[i];
        auto pnt2 = polygon[i+1];

        float t1 = 0.0;
        float t2 = 1.0;

        int dx = pnt2.first - pnt1.first;
        int dy = pnt2.second - pnt1.second;

        if (test_liang_barsky(-dx, pnt1.first - (xleft + 1), t1, t2)){  /// left edge
            if (test_liang_barsky(dx, (xright - 1) - pnt1.first, t1, t2)){  ///right edge
                if (test_liang_barsky(-dy, pnt1.second - (ybottom+1), t1, t2)){
                    if (test_liang_barsky(dy, (ytop-1)-pnt1.second, t1, t2)){

                        if(t2 < 1.0) {
                            pnt2 = {pnt1.first + t2 * dx, pnt1.second + t2 * dy};
                        }
                        if(t1 > 0.0) {
                            pnt1 = {pnt1.first + t1 * dx, pnt1.second + t1 * dy};
                        }


                        newList.push_back({pnt1, pnt2});
                    }
                }
            }
        }
    }

    auto time = timer.nsecsElapsed();
    ui->time_show->setText(QString::number(time));


    for (int i = 0; i < height_total; i++){
        for (int j = 0; j < height_total; j++){
            img.setPixel(j,i,qRgb(0,0,0));
        }
    }
    _dda_line_scanfill(xleft, ytop, xleft, ybottom);
    _dda_line_scanfill(xright, ytop, xright, ybottom);
    _dda_line_scanfill(xright, ytop, xleft, ytop);
    _dda_line_scanfill(xright, ybottom, xleft, ybottom);

    for (int i = 0; i < newList.size(); i++){
        _dda_line_scanfill(newList[i].first.first, newList[i].first.second, newList[i].second.first, newList[i].second.second);
    }
}



void MainWindow::on_poly_clip_button_clicked()
{

    if (this->polygon.empty()) return;
    auto pa = orig_to_user(p1.x(), p1.y());
    auto pb = orig_to_user(p2.x(), p2.y());
    int xleft = pa.x();
    int ytop = pa.y();
    int xright = pb.x();
    int ybottom = pb.y();

    //top left - bottom right
    if(xleft > xright) std::swap(xleft, xright);
    if(ybottom > ytop) std::swap(ybottom, ytop);




    //clear
    if(xright - xleft < 2 || ytop - ybottom < 2) {
        for (int i = 0; i < height_total; i++){
            for (int j = 0; j < height_total; j++){
                img.setPixel(j,i,qRgb(0,0,0));
            }
        }
        ui->frame->setPixmap(QPixmap::fromImage(img));
        ui->time_show->setText(QString::number(0));
        return;
    }


    timer.start();
    std::vector<std::pair<float, float> > newPolygon;

    for (char direction : {8, 4, 2, 1}){

//        std::cout << direction << " -> ";
//        for (auto elem : polygon){
//            std:: cout << elem.first << " " << elem.second << " ";
//        } std::cout << std::endl;
//        for (int i = 0; i < height_total; i++){
//            for (int j = 0; j < height_total; j++){
//                img.setPixel(j,i,qRgb(0,0,0));
//            }
//        }
//        draw_poly(polygon);
//        ui->frame->setPixmap(QPixmap::fromImage(img));


        bool isp1in;
        bool isp2in;
        if (polygon.empty()) return;

        for (int itr = 0; itr < polygon.size(); itr++){
            auto pnt1 = polygon[itr];
            auto pnt2 = polygon[(itr+1)%polygon.size()];

            switch (direction) {
                case 8:
                    isp1in = (pnt1.second < ytop);
                    isp2in = (pnt2.second < ytop);
                    break;
                case 4:
                    isp1in = (pnt1.second > ybottom);
                    isp2in = (pnt2.second > ybottom);
                    break;
                case 2:
                    isp1in = (pnt1.first > xleft);
                    isp2in = (pnt2.first > xleft);
                    break;
                case 1:
                    isp1in = (pnt1.first < xright);
                    isp2in = (pnt2.first < xright);
                    break;
            }

            if (isp1in) newPolygon.push_back(pnt1);

            if (isp1in != isp2in) {
                //vertical
                if (pnt1.first == pnt2.first){
                    auto temp = pnt1;
                    switch(direction){
                        case 8:
                            temp.second = ytop -1;
                            break;
                        case 4:
                            temp.second = ybottom + 1;
                            break;
                    }
                    newPolygon.push_back(temp);
                    continue;
                }


                float m = ((float)(pnt2.second - pnt1.second))/(pnt2.first - pnt1.first);
                float c = pnt1.second - m * pnt1.first;


                switch (direction){
                case 8:
                    newPolygon.push_back({(ytop-1-c)/m, ytop-1});
                    break;
                case 4:
                    newPolygon.push_back({(ybottom+1-c)/m, ybottom+1});
                    break;
                case 2:
                    newPolygon.push_back({xleft+1, m*(xleft+1)+c});
                    break;
                case 1:
                    newPolygon.push_back({xright-1, m*(xright-1)+c});
                    break;
                }
            }

        }
        polygon = newPolygon;
        newPolygon.clear();
    }

    auto time = timer.nsecsElapsed();
    ui->time_show->setText(QString::number(time));

    for (int i = 0; i < height_total; i++){
        for (int j = 0; j < height_total; j++){
            img.setPixel(j,i,qRgb(0,0,0));
        }
    }
    _dda_line_scanfill(xleft, ytop, xleft, ybottom);
    _dda_line_scanfill(xright, ytop, xright, ybottom);
    _dda_line_scanfill(xright, ytop, xleft, ytop);
    _dda_line_scanfill(xright, ybottom, xleft, ybottom);
    draw_poly(polygon);

    ui->frame->setPixmap(QPixmap::fromImage(img));


//        std::cout << " -> ";
//        for (auto elem : polygon){
//            std:: cout << elem.first << " "  << elem.second << " ";
//        } std::cout << std::endl;

}





#endif // CLIPPING_H
