#ifndef LED_H
#define LED_H

#include <QWidget>

class LED : public QWidget
{
    Q_OBJECT
public:
    explicit LED(QWidget *parent = nullptr);
    void display( bool key);//设置LED灯状态
    void setimg(const QString &fileName);
protected:
    void paintEvent( QPaintEvent *event );//绘制自己的控件
    QPixmap ledpixmap;
private:
    bool state;//LED灯的状态
signals:

};

#endif // LED_H
