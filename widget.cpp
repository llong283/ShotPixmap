#include "widget.h"
#include "ui_widget.h"
#include <QtGui>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    fullScreenLabel = NULL;
    shotScreenLabel = NULL;
    shortCut = NULL;
    sc = NULL;
    tool = NULL;

    createWidgets();
    createEventFilter();

    shotScreenLabel->hide();
    fullScreenLabel->hide();
    tool->hide();
    bComplete = false;
    bIsShotLabelFix = false;
    shotScreenLabel->SetIsPmInit(false);
    shotScreenLabel->SetIsDrawing(false);
    shotScreenLabel->SetIsPaint(false);
    shotScreenLabel->SetIsWrite(false);
    shotScreenLabel->SetIsFocusOut(false);
    showMinimized();
    this->setWindowFlags(Qt::Popup);
    this->hide();
    
    //test
    trayIcon->installEventFilter(this);
}

Widget::~Widget()
{
    quit = NULL;
    mini = NULL;
    restore = NULL;
    menu = NULL;
    trayIcon = NULL;

    delete shotScreenLabel;
    shotScreenLabel = NULL;
    delete fullScreenLabel;
    fullScreenLabel = NULL;
    delete tool;
    tool = NULL;

    delete ui;
}

bool Widget::eventFilter(QObject *o, QEvent *e)
{
    qDebug() << "eventFilter";            
    if (o == trayIcon) {
        qDebug() << "trayIcon";            
    }
    if (o != fullScreenLabel) {
        qDebug() << "not fullScreenLabel event";
        return Widget::eventFilter(o, e);
    }
    QMouseEvent *mouseEvent = static_cast<QMouseEvent*> (e);

    if (bComplete == true) {
        if (mouseEvent->button() == Qt::RightButton) {
            qDebug() << "RightButton" << __FILE__ << __LINE__;
//            fullScreenLabel->close();
//            shotScreenLabel->close();
//            tool->close();
            fullScreenLabel->hide();
            shotScreenLabel->hide();
            tool->hide();
            bComplete = false;
            return true;
        }
        else
            return QWidget::eventFilter(o, e);
    }

    //true 鼠标左键按下且按键还未弹起
    if ((mouseEvent->button() == Qt::LeftButton)
        && (mouseEvent->type() == QEvent::MouseButtonPress)) {
        qDebug() << "QEvent::MouseButtonPress"  << __FILE__ << __LINE__;
        //鼠标左键标志位按下
        leftMousePress = true;
        //获取鼠标点
        //            origin = mouseEvent->pos();
        //            shotScreenLabel->setGeometry(QRect(origin, QSize()));
        //            shotScreenLabel->show();
        //            if (mouseEvent->pos().x() < tool->geometry().width())
        //                tool->move(0, mouseEvent->pos().y());
        //            else
        //                tool->move(mouseEvent->pos().x() - tool->geometry().width(),
        //                           mouseEvent->pos().y());
        origin = mouseEvent->globalPos();
        shotScreenLabel->setGeometry(QRect(origin, QSize()));
        shotScreenLabel->show();
        if (mouseEvent->globalX() < tool->geometry().width())
            tool->move(0, mouseEvent->globalY());
        else
            tool->move(mouseEvent->globalX() - tool->geometry().width(),
                       mouseEvent->globalY());
        tool->show();
        return true;
    }

    //true 鼠标左键按下并拖动
    if ((mouseEvent->type() == QEvent::MouseMove)
        && (leftMousePress)) {
        //            shotScreenLabel->setGeometry(QRect(origin, mouseEvent->pos()).normalized());
        shotScreenLabel->setGeometry(QRect(origin, mouseEvent->globalPos()).normalized());
        shotScreenLabel->show();
        //        if (mouseEvent->pos().x() < tool->geometry().width())
        //            tool->move(0, mouseEvent->pos().y());
        //        else
        //            tool->move(mouseEvent->pos().x() - tool->geometry().width(),
        //                       mouseEvent->pos().y());
        //        tool->show();
        slotChanged();
        return true;
    }

    //鼠标左键松开
    if ((mouseEvent->button() == Qt::LeftButton)
        && (mouseEvent->type() == QEvent::MouseButtonRelease)) {
        qDebug() << "QEvent::MouseButtonRelease"  << __FILE__ << __LINE__;
        //鼠标标志位弹起
        leftMousePress = false;
        //获取橡皮筋框的终止坐标
        termination = mouseEvent->pos();
        QRect rect = QRect(origin, termination);
        //将shotScreenLabel的用户区大小固定为所截图片大小
        shotScreenLabel->setGeometry(rect);
        shotScreenLabel->show();
        //        if (mouseEvent->pos().x() < tool->geometry().width())
        //            tool->move(0, mouseEvent->pos().y());
        //        else
        //            tool->move(mouseEvent->pos().x() - tool->geometry().width(),
        //                       mouseEvent->pos().y());
        //        tool->show();
        slotChanged();
        bComplete = true;
        return true;
    }
    return false;
}

//descr：实例化控件
void Widget::createWidgets()
{
    //两个QLabel的父控件不能为this，否则截图信息会现在是主窗口中，无法正确显示
    fullScreenLabel = new CustomLabel();
    connect(fullScreenLabel, SIGNAL(signDoubleClick()), this, SLOT(slotCopyPixmap()));
    connect(fullScreenLabel, SIGNAL(signClosed()), fullScreenLabel, SLOT(hide()));

    shotScreenLabel = new CustomLabel();
//    shotScreenLabel->setStyleSheet("border: 1px solid blue");
    shotScreenLabel->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowStaysOnTopHint);
    shotScreenLabel->setCursor(Qt::SizeAllCursor);
    connect(shotScreenLabel, SIGNAL(changed()), this, SLOT(slotChanged()));
    connect(shotScreenLabel, SIGNAL(signDoubleClick()), this, SLOT(slotCopyPixmap()));
    connect(shotScreenLabel, SIGNAL(signClosed()), this, SLOT(slotClose()));
    savePixmap = new QAction(tr("save"), this);
    connect(savePixmap, SIGNAL(triggered()), this, SLOT(saveShotPixmap()));
    shotScreenLabel->addAction(savePixmap);
    copyPixmap = new QAction(tr("copy"), this);
    connect(copyPixmap, SIGNAL(triggered()), this, SLOT(slotCopyPixmap()));
    shotScreenLabel->addAction(copyPixmap);
    shotScreenLabel->setContextMenuPolicy(Qt::ActionsContextMenu);

    leftMousePress = false;

    //初始化托盘控件并组装**************************************************************
//    trayIcon = new QSystemTrayIcon(QIcon(tr(":/images/heart.svg")), this);
    trayIcon = new QSystemTrayIcon(QIcon(tr(":/images/icon.png")), this);
    menu = new QMenu(QApplication::desktop());
    shot = new QAction("shot(Ctrl+Alt+X)", this);
    shot->setShortcutContext(Qt::WindowShortcut);
    connect(shot, SIGNAL(triggered()), this, SLOT(grapWindowScreen()));
//    restore = new QAction(tr("Restore"), this);
//    mini = new QAction(tr("Mini"), this);
    quit = new QAction(tr("Quit"), this);
//    connect(restore, SIGNAL(triggered()), this, SLOT(restoreWindows()));
//    connect(mini, SIGNAL(triggered()), this, SLOT(miniWindows()));
    connect(quit, SIGNAL(triggered()), this, SLOT(quitApplication()));

    menu->addAction(shot);
//    menu->addAction(restore);
//    menu->addAction(mini);
    menu->addAction(quit);
    trayIcon->setContextMenu(menu);

    //将托盘显示
    trayIcon->show();

    connect(ui->pbtnShot, SIGNAL(clicked()), this, SLOT(grapWindowScreen()));
    connect(ui->pbtnShotAndMin, SIGNAL(clicked()), this, SLOT(miniWindows()));
    connect(ui->pbtnMin, SIGNAL(clicked()), this, SLOT(miniWindows()));

    tool = new Tool();
    tool->setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);
    connect(tool, SIGNAL(signDoneClick()), this, SLOT(slotCopyPixmap()));
    connect(tool, SIGNAL(signSaveClick()), this, SLOT(saveShotPixmap()));
    connect(tool, SIGNAL(signDrawClick()), this, SLOT(slotDraw()));
    connect(tool, SIGNAL(signClearClick()), this, SLOT(slotClear()));
    connect(tool, SIGNAL(signWriteClick()), this, SLOT(slotWrite()));

    sc = new QxtGlobalShortcut(QKeySequence("Ctrl+Alt+X"), this);
    connect(sc, SIGNAL(activated()),this, SLOT(miniWindows()));
}

void Widget::createEventFilter()
{
    fullScreenLabel->installEventFilter(this);
//    shotScreenLabel->installEventFilter(this);
}

QString Widget::getSaveShotPixmap()
{
    return QFileDialog::getSaveFileName(shotScreenLabel,
                                        tr("Open Image"),
                                        ".",
                                        tr("Image Files(*.JPG *.PNG)"));
}

void Widget::grapWindowScreen()
{
    QTime t;
    t.start();
    while(t.elapsed() < 10)
        QCoreApplication::processEvents();

    menu->hide();
    this->hide();

    bComplete = false;
    if (!fullScreenLabel)
    {
        fullScreenLabel = new CustomLabel();
    }

    //获取全屏截图fullScreenPixmap，并将其放入fullScreenLabel
    fullScreenPixmap = QPixmap::grabWindow(QApplication::desktop()->winId());
    fullScreenLabel->setPixmap(fullScreenPixmap);

    //label全屏显示
    fullScreenLabel->showFullScreen();

    shotScreenLabel->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowStaysOnTopHint);
    shotScreenLabel->setCursor(Qt::SizeAllCursor);
    shotScreenLabel->setFixedSize(QWIDGETSIZE_MAX, QWIDGETSIZE_MAX);
}

void Widget::miniWindows()
{
    showMinimized();
    grapWindowScreen();
}

void Widget::restoreWindows()
{
    showNormal();
}

void Widget::quitApplication()
{
    qApp->quit();
}

void Widget::saveShotPixmap()
{
    QString fileName;
    bool ret;

    fileName = getSaveShotPixmap();

    if (!fileName.isNull())
    {
//        fullScreenPixmap.save(fileName);
//        shotScreenPixmap.save(fileName);
        ret = shotScreenLabel->pixmap()->save(fileName);
        if (!ret)
            QMessageBox::information(this, "ShotPixmap", "保存文件失败！");
    }
//    shotScreenLabel->close();
//    tool->close();
//    fullScreenLabel->close();
    shotScreenLabel->hide();
    tool->hide();
    fullScreenLabel->hide();
}

void Widget::slotChanged()
{    
//    qDebug() << "Widget::slotChanged" << __FILE__ << __LINE__;
    if (!shotScreenLabel) {
        qDebug() << "!shotScreenLabel"  << __FILE__ << __LINE__;
    }

    if (!bIsShotLabelFix) {
        shotScreenPixmap = fullScreenPixmap.copy(shotScreenLabel->geometry());
        shotScreenLabel->setPixmap(shotScreenPixmap);
        shotScreenLabel->show();
    }
    if (shotScreenLabel->geometry().right() < tool->geometry().width())
        tool->move(0, shotScreenLabel->geometry().bottom() + 2);
    else
        tool->move(shotScreenLabel->geometry().right() - tool->geometry().width(),
                   shotScreenLabel->geometry().bottom() + 2);
    tool->show();
}

void Widget::slotCopyPixmap()
{
    qDebug() << "Widget::slotCopyPixmap"  << __FILE__ << __LINE__ << t.currentTime();
//    QApplication::clipboard()->setPixmap(shotScreenPixmap);
    QApplication::clipboard()->setPixmap(*shotScreenLabel->pixmap());
//    shotScreenLabel->close();
//    tool->close();
//    fullScreenLabel->close();
    shotScreenLabel->hide();
    tool->hide();
    fullScreenLabel->hide();
    bComplete = false;
    bIsShotLabelFix = false;
    shotScreenLabel->SetIsPmInit(false);
    shotScreenLabel->SetIsDrawing(false);
    shotScreenLabel->SetIsPaint(false);
    shotScreenLabel->SetIsWrite(false);
    shotScreenLabel->SetIsFocusOut(false);
}

void Widget::slotDraw()
{
    bIsShotLabelFix = true;
    shotScreenLabel->SetIsPaint(true);
    shotScreenLabel->SetIsPmInit(false);
    shotScreenLabel->SetIsWrite(false);
    shotScreenLabel->SetIsFocusOut(false);
    shotScreenLabel->setFixedSize(shotScreenLabel->size());
    shotScreenLabel->setCursor(Qt::CrossCursor);
}

void Widget::slotClose()
{
    shotScreenLabel->SetIsPmInit(false);
    shotScreenLabel->SetIsDrawing(false);
    shotScreenLabel->SetIsPaint(false);
    shotScreenLabel->SetIsWrite(false);
    shotScreenLabel->SetIsFocusOut(false);
//    shotScreenLabel->close();
//    tool->close();
//    fullScreenLabel->close();
    shotScreenLabel->hide();
    tool->hide();
    fullScreenLabel->hide();
    bComplete = false;
    bIsShotLabelFix = false;
}

void Widget::slotClear()
{
    qDebug() << "Widget::slotClear"  << __FILE__ << __LINE__;
    shotScreenLabel->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowStaysOnTopHint);
    shotScreenLabel->setFixedSize(QWIDGETSIZE_MAX, QWIDGETSIZE_MAX);
    shotScreenLabel->setCursor(Qt::SizeAllCursor);
    shotScreenPixmap = fullScreenPixmap.copy(shotScreenLabel->geometry());
    shotScreenLabel->setPixmap(shotScreenPixmap);
    shotScreenLabel->show();
    shotScreenLabel->SetIsPmInit(false);
    shotScreenLabel->SetIsDrawing(false);
    shotScreenLabel->SetIsPaint(false);
    shotScreenLabel->SetIsWrite(false);
    shotScreenLabel->SetIsFocusOut(false);
    bComplete = false;
    bIsShotLabelFix = false;
}

void Widget::slotWrite()
{
    qDebug() << "Widget::slotWrite"  << __FILE__ << __LINE__;
    shotScreenLabel->SetIsPaint(true);
    shotScreenLabel->SetIsWrite(true);
    shotScreenLabel->SetIsFocusOut(false);
    shotScreenLabel->setCursor(Qt::IBeamCursor);
}
