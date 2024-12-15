#include "CTitleBar.h"

CTitleBar::CTitleBar(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
    m_wid_Parent = parent;
	initTitleBar();
	connectSignalSlot();
}

CTitleBar::~CTitleBar()
{}

void CTitleBar::initTitleBar(void)
{
    m_label_TitleIcon = new QLabel(this);//标题栏图标
    m_ledit_Search = new QLineEdit(this);//搜索框
    m_act_Search = new QAction(this);//搜索按钮
    m_pbtn_Skin = new QPushButton(this);//皮肤壁纸
    m_pbtn_Email = new QPushButton(this);//通知
    m_pbtn_Setting = new QPushButton(this);//设置
    m_pbtn_UserIcon = new QPushButton(this);//用户头像
    m_pbtn_UserName = new QPushButton(this);//用户昵称
    m_label_Split = new QLabel(this);//分割线
    m_pbtn_Hide = new QPushButton(this);//隐藏
    m_pbtn_Minimum = new QPushButton(this);//最小化
    m_pbtn_Maximum = new QPushButton(this);//最大化
    m_pbtn_CloseWid = new QPushButton(this);//关闭窗口
    m_hlay_Main = new QHBoxLayout();

    m_label_TitleIcon->setObjectName("m_label_TitleIcon");
    //m_label_TitleIcon->setText(QString::fromLocal8Bit("COSER社区"));
    //m_label_TitleIcon->setScaledContents(true);	//设置图片自适应标签大小
    m_label_TitleIcon->setCursor(Qt::PointingHandCursor);//鼠标悬停时的形状

    m_ledit_Search->setObjectName("m_ledit_Search");
    m_ledit_Search->setPlaceholderText(QStringLiteral("请输入关键词..."));//默认文本
    m_act_Search->setObjectName("m_act_Search");
    m_act_Search->setToolTip(QStringLiteral("搜索"));
    m_act_Search->setIcon(QIcon(QString(":/image/titleBar/search.png")));
    m_ledit_Search->addAction(m_act_Search, QLineEdit::TrailingPosition);//添加到右侧

    m_pbtn_Skin->setObjectName("m_pbtn_Skin");
    m_pbtn_Skin->setToolTip(QStringLiteral("主题"));
    m_pbtn_Skin->setCursor(Qt::PointingHandCursor);

    m_pbtn_Email->setObjectName("m_pbtn_Email");
    m_pbtn_Email->setToolTip(QStringLiteral("通知"));
    m_pbtn_Email->setCursor(Qt::PointingHandCursor);

    m_pbtn_Setting->setObjectName("m_pbtn_Setting");
    m_pbtn_Setting->setToolTip(QStringLiteral("设置"));
    m_pbtn_Setting->setCursor(Qt::PointingHandCursor);

    m_pbtn_UserIcon->setObjectName("m_pbtn_UserIcon");
    m_pbtn_UserIcon->setCursor(Qt::PointingHandCursor);

    m_pbtn_UserName->setObjectName("m_pbtn_UserName");
    m_pbtn_UserName->setText(QStringLiteral("未登录"));
    m_pbtn_UserName->setToolTip(QStringLiteral("用户名"));
    m_pbtn_UserName->setCursor(Qt::PointingHandCursor);

    m_label_Split->setObjectName("m_label_Split");
    m_label_Split->setFixedHeight(25);

    m_pbtn_Hide->setObjectName("m_pbtn_Hide");
    m_pbtn_Hide->setToolTip(QStringLiteral("隐藏"));
    m_pbtn_Hide->setCursor(Qt::PointingHandCursor);

    m_pbtn_Minimum->setObjectName("m_pbtn_Minimum");
    m_pbtn_Minimum->setToolTip(QStringLiteral("最小化"));
    m_pbtn_Minimum->setCursor(Qt::PointingHandCursor);

    m_pbtn_Maximum->setObjectName("m_pbtn_Maximum");
    m_pbtn_Maximum->setCursor(Qt::PointingHandCursor);

    m_pbtn_CloseWid->setObjectName("m_pbtn_CloseWid");
    m_pbtn_CloseWid->setToolTip(QStringLiteral("关闭"));
    m_pbtn_CloseWid->setCursor(Qt::PointingHandCursor);

    QHBoxLayout* hlay_2 = new QHBoxLayout;
    hlay_2->setSpacing(0);
    hlay_2->addWidget(m_pbtn_Skin);
    hlay_2->addSpacing(20);
    hlay_2->addWidget(m_pbtn_Email);
    hlay_2->addSpacing(20);
    hlay_2->addWidget(m_pbtn_Setting);
    hlay_2->addSpacing(20);
    hlay_2->addWidget(m_pbtn_UserIcon);
    hlay_2->addWidget(m_pbtn_UserName);
    hlay_2->addSpacing(15);
    hlay_2->addWidget(m_label_Split);
    hlay_2->addSpacing(15);
    hlay_2->addWidget(m_pbtn_Hide);
    hlay_2->addSpacing(20);
    hlay_2->addWidget(m_pbtn_Minimum);
    hlay_2->addSpacing(20);
    hlay_2->addWidget(m_pbtn_Maximum);
    hlay_2->addSpacing(20);
    hlay_2->addWidget(m_pbtn_CloseWid);

    m_hlay_Main->setSpacing(0);
    m_hlay_Main->setContentsMargins(QMargins(10, 10, 10, 10));
    m_hlay_Main->addWidget(m_label_TitleIcon);
    m_hlay_Main->addStretch();//弹簧
    m_hlay_Main->addWidget(m_ledit_Search);
    m_hlay_Main->addStretch();//弹簧
    m_hlay_Main->addLayout(hlay_2);
    setLayout(m_hlay_Main);

    //窗口样式
    setAttribute(Qt::WA_StyledBackground, true);//如果不设置，qss对QWidget的样式不会生效
    setFixedHeight(TITLEBAR_HEIGHT);
    setMinimumWidth(TITLEBAR_WIDTH);
}

void CTitleBar::connectSignalSlot(void)
{
    connect(m_pbtn_Hide, &QPushButton::clicked, this, &CTitleBar::showMinWindow_slot);
    connect(m_pbtn_Minimum, &QPushButton::clicked, this, &CTitleBar::showMinWindow_slot);
    connect(m_pbtn_Maximum, &QPushButton::clicked, this, &CTitleBar::showMaxWindow_slot);
    connect(m_pbtn_CloseWid, &QPushButton::clicked, this, &CTitleBar::closeWindow_slot);
}

void CTitleBar::enterEvent(QEvent* event)
{
    emit mouseEnter_signal();
}

void CTitleBar::leaveEvent(QEvent* event)
{
    emit mouseLeave_signal();
}

void CTitleBar::mouseDoubleClickEvent(QMouseEvent* event)
{
    showMaxWindow_slot();
}

void CTitleBar::showMinWindow_slot(void)
{
    m_wid_Parent->showMinimized();
}

void CTitleBar::showMaxWindow_slot(void)
{
    if (m_wid_Parent->isMaximized()) {
        m_wid_Parent->showNormal();
    }
    else {
        m_wid_Parent->showMaximized();
    }
}

void CTitleBar::closeWindow_slot(void)
{
    m_wid_Parent->close();
}
