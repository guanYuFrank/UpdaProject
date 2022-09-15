#include "mainproject.h"
#include "ui_mainproject.h"

MainProject::MainProject(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainProject)
{
    ui->setupUi(this);
}

MainProject::~MainProject()
{
    delete ui;
}
