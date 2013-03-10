#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPixmap>
#include <QPoint>
#include "customlabel.h"
#include "customrubberband.h"
#include "qxtglobalshortcut.h"
#include "tool.h"

class QSystemTrayIcon;
class QMenu;
class QAction;

namespace Ui {
    class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

protected:
    virtual bool eventFilter(QObject *o, QEvent *e);

private:
    void createWidgets();
    void createConnects();
    void createEventFilter();

    QString getSaveShotPixmap();

private slots:
    void grapWindowScreen();
    void miniWindows();
    void restoreWindows();
    void quitApplication();
    void saveShotPixmap();

private:
    Ui::Widget *ui;

    //�������пؼ�***************************************************************
    QSystemTrayIcon *trayIcon;
    QMenu *menu;
    QAction *restore;
    QAction *mini;
    QAction *quit;
    //�������пؼ�***************************************************************

    //���ȫ����ͼ���û�ѡ���ͼ�Ŀؼ�
    CustomLabel *fullScreenLabel;
    CustomLabel *shotScreenLabel;

    //�û���ͼ��������Ҽ��������ģ����Ա����ͼ
    QAction *savePixmap;

    //�û�ѡ��ĳ�ʼ�������ֹ����
    QPoint origin;
    QPoint termination;

    //�û����������ťʱ��ȡ��ȫ����Ϣ
    QPixmap fullScreenPixmap;

    //���������±�־λ
    bool leftMousePress;

    //members
    QAction *copyPixmap;
    QTime t;
    QAction *shot;
    QShortcut *shortCut;
    QxtGlobalShortcut * sc;
    Tool *tool;
    QPixmap shotScreenPixmap;
    bool bComplete;
    bool bIsShotLabelFix;

    //methods

private slots:
    void slotChanged();
    void slotCopyPixmap();
    void slotDraw();
    void slotClose();
    void slotClear();
    void slotWrite();
};

#endif // WIDGET_H
