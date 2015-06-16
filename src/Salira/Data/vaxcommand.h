#ifndef VAXCOMMAND_H
#define VAXCOMMAND_H
#include <Data/gcommand.h>

class VAXArgument;

class VAXCommand
{
private:
    bool _valid;
    QString _value;
    QList<VAXArgument> _args;
public:
    VAXCommand(QString command, QString arg1 = "", QString arg2 = "");
    ~VAXCommand();

    QString ToString() const;
    static bool GetCommands(GCommand input, QList<VAXCommand>* output);
    static bool PushInt(QList<VAXCommand>* output, QString value);
    static bool PushGlobal(QList<VAXCommand>* output, QString value);
    static bool GlobStart(QList<VAXCommand>* output, QString value);
    static bool Push(QList<VAXCommand>* output, QString value);
    static bool Pop(QList<VAXCommand>* output, QString value);
    static bool Slide(QList<VAXCommand>* output, QString value);
    static bool Alloc(QList<VAXCommand>* output, int value);
    static bool Update(QList<VAXCommand>* output, QString value);
    static bool Mkap(QList<VAXCommand>* output);
    static bool Cons(QList<VAXCommand>* output);
    static bool Add(QList<VAXCommand>* output);
    static bool Sub(QList<VAXCommand>* output);
    static bool Mul(QList<VAXCommand>* output);
    static bool Div(QList<VAXCommand>* output);
    static bool Neg(QList<VAXCommand>* output);
    static bool Head(QList<VAXCommand>* output);
    static bool End(QList<VAXCommand>* output);
    static bool Begin(QList<VAXCommand>* output);
    static bool Print(QList<VAXCommand>* output);
    static bool Min(QList<VAXCommand>* output);
    static bool Max(QList<VAXCommand>* output);
    static bool Eval(QList<VAXCommand>* output);
    static bool Eval2(QList<VAXCommand>* output);
    static bool Unwind(QList<VAXCommand>* output);
    static bool Unwind2(QList<VAXCommand>* output);
    static bool Return(QList<VAXCommand>* output);
    static bool Label(QList<VAXCommand>* output, QString value);
    static bool Jump(QList<VAXCommand>* output, QString value);
    static bool JFalse(QList<VAXCommand>* output, QString value);
};

class VAXArgument
{
private:
    QString _value;
public:
    VAXArgument(QString value);
    ~VAXArgument();

    QString ToString() const;
};

#endif // VAXCOMMAND_H
