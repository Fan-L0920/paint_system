#ifndef PAINTAREA_H
#define PAINTAREA_H

#include <QWidget>
#include <QPen>
#include <QBrush>
#include <QPainter>
#include <QMouseEvent>
#include <QTimerEvent>
#include <QVector>
#include <QPixmap>
#include <QResizeEvent>
#include <QFile>
#include <QFileDialog>
#include <QString>
#include <QImage>
#include <QQueue>
#include <QColor>
#include <QCursor>

class PaintArea : public QWidget
{
    Q_OBJECT
public:
    //shape types
    enum Shape{Line,Rectangle,Ellipse,Circle, Polygon, Polyline, Point, Points, Pixmap, Bucket, Dropper, Eraser};
    //constructor
    explicit PaintArea(QWidget *parent = 0);
    //设置形状
    void setShape(Shape);
    //设置画笔
    void setPen(QPen);
    //获得画笔的颜色
    QColor getPenColor();
    //设置画刷
    void setBrush(QBrush);
    //设置填充模式
    void setFillRule(Qt::FillRule);
    //绘图时间，update,repaint或者每隔固定时间间隔执行
    void paintEvent(QPaintEvent *);
    //鼠标键按下的事件
    void mousePressEvent(QMouseEvent *e);
    //鼠标移动事件
    void mouseMoveEvent(QMouseEvent *e);
    //鼠标释放事件
    void mouseReleaseEvent(QMouseEvent *e);
    //窗口大小变化事件
    void resizeEvent(QResizeEvent *e);
    //载入图片文件
    void loadImageFile(QString filename);
    //保存为图片文件
    void saveImageFile(QString filename);
    //设置为填充桶
    //采用深度优先填充
    //填充颜色为pen的颜色
    void setBucket(QPoint point);
    //设置为滴管
    void dropper(QPoint point);
    //撤回上一次操作
    void backPix();
    //取消上一次撤回
    void forwardPix();
    //放大image 20%
    void maximizeImage();       //
    //减小image 20%
    void minimizeImage();       //
    //画布清空重置
    void clear();
    //顺时针旋转画布90°
    void rotate_image();
    //设置画布高
    void set_height(int h);
    //设置画布宽
    void set_width(int w);
private:
    //保存上一张pix，用于刷新画面
    void saveLastPix(QPixmap &pix);
signals:

public slots: //added slots

private:
    //保存上10次操作用于撤回
    const int BACKSIZE = 10;
    const QPoint DefaultPoint = QPoint(-100, -100);
    //形状（绘制类型）
    Shape shape;
    //鼠标形状
    QCursor eraser_cursor, dropper_cursor, bucket_cursor;
    //默认鼠标形状
    QCursor cursor;
    //画笔
    QPen pen;
    //橡皮
    QPen eraser;
    //画刷
    QBrush brush;
    //填充模式
    Qt::FillRule fillRule;
    //rectangle 用于绘图
    QRect rect;
    //画线时的起点和终点
    QPoint startpoint, endpoint;
    //上一次操作的pix
    QPixmap *pix;
    //背景pix
    QPixmap *backround;
    //多边形的points
    QVector<QPoint> points;   /*points determine*/
    //前几次的操作
    QVector<QPixmap> record;
    //撤回的操作
    QVector<QPixmap> wrecord;
    //是否处于绘图中（标志）
    bool isPainting;
};

#endif // PAINTAREA_H
