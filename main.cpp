#include "mainwindow.h"
#include "main.h"
#include <QApplication>
 App_Measure *measure_main;
App_Output *output;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    measure_main=new App_Measure();
    output =new App_Output();
    MainWindow w;//主界面
    w.show();
    return a.exec();
}
/*定时器槽函数，用于在每个界面中刷新时间*/
void Refresh_Time(QWidget * parent)
{


}
void background(QWidget *parent )
{
    static const QPoint Up_Hand[6] = {
        QPoint(0, 0),
        QPoint(800, 0),
        QPoint(800, 30),
        QPoint(790, 40),
        QPoint(10,40),
        QPoint(0,30)
    };
    static const QPoint Down_Hand[6] = {
        QPoint(0, 480),
        QPoint(0, 450),
        QPoint(10, 440),
        QPoint(790, 440),
        QPoint(800,450),
        QPoint(800,480)
    };
  QPainter p(parent);
  QColor main_color("#66cc33");
  p.setRenderHint(QPainter::Antialiasing);
  p.setPen(Qt::black);//画笔边框颜色
  p.setBrush(main_color);//填充颜色
   p.save();//将上面的代码压到栈中，修改后出栈，之前的参数不被修改
  p.drawConvexPolygon(Up_Hand,6);
  p.restore();
  p.save();
 p.drawConvexPolygon(Down_Hand,6);
 p.restore();

}
