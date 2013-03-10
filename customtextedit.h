#ifndef CUSTOMTEXTEDIT_H
#define CUSTOMTEXTEDIT_H

#include <QTextEdit>

class CustomTextEdit : public QTextEdit
{
    Q_OBJECT
public:
    explicit CustomTextEdit(QWidget *parent = 0);
    void focusOutEvent ( QFocusEvent * e );

signals:
    void signFocusOut();

public slots:

};

#endif // CUSTOMTEXTEDIT_H
