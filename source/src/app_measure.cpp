#include "app_measure.h"
#include "QTimer"

App_Measure::App_Measure()
{
this->Measure_Raw=0;
    this->Measure_Adept=0;
    this->Measure_Vol=0;
    this->Measure_Adept=1;
    Device1 = new QModbusRtuSerialMaster(this);

    /*串口配置*/
    QSerialPortInfo my_serialportinfo;
       QList<QSerialPortInfo> portlist = my_serialportinfo.availablePorts();
       qDebug()<<"串口数："<<portlist.length();
       for(int i=0;i<portlist.length();i++)
       {
          qDebug()<<portlist[i].portName();
       }
       /*
       Measere_port=new QSerialPort();
       Measere_port->setPort(portlist[0]);
       Measere_port->setBaudRate(19200);
       Measere_port->setDataBits(QSerialPort::Data8);//8位数据为
       Measere_port->setStopBits(QSerialPort::OneStop);//1位停止位
       Measere_port->setParity(QSerialPort::NoParity);//不开启就奇偶校验
       Measere_port->setFlowControl(QSerialPort::NoFlowControl);
       if(Measere_port->open(QIODevice::ReadWrite)==false)
       {
           qDebug()<<"串口打开失败"<<portlist[0].portName();
           return;
       }
       */
       /*Qmodbus*/
        App_Measure_Connect();

}
void App_Measure::App_Measure_Connect(void)
{
    if(!Device1)
    {
        qDebug("error");
    }

    Device1->disconnectDevice();
    Device1->setConnectionParameter(QModbusDevice::SerialPortNameParameter,App_Measure_Get_com_name());
    Device1->setConnectionParameter(QModbusDevice::SerialParityParameter,QSerialPort::NoParity);
    Device1->setConnectionParameter(QModbusDevice::SerialBaudRateParameter,19200);
    Device1->setConnectionParameter(QModbusDevice::SerialDataBitsParameter,QSerialPort::Data8);
    Device1->setConnectionParameter(QModbusDevice::SerialStopBitsParameter,QSerialPort::OneStop);
    Device1->setTimeout(1000);
    Device1->setNumberOfRetries(3);
    qDebug()<< Device1->errorString();
    if(Device1->connectDevice()==false)
    {
        Device1->disconnectDevice();
        qDebug()<<"连接Modbus设备失败";
       return;
    }
    connect(Device1, SIGNAL( stateChanged(QModbusDevice::State )),this, SLOT(Device1_Connect_State_Change(QModbusDevice::State )));
     simpling_timer =new QTimer(this);
     simpling_timer->start(1000);
     connect(simpling_timer,SIGNAL(timeout()),this,SLOT(Simpling_timer_slot()));
     App_Measure_DeviceSet();

}
void App_Measure::App_Measure_Get(void)
{
    /*读数据*处理*/
    Device1_reply =Device1->sendReadRequest(QModbusDataUnit(QModbusDataUnit::HoldingRegisters,DEVICE1_DATA_ADDR_START,DEVICE1_DATA_ADDR_MAX),DEVICE1_ADDR);
    if(!Device1_reply)
    {
        qDebug()<<Device1->errorString();
        qDebug()<<"error";
    }
    else
    {
        if (!Device1_reply->isFinished())//回复或终止时返回
        {
           connect(Device1_reply, &QModbusReply::finished, this, &App_Measure::onReadReady_slot);
        }
        else
        {
            delete (Device1_reply);
        }
    }
    App_Measure_SaveData();
    int temp =alarm_type;
    APP_Measure_Alarm();
    if(temp!=alarm_type)
    {
        qDebug()<<"alarm_type = "<<alarm_type;
        emit APP_Measure_Alarm_signal(alarm_type);
    }
}
void App_Measure::App_Measure_DeviceSet(void)
{
    /*设置读取参数为浊度*/
    QModbusDataUnit writeUnit=QModbusDataUnit(QModbusDataUnit::HoldingRegisters,0xb,1);
    writeUnit.setValue(0,0);
    Device1_reply = Device1->sendWriteRequest(writeUnit,DEVICE1_ADDR);
    if(Device1_reply)
    {
    if(!Device1_reply->isFinished())
    {
        connect(Device1_reply, &QModbusReply::finished, this, [this]() {qDebug("error");qDebug()<< Device1_reply->errorString();});
    }
    else
        Device1_reply->deleteLater();
    }else
    {
        qDebug()<<"Write error"<<Device1->errorString();
    }
}
void App_Measure::Device1_Connect_State_Change(QModbusDevice::State state)
{
    qDebug()<<"Device1_Connect_State_Change";
    if(state!=QModbusClient::ConnectedState)
    {
        Device1->connectDevice();
    }
}
void App_Measure::onReadReady_slot(void)
{
    quint32 float_byte;
    float *real_float;
    auto Device1_reply  = qobject_cast<QModbusReply *>(sender());
if(Device1_reply->error()==QModbusDevice::NoError)
{
    QModbusDataUnit Device1_result = Device1_reply->result();

       float_byte= (quint32)((Device1_result.value(1)&0xffff)<<16)|(quint32)(Device1_result.value(0)&0xffff);
       real_float=(float*)&float_byte;    
        App_Measure_count(*real_float);
        emit App_Measure_muddy(this->Measure_Adept);
        //qDebug("浊度：%.2f",this->Measure_Adept);
       float_byte=0;
       float_byte= (quint32)((Device1_result.value(5)&0xffff)<<16)|(quint32)(Device1_result.value(4)&0xffff);
        real_float=(float*)&float_byte;
        emit App_Measure_suspension(*real_float);

        //qDebug("悬浮物值：%f",*real_float);

        /*
       for(uint i=0;i<Device1_result.valueCount();i++)
       {
        qDebug()<<(Device1_result.startAddress() + i)<<QString::number(Device1_result.value(i),
                     Device1_result.registerType() <= QModbusDataUnit::Coils ? 10 : 16);
         }
         */

}
else
{
    qDebug()<<Device1_reply->errorString();
}
Device1_reply->deleteLater();
}
void App_Measure::Simpling_timer_slot(void)
{
    this->App_Measure_Get();
}

float App_Measure::App_Measure_Current(void)//立即返回一次测量值
{
  return this->Measure_Adept;
}
 float App_Measure::App_Measure_count(float raw)//计算校准值
 {
     this->Measure_Raw=raw;
     this->Measure_Adept=(this->Measure_Raw*this->Measure_Slope)+this->Measure_Vol;
     return this->Measure_Adept;
 }
#define INSERT "insert into test2(tempindex , value) values(%lld,%f)"
void App_Measure::App_Measure_SaveData(void)
{
    if((Save_count%Save_Cycle)==0)
    {
    this->Database_mutex->lock();
    sqlite3* database;
    char command[256];
   int ret = 0;
    char *error_msg=(char*)malloc(256);
    ret =sqlite3_open(database_file, &database);
       if (ret != SQLITE_OK)
       {
           qDebug("数据库打开失败\n");
           this->Database_mutex->unlock();
           return ;
       }
       sprintf(command,INSERT,QDateTime::currentMSecsSinceEpoch()/1000,this->Measure_Adept);
       qDebug()<<command;
       ret= sqlite3_exec(database,command,0,0,&error_msg);
       if(ret!=SQLITE_OK)
       {
           qDebug("数据写入失败 %s",error_msg);
       }
       sqlite3_close(database);
       this->Database_mutex->unlock();
    }
    Save_count++;
}
/*
 *报警信号简单滤波和控制信号发送
 *  return 0:没有报警
 * 1：下阈值报警
 * 2：上阈值报警
*/
int App_Measure::APP_Measure_Alarm(void)
{
    if(Measure_Adept>Alarm_high_value)
    {
        if(high_count>=4)
        {
            alarm_type=2;
        }
        else
        {
            high_count++;
        }
        if(low_count)
        {
            low_count--;
        }
    }
    else if(Measure_Adept<Alarm_low_value)
    {
        if(low_count>=4)
        {
            alarm_type=1;
        }
        else
        {
            low_count++;
        }
        if(high_count)
        {
            high_count--;
        }
    }
    else
    {
        if(high_count)
        {
            high_count--;
        }
        if(low_count)
        {
            low_count--;
        }
        if((low_count==0)&&(high_count==0))
        {
            alarm_type=0;
        }
    }
    return alarm_type;
}
  void App_Measure::App_Measure_Clean(quint16 clean_count)
  {

      /*设置读取参数为浊度*/
      QModbusDataUnit writeUnit=QModbusDataUnit(QModbusDataUnit::HoldingRegisters,0x14,1);
      writeUnit.setValue(0,clean_count);
      Device1_reply = Device1->sendWriteRequest(writeUnit,DEVICE1_ADDR);
      if(Device1_reply)
      {
      if(!Device1_reply->isFinished())
      {
          connect(Device1_reply, &QModbusReply::finished, this, [this]() {qDebug("error");qDebug()<< Device1_reply->errorString();});
      }
      else
          Device1_reply->deleteLater();
      }else
      {
          qDebug()<<"Write error"<<Device1->errorString();
      }
  }
