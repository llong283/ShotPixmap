#ifndef CUSTOMLABEL_H
#define CUSTOMLABEL_H

#include <QLabel>
#include <QtGui>
#include <QtCore>

class CustomLabel : public QLabel
{
    Q_OBJECT
public:
    //methods
    explicit CustomLabel(QWidget *parent = 0);
    void keyPressEvent(QKeyEvent *ev);
    void paintEvent(QPaintEvent *);
    void resizeEvent(QResizeEvent *);
    void mousePressEvent(QMouseEvent *ev);
    void mouseReleaseEvent(QMouseEvent *ev);
    void mouseMoveEvent(QMouseEvent *ev);
    void mouseDoubleClickEvent(QMouseEvent *);
    void SetIsPmInit(bool flag);
    void SetIsPaint(bool flag);
    void SetIsDrawing(bool flag);
    void SetIsWrite(bool flag);
    void SetIsFocusOut(bool flag);

    //members

private:
    QPixmap pm;
    QPixmap tempPm;
    QPoint org;
    QPoint dst;
    QPoint writePos;
    bool isDrawing;
    bool isPmInit;
    bool isPaint;
    bool isWrite;
    bool isFocusOut;
    QTextEdit *edit;

signals:
    void changed();
    void signClosed();
    void signDoubleClick();

public slots:
    void slotTextChanged();
    void slotFocusOut();
};

#endif // CUSTOMLABEL_H
