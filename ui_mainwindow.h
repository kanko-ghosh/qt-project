/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
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
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1219, 736);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        frame = new my_label(centralWidget);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(0, 0, 700, 700));
        frame->setCursor(QCursor(Qt::CrossCursor));
        frame->setMouseTracking(true);
        frame->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 0);"));
        frame->setFrameShape(QFrame::Box);
        frame->setLineWidth(1);
        mouse_movement = new QLabel(centralWidget);
        mouse_movement->setObjectName(QString::fromUtf8("mouse_movement"));
        mouse_movement->setGeometry(QRect(1090, 280, 111, 31));
        mouse_movement->setFrameShape(QFrame::Panel);
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(1090, 260, 111, 20));
        mouse_pressed = new QLabel(centralWidget);
        mouse_pressed->setObjectName(QString::fromUtf8("mouse_pressed"));
        mouse_pressed->setGeometry(QRect(1090, 350, 111, 31));
        mouse_pressed->setFrameShape(QFrame::Panel);
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(1100, 330, 81, 20));
        x_axis = new QFrame(centralWidget);
        x_axis->setObjectName(QString::fromUtf8("x_axis"));
        x_axis->setGeometry(QRect(0, 225, 700, 5));
        x_axis->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        x_axis->setFrameShadow(QFrame::Raised);
        x_axis->setLineWidth(0);
        x_axis->setFrameShape(QFrame::HLine);
        y_axis = new QFrame(centralWidget);
        y_axis->setObjectName(QString::fromUtf8("y_axis"));
        y_axis->setGeometry(QRect(225, 0, 5, 700));
        y_axis->setStyleSheet(QString::fromUtf8("\n"
"background-color: rgb(255, 255, 255);"));
        y_axis->setFrameShadow(QFrame::Raised);
        y_axis->setLineWidth(0);
        y_axis->setFrameShape(QFrame::VLine);
        show_axes = new QCheckBox(centralWidget);
        show_axes->setObjectName(QString::fromUtf8("show_axes"));
        show_axes->setGeometry(QRect(1100, 230, 91, 21));
        circle_radius = new QSpinBox(centralWidget);
        circle_radius->setObjectName(QString::fromUtf8("circle_radius"));
        circle_radius->setGeometry(QRect(790, 240, 46, 20));
        circle_radius->setMinimum(1);
        set_point1 = new QPushButton(centralWidget);
        set_point1->setObjectName(QString::fromUtf8("set_point1"));
        set_point1->setGeometry(QRect(1120, 120, 81, 23));
        set_point2 = new QPushButton(centralWidget);
        set_point2->setObjectName(QString::fromUtf8("set_point2"));
        set_point2->setGeometry(QRect(1120, 150, 81, 23));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(940, 200, 101, 41));
        show_grid = new QCheckBox(centralWidget);
        show_grid->setObjectName(QString::fromUtf8("show_grid"));
        show_grid->setGeometry(QRect(1120, 10, 93, 26));
        grid_size = new QSpinBox(centralWidget);
        grid_size->setObjectName(QString::fromUtf8("grid_size"));
        grid_size->setGeometry(QRect(1120, 50, 91, 29));
        grid_size->setMinimum(5);
        grid_size->setSingleStep(2);
        bresenham_line = new QPushButton(centralWidget);
        bresenham_line->setObjectName(QString::fromUtf8("bresenham_line"));
        bresenham_line->setGeometry(QRect(725, 82, 111, 31));
        dda = new QPushButton(centralWidget);
        dda->setObjectName(QString::fromUtf8("dda"));
        dda->setGeometry(QRect(725, 42, 111, 31));
        time_label = new QLabel(centralWidget);
        time_label->setObjectName(QString::fromUtf8("time_label"));
        time_label->setGeometry(QRect(1096, 580, 91, 20));
        time_show = new QLabel(centralWidget);
        time_show->setObjectName(QString::fromUtf8("time_show"));
        time_show->setGeometry(QRect(1080, 610, 121, 41));
        time_show->setFrameShape(QFrame::Panel);
        time_show->setAlignment(Qt::AlignCenter);
        line_label = new QLabel(centralWidget);
        line_label->setObjectName(QString::fromUtf8("line_label"));
        line_label->setGeometry(QRect(720, 13, 121, 20));
        line_label->setAlignment(Qt::AlignCenter);
        circle_label = new QLabel(centralWidget);
        circle_label->setObjectName(QString::fromUtf8("circle_label"));
        circle_label->setGeometry(QRect(714, 128, 131, 20));
        circle_label->setAlignment(Qt::AlignCenter);
        polar_circle = new QPushButton(centralWidget);
        polar_circle->setObjectName(QString::fromUtf8("polar_circle"));
        polar_circle->setGeometry(QRect(725, 156, 111, 31));
        bresenham_cicle = new QPushButton(centralWidget);
        bresenham_cicle->setObjectName(QString::fromUtf8("bresenham_cicle"));
        bresenham_cicle->setGeometry(QRect(725, 196, 111, 31));
        radius = new QLabel(centralWidget);
        radius->setObjectName(QString::fromUtf8("radius"));
        radius->setGeometry(QRect(720, 240, 51, 20));
        ellipse_label = new QLabel(centralWidget);
        ellipse_label->setObjectName(QString::fromUtf8("ellipse_label"));
        ellipse_label->setGeometry(QRect(720, 272, 121, 20));
        polar_ellipse = new QPushButton(centralWidget);
        polar_ellipse->setObjectName(QString::fromUtf8("polar_ellipse"));
        polar_ellipse->setGeometry(QRect(724, 299, 111, 31));
        bresenham_ellipse = new QPushButton(centralWidget);
        bresenham_ellipse->setObjectName(QString::fromUtf8("bresenham_ellipse"));
        bresenham_ellipse->setGeometry(QRect(725, 340, 111, 31));
        radius_2 = new QLabel(centralWidget);
        radius_2->setObjectName(QString::fromUtf8("radius_2"));
        radius_2->setGeometry(QRect(720, 390, 61, 20));
        radius_x = new QSpinBox(centralWidget);
        radius_x->setObjectName(QString::fromUtf8("radius_x"));
        radius_x->setGeometry(QRect(790, 390, 46, 20));
        radius_x->setMinimum(1);
        radius_y = new QSpinBox(centralWidget);
        radius_y->setObjectName(QString::fromUtf8("radius_y"));
        radius_y->setGeometry(QRect(790, 420, 46, 20));
        radius_y->setMinimum(1);
        radius_3 = new QLabel(centralWidget);
        radius_3->setObjectName(QString::fromUtf8("radius_3"));
        radius_3->setGeometry(QRect(720, 420, 61, 20));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1219, 25));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
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
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
