#include "ClickableLabel.h"
#include <QDebug>

ClickableLabel::ClickableLabel(const QString& text, QWidget* parent)
    : QLabel(parent)
{
    setText(text);
      qDebug()<<"verification signal click";
}

ClickableLabel::~ClickableLabel()
{

}
void ClickableLabel::mousePressEvent(QMouseEvent* event)
{
    qDebug()<<"verification signal";
    if(event->button() == Qt::LeftButton)
        {

        }
        QLabel::mousePressEvent(event);//将该事件传给父类处理
}
