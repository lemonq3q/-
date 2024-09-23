#include "mdiaolog.h"
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>

MDiaolog::MDiaolog(QString showText, QString buttonText, int width, int height)
{
    this->setFixedSize(width,height);
    this->setStyleSheet("background-color:#B99A74;border: 2px solid #6B4C2B;");
    this->setWindowFlags(Qt::FramelessWindowHint);

    QPushButton *bt = new QPushButton(buttonText, this);
    bt->setFixedSize(100,30);
    bt->setStyleSheet("background-color:#6B4C2B;color:#F1E8D6;font-size: 16px;");
    QLabel *label = new QLabel(showText,this);
    label->setFont(QFont("Helvetica", 12));
    label->setStyleSheet("color:#6B4C2B;font-size: 20px;font-weight: bold;border: 2px solid #B99A74;");
    QVBoxLayout *vLayout = new QVBoxLayout(this);

    label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);   //设置文字水平垂直居中
    vLayout->addWidget(label);
    vLayout->addWidget(bt);
    vLayout->setAlignment(Qt::AlignHCenter);

    connect(bt,&QPushButton::clicked,this,&MDiaolog::accept);
}

void MDiaolog::accept()
{
    QDialog::accept();   //关闭窗口顺便发送窗口关闭的信号
    emit diaologClose();
}
