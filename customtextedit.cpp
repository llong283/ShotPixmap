#include "customtextedit.h"
#include <QDebug>

CustomTextEdit::CustomTextEdit(QWidget *parent) :
    QTextEdit(parent)
{
}
void CustomTextEdit::focusOutEvent(QFocusEvent *e)
{
//    qDebug() << "CustomTextEdit::focusOutEvent" << __FILE__ << __LINE__;
    emit signFocusOut();
    QTextEdit::focusOutEvent(e);
}
