#ifndef GCOMMAND_H
#define GCOMMAND_H
#include <QString>
#include <QList>
#include <QStringList>
#include <memory>

using namespace std;

class GArgument;
class GArgumentInt;
class GArgumentString;

class GCommand
{
/*public:
    enum GCommandType
    {
        NONE = 0,
        PUSHINT,
        PUSHGLOBAL,
        GLOBSTART,
        PUSH,
        POP,
        SLIDE,
        ALLOC,
        UPDATE,
        MKAP,
        CONS,
        ADD,
        SUB,
        MUL,
        DIV,
        NEG,
        HEAD,
        END,
        BEGIN,
        PRINT,
        MIN,
        MAX,
        EVAL,
        EVAL2,
        UNWIND,
        UNWIND2,
        RETURN,
        LABEL,
        JUMP,
        JFALSE
    };*/

private:
    bool _valid;
    QString _value;
    QList<GArgument*> _args;
public:
    GCommand(QString value);
    ~GCommand();

    bool valid();
    QString value();
    QList<GArgument*> args();

    QString ToString() const;
    void AddArg(QString arg);
    void AddArg(int arg);
};

class GArgument
{
public:
    ~GArgument();
    virtual QString ToString() const = 0;
};

class GArgumentString : public GArgument
{
private:
    QString _value;
public:
    GArgumentString(QString value);
    ~GArgumentString();

    QString ToString() const;
};

class GArgumentInt : public GArgument
{
private:
    int _value;
public:
    GArgumentInt(int value);
    ~GArgumentInt();

    QString ToString() const;
};


#endif // GCOMMAND_H
