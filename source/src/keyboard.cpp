#include "keyboard.h"

keyboard::keyboard(QWidget *parent) : QWidget(parent)
{
    setAttribute(Qt::WA_DeleteOnClose);
    this->setFixedSize(800,480);
    QFont font;
    font.setPointSize(50);
    /*时间显示*/
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
    /******************第一排*/
QPushButton *number1=new QPushButton("1",this);
number1->setFont(font);
number1->setGeometry(ORIGIN_X,ORIGIN_Y,BUTTON_W,BUTTON_H);

QPushButton *number2=new QPushButton("2",this);
number2->setFont(font);
number2->setGeometry(ORIGIN_X+BUTTON_W+20,ORIGIN_Y,BUTTON_W,BUTTON_H);

QPushButton *number3=new QPushButton("3",this);
number3->setFont(font);
number3->setGeometry(ORIGIN_X+(BUTTON_W+20)*2,ORIGIN_Y,BUTTON_W,BUTTON_H);

QPushButton *number4=new QPushButton("4",this);
number4->setFont(font);
number4->setGeometry(ORIGIN_X+(BUTTON_W+20)*3,ORIGIN_Y,BUTTON_W,BUTTON_H);
/*********************第二排*/
QPushButton *number5=new QPushButton("5",this);
number5->setFont(font);
number5->setGeometry(ORIGIN_X,ORIGIN_Y+BUTTON_H+20,BUTTON_W,BUTTON_H);

QPushButton *number6=new QPushButton("6",this);
number6->setFont(font);
number6->setGeometry(ORIGIN_X+BUTTON_W+20,ORIGIN_Y+BUTTON_H+20,BUTTON_W,BUTTON_H);

QPushButton *number7=new QPushButton("7",this);
number7->setFont(font);
number7->setGeometry(ORIGIN_X+(BUTTON_W+20)*2,ORIGIN_Y+BUTTON_H+20,BUTTON_W,BUTTON_H);

QPushButton *number8=new QPushButton("8",this);
number8->setFont(font);
number8->setGeometry(ORIGIN_X+(BUTTON_W+20)*3,ORIGIN_Y+BUTTON_H+20,BUTTON_W,BUTTON_H);
/***********************第三排**/
QPushButton *number9=new QPushButton("9",this);
number9->setFont(font);
number9->setGeometry(ORIGIN_X,ORIGIN_Y+(BUTTON_H+20)*2,BUTTON_W,BUTTON_H);

QPushButton *number0=new QPushButton("0",this);
number0->setFont(font);
number0->setGeometry(ORIGIN_X+BUTTON_W+20,ORIGIN_Y+(BUTTON_H+20)*2,BUTTON_W,BUTTON_H);

QPushButton *number_negative=new QPushButton("-",this);
number_negative->setFont(font);
number_negative->setGeometry(ORIGIN_X+(BUTTON_W+20)*2,ORIGIN_Y+(BUTTON_H+20)*2,BUTTON_W,BUTTON_H);

QPushButton *number_delete=new QPushButton("<-",this);
number_delete->setFont(font);
number_delete->setGeometry(ORIGIN_X+(BUTTON_W+20)*3,ORIGIN_Y+(BUTTON_H+20)*2,BUTTON_W,BUTTON_H);
/*******************/
font.setPointSize(25);

QPushButton *number_point=new QPushButton(".",this);
number_point->setFont(font);
number_point->setGeometry(ORIGIN_X+(BUTTON_W+20)*4,ORIGIN_Y,BUTTON_W,BUTTON_H);

QPushButton *number_back=new QPushButton("返回",this);
number_back->setFont(font);
number_back->setGeometry(ORIGIN_X+(BUTTON_W+20)*4,ORIGIN_Y+BUTTON_H+20,BUTTON_W,BUTTON_H);

QPushButton *number_ok=new QPushButton("确认",this);
number_ok->setFont(font);
number_ok->setGeometry(ORIGIN_X+(BUTTON_W+20)*4,ORIGIN_Y+(BUTTON_H+20)*2,BUTTON_W,BUTTON_H);

QList<QPushButton *>pushbutton_list;
pushbutton_list.append(number1);
pushbutton_list.append(number2);
pushbutton_list.append(number3);
pushbutton_list.append(number4);
pushbutton_list.append(number5);
pushbutton_list.append(number6);
pushbutton_list.append(number7);
pushbutton_list.append(number8);
pushbutton_list.append(number9);
pushbutton_list.append(number0);
pushbutton_list.append(number_negative);
pushbutton_list.append(number_delete);
pushbutton_list.append(number_point);
pushbutton_list.append(number_back);
pushbutton_list.append(number_ok);
for(int i=0;i<pushbutton_list.length();i++)
pushbutton_list[i]->setStyleSheet("QPushButton{background-color:#9AC0CD;\
                                  color: black;border-radius: 10px;  border: 4px groove gray;\
                                        border-style: outset;}"
                                      "QPushButton:pressed{background-color:#EE6A50;\
                                                       border-style: inset; }");

number_edit =new QLineEdit(this);
font.setPointSize(40);
number_edit->setFont(font);
number_edit->setGeometry(ORIGIN_X,60,ORIGIN_X+(BUTTON_W+20)*4+60,60);
number_edit->setReadOnly(true);
number_edit->setStyleSheet("background-color:#d3d7d4;color: black;\
                                border-radius: 10px;  border: 4px groove gray;\
                                                                       border-style: outset;\
            " );
this->connect(number1,SIGNAL(clicked(void)),this,SLOT(number1_sclick(void)));
this->connect(number2,SIGNAL(clicked(void)),this,SLOT(number2_sclick(void)));
this->connect(number3,SIGNAL(clicked(void)),this,SLOT(number3_sclick(void)));
this->connect(number4,SIGNAL(clicked(void)),this,SLOT(number4_sclick(void)));
this->connect(number5,SIGNAL(clicked(void)),this,SLOT(number5_sclick(void)));
this->connect(number6,SIGNAL(clicked(void)),this,SLOT(number6_sclick(void)));
this->connect(number7,SIGNAL(clicked(void)),this,SLOT(number7_sclick(void)));
this->connect(number8,SIGNAL(clicked(void)),this,SLOT(number8_sclick(void)));
this->connect(number9,SIGNAL(clicked(void)),this,SLOT(number9_sclick(void)));
this->connect(number0,SIGNAL(clicked(void)),this,SLOT(number0_sclick(void)));
this->connect(number_point,SIGNAL(clicked(void)),this,SLOT(number_point_sclick(void)));
this->connect(number_negative,SIGNAL(clicked(void)),this,SLOT(number_negative_sclick(void)));
this->connect(number_delete,SIGNAL(clicked(void)),this,SLOT(number_delete_sclick(void)));
this->connect(number_back,SIGNAL(clicked(void)),this,SLOT(number_back_sclick(void)));
this->connect(number_ok,SIGNAL(clicked(void)),this,SLOT(number_ok_sclick(void)));
#if RASPBERRY_PI
    this->showFullScreen();
#endif

}
void keyboard::number1_sclick(void)
{
    qDebug("按下了1\n");
    if(number_edit->text().length()<IPUT_MAX)
    {
        number_edit->insert("1");
    }

}
void keyboard::number2_sclick(void)
{
    qDebug("按下了2\n");
    if(number_edit->text().length()<IPUT_MAX)
    {
    number_edit->insert("2");
    }
}
void keyboard::number3_sclick(void)
{
    qDebug("按下了3\n");
    if(number_edit->text().length()<IPUT_MAX)
    {
    number_edit->insert("3");
    }
}
void keyboard::number4_sclick(void)
{
    qDebug("按下了4\n");
    if(number_edit->text().length()<IPUT_MAX)
    {
    number_edit->insert("4");
    }
}
void keyboard::number5_sclick(void)
{
    qDebug("按下了5\n");
    if(number_edit->text().length()<IPUT_MAX)
    {
    number_edit->insert("5");
    }
}
void keyboard::number6_sclick(void)
{
    qDebug("按下了6\n");
    if(number_edit->text().length()<IPUT_MAX)
    {
    number_edit->insert("6");
    }
}
void keyboard::number7_sclick(void)
{
    qDebug("按下了7\n");
    {
    number_edit->insert("7");
    }
}
void keyboard::number8_sclick(void)
{
    qDebug("按下了8\n");
    if(number_edit->text().length()<IPUT_MAX)
    {
    number_edit->insert("8");
    }
}
void keyboard::number9_sclick(void)
{
    qDebug("按下了9\n");
    if(number_edit->text().length()<IPUT_MAX)
    {
    number_edit->insert("9");
    }
}
void keyboard::number0_sclick(void)
{
    qDebug("按下0\n");
    /*
    1.不能超过长度
    2.不能在‘-0’或‘0’之后
        */
    int length=number_edit->text().length();
    QString temp_str=number_edit->text();
    if(length<IPUT_MAX)
    {
        if((temp_str==QString::fromLocal8Bit("-0"))||(temp_str==QString::fromLocal8Bit("0")))
        {
        qDebug()<<"不允许输入 多余0";
        return ;
        }
        else
        {
            number_edit->insert("0");
        }
    }

}
 void keyboard::number_negative_sclick(void)
 {
     qDebug("按下了-\n");
     if(number_edit->text().length()==0)
     {
         number_edit->insert("-");
     }
 }
 void keyboard::number_point_sclick(void)
 {
     qDebug("按下了.\n");
     /*
    1.不能出现在第一个
    2.不能出现第二次
*/
     if(number_edit->text().length()!=0)
     {
         if(!number_edit->text().contains("."))
         {
         number_edit->insert(".");
         }
     }
 }
  void keyboard::number_delete_sclick(void)
{
    qDebug("按下了删除\n");
    if(number_edit->text().length()>0)
    {
    number_edit->setText(number_edit->text().left(number_edit->text().length()-1));
    }
}
   void keyboard::number_back_sclick(void)
   {
       qDebug("按下了返回\n");
       this->parent_view->show();
       this->close();
   }

void keyboard::number_ok_sclick(void)
{
    qDebug("按下了确认\n");
    bool ok;
    float temp=number_edit->text().toFloat(&ok);
    if(ok==true)
    {
        emit keyboard_signal(temp);
    }
    this->parent_view->show();
    this->close();
}

void keyboard::set_parent_view(QWidget * parent)
{
    this-> parent_view= parent;

}
void keyboard::paintEvent(QPaintEvent *)
{
    background(this);
}
void keyboard::set_clock(void)
{
    QDateTime new_time = QDateTime::currentDateTime();
    this->time_label->setText(new_time.toString("yyyy.MM.dd hh:mm:ss"));
}
