#include "menu_note.h"

Menu_Note::Menu_Note(QWidget *parent) : QWidget(parent)
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

   QFont edit_font;
   edit_font.setPixelSize(30);
   QFont label_font;
   label_font.setPixelSize(30);
   /*采样间隔设置*/
    simpling_cycle_number=measure_main->App_Measure_Get_Save_Cycle();
    /*时间设置*/
   new_datetime =new QDateTime();
   _new_date = new QDate(QDate::currentDate());
   _new_time = new QTime(QTime::currentTime());
   /*年*/
   QLabel *year_label =new QLabel(this);
   year_label->setText("年");
   year_label->setGeometry(20,100,90,45);
   year_label->setFont(label_font);
   year_edit =new QLineEdit(this);
   year_edit->setGeometry(50,100,90,45);
   year_edit->setFont(edit_font);
   year_edit->setReadOnly(true);
   year_edit->setAlignment(Qt::AlignCenter);
   year_edit->setText(QString::number( _new_date->year()));
   year_edit->setStyleSheet("background-color:#d3d7d4;color: black;\
                                   border-radius: 10px;  border: 4px groove gray;\
                                                                          border-style: outset;\
               " );
    year_button= new QPushButton(this);
    year_button->setGeometry(160,100,45,45);
    year_button->setText("...");

   /*月*/
    QLabel *month_label =new QLabel(this);
    month_label->setText("月");
    month_label->setGeometry(20,195,90,45);
    month_label->setFont(label_font);
    month_edit =new QLineEdit(this);
    month_edit->setGeometry(50,195,90,45);
    month_edit->setFont(edit_font);
    month_edit->setReadOnly(true);
    month_edit->setAlignment(Qt::AlignCenter);
    month_edit->setText(QString::number( _new_date->month()));
    month_edit->setStyleSheet("background-color:#d3d7d4;color: black;\
                                    border-radius: 10px;  border: 4px groove gray;\
                                                                           border-style: outset;\
                " );
    month_button= new QPushButton(this);
    month_button->setGeometry(160,195,45,45);
    month_button->setText("...");
   /*日*/
    QLabel *day_label =new QLabel(this);
    day_label->setText("日");
    day_label->setGeometry(20,290,90,45);
    day_label->setFont(label_font);
    day_edit =new QLineEdit(this);
    day_edit->setGeometry(50,290,90,45);
    day_edit->setFont(edit_font);
    day_edit->setReadOnly(true);
    day_edit->setAlignment(Qt::AlignCenter);
    day_edit->setText(QString::number( _new_date->day()));
    day_edit->setStyleSheet("background-color:#d3d7d4;color: black;\
                                    border-radius: 10px;  border: 4px groove gray;\
                                                                           border-style: outset;\
                " );
    day_button= new QPushButton(this);
    day_button->setGeometry(160,290,45,45);
    day_button->setText("...");
   /*时*/
    QLabel *hour_label =new QLabel(this);
    hour_label->setText("时");
    hour_label->setGeometry(250,100,90,45);
    hour_label->setFont(label_font);
    hour_edit =new QLineEdit(this);
    hour_edit->setGeometry(280,100,90,45);
    hour_edit->setFont(edit_font);
    hour_edit->setReadOnly(true);
    hour_edit->setAlignment(Qt::AlignCenter);
    hour_edit->setText(QString::number( _new_time->hour()));
    hour_edit->setStyleSheet("background-color:#d3d7d4;color: black;\
                                    border-radius: 10px;  border: 4px groove gray;\
                                                                           border-style: outset;\
                " );
    hour_button= new QPushButton(this);
    hour_button->setGeometry(390,100,45,45);
    hour_button->setText("...");
   /*分*/
    QLabel *min_label =new QLabel(this);
    min_label->setText("分");
    min_label->setGeometry(250,195,90,45);
    min_label->setFont(label_font);
    min_edit =new QLineEdit(this);
    min_edit->setGeometry(280,195,90,45);
    min_edit->setFont(edit_font);
    min_edit->setReadOnly(true);
    min_edit->setAlignment(Qt::AlignCenter);
    min_edit->setText(QString::number( _new_time->minute()));
    min_edit->setStyleSheet("background-color:#d3d7d4;color: black;\
                                    border-radius: 10px;  border: 4px groove gray;\
                                                                           border-style: outset;\
                " );
    min_button= new QPushButton(this);
    min_button->setGeometry(390,195,45,45);
    min_button->setText("...");
   /*秒*/
    QLabel *second_label =new QLabel(this);
    second_label->setText("秒");
    second_label->setGeometry(250,290,90,45);
    second_label->setFont(label_font);
    second_edit =new QLineEdit(this);
    second_edit->setGeometry(280,290,90,45);
    second_edit->setFont(edit_font);
    second_edit->setReadOnly(true);
    second_edit->setAlignment(Qt::AlignCenter);
     second_edit->setText(QString::number( _new_time->second()));
     second_edit->setStyleSheet("background-color:#d3d7d4;color: black;\
                                     border-radius: 10px;  border: 4px groove gray;\
                                                                            border-style: outset;\
                 " );
    second_button= new QPushButton(this);
    second_button->setGeometry(390,290,45,45);
    second_button->setText("...");

    QLabel *simpling_cycle_label =new QLabel(this);
    simpling_cycle_label->setFont(label_font);
    simpling_cycle_label->setGeometry(450,60,200,30);
    simpling_cycle_label->setText("设置记录间隔");
    simpling_cycle_edit =new QLineEdit(this);
    simpling_cycle_edit->setGeometry(450,100,180,45);
    simpling_cycle_edit->setFont(edit_font);
    simpling_cycle_edit->setReadOnly(true);
    simpling_cycle_edit->setAlignment(Qt::AlignCenter);
    simpling_cycle_edit->setText(QString::number(measure_main->App_Measure_Get_Save_Cycle()));
    simpling_cycle_edit->setStyleSheet("background-color:#d3d7d4;color: black;\
                                    border-radius: 10px;  border: 4px groove gray;\
                                                                           border-style: outset;\
                " );
     edit_font.setPixelSize(20);
    simpling_cycle =new QComboBox(this);
    simpling_cycle->setGeometry(650,100,65,45);
    simpling_cycle->setFont(edit_font);
    simpling_cycle->addItem("秒");
    simpling_cycle->addItem("分钟");
    simpling_cycle->addItem("小时");
    QPushButton *simpling_cycle_button= new QPushButton(this);
    simpling_cycle_button->setGeometry(730,100,60,45);
    simpling_cycle_button->setText("...");

    /*确定*/
    QFont fixfont;
    fixfont.setPixelSize(40);
    fix_button =new QPushButton(this);
    fix_button->setFont(fixfont);
    fix_button->setGeometry(600,355,100,60);
    fix_button->setText("确定");
    QList<QPushButton*>button_list;
    button_list.append(year_button);
    button_list.append(month_button);
    button_list.append(day_button);
    button_list.append(hour_button);
    button_list.append(min_button);
    button_list.append(second_button);
     button_list.append(simpling_cycle_button);
      button_list.append(fix_button);
      for(int i=0;i<button_list.length();i++)
      {
          button_list[i]->setStyleSheet("QPushButton{background-color:#9AC0CD;\
                                        color: black;border-radius: 10px;  border: 4px groove gray;\
                                              border-style: outset;}"
                                            "QPushButton:pressed{background-color:#EE6A50;\
                                                             border-style: inset; }");
      }
QFont serial_font;
serial_font.setPixelSize(15);
QLabel *com_label =new QLabel(this);
com_label->setGeometry(450,155,200,45);
com_label->setText("串口选择");
com_label->setFont(label_font);
serial_com =new QComboBox(this);
serial_com->setGeometry(450,195,180,45);
serial_com->setFont(serial_font);
QSerialPortInfo my_serialportinfo;
QList<QSerialPortInfo> portlist = my_serialportinfo.availablePorts();
for(int i=0;i<portlist.length();i++)
{
   qDebug()<<portlist[i].portName()<<endl;
   serial_com->addItem(portlist[i].portName());
}
    serial_com->setCurrentText(measure_main->App_Measure_Get_com_name());

    connect(year_button,SIGNAL(clicked()),this,SLOT(year_button_slot()));
    connect(month_button,SIGNAL(clicked()),this,SLOT(month_button_slot()));
    connect(day_button,SIGNAL(clicked()),this,SLOT(day_button_slot()));
    connect(hour_button,SIGNAL(clicked()),this,SLOT(hour_button_slot()));
    connect(min_button,SIGNAL(clicked()),this,SLOT(min_button_slot()));
    connect(second_button,SIGNAL(clicked()),this,SLOT(second_button_slot()));
    connect(simpling_cycle_button,SIGNAL(clicked()),this,SLOT(simpling_cycle_button()));
    connect(fix_button,SIGNAL(clicked()),this,SLOT(fix_button_slot()));
#if RASPBERRY_PI
    this->showFullScreen();
#endif
}
   void Menu_Note::set_parent_view(QWidget * parent)
   {
       this-> parent_view= parent;

   }
   void Menu_Note::paintEvent(QPaintEvent *)
   {
       background(this);
   }
   void Menu_Note::set_clock(void)
   {
       QDateTime new_time = QDateTime::currentDateTime();
       this->time_label->setText(new_time.toString("yyyy.MM.dd hh:mm:ss"));
   }
   void Menu_Note::back(void)
   {

   this->parent_view->show();
   this->close();
   }
    void Menu_Note::year_button_slot(void)
    {
        keyboard *k =new keyboard();
        k->set_parent_view(this);
        k->show();
        connect(k,&keyboard::keyboard_signal,this,[this](float data){
            int temp =(int)data;
            if(temp>1960&&temp<2100)
            {
               this->year_edit->setText(QString::number(temp));
               _new_datetime.day=temp;
            }
            });
        this->hide();
    }
    void Menu_Note::month_button_slot(void)
    {
        keyboard *k =new keyboard();
        k->set_parent_view(this);
        k->show();
        connect(k,&keyboard::keyboard_signal,this,[this](float data){
            int temp =(int)data;
            if((temp>0)&&(temp<13))
            {
               this->month_edit->setText(QString::number(temp));
               _new_datetime.month=temp;
            }
            });
        this->hide();
    }
    void Menu_Note::day_button_slot(void)
    {
        keyboard *k =new keyboard();
        k->set_parent_view(this);
        k->show();
        connect(k,&keyboard::keyboard_signal,this,[this](float data){
            int temp =(int)data;
            if((temp>0)&&(temp<32))
            {
               this->day_edit->setText(QString::number(temp));
               _new_datetime.day=temp;
            }
            });
        this->hide();
    }
    void Menu_Note::hour_button_slot(void)
    {
        keyboard *k =new keyboard();
        k->set_parent_view(this);
        k->show();
        connect(k,&keyboard::keyboard_signal,this,[this](float data){
            int temp =(int)data;
            if((temp>=0)&&(temp<24))
            {
               this->hour_edit->setText(QString::number(temp));
               _new_datetime.hour=temp;
            }
            });
        this->hide();
    }
    void Menu_Note::min_button_slot(void)
    {
        keyboard *k =new keyboard();
        k->set_parent_view(this);
        k->show();
        connect(k,&keyboard::keyboard_signal,this,[this](float data){
            int temp =(int)data;
            if((temp>=0)&&(temp<60))
            {
               this->min_edit->setText(QString::number(temp));
               _new_datetime.min=temp;
            }
            });
        this->hide();
    }
    void Menu_Note::second_button_slot(void)
    {
        keyboard *k =new keyboard();
        k->set_parent_view(this);
        k->show();
        connect(k,&keyboard::keyboard_signal,this,[this](float data){
            int temp =(int)data;
            if((temp>=0)&&(temp<60))
            {
               this->second_edit->setText(QString::number(temp));
               _new_datetime.second=temp;
            }
            });
        this->hide();
    }
    void Menu_Note::simpling_cycle_button(void)
    {
        keyboard *k =new keyboard();
        k->set_parent_view(this);
        k->show();
        connect(k,&keyboard::keyboard_signal,this,[this](float data){
            int temp =(int)data;
            if((temp>=0)&&(temp<60))
            {
               this->simpling_cycle_edit->setText(QString::number(temp));
               simpling_cycle_number=temp;
            }
            });
        this->hide();
    }
 void Menu_Note::fix_button_slot(void)
 {
     qDebug("设置时间");
#if RASPBERRY_PI
     char time_buff[40];
     _new_datetime.year=year_edit->text().toInt();
     _new_datetime.month=month_edit->text().toInt();
     _new_datetime.day=day_edit->text().toInt();
     _new_datetime.hour=hour_edit->text().toInt();
     _new_datetime.min=min_edit->text().toInt();
     _new_datetime.second=second_edit->text().toInt();
     sprintf(time_buff,"sudo date --s \"%d-%d-%d %d:%d:%d\n\"",
             _new_datetime.year,
             _new_datetime.month,
             _new_datetime.day,
             _new_datetime.hour,
             _new_datetime.min,
             _new_datetime.second);
     system(time_buff);
     qDebug()<<time_buff;
#endif
     qDebug()<<_new_datetime.year;
     quint32 temp_cycleindex;
     switch (simpling_cycle->currentIndex())
     {
     case 0:
     {
         temp_cycleindex=simpling_cycle_number;
         break;
     }
     case 1:
     {
         temp_cycleindex=simpling_cycle_number*60;
           break;
     }
     case 2:
     {
         temp_cycleindex=simpling_cycle_number*60*60;
           break;
     }
     default :
     {
         this->parent_view->show();
         this->close();
         return;
     }
     }
     measure_main->App_Measure_Set_Save_Cycle(temp_cycleindex);
     if(measure_main->App_Measure_Get_com_name()!=serial_com->currentText())
     {
     measure_main->App_Measure_Set_com_name(serial_com->currentText());\

     measure_main->App_Measure_Connect();

     }
     this->parent_view->show();
     this->close();
 }
