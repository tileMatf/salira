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
    void on_btnClear_clicked();

    void on_txtEditorGCode_textChanged();

    void on_btnTranslate_clicked();

    void on_btnPlay_clicked();

    void on_btnNext_clicked();

    void on_btnPrevious_clicked();

    void on_btnRestart_clicked();
    void delay(int miliseconds);
    void on_btnStop_clicked();

    void on_btnRun_clicked();

    void on_tsmiOpen_triggered();

    void on_tsmiSaveGCode_triggered();

    void on_tsmiSaveVAXCode_triggered();

    void on_tsmiClear_triggered();

    void on_tsmiClose_triggered();

private:
    Ui::MainWindow *ui;
    void FillGCodeEditor();
    void FillVAXCodeEditor();
    void FillOutput();
    void Open();
    void Clear();
    void SaveGCode();
    void SaveVAXCode();
    void Close();
};

#endif // MAINWINDOW_H
