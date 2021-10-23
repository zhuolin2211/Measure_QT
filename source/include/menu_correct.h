#ifndef MENU_CORRECT_H
#define MENU_CORRECT_H

#include <QWidget>
#include "QTimer"
#include "QLabel"
#include "main.h"
#include "QLineEdit"

class Menu_Correct : public QWidget
{
    Q_OBJECT
public:
    explicit Menu_Correct(QWidget *parent = nullptr);
    void set_parent_view(QWidget * parent);
      void set_dispaly_nubmer(float number);
private:
    QTimer *Refresh_Timer;
    QLabel *time_label;
    QWidget *parent_view;
    QLabel *dispaly_nubmer;
    QLineEdit *Slope_edit;
    QLineEdit *Vol_edit;

private slots:
    void set_clock(void);
    void back(void);
    void receive_App_Measure_muddy_slot(float muddy);
    void Slope_button_clicked_slot();
    void Vol_button_clicked_slot();
    void Slope_receive_keyboard(float keyboard);
    void Vol_receive_keyboard(float keyboard);
signals:

protected:
     void paintEvent(QPaintEvent *event) override;
};

#endif // MENU_CORRECT_H
