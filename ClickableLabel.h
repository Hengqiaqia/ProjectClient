#ifndef CLICKABLELABEL_H
#define CLICKABLELABEL_H

#include <QWidget>
#include <QLabel>
#include <QtGui>
#include <QMouseEvent>
#include <QDebug>

class ClickableLabel : public QLabel
{
    Q_OBJECT
public:
    explicit ClickableLabel( QWidget* parent=0 )
    {
        Q_UNUSED(parent);
    }
    explicit ClickableLabel( const QString& text="", QWidget* parent=0 );
    ~ClickableLabel();
signals:
//    void leclicked();
protected:
    void mousePressEvent(QMouseEvent* event);
};

#endif // CLICKABLELABEL_H
