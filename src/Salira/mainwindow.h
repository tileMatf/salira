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
    void FillGCodeEditor();
    void FillVAXCodeEditor();

private slots:
    void on_btnOpen_clicked();

    void on_btnClear_clicked();

    void on_txtEditorGCode_textChanged();

    void on_btnTranslate_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
