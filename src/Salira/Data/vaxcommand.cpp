#include "vaxcommand.h"

VAXCommand::VAXCommand(GCommand input)
    :Valid(false)
{
    this->Value = input.Value;

    //ako sve lepo prodje
    this->Valid = true;
}

VAXCommand::~VAXCommand()
{
}

VAXArgument::VAXArgument(QString value)
    :Value(value)
{
}

VAXArgument::~VAXArgument()
{
}

