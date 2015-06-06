#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <iostream>
#include <fstream>
#include <QTextStream>
#include <Engines/translator.h>
#include <Engines/parser.h>

using namespace std;

static QString fileName;
static QList<GCommand> gCommands;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::FillGCodeEditor()
{
    ui -> txtEditorGCode->clear();

    foreach (GCommand command, gCommands)
        ui->txtEditorGCode->append(command.Value);

    ui->btnTranslate->setEnabled(true);
    ui->btnClear->setEnabled(true);
}

void MainWindow::on_btnOpen_clicked()
{
    fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("Files (.)"));

    if(fileName.length() > 0)
    {
        QFile file(fileName);
        if(file.open(QIODevice::ReadOnly))
        {
            QTextStream in(&file);
            QList<QString> buffer;

            while(!in.atEnd())
                buffer.push_back(in.readLine());
            file.close();

            Parser::Instance().Parse(buffer, &gCommands);
            FillGCodeEditor();
        }
    }

}

void MainWindow::on_btnClear_clicked()
{
    ui->txtEditorGCode->clear();
    ui->btnTranslate->setEnabled(false);
}

void MainWindow::on_txtEditorGCode_textChanged()
{
    bool enable = ui->txtEditorGCode->toPlainText().length() > 0;

    ui->btnClear->setEnabled(enable);
    ui->btnTranslate->setEnabled(enable);
}

void MainWindow::on_btnTranslate_clicked()
{
    //odavde se pozove Translate
    //dobijeni rezultat se prebaci u txtEditorVAX
    //za sada prebacimo cist text i enable dugmica za play i ostalo

    ui->txtEditorVAXCode->clear();
    ui->txtEditorVAXCode->append(ui->txtEditorGCode->toPlainText());

    ui->btnTranslate->setEnabled(false);
    ui->btnNext->setEnabled(true);
    ui->btnPlay->setEnabled(true);
}
