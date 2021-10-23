#ifndef APP_OUTPUT_H
#define APP_OUTPUT_H

#include <QObject>
#include <QModbusRtuSerialSlave>
#include <QModbusTcpServer>
#include "QSerialPort"
class App_Output : public QObject
{
    Q_OBJECT
public:
    explicit App_Output(QObject *parent = nullptr);
    void App_Output_Connect(void);
    void App_Output_Set_com(QString com){App_Output_com=com;}
    void App_Output_Set_baud(quint16 baud){App_Output_baud=baud;}
    void App_Output_Set_databit(quint8 databit){App_Output_databit=databit;}
    void App_Output_Set_parity(quint8 parity){App_Output_parity=parity;}
    void App_Output_Set_stopbit(quint8 stopbit){App_Output_stopbit=stopbit;}
    void App_Output_Set_serveraddr(quint16 addr){ServerAddress=addr;}
    QString App_Output_Get_com(void){return App_Output_com;}
    quint16 App_Output_Get_baud(void){return App_Output_baud;}
    quint8 App_Output_Get_databit(void){return App_Output_databit;}
    quint8 App_Output_Get_parity(void){return App_Output_parity;}
    quint8 App_Output_Get_stopbit(void){return App_Output_stopbit;}
    quint16 App_Output_Get_serveraddr(void){return ServerAddress;}
public slots:
    void App_Output_option_slot(void);
private:
    QModbusServer *modbusDevice;

    /*参数*/
    QString App_Output_com;
    quint16 App_Output_baud=QSerialPort::Baud19200;
    quint8 App_Output_databit=QSerialPort::Data8;
    quint8 App_Output_parity =QSerialPort::NoParity;
    quint8 App_Output_stopbit =QSerialPort::OneStop;

    quint16 ServerAddress;
signals:
private slots:
    void App_Output_Receive_muddy_slot(float);
};
#endif // APP_OUTPUT_H
