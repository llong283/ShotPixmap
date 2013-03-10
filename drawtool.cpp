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
//    case "��ɫ":
//        color = Qt::red;
//        break;
//    case "��ɫ":
//        color = Qt::black;
//        break;
//    case "��ɫ":
//        color = Qt::white;
//        break;
//    case "��ɫ":
//        color = Qt::blue;
//        break;
//    case "��ɫ":
//        color = Qt::yellow;
//        break;
//    default:
//        color = Qt::red;
//    }

//    emit signDrawToolChange(ui->comboShape->currentText(),
//                            ui->comboSize->currentText().toInt(),
//                            color);
}
