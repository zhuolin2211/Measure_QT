#ifndef APP_MEASURE_H
#define APP_MEASURE_H
#include "QDebug"
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include "QtSerialBus/QModbusRtuSerialMaster"
#include "QtSerialBus/QModbusDataUnit"
#include "QtSerialBus/QModbusServer"
#include "QtSerialBus/QModbusClient"
#include "QTimer"
#include "QDateTime"
#include "QMutex"
#include "sqlite3.h"
#include "platform_config.h"

class App_Measure  :public QObject
{
    Q_OBJECT
public:
    App_Measure();
    void App_Measure_Connect(void);
    float App_Measure_Current(void);//立即返回一次测量值
    void App_Measure_Set_Slope(float slope){Measure_Slope=slope;}
    void App_Measure_Set_Vol(float vol){ Measure_Vol= vol;}
     float App_Measure_Get_Slope(){return Measure_Slope; }
      float App_Measure_Get_Vol(){return Measure_Vol;}
        void App_Measure_Set_Alarmhigh(float high){Alarm_high_value =high;}
        void App_Measure_Set_Alarmlow(float low){Alarm_low_value=low;}
        float App_Measure_Get_Alarmhigh(){return Alarm_high_value;}
        float App_Measure_Get_Alarmlow(){return Alarm_low_value;}
        void App_Measure_Set_com_name(QString name){com_name=name;}
        QString App_Measure_Get_com_name(void){return com_name;}
    float App_Measure_count(float raw);//计算校准值
    void App_Measure_Set_Cleannumber(quint16 number){this->Clean_number= number;}
    quint16 App_Measure_Get_Cleannumber(void){return this->Clean_number;}
    /*history save data*/
    QMutex *Database_mutex =new QMutex();
    void App_Measure_SaveData(void);
    void App_Measure_Set_Save_Cycle(quint32 count){Save_Cycle=count;}
    quint32 App_Measure_Get_Save_Cycle(void){return Save_Cycle;}
    void App_Measure_Clean(quint16 clean_count = 1);
private:
    float Measure_Raw;//原始数据
    float Measure_Adept;//熟数据

    float Measure_Slope=1;//线性调整值
    float Measure_Vol=0;//偏置调整值

    float Alarm_high_value =80;
    float Alarm_low_value=40;
    quint16 Clean_number=1;
    void App_Measure_Get(void);
    void App_Measure_DeviceSet(void);
    int APP_Measure_Alarm(void);
    /*滤波计数器*/
    qint8 high_count;
    qint8 low_count;
    qint8 alarm_type;
    /*记录计数器*/
    quint32 Save_count=0;
    quint32 Save_Cycle=1;
    /*控件*/
     QModbusClient *Device1;
    QModbusReply *Device1_reply;
    QTimer *simpling_timer;
    /*串口配置*/
    QString com_name="ttyUSB0";
private slots:
    void Device1_Connect_State_Change(QModbusDevice::State state);
    void onReadReady_slot(void);
    void Simpling_timer_slot(void);
signals:
    void App_Measure_muddy(float);
    void App_Measure_suspension(float);
    void APP_Measure_Alarm_signal(int alam);

};
#define DEVICE1_ADDR 0x04
#define DEVICE1_DATA_ADDR_START 0x00
#define DEVICE1_DATA_ADDR_MAX 21
#endif // APP_MEASURE_H
