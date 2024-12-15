#include "CustomWindowFrame.h"

CustomWindowFrame::CustomWindowFrame(QWidget *parent)
    : QFrame(parent)
{
    ui.setupUi(this);
    initCustomWindowFrame();
    connectSignalSlot();
}

CustomWindowFrame::~CustomWindowFrame()
{}

void CustomWindowFrame::initCustomWindowFrame(void)
{
    m_TitleBar = new CTitleBar(this);
    m_wid_CentralWidget = new QWidget(this);
    m_vlay_CentralWidget = new QVBoxLayout(m_wid_CentralWidget);
    m_vlay_Main = new QVBoxLayout(this);

    m_TitleBar->setObjectName("m_TitleBar");
    m_wid_CentralWidget->setObjectName("m_wid_CentralWidget");
    m_vlay_Main->addWidget(m_TitleBar);
    m_vlay_Main->addWidget(m_wid_CentralWidget);
    m_vlay_Main->setSpacing(0);
    m_vlay_Main->setContentsMargins(QMargins(0, 0, 0, 0));
    m_vlay_CentralWidget->setSpacing(0);
    m_vlay_CentralWidget->setContentsMargins(QMargins(0, 0, 0, 0));
    setObjectName("CustomWindowFrame");

    setWindowFlags(Qt::FramelessWindowHint);
    setMouseTracking(true);
    setCursor(Qt::ArrowCursor);
    setAttribute(Qt::WA_Hover, true);//ǿ��Qt����������뿪С����ʱ���ɻ����¼����������ͨ����ʵ���Զ�����ʽʱʹ�ã�
    setAttribute(Qt::WA_StyledBackground, true);//��������ã�qss��QWidget����ʽ������Ч
    setAttribute(Qt::WA_TranslucentBackground);//����͸����������������ʽԲ��ʱ���������ص�ԭ����ֱ��
}

void CustomWindowFrame::connectSignalSlot(void)
{
    connect(m_TitleBar, &CTitleBar::mouseEnter_signal, this, [&]() { m_bMoveWindow = true; });
    connect(m_TitleBar, &CTitleBar::mouseLeave_signal, this, [&]() { m_bMoveWindow = false; });
}

CursorPos CustomWindowFrame::calculateMousePos(const QPoint Point)
{
    CursorPos cursorPos;
    if (Point.x() < m_Border && Point.y() < m_Border) {
        cursorPos = CursorPos::TopLeft;
    }
    else if (Point.x() >= (width() - m_Border) && Point.y() >= (height() - m_Border)) {
        cursorPos = CursorPos::BottomRight;
    }
    else if (Point.x() >= (width() - m_Border) && Point.y() < m_Border) {
        cursorPos = CursorPos::TopRight;
    }
    else if (Point.x() < m_Border && Point.y() >= (height() - m_Border)) {
        cursorPos = CursorPos::BottomLeft;
    }
    else if (Point.x() < m_Border) {
        cursorPos = CursorPos::Left;
    }
    else if (Point.x() >= (width() - m_Border)) {
        cursorPos = CursorPos::Right;
    }
    else if (Point.y() < m_Border) {
        cursorPos = CursorPos::Top;
    }
    else if (Point.y() >= (height() - m_Border)) {
        cursorPos = CursorPos::Bottom;
    }
    else {
        cursorPos = CursorPos::Default;
    }
    return cursorPos;
}

void CustomWindowFrame::changeCursorShape(const CursorPos Type)
{
    switch (Type) {
    case CursorPos::Top:
    case CursorPos::Bottom:
        setCursor(Qt::SizeVerCursor);
        break;
    case CursorPos::Left:
    case CursorPos::Right:
        setCursor(Qt::SizeHorCursor);
        break;
    case CursorPos::TopLeft:
    case CursorPos::BottomRight:
        setCursor(Qt::SizeFDiagCursor);
        break;
    case CursorPos::TopRight:
    case CursorPos::BottomLeft:
        setCursor(Qt::SizeBDiagCursor);
        break;
    default:
        setCursor(Qt::ArrowCursor);
        break;
    }
}

bool CustomWindowFrame::event(QEvent* event)
{
    switch (event->type()) {
    case QEvent::HoverMove: {
        QHoverEvent* HoverEvent = (QHoverEvent*)event;
        m_CursorPos = calculateMousePos(HoverEvent->pos());
        changeCursorShape(m_CursorPos);
        return true;
    }
    case QEvent::TouchBegin:
        /* Touch begin event for tocuch screen */
        // resizeMoveWindow(static_cast<QTouchEvent *>(event)->pos().first().position());
        // resizeMoveWindow(event->pos());
        return true;
    case QEvent::TouchUpdate:
        /* Touch update event for tocuch screen */
        // resizeMoveWindow(static_cast<QTouchEvent *>(event)->pos().first().position());
        return true;
    case QEvent::TouchEnd:
        /* Touch end event for tocuch screen */
        return true;
    default:
        return QWidget::event(event);
    }
}

void CustomWindowFrame::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton) {
        m_bMousePressed = true;
        m_pot_MousePos = mapToGlobal(event->pos());
        m_rect_WindowPos = frameGeometry();

        switch (m_CursorPos)
        {
        case CursorPos::Default:
            if (m_bMoveWindow) {
                m_MouseOpt = MouseOpt::MoveWindow;
            }
            else {
                m_MouseOpt = MouseOpt::Default;
            }
            break;
        case CursorPos::Top:
            m_MouseOpt = MouseOpt::MoveTop;
            break;
        case CursorPos::TopRight:
            m_MouseOpt = MouseOpt::MoveTopRight;
            break;
        case CursorPos::Right:
            m_MouseOpt = MouseOpt::MoveRight;
            break;
        case CursorPos::BottomRight:
            m_MouseOpt = MouseOpt::MoveBottomRight;
            break;
        case CursorPos::Bottom:
            m_MouseOpt = MouseOpt::MoveBottom;
            break;
        case CursorPos::BottomLeft:
            m_MouseOpt = MouseOpt::MoveBottomLeft;
            break;
        case CursorPos::Left:
            m_MouseOpt = MouseOpt::MoveLeft;
            break;
        case CursorPos::TopLeft:
            m_MouseOpt = MouseOpt::MoveTopLeft;
            break;
        default:
            break;
        }
    }
}

void CustomWindowFrame::mouseReleaseEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton) {
        m_bMousePressed = false;
        m_MouseOpt = MouseOpt::Default;
    }
}

void CustomWindowFrame::mouseMoveEvent(QMouseEvent* event)
{
    QPoint CurMousePos = mapToGlobal(event->pos());
    int nX = 0;
    int nY = 0;
    int nWidth = 0;
    int nHeight = 0;
    switch (m_MouseOpt)
    {
    case MouseOpt::MoveTop:
        nX = m_rect_WindowPos.x();
        nY = CurMousePos.y() > (m_rect_WindowPos.y() + m_rect_WindowPos.height() - minimumHeight()) ? (m_rect_WindowPos.y() + m_rect_WindowPos.height() - minimumHeight()) : CurMousePos.y();
        nWidth = m_rect_WindowPos.width();
        nHeight = m_rect_WindowPos.height() - (nY - m_rect_WindowPos.y());
        setGeometry(nX, nY, nWidth, nHeight);
        break;
    case MouseOpt::MoveTopRight:
        nX = m_rect_WindowPos.x();
        nY = CurMousePos.y() > (m_rect_WindowPos.y() + m_rect_WindowPos.height() - minimumHeight()) ? (m_rect_WindowPos.y() + m_rect_WindowPos.height() - minimumHeight()) : CurMousePos.y();
        nWidth = CurMousePos.x() > (m_rect_WindowPos.x() + minimumWidth()) ? (CurMousePos.x() - m_rect_WindowPos.x()) : minimumWidth();
        nHeight = m_rect_WindowPos.height() - (nY - m_rect_WindowPos.y());
        setGeometry(nX, nY, nWidth, nHeight);
        break;
    case MouseOpt::MoveRight:
        nX = m_rect_WindowPos.x();
        nY = m_rect_WindowPos.y();
        nWidth = CurMousePos.x() > (m_rect_WindowPos.x() + minimumWidth()) ? (CurMousePos.x() - m_rect_WindowPos.x()) : minimumWidth();
        nHeight = m_rect_WindowPos.height();
        setGeometry(nX, nY, nWidth, nHeight);
        break;
    case MouseOpt::MoveBottomRight:
        nX = m_rect_WindowPos.x();
        nY = m_rect_WindowPos.y();
        nWidth = CurMousePos.x() > (m_rect_WindowPos.x() + minimumWidth()) ? (CurMousePos.x() - m_rect_WindowPos.x()) : minimumWidth();
        nHeight = CurMousePos.y() > (m_rect_WindowPos.y() + minimumHeight()) ? (CurMousePos.y() - m_rect_WindowPos.y()) : minimumHeight();
        setGeometry(nX, nY, nWidth, nHeight);
        break;
    case MouseOpt::MoveBottom:
        nX = m_rect_WindowPos.x();
        nY = m_rect_WindowPos.y();
        nWidth = m_rect_WindowPos.width();
        nHeight = CurMousePos.y() > (m_rect_WindowPos.y() + minimumHeight()) ? (CurMousePos.y() - m_rect_WindowPos.y()) : minimumHeight();
        setGeometry(nX, nY, nWidth, nHeight);
        break;
    case MouseOpt::MoveBottomLeft:
        nX = CurMousePos.x() > (m_rect_WindowPos.x() + m_rect_WindowPos.width() - minimumWidth()) ? (m_rect_WindowPos.x() + m_rect_WindowPos.width() - minimumWidth()) : CurMousePos.x();
        nY = m_rect_WindowPos.y();
        nWidth = m_rect_WindowPos.width() - (nX - m_rect_WindowPos.x());
        nHeight = CurMousePos.y() > (m_rect_WindowPos.y() + minimumHeight()) ? (CurMousePos.y() - m_rect_WindowPos.y()) : minimumHeight();
        setGeometry(nX, nY, nWidth, nHeight);
        break;
    case MouseOpt::MoveLeft:
        nX = CurMousePos.x() > (m_rect_WindowPos.x() + m_rect_WindowPos.width() - minimumWidth()) ? (m_rect_WindowPos.x() + m_rect_WindowPos.width() - minimumWidth()) : CurMousePos.x();
        nY = m_rect_WindowPos.y();
        nWidth = m_rect_WindowPos.width() - (nX - m_rect_WindowPos.x());
        nHeight = m_rect_WindowPos.height();
        setGeometry(nX, nY, nWidth, nHeight);
        break;
    case MouseOpt::MoveTopLeft:
        nX = CurMousePos.x() > (m_rect_WindowPos.x() + m_rect_WindowPos.width() - minimumWidth()) ? (m_rect_WindowPos.x() + m_rect_WindowPos.width() - minimumWidth()) : CurMousePos.x();
        nY = CurMousePos.y() > (m_rect_WindowPos.y() + m_rect_WindowPos.height() - minimumHeight()) ? (m_rect_WindowPos.y() + m_rect_WindowPos.height() - minimumHeight()) : CurMousePos.y();
        nWidth = m_rect_WindowPos.width() - (nX - m_rect_WindowPos.x());
        nHeight = m_rect_WindowPos.height() - (nY - m_rect_WindowPos.y());
        setGeometry(nX, nY, nWidth, nHeight);
        break;
    case MouseOpt::MoveWindow:
        if (isMaximized()) {
            int nMaxWidth = this->width();
            showNormal();
            update();
            int nWidth = this->width();
            //��Ҫ����һ�»ָ�֮��Ĵ��ں����λ��֮���ƫ��
            //���������ȫ�����ڵ�λ�ã��ȱ������ţ���������ڻָ���Ĵ��ڵ�λ�ã�����������ָ���Ĵ���λ��
            // nWidth / nMaxWidth = x / CurMousePos.x()
            int nWidPosX = nWidth / nMaxWidth * CurMousePos.x();
            mapToGlobal(QPoint(nWidPosX, CurMousePos.y())).x() - nWidPosX;
            move(mapToGlobal(QPoint(nWidPosX, CurMousePos.y())).x() - nWidPosX, CurMousePos.y() - TITLEBAR_HEIGHT / 2);
            m_rect_WindowPos = frameGeometry();//���¼�¼�Ĵ���λ��
            //qDebug() << QString("############## window rect: (%1,%2,%3,%4)")
            //                    .arg(m_rect_WindowPos.x()).arg(m_rect_WindowPos.y()).arg(m_rect_WindowPos.width()).arg(m_rect_WindowPos.height());
        }
        else {
            move(m_rect_WindowPos.x() + (CurMousePos.x() - m_pot_MousePos.x()), m_rect_WindowPos.y() + (CurMousePos.y() - m_pot_MousePos.y()));
        }
        break;
    default:
        break;
    }
    updateGeometry();
}

void CustomWindowFrame::setCentralWidget(QWidget* widget)
{
    m_vlay_CentralWidget->addWidget(widget);
    update();
}
