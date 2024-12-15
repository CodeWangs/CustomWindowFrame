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

#define TITLEBAR_WIDTH 650 //�������� ��ò�ҪС�����ֵ�����пؼ�������ʾ����Сֵ
#define TITLEBAR_HEIGHT 50 //�������� ��ò�ҪС�����ֵ����Ӱ��ͷ������״

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
    QLabel* m_label_TitleIcon = nullptr;        //������ͼ��
    QLineEdit* m_ledit_Search = nullptr;        //������
    QAction* m_act_Search = nullptr;            //������ť
    QPushButton* m_pbtn_Skin = nullptr;         //Ƥ����ֽ
    QPushButton* m_pbtn_Email = nullptr;        //֪ͨ
    QPushButton* m_pbtn_Setting = nullptr;      //����
    QPushButton* m_pbtn_UserIcon = nullptr;     //�û�ͷ��
    QPushButton* m_pbtn_UserName = nullptr;     //�û��ǳ�
    QLabel* m_label_Split = nullptr;            //�ָ���
    QPushButton* m_pbtn_Hide = nullptr;         //����
    QPushButton* m_pbtn_Minimum = nullptr;      //��С��
    QPushButton* m_pbtn_Maximum = nullptr;      //���
    QPushButton* m_pbtn_CloseWid = nullptr;     //�رմ���
    QHBoxLayout* m_hlay_Main = nullptr;
    QWidget* m_wid_Parent = nullptr;
};
