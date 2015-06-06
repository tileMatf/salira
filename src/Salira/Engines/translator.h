#ifndef TRANSLATE_H
#define TRANSLATE_H
#include <QString>
#include <QList>
#include <Data/vaxcommand.h>
#include <Data/gcommand.h>

using namespace std;

class Translator
{
private:
    Translator();
public:
    static Translator& Instance();
    bool Translate(QList<GCommand> input, QList<VAXCommand>* output);
};

#endif // TRANSLATE_H
