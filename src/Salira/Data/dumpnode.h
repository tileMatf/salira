#ifndef DUMPNODE_H
#define DUMPNODE_H
#include <QVector>
#include <QString>

class DumpNode
{
private:
    QVector<int> _stack;
    QVector<QString> _code;
public:
    DumpNode();
    DumpNode(QVector<int> stack, QVector<QString> code);
    ~DumpNode();

    QVector<int> stack();
    QVector<QString> code();
};

#endif // DUMPNODE_H
