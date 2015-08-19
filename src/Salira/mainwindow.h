#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_tsmiOpen_triggered();

    void on_tsmiClear_triggered();

    void on_tsmiSaveGCode_triggered();

    void on_tsmiSaveVAXCode_triggered();

    void on_tsmiClose_triggered();

    void on_tsmiRestart_triggered();

    void on_tsmiNext_triggered();

    void on_tsmiPrevious_triggered();

    void on_tsmiRun_triggered();

    void on_tsmiStop_triggered();

    void on_btnRestart_clicked();

    void on_btnNext_clicked();

    void on_btnPrevious_clicked();

    void on_btnRun_clicked();

    void on_btnStop_clicked();

    void on_txtEditorGCode_textChanged();

    void on_btnTranslate_clicked();

    void on_txtEditorVAXCode_textChanged();

    void delay(int miliseconds);

    void on_btnPlay_clicked();

    void on_btnExecute_clicked();

    void on_textEditHaskell_textChanged();

    void on_btnOpen_clicked();

private:
    Ui::MainWindow *ui;
    void FillGCodeEditor();
    void FillVAXCodeEditor(bool clearOnly = false);
    void FillStack(bool clearOnly = false);
    void FillGraph(bool clearOnly = false);
    void FillDump(bool clearOnly = false);
    void FillOutput(bool clearOnly = false);
    void RefreshUI(bool clearOnly = false, bool keepGCodeText = false);
    void RefreshFileMenu(bool clearEnabled, bool saveGCodeEnabled, bool saveVAXCodeEnabled);
    void RefreshRunMenu(bool evaluateEnabled, bool nextEnabled, bool previousEnabled, bool runEnabled, bool stopEnabled);
    void RemoveAllButtons(QLayout *layout);
    void Clear(bool keepGCodeText = false);

    void Open();
    void Evaluate();
    void Next();
    void Previous();
    void Run();
    void Stop();
};

#endif // MAINWINDOW_H
