#ifndef MENU_OUTPUT_H
#define MENU_OUTPUT_H

#include <QWidget>
#include "QTimer"
#include "QLabel"
#include "main.h"
#include "QComboBox"
#include "QPushButton"
#include "app_output.h"
#include "QLineEdit"
class Menu_Output : public QWidget
{
    Q_OBJECT
public:
    explicit Menu_Output(QWidget *parent = nullptr);
    void set_parent_view(QWidget * parent);
private:
    QTimer *Refresh_Timer;
    QLabel *time_label;
    QWidget *parent_view;

    QComboBox *serial_com;
    QComboBox *serial_baud;
    QComboBox *serial_parity;
    QComboBox *serial_databits;
    QComboBox *serial_stopbits;
    QPushButton *fix_button;
    QLineEdit *server_addr_edit;
private slots:
    void set_clock(void);
    void back(void);
    void fix(void);
    void Menu_Output_server_addr_button_slot(void);

signals:
    void Menu_Output_option(void);
protected:
     void paintEvent(QPaintEvent *event) override;
};

#endif // MENU_OUTPUT_H
