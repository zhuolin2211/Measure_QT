
#ifndef MAIN_H
#define MAIN_H
#include "QWidget"
#include "QDateTime"
#include "QLabel"
#include "QStackedWidget"
#include "QPainter"
#include "menu.h"
#include "history.h"
#include "mainwindow.h"
#include "app_measure.h"
#include "app_output.h"
void Refresh_Time(QWidget * parent);
void background(QWidget *parent );
extern App_Measure *measure_main;
extern App_Output *output;
#endif // MAIN_H
