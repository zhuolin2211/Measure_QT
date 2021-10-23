#include "menu_output.h"
#include "QFont"
#include "main.h"
Menu_Output::Menu_Output(QWidget *parent) : QWidget(parent)
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

   /*串口配置*/
   QFont serial_font;
   serial_font.setPixelSize(30);
   QLabel *com_label =new QLabel(this);
   com_label->setGeometry(20,80,200,45);
   com_label->setText("串口选择");
   com_label->setFont(serial_font);
   serial_com =new QComboBox(this);
   serial_com->setGeometry(200,80,200,45);
   serial_com->setFont(font);
   QSerialPortInfo my_serialportinfo;
   QList<QSerialPortInfo> portlist = my_serialportinfo.availablePorts();
   for(int i=0;i<portlist.length();i++)
   {
      qDebug()<<portlist[i].portName()<<endl;
      serial_com->addItem(portlist[i].portName());
   }
   serial_com->setCurrentText(output->App_Output_Get_com());
    /*波特率*/
   QLabel *baud_label =new QLabel(this);
   baud_label->setGeometry(20,145,200,45);
   baud_label->setText("波特率");
   baud_label->setFont(serial_font);
   serial_baud =new QComboBox(this);
   serial_baud->setGeometry(200,145,200,45);
   serial_baud->setFont(font);
   serial_baud->addItem(QString::number(115200));
   serial_baud->addItem(QString::number(19200));
   serial_baud->addItem(QString::number(9600));
   serial_baud->addItem(QString::number(4800));
   switch (output->App_Output_Get_baud())
   {
   case 115200: {serial_baud->setCurrentIndex(0);break;}
   case 19200: {serial_baud->setCurrentIndex(1);break;}
   case 9600: {serial_baud->setCurrentIndex(2);break;}
   case 4800: {serial_baud->setCurrentIndex(3);break;}
   default:break;
   }
    /*奇偶*/
   QLabel *parityd_label= new QLabel(this);
   parityd_label->setGeometry(20,210,200,45);
   parityd_label->setText("奇偶校验");
   parityd_label->setFont(serial_font);
   serial_parity =new QComboBox(this);
   serial_parity->setGeometry(200,210,200,45);
   serial_parity->setFont(font);
   serial_parity->addItem("不校验");
   serial_parity->addItem("偶校验");
   serial_parity->addItem("奇校验");
   switch (output->App_Output_Get_parity())
   {
   case QSerialPort::NoParity: {serial_parity->setCurrentIndex(0);break;}
   case QSerialPort::EvenParity : {serial_parity->setCurrentIndex(1);break;}
   case QSerialPort::OddParity: {serial_parity->setCurrentIndex(2);break;}
   default:break;
   }

   /*数据位*/
   QLabel *databits_label=new QLabel(this);
   databits_label->setGeometry(20,275,200,45);
   databits_label->setText("数据位");
   databits_label->setFont(serial_font);
   serial_databits =new QComboBox(this);
   serial_databits->setGeometry(200,275,200,45);
   serial_databits->setFont(font);
   serial_databits->addItem("8数据位");
   serial_databits->addItem("7数据位");
   switch (output->App_Output_Get_databit())
   {
   case QSerialPort::Data8: {serial_databits->setCurrentIndex(0);break;}
   case QSerialPort::Data7 : {serial_databits->setCurrentIndex(1);break;}
   default:break;
   }
   /*停止位*/
   QLabel *stopbits_label=new QLabel(this);
   stopbits_label->setGeometry(20,340,200,45);
   stopbits_label->setText("停止位");
   stopbits_label->setFont(serial_font);
   serial_stopbits =new QComboBox(this);
   serial_stopbits->setGeometry(200,340,200,45);
   serial_stopbits->setFont(font);
   serial_stopbits->addItem("1停止位");
   serial_stopbits->addItem("2位停止位");
   switch (output->App_Output_Get_stopbit())
   {
   case QSerialPort::OneStop: {serial_stopbits->setCurrentIndex(0);break;}
   case QSerialPort::TwoStop : {serial_stopbits->setCurrentIndex(1);break;}
   default:break;
   }

   /*确定*/
   QFont fixfont;
   fixfont.setPixelSize(40);
   fix_button =new QPushButton(this);
   fix_button->setFont(fixfont);
   fix_button->setGeometry(600,355,100,60);
   fix_button->setText("确定");
   fix_button->setStyleSheet("QPushButton{background-color:#9AC0CD;\
                                       color: black;border-radius: 10px;  border: 4px groove gray;\
                                             border-style: outset;}"
                                           "QPushButton:pressed{background-color:#EE6A50;\
                                                            border-style: inset; }");
    QFont label_font;
    label_font.setPixelSize(20);
    QLabel *server_addr_label =new QLabel(this);
     server_addr_label->setFont(fixfont);
     server_addr_label->setGeometry(450,60,200,30);
     server_addr_label->setText("设置设备Modbus地址");
     server_addr_label->setFont(label_font);
    server_addr_edit =new QLineEdit(this);
    server_addr_edit->setGeometry(450,100,180,45);
    server_addr_edit->setFont(fixfont);
     server_addr_edit->setReadOnly(true);
      server_addr_edit->setAlignment(Qt::AlignCenter);
      server_addr_edit->setText(QString::number(output->App_Output_Get_serveraddr()));
     server_addr_edit->setStyleSheet("background-color:#d3d7d4;color: black;\
      border-radius: 10px;  border: 4px groove gray;\
      border-style: outset;\
       " );
      QPushButton *server_addr_button= new QPushButton(this);
      server_addr_button->setGeometry(700,100,60,45);
      server_addr_button->setText("...");
      server_addr_button->setStyleSheet("QPushButton{background-color:#9AC0CD;\
                                          color: black;border-radius: 10px;  border: 4px groove gray;\
                                                border-style: outset;}"
                                              "QPushButton:pressed{background-color:#EE6A50;\
                                                               border-style: inset; }");
    connect(fix_button,SIGNAL(clicked()),this,SLOT(fix()));
    connect(this,SIGNAL(Menu_Output_option()),output,SLOT(App_Output_option_slot()));
    connect(server_addr_button,SIGNAL(clicked()),this,SLOT(Menu_Output_server_addr_button_slot()));
#if RASPBERRY_PI
    this->showFullScreen();
#endif
   }
   void Menu_Output::set_parent_view(QWidget * parent)
   {
       this-> parent_view= parent;

   }
   void Menu_Output::paintEvent(QPaintEvent *)
   {
       background(this);
   }
   void Menu_Output::set_clock(void)
   {
       QDateTime new_time = QDateTime::currentDateTime();
       this->time_label->setText(new_time.toString("yyyy.MM.dd hh:mm:ss"));
   }
   void Menu_Output::back(void)
   {

   this->parent_view->show();
   this->close();
   }
   void Menu_Output::fix(void)
   {
       output->App_Output_Set_com(serial_com->currentText());
       output->App_Output_Set_baud(serial_baud->currentText().toUShort());
       switch (serial_parity->currentIndex())
       {
           case 0:
           {
               output->App_Output_Set_parity(QSerialPort::NoParity);
               break;
           }
       case 1:
       {
           output->App_Output_Set_parity(QSerialPort::EvenParity);
           break;
       }
       case 2:
       {
           output->App_Output_Set_parity(QSerialPort::OddParity);
           break;
       }
       default:
           break;
       }
       switch (serial_databits->currentIndex())
       {
       case 0:
       {
           output->App_Output_Set_databit(QSerialPort::Data8);
                   break;
       }
       case 1:
       {
           output->App_Output_Set_databit(QSerialPort::Data7);
                   break;
       }
       default:break;
       }
       switch(serial_stopbits->currentIndex())
       {
       case 0:
       {
           output->App_Output_Set_stopbit(QSerialPort::OneStop);
           break;
       }
       case 1:
       {
           output->App_Output_Set_stopbit(QSerialPort::TwoStop);
           break;
       }
       default:break;
       }
        output->App_Output_Set_serveraddr(server_addr_edit->text().toUShort());
        emit Menu_Output_option();
       this->parent_view->show();
       this->close();
   }
void Menu_Output::Menu_Output_server_addr_button_slot(void)
{
    keyboard *k =new keyboard();
    k->set_parent_view(this);
    k->show();
    connect(k,&keyboard::keyboard_signal,this,[this](float data){
        quint16 temp =(quint16)data;
        if(temp<100)
        {
           this->server_addr_edit->setText(QString::number(temp));
        }
        });
    this->hide();
}
