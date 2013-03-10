#include "tool.h"
#include "ui_tool.h"

Tool::Tool(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Tool)
{
    ui->setupUi(this);

    connect(ui->pushClear, SIGNAL(clicked()), this, SIGNAL(signClearClick()));
    connect(ui->pushDone, SIGNAL(clicked()), this, SIGNAL(signDoneClick()));
    connect(ui->pushDraw, SIGNAL(clicked()), this, SIGNAL(signDrawClick()));
    connect(ui->pushSave, SIGNAL(clicked()), this, SIGNAL(signSaveClick()));
    connect(ui->pushWrite, SIGNAL(clicked()), this, SIGNAL(signWriteClick()));
}

Tool::~Tool()
{
    delete ui;
}
