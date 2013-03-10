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

    //托盘所有控件***************************************************************
    QSystemTrayIcon *trayIcon;
    QMenu *menu;
    QAction *restore;
    QAction *mini;
    QAction *quit;
    //托盘所有控件***************************************************************

    //存放全屏截图和用户选择截图的控件
    CustomLabel *fullScreenLabel;
    CustomLabel *shotScreenLabel;

    //用户截图后点击鼠标右键的上下文，用以保存截图
    QAction *savePixmap;

    //用户选择的初始坐标和终止坐标
    QPoint origin;
    QPoint termination;

    //用户点击截屏按钮时截取的全屏信息
    QPixmap fullScreenPixmap;

    //鼠标左键按下标志位
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
