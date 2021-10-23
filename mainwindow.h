#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QTimer"
#include "QLabel"
#include "main.h"
#include "QStackedWidget"
#include "menu.h"
#include "history.h"
#include "led.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void Draw_main(void);
    void set_relay1_state(bool state);
    void set_relay2_state(bool state);
    void set_relay3_state(bool state);
private:
    Ui::MainWindow *ui;
    QLabel *dispaly_nubmer;
    LED *LED1,*LED2,*LED3;
    bool relay1_state=0;
    bool relay2_state=0;
    bool relay3_state=0;
    QTimer *Refresh_Timer;
    QLabel *time_label;
    QPushButton *Manual_Clean;
    QTimer *Clean_Timer =new QTimer();
private slots:
    void set_clock(void);
    void menu_jump(void);
    void history_jump(void);
    void receive_App_Measure_muddy_slot(float);
    void Clean_slot(void);
protected:
    void paintEvent(QPaintEvent *event) override;
    void set_dispaly_nubmer(float number);
protected slots:
    void Alarm_slot(int alarm);
};
extern void background(QWidget *parent );
#define RELAY_STATE_OFF_FILE ":/icon/resoure/icon/state_relay_off.png"
#define RELAY_STATE_ON_FILE ":/icon/resoure/icon/state_relay_on.png"
#endif // MAINWINDOW_H
