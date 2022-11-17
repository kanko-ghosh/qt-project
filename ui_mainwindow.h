/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include <my_label.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    my_label *frame;
    QLabel *mouse_movement;
    QLabel *label_3;
    QLabel *mouse_pressed;
    QLabel *label_5;
    QFrame *x_axis;
    QFrame *y_axis;
    QCheckBox *show_axes;
    QSpinBox *circle_radius;
    QPushButton *set_point1;
    QPushButton *set_point2;
    QPushButton *pushButton;
    QCheckBox *show_grid;
    QSpinBox *grid_size;
    QPushButton *bresenham_line;
    QPushButton *dda;
    QLabel *time_label;
    QLabel *time_show;
    QLabel *line_label;
    QLabel *circle_label;
    QPushButton *polar_circle;
    QPushButton *bresenham_cicle;
    QLabel *radius;
    QLabel *ellipse_label;
    QPushButton *polar_ellipse;
    QPushButton *bresenham_ellipse;
    QLabel *radius_2;
    QSpinBox *radius_x;
    QSpinBox *radius_y;
    QLabel *radius_3;
    QPushButton *scanline;
    QSpinBox *red_color_spinbox;
    QSpinBox *green_color_spinbox;
    QSpinBox *blue_color_spinbox;
    QLabel *select_colors;
    QLabel *red_label;
    QLabel *green_label;
    QLabel *blue_label;
    QPushButton *boundary_fill;
    QPushButton *flood_fill;
    QLabel *label;
    QPushButton *translation;
    QPushButton *rotation;
    QPushButton *scaling;
    QPushButton *shear;
    QPushButton *reflection;
    QDoubleSpinBox *translation_x;
    QDoubleSpinBox *tranlation_y;
    QSpinBox *rotation_angle;
    QDoubleSpinBox *scale_x;
    QDoubleSpinBox *scale_y;
    QDoubleSpinBox *shear_x;
    QDoubleSpinBox *shear_y;
    QCheckBox *check_if_x;
    QPushButton *transform;
    QPushButton *beizer_curve_button;
    QPushButton *poly_clip_button;
    QPushButton *line_clipping;
    QDoubleSpinBox *beizer_coeff;
    QPushButton *draw_lines;
    QPushButton *line_clipping_2;
    QPushButton *scanline_2;
    QPushButton *clock;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1219, 736);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName("centralWidget");
        frame = new my_label(centralWidget);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(0, 0, 700, 700));
        frame->setCursor(QCursor(Qt::CrossCursor));
        frame->setMouseTracking(true);
        frame->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 0);"));
        frame->setFrameShape(QFrame::Box);
        frame->setLineWidth(1);
        mouse_movement = new QLabel(centralWidget);
        mouse_movement->setObjectName("mouse_movement");
        mouse_movement->setGeometry(QRect(1090, 330, 111, 31));
        mouse_movement->setFrameShape(QFrame::Panel);
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(1090, 310, 111, 20));
        mouse_pressed = new QLabel(centralWidget);
        mouse_pressed->setObjectName("mouse_pressed");
        mouse_pressed->setGeometry(QRect(1090, 400, 111, 31));
        mouse_pressed->setFrameShape(QFrame::Panel);
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(1100, 380, 81, 20));
        x_axis = new QFrame(centralWidget);
        x_axis->setObjectName("x_axis");
        x_axis->setGeometry(QRect(0, 225, 700, 5));
        x_axis->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        x_axis->setFrameShadow(QFrame::Raised);
        x_axis->setLineWidth(0);
        x_axis->setFrameShape(QFrame::HLine);
        y_axis = new QFrame(centralWidget);
        y_axis->setObjectName("y_axis");
        y_axis->setGeometry(QRect(225, 0, 5, 700));
        y_axis->setStyleSheet(QString::fromUtf8("\n"
"background-color: rgb(255, 255, 255);"));
        y_axis->setFrameShadow(QFrame::Raised);
        y_axis->setLineWidth(0);
        y_axis->setFrameShape(QFrame::VLine);
        show_axes = new QCheckBox(centralWidget);
        show_axes->setObjectName("show_axes");
        show_axes->setGeometry(QRect(890, 470, 91, 21));
        circle_radius = new QSpinBox(centralWidget);
        circle_radius->setObjectName("circle_radius");
        circle_radius->setGeometry(QRect(790, 240, 46, 20));
        circle_radius->setMinimum(1);
        set_point1 = new QPushButton(centralWidget);
        set_point1->setObjectName("set_point1");
        set_point1->setGeometry(QRect(890, 600, 81, 23));
        set_point2 = new QPushButton(centralWidget);
        set_point2->setObjectName("set_point2");
        set_point2->setGeometry(QRect(890, 630, 81, 23));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(730, 620, 101, 41));
        show_grid = new QCheckBox(centralWidget);
        show_grid->setObjectName("show_grid");
        show_grid->setGeometry(QRect(890, 490, 93, 26));
        grid_size = new QSpinBox(centralWidget);
        grid_size->setObjectName("grid_size");
        grid_size->setGeometry(QRect(890, 530, 91, 29));
        grid_size->setMinimum(5);
        grid_size->setSingleStep(2);
        bresenham_line = new QPushButton(centralWidget);
        bresenham_line->setObjectName("bresenham_line");
        bresenham_line->setGeometry(QRect(725, 82, 111, 31));
        dda = new QPushButton(centralWidget);
        dda->setObjectName("dda");
        dda->setGeometry(QRect(725, 42, 111, 31));
        time_label = new QLabel(centralWidget);
        time_label->setObjectName("time_label");
        time_label->setGeometry(QRect(1096, 580, 91, 20));
        time_show = new QLabel(centralWidget);
        time_show->setObjectName("time_show");
        time_show->setGeometry(QRect(1080, 610, 121, 41));
        time_show->setFrameShape(QFrame::Panel);
        time_show->setAlignment(Qt::AlignCenter);
        line_label = new QLabel(centralWidget);
        line_label->setObjectName("line_label");
        line_label->setGeometry(QRect(720, 13, 121, 20));
        line_label->setAlignment(Qt::AlignCenter);
        circle_label = new QLabel(centralWidget);
        circle_label->setObjectName("circle_label");
        circle_label->setGeometry(QRect(714, 128, 131, 20));
        circle_label->setAlignment(Qt::AlignCenter);
        polar_circle = new QPushButton(centralWidget);
        polar_circle->setObjectName("polar_circle");
        polar_circle->setGeometry(QRect(725, 156, 111, 31));
        bresenham_cicle = new QPushButton(centralWidget);
        bresenham_cicle->setObjectName("bresenham_cicle");
        bresenham_cicle->setGeometry(QRect(725, 196, 111, 31));
        radius = new QLabel(centralWidget);
        radius->setObjectName("radius");
        radius->setGeometry(QRect(720, 240, 51, 20));
        ellipse_label = new QLabel(centralWidget);
        ellipse_label->setObjectName("ellipse_label");
        ellipse_label->setGeometry(QRect(720, 272, 121, 20));
        polar_ellipse = new QPushButton(centralWidget);
        polar_ellipse->setObjectName("polar_ellipse");
        polar_ellipse->setGeometry(QRect(724, 299, 111, 31));
        bresenham_ellipse = new QPushButton(centralWidget);
        bresenham_ellipse->setObjectName("bresenham_ellipse");
        bresenham_ellipse->setGeometry(QRect(725, 340, 111, 31));
        radius_2 = new QLabel(centralWidget);
        radius_2->setObjectName("radius_2");
        radius_2->setGeometry(QRect(720, 390, 61, 20));
        radius_x = new QSpinBox(centralWidget);
        radius_x->setObjectName("radius_x");
        radius_x->setGeometry(QRect(790, 390, 46, 20));
        radius_x->setMinimum(1);
        radius_y = new QSpinBox(centralWidget);
        radius_y->setObjectName("radius_y");
        radius_y->setGeometry(QRect(790, 420, 46, 20));
        radius_y->setMinimum(1);
        radius_3 = new QLabel(centralWidget);
        radius_3->setObjectName("radius_3");
        radius_3->setGeometry(QRect(720, 420, 61, 20));
        scanline = new QPushButton(centralWidget);
        scanline->setObjectName("scanline");
        scanline->setGeometry(QRect(725, 460, 111, 31));
        red_color_spinbox = new QSpinBox(centralWidget);
        red_color_spinbox->setObjectName("red_color_spinbox");
        red_color_spinbox->setGeometry(QRect(1150, 475, 44, 26));
        red_color_spinbox->setMaximum(255);
        green_color_spinbox = new QSpinBox(centralWidget);
        green_color_spinbox->setObjectName("green_color_spinbox");
        green_color_spinbox->setGeometry(QRect(1150, 505, 44, 26));
        green_color_spinbox->setMaximum(255);
        blue_color_spinbox = new QSpinBox(centralWidget);
        blue_color_spinbox->setObjectName("blue_color_spinbox");
        blue_color_spinbox->setGeometry(QRect(1150, 535, 44, 26));
        blue_color_spinbox->setMaximum(255);
        select_colors = new QLabel(centralWidget);
        select_colors->setObjectName("select_colors");
        select_colors->setGeometry(QRect(1100, 455, 91, 17));
        red_label = new QLabel(centralWidget);
        red_label->setObjectName("red_label");
        red_label->setGeometry(QRect(1100, 480, 67, 17));
        green_label = new QLabel(centralWidget);
        green_label->setObjectName("green_label");
        green_label->setGeometry(QRect(1100, 510, 67, 17));
        blue_label = new QLabel(centralWidget);
        blue_label->setObjectName("blue_label");
        blue_label->setGeometry(QRect(1100, 540, 67, 17));
        boundary_fill = new QPushButton(centralWidget);
        boundary_fill->setObjectName("boundary_fill");
        boundary_fill->setGeometry(QRect(725, 500, 111, 31));
        flood_fill = new QPushButton(centralWidget);
        flood_fill->setObjectName("flood_fill");
        flood_fill->setGeometry(QRect(725, 540, 111, 31));
        label = new QLabel(centralWidget);
        label->setObjectName("label");
        label->setGeometry(QRect(926, 39, 111, 17));
        translation = new QPushButton(centralWidget);
        translation->setObjectName("translation");
        translation->setGeometry(QRect(923, 81, 89, 25));
        rotation = new QPushButton(centralWidget);
        rotation->setObjectName("rotation");
        rotation->setGeometry(QRect(923, 111, 89, 25));
        scaling = new QPushButton(centralWidget);
        scaling->setObjectName("scaling");
        scaling->setGeometry(QRect(923, 141, 89, 25));
        shear = new QPushButton(centralWidget);
        shear->setObjectName("shear");
        shear->setGeometry(QRect(923, 171, 89, 25));
        reflection = new QPushButton(centralWidget);
        reflection->setObjectName("reflection");
        reflection->setGeometry(QRect(923, 202, 89, 25));
        translation_x = new QDoubleSpinBox(centralWidget);
        translation_x->setObjectName("translation_x");
        translation_x->setGeometry(QRect(1050, 80, 44, 26));
        translation_x->setMinimum(-100.000000000000000);
        tranlation_y = new QDoubleSpinBox(centralWidget);
        tranlation_y->setObjectName("tranlation_y");
        tranlation_y->setGeometry(QRect(1130, 80, 44, 26));
        tranlation_y->setMinimum(-100.000000000000000);
        rotation_angle = new QSpinBox(centralWidget);
        rotation_angle->setObjectName("rotation_angle");
        rotation_angle->setGeometry(QRect(1050, 110, 44, 26));
        rotation_angle->setMinimum(-180);
        scale_x = new QDoubleSpinBox(centralWidget);
        scale_x->setObjectName("scale_x");
        scale_x->setGeometry(QRect(1050, 140, 44, 26));
        scale_y = new QDoubleSpinBox(centralWidget);
        scale_y->setObjectName("scale_y");
        scale_y->setGeometry(QRect(1130, 140, 44, 26));
        shear_x = new QDoubleSpinBox(centralWidget);
        shear_x->setObjectName("shear_x");
        shear_x->setGeometry(QRect(1050, 171, 44, 26));
        shear_x->setMinimum(-99.000000000000000);
        shear_y = new QDoubleSpinBox(centralWidget);
        shear_y->setObjectName("shear_y");
        shear_y->setGeometry(QRect(1130, 170, 44, 26));
        shear_y->setMinimum(-99.000000000000000);
        check_if_x = new QCheckBox(centralWidget);
        check_if_x->setObjectName("check_if_x");
        check_if_x->setGeometry(QRect(1053, 203, 92, 23));
        transform = new QPushButton(centralWidget);
        transform->setObjectName("transform");
        transform->setGeometry(QRect(1050, 30, 121, 31));
        beizer_curve_button = new QPushButton(centralWidget);
        beizer_curve_button->setObjectName("beizer_curve_button");
        beizer_curve_button->setGeometry(QRect(929, 239, 121, 31));
        poly_clip_button = new QPushButton(centralWidget);
        poly_clip_button->setObjectName("poly_clip_button");
        poly_clip_button->setGeometry(QRect(930, 280, 121, 31));
        line_clipping = new QPushButton(centralWidget);
        line_clipping->setObjectName("line_clipping");
        line_clipping->setGeometry(QRect(880, 390, 121, 31));
        beizer_coeff = new QDoubleSpinBox(centralWidget);
        beizer_coeff->setObjectName("beizer_coeff");
        beizer_coeff->setGeometry(QRect(1058, 241, 65, 26));
        beizer_coeff->setMaximum(1.000000000000000);
        draw_lines = new QPushButton(centralWidget);
        draw_lines->setObjectName("draw_lines");
        draw_lines->setGeometry(QRect(880, 350, 121, 31));
        line_clipping_2 = new QPushButton(centralWidget);
        line_clipping_2->setObjectName("line_clipping_2");
        line_clipping_2->setGeometry(QRect(880, 430, 121, 31));
        scanline_2 = new QPushButton(centralWidget);
        scanline_2->setObjectName("scanline_2");
        scanline_2->setGeometry(QRect(720, 580, 111, 31));
        clock = new QPushButton(centralWidget);
        clock->setObjectName("clock");
        clock->setGeometry(QRect(890, 570, 89, 25));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName("menuBar");
        menuBar->setGeometry(QRect(0, 0, 1219, 22));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName("mainToolBar");
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName("statusBar");
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        frame->setText(QString());
        mouse_movement->setText(QString());
        label_3->setText(QCoreApplication::translate("MainWindow", "    Mouse Movement", nullptr));
        mouse_pressed->setText(QString());
        label_5->setText(QCoreApplication::translate("MainWindow", "Mouse Pressed", nullptr));
        show_axes->setText(QCoreApplication::translate("MainWindow", "Show Axes", nullptr));
        set_point1->setText(QCoreApplication::translate("MainWindow", "Set point 1", nullptr));
        set_point2->setText(QCoreApplication::translate("MainWindow", "Set point 2", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "RESET", nullptr));
        show_grid->setText(QCoreApplication::translate("MainWindow", "Show Grid", nullptr));
        bresenham_line->setText(QCoreApplication::translate("MainWindow", "Bresenham", nullptr));
        dda->setText(QCoreApplication::translate("MainWindow", "DDA", nullptr));
        time_label->setText(QCoreApplication::translate("MainWindow", "Time Elapsed", nullptr));
        time_show->setText(QString());
        line_label->setText(QCoreApplication::translate("MainWindow", "Line Algorithms", nullptr));
        circle_label->setText(QCoreApplication::translate("MainWindow", "Circle Algorithms", nullptr));
        polar_circle->setText(QCoreApplication::translate("MainWindow", "Polar", nullptr));
        bresenham_cicle->setText(QCoreApplication::translate("MainWindow", "Bresenham", nullptr));
        radius->setText(QCoreApplication::translate("MainWindow", "Radius", nullptr));
        ellipse_label->setText(QCoreApplication::translate("MainWindow", "Ellipse Algorithms", nullptr));
        polar_ellipse->setText(QCoreApplication::translate("MainWindow", "Polar", nullptr));
        bresenham_ellipse->setText(QCoreApplication::translate("MainWindow", "Bresenham", nullptr));
        radius_2->setText(QCoreApplication::translate("MainWindow", "Radius-X", nullptr));
        radius_3->setText(QCoreApplication::translate("MainWindow", "Radius-Y", nullptr));
        scanline->setText(QCoreApplication::translate("MainWindow", "ScanLine-Fill", nullptr));
        select_colors->setText(QCoreApplication::translate("MainWindow", "Select Colors", nullptr));
        red_label->setText(QCoreApplication::translate("MainWindow", "RED", nullptr));
        green_label->setText(QCoreApplication::translate("MainWindow", "GREEN", nullptr));
        blue_label->setText(QCoreApplication::translate("MainWindow", "BLUE", nullptr));
        boundary_fill->setText(QCoreApplication::translate("MainWindow", "Boundary Fill", nullptr));
        flood_fill->setText(QCoreApplication::translate("MainWindow", "Flood Fill", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Transformation", nullptr));
        translation->setText(QCoreApplication::translate("MainWindow", "Translation", nullptr));
        rotation->setText(QCoreApplication::translate("MainWindow", "Rotation", nullptr));
        scaling->setText(QCoreApplication::translate("MainWindow", "Scaling", nullptr));
        shear->setText(QCoreApplication::translate("MainWindow", "Shear", nullptr));
        reflection->setText(QCoreApplication::translate("MainWindow", "Reflection", nullptr));
        check_if_x->setText(QCoreApplication::translate("MainWindow", "X-axis?", nullptr));
        transform->setText(QCoreApplication::translate("MainWindow", "Draw Polygon", nullptr));
        beizer_curve_button->setText(QCoreApplication::translate("MainWindow", "Beizer Curve", nullptr));
        poly_clip_button->setText(QCoreApplication::translate("MainWindow", "Polygon_clipping", nullptr));
        line_clipping->setText(QCoreApplication::translate("MainWindow", "LC Cohen Sund.", nullptr));
        draw_lines->setText(QCoreApplication::translate("MainWindow", "Draw Lines", nullptr));
        line_clipping_2->setText(QCoreApplication::translate("MainWindow", "LC Liang Barsky", nullptr));
        scanline_2->setText(QCoreApplication::translate("MainWindow", "ScanLine-Fill-2", nullptr));
        clock->setText(QCoreApplication::translate("MainWindow", "Clock", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
