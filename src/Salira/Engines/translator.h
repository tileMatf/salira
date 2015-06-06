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
    QList<VAXCommand> Translate(QList<GCommand> input);
};

#endif // TRANSLATE_H
