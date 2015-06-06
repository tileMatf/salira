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
    foreach (QString line, input)
    {
        GCommand command = GCommand(line);
        if(!command.Valid)
            return false;
        output->push_back(command);
    }

    return true;
}

