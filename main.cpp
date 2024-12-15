#include "CustomWindowFrame.h"
#include <QtWidgets/QApplication>
#include <QHBoxLayout>
#include <QTextEdit>
#include <QFile>
class CommonHelper
{
public:
    static void setStyle(const QString& style) {
        QFile qss(style);
        qss.open(QFile::ReadOnly);
        qApp->setStyleSheet(qss.readAll());
        qss.close();
    }
};

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // 加载QSS样式
    CommonHelper::setStyle("./style/default.qss");

    CustomWindowFrame w;
    //***********************************************************
    QWidget* widget = new QWidget();
    QTextEdit* text = new QTextEdit();
    QString str = QString::fromLocal8Bit("\n\n\n\n\nCentral widget\n\nCodeWangs的自定义标题栏窗口框架");
    text->setAlignment(Qt::AlignCenter);
    text->setStyleSheet("QTextEdit{border:none; text-align:center; font:20px;}");
    text->append(str);
    QHBoxLayout* hlay = new QHBoxLayout(widget);
    hlay->addWidget(text);
    w.setCentralWidget(widget);
    //***********************************************************
    w.show();

    return a.exec();
}
