#include "gcommand.h"

GCommand::GCommand(QString value)
    :Value(value), Valid(false)
{
    //videti kako ovde parsirati
    //eventualno dodati metodu ToString, a value da bude bas komanda
    //ako je sve okej
    this->Valid = true;
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

