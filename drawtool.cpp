#include "drawtool.h"
#include "ui_drawtool.h"

DrawTool::DrawTool(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DrawTool)
{
    ui->setupUi(this);

    connect(ui->comboShape, SIGNAL(currentIndexChanged(QString)), this, SLOT(slotDrawToolChange()));
}

DrawTool::~DrawTool()
{
    delete ui;
}

void DrawTool::slotDrawToolChange()
{
//    QColor color;
//    switch (ui->comboColor->currentText()) {
//    case "红色":
//        color = Qt::red;
//        break;
//    case "黑色":
//        color = Qt::black;
//        break;
//    case "白色":
//        color = Qt::white;
//        break;
//    case "蓝色":
//        color = Qt::blue;
//        break;
//    case "黄色":
//        color = Qt::yellow;
//        break;
//    default:
//        color = Qt::red;
//    }

//    emit signDrawToolChange(ui->comboShape->currentText(),
//                            ui->comboSize->currentText().toInt(),
//                            color);
}
