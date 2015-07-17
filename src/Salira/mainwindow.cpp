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
#include <QTime>


using namespace std;

static QString fileName = "/home/kostic/Downloads/Salira_Literatura/smiskovic_gmasina/";
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

void removeAllButton(QLayout *layout)
{
    QLayoutItem *child;
    while ((child = layout->takeAt(0)) != 0) {
        delete child->widget();
        delete child;
    }
}

void MainWindow::FillOutput()
{
    ui->txtOutput->clear();

    foreach (QString line, Executor::Instance().currentState().output())
        ui->txtOutput->append(">> " + line + "\n");


    removeAllButton(ui->stackLayout);

    for(int i = 0; i < Executor::Instance().currentState().stack().length(); i++)
    {
        QString nodeName = "NODE [" + QString::number(Executor::Instance().currentState().stack().at(i)+1) + "]";
        ui->stackLayout->insertWidget(ui->stackLayout->count()-i,new QPushButton(nodeName));
    }

    removeAllButton(ui->graphLayout);
    for(int i = 0; i < Executor::Instance().currentState().graph().length(); i++)
    {
        QString nodeName;
        switch(Executor::Instance().currentState().graph()[i].type())
        {
        case 0:
            nodeName = "HOLE";
            break;
        case 1:
            nodeName = "INTEGER\nNODE [" + QString::number(Executor::Instance().currentState().graph()[i].id()+1)
                    + "]\n" + QString::number(Executor::Instance().currentState().graph()[i].value());
            break;
        case 2:
            nodeName = "FUNCTION\nNODE [" + QString::number(Executor::Instance().currentState().graph()[i].id()+1)
                    + "]\n" + Executor::Instance().currentState().graph()[i].functionName();
            break;
        case 3:
            nodeName = "CONST";
            break;
        case 4:
            nodeName = "APPLICATION\nNODE[" + QString::number(Executor::Instance().currentState().graph()[i].id()+1)
                    + "]\nNODE [" + QString::number(Executor::Instance().currentState().graph()[i].idRef1()+1)
                    + "]\nNODE [" + QString::number(Executor::Instance().currentState().graph()[i].idRef2()+1);
            break;
        }

        ui->graphLayout->insertWidget(ui->graphLayout->count()-i,new QPushButton(nodeName));
    }


    ui->txtOutput->append(QString("Stack:"));
    for(int i =0; i < Executor::Instance().currentState().stack().length(); i++)
        ui->txtOutput->append("id = " + QString::number(Executor::Instance().currentState().stack().at(i)));
    ui->txtOutput->append(QString("Graph:"));
    for(int i =0; i < Executor::Instance().currentState().graph().length(); i++)
        ui->txtOutput->append("id = " + QString::number(Executor::Instance().currentState().graph()[i].id()) +
                             + "value = " + QString::number(Executor::Instance().currentState().graph()[i].value()) +
                              +" length=" + QString::number(Executor::Instance().currentState().graph().length())
                              + " ep= " + QString::number(Executor::Instance().currentState().ep())
                              + " type= " + QString::number(Executor::Instance().currentState().graph()[i].type())
                              + " n1 n2 = " + QString::number(Executor::Instance().currentState().graph()[i].idRef1())
                              + " " + QString::number(Executor::Instance().currentState().graph()[i].idRef2()));

    ui->txtOutput->append(QString("Dump:"));
    for(int i =0; i < Executor::Instance().currentState().dump().length(); i++)
        for(int j = 0; j < Executor::Instance().currentState().dump()[i].stack().length(); j++)
        ui->txtOutput->append(QString::number(Executor::Instance().currentState().dump()[i].stack()[j]) + " ");
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
    fileName = QFileDialog::getOpenFileName (this, tr("Open File"), fileName /*, tr("Files (.)")*/);

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
