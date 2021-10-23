#include "app_output.h"
#include "QSerialPort"
#include "main.h"
App_Output::App_Output(QObject *parent) : QObject(parent)
{
modbusDevice= new QModbusRtuSerialSlave(this);
App_Output_Connect();
connect(measure_main,SIGNAL(App_Measure_muddy(float)),this,SLOT(App_Output_Receive_muddy_slot(float)));

}
void App_Output::App_Output_Connect(void)
{
    modbusDevice->disconnectDevice();
    if(modbusDevice->state() == QModbusDevice::UnconnectedState)
    {
        modbusDevice->setConnectionParameter(QModbusDevice::SerialPortNameParameter,App_Output_Get_com());
        modbusDevice->setConnectionParameter(QModbusDevice::SerialParityParameter, App_Output_Get_parity());
        modbusDevice->setConnectionParameter(QModbusDevice::SerialBaudRateParameter,App_Output_Get_baud());
        modbusDevice->setConnectionParameter(QModbusDevice::SerialDataBitsParameter,App_Output_Get_databit());
        modbusDevice->setConnectionParameter(QModbusDevice::SerialStopBitsParameter,App_Output_Get_stopbit());
        modbusDevice->setServerAddress(1);
        if (!modbusDevice->connectDevice()) {
            qDebug("串口连接失败");
            return;
        }
        QModbusDataUnitMap reg;
        reg.insert(QModbusDataUnit::Coils, { QModbusDataUnit::Coils, 0, 10 });
        reg.insert(QModbusDataUnit::DiscreteInputs, { QModbusDataUnit::DiscreteInputs, 0, 10 });
        reg.insert(QModbusDataUnit::InputRegisters, { QModbusDataUnit::InputRegisters, 0, 10 });
        reg.insert(QModbusDataUnit::HoldingRegisters, { QModbusDataUnit::HoldingRegisters, 0, 10 });
        modbusDevice->setMap(reg);
        modbusDevice->setData(QModbusDataUnit::HoldingRegisters,0,0);
        modbusDevice->setData(QModbusDataUnit::HoldingRegisters,1,0);
    }
    else {
        qDebug()<<"已经连接";
    }
}
void App_Output::App_Output_Receive_muddy_slot(float muddy)
{
    quint16 high_byte,low_byte;
    quint32 *temp;
    temp=(quint32*)&muddy;
    low_byte = (*temp)&0xffff;
    high_byte=((*temp)>>16)&0xffff;
    modbusDevice->setData(QModbusDataUnit::HoldingRegisters,0,low_byte);
    modbusDevice->setData(QModbusDataUnit::HoldingRegisters,1,high_byte);
}
void App_Output::App_Output_option_slot(void)
{
    modbusDevice->setConnectionParameter(QModbusDevice::SerialPortNameParameter,App_Output_Get_com());
    modbusDevice->setConnectionParameter(QModbusDevice::SerialParityParameter, App_Output_Get_parity());
    modbusDevice->setConnectionParameter(QModbusDevice::SerialBaudRateParameter,App_Output_Get_baud());
    modbusDevice->setConnectionParameter(QModbusDevice::SerialDataBitsParameter,App_Output_Get_databit());
    modbusDevice->setConnectionParameter(QModbusDevice::SerialStopBitsParameter,App_Output_Get_stopbit());
    modbusDevice->setServerAddress(1);
    App_Output_Connect();
    qDebug()<<"App_Output_option_slot";
}
