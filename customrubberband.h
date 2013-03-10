#ifndef CUSTOMRUBBERBAND_H
#define CUSTOMRUBBERBAND_H

#include <QRubberBand>
#include <QtGui>
#include <QtCore>

class CustomRubberBand : public QRubberBand
{
    Q_OBJECT
public:
//    explicit CustomRubberBand(QWidget *parent = 0);
    CustomRubberBand(QRubberBand::Shape s, QWidget * p = 0 ) :
            QRubberBand(s, p) {}

//    void keyPressEvent(QKeyEvent *ev);

signals:

public slots:

};

#endif // CUSTOMRUBBERBAND_H
