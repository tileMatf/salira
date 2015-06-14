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
public:
    GCommand(QString value);
    ~GCommand();
    QString Value;
    QList<shared_ptr<GArgument>> Args;
    bool Valid;
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
public:
    GArgumentString(QString value);
    ~GArgumentString();
    QString Value;
    QString ToString() const;
};

class GArgumentInt : public GArgument
{
public:
    GArgumentInt(int value);
    ~GArgumentInt();
    int Value;
    QString ToString() const;
};


#endif // GCOMMAND_H
