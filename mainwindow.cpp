#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "qlabel.h"
#include "QtWidgets"
#include "QIcon"
#include "QLCDNumber"
#include "QDateTime"
#include "qdebug.h"
#include "menu.h"
#include "history.h"
#include "app_measure.h"
#include "main.h"
extern App_Measure *measure_main;
void background(QWidget *parent );
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

   this->setFixedSize(800,480);


    this->setAttribute(Qt::WA_DeleteOnClose);
    /*公司图标*/
    QLabel *_name=new QLabel(this);
    QFont pen;
    pen.setPixelSize(25);
    _name->setFont(pen);
    _name->setText("悬浮物浓度仪");
    _name->setGeometry(320,440,250,40);

    LED1 =new LED(this);//继电器开关
    LED2 =new LED(this);
    LED3 =new LED(this);
    LED1->setGeometry(30,100,90,80);
    LED1->setimg(RELAY_STATE_OFF_FILE);
    LED2->setGeometry(30,170,90,80);
    LED2->setimg(RELAY_STATE_OFF_FILE);
    LED3->setGeometry(30,240,90,80);
    LED3->setimg(RELAY_STATE_OFF_FILE);
    pen.setPixelSize(15);
    QLabel *relay1_text=new QLabel(this);
    relay1_text->setText("高限报警");
    relay1_text->setFont(pen);
    relay1_text->setGeometry(120,100,200,80);
    QLabel *relay2_text=new QLabel(this);
     relay2_text->setText("低限报警");
     relay2_text->setFont(pen);
      relay2_text->setGeometry(120,170,200,80);
    QLabel *relay3_text=new QLabel(this);
     relay3_text->setText("清洗");
     relay3_text->setFont(pen);
     relay3_text->setGeometry(120,240,200,80);

     Manual_Clean =new QPushButton(this);
     Manual_Clean->setGeometry(200,255,80,60);
     QIcon Manual_Clean_icon;
     Manual_Clean_icon.addFile(":/icon/resoure/icon/clean.png");
      Manual_Clean->setIconSize(QSize(35,35));
     Manual_Clean->setIcon( Manual_Clean_icon);
     Manual_Clean->setStyleSheet("QPushButton{background-color:#9AC0CD;\
                    color: black;border-radius: 10px;  border: 4px groove gray;\
                          border-style: outset;}"
                        "QPushButton:pressed{background-color:#EE6A50;\
                                         border-style: inset; }");

     /**将这一段放到槽函数中**/
     /*绘制 继电器 状态*/
     LED1->setimg(MainWindow::relay1_state?RELAY_STATE_ON_FILE:RELAY_STATE_OFF_FILE);
     LED2->setimg(MainWindow::relay2_state?RELAY_STATE_ON_FILE:RELAY_STATE_OFF_FILE);
     LED3->setimg(MainWindow::relay3_state?RELAY_STATE_ON_FILE:RELAY_STATE_OFF_FILE);
     /********************/
     pen.setWeight(20);
    QPushButton *menu=new QPushButton(this);
    menu->setText("菜单");
    menu->setFont(pen);
    menu->setGeometry(30,440,90,40);
    QIcon menu_icon;
    menu_icon.addFile(":/icon/resoure/icon/menu.png");
    menu->setIconSize(QSize(35,35));
    menu->setIcon(menu_icon);
    menu->setFlat(true);

    QPushButton *history=new QPushButton(this);
    history->setText("历史");
    history->setFont(pen);
    history->setGeometry(690,440,90,40);
    QIcon history_icon;
    history_icon.addFile(":/icon/resoure/icon/history.png");
    history->setIconSize(QSize(35,35));
    history->setIcon(history_icon);
    history->setFlat(true);
    /*数据显示*/
    pen.setPixelSize(100);
    pen.setBold(100);//加粗，权重75
    dispaly_nubmer =new QLabel(this);
    dispaly_nubmer->setGeometry(280,130,400,150);
    dispaly_nubmer->setText("0000.00");
    dispaly_nubmer->setFont(pen);
    dispaly_nubmer->setAlignment(Qt::AlignRight);//文本居右
    set_dispaly_nubmer(0.00);
    QLabel *unit=new QLabel(this);
    QFont unit_font;
    unit_font.setPixelSize(40);
    unit->setFont(unit_font);
    unit->setGeometry(680,200,120,60);
    unit->setText("mg/L");
    /*时间显示*/
    Refresh_Timer =new QTimer(this);
    Refresh_Timer->start(1000);
    QFont time_label_font;
    time_label_font.setPixelSize(30);
    time_label=new QLabel(this);
    time_label->setGeometry(500,5,400,30);
    time_label->setFont(time_label_font);
    QDateTime new_time = QDateTime::currentDateTime();
    time_label->setText(new_time.toString("yyyy.MM.dd hh:mm:ss"));
    connect(Refresh_Timer,SIGNAL(timeout()),this,SLOT(set_clock()));
    connect(menu,SIGNAL(clicked()),this,SLOT(menu_jump()));
    connect(history,SIGNAL(clicked()),this,SLOT(history_jump()));
    connect(measure_main,SIGNAL(App_Measure_muddy(float)),this,SLOT(receive_App_Measure_muddy_slot(float)));
    /*报警操作槽*/
    connect(measure_main,SIGNAL(APP_Measure_Alarm_signal(int)),this,SLOT(Alarm_slot(int)));
    /*手动清洗*/

    connect(Manual_Clean,SIGNAL(clicked()),this,SLOT(Clean_slot()));
#if RASPBERRY_PI
    this->showFullScreen();
#endif

}

MainWindow::~MainWindow()
{
    qDebug("~MainWindow");
    delete ui;
}
void MainWindow::paintEvent(QPaintEvent *)
  {
      background(this);
  }

void MainWindow::set_relay1_state(bool state)
{
    relay1_state=state;
}
void MainWindow::set_relay2_state(bool state)
{
    relay2_state=state;
}
void MainWindow::set_relay3_state(bool state)
{
    relay3_state=state;
}
/*设置主界面显示的测量值*/
void MainWindow::set_dispaly_nubmer(float number)
{
    if(number>=10000)
    {
        dispaly_nubmer->setText("***.**");
    }
    else
    {
    dispaly_nubmer->setText(QString::number(number,'f',2));
    }
}
/*设置时间槽函数*/
void MainWindow::set_clock(void)
{
    QDateTime new_time = QDateTime::currentDateTime();
    time_label->setText(new_time.toString("yyyy.MM.dd hh:mm:ss"));
}
void MainWindow::menu_jump(void)
{

    Menu *menu_view =new Menu();
   menu_view->set_parent_view(this);
   menu_view->show();//菜单界面
   this->hide();
   qDebug("menu_jump");
}
void MainWindow::history_jump(void)
{

    History* history_view=new History();
    history_view->set_parent_view(this);
    history_view->show();//历史界面
    this->hide();

        qDebug("history_jump");
}
/*测量数据更新槽*/
void MainWindow::receive_App_Measure_muddy_slot(float muddy)
{
    qDebug()<<"receive_App_Measure_muddy_slot";
    set_dispaly_nubmer(muddy);
}
/*报警操作槽*/
void MainWindow::Alarm_slot(int alarm)
{
    switch (alarm) {
    case 0:
    {
        LED1->setimg(RELAY_STATE_OFF_FILE);
        LED2->setimg(RELAY_STATE_OFF_FILE);
        qDebug("正常");
        break;
    }
    case 1:
    {
        LED1->setimg(RELAY_STATE_OFF_FILE);
        LED2->setimg(RELAY_STATE_ON_FILE);
        qDebug("低阈值");
        break;
    }
    case 2:
    {
        LED1->setimg(RELAY_STATE_ON_FILE);
        LED2->setimg(RELAY_STATE_OFF_FILE);
        qDebug("高阈值");
        break;
    }

    default :break;
    }
}
void MainWindow::Clean_slot(void)
{

measure_main->App_Measure_Clean(measure_main->App_Measure_Get_Cleannumber());
LED3->setimg(RELAY_STATE_ON_FILE);
Clean_Timer->start(6000*measure_main->App_Measure_Get_Cleannumber());
connect(Clean_Timer,&QTimer::timeout,this,[this](){LED3->setimg(RELAY_STATE_OFF_FILE);Clean_Timer->stop();});
}
