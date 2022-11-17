#ifndef SCANFILL_H
#define SCANFILL_H


void MainWindow::on_scanline_clicked()
{
    to_do = 5;
    list_scan.resize(0);
}

//struct Edge {
//    int yUpper;
//    float xIntersect;
//    float dxPerScan;
//    Edge * next;
//};


void MainWindow::insertEdge(Edge * list, Edge * edge) {
    Edge * q = list;
    Edge * p = q->next;

    while (p != NULL){
        if (edge->xIntersect < p->xIntersect) {
            p = NULL;
        } else {
            q = p;
            p = p ->next;
        }
    }
    edge->next = q->next;
    q->next = edge;
}

int MainWindow::yNext (int k, std::vector<QPoint> pts ){
    int cnt = pts.size();
    int j;
    if ((k+1) > cnt-1) j = 0;
    else j = k+1;

    while (pts[k].y() == pts[j].y()) {
        if (j+1 > cnt-1) j = 0;
        else j++;
    }
    return pts[j].y();
}

void MainWindow::makeEdgeRec(QPoint lower, QPoint upper, int yComp, Edge * edge, Edge * edges[]){
    int grid_size = ui->grid_size->value();
    int lim = (height_total/2)/grid_size;

    edge->dxPerScan = (float) (upper.x() - lower.x())/(upper.y()-lower.y());
    edge->xIntersect = lower.x();
    if ((float)(upper.y()) < (float)(yComp - 0.5)) edge->yUpper = upper.y() - 1;
    else edge->yUpper = upper.y();
    insertEdge (edges[lower.y()+lim], edge);
}

void MainWindow::buildEdgeList (std::vector<QPoint> pts, Edge * edges[]){
    int cnt = pts.size();
    int yPrev = pts[cnt-2].y();

    QPoint v1, v2;

    v1.setX(pts[cnt-1].x());
    v1.setY(pts[cnt-1].y());

    for (int i = 0; i < cnt; i++){
        v2 = pts[i];
        if (v1.y() != v2.y()){
            Edge * edge = new Edge();
            if (v1.y() < v2.y()){
                makeEdgeRec(v1, v2, yNext(i, pts), edge, edges);
            } else {
                makeEdgeRec(v2, v1, yPrev, edge, edges);
            }
        }
        yPrev = v1.y();
        v1 = v2;
    }
}

void MainWindow::buildActiveList (int scan, Edge * active, Edge * edges[]){
    Edge * p = edges[scan]->next;
    while (p){
        Edge * q = p->next;
        insertEdge (active, p);
        p = q;
    }
}

void MainWindow::fillScan (int scan, Edge * active){
    Edge *p1 = active->next;
    while (p1){
        if (p1 == NULL) return;
        Edge * p2 = p1->next;

        for (int i = p1->xIntersect; i < p2->xIntersect; i++){
            draw_pt (i, scan, qRgb(255, 255, 255));
            ui->frame->repaint();
            Sleeper::msleep(1);
        }
        p1 = p2->next;
    }
}

void MainWindow::deleteAfter (Edge * q) {
    Edge *p = q->next;
    q->next = p->next;
    free(p);
}

void MainWindow::updateActiveList (int scan, Edge * active){
    Edge *q = active;
    Edge *p = active->next;

    while (p){
        if (scan >= p->yUpper){
            p=p->next;
            deleteAfter(q);
        } else {
            p->xIntersect = p->xIntersect + p->dxPerScan;
            q = p;
            p = p->next;
        }
    }
}

void MainWindow::resortActiveList (Edge * active){
    Edge *p = active->next;
    active->next = NULL;
    while (p) {
        Edge *q = p->next;
        insertEdge(active, p);
        p = q;
    }
}

void MainWindow::_scan_fill(std::vector<QPoint> list_pts){

    int r = ui->red_color_spinbox->value();
    int g = ui->green_color_spinbox->value();
    int b = ui->blue_color_spinbox->value();
    ui->red_color_spinbox->setValue(255);
    ui->green_color_spinbox->setValue(255);
    ui->blue_color_spinbox->setValue(255);
    for (int i = 0; i < list_pts.size()-1; i++){
        _dda_line_scanfill(list_pts[i].x(), list_pts[i].y(), list_pts[i+1].x(), list_pts[i+1].y());
    }
    _dda_line_scanfill(list_pts[0].x(), list_pts[0].y(), list_pts[list_pts.size()-1].x(), list_pts[list_pts.size()-1].y());
    ui->red_color_spinbox->setValue(r);
    ui->green_color_spinbox->setValue(g);
    ui->blue_color_spinbox->setValue(b);

    int grid_size = ui->grid_size->value();
    int lim = (height_total/2)/grid_size;

    Edge * edges [lim*2+1];

    for (int i = -1*lim; i <=lim; i++){
        edges[lim+i] = new Edge();
        edges[lim+i]->next = NULL;
    }

    buildEdgeList (list_pts, edges);

//    for (int i = -1*lim; i <= lim; i++){
//        Edge * temp = edges[lim+1];
//        while (temp){
//            std::cout << i << ":::";
//            std::cout << "(" << temp->yUpper << ", " << temp->dxPerScan << ", " << temp->xIntersect << ") -> ";
//            temp = temp->next;
//        } std::cout << std::endl;
//    }

    Edge * active = new Edge();
    active->next = NULL;

    for (int scan = -1*lim; scan <= lim; scan++){
        buildActiveList (scan+lim, active, edges);
        if (active->next){
            fillScan(scan, active);
            updateActiveList (scan, active);
            resortActiveList (active);
        }
    }





}


#endif // SCANFILL_H
