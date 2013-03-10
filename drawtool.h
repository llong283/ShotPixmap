#ifndef DRAWTOOL_H
#define DRAWTOOL_H

#include <QWidget>

namespace Ui {
    class DrawTool;
}

class DrawTool : public QWidget
{
    Q_OBJECT

public:
    explicit DrawTool(QWidget *parent = 0);
    ~DrawTool();

signals:
    void signDrawToolChange(QString shape, int size, QColor color);

private slots:
    void slotDrawToolChange();

private:
    Ui::DrawTool *ui;
};

#endif // DRAWTOOL_H
