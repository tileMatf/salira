#ifndef VAXCOMMAND_H
#define VAXCOMMAND_H
#include <Data/gcommand.h>

class VAXArgument;

class VAXCommand
{
public:
    VAXCommand(GCommand command);
    ~VAXCommand();
    QString Value;
    QList<VAXArgument> Args;
    bool Valid;
};

class VAXArgument
{
public:
    VAXArgument(QString value);
    ~VAXArgument();
    QString Value;
};

#endif // VAXCOMMAND_H
