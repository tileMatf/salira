#ifndef GCOMMAND_H
#define GCOMMAND_H
#include <QString>
#include <QList>

class GArgument;
class GArgumentInt;
class GArgumentString;

class GCommand
{
public:
    GCommand(QString value);
    GCommand(QString value, QList<GArgument> args);
    QString Value;
    QList<GArgument> Args;
};

class GArgument
{
};

class GArgumentString : public GArgument
{
public:
    GArgumentString(QString value);
    ~GArgumentString();
    QString Value;
};

class GArgumentInt : public GArgument
{
    GArgumentInt(int value);
    ~GArgumentInt();
    int Value;
};


#endif // GCOMMAND_H
