#ifndef PARSER_H
#define PARSER_H
#include <QList>
#include <Data/gcommand.h>

using namespace std;

class Parser
{
private:
    Parser();
public:
    static Parser& Instance();
    void Parse(QList<QString> input, QList<GCommand>* gCommands);
};

#endif // PARSER_H
