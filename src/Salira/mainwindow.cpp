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

static QString fileName = "/home/jupikea/Desktop/Funkcionalno/Projekat/salira/src/Test/";
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
    //ui->btnClear->setEnabled(true);
}

void MainWindow::FillVAXCodeEditor()
{
    ui -> txtEditorVAXCode->clear();

    if(vaxCommands.size() == 0)
        return;

    foreach (VAXCommand command, vaxCommands)
        ui->txtEditorVAXCode->append(command.ToString());
}

void MainWindow::FillOutput()
{
    ui->txtOutput->clear();

    foreach (QString line, Executor::Instance().currentState().output())
        ui->txtOutput->append(">> " + line);
}

void MainWindow::on_btnClear_clicked()
{
    this->Clear();
}

void MainWindow::on_txtEditorGCode_textChanged()
{
    bool enable = ui->txtEditorGCode->toPlainText().length() > 0;

    //ui->btnClear->setEnabled(enable);
    ui->btnTranslate->setEnabled(enable);
}

void MainWindow::on_btnTranslate_clicked()
{
    if(Translator::Instance().Translate(gCommands, &vaxCommands))
        FillVAXCodeEditor();
}

void MainWindow::on_btnPrevious_clicked()
{
    Executor::Instance().ExecutePrevious();
    this->FillGCodeEditor();
    this->FillOutput();

    int currentID = Executor::Instance().currentState().id();
    ui->btnPrevious->setEnabled(currentID > 0);
    ui->btnRestart->setEnabled(currentID > 0);
    ui->btnNext->setEnabled(currentID < State::maxID());
    ui->btnRun->setEnabled(currentID < State::maxID());
}

void MainWindow::on_btnNext_clicked()
{
    Executor::Instance().ExecuteNext();
    this->FillGCodeEditor();
    this->FillOutput();

    int currentID = Executor::Instance().currentState().id();
    ui->btnPrevious->setEnabled(currentID > 0);
    ui->btnRestart->setEnabled(currentID > 0);
    ui->btnNext->setEnabled(currentID < State::maxID());
    ui->btnRun->setEnabled(currentID < State::maxID());
}

void MainWindow::on_btnRun_clicked()
{
    _stopped = false;
    ui->btnStop->setEnabled(true);
    ui->btnPrevious->setEnabled(false);
    ui->btnNext->setEnabled(false);
    ui->btnRun->setEnabled(false);
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
    ui->btnRun->setEnabled(currentID < State::maxID());
    ui->btnRestart->setEnabled(currentID > 0);
    ui->btnStop->setEnabled(false);
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
    ui->btnRun->setEnabled(true);
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

void MainWindow::on_btnPlay_clicked()
{

}

void MainWindow::on_tsmiOpen_triggered()
{
    this->Open();
}

void MainWindow::on_tsmiClear_triggered()
{
    this->Clear();
}

void MainWindow::on_tsmiSaveGCode_triggered()
{
    this->SaveGCode();
}

void MainWindow::on_tsmiSaveVAXCode_triggered()
{
   this->SaveVAXCode();
}

void MainWindow::on_tsmiClose_triggered()
{
   this->close();
}

void MainWindow::Open()
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
                ui->btnRun->setEnabled(true);
                ui->btnNext->setEnabled(true);
            }
        }
    }
}

void MainWindow::Clear()
{
    ui->txtEditorGCode->clear();
    ui->txtEditorVAXCode->clear();
    ui->btnTranslate->setEnabled(false);
}

void MainWindow::SaveGCode()
{

}

void MainWindow::SaveVAXCode()
{

}

void MainWindow::Close()
{
    this->close();
}
