#include "parser.h"

static Parser *instance = nullptr;

Parser::Parser()
{
}

Parser& Parser::Instance()
{
    static Parser instance;
    return instance;
}

bool Parser::Parse(QList<QString> input, QList<GCommand>* output)
{
    output->clear();

    if(input.length() == 0)
        return false;

    foreach (QString line, input)
    {
        GCommand command = GCommand(line);
        if(!command.valid())
            return false;
        output->push_back(command);
    }

    return true;
}

