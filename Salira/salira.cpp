#include "salira.h"
#include "ui_salira.h"

Salira::Salira(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Salira)
{
    ui->setupUi(this);
}

Salira::~Salira()
{
    delete ui;
}
