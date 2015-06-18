#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <iostream>
#include <fstream>
#include <QTextStream>
#include <Engines/translator.h>
#include <Engines/parser.h>
#include <Engines/executor.h>
#include <unistd.h>
#include<QTime>

using namespace std;

static QString fileName;
static QList<GCommand> gCommands;
static QList<VAXCommand> vaxCommands;
static bool _stopped;

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
    int i = 0, currentCommandNumber = Executor::Instance().currentState().id() - 1;
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
            {
                FillGCodeEditor();
                Executor::Instance().Init(gCommands);
                ui->btnPlay->setEnabled(true);
                ui->btnNext->setEnabled(true);
            }
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
}

void MainWindow::on_btnPlay_clicked()
{
    _stopped = false;
    ui->btnStop->setEnabled(true);
    ui->btnPrevious->setEnabled(false);
    ui->btnNext->setEnabled(false);
    ui->btnPlay->setEnabled(false);
    ui->btnRestart->setEnabled(false);

    while(Executor::Instance().currentState().id() < State::maxID())
    {
        if(_stopped)
            break;
        this->delay(500);
        Executor::Instance().ExecuteNext();
        FillGCodeEditor();
    }

    int currentID = Executor::Instance().currentState().id();
    ui->btnPrevious->setEnabled(currentID > 0);
    ui->btnNext->setEnabled(currentID < State::maxID());
    ui->btnPlay->setEnabled(currentID < State::maxID());
    ui->btnRestart->setEnabled(currentID > 0);
    ui->btnStop->setEnabled(false);
}

void MainWindow::on_btnNext_clicked()
{
    Executor::Instance().ExecuteNext();
    this->FillGCodeEditor();

    int currentID = Executor::Instance().currentState().id();
    ui->btnPrevious->setEnabled(currentID > 0);
    ui->btnRestart->setEnabled(currentID > 0);
    ui->btnNext->setEnabled(currentID < State::maxID());
    ui->btnPlay->setEnabled(currentID < State::maxID());
}

void MainWindow::on_btnPrevious_clicked()
{
    Executor::Instance().ExecutePrevious();
    this->FillGCodeEditor();

    int currentID = Executor::Instance().currentState().id();
    ui->btnPrevious->setEnabled(currentID > 0);
    ui->btnRestart->setEnabled(currentID > 0);
    ui->btnNext->setEnabled(currentID < State::maxID());
    ui->btnPlay->setEnabled(currentID < State::maxID());
}

void MainWindow::on_btnStop_clicked()
{
    _stopped = true;
    ui->btnStop->setEnabled(false);
}

void MainWindow::on_btnRestart_clicked()
{
    Executor::Instance().Init(gCommands);
    this->FillGCodeEditor();

    ui->btnNext->setEnabled(true);
    ui->btnPlay->setEnabled(true);
    ui->btnPrevious->setEnabled(false);
    ui->btnRestart->setEnabled(false);
}

void MainWindow::delay( int millisecondsToWait)
{
    QTime dieTime = QTime::currentTime().addMSecs( millisecondsToWait );
    while( QTime::currentTime() < dieTime )
    {
        QCoreApplication::processEvents( QEventLoop::AllEvents, 100 );
    }
}
