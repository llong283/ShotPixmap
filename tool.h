#ifndef TOOL_H
#define TOOL_H

#include <QWidget>

namespace Ui {
    class Tool;
}

class Tool : public QWidget
{
    Q_OBJECT

public:
    explicit Tool(QWidget *parent = 0);
    ~Tool();

private:
    Ui::Tool *ui;

signals:
    void signDoneClick();
    void signSaveClick();
    void signDrawClick();
    void signClearClick();
    void signWriteClick();

private slots:

};

#endif // TOOL_H
