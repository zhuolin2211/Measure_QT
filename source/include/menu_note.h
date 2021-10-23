#ifndef MENU_NOTE_H
#define MENU_NOTE_H

#include <QWidget>
#include "QTimer"
#include "QLabel"
#include "main.h"
#include "QDateTimeEdit"
#include "QComboBox"
#include "QPushButton"
#include "QDateTime"
#include "QDate"
#include "QTime"
class Menu_Note : public QWidget
{
    Q_OBJECT
public:
    explicit Menu_Note(QWidget *parent = nullptr);
    void set_parent_view(QWidget * parent);
private:


    QDateTime *new_datetime;
    QDate *_new_date;
    QTime *_new_time;
    struct datetime_struct
    {
        int year;
        int month;
        int day;
        int hour;
        int min;
        int second;
    }_new_datetime;

    QTimer *Refresh_Timer;
    QLabel *time_label;
    QWidget *parent_view;

    quint32  simpling_cycle_number=1;

     QLineEdit *year_edit;
     QLineEdit *month_edit;
     QLineEdit *day_edit;
     QLineEdit *hour_edit;
     QLineEdit *min_edit;
     QLineEdit *second_edit;
     QPushButton *year_button;
      QPushButton *month_button;
      QPushButton *day_button;
      QPushButton *hour_button;
      QPushButton *min_button;
      QPushButton *second_button;
      QPushButton *fix_button;
      QComboBox *simpling_cycle;
     QLineEdit *simpling_cycle_edit;

     QComboBox *serial_com;
private slots:
    void set_clock(void);
    void back(void);
     void year_button_slot(void);
     void month_button_slot(void);
     void day_button_slot(void);
     void hour_button_slot(void);
     void min_button_slot(void);
     void second_button_slot(void);
     void simpling_cycle_button(void);
     void fix_button_slot(void);
signals:

protected:
     void paintEvent(QPaintEvent *event) override;
};


#endif // MENU_NOTE_H
