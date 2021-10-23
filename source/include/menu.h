#ifndef MENU_H
#define MENU_H
#include <QWidget>
#include "QTimer"
#include "QLabel"
#include "menu_alarm.h"
#include "menu_output.h"
#include "menu_note.h"
#include "menu_correct.h"
class Menu : public QWidget
{
    Q_OBJECT
public:
    explicit Menu(QWidget *parent = nullptr);
    void set_parent_view(QWidget * parent);
private:
    QTimer *Refresh_Timer;
    QLabel *time_label;
    QWidget *parent_view;
private slots:
    void set_clock(void);
    void back(void);
    void Menu_Alarm_slot(void);
    void Menu_Output_slot(void);
    void Menu_Note_slot(void);
    void Menu_Correct_slot(void);
    void exit_slot(void);
protected:
     void paintEvent(QPaintEvent *event) override;
signals:

};
#define ORIGIN_X 10
#define ORIGIN_Y 50
#define BUTTON_W 187
#define BUTTON_H 180
#endif // MENU_H
