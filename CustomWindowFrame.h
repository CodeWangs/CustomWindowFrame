#pragma once

#include <QtWidgets/QWidget>
#include "ui_CustomWindowFrame.h"
#include <QMouseEvent>
#include <QDebug>
#include <QPaintEvent>
#include <QMainWindow>
#include <QStatusBar>
#include <QEvent>
#include <QBoxLayout>
#include <QVBoxLayout>
#include <QFrame>
#include "CTitleBar.h"

#if !defined(__PRETTY_FUNCTION__) && !defined(__GNUC__)
#define __PRETTY_FUNCTION__ __FUNCSIG__
#endif


//将窗口划分成9宫格的9个区域，鼠标落在不同区域时，光标不同、拖拽效果不同
enum class CursorPos : unsigned int
{
    Default = 0,
    Top,
    TopRight,
    Right,
    BottomRight,
    Bottom,
    BottomLeft,
    Left,
    TopLeft,
};

//记录鼠标操作状态，在鼠标按下 —— 释放的周期内只进行一种类型的操作，防止出现向右拖动左侧边框，鼠标超过右侧边框时又去拖动右侧边框；
enum class MouseOpt : unsigned int
{
    Default = 0,//鼠标释放后的默认值
    MoveTop,
    MoveTopRight,
    MoveRight,
    MoveBottomRight,
    MoveBottom,
    MoveBottomLeft,
    MoveLeft,
    MoveTopLeft,
    MoveWindow,
};

class CustomWindowFrame : public QFrame
{
    Q_OBJECT

public:
    explicit CustomWindowFrame(QWidget *parent = nullptr);
    ~CustomWindowFrame();
private:
    void initCustomWindowFrame(void);
    void connectSignalSlot(void);
    CursorPos calculateMousePos(const QPoint Point);//计算鼠标位置所在区域
    void changeCursorShape(const CursorPos Type);//根据鼠标位置，改变光标形状
    bool event(QEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
public:
    void setCentralWidget(QWidget* widget);
signals:
private:
    Ui::CustomWindowFrameClass ui;
    CTitleBar* m_TitleBar = nullptr;
    QWidget* m_wid_CentralWidget = nullptr;
    QVBoxLayout* m_vlay_CentralWidget = nullptr;
    QVBoxLayout* m_vlay_Main = nullptr;

    int m_Border = 10;//四周边框宽度
    bool m_bMousePressed = false;//鼠标是否按下
    bool m_bMoveWindow = false;
    QPoint m_pot_MousePos;//拖拽前的鼠标位置（全局坐标）
    QRect m_rect_WindowPos;//拖拽前的窗口位置和大小
    CursorPos m_CursorPos;//当前鼠标区域
    MouseOpt m_MouseOpt;
};
