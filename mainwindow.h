#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include <QtCore>

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
    void _dda_line_debug(int x1, int y1, int x2, int y2);
    void _bresenham(int x1, int y1, int x2, int y2);
    void _bresenham_debug(int x1, int y1, int x2, int y2);

    //circle
    void _polar_circle(int x1, int y1, int r);
};

#endif // MAINWINDOW_H
