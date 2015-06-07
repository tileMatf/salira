#ifndef GCOMMAND_H
#define GCOMMAND_H
#include <QString>
#include <QList>
#include <QStringList>

class GArgument;
class GArgumentInt;
class GArgumentString;

class GCommand
{
public:
    GCommand(QString value);
    ~GCommand();
    QString Value;
    QList<GArgument> Args;
    bool Valid;
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
public:
    GArgumentInt(int value);
    ~GArgumentInt();
    int Value;
};


#endif // GCOMMAND_H
