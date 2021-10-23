#include "menu.h"
#include <QWidget>
#include "QPushButton"
#include "QDateTime"
#include "QDebug"
#include "main.h"
Menu::Menu(QWidget *parent) : QWidget(parent)
{
    setAttribute(Qt::WA_DeleteOnClose);
    this->setFixedSize(800,480);
    this->setAttribute(Qt::WA_DeleteOnClose,1);
        QFont font;
        QLabel *_name=new QLabel(this);
        font.setPixelSize(25);
        _name->setFont(font);
        _name->setText("悬浮物浓度仪");
        _name->setGeometry(320,440,250,40);



        /*第一排*/
        font.setPointSize(40);
        QPushButton *menu1=new QPushButton("报警\r\n设置",this);
        menu1->setFont(font);
        menu1->setGeometry(ORIGIN_X,ORIGIN_Y,BUTTON_W,BUTTON_H);
        menu1->setStyleSheet("QPushButton{background-color:#9AC0CD;\
                       color: black;border-radius: 10px;  border: 4px groove gray;\
                             border-style: outset;}"
                           "QPushButton:pressed{background-color:#EE6A50;\
                                            border-style: inset; }"
                            );



        QPushButton *menu2=new QPushButton("输出\r\n设置",this);
        menu2->setFont(font);
        menu2->setGeometry(ORIGIN_X+(BUTTON_W+10),ORIGIN_Y,BUTTON_W,BUTTON_H);
        menu2->setStyleSheet("QPushButton{background-color:#9AC0CD;\
                       color: black;border-radius: 10px;  border: 4px groove gray;\
                             border-style: outset;}"
                           "QPushButton:pressed{background-color:#EE6A50;\
                                            border-style: inset; }"
                            );

        QPushButton *menu3=new QPushButton("记录\r\n设置",this);
        menu3->setFont(font);
        menu3->setGeometry(ORIGIN_X+(BUTTON_W+10)*2,ORIGIN_Y,BUTTON_W,BUTTON_H);
        menu3->setStyleSheet("QPushButton{background-color:#9AC0CD;\
                       color: black;border-radius: 10px;  border: 4px groove gray;\
                             border-style: outset;}"
                           "QPushButton:pressed{background-color:#EE6A50;\
                                            border-style: inset; }"
                            );

        QPushButton *menu4=new QPushButton("校准\r\n设置",this);
        menu4->setFont(font);
        menu4->setGeometry(ORIGIN_X+(BUTTON_W+10)*3,ORIGIN_Y,BUTTON_W,BUTTON_H);
        menu4->setStyleSheet("QPushButton{background-color:#9AC0CD;\
                       color: black;border-radius: 10px;  border: 4px groove gray;\
                             border-style: outset;}"
                           "QPushButton:pressed{background-color:#EE6A50;\
                                            border-style: inset; }"
                            );

        /*第二排*/
        QPushButton *menu5=new QPushButton("---",this);
        menu5->setFont(font);
        menu5->setGeometry(ORIGIN_X,ORIGIN_Y+BUTTON_H+10,BUTTON_W,BUTTON_H);
        menu5->setStyleSheet("QPushButton{background-color:#9AC0CD;\
                       color: black;border-radius: 10px;  border: 4px groove gray;\
                             border-style: outset;}"
                           "QPushButton:pressed{background-color:#EE6A50;\
                                            border-style: inset; }"
                            );


        QPushButton *menu6=new QPushButton("---",this);
        menu6->setFont(font);
        menu6->setGeometry(ORIGIN_X+(BUTTON_W+10),ORIGIN_Y+BUTTON_H+10,BUTTON_W,BUTTON_H);
        menu6->setStyleSheet("QPushButton{background-color:#9AC0CD;\
                       color: black;border-radius: 10px;  border: 4px groove gray;\
                             border-style: outset;}"
                           "QPushButton:pressed{background-color:#EE6A50;\
                                            border-style: inset; }"
                            );

        QPushButton *menu7=new QPushButton("---",this);
        menu7->setFont(font);
        menu7->setGeometry(ORIGIN_X+(BUTTON_W+10)*2,ORIGIN_Y+BUTTON_H+10,BUTTON_W,BUTTON_H);
        menu7->setStyleSheet("QPushButton{background-color:#9AC0CD;\
                       color: black;border-radius: 10px;  border: 4px groove gray;\
                             border-style: outset;}"
                           "QPushButton:pressed{background-color:#EE6A50;\
                                            border-style: inset; }"
                            );

        QPushButton *menu8=new QPushButton("退出",this);
        menu8->setFont(font);
        menu8->setGeometry(ORIGIN_X+(BUTTON_W+10)*3,ORIGIN_Y+BUTTON_H+10,BUTTON_W,BUTTON_H);
        menu8->setStyleSheet("QPushButton{background-color:#9AC0CD;\
                       color: black;border-radius: 10px;  border: 4px groove gray;\
                             border-style: outset;}"
                           "QPushButton:pressed{background-color:#EE6A50;\
                                            border-style: inset; }"
                            );

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
        connect(menu1,SIGNAL(clicked()),this,SLOT(Menu_Alarm_slot()));
        connect(menu2,SIGNAL(clicked()),this,SLOT(Menu_Output_slot()));
        connect(menu3,SIGNAL(clicked()),this,SLOT(Menu_Note_slot()));
        connect(menu4,SIGNAL(clicked()),this,SLOT(Menu_Correct_slot()));
        connect(menu8,SIGNAL(clicked()),this,SLOT(exit_slot()));
#if RASPBERRY_PI
    this->showFullScreen();
#endif
        }
void Menu::set_parent_view(QWidget * parent)
{
    this-> parent_view= parent;

}
void Menu::paintEvent(QPaintEvent *)
{
    background(this);
}
void Menu::set_clock(void)
{
    QDateTime new_time = QDateTime::currentDateTime();
    this->time_label->setText(new_time.toString("yyyy.MM.dd hh:mm:ss"));
}
void Menu::back(void)
{

this->parent_view->show();
this->close();
}
void Menu::exit_slot(void)
{
    QApplication *a;
    a->exit();
}
void Menu::Menu_Alarm_slot(void)
{
    Menu_Alarm  *alarm =new Menu_Alarm();
    alarm->set_parent_view(this);
    alarm->show();
    this->hide();
}
void  Menu::Menu_Output_slot(void)
{
    Menu_Output  *ouput =new Menu_Output();
    ouput->set_parent_view(this);
    ouput->show();
    this->hide();
}
void Menu::Menu_Note_slot(void)
{
    Menu_Note  *note =new Menu_Note();
    note->set_parent_view(this);
    note->show();
    this->hide();
}
void Menu::Menu_Correct_slot(void)
{
    Menu_Correct  *correct =new Menu_Correct();
    correct->set_parent_view(this);
    correct->show();
    this->hide();
}
