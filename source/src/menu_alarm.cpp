#include "menu_alarm.h"

Menu_Alarm::Menu_Alarm(QWidget *parent) : QWidget(parent)
{
    setAttribute(Qt::WA_DeleteOnClose);
    this->setFixedSize(800,480);
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
    /*返回*/
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
   connect(back,SIGNAL(clicked()),this,SLOT(back()));
   /*数据显示*/
   QFont pen;
   pen.setPixelSize(100);
   pen.setBold(100);//加粗，权重75
   dispaly_nubmer =new QLabel(this);
   dispaly_nubmer->setGeometry(340,130,400,150);
   dispaly_nubmer->setText("0000.00");
   dispaly_nubmer->setFont(pen);
   dispaly_nubmer->setAlignment(Qt::AlignRight);//文本居右
   set_dispaly_nubmer(0);
   QLabel *unit=new QLabel(this);
   QFont unit_font;
   unit_font.setPixelSize(40);
   unit->setFont(unit_font);
   unit->setGeometry(680,240,120,60);
   unit->setText("mg/L");
   /*设置内容*/
   connect(measure_main,SIGNAL(App_Measure_muddy(float)),this,SLOT(receive_App_Measure_muddy_slot(float)));
   QFont edit_font;
   edit_font.setPixelSize(30);
   QFont label_font;
   label_font.setPixelSize(30);
    /*高阈值*/
   high_alarm_edit =new QLineEdit(this);
    high_alarm_edit->setText(QString::number( measure_main->App_Measure_Get_Alarmhigh()));
   high_alarm_edit->setGeometry(180,100,140,50);
   high_alarm_edit->setFont(edit_font);
   high_alarm_edit->setReadOnly(true);
   high_alarm_edit->setAlignment(Qt::AlignCenter);//居中
   high_alarm_edit->setStyleSheet("background-color:#d3d7d4;color: black;\
                                   border-radius: 10px;  border: 4px groove gray;\
                                                                          border-style: outset;\
               " );
   QLabel *high_label=new QLabel(this);
   high_label->setGeometry(30,100,140,50);
   high_label->setText("高位阈值:");
   high_label->setFont(label_font);
   QPushButton *high_alarm_button= new QPushButton(this);
   high_alarm_button->setGeometry(330,105,40,40);
   high_alarm_button->setText("...");

   /*低阈值*/
   low_alarm_edit =new QLineEdit(this);
   low_alarm_edit->setText(QString::number( measure_main->App_Measure_Get_Alarmlow()));
   low_alarm_edit->setGeometry(180,180,140,50);
   low_alarm_edit->setFont(edit_font);
   low_alarm_edit->setReadOnly(true);
   low_alarm_edit->setAlignment(Qt::AlignCenter);//居中
   low_alarm_edit->setStyleSheet("background-color:#d3d7d4;color: black;\
                                   border-radius: 10px;  border: 4px groove gray;\
                                                                          border-style: outset;\
               " );
   QLabel *low_label= new QLabel(this);
   low_label->setGeometry(30,180,140,50);
   low_label->setText("低位阈值:");
   low_label->setFont(label_font);
   QPushButton *low_alarm_button= new QPushButton(this);
   low_alarm_button->setGeometry(330,185,40,40);
   low_alarm_button->setText("...");

   /*自动清洗阈值*/
   clear_alarm_edit =new QLineEdit(this);
   clear_alarm_edit->setText(QString::number(measure_main->App_Measure_Get_Cleannumber()));
   clear_alarm_edit->setGeometry(180,260,140,50);
   clear_alarm_edit->setFont(edit_font);
   clear_alarm_edit->setReadOnly(true);
   clear_alarm_edit->setAlignment(Qt::AlignCenter);//居中
   clear_alarm_edit->setStyleSheet("background-color:#d3d7d4;color: black;\
                                   border-radius: 10px;  border: 4px groove gray;\
                                                                          border-style: outset;\
               " );
   QLabel *clear_label= new QLabel(this);
   clear_label->setGeometry(30,260,140,50);
   clear_label->setText("清洗次数:");
   clear_label->setFont(label_font);
   QPushButton *clear_alarm_button= new QPushButton(this);
   clear_alarm_button->setGeometry(330,265,40,40);
   clear_alarm_button->setText("...");
   QList<QPushButton *>push_button;
   push_button.append(high_alarm_button);
   push_button.append(low_alarm_button);
   push_button.append(clear_alarm_button);
   for(int i=0;i<push_button.length();i++)
   {
   push_button[i]->setStyleSheet("QPushButton{background-color:#9AC0CD;\
                                 color: black;border-radius: 10px;  border: 4px groove gray;\
                                       border-style: outset;}"
                                     "QPushButton:pressed{background-color:#EE6A50;\
                                                      border-style: inset; }");
   }

    /*点击信号*/
   connect(high_alarm_button,SIGNAL(clicked()),this,SLOT(high_alarm_button_clicked_slot()));
   connect(low_alarm_button,SIGNAL(clicked()),this,SLOT(low_alarm_button_clicked_slot()));
    connect(clear_alarm_button,SIGNAL(clicked()),this,SLOT(clear_alarm_button_clicked_slot()));
#if RASPBERRY_PI
    this->showFullScreen();
#endif
}
void Menu_Alarm::set_parent_view(QWidget * parent)
{
    this-> parent_view= parent;

}
void Menu_Alarm::paintEvent(QPaintEvent *)
{
    background(this);
}
void Menu_Alarm::set_clock(void)
{
    QDateTime new_time = QDateTime::currentDateTime();
    this->time_label->setText(new_time.toString("yyyy.MM.dd hh:mm:ss"));
}
void Menu_Alarm::back(void)
{

this->parent_view->show();
this->close();
}
/*设置主界面显示的测量值*/
void Menu_Alarm::set_dispaly_nubmer(float number)
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
/*编辑框点击事件，呼出键盘*/
void Menu_Alarm::high_alarm_button_clicked_slot(void)
{
    keyboard *k =new keyboard();
    k->set_parent_view(this);
    k->show();
    connect(k,SIGNAL(keyboard_signal(float)),this,SLOT(high_alarmreceive_keyboard(float)));
    this->hide();
}
void Menu_Alarm::low_alarm_button_clicked_slot(void)
{
    keyboard *k =new keyboard();
    k->set_parent_view(this);
    k->show();
    connect(k,SIGNAL(keyboard_signal(float)),this,SLOT(low_alarmreceive_keyboard(float)));
    this->hide();
}
void Menu_Alarm::clear_alarm_button_clicked_slot(void)
{
    keyboard *k =new keyboard();
    k->set_parent_view(this);
    k->show();
    connect(k,SIGNAL(keyboard_signal(float)),this,SLOT(clear_alarmreceive_keyboard(float)));
    this->hide();
}
void Menu_Alarm::high_alarmreceive_keyboard(float keyboard)
{
       high_alarm_edit->setText(QString::number(keyboard));
       measure_main->App_Measure_Set_Alarmhigh(keyboard);
}
void Menu_Alarm::low_alarmreceive_keyboard(float keyboard)
{
    low_alarm_edit->setText(QString::number(keyboard));
     measure_main->App_Measure_Set_Alarmlow(keyboard);
}
void Menu_Alarm::clear_alarmreceive_keyboard(float keyboard)
{
     clear_alarm_edit->setText(QString::number((quint16)keyboard));
    measure_main->App_Measure_Set_Cleannumber((quint16)keyboard);
}
/*测量数据更新槽*/
void Menu_Alarm::receive_App_Measure_muddy_slot(float muddy)
{
    set_dispaly_nubmer(muddy);
}
