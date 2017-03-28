#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include "paintarea.h"
#include <QLabel>
#include <QComboBox>
#include <QSpinBox>
#include <QPushButton>
#include <QGridLayout>
#include <QGradient>
#include <QComboBox>
#include <QAction>
#include <QToolBar>
#include <QString>
#include <QFileDialog>
#include <QFileInfo>
#include <QColorDialog>
#include <QMessageBox>
#include <QScrollArea>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    QMenu *fileMenu;//定义菜单栏
    PaintArea *paintArea;//定义paintArea类的变量

    PaintArea::Shape shape;//定义画笔与笔刷的属性
    QBrush brush;
    QColor color;
    QColor back_color;
    Qt::PenStyle style;
    Qt::PenCapStyle cap;
    Qt::PenJoinStyle join;
    Qt::FillRule rule;
    QGradient::Spread spread;
    Qt::BrushStyle brushStyle;
    int width;
    int color_position_state;

    QAction *fileNew;//定义各个功能的事件
    QAction *fileOpen;
    QAction *fileSave;
    QAction *fileStepback;
    QAction *fileStepforward;

    QAction *styleSolidLine;
    QAction *styleDashLine;
    QAction *styleDotLine;
    QAction *styleDashDotLine;
    QAction *styleDashDotDotLine;
    QAction *styleCustomDashLine;

    QAction *capSquareCap;
    QAction *capFlatCap;
    QAction *capRoundCap;

    QAction *joinBevelJoin;
    QAction *joinMiterJoin;
    QAction *joinRoundJoin;

    QAction *fillOddEvenFill;
    QAction *fillWindingFill;

    QAction *spreadPadSpread;
    QAction *spreadRepeatSpread;
    QAction *spreadReflectSpread;

    QAction *patternSolidPattern;
    QAction *patternDense1Pattern;
    QAction *patternDense2Pattern;
    QAction *patternDense3Pattern;
    QAction *patternDense4Pattern;
    QAction *patternDense5Pattern;
    QAction *patternDense6Pattern;
    QAction *patternDense7Pattern;
    QAction *patternHorPattern;
    QAction *patternVerPattern;
    QAction *patternCrossPattern;
    QAction *patternBDiagPattern;
    QAction *patternFDiagPattern;
    QAction *patternDiagCrossPattern;
    QAction *patternLinearGradientPattern;
    QAction *patternConicalGradientPattern;
    QAction *patternTexturePattern;

    QAction *toolNew;
    QAction *toolOpen;
    QAction *toolSave;
    QAction *toolStepback;
    QAction *toolStepforward;
    QAction *toolMax;
    QAction *toolMin;
    QAction *toolRotate;
    QAction *toolPen;
    QAction *toolEraser;
    QAction *toolBucket;
    QAction *toolDropper;
    QAction *toolLine;
    QAction *toolRectangle;
    QAction *toolEllipse;
    QAction *toolCircle;
    QAction *toolPolygon;
    QAction *toolPolyline;
    QAction *toolPoint;
    QAction *toolPixmap;
    QSpinBox *toolWidth;
    QSpinBox *painterWidth;
    QSpinBox *painterHeight;
    QAction *colorBlack;
    QAction *colorRed;
    QAction *colorWhite;
    QAction *colorYellow;
    QAction *colorGreen;
    QAction *colorBlue;
    QAction *colorChoose;

    QPushButton *choose_back;
    QPushButton *choose_front;

private slots:

    void fill_OddEvenFill();//对各个槽函数的声明
    void fill_WindingFill();

    void spread_PadSpread();
    void spread_RepeatSpread();
    void spread_ReflectSpread();

    void pattern_SolidPattern();
    void pattern_Dense1Pattern();
    void pattern_Dense2Pattern();
    void pattern_Dense3Pattern();
    void pattern_Dense4Pattern();
    void pattern_Dense5Pattern();
    void pattern_Dense6Pattern();
    void pattern_Dense7Pattern();
    void pattern_HorPattern();
    void pattern_VerPattern();
    void pattern_CrossPattern();
    void pattern_BDiagPattern();
    void pattern_FDiagPattern();
    void pattern_DiagCrossPattern();
    void pattern_LinearGradientPattern();
    void pattern_ConicalGradientPattern();
    void pattern_TexturePattern();

    void pattern_setting();

    void file_new();
    bool file_open();
    void file_save();
    void file_stepback();
    void file_stepforward();
    void image_max();
    void image_min();
    void image_rotate();
    void style_SolidLine();
    void style_DashLine();
    void style_DotLine();
    void style_DashDotLine();
    void style_DashDotDotLine();
    void style_CustomDashLine();

    void cap_SquareCap();
    void cap_FlatCap();
    void cap_RoundCap();

    void join_BevelJoin();
    void join_MiterJoin();
    void join_RoundJoin();

    void shape_pen();
    void shape_eraser();
    void shape_bucket();
    void shape_dropper();

    void shape_line();
    void shape_rectangle();
    void shape_ellipse();
    void shape_circle();
    void shape_polygon();
    void shape_polyline();
    void shape_point();
    void width_set(int);
    void color_black();
    void color_red();
    void color_white();
    void color_yellow();
    void color_green();
    void color_blue();
    void color_choose();

    void choose_color_front();
    void choose_color_back();

    void painter_width_set(int value);
    void painter_height_set(int value);
};

#endif // MAINWINDOW_H
