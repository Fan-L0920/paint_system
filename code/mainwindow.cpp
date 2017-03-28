#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowTitle("simple painter");//窗体设置：窗体名字
    this->setWindowIcon(QIcon(":/new/prefix1/choosecolor"));//窗体设置：窗体图标
    this->setMinimumSize(1200,600);//窗体设置：窗体大小限制

    width = 1;//这里是对画笔的所有属性进行初始化的赋值，这是画笔宽度
    color = Qt::black;//画笔颜色
    back_color = Qt::white;//笔刷颜色
    shape = PaintArea::Points;//画笔形状
    style = Qt::SolidLine;//画笔风格
    cap = Qt::SquareCap;//画笔端点设置
    join = Qt::RoundJoin;//画笔交点设置
    brush.setColor(Qt::white);//笔刷颜色
    brushStyle=Qt::SolidPattern;//笔刷风格
    color_position_state=1;//控制画笔还是笔刷颜色选择

    paintArea =new PaintArea(this);//调用paintArea类并且设置画笔属性
    paintArea->setShape(shape);
    paintArea->setPen(QPen(color,width,style,cap,join));

    fileMenu = new QMenu(this);//创建菜单栏
    fileNew = new QAction(QIcon(":/new/prefix1/filenew"),tr("New file"),this);//菜单栏的文件操作各条功能
    fileOpen = new QAction(QIcon(":/new/prefix1/fileopen"),tr("Open file"),this);
    fileSave = new QAction(QIcon(":/new/prefix1/filesave"),tr("Save file"),this);
    fileStepback = new QAction(QIcon(":/new/prefix1/stepback"),tr("Step back"),this);
    fileStepforward = new QAction(QIcon(":/new/prefix1/forward"),tr("Step forward"),this);

    styleSolidLine = new QAction(QIcon(),tr("Solid line"),this);//菜单栏中对画笔的各属性设置
    styleDashLine = new QAction(QIcon(),tr("Dash line"),this);
    styleDotLine = new QAction(QIcon(),tr("Dot line"),this);
    styleDashDotLine = new QAction(QIcon(),tr("Dash dot line"),this);
    styleDashDotDotLine = new QAction(QIcon(),tr("Dash dot dot line"),this);
    styleCustomDashLine = new QAction(QIcon(),tr("Custom dash line"),this);
    capSquareCap = new QAction(QIcon(),tr("Sqare cap"),this);
    capFlatCap = new QAction(QIcon(),tr("Flat cap"),this);
    capRoundCap = new QAction(QIcon(),tr("Round cap"),this);
    joinBevelJoin = new QAction(QIcon(),tr("Bevel join"),this);
    joinMiterJoin = new QAction(QIcon(),tr("Miter join"),this);
    joinRoundJoin = new QAction(QIcon(),tr("Round join"),this);

    fillOddEvenFill = new QAction(QIcon(),tr("Odd Even Fill"),this);//菜单栏中对笔刷填充的各属性设置
    fillWindingFill = new QAction(QIcon(),tr("Winding Fill"),this);
    spreadPadSpread = new QAction(QIcon(),tr("Pad Spread"),this);
    spreadRepeatSpread = new QAction(QIcon(),tr("Repeat Spread"),this);
    spreadReflectSpread = new QAction(QIcon(),tr("Reflect Spread"),this);
    patternSolidPattern = new QAction(QIcon(),tr("Solid Pattern"),this);
    patternDense1Pattern = new QAction(QIcon(),tr("Dense1 Pattern"),this);
    patternDense2Pattern = new QAction(QIcon(),tr("Dense2 Pattern"),this);
    patternDense3Pattern = new QAction(QIcon(),tr("Dense3 Pattern"),this);
    patternDense4Pattern = new QAction(QIcon(),tr("Dense4 Pattern"),this);
    patternDense5Pattern = new QAction(QIcon(),tr("Dense5 Pattern"),this);
    patternDense6Pattern = new QAction(QIcon(),tr("Dense6 Pattern"),this);
    patternDense7Pattern = new QAction(QIcon(),tr("Dense7 Pattern"),this);
    patternHorPattern = new QAction(QIcon(),tr("Hor Pattern"),this);
    patternVerPattern = new QAction(QIcon(),tr("Ver Pattern"),this);
    patternCrossPattern = new QAction(QIcon(),tr("Cross Pattern"),this);
    patternBDiagPattern = new QAction(QIcon(),tr("BDiag Pattern"),this);
    patternFDiagPattern = new QAction(QIcon(),tr("FDiag Pattern"),this);
    patternDiagCrossPattern = new QAction(QIcon(),tr("Diag Cross Pattern"),this);
    patternLinearGradientPattern = new QAction(QIcon(),tr("Linear Gradient Pattern"),this);
    patternConicalGradientPattern = new QAction(QIcon(),tr("Conical Gradient Pattern"),this);
    patternTexturePattern = new QAction(QIcon(),tr("Texture Pattern"),this);

    fileNew->setShortcut(tr("Ctrl+N"));//对部分操作的快捷键设置
    fileOpen->setShortcut(tr("Ctrl+O"));
    fileSave->setShortcut(tr("Ctrl+S"));

    fileMenu = new QMenu(this);
    fileMenu = menuBar()->addMenu(tr("File"));//在菜单栏中新建File栏

    fileMenu->addAction(fileNew);//将文件操作事件加到File栏中
    fileMenu->addAction(fileOpen);
    fileMenu->addAction(fileSave);
    fileMenu->addSeparator();
    fileMenu->addAction(fileStepback);
    fileMenu->addAction(fileStepforward);

    fileMenu = menuBar()->addMenu(tr("Pen set"));//在菜单栏中新建Pen set栏

    QActionGroup *style_group = new QActionGroup(fileMenu);//将画笔各属性操作的事件添加到Pen set栏中
    fileMenu->addAction(styleSolidLine);
    style_group->addAction(styleSolidLine);
    styleSolidLine->setCheckable(true);
    styleSolidLine->setChecked(true);
    fileMenu->addAction(styleDashLine);
    style_group->addAction(styleDashLine);
    styleDashLine->setCheckable(true);
    fileMenu->addAction(styleDotLine);
    style_group->addAction(styleDotLine);
    styleDotLine->setCheckable(true);
    fileMenu->addAction(styleDashDotLine);
    style_group->addAction(styleDashDotLine);
    styleDashDotLine->setCheckable(true);
    fileMenu->addAction(styleDashDotDotLine);
    style_group->addAction(styleDashDotDotLine);
    styleDashDotDotLine->setCheckable(true);
    fileMenu->addAction(styleCustomDashLine);
    style_group->addAction(styleCustomDashLine);
    styleCustomDashLine->setCheckable(true);

    QActionGroup *cap_group = new QActionGroup(fileMenu);
    fileMenu->addSeparator();
    fileMenu->addAction(capSquareCap);
    cap_group->addAction(capSquareCap);
    capSquareCap->setCheckable(true);
    capSquareCap->setChecked(true);
    fileMenu->addAction(capFlatCap);
    cap_group->addAction(capFlatCap);
    capFlatCap->setCheckable(true);
    fileMenu->addAction(capRoundCap);
    cap_group->addAction(capRoundCap);
    capRoundCap->setCheckable(true);

    QActionGroup *join_group = new QActionGroup(fileMenu);
    fileMenu->addSeparator();
    fileMenu->addAction(joinRoundJoin);
    join_group->addAction(joinRoundJoin);
    joinRoundJoin->setCheckable(true);
    joinRoundJoin->setChecked(true);
    fileMenu->addAction(joinBevelJoin);
    join_group->addAction(joinBevelJoin);
    joinBevelJoin->setCheckable(true);
    fileMenu->addAction(joinMiterJoin);
    join_group->addAction(joinMiterJoin);
    joinMiterJoin->setCheckable(true);

    fileMenu = menuBar()->addMenu(tr("Fill set"));//在菜单栏中新建Fill set栏

    QActionGroup *fill_group = new QActionGroup(fileMenu);//将对笔刷的各属性设置事件添加到Fill set栏中
    fileMenu->addSeparator();
    fileMenu->addAction(fillOddEvenFill);
    fill_group->addAction(fillOddEvenFill);
    fillOddEvenFill->setCheckable(true);
    fillOddEvenFill->setChecked(true);
    fileMenu->addAction(fillWindingFill);
    fill_group->addAction(fillWindingFill);
    fillWindingFill->setCheckable(true);

    QActionGroup *spread_group = new QActionGroup(fileMenu);
    fileMenu->addSeparator();
    fileMenu->addAction(spreadPadSpread);
    spread_group->addAction(spreadPadSpread);
    spreadPadSpread->setCheckable(true);
    spreadPadSpread->setChecked(true);
    fileMenu->addAction(spreadRepeatSpread);
    spread_group->addAction(spreadRepeatSpread);
    spreadRepeatSpread->setCheckable(true);
    fileMenu->addAction(spreadReflectSpread);
    spread_group->addAction(spreadReflectSpread);
    spreadReflectSpread->setCheckable(true);

    QActionGroup *pattern_group = new QActionGroup(fileMenu);
    fileMenu->addSeparator();
    fileMenu->addAction(patternSolidPattern);
    pattern_group->addAction(patternSolidPattern);
    patternSolidPattern->setCheckable(true);
    patternSolidPattern->setChecked(true);
    fileMenu->addAction(patternDense1Pattern);
    pattern_group->addAction(patternDense1Pattern);
    patternDense1Pattern->setCheckable(true);
    fileMenu->addAction(patternDense2Pattern);
    pattern_group->addAction(patternDense2Pattern);
    patternDense2Pattern->setCheckable(true);
    fileMenu->addAction(patternDense3Pattern);
    pattern_group->addAction(patternDense3Pattern);
    patternDense3Pattern->setCheckable(true);
    fileMenu->addAction(patternDense4Pattern);
    pattern_group->addAction(patternDense4Pattern);
    patternDense4Pattern->setCheckable(true);
    fileMenu->addAction(patternDense5Pattern);
    pattern_group->addAction(patternDense5Pattern);
    patternDense5Pattern->setCheckable(true);
    fileMenu->addAction(patternDense6Pattern);
    pattern_group->addAction(patternDense6Pattern);
    patternDense6Pattern->setCheckable(true);
    fileMenu->addAction(patternDense7Pattern);
    pattern_group->addAction(patternDense7Pattern);
    patternDense7Pattern->setCheckable(true);
    fileMenu->addAction(patternHorPattern);
    pattern_group->addAction(patternHorPattern);
    patternHorPattern->setCheckable(true);
    fileMenu->addAction(patternVerPattern);
    pattern_group->addAction(patternVerPattern);
    patternVerPattern->setCheckable(true);
    fileMenu->addAction(patternCrossPattern);
    pattern_group->addAction(patternCrossPattern);
    patternCrossPattern->setCheckable(true);
    fileMenu->addAction(patternBDiagPattern);
    pattern_group->addAction(patternBDiagPattern);
    patternBDiagPattern->setCheckable(true);
    fileMenu->addAction(patternFDiagPattern);
    pattern_group->addAction(patternFDiagPattern);
    patternFDiagPattern->setCheckable(true);
    fileMenu->addAction(patternDiagCrossPattern);
    pattern_group->addAction(patternDiagCrossPattern);
    patternDiagCrossPattern->setCheckable(true);
    fileMenu->addAction(patternLinearGradientPattern);
    pattern_group->addAction(patternLinearGradientPattern);
    patternLinearGradientPattern->setCheckable(true);
    fileMenu->addAction(patternConicalGradientPattern);
    pattern_group->addAction(patternConicalGradientPattern);
    patternConicalGradientPattern->setCheckable(true);
    fileMenu->addAction(patternTexturePattern);
    pattern_group->addAction(patternTexturePattern);
    patternTexturePattern->setCheckable(true);

    connect(fileNew,SIGNAL(triggered(bool)),this,SLOT(file_new()));//下面是对上述的各项功能绑定到各槽函数
    connect(fileOpen,SIGNAL(triggered(bool)),this,SLOT(file_open()));
    connect(fileSave,SIGNAL(triggered(bool)),this,SLOT(file_save()));
    connect(fileStepback,SIGNAL(triggered(bool)),this,SLOT(file_stepback()));
    connect(fileStepforward,SIGNAL(triggered(bool)),this,SLOT(file_stepforward()));

    connect(styleSolidLine,SIGNAL(triggered(bool)),this,SLOT(style_SolidLine()));
    connect(styleDashLine,SIGNAL(triggered(bool)),this,SLOT(style_DashLine()));
    connect(styleDotLine,SIGNAL(triggered(bool)),this,SLOT(style_DotLine()));
    connect(styleDashDotLine,SIGNAL(triggered(bool)),this,SLOT(style_DashDotLine()));
    connect(styleDashDotDotLine,SIGNAL(triggered(bool)),this,SLOT(style_DashDotDotLine()));
    connect(styleCustomDashLine,SIGNAL(triggered(bool)),this,SLOT(style_CustomDashLine()));
    connect(capSquareCap,SIGNAL(triggered(bool)),this,SLOT(cap_SquareCap()));
    connect(capFlatCap,SIGNAL(triggered(bool)),this,SLOT(cap_FlatCap()));
    connect(capRoundCap,SIGNAL(triggered(bool)),this,SLOT(cap_RoundCap()));
    connect(joinBevelJoin,SIGNAL(triggered(bool)),this,SLOT(join_BevelJoin()));
    connect(joinMiterJoin,SIGNAL(triggered(bool)),this,SLOT(join_MiterJoin()));
    connect(joinRoundJoin,SIGNAL(triggered(bool)),this,SLOT(join_RoundJoin()));
    connect(fillOddEvenFill,SIGNAL(triggered(bool)),this,SLOT(fill_OddEvenFill()));
    connect(fillWindingFill,SIGNAL(triggered(bool)),this,SLOT(fill_WindingFill()));
    connect(spreadPadSpread,SIGNAL(triggered(bool)),this,SLOT(spread_PadSpread()));
    connect(spreadRepeatSpread,SIGNAL(triggered(bool)),this,SLOT(spread_RepeatSpread()));
    connect(spreadReflectSpread,SIGNAL(triggered(bool)),this,SLOT(spread_ReflectSpread()));
    connect(patternSolidPattern,SIGNAL(triggered(bool)),this,SLOT(pattern_SolidPattern()));
    connect(patternDense1Pattern,SIGNAL(triggered(bool)),this,SLOT(pattern_Dense1Pattern()));
    connect(patternDense2Pattern,SIGNAL(triggered(bool)),this,SLOT(pattern_Dense2Pattern()));
    connect(patternDense3Pattern,SIGNAL(triggered(bool)),this,SLOT(pattern_Dense3Pattern()));
    connect(patternDense4Pattern,SIGNAL(triggered(bool)),this,SLOT(pattern_Dense4Pattern()));
    connect(patternDense5Pattern,SIGNAL(triggered(bool)),this,SLOT(pattern_Dense5Pattern()));
    connect(patternDense6Pattern,SIGNAL(triggered(bool)),this,SLOT(pattern_Dense6Pattern()));
    connect(patternDense7Pattern,SIGNAL(triggered(bool)),this,SLOT(pattern_Dense7Pattern()));
    connect(patternHorPattern,SIGNAL(triggered(bool)),this,SLOT(pattern_HorPattern()));
    connect(patternVerPattern,SIGNAL(triggered(bool)),this,SLOT(pattern_VerPattern()));
    connect(patternCrossPattern,SIGNAL(triggered(bool)),this,SLOT(pattern_CrossPattern()));
    connect(patternBDiagPattern,SIGNAL(triggered(bool)),this,SLOT(pattern_BDiagPattern()));
    connect(patternFDiagPattern,SIGNAL(triggered(bool)),this,SLOT(pattern_FDiagPattern()));
    connect(patternDiagCrossPattern,SIGNAL(triggered(bool)),this,SLOT(pattern_DiagCrossPattern()));
    connect(patternLinearGradientPattern,SIGNAL(triggered(bool)),this,SLOT(pattern_LinearGradientPattern()));
    connect(patternConicalGradientPattern,SIGNAL(triggered(bool)),this,SLOT(pattern_ConicalGradientPattern()));
    connect(patternTexturePattern,SIGNAL(triggered(bool)),this,SLOT(pattern_TexturePattern()));

    QToolBar *file_bar = this->addToolBar("File");//创建工具条File,Tool,Color,ColorPosition
    QToolBar *tool_bar = this->addToolBar("Tool");
    QToolBar *color_bar = this->addToolBar("Color");
    QToolBar *color_position = this->addToolBar("ColorPosition");
    QActionGroup *file_group = new QActionGroup(file_bar);
    QActionGroup *tool_group = new QActionGroup(tool_bar);
    QActionGroup *color_group = new QActionGroup(color_bar);

    this->setCentralWidget(paintArea);//将paintArea置于窗体中心

    toolNew = new QAction("New",file_bar);//下面是将各个功能添加到工具条并且绑定到目标槽函数之中
    toolNew->setIcon(QIcon(":/new/prefix1/filenew"));
    toolNew->setToolTip(tr("New"));
    toolNew->setStatusTip(tr("you can get a new painter"));
    toolNew->setCheckable(false);
    file_group->addAction(toolNew);
    file_bar->addAction(toolNew);
    connect(toolNew,SIGNAL(triggered(bool)),this,SLOT(file_new()));

    toolOpen = new QAction("Open",file_bar);
    toolOpen->setIcon(QIcon(":/new/prefix1/fileopen"));
    toolOpen->setToolTip(tr("Open"));
    toolOpen->setStatusTip(tr("you can open an image "));
    toolOpen->setCheckable(false);
    file_group->addAction(toolOpen);
    file_bar->addAction(toolOpen);
    connect(toolOpen,SIGNAL(triggered(bool)),this,SLOT(file_open()));

    toolSave = new QAction("Save",file_bar);
    toolSave->setIcon(QIcon(":/new/prefix1/filesave"));
    toolSave->setToolTip(tr("Save"));
    toolSave->setStatusTip(tr("you can save an image "));
    toolSave->setCheckable(false);
    file_group->addAction(toolSave);
    file_bar->addAction(toolSave);
    connect(toolSave,SIGNAL(triggered(bool)),this,SLOT(file_save()));

    toolStepback = new QAction("Stepback",file_bar);
    toolStepback->setIcon(QIcon(":/new/prefix1/stepback"));
    toolStepback->setToolTip(tr("Stepback"));
    toolStepback->setStatusTip(tr("Stepback to last state"));
    toolStepback->setCheckable(false);
    file_group->addAction(toolStepback);
    file_bar->addAction(toolStepback);
    connect(toolStepback,SIGNAL(triggered(bool)),this,SLOT(file_stepback()));

    toolStepforward = new QAction("Stepforward",file_bar);
    toolStepforward->setIcon(QIcon(":/new/prefix1/forward"));
    toolStepforward->setToolTip(tr("Stepforward"));
    toolStepforward->setStatusTip(tr("stepforward to the state you stepback"));
    toolStepforward->setCheckable(false);
    file_group->addAction(toolStepforward);
    file_bar->addAction(toolStepforward);
    connect(toolStepforward,SIGNAL(triggered(bool)),this,SLOT(file_stepforward()));

    toolMax = new QAction("Magnify", file_bar);
    toolMax->setIcon(QIcon(":/new/prefix1/max"));
    file_bar->addAction(toolMax);
    connect(toolMax, SIGNAL(triggered(bool)), this, SLOT(image_max()));

    toolMin = new QAction("Magnify", file_bar);
    toolMin->setIcon(QIcon(":/new/prefix1/min"));
    file_bar->addAction(toolMin);
    connect(toolMin, SIGNAL(triggered(bool)), this, SLOT(image_min()));

    toolRotate = new QAction("Magnify", file_bar);
    toolRotate->setIcon(QIcon(":/new/prefix1/rotate"));
    file_bar->addAction(toolRotate);
    connect(toolRotate, SIGNAL(triggered(bool)), this, SLOT(image_rotate()));
    toolPen = new QAction("Pen",tool_bar);
    toolPen->setIcon(QIcon(":/new/prefix1/pen"));
    toolPen->setToolTip(tr("Pen"));
    toolPen->setStatusTip(tr("now you can draw anything you like"));
    toolPen->setCheckable(true);
    toolPen->setChecked(true);
    tool_group->addAction(toolPen);
    tool_bar->addAction(toolPen);
    connect(toolPen,SIGNAL(triggered(bool)),this,SLOT(shape_pen()));

    toolEraser = new QAction("Eraser",tool_bar);
    toolEraser->setIcon(QIcon(":/new/prefix1/eraser"));
    toolEraser->setToolTip(tr("Eraser"));
    toolEraser->setStatusTip(tr("you can erase things"));
    toolEraser->setCheckable(true);
    tool_group->addAction(toolEraser);
    tool_bar->addAction(toolEraser);
    connect(toolEraser,SIGNAL(triggered(bool)),this,SLOT(shape_eraser()));

    toolBucket = new QAction("Bucket",tool_bar);
    toolBucket->setIcon(QIcon(":/new/prefix1/bucket"));
    toolBucket->setToolTip(tr("Bucket"));
    toolBucket->setStatusTip(tr("now you can painting a closed area"));
    toolBucket->setCheckable(true);
    tool_group->addAction(toolBucket);
    tool_bar->addAction(toolBucket);
    connect(toolBucket,SIGNAL(triggered(bool)),this,SLOT(shape_bucket()));

    toolDropper = new QAction("Dropper",tool_bar);
    toolDropper->setIcon(QIcon(":/new/prefix1/dropper"));
    toolDropper->setToolTip(tr("Dropper"));
    toolDropper->setStatusTip(tr("get color from where you like"));
    toolDropper->setCheckable(true);
    tool_group->addAction(toolDropper);
    tool_bar->addAction(toolDropper);
    connect(toolDropper,SIGNAL(triggered(bool)),this,SLOT(shape_dropper()));

    toolLine = new QAction("Line",tool_bar);
    toolLine->setIcon(QIcon(":/new/prefix1/line"));
    toolLine->setToolTip(tr("Line"));
    toolLine->setStatusTip(tr("now you can draw a line"));
    toolLine->setCheckable(true);
    tool_group->addAction(toolLine);
    tool_bar->addAction(toolLine);
    connect(toolLine,SIGNAL(triggered(bool)),this,SLOT(shape_line()));

    toolRectangle = new QAction("Rectangle",tool_bar);
    toolRectangle->setIcon(QIcon(":/new/prefix1/rectangle"));
    toolRectangle->setToolTip(tr("Rectangle"));
    toolRectangle->setStatusTip(tr("now you can draw a rectangle"));
    toolRectangle->setCheckable(true);
    tool_group->addAction(toolRectangle);
    tool_bar->addAction(toolRectangle);
    connect(toolRectangle,SIGNAL(triggered(bool)),this,SLOT(shape_rectangle()));

    toolEllipse = new QAction("Ellipse",tool_bar);
    toolEllipse->setIcon(QIcon(":/new/prefix1/ellipse"));
    toolEllipse->setToolTip(tr("Ellipse"));
    toolEllipse->setStatusTip(tr("now you can draw a ellipse"));
    toolEllipse->setCheckable(true);
    tool_group->addAction(toolEllipse);
    tool_bar->addAction(toolEllipse);
    connect(toolEllipse,SIGNAL(triggered(bool)),this,SLOT(shape_ellipse()));

    toolCircle = new QAction("Circle",tool_bar);
    toolCircle->setIcon(QIcon(":/new/prefix1/circle"));
    toolCircle->setToolTip(tr("Circle"));
    toolCircle->setStatusTip(tr("now you can draw a circle"));
    toolCircle->setCheckable(true);
    tool_group->addAction(toolCircle);
    tool_bar->addAction(toolCircle);
    connect(toolCircle,SIGNAL(triggered(bool)),this,SLOT(shape_circle()));

    toolPolygon = new QAction("Polygon",tool_bar);
    toolPolygon->setIcon(QIcon(":/new/prefix1/polygon"));
    toolPolygon->setToolTip(tr("Polygon"));
    toolPolygon->setStatusTip(tr("now you can draw a polygon"));
    toolPolygon->setCheckable(true);
    tool_group->addAction(toolPolygon);
    tool_bar->addAction(toolPolygon);
    connect(toolPolygon,SIGNAL(triggered(bool)),this,SLOT(shape_polygon()));

    toolPolyline = new QAction("Polyline",tool_bar);
    toolPolyline->setIcon(QIcon(":/new/prefix1/polyline"));
    toolPolyline->setToolTip(tr("Polyline"));
    toolPolyline->setStatusTip(tr("now you can draw a polyline"));
    toolPolyline->setCheckable(true);
    tool_group->addAction(toolPolyline);
    tool_bar->addAction(toolPolyline);
    connect(toolPolyline,SIGNAL(triggered(bool)),this,SLOT(shape_polyline()));

    toolPoint = new QAction("Point",tool_bar);
    toolPoint->setIcon(QIcon(":/new/prefix1/point"));
    toolPoint->setToolTip(tr("Point"));
    toolPoint->setStatusTip(tr("now you can draw a point"));
    toolPoint->setCheckable(true);
    tool_group->addAction(toolPoint);
    tool_bar->addAction(toolPoint);
    connect(toolPoint,SIGNAL(triggered(bool)),this,SLOT(shape_point()));

    toolWidth =new QSpinBox();//对画笔粗度的设置
    toolWidth->setRange(0,20);
    toolWidth->setValue(1);
    tool_bar->addWidget(toolWidth);
    connect(toolWidth,SIGNAL(valueChanged(int)),this,SLOT (width_set(int)));

    painterWidth =new QSpinBox();//对画布宽度的设置
    painterWidth->setRange(100,1000);
    painterWidth->setSingleStep(20);
    painterWidth->setValue(600);
    tool_bar->addWidget(painterWidth);
    connect(painterWidth,SIGNAL(valueChanged(int)),this,SLOT (painter_width_set(int)));

    painterHeight =new QSpinBox();//对画布高度的设置
    painterHeight->setRange(100,1000);
    painterHeight->setSingleStep(20);
    painterHeight->setValue(400);
    tool_bar->addWidget(painterHeight);
    connect(painterHeight,SIGNAL(valueChanged(int)),this,SLOT (painter_height_set(int)));

    colorBlack = new QAction("Black",color_bar);
    colorBlack->setIcon(QIcon(":/new/prefix1/black"));
    colorBlack->setToolTip(tr("Black"));
    colorBlack->setStatusTip(tr("color black"));
    colorBlack->setCheckable(true);
    colorBlack->setChecked(true);
    color_group->addAction(colorBlack);
    color_bar->addAction(colorBlack);
    connect(colorBlack,SIGNAL(triggered(bool)),this,SLOT(color_black()));

    colorRed = new QAction("Red",color_bar);
    colorRed->setIcon(QIcon(":/new/prefix1/red"));
    colorRed->setToolTip(tr("Red"));
    colorRed->setStatusTip(tr("color Red"));
    colorRed->setCheckable(true);
    color_group->addAction(colorRed);
    color_bar->addAction(colorRed);
    connect(colorRed,SIGNAL(triggered(bool)),this,SLOT(color_red()));

    colorWhite = new QAction("White",color_bar);
    colorWhite->setIcon(QIcon(":/new/prefix1/white"));
    colorWhite->setToolTip(tr("White"));
    colorWhite->setStatusTip(tr("color White"));
    colorWhite->setCheckable(true);
    color_group->addAction(colorWhite);
    color_bar->addAction(colorWhite);
    connect(colorWhite,SIGNAL(triggered(bool)),this,SLOT(color_white()));

    colorYellow = new QAction("Yellow",color_bar);
    colorYellow->setIcon(QIcon(":/new/prefix1/yellow"));
    colorYellow->setToolTip(tr("Yellow"));
    colorYellow->setStatusTip(tr("color Yellow"));
    colorYellow->setCheckable(true);
    color_group->addAction(colorYellow);
    color_bar->addAction(colorYellow);
    connect(colorYellow,SIGNAL(triggered(bool)),this,SLOT(color_yellow()));

    colorGreen = new QAction("Green",color_bar);
    colorGreen->setIcon(QIcon(":/new/prefix1/green"));
    colorGreen->setToolTip(tr("Green"));
    colorGreen->setStatusTip(tr("color Green"));
    colorGreen->setCheckable(true);
    color_group->addAction(colorGreen);
    color_bar->addAction(colorGreen);
    connect(colorGreen,SIGNAL(triggered(bool)),this,SLOT(color_green()));

    colorBlue = new QAction("Blue",color_bar);
    colorBlue->setIcon(QIcon(":/new/prefix1/blue"));
    colorBlue->setToolTip(tr("Blue"));
    colorBlue->setStatusTip(tr("color Blue"));
    colorBlue->setCheckable(true);
    color_group->addAction(colorBlue);
    color_bar->addAction(colorBlue);
    connect(colorBlue,SIGNAL(triggered(bool)),this,SLOT(color_blue()));

    colorChoose = new QAction("Choose more color",color_bar);
    colorChoose->setIcon(QIcon(":/new/prefix1/choosecolor"));
    colorChoose->setToolTip(tr("Choose"));
    colorChoose->setStatusTip(tr("color Choose"));
    colorChoose->setCheckable(true);
    color_group->addAction(colorChoose);
    color_bar->addAction(colorChoose);
    connect(colorChoose,SIGNAL(triggered(bool)),this,SLOT(color_choose()));

    choose_front = new QPushButton(this);
    choose_front->setCheckable(true);
    choose_front->setText("Front");
    choose_front->setChecked(true);

    choose_back = new QPushButton(this);
    choose_back->setText("Back");
    choose_back->setCheckable(true);

    color_position->addWidget(choose_front);
    color_position->addWidget(choose_back);

    connect(choose_front,SIGNAL(clicked(bool)),this,SLOT(choose_color_front()));
    connect(choose_back,SIGNAL(clicked(bool)),this,SLOT(choose_color_back()));

}

MainWindow::~MainWindow()//析构函数
{
    delete ui;
}

void MainWindow::file_new(){//新建文件，将有警告提示窗
    int btn = QMessageBox::warning(this,tr("Hello"),tr("new file?"),
    QMessageBox::Yes | QMessageBox::Default,QMessageBox::No);
    if(btn == QMessageBox::Yes)
    {
        file_save();
        paintArea->clear();
        toolWidth->setValue(1);
        painterWidth->setValue(600);
        painterHeight->setValue(400);
    }
}

void MainWindow::fill_OddEvenFill(){//对填充方式的设置的槽函数
    rule = Qt::OddEvenFill;
    paintArea->setFillRule(rule);
}

void MainWindow::fill_WindingFill(){
    rule = Qt::WindingFill;
    paintArea->setFillRule(rule);
}

void MainWindow::spread_PadSpread(){//对扩散方式的设置的槽函数
    spread = QGradient::PadSpread;
}

void MainWindow::spread_RepeatSpread(){
    spread = QGradient::RepeatSpread;
}

void MainWindow::spread_ReflectSpread(){
    spread = QGradient::ReflectSpread;
}

void MainWindow::pattern_SolidPattern(){//对填充模式的设置的槽函数
    brushStyle = Qt::SolidPattern;
    pattern_setting();
}

void MainWindow::pattern_Dense1Pattern(){
    brushStyle = Qt::Dense1Pattern;
    pattern_setting();
}


void MainWindow::pattern_Dense2Pattern(){
    brushStyle = Qt::Dense2Pattern;
    pattern_setting();
}

void MainWindow::pattern_Dense3Pattern(){
    brushStyle = Qt::Dense3Pattern;
    pattern_setting();
}

void MainWindow::pattern_Dense4Pattern(){
    brushStyle = Qt::Dense4Pattern;
    pattern_setting();
}

void MainWindow::pattern_Dense5Pattern(){
    brushStyle = Qt::Dense5Pattern;
    pattern_setting();
}

void MainWindow::pattern_Dense6Pattern(){
    brushStyle = Qt::Dense6Pattern;
    pattern_setting();
}

void MainWindow::pattern_Dense7Pattern(){
    brushStyle = Qt::Dense7Pattern;
    pattern_setting();
}

void MainWindow::pattern_HorPattern(){
    brushStyle = Qt::HorPattern;
    pattern_setting();
}

void MainWindow::pattern_VerPattern(){
    brushStyle = Qt::VerPattern;
    pattern_setting();
}

void MainWindow::pattern_CrossPattern(){
    brushStyle = Qt::CrossPattern;
    pattern_setting();
}

void MainWindow::pattern_BDiagPattern(){
    brushStyle = Qt::BDiagPattern;
    pattern_setting();
}

void MainWindow::pattern_FDiagPattern(){
    brushStyle = Qt::FDiagPattern;
    pattern_setting();
}

void MainWindow::pattern_DiagCrossPattern(){
    brushStyle = Qt::DiagCrossPattern;
    pattern_setting();
}

void MainWindow::pattern_LinearGradientPattern(){
    brushStyle = Qt::LinearGradientPattern;
    pattern_setting();
}

void MainWindow::pattern_ConicalGradientPattern(){
    brushStyle = Qt::ConicalGradientPattern;
    pattern_setting();
}

void MainWindow::pattern_TexturePattern(){
    brushStyle = Qt::TexturePattern;
    pattern_setting();
}

void MainWindow::pattern_setting(){
    if(brushStyle == Qt::LinearGradientPattern)
    {
        QLinearGradient linearGradient(0,0,400,400);
        linearGradient.setColorAt(0.0,Qt::white);
        linearGradient.setColorAt(0.2,back_color);
        linearGradient.setColorAt(1.0,Qt::black);
        linearGradient.setSpread(spread);
        paintArea->setBrush(linearGradient);
    }
    else if(brushStyle == Qt::ConicalGradientPattern)
    {
        QConicalGradient conicalGradient(200,200,30);
        conicalGradient.setColorAt(0.0,Qt::white);
        conicalGradient.setColorAt(0.2,back_color);
        conicalGradient.setColorAt(1.0,Qt::black);
        paintArea->setBrush(conicalGradient);
    }
    else if(brushStyle == Qt::TexturePattern)
    {
        paintArea->setBrush(QBrush(QPixmap(":/new/prefix1/frog")));
    }
    else
    {
        paintArea->setBrush(QBrush(back_color,brushStyle));
    }
}

void MainWindow::choose_color_front(){//设置当前为对画笔颜色设置的状态
   choose_back->setChecked(false);
   choose_front->setChecked(true);
   color_position_state=1;

   colorBlack->setChecked(false);
   colorRed->setChecked(false);
   colorWhite->setChecked(false);
   colorYellow->setChecked(false);
   colorGreen->setChecked(false);
   colorBlue->setChecked(false);
   colorChoose->setChecked(false);
   if(color==Qt::black){
       colorBlack->setChecked(true);
   }
   else if(color==Qt::red){
       colorRed->setChecked(true);
   }
   else if(color==Qt::white){
       colorWhite->setChecked(true);
   }
   else if(color==Qt::yellow){
       colorYellow->setChecked(true);
   }
   else if(color==Qt::green){
       colorGreen->setChecked(true);
   }
   else if(color==Qt::blue){
       colorBlue->setChecked(true);
   }
   else{
       colorChoose->setChecked(true);
   }
}

void MainWindow::choose_color_back(){//设置当前为对笔刷颜色设置的状态
    choose_back->setChecked(true);
    choose_front->setChecked(false);
    color_position_state=0;

    colorBlack->setChecked(false);
    colorRed->setChecked(false);
    colorWhite->setChecked(false);
    colorYellow->setChecked(false);
    colorGreen->setChecked(false);
    colorBlue->setChecked(false);
    colorChoose->setChecked(false);

    if(back_color==Qt::black){
        colorBlack->setChecked(true);
    }
    else if(back_color==Qt::red){
        colorRed->setChecked(true);
    }
    else if(back_color==Qt::white){
        colorWhite->setChecked(true);
    }
    else if(back_color==Qt::yellow){
        colorYellow->setChecked(true);
    }
    else if(back_color==Qt::green){
        colorGreen->setChecked(true);
    }
    else if(back_color==Qt::blue){
        colorBlue->setChecked(true);
    }
    else{
        colorChoose->setChecked(true);
    }
 }

void MainWindow::style_SolidLine(){//对画笔风格的设置
    style = Qt::SolidLine;
    paintArea->setPen(QPen(color,width,style,cap,join));
}

void MainWindow::style_DashLine(){
    style = Qt::DashLine;
    paintArea->setPen(QPen(color,width,style,cap,join));
}

void MainWindow::style_DotLine(){
    style = Qt::DotLine;
    paintArea->setPen(QPen(color,width,style,cap,join));
}

void MainWindow::style_DashDotLine(){
    style = Qt::DashDotLine;
    paintArea->setPen(QPen(color,width,style,cap,join));
}

void MainWindow::style_DashDotDotLine(){
    style = Qt::DashDotDotLine;
    paintArea->setPen(QPen(color,width,style,cap,join));
}

void MainWindow::style_CustomDashLine()
{
    style = Qt::CustomDashLine;
    paintArea->setPen(QPen(color,width,style,cap,join));
}

void MainWindow::cap_SquareCap(){//对画笔端点的设置
    cap = Qt::SquareCap;
    paintArea->setPen(QPen(color,width,style,cap,join));
}

void MainWindow::cap_FlatCap(){
    cap = Qt::FlatCap;
    paintArea->setPen(QPen(color,width,style,cap,join));
}

void MainWindow::cap_RoundCap(){
    cap = Qt::RoundCap;
    paintArea->setPen(QPen(color,width,style,cap,join));
}

void MainWindow::join_BevelJoin(){//对画笔相交点的设置
    join = Qt::BevelJoin;
    paintArea->setPen(QPen(color,width,style,cap,join));
}

void MainWindow::join_MiterJoin(){
    join = Qt::MiterJoin;
    paintArea->setPen(QPen(color,width,style,cap,join));
}

void MainWindow::join_RoundJoin(){
    join = Qt::RoundJoin;
    paintArea->setPen(QPen(color,width,style,cap,join));
}

void MainWindow::color_black(){//对颜色的设置，其中包含了对画笔或者笔刷的颜色判断预设置
    if(color_position_state){
        color.setRgb(0,0,0);
        paintArea->setPen(QPen(color,width,style,cap,join));
    }
    else{
        back_color.setRgb(0,0,0);
        brush.setColor(back_color);
        paintArea->setBrush(QBrush(back_color,brushStyle));
    }
}

void MainWindow::color_red(){
    if(color_position_state){
        color.setRgb(255,0,0);
        paintArea->setPen(QPen(color,width,style,cap,join));
    }
    else{
        back_color.setRgb(255,0,0);
        brush.setColor(back_color);
        paintArea->setBrush(QBrush(back_color,brushStyle));
    }
}

void MainWindow::color_white(){
    if(color_position_state){
        color.setRgb(255,255,255);
        paintArea->setPen(QPen(color,width,style,cap,join));
    }
    else{
        back_color.setRgb(255,255,255);
        brush.setColor(back_color);
        paintArea->setBrush(QBrush(back_color,brushStyle));
    }
}

void MainWindow::color_yellow(){
    if(color_position_state){
        color.setRgb(255,255,0);
        paintArea->setPen(QPen(color,width,style,cap,join));
    }
    else{
        back_color.setRgb(255,255,0);
        brush.setColor(back_color);
        paintArea->setBrush(QBrush(back_color,brushStyle));
    }
}

void MainWindow::color_green(){
    if(color_position_state){
        color.setRgb(0,255,0);
        paintArea->setPen(QPen(color,width,style,cap,join));
    }
    else{
        back_color.setRgb(0,255,0);
        brush.setColor(back_color);
        paintArea->setBrush(QBrush(back_color,brushStyle));
    }
}

void MainWindow::color_blue(){
    if(color_position_state){
        color.setRgb(0,0,255);
        paintArea->setPen(QPen(color,width,style,cap,join));
    }
    else{
        back_color.setRgb(0,0,255);
        brush.setColor(back_color);
        paintArea->setBrush(QBrush(back_color,brushStyle));
    }
}

void MainWindow::color_choose(){
    if(color_position_state){
        color = QColorDialog::getColor();
        paintArea->setPen(QPen(color,width,style,cap,join));
    }
    else{
        back_color = QColorDialog::getColor();
        brush.setColor(back_color);
        paintArea->setBrush(QBrush(back_color,brushStyle));
    }
}

bool MainWindow::file_open()//调用文件浏览窗口来完成文件的打开
{
    QString filename = QFileDialog::getOpenFileName(this);
    QFileInfo fi(filename);
    if(fi.suffix()=="png"||fi.suffix()=="jpg"||fi.suffix()=="jpeg"||fi.suffix()=="bmp")
    {
        paintArea->loadImageFile(filename);
        return true;
    }
    else
        return false;
}
/*save image file*/
void MainWindow::file_save()//调用文件浏览窗口来完成文件的保存
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), "myQt.png", tr("Images (*.png *.jpg)"));
    paintArea->saveImageFile(fileName);
}

void MainWindow::file_stepback()//将调用保存的记录来还原前一步的状态
{
    paintArea->backPix();
}

void MainWindow::file_stepforward()//调用保存的撤销记录来完成向前撤销
{
    paintArea->forwardPix();
}

void MainWindow::shape_pen()//对画笔形状的设置
{
    shape = PaintArea::Points;
    paintArea->setShape(shape);
    color = paintArea->getPenColor();
    paintArea->setPen(QPen(color,width,style,cap,join));
}

void MainWindow::shape_eraser()
{
    shape = PaintArea::Eraser;
    paintArea->setShape(shape);
}

void MainWindow::shape_bucket()
{
    paintArea->setShape(PaintArea::Bucket);
    color = paintArea->getPenColor();
    paintArea->setPen(QPen(color,width,style,cap,join));
}

void MainWindow::shape_dropper()
{
    paintArea->setShape(PaintArea::Dropper);
    color = paintArea->getPenColor();
    paintArea->setPen(QPen(color,width,style,cap,join));
}

void MainWindow::shape_line()
{
    shape = PaintArea::Line;
    paintArea->setShape(shape);
    color = paintArea->getPenColor();
    paintArea->setPen(QPen(color,width,style,cap,join));
}

void MainWindow::shape_rectangle()
{
    shape = PaintArea::Rectangle;
    paintArea->setShape(shape);
    color = paintArea->getPenColor();
    paintArea->setPen(QPen(color,width,style,cap,join));
}

void MainWindow::shape_ellipse()
{
    shape = PaintArea::Ellipse;
    paintArea->setShape(shape);
    color = paintArea->getPenColor();
    paintArea->setPen(QPen(color,width,style,cap,join));
}

void MainWindow::shape_circle()
{
    shape = PaintArea::Circle;
    paintArea->setShape(shape);
    color = paintArea->getPenColor();
    paintArea->setPen(QPen(color,width,style,cap,join));
}

void MainWindow::shape_polygon()
{
    shape = PaintArea::Polygon;
    paintArea->setShape(shape);
    color = paintArea->getPenColor();
    paintArea->setPen(QPen(color,width,style,cap,join));
}

void MainWindow::shape_polyline()
{
    shape = PaintArea::Polyline;
    paintArea->setShape(shape);
    color = paintArea->getPenColor();
    paintArea->setPen(QPen(color,width,style,cap,join));
}

void MainWindow::shape_point()
{
    shape = PaintArea::Point;
    paintArea->setShape(shape);
    color = paintArea->getPenColor();
    paintArea->setPen(QPen(color,width,style,cap,join));
}

void MainWindow::width_set(int value)//对画笔粗度的调整
{
    width = value;
    paintArea->setPen(QPen(color,width,style,cap,join));
}
void MainWindow::painter_width_set(int value)//对画布宽度的调整
{
    paintArea->set_width(value);
}

void MainWindow::painter_height_set(int value)//对画布高度的调整
{
    paintArea->set_height(value);
}
void MainWindow::image_max()//调用paintArea当中的函数来完成对画布的放大
{
    paintArea->maximizeImage();
}

void MainWindow::image_min()//调用paintArea当中的函数来完成对画布的缩小
{
    paintArea->minimizeImage();
}
void MainWindow::image_rotate()//调用paintArea当中的函数来完成对画布的旋转
{
    paintArea->rotate_image();
}

