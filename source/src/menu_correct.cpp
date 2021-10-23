#include "menu_correct.h"

Menu_Correct::Menu_Correct(QWidget *parent) : QWidget(parent)
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
   dispaly_nubmer->setText(QString::number(0.00,'f',2));
   QLabel *unit=new QLabel(this);
   QFont unit_font;
   unit_font.setPixelSize(40);
   unit->setFont(unit_font);
   unit->setGeometry(680,240,120,60);
   unit->setText("mg/L");
   connect(measure_main,SIGNAL(App_Measure_muddy(float)),this,SLOT(receive_App_Measure_muddy_slot(float)));

   /*设置内容*/
   QFont edit_font;
   edit_font.setPixelSize(30);
   QFont label_font;
   label_font.setPixelSize(30);
    /*高阈值*/
   Slope_edit =new QLineEdit(this);
    Slope_edit->setText(QString::number( measure_main->App_Measure_Get_Slope()));
   Slope_edit->setGeometry(180,100,140,50);
   Slope_edit->setFont(edit_font);
   Slope_edit->setReadOnly(true);
   Slope_edit->setAlignment(Qt::AlignCenter);//居中
   Slope_edit->setStyleSheet("background-color:#d3d7d4;color: black;\
                                   border-radius: 10px;  border: 4px groove gray;\
                                                                          border-style: outset;\
               " );
   QLabel *Slope_label=new QLabel(this);
   Slope_label->setGeometry(30,100,140,50);
   Slope_label->setText("线性调整:");
   Slope_label->setFont(label_font);
   QPushButton *Slope_button= new QPushButton(this);
   Slope_button->setGeometry(330,105,40,40);
   Slope_button->setText("...");

   /*低阈值*/
   Vol_edit =new QLineEdit(this);
   Vol_edit->setText(QString::number( measure_main->App_Measure_Get_Vol()));
   Vol_edit->setGeometry(180,180,140,50);
   Vol_edit->setFont(edit_font);
   Vol_edit->setReadOnly(true);
   Vol_edit->setAlignment(Qt::AlignCenter);//居中
   Vol_edit->setStyleSheet("background-color:#d3d7d4;color: black;\
                                   border-radius: 10px;  border: 4px groove gray;\
                                                                          border-style: outset;\
               " );
   QLabel *Vol_label= new QLabel(this);
    Vol_label->setGeometry(30,180,140,50);
   Vol_label->setText("偏置调整:");
   Vol_label->setFont(label_font);
   QPushButton *Vol_button= new QPushButton(this);
   Vol_button->setGeometry(330,185,40,40);
   Vol_button->setText("...");
Slope_button->setStyleSheet("QPushButton{background-color:#9AC0CD;\
                            color: black;border-radius: 10px;  border: 4px groove gray;\
                                  border-style: outset;}"
                                "QPushButton:pressed{background-color:#EE6A50;\
                                                 border-style: inset; }");

Vol_button->setStyleSheet("QPushButton{background-color:#9AC0CD;\
                            color: black;border-radius: 10px;  border: 4px groove gray;\
                             border-style: outset;}"
                             "QPushButton:pressed{background-color:#EE6A50;\
                             border-style: inset; }");

   connect(Slope_button,SIGNAL(clicked()),this,SLOT(Slope_button_clicked_slot()));
   connect(Vol_button,SIGNAL(clicked()),this,SLOT(Vol_button_clicked_slot()));
#if RASPBERRY_PI
    this->showFullScreen();
#endif
   }
   void Menu_Correct::set_parent_view(QWidget * parent)
   {
       this-> parent_view= parent;

   }
   void Menu_Correct::paintEvent(QPaintEvent *)
   {
       background(this);
   }
   void Menu_Correct::set_clock(void)
   {
       QDateTime new_time = QDateTime::currentDateTime();
       this->time_label->setText(new_time.toString("yyyy.MM.dd hh:mm:ss"));
   }
   void Menu_Correct::back(void)
   {

   this->parent_view->show();
   this->close();
   }
   /*设置主界面显示的测量值*/
   void Menu_Correct::set_dispaly_nubmer(float number)
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
   /*测量数据更新槽*/
   void Menu_Correct::receive_App_Measure_muddy_slot(float muddy)
   {
       set_dispaly_nubmer(muddy);
   }
    void Menu_Correct::Slope_button_clicked_slot()
    {
        keyboard *k =new keyboard();
        k->set_parent_view(this);
        k->show();
        connect(k,SIGNAL(keyboard_signal(float)),this,SLOT(Slope_receive_keyboard(float)));
        this->hide();
    }
    void Menu_Correct::Vol_button_clicked_slot()
    {
        keyboard *k =new keyboard();
        k->set_parent_view(this);
        k->show();
        connect(k,SIGNAL(keyboard_signal(float)),this,SLOT(Vol_receive_keyboard(float)));
        this->hide();
    }
    void Menu_Correct::Slope_receive_keyboard(float keyboard)
    {
           Slope_edit->setText(QString::number(keyboard));
           measure_main->App_Measure_Set_Slope(keyboard);
    }
    void Menu_Correct::Vol_receive_keyboard(float keyboard)
    {
        Vol_edit->setText(QString::number(keyboard));
         measure_main->App_Measure_Set_Vol(keyboard);
    }
