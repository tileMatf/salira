#include "gcommand.h"

GCommand::GCommand(QString value)
    :Value(value), Valid(false)
{
    if(value == "") // potrebno je definisati i praznu komandu
    {
        Valid = true;
        return ;
    }

    /*promenljiva koja indikuje da li su argumenti u redu*/
    bool ok;

    /*provera da li se komanda zavrsava sa ; */
    if(!value.contains(';') || value.indexOf(';') != (value.size()-1))
        return;

    value = value.toUpper();

    /*razdvajanje komande na podstringove*/
    QStringList GCommandParts = value.split(" ");
    foreach (QString part, GCommandParts)
       part.trimmed();

    /*uklanjanje ; */
    GCommandParts[GCommandParts.size()-1].replace(';', "");


    if(!GCommandParts[0].compare("PUSHINT")) //Miskovic je u PUSHINT dopustio double kao argument
    {
        if(GCommandParts.size() != 2)
            return;

        int arg = GCommandParts[1].toInt(&ok, 10);

        if(!ok)
            return;

        this->AddArg(arg);
        this->Value = GCommandParts[0];
        this->Valid = true;
    }
    else if(!GCommandParts[0].compare("PUSHGLOBAL") || !GCommandParts[0].compare("GLOBSTART"))
    {
        if(GCommandParts.size() != 3 || GCommandParts[1].at(0) != '$' || GCommandParts[1].at(1).isDigit())
            return;

        int arg = GCommandParts[2].toInt(&ok, 10);

        if(!ok)
            return;

        this->AddArg(GCommandParts[1]);
        this->AddArg(arg);
        this->Value = GCommandParts[0];
        this->Valid = true;
    }
    else if(!GCommandParts[0].compare("PUSH") || !GCommandParts[0].compare("POP") ||
            !GCommandParts[0].compare("SLIDE") || !GCommandParts[0].compare("ALLOC")
            || !GCommandParts[0].compare("UPDATE"))
    {
        if(GCommandParts.size() != 2)
            return;

        int arg = GCommandParts[1].toInt(&ok, 10);

        if(!ok)
            return;

        this->AddArg(arg);
        this->Value = GCommandParts[0];
        this->Valid = true;
    }
    else if(!GCommandParts[0].compare("MKAP") || !GCommandParts[0].compare("CONS") ||
            !GCommandParts[0].compare("ADD") || !GCommandParts[0].compare("SUB") ||
            !GCommandParts[0].compare("MUL") || !GCommandParts[0].compare("DIV") ||
            !GCommandParts[0].compare("NEG") || !GCommandParts[0].compare("HEAD") ||
            !GCommandParts[0].compare("END") || !GCommandParts[0].compare("BEGIN") ||
            !GCommandParts[0].compare("PRINT") || !GCommandParts[0].compare("MIN") ||
            !GCommandParts[0].compare("MAX") || !GCommandParts[0].compare("EVAL") ||
            !GCommandParts[0].compare("EVAL2") || !GCommandParts[0].compare("UNWIND") ||
            !GCommandParts[0].compare("UNWIND2") || !GCommandParts[0].compare("RETURN"))
    {
        if(GCommandParts.size() != 1)
            return;

        this->Value = GCommandParts[0];
        this->Valid = true;
    }
    else if(!GCommandParts[0].compare("LABEL") || !GCommandParts[0].compare("JUMP") ||
            !GCommandParts[0].compare("JFALSE"))
    {
        if(GCommandParts.size() != 2)
            return;

        this->AddArg(GCommandParts[1]);
        this->Value = GCommandParts[0];
        this->Valid = true;
    }
}

GCommand::~GCommand()
{

}

QString GCommand::ToString() const
{
    QString retValue;

    if(this->Value.length() > 0)
    {
        retValue += this->Value;

        foreach (shared_ptr<GArgument> argument, this->Args)
            retValue += " " + argument.get()->ToString();
        retValue += ";";
    }

    return retValue;
}

void GCommand::AddArg(QString arg)
{
    this->Args.push_back(shared_ptr<GArgument>(new GArgumentString(arg)));
}

void GCommand::AddArg(int arg)
{
    this->Args.push_back(shared_ptr<GArgument>(new GArgumentInt(arg)));
}

GArgument::~GArgument()
{

}

GArgumentString::GArgumentString(QString value)
    :Value(value)
{
}

GArgumentString::~GArgumentString()
{
}

QString GArgumentString::ToString() const
{
    return this->Value;
}

GArgumentInt::GArgumentInt(int value)
    :Value(value)
{
}

GArgumentInt::~GArgumentInt()
{
}

QString GArgumentInt::ToString() const
{
    return QString::number(this->Value);
}

