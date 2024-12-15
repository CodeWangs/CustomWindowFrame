#pragma once

#include <QWidget>
#include "ui_CTitleBar.h"
#include <QLabel>
#include <QLineEdit>
#include <QAction>
#include <QPushButton>
#include <QHBoxLayout>
#include <QEvent>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QPoint>
#include <QString>

#define TITLEBAR_WIDTH 650 //标题栏宽 最好不要小于这个值，所有控件正常显示的最小值
#define TITLEBAR_HEIGHT 50 //标题栏高 最好不要小于这个值，会影响头像框的形状

class CTitleBar : public QWidget
{
	Q_OBJECT

public:
	explicit CTitleBar(QWidget *parent);
	~CTitleBar();
private:
	void initTitleBar(void);
	void connectSignalSlot(void);
    void enterEvent(QEvent* event) override;
    void leaveEvent(QEvent* event) override;
    void mouseDoubleClickEvent(QMouseEvent* event) override;
private slots:
    void showMinWindow_slot(void);
    void showMaxWindow_slot(void);
    void closeWindow_slot(void);
signals:
    void mouseEnter_signal(void);
    void mouseLeave_signal(void);
private:
	Ui::CTitleBarClass ui;
    QLabel* m_label_TitleIcon = nullptr;        //标题栏图标
    QLineEdit* m_ledit_Search = nullptr;        //搜索框
    QAction* m_act_Search = nullptr;            //搜索按钮
    QPushButton* m_pbtn_Skin = nullptr;         //皮肤壁纸
    QPushButton* m_pbtn_Email = nullptr;        //通知
    QPushButton* m_pbtn_Setting = nullptr;      //设置
    QPushButton* m_pbtn_UserIcon = nullptr;     //用户头像
    QPushButton* m_pbtn_UserName = nullptr;     //用户昵称
    QLabel* m_label_Split = nullptr;            //分割线
    QPushButton* m_pbtn_Hide = nullptr;         //隐藏
    QPushButton* m_pbtn_Minimum = nullptr;      //最小化
    QPushButton* m_pbtn_Maximum = nullptr;      //最大化
    QPushButton* m_pbtn_CloseWid = nullptr;     //关闭窗口
    QHBoxLayout* m_hlay_Main = nullptr;
    QWidget* m_wid_Parent = nullptr;
};
