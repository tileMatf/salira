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
    foreach (GCommand gCommand, input)
    {
        VAXCommand command = VAXCommand(gCommand.Value);
        if(!command.Valid)
            return false;
        output->push_back(command);
    }

    return true;
}

