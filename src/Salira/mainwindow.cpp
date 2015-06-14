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
static QList<VAXCommand> vaxCommands;
static int currentCommandNumber;

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

    if(gCommands.size() == 0)
        return;

    QString buffer;
    int i = 0;
    foreach (GCommand command, gCommands)
    {
        if(i == currentCommandNumber)
            buffer += "<font color=\"red\">" + command.ToString() + "</font><br>";
        else
            buffer += command.ToString() + "<br>";
        i++;
    }


    ui->txtEditorGCode->setHtml(buffer);
    ui->btnTranslate->setEnabled(true);
    ui->btnClear->setEnabled(true);
}

void MainWindow::FillVAXCodeEditor()
{
    ui -> txtEditorVAXCode->clear();

    if(vaxCommands.size() == 0)
        return;

    foreach (VAXCommand command, vaxCommands)
        ui->txtEditorVAXCode->append(command.ToString());

    ui->btnPlay->setEnabled(true);
    ui->btnNext->setEnabled(true);
}

void MainWindow::on_btnOpen_clicked()
{
    fileName = QFileDialog::getOpenFileName (this, tr("Open File"), fileName, tr("Files (.)"));

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

            if(Parser::Instance().Parse(buffer, &gCommands))
                FillGCodeEditor();
        }
    }

}

void MainWindow::on_btnClear_clicked()
{
    ui->txtEditorGCode->clear();
    ui->txtEditorVAXCode->clear();
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
    if(Translator::Instance().Translate(gCommands, &vaxCommands))
        FillVAXCodeEditor();

    currentCommandNumber = 0;
}

void MainWindow::on_btnPlay_clicked()
{

}

void MainWindow::on_btnNext_clicked()
{
    currentCommandNumber++;
    this->FillGCodeEditor();
}

void MainWindow::on_btnPrevious_clicked()
{
    currentCommandNumber--;
    this->FillGCodeEditor();
}

void MainWindow::on_btnRestart_clicked()
{
    currentCommandNumber = 0;
    this->FillGCodeEditor();
}
