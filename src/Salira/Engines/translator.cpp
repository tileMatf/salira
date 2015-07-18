#include "translator.h"

Translator::Translator()
{
}

Translator& Translator::Instance()
{
    static Translator instance;
    return instance;
}

bool Translator::Translate(QList<GCommand> input, QList<VAXCommand>* output)
{
    output->clear();

    if(input.length() == 0)
        return false;

    foreach (GCommand gCommand, input)
    {
        QList<VAXCommand> vaxCommands;
        if(!VAXCommand::GetCommands(gCommand, &vaxCommands))
            return false;
        output->append(vaxCommands);
    }

    return true;
}

