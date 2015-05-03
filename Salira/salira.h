#ifndef SALIRA_H
#define SALIRA_H

#include <QMainWindow>

namespace Ui {
class Salira;
}

class Salira : public QMainWindow
{
    Q_OBJECT

public:
    explicit Salira(QWidget *parent = 0);
    ~Salira();

private:
    Ui::Salira *ui;
};

#endif // SALIRA_H
