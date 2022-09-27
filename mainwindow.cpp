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
    if (to_do == 5){
        if (!list_scan.empty() && list_scan.front()==pt){
            this->to_do = 1;
            _scan_fill(list_scan);
        }
        list_scan.push_back(pt);
    }
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

#include "line_algos.h"
#include "circle_algos.h"
#include "ellipse_algos.h"



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
    if (upper.y() < yComp) edge->yUpper = upper.y() - 1;
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


    for (int i = 0; i < list_pts.size()-1; i++){
        _dda_line_scanfill(list_pts[i].x(), list_pts[i].y(), list_pts[i+1].x(), list_pts[i+1].y());
    }
    _dda_line_scanfill(list_pts[0].x(), list_pts[0].y(), list_pts[list_pts.size()-1].x(), list_pts[list_pts.size()-1].y());
}
