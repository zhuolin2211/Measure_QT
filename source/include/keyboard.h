#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <QWidget>
#include "QPushButton"
#include "QFont"
#include "QLineEdit"
#include "QDebug"
#include "QLabel"
#include "main.h"
#define ORIGIN_X (60)
#define ORIGIN_Y (140)
#define BUTTON_W 120
#define BUTTON_H 80
class keyboard : public QWidget
{
    Q_OBJECT
public:
    explicit keyboard(QWidget *parent = nullptr);
     void set_parent_view(QWidget * parent);
private:
     QTimer *Refresh_Timer;
     QLabel *time_label;
    QLineEdit *number_edit;
    QString input_string;
    void number_check(QString & str);
    QWidget *parent_view;
signals:
    void  keyboard_signal(float);


private slots:
    void number1_sclick(void);
    void number2_sclick(void);
    void number3_sclick(void);
    void number4_sclick(void);
    void number5_sclick(void);
    void number6_sclick(void);
    void number7_sclick(void);
    void number8_sclick(void);
    void number9_sclick(void);
    void number0_sclick(void);
     void number_point_sclick(void);
     void number_negative_sclick(void);
      void number_delete_sclick(void);
       void number_back_sclick(void);
    void number_ok_sclick(void);
    void set_clock(void);
protected:
     void paintEvent(QPaintEvent *event) override;
};
#define IPUT_MAX 10
#endif // KEYBOARD_H
