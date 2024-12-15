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


//�����ڻ��ֳ�9�����9������������ڲ�ͬ����ʱ����겻ͬ����קЧ����ͬ
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

//��¼������״̬������갴�� ���� �ͷŵ�������ֻ����һ�����͵Ĳ�������ֹ���������϶����߿���곬���Ҳ�߿�ʱ��ȥ�϶��Ҳ�߿�
enum class MouseOpt : unsigned int
{
    Default = 0,//����ͷź��Ĭ��ֵ
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
    CursorPos calculateMousePos(const QPoint Point);//�������λ����������
    void changeCursorShape(const CursorPos Type);//�������λ�ã��ı�����״
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

    int m_Border = 10;//���ܱ߿���
    bool m_bMousePressed = false;//����Ƿ���
    bool m_bMoveWindow = false;
    QPoint m_pot_MousePos;//��קǰ�����λ�ã�ȫ�����꣩
    QRect m_rect_WindowPos;//��קǰ�Ĵ���λ�úʹ�С
    CursorPos m_CursorPos;//��ǰ�������
    MouseOpt m_MouseOpt;
};
