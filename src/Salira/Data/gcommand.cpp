#include "gcommand.h"
#include <QStringList>

GCommand::GCommand(QString value)
    :Value(value), Valid(false)
{
    //videti kako ovde parsirati
    //eventualno dodati metodu ToString, a value da bude bas komanda
    //ako je sve okej
    bool ok;
    value = value.toUpper();

    QStringList GCommandParts = value.split(" ");
    foreach (QString part, GCommandParts)
       part.trimmed();

    if(!GCommandParts[0].compare("PUSHINT"))
    {
        if(GCommandParts.size() != 2)
        {
            this->Valid = false;
            return;
        }

        int arg = GCommandParts[1].toInt(&ok, 10);

        if(!ok)
        {
            this->Valid = false;
            return;
        }

        this->Args.push_back(GArgumentInt(arg));
        this->Value = GCommandParts[0];
        this->Valid = true;
    }
    else if(!GCommandParts[0].compare("PUSHGLOBAL"))
    {
        if(GCommandParts.size() != 3 || GCommandParts[1].at(0) != '$' || GCommandParts[1].at(1).isDigit())
        {
            this->Valid = false;
            return;
        }

        int arg = GCommandParts[2].toInt(&ok, 10);

        if(!ok)
        {
            this->Valid = false;
            return;
        }

        this->Args.push_back(GArgumentString(GCommandParts[1]));
        this->Args.push_back(GArgumentInt(arg));
        this->Value = GCommandParts[0];
        this->Valid = true;
    }
}

GCommand::~GCommand()
{

}

GArgumentString::GArgumentString(QString value)
    :Value(value)
{
}

GArgumentString::~GArgumentString()
{
}

GArgumentInt::GArgumentInt(int value)
    :Value(value)
{
}

GArgumentInt::~GArgumentInt()
{
}

