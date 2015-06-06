#include "gcommand.h"

GCommand::GCommand(QString value)
    :Value(value)
{
    //videti kako ovde parsirati
}

GCommand::GCommand(QString value, QList<GArgument> args)
    :Value(value), Args(args)
{
}

GArgumentString::GArgumentString(QString value)
    :Value(value)
{
}

GArgumentInt::GArgumentInt(int value)
    :Value(value)
{
}

