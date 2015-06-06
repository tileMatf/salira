#include "translator.h"

Translator::Translator()
{
}

Translator& Translator::Instance()
{
    static Translator instance;
    return instance;
}

QList<VAXCommand> Translator::Translate(QList<GCommand> input)
{
    return QList<VAXCommand>();
}

