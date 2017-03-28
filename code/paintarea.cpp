#include "paintarea.h"
#include "algorithm"
#include <QtMath>
#include <QDebug>
PaintArea::PaintArea(QWidget *parent) :
    QWidget(parent)
{
    isPainting = false;
    setPalette(QPalette(Qt::white));
    setAutoFillBackground(true);        // auto fill
    // PaintArea widget minimum size
    setMinimumSize(700,450);

    //rect point 初始化
    rect = QRect(-1, -1, -1, -1);
    startpoint = DefaultPoint;
    endpoint = DefaultPoint;

    //initial 600*400 white填充
    pix = new QPixmap(600, 400);
    pix->fill(Qt::white);

    //背景初始化
    backround = new QPixmap(size());
    backround->fill(Qt::gray);

    points.push_back(DefaultPoint);
    /*set eraser*/
    eraser.setColor(Qt::white);
    eraser.setWidth(10);
    eraser.setCapStyle(Qt::RoundCap);
    eraser.setJoinStyle(Qt::RoundJoin);

    //特殊鼠标样式初始设置
    QPixmap bucket_pix(":/new/prefix1/cursor_bucket");
    bucket_cursor = QCursor(bucket_pix, -1, -1);

    QPixmap dropper_pix(":/new/prefix1/cursor_dropper");
    dropper_cursor = QCursor(dropper_pix, -1, -1);

    QPixmap erase_pix(":/new/prefix1/cursor_eraser");
    eraser_cursor = QCursor(erase_pix, -1, -1);
    //绘图鼠标样式
    cursor = QCursor(Qt::CrossCursor);

    setCursor(cursor);
    //记录栈清空
    record.clear();
    record.push_back(*pix);
    wrecord.clear();
}

void PaintArea::setShape(Shape s)
{
    shape = s;
    //根据形状设置鼠标
    if(s==Dropper)
        setCursor(dropper_cursor);
    else if(s==Bucket)
        setCursor(bucket_cursor);
    else if(s==Eraser)
        setCursor(eraser_cursor);
    else
        setCursor(cursor);
    update();       //更新，重画绘制区窗体
}

void PaintArea::setPen(QPen p)
{
    pen = p;
    update();
}

QColor PaintArea::getPenColor()
{
    return pen.color();
}

void PaintArea::setBrush(QBrush b)
{
    brush = b;
    update();
}

void PaintArea::setFillRule(Qt::FillRule rule)
{
    fillRule =rule;
    update();
}

void PaintArea::loadImageFile(QString filename)
{
    QPainter p;
    //导入图片
    p.begin(pix);
    p.drawPixmap(0, 0, QPixmap(filename));
    p.end();
}

void PaintArea::saveImageFile(QString filename)
{
    pix->toImage().save(filename);
}

void PaintArea::backPix()
{
    //如果有前面的操作
    if(record.size() > 1)
    {
        wrecord.push_back(*pix);
        record.pop_back();
        *pix = record.last();
        update();
    }
}

void PaintArea::forwardPix()
{
    //如果有过撤回操作
    if(!wrecord.empty())
    {
        *pix = wrecord.last();
        saveLastPix(wrecord.last());
        wrecord.pop_back();
        update();
    }
}

void PaintArea::maximizeImage()
{
    int width = pix->width() + pix->width()/5;
    int height = pix->height() + pix->height()/5;
    //保持纵横比放大
    *pix = pix->scaled(width,height,Qt::KeepAspectRatio, Qt::SmoothTransformation);
    repaint();
}

void PaintArea::minimizeImage()
{
    int width = pix->width() - pix->width()/5;
    int height = pix->height()- pix->height()/5;
    //保持纵横比缩小
    if(width >= 200 && height >= 200)
        *pix = pix->scaled(width,height,Qt::KeepAspectRatio, Qt::SmoothTransformation);
    repaint();
}

void PaintArea::rotate_image()
{
    QPixmap *npix = new QPixmap(pix->height(), pix->width());

    QPainter p(npix);
    p.translate(pix->height(), 0 );
    p.rotate(90);
    p.setPen(pen);
    p.setBrush(brush);
    p.drawPixmap(0, 0, *pix);;
    p.translate(-pix->height(), 0);
    p.end();
    pix = npix;
    repaint();
}

void PaintArea::set_height(int h)
{
    QPixmap *npix = new QPixmap(pix->width(),h);
    //默认白色
    npix->fill(Qt::white);
    QPainter p(npix);
    p.drawPixmap(0, 0, *pix);
    p.end();
    pix = npix;
    repaint();
}

void PaintArea::set_width(int w)
{
    QPixmap *npix = new QPixmap(w, pix->height());
    npix->fill(Qt::white);
    QPainter p(npix);
    p.drawPixmap(0, 0, *pix);
    p.end();
    pix = npix;
    repaint();
}


void PaintArea::saveLastPix(QPixmap &pix)
{
    if(record.size()>=BACKSIZE)
    {//如果超过上限
        record.pop_front();
        record.push_back(pix);
    }
    else
    {
        record.push_back(pix);
    }
    update();
}

void PaintArea::mousePressEvent(QMouseEvent *e)
{
    //没有在画图中情况
    if(!isPainting)
    {
        switch(shape)
        {
        //以下图形的情况
        //将开始点和结束点均设为当前鼠标按下的点
        case (Line):case (Rectangle):case(Ellipse):case(Circle):case(Point):
        {
            startpoint = endpoint = e->pos();
            break;
        }
        case(Bucket):
        {
            startpoint = endpoint = e->pos();
            isPainting = true;
            setBucket(startpoint);
            break;
        }
        //将当前鼠标点压入
        case (Polygon):case(Polyline):
        {
            *points.rbegin() = e->pos();
            points.push_back(e->pos());
            break;
        }
        //点
        case (Points):
        {
            *points.begin() = e->pos();
            break;
        }
        //滴管取当前点的颜色
        case(Dropper):
        {
            dropper(e->pos());
            break;
        }
        //橡皮
        //画笔设为橡皮模式
        case(Eraser):
        {
            setPen(eraser);
            *points.begin() = e->pos();
            break;
        }
        default:
        {
            break;
        }
        }
        isPainting = true;  //状态设置为正在画图
    }
    else
    {
        //多边形和多线的情况
        //points新添一个点
        switch(shape)
        {
        case (Polygon):case(Polyline):
        {
            *points.rbegin() = e->pos();
            points.push_back(e->pos());
            break;
        }
        default:
            break;
        }
    }
    update();

}

void PaintArea::mouseMoveEvent(QMouseEvent *e)
{
    // 鼠标移动
    // 正在绘图状态时
    if(isPainting)
    {
        switch(shape)
        {
        case(Line):
        {
            endpoint = e->pos();
            break;
        }
        case(Rectangle):
        {
            endpoint = e->pos();
            rect.setTopLeft(QPoint(std::min(startpoint.x(), endpoint.x()), std::min(startpoint.y(), endpoint.y())));
            rect.setBottomRight(QPoint(std::max(startpoint.x(), endpoint.x()), std::max(startpoint.y(), endpoint.y())));
            break;
        }
        case(Ellipse):
        {
            endpoint = e->pos();
            QPoint temppoint = 2*startpoint - endpoint;
            rect.setTopLeft(QPoint(std::min(temppoint.x(), endpoint.x()), std::min(temppoint.y(), endpoint.y())));
            rect.setBottomRight(QPoint(std::max(temppoint.x(), endpoint.x()), std::max(temppoint.y(), endpoint.y())));
            break;
        }
        case(Circle):
        {
            endpoint = e->pos();
            int delta_x = startpoint.x()-endpoint.x();
            int delta_y = startpoint.y() - endpoint.y();
            int radius =qFloor(qSqrt(delta_x*delta_x + delta_y*delta_y));
            rect.setTopLeft(QPoint(startpoint.x()-radius, startpoint.y()-radius));
            rect.setBottomRight(QPoint(startpoint.x()+radius, startpoint.y()+radius));
            break;
        }
        case(Polygon):case(Polyline):
        {
            *points.rbegin() = e->pos();
            break;
        }
        case(Points):case(Eraser):
        {
            points.push_back(e->pos());
            break;
        }
        default:
            break;
        }
    }
    //立即重绘
    repaint();
}

void PaintArea::mouseReleaseEvent(QMouseEvent *e)
{
    //左键释放
    if(e->button()==Qt::LeftButton)
    {
        if(isPainting)
        {   switch(shape)
            {
            //终止画图
            case(Line):case(Rectangle):case(Ellipse):case(Circle):case(Point):case(Bucket):case(Points):case(Dropper):
            {
                isPainting = false;
                repaint();
                //保存这一个pix
                saveLastPix(*pix);
                break;
            }
            case(Eraser):
            {
                isPainting = false;
                repaint();
                saveLastPix(*pix);
                setPen(pen);
                break;
            }
            default:
            {
                break;
            }
            }
        }
        update();
    }
    //右键释放
    else if(e->button()==Qt::RightButton)
    {
        if(isPainting)
        {
        switch(shape)
        {
            case(Polygon):
            {
                points.push_back(points.first());
                isPainting = false;
                repaint();
                saveLastPix(*pix);
                break;
            }

            case(Polyline):
            {
                isPainting = false;
                repaint();
                saveLastPix(*pix);
                break;
            }
        default:
            break;
        }
        }
    }
}

//窗口size变化
//背景pix随窗口size变化
void PaintArea::resizeEvent(QResizeEvent *e)
{
    QPixmap *nPix = new QPixmap(size());
    nPix->fill(Qt::gray);
    QPainter p(nPix);
    p.drawPixmap(QPoint(0,0),*backround);
    backround = nPix;
    QWidget::resizeEvent(e);
}

//填充，广度优先搜索
void PaintArea::setBucket(QPoint point)
{
    int i;
    int x = point.x(), y = point.y();
    int map_height = pix->height();     //get画布的size
    int map_width = pix->width();

    bool *pixl = new bool[map_height * map_width];//用于标记已经被遍历过的点,这里是动态分配的版本，二维数组一直不成功只能用一维数组了
    QPainter pp(pix);
    QQueue <QPoint> queue;//用于存放需填充的点
    const QPoint *point_pre_to_fill;//待填充的点
    QImage image = pix->toImage();  //put it to image
    QColor pix_color = image.pixelColor(point);
    for(i = 0; i < map_height * map_width; i++)
            pixl[i] = false;
    QPen ppen = pen;
    ppen.setWidth(1);
    pp.setPen(ppen);
    pp.setBrush(brush);
    point_pre_to_fill = &point;
    queue.enqueue(*point_pre_to_fill);
    pixl[point_pre_to_fill->x() *  map_height + point_pre_to_fill->y()] = true;
    pp.drawPoint(*point_pre_to_fill);
    while(queue.count() != 0)
    {
        x = queue.at(0).x();
        y = queue.at(0).y();
        queue.dequeue();//获取队列头的点的坐标，然后出队
        point_pre_to_fill = &QPoint(x, y + 1);
        if(y < map_height - 1 && pixl[x * map_height + y + 1] == false && image.pixelColor(*point_pre_to_fill) == pix_color)//如果当前点未遍历过且颜色与初始点相同，则将其填充，之后入队
        {
            pp.drawPoint(*point_pre_to_fill);
            queue.enqueue(*point_pre_to_fill);
            pixl[x * map_height + y + 1] = true;
        }
        point_pre_to_fill = &QPoint(x, y - 1);
        if(y > 1 && pixl[x * map_height + y - 1] == false && image.pixelColor(*point_pre_to_fill) == pix_color)
        {
            pp.drawPoint(*point_pre_to_fill);
            queue.enqueue(*point_pre_to_fill);
            pixl[x * map_height + y - 1] = true;
        }
        point_pre_to_fill = &QPoint(x + 1, y);
        if(x < map_width - 1 && pixl[(x + 1) * map_height + y] == false && image.pixelColor(*point_pre_to_fill) == pix_color)
        {
            pp.drawPoint(*point_pre_to_fill);
            queue.enqueue(*point_pre_to_fill);
            pixl[(x + 1) * map_height + y] = true;
        }
        point_pre_to_fill = &QPoint(x - 1, y);
        if(x > 1 && y < map_height && pixl[(x - 1) * map_height + y] == false && image.pixelColor(*point_pre_to_fill) == pix_color)
        {
            pp.drawPoint(*point_pre_to_fill);
            queue.enqueue(*point_pre_to_fill);
            pixl[(x - 1) * map_height + y] = true;
        }
    }
    pp.endNativePainting();
    delete[] pixl;
}

void PaintArea::dropper(QPoint point)
{   //滴管
    //获取当前点的color
    QColor color = pix->toImage().pixelColor(point);
    pen.setColor(color);
}

void PaintArea::clear()
{
    //重置
    record.clear();
    wrecord.clear();
    points.clear();
    startpoint = endpoint = DefaultPoint;
    pix = new QPixmap(600, 400);
    pix->fill(Qt::white);
    record.push_back(*pix);
    backround = new QPixmap(size());
    backround->fill(Qt::gray);
}

//most important
//采用多重缓冲的机制
//最后的pix结果存放在pix变量
void PaintArea::paintEvent(QPaintEvent *)
{
    QPainter p, pcopy;
    //newpix 存放的是此次绘制包含背景的临时图像
    QPixmap *newpix = new QPixmap(size());
    //copypix 存放的pix的临时绘制图像
    QPixmap *copypix = new QPixmap(*pix);
    //默认白色扩展
    newpix->fill(Qt::white);

    p.begin(newpix);
    p.setPen(pen);
    p.setBrush(brush);
    p.drawPixmap(0, 0, *backround);
    //将绘制的图形划入copypix
    pcopy.begin(copypix);
    pcopy.setPen(pen);
    pcopy.setBrush(brush);

    switch(shape)
    {
        case Line:                                         	//直线
            pcopy.drawLine(startpoint,endpoint); 	break;
        case Rectangle:                                    	//长方形
            pcopy.drawRect(rect);	break;
        case Circle:                                    	//圆，通过设置椭圆的参数
            pcopy.drawEllipse(rect); 	break;
        case Ellipse:                                      	//椭圆形
            pcopy.drawEllipse(rect); 	break;
        case Polygon:                                      	//多边形
            pcopy.drawPolyline(points); 	break;
        case Polyline:                                      //多线
            pcopy.drawPolyline(points); 	break;
        case Point:
            pcopy.drawPoint(startpoint);     break;              //点
        case Points:
            pcopy.drawPolyline(points);        break;              //随笔画
        case Eraser:
            pcopy.drawPolyline(points);         break;              //橡皮擦
        default: 	break;
    }

    pcopy.end();
    p.drawPixmap(0, 0, *copypix);
    p.end();

    if(!isPainting)
    {
        //isPainting = FALSE 表示只一次绘制步骤结束
        //将结果存入pix
        p.begin(pix);
        p.drawPixmap(0, 0, *newpix);
        p.end();
        /*set to initial status*/
        points.clear();
        points.push_back(DefaultPoint);
        startpoint = endpoint = DefaultPoint;
        rect = QRect(DefaultPoint, DefaultPoint);
    }
    //isPainting表示正在绘制，将撤回记录清空
    if(isPainting)
    {
        wrecord.clear(); /* new image insert so clear the waste*/
    }
    //将newpix正是显示
    p.begin(this);
    p.drawPixmap(0, 0, *newpix);
    p.end();
    delete[] newpix;
    delete[] copypix;
}
