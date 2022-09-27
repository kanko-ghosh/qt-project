#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include <QtCore>

class Edge {
public:
    int yUpper;
    float xIntersect;
    float dxPerScan;
    Edge * next;
};

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public slots:
    void Mouse_Pressed();
    void showMousePosition(QPoint& pos);
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_show_axes_clicked();

//    void on_Draw_clicked();

    void on_set_point1_clicked();

    void on_set_point2_clicked();

    void on_pushButton_clicked();

    void on_show_grid_clicked();

    void on_grid_size_valueChanged(int arg1);

    void on_dda_clicked();

    void on_bresenham_line_clicked();

    void on_polar_circle_clicked();

    void on_bresenham_cicle_clicked();

    void on_polar_ellipse_clicked();

    void on_bresenham_ellipse_clicked();

    void on_scanline_clicked();

private:
    Ui::MainWindow *ui;
    QPoint p1,p2;
    void point(int,int);

    //timer
    QElapsedTimer timer;

    //draw a point
    void draw_pt(int x, int y, QRgb color);
    QPoint orig_to_user (int x, int y);

    //line algos
    void _dda_line(int x1, int y1, int x2, int y2);
    void _dda_line_scanfill(int x1, int y1, int x2, int y2);
    void _dda_line_debug(int x1, int y1, int x2, int y2);
    void _bresenham(int x1, int y1, int x2, int y2);
    void _bresenham_debug(int x1, int y1, int x2, int y2);

    //circle
    void _polar_circle(int x1, int y1, int r);
    void _polar_circle_debug(int xc, int yc, int r);
    void _bresenham_circle(int xc, int yc, int r);
    void _bresenham_circle_debug(int xc, int yc, int r);

    //ellipse
    void _polar_ellipse(int xc, int yc, int rx, int ry);
    void _polar_ellipse_debug(int xc, int yc, int rx, int ry);
    void _bresenham_ellipse(int xc, int yc, int rx, int ry);
    void _bresenham_ellipse_debug(int xc, int yc, int rx, int ry);

    //scanfill
    int to_do;
    std::vector<QPoint> list_scan;
    void _scan_fill(std::vector<QPoint> list_scan);
    void resortActiveList (Edge * active);
    void updateActiveList (int scan, Edge * active);
    void deleteAfter (Edge * q);
    void fillScan (int scan, Edge * active);
    void buildActiveList (int scan, Edge * active, Edge * edges[]);
    void buildEdgeList (std::vector<QPoint> pts, Edge * edges[]);
    void makeEdgeRec(QPoint lower, QPoint upper, int yComp, Edge * edge, Edge * edges[]);
    void insertEdge(Edge * list, Edge * edge);
    int yNext (int k, std::vector<QPoint> pts );
};

#endif // MAINWINDOW_H
