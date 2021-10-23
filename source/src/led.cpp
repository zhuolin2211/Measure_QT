#include "led.h"
#include <QPaintEvent>
#include <QPainter>
#include "qdebug.h"
LED::LED(QWidget *parent) : QWidget(parent)
{
 state = false;
}
void LED::display(bool key)
{
    state = key;
    repaint();
}

void LED::setimg(const QString &filename)
{
    this->ledpixmap = QPixmap(filename);
    repaint();
}
void LED::paintEvent(QPaintEvent *event)//重写了继承自qwidget的painEvent方法
{
    QPainter paint(this);
    /**
     *rect()返回需要更新的矩形范围 QRect
     * QRect.intersects() QRect与contentsRect()相交则返回true
     * 返回widget的范围
     * 也就是判断这个对象绘制时的坐标位于窗口或者widget内
     **/
    if (event->rect().intersects(contentsRect()))
    {
        /**
         *region()返回需要更新的区域
         * intersected(contentsRect())返回当前widget与区域的交点区域
         * 设置剪辑上述区域到绘制区域paint
          **/

       paint.setClipRegion(event->region().intersected(contentsRect()));
        QRect r = contentsRect();
        /**
         * qMin 最小值
         **/
        int size = qMin(r.width(), r.height());
        /**
         * @brief center
         * 创建一个点
         **/
        QPoint center(size / 2, size / 2 );
        /**
         * setBrush()设置画笔
         **/
        //抗锯齿
        paint.setRenderHints(QPainter::SmoothPixmapTransform);
        if(state)
        {
            paint.setBrush(QBrush(Qt::red,Qt::SolidPattern));
        }
        else
        {
            paint.setBrush(QBrush(Qt::darkRed,Qt::SolidPattern));
        }
        /**
         * 绘制椭圆
         **/
       // paint.drawEllipse(center,size/2-1,size/2-1);
        paint.drawPixmap(rect(),this->ledpixmap,QRect());

    }
}
