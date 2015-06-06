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

void Parser::Parse(QList<QString> input, QList<GCommand>* gCommands)
{
    gCommands->clear();
    foreach (QString line, input)
        gCommands->push_back(GCommand(line));
}

