## PaintArea类 ##
PaintArea是一个继承于QWidget的绘图类，提供绘制的函数，由mainwindow调用。
支持绘制图形: 点(point)、直线(line)、椭圆(ellipse)、圆(circle)、矩形(rectangle)、多边形(polygon)、随笔画(points)、任意边(polyline)。
支持工具：桶填充(Bucket)、滴管（dropper)、橡皮擦(eraser)、导入图片（loadImage)、图片放大缩小、图片的旋转、画布大小设置。
绘制选项：线形(dot line、dash line等)、线帽(square cap、round cap等)、填充模式(solid pattern、cross pattern等)。
### 1、绘图的实现 ###
每个PaintArea对象中有一个IsPainting变量标志当前是否正处于绘制状态。
![](http://i.imgur.com/ips9BoG.png)
如上图所示，PaintArea对外显示由两部分组成:背景部分backgroud 和 画布部分pix。其中所有的绘制部分均是对画布而言。画布的绘制，是先将原来的pix，即上一次绘制的结果绘制到一个新的变量copypix上，然后将这一次绘制的图形绘制上去（不论是否是IsPainting的状态）。如果是IsPainting状态，表示此次绘制过程没有结束，那么不把copypix保存到pix中。如果是IsPainting=FALSE的状态，那么表示绘制结束，将copypix保存到pix中。PaintArea对外显示是一个newpix的图像，即copypix和background的组合。
```cpp
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
```
### 2、不同图形的绘制实现 ###
图形的绘制由鼠标事件完成。
#### 2.1 直线的绘制 ####
取鼠标按下的点作为直线的起始点，鼠标释放的点作为直线的结束点。
![](http://i.imgur.com/5pfbCto.png)
#### 2.2 矩形的绘制 ####
取鼠标按下的点作为矩形的中心点，鼠标释放的点作为矩形的一个顶点。
![](http://i.imgur.com/qYLEq5Z.png)
#### 2.3 圆形的绘制 ####
取鼠标按下的点作为圆心，鼠标释放的点到圆心的距离作为半径。
![](http://i.imgur.com/DnNLkXO.png)
#### 2.4 椭圆的绘制 ####
取鼠标按下的作为椭圆的中心，鼠标释放的点与椭圆中心构成的矩形两条边与椭圆相切。
![](http://i.imgur.com/8yXbbCb.png)
#### 2.5 多边形的绘制 ####
每次鼠标按下一次，就把按下的点作为多边形的一个新的顶点。右键点击结束绘制。
![](http://i.imgur.com/GQaFY37.png)
#### 2.6 多条边的绘制 ####
每次鼠标按下一次，就把按下的点与前一点做一条新边。右键点击结束绘制。
![](http://i.imgur.com/3jJ0tXe.png)
#### 2.7 随笔画 ####
每次鼠标移动都将新的点加入points的列表中，对points的所有点画图。
![](http://i.imgur.com/WnzkyMj.png)
#### 2.8 橡皮的实现 ####
橡皮的实现与随笔画类似。将画笔的颜色设为白色，画笔宽度设为10，就可达到橡皮的效果。
#### 2.9 导入图片 ####
将pix变量作为画布，把需要导入的图片画到(pix, 0, 0)上即可。
```cpp
void PaintArea::loadImageFile(QString filename)
{
    QPainter p;
    //导入图片
    p.begin(pix);
    p.drawPixmap(0, 0, QPixmap(filename));
    p.end();
}
```
```cpp
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
```
### 3、画布的操作 ###
#### 3.1 画布大小的设置 ####
提供set_height和set_width的接口改变画布大小。
```cpp
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
```
#### 3.2 图片的放大缩小 ####
将图片保持纵横比放大或者缩小原图的20%.
```cpp
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
```
#### 3.3 图片的旋转 ####
把图片的长宽颠倒达到把图片顺时针旋转90°的效果。
```cpp
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
```