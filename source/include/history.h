#ifndef HISTORY_H
#define HISTORY_H

#include <QWidget>
#include "QLabel"
#include "QTimer"
#include <QtCharts>
#include <QtCharts/QChartView>//显示图表
#include <QtCharts/QLineSeries>//线系列
#include <QtCharts/QSplineSeries>//线系列
#include "QtCharts/QValueAxis"//坐标轴系列
#include <QDoubleSpinBox>
#include "sqlite3.h"
#include "QDateTime"
#include "QComboBox"
QT_CHARTS_USE_NAMESPACE
class History : public QWidget
{
    Q_OBJECT
public:
    explicit History(QWidget *parent = nullptr);
     void set_parent_view(QWidget * parent);
     void add_data(void);
protected:
     static int sqlit3_find_calback(void * data, int col_count, char ** col_values, char ** col_Name);
     static qint64 time[3600];
     static float value[3600] ;
     static int key_boad_cnt;
     static qint64 cycle;//展示数据的总时间
     static qint64 cycle_unit;
     void paintEvent(QPaintEvent *event) override;
private:
     QTimer *Refresh_Timer;
     QLabel *time_label;
     QDateTimeAxis  *axisx =new QDateTimeAxis();
     QValueAxis *axisy =new QValueAxis;
      QSplineSeries *series= new QSplineSeries();
       QChart *chart =new QChart();
       QChartView *chartView =new QChartView(chart,this);
       QWidget *parent_view;


     void paint_charts(void);
private slots:
     void back(void);
     void set_clock(void);
     void update_slot(int index);
signals:

};
#endif // HISTORY_H
