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

    void on_boundary_fill_clicked();

    void on_flood_fill_clicked();


    void on_transform_clicked();

    void on_translation_clicked();

    void on_rotation_clicked();

    void on_scaling_clicked();

    void on_shear_clicked();

    void on_reflection_clicked();

    void on_beizer_curve_button_clicked();

    void on_poly_clip_button_clicked();

    void on_line_clipping_clicked();

    void on_draw_lines_clicked();

    void on_line_clipping_2_clicked();

    void on_scanline_2_clicked();

    void on_clock_clicked();

private:
    Ui::MainWindow *ui;
    QPoint p1,p2;
    void point(int,int);
    float matrix[3][3];

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
    bool isClockAnimating = false;
    void _polar_circle(int x1, int y1, int r);
    void _polar_circle_debug(int xc, int yc, int r);
    void _polar_circle_clock(int xc, int yc, int r);
    void _bresenham_circle(int xc, int yc, int r);
    void _bresenham_circle_debug(int xc, int yc, int r);
    void animateClock();

    //ellipse
    void _polar_ellipse(int xc, int yc, int rx, int ry);
    void _polar_ellipse_debug(int xc, int yc, int rx, int ry);
    void _bresenham_ellipse(int xc, int yc, int rx, int ry);
    void _bresenham_ellipse_debug(int xc, int yc, int rx, int ry);

    //scanfill
    int to_do = 1;
    int count;
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

    //seedfill
    void _boundary_fill(std::vector<QPoint> list_scan);
    void _rec_boundary (int x, int y, QColor target_color, QRgb boundary_color);
    void _flood_fill(int x, int y);
    void _rec_flood (int x, int y , QColor seed_color);

    //scanfill 2.0
    int inter[20],x,y;
    int xmin,ymin,xmax,ymax;

    int c_scan;
    void calcs();
    void ints(int);
    void sort(int);

    //transformation
    std::vector<std::pair<float, float> > polygon;
    void draw_poly(std::vector<std::pair<float, float> > list_pts);
    void init_matrix();
    void draw_poly(std::vector<QPoint> list);

    //beizer
    int comb(int n, int r);
};

#endif // MAINWINDOW_H
