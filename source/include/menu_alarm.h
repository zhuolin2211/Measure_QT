#ifndef MENU_ALARM_H
#define MENU_ALARM_H

#include <QWidget>
#include "QTimer"
#include "QLabel"
#include "main.h"
#include "QLineEdit"
#include "keyboard.h"
#include "QPushButton"
class Menu_Alarm : public QWidget
{
    Q_OBJECT
public:
    explicit Menu_Alarm(QWidget *parent = nullptr);
    void set_parent_view(QWidget * parent);
private:
    QTimer *Refresh_Timer;
    QLabel *time_label;
    QWidget *parent_view;
    QLabel *dispaly_nubmer;
    QLineEdit *high_alarm_edit;
    QLineEdit *low_alarm_edit;
    QLineEdit *clear_alarm_edit;
private slots:
    void set_clock(void);
    void back(void);
    void receive_App_Measure_muddy_slot(float muddy);
    void high_alarm_button_clicked_slot(void);
    void low_alarm_button_clicked_slot(void);
    void clear_alarm_button_clicked_slot(void);
    void high_alarmreceive_keyboard(float);
    void low_alarmreceive_keyboard(float);
    void clear_alarmreceive_keyboard(float);
signals:

protected:
    void set_dispaly_nubmer(float number);
     void paintEvent(QPaintEvent *event) override;
};

#endif // MENU_ALARM_H
