#include "customlabel.h"
#include "customtextedit.h"
#include <QDebug>

CustomLabel::CustomLabel(QWidget *parent) :
    QLabel(parent)
{
    isPaint = false;
    isDrawing = false;
    isPmInit = false;
    isWrite = false;
    isFocusOut = false;

    QFont font("ËÎÌו", 12);
    QFontMetrics fm(font);
    edit = new CustomTextEdit(this);
    edit->setFont(QFont("ËÎÌו", 12));
    edit->resize(fm.maxWidth() * 2, fm.height() * 2);
    connect(edit, SIGNAL(textChanged()), this, SLOT(slotTextChanged()));
    connect(edit, SIGNAL(signFocusOut()), this, SLOT(slotFocusOut()));
    edit->hide();
}

void CustomLabel::keyPressEvent(QKeyEvent *e)
{
    qDebug() << "CustomLabel::keyPressEvent" << QString("0x%1").arg(e->key(), 0, 16) << __FILE__ << __LINE__;
    switch(e->key()) {
    case Qt::Key_Escape:
        qDebug() << "Qt::Key_Escape" << __FILE__ << __LINE__;
        emit signClosed();
        break;
    default:
        QWidget::keyPressEvent(e);
    }
}

void CustomLabel::paintEvent(QPaintEvent *e)
{
    if (isPaint && !isPmInit && this->pixmap()) {
        qDebug() << "CustomLabel::paintEvent" << __FILE__ << __LINE__;

        pm = this->pixmap()->copy(this->pixmap()->rect());
        isPmInit = true;
    }
    QLabel::paintEvent(e);
}

void CustomLabel::mouseDoubleClickEvent(QMouseEvent *)
{
    emit signDoubleClick();
}

void CustomLabel::mousePressEvent(QMouseEvent *ev)
{
    if (!isPaint)
        return;
    else
        org = ev->pos();

    QFontMetrics fm(edit->font());

    if (isWrite && !isFocusOut) {
        qDebug() << "CustomLabel::mousePressEvent" << __FILE__ << __LINE__;

        writePos = ev->pos();
        edit->move(ev->pos().x() - fm.maxWidth() / 4.0,
                   ev->pos().y() - fm.height());
        edit->setFocus();
        edit->show();
        isFocusOut = true;
    }
    else if (isWrite && isFocusOut) {
        qDebug() << "CustomLabel::mousePressEvent" << __FILE__ << __LINE__;

        QPainter p(&pm);
        QPen pen(Qt::red, 2);
        QRect rect;

        rect = QRect(edit->geometry().x(),
                     edit->geometry().y(),
                     edit->geometry().width() - fm.maxWidth(),
                     edit->geometry().height());
        p.setPen(pen);
        p.setFont(edit->font());
        p.drawText(rect, Qt::AlignCenter, edit->toPlainText());
        this->setPixmap(pm);
        edit->setText("");
        edit->hide();
        isFocusOut = false;
    }
}

void CustomLabel::mouseReleaseEvent(QMouseEvent *ev)
{
    if (!isPaint || isWrite)
        return;
    dst = ev->pos();
    if (dst == org)
        return;
    QPainter p(&pm);
    QPen pen(Qt::red, 3);
    p.setPen(pen);
//    p.drawLine(org, dst);
    p.drawRect(QRect(org, dst));
    p.drawPixmap(0, 0, pm);
    this->setPixmap(pm);
}

void CustomLabel::mouseMoveEvent(QMouseEvent *ev)
{
    if (!isPaint || isWrite)
        return;
    tempPm = pm;
    QPainter p(&tempPm);
    QPen pen(Qt::red, 3);
    p.setPen(pen);
//    p.drawLine(org, ev->pos());
    p.drawRect(QRect(org, ev->pos()));
    p.drawPixmap(0, 0, tempPm);
    this->setPixmap(tempPm);
}

void CustomLabel::resizeEvent(QResizeEvent *e)
{
    emit changed();
}

void CustomLabel::SetIsDrawing(bool flag)
{
    isDrawing = flag;
}

void CustomLabel::SetIsPaint(bool flag)
{
    isPaint = flag;
}

void CustomLabel::SetIsPmInit(bool flag)
{
    isPmInit = flag;
}

void CustomLabel::SetIsWrite(bool flag)
{
    isWrite = flag;
}

void CustomLabel::SetIsFocusOut(bool flag)
{
    isFocusOut = flag;
}

void CustomLabel::slotTextChanged()
{
//    QFont font("ËÎÌו", 12);
//    edit->setFont(font);
    QFontMetrics fm(edit->font());
    edit->resize(fm.width(edit->toPlainText()) + fm.maxWidth() * 2, fm.height() * 2);
//    edit->resize(fm.width(edit->toPlainText()) + 10, fm.height() + 15);
}

void CustomLabel::slotFocusOut()
{
    isFocusOut = true;
}
