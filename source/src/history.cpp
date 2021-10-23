#include "history.h"
#include "QPushButton"
#include "QDateTime"
#include "main.h"
#include "stdio.h"
#include "platform_config.h"
extern App_Measure *measure_main;
History::History(QWidget *parent) : QWidget(parent)
{
setAttribute(Qt::WA_DeleteOnClose);
this->parent_view=parent;
    this->setFixedSize(800,480);
    QFont font_name;
    QLabel *_name=new QLabel(this);
    font_name.setPixelSize(25);
    _name->setFont(font_name);
    _name->setText("悬浮物浓度仪");
    _name->setGeometry(320,440,250,40);
        QFont font;
        font.setPixelSize(15);
       QPushButton *back=new QPushButton(this);
       back->setText("返回");
       back->setFont(font);
       back->setGeometry(30,440,90,40);
       QIcon back_icon;
       back_icon.addFile(":/icon/resoure/icon/back.png");
       back->setIconSize(QSize(35,35));
       back->setIcon(back_icon);
       back->setFlat(true);

       QFont time_label_font;
       time_label_font.setPixelSize(30);
       time_label=new QLabel(this);
       time_label->setGeometry(500,5,400,30);
       time_label->setFont(time_label_font);
       QDateTime new_time = QDateTime::currentDateTime();
       time_label->setText(new_time.toString("yyyy.MM.dd hh:mm:ss"));
       Refresh_Timer =new QTimer(this);
       Refresh_Timer->start(1000);
       connect(this->Refresh_Timer,SIGNAL(timeout()),this,SLOT(set_clock()));
       connect(back,SIGNAL(clicked()),this,SLOT(back()));

       /*图表*/
       paint_charts();

#if RASPBERRY_PI
    this->showFullScreen();
#endif

}
 void History::paint_charts(void)
 {
     add_data();

     //设置线条颜色，如果不设置会给默认颜色

     series->setColor(QColor(255,0,255));
     chart->setTheme(QChart::ChartThemeBlueCerulean);//设置系统主题
     chart->setAnimationOptions(QChart::GridAxisAnimations);//设置启用或禁用动画
     chart->setLocalizeNumbers(false);//数字是否本地化
     chart->addSeries(series);//添加系列到QChart上
     //chart->legend()->deleteLater();//删除(这句再在树莓派上会造成闪退)
     chart->legend()->hide();//使用该句替代
     chart->setTitleBrush(QBrush(QColor(255,0,0)));//设置标题Brush
     chart->setTitleFont(QFont("微软雅黑"));//设置标题字体

     axisy->setRange(0,100);//设置坐标轴范围
     axisy->setTickCount(10+1);//设置坐标区间格数
     axisx->setTickCount(10+1);
     axisy->setLabelFormat("%d%");
     axisx->setFormat("HH:mm:ss");
     axisy->setTitleText("浊度 %");
     axisx->setTitleText("日期/分钟");
     axisx->setLabelsAngle(70);
     axisy->setGridLineVisible(false);
     axisx->setGridLineVisible(false);

     chart->addAxis(axisy,Qt::AlignLeft);
     chart->addAxis(axisx,Qt::AlignBottom);

     series->attachAxis(axisx);
      series->attachAxis(axisy);
     chartView->setRenderHint(QPainter::Antialiasing);
     chartView->setGeometry(20,40,760,400);

     /*选择展示时间段*/

      QComboBox *select_combox=new QComboBox(this);
      select_combox->setGeometry(600,60,150,30);
      select_combox->insertItem(0,"1小时");
      select_combox->insertItem(1,"24小时");
      select_combox->insertItem(2,"一个月");
      select_combox->insertItem(3,"一年");
      this->connect(select_combox,SIGNAL(activated(int )),this,SLOT(update_slot(int )));

 }
 void History::set_parent_view(QWidget * parent)
 {
     this-> parent_view= parent;
 }
void History::paintEvent(QPaintEvent *)
{
    background(this);
}
void History::set_clock(void)
{
    QDateTime new_time = QDateTime::currentDateTime();
    this->time_label->setText(new_time.toString("yyyy.MM.dd hh:mm:ss"));
}
void History::back(void)
{
    this->parent_view->show();
    this->close();
}

#define CREAT_TABLE "create table test2(tempindex integer,value real);"
#define FIND_DATA "select * from test2 where tempindex>%ld and tempindex<%lld"




void History::add_data(void)
{
    sqlite3* database;
    char command[256];
   int ret = 0;
    char *error_msg=(char*)malloc(256);
    measure_main->Database_mutex->lock();
    ret =sqlite3_open(database_file, &database);
       if (ret != SQLITE_OK)
       {
           qDebug("数据库打开失败\n");
           return ;
       }
       qDebug()<<cycle<<cycle_unit;
       sprintf(command,FIND_DATA,QDateTime::currentMSecsSinceEpoch()/1000-cycle,QDateTime::currentMSecsSinceEpoch()/1000);
       this->axisx->setRange(QDateTime::fromMSecsSinceEpoch(QDateTime::currentMSecsSinceEpoch()-(cycle*1000)),QDateTime::currentDateTime());

       qDebug()<<command;
       ret= sqlite3_exec(database,command,sqlit3_find_calback,0,&error_msg);
       if(ret !=SQLITE_OK)
       {
           qDebug("数据库打开失败 %s\n",error_msg);
       }
       else
       {
        qDebug("数据读取成功\n");
        QVector<QPointF> point_list;
        point_list.clear();
        for(int i=0;i<History::key_boad_cnt;i++)
        {
            point_list.append(QPointF(History::time[i]*1000,History::value[i]));
        }
        this->series->replace(point_list);
        qDebug()<<  History::key_boad_cnt;
       }
       History::key_boad_cnt=0;
       sqlite3_close(database);
       measure_main->Database_mutex->unlock();
        free(error_msg);
}
#define POINT_MAX 3600
 int History::key_boad_cnt=0;
  qint64 History::time[POINT_MAX];
 float History::value[POINT_MAX] ;
 qint64 History::cycle=3600;
 qint64 History::cycle_unit=cycle/POINT_MAX;
 int History::sqlit3_find_calback(void * data, int col_count, char ** col_values, char ** col_Name)
{
     if(History::key_boad_cnt>=POINT_MAX)
     {
         return 0;
     }


for(int i=0;i<col_count;i++)
{
    if(strcmp(col_Name[i],"tempindex")==0)
    {
        QString value_number =QString(col_values[i]);
        History::time[History::key_boad_cnt]=value_number.toLongLong();;
    }
    else if(strcmp(col_Name[i],"value")==0)
    {
        QString value_number =QString(col_values[i]);
        History::value[History::key_boad_cnt]=value_number.toFloat();
    }
}
if((History::time[History::key_boad_cnt]%cycle_unit)==0)
{
   History::key_boad_cnt++;
}
return 0;
}
 void History::update_slot(int index)
 {
    switch (index)
    {
    case 0://1小时
    {
        cycle = 3600;
        cycle_unit=cycle/POINT_MAX;
        break;
    }
    case 1://24小时
    {
        cycle = 86400;
        cycle_unit=cycle/POINT_MAX;
        break;
    }
    case 2://一个月
    {
        cycle = 2592000;
        cycle_unit=cycle/POINT_MAX;
        break;
    }
    case 3://一年
    {
        cycle = 31536000;
        cycle_unit=cycle/POINT_MAX;
        break;
    }
    default:
        return;
    }
    add_data();
 }
