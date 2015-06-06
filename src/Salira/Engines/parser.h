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
    bool Parse(QList<QString> input, QList<GCommand>* output);
};

#endif // PARSER_H
