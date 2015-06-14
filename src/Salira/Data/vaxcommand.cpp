#include "vaxcommand.h"

VAXCommand::VAXCommand(QString command, QString arg1, QString arg2)
    :Valid(false)
{
    this->Value = command;
    if(arg1.length() > 0)
        this->Args.push_back(arg1);
    if(arg2.length() > 0)
        this->Args.push_back(arg2);
    this->Valid = true;
}

VAXCommand::~VAXCommand()
{
}

bool VAXCommand::GetCommands(GCommand input, QList<VAXCommand>* output)
{
    if(input.Value == "")
        return true;

    if(input.Value == "PUSHINT")
        return PushInt(output, input.Args[0].get()->ToString());

    if(input.Value == "PUSHGLOBAL")
        return PushGlobal(output, input.Args[0].get()->ToString());

    if(input.Value == "GLOBSTART")
        return GlobStart(output, input.Args[0].get()->ToString());

    if(input.Value == "PUSH")
        return Push(output,input.Args[0].get()->ToString());

    if(input.Value == "POP")
        return Pop(output, input.Args[0].get()->ToString());

    if(input.Value == "SLIDE")
        return Slide(output, input.Args[0].get()->ToString());

    if(input.Value == "ALLOC")
        return Alloc(output, (int)input.Args[0].get()->ToString().toInt());

    if(input.Value == "UPDATE")
        return Update(output, input.Args[0].get()->ToString());

    if(input.Value == "MKAP")
        return Mkap(output);

    if(input.Value == "CONS")
        return Cons(output);

    if(input.Value == "ADD")
        return Add(output);

    if(input.Value == "SUB")
        return Sub(output);

    if(input.Value == "MUL")
        return Mul(output);

    if(input.Value == "DIV")
        return Div(output);

    if(input.Value == "NEG")
        return Neg(output);

    if(input.Value == "HEAD")
        return Head(output);

    if(input.Value == "END")
        return End(output);

    if(input.Value == "BEGIN")
        return Begin(output);

    if(input.Value == "PRINT")
        return Print(output);

    if(input.Value == "MIN")
        return Min(output);

    if(input.Value == "MAX")
        return Max(output);

    if(input.Value == "EVAL")
        return Eval(output);

    if(input.Value == "EVAL2")
        return Eval2(output);

    if(input.Value == "UNWIND")
        return Unwind(output);

    if(input.Value == "UNWIND2")//treba videti kako radi
        return Unwind2(output);

    if(input.Value == "RETURN")
        return Return(output);

    if(input.Value == "LABEL")
        return Label(output, input.Args[0].get()->ToString());

    if(input.Value == "JUMP")
        return Jump(output, input.Args[0].get()->ToString());

    if(input.Value == "JFALSE")
        return JFalse(output, input.Args[0].get()->ToString());

    return false;
}

QString VAXCommand::ToString() const
{
    QString retValue;

    if(this->Value.length() > 0)
    {
        retValue += this->Value;

        if(this->Args.length() > 0)
            retValue += " ";

        int i = 1;
        foreach (VAXArgument argument, this->Args)
            retValue += argument.ToString() + (i++ < this->Args.length() ? "," : "");
    }

    return retValue;
}

bool VAXCommand::PushInt(QList<VAXCommand> *output, QString value)
{
    output->push_back(VAXCommand("incl", "(%hp)"));
    output->push_back(VAXCommand("incl", "(%ep)"));
    output->push_back(VAXCommand("moval", "(%hp)", "(%ep)"));
    output->push_back(VAXCommand("moval", "INTEGER", "(%hp)"));
    output->push_back(VAXCommand("incl", "(%hp)"));
    output->push_back(VAXCommand("incl", "(%ep)"));
    output->push_back(VAXCommand("moval", "(%hp)", "(%ep)"));
    output->push_back(VAXCommand("moval", value, "(%hp)"));

    return true;
}

bool VAXCommand::PushGlobal(QList<VAXCommand> *output, QString value)
{
    output->push_back(VAXCommand("incl", "(%hp)"));
    output->push_back(VAXCommand("incl", "(%ep)"));
    output->push_back(VAXCommand("moval", "(%hp)", "(%ep)"));
    output->push_back(VAXCommand("moval", "FUNCTION", "(%hp)"));
    output->push_back(VAXCommand("incl", "(%hp)"));
    output->push_back(VAXCommand("incl", "(%ep)"));
    output->push_back(VAXCommand("moval", "(%hp)", "(%ep)"));
    output->push_back(VAXCommand("moval", value, "(%hp)"));
    output->push_back(VAXCommand("incl", "(%hp)"));
    output->push_back(VAXCommand("incl", "(%ep)"));
    output->push_back(VAXCommand("moval", "(%hp)", "(%ep)"));
    output->push_back(VAXCommand("moval", "y", "(%hp)"));

    return true;
}

bool VAXCommand::GlobStart(QList<VAXCommand> *output, QString value)
{
    output->push_back(VAXCommand(value + ":"));
    return true;
}

bool VAXCommand::Push(QList<VAXCommand> *output, QString value)
{
    output->push_back(VAXCommand("incl", "(%ep)"));
    output->push_back(VAXCommand("movl", "(4*(" + value +"+1))(%ep)", "(%ep)"));

    return true;
}

bool VAXCommand::Pop(QList<VAXCommand> *output, QString value)
{
    output->push_back(VAXCommand("moval", "(4*" + value +")(%ep)", "(%ep)"));
    return true;
}

bool VAXCommand::Slide(QList<VAXCommand> *output, QString value)
{
    output->push_back(VAXCommand("movl", "(%ep)", "r0"));
    output->push_back(VAXCommand("moval", "(4*(" + value +"+1))(%ep)", "(%ep)"));
    output->push_back(VAXCommand("incl", "(%ep)"));
    output->push_back(VAXCommand("movl", "r0", "(%ep)"));

    return true;
}

bool VAXCommand::Alloc(QList<VAXCommand> *output, int value)
{
    for (int j = 0; j < value; j++)
        output->push_back(VAXCommand("incl", "(%ep)"));
    for (int j = 0; j < value; j++)
        output->push_back(VAXCommand("incl", "(%hp)"));
    for (int j = 0; j < value; j++)
        output->push_back(VAXCommand("moval", "(%hp)", "(%ep)"));
    for (int j = 0; j < value; j++)
        output->push_back(VAXCommand("moval", "HOLE", "(%hp)"));

    return true;
}

bool VAXCommand::Update(QList<VAXCommand> *output, QString value)
{
    output->push_back(VAXCommand("movl", "(%ep)", "r0"));
    output->push_back(VAXCommand("decl", "ep"));
    output->push_back(VAXCommand("movl", "r0", value +"(%ep)"));

    return true;
}

bool VAXCommand::Mkap(QList<VAXCommand>* output)
{
    output->push_back(VAXCommand("movl", "(%ep)", "r0"));
    output->push_back(VAXCommand("decl", "(%ep)"));
    output->push_back(VAXCommand("movl", "(%ep)", "r1"));
    output->push_back(VAXCommand("incl", "(%hp)"));
    output->push_back(VAXCommand("moval", "(%hp)", "(%ep)"));
    output->push_back(VAXCommand("moval", "APPLY", "(%hp)"));
    output->push_back(VAXCommand("incl", "(%hp)"));
    output->push_back(VAXCommand("movl", "r0", "(%hp)"));
    output->push_back(VAXCommand("incl", "(%hp)"));
    output->push_back(VAXCommand("movl", "r1", "(%hp)"));

    return true;
}

bool VAXCommand::Cons(QList<VAXCommand>* output)
{
    output->push_back(VAXCommand("movl", "(%ep)", "r0"));
    output->push_back(VAXCommand("decl", "ep"));
    output->push_back(VAXCommand("movl", "(%ep)", "r1"));
    output->push_back(VAXCommand("incl", "(%hp)"));
    output->push_back(VAXCommand("moval", "(%hp)", "(%ep)"));
    output->push_back(VAXCommand("moval", "APPLY", "(%hp)"));
    output->push_back(VAXCommand("incl", "(%hp)"));
    output->push_back(VAXCommand("movl", "r0", "(%hp)"));
    output->push_back(VAXCommand("incl", "(%hp)"));
    output->push_back(VAXCommand("movl", "r1", "(%hp)"));

    //treba proveriti jel ovo okej
    return true;
}

bool VAXCommand::Add(QList<VAXCommand>* output)
{
    output->push_back(VAXCommand("movl", "@(%ep)", "r0"));
    output->push_back(VAXCommand("decl", "(%ep)"));
    output->push_back(VAXCommand("movl", "@(%ep)", "r1"));
    output->push_back(VAXCommand("incl", "(%hp)"));
    output->push_back(VAXCommand("moval", "(%hp)", "(%ep)"));
    output->push_back(VAXCommand("addl2", "r0", "r1"));
    output->push_back(VAXCommand("moval", "r0", "(%hp)"));

    return true;
}

bool VAXCommand::Sub(QList<VAXCommand>* output)
{
    output->push_back(VAXCommand("movl", "@(%ep)", "r0"));
    output->push_back(VAXCommand("decl", "(%ep)"));
    output->push_back(VAXCommand("movl", "@(%ep)", "r1"));
    output->push_back(VAXCommand("incl", "(%hp)"));
    output->push_back(VAXCommand("moval", "(%hp)", "(%ep)"));
    output->push_back(VAXCommand("subl2", "r0", "r1"));
    output->push_back(VAXCommand("moval", "r0", "(%hp)"));

    return true;
}

bool VAXCommand::Mul(QList<VAXCommand>* output)
{
    output->push_back(VAXCommand("movl", "@(%ep)", "r0"));
    output->push_back(VAXCommand("decl", "(%ep)"));
    output->push_back(VAXCommand("movl", "@(%ep)", "r1"));
    output->push_back(VAXCommand("incl", "(%hp)"));
    output->push_back(VAXCommand("moval", "(%hp)", "(%ep)"));
    output->push_back(VAXCommand("mull2", "r0", "r1"));
    output->push_back(VAXCommand("moval", "r0", "(%hp)"));

    return true;
}

bool VAXCommand::Div(QList<VAXCommand>* output)
{
    output->push_back(VAXCommand("movl", "@(%ep)", "r0"));
    output->push_back(VAXCommand("decl", "(%ep)"));
    output->push_back(VAXCommand("movl", "@(%ep)", "r1"));
    output->push_back(VAXCommand("incl", "(%hp)"));
    output->push_back(VAXCommand("moval", "(%hp)", "(%ep)"));
    output->push_back(VAXCommand("divl2", "r0", "r1"));
    output->push_back(VAXCommand("moval", "r0", "(%hp)"));

    return true;
}

bool VAXCommand::Neg(QList<VAXCommand>* output)
{
    output->push_back(VAXCommand("movl", "@(%ep)", "r0"));
    output->push_back(VAXCommand("mull2", "r0", "#-1"));
    output->push_back(VAXCommand("incl", "(%hp)"));
    output->push_back(VAXCommand("moval", "(%hp)", "(%ep)"));
    output->push_back(VAXCommand("moval", "r0", "(%hp)"));

    return true;
}

bool VAXCommand::Head(QList<VAXCommand>* output)
{
    output->push_back(VAXCommand("movl", "1(%ep)", "(%ep)"));
    return true;
}

bool VAXCommand::End(QList<VAXCommand>* output)
{
    return true;
}

bool VAXCommand::Begin(QList<VAXCommand>* output)
{
    //mozda dodati name
    output->push_back(VAXCommand(".set", "ep", "0"));
    output->push_back(VAXCommand(".set", "hp", "1000"));
    output->push_back(VAXCommand(".set", "sp", "2000"));
    output->push_back(VAXCommand(".set", "op", "3000"));

    return true;
}

bool VAXCommand::Print(QList<VAXCommand>* output)
{
    output->push_back(VAXCommand("incl", "(%op)"));
    output->push_back(VAXCommand("moval", "x","(%op)"));

    return true;
}

bool VAXCommand::Min(QList<VAXCommand>* output)
{
    output->push_back(VAXCommand("movl", "@(%ep)", "r0"));
    output->push_back(VAXCommand("decl", "(%ep)"));
    output->push_back(VAXCommand("movl", "@(%ep)", "r1"));
    output->push_back(VAXCommand("incl", "(%hp)"));
    output->push_back(VAXCommand("moval", "@(%hp)", "(%ep)"));
    output->push_back(VAXCommand("movl", "minu(r0,r1)", "r0"));
    output->push_back(VAXCommand("movl", "r0", "(%hp)"));

    return true;
}

bool VAXCommand::Max(QList<VAXCommand>* output)
{
    output->push_back(VAXCommand("movl", "@(%ep)", "r0"));
    output->push_back(VAXCommand("decl", "(%ep)"));
    output->push_back(VAXCommand("movl", "@(%ep)", "r1"));
    output->push_back(VAXCommand("incl", "(%hp)"));
    output->push_back(VAXCommand("moval", "@(%hp)", "(%ep)"));
    output->push_back(VAXCommand("movl", "maxu(r0,r1)", "r0"));
    output->push_back(VAXCommand("movl", "r0", "(%hp)"));

    return true;
}

bool VAXCommand::Eval(QList<VAXCommand>* output)
{
    output->push_back(VAXCommand("cmpl", "@(%ep)", "APPLY"));
    output->push_back(VAXCommand("jlss", "eval_apply"));
    output->push_back(VAXCommand("cmpl", "@(%ep)", "FUNCTION"));
    output->push_back(VAXCommand("jlss", "eval_function"));

    return true;
}

bool VAXCommand::Eval2(QList<VAXCommand>* output)
{
    output->push_back(VAXCommand("eval_apply:"));
    output->push_back(VAXCommand("moval", "1(%ep)", "(%sp)"));
    output->push_back(VAXCommand("movl", "(%ep)", "r0"));
    output->push_back(VAXCommand("moval", "#1", "(%ep)"));
    output->push_back(VAXCommand("movl", "r0", "(%ep)"));
    output->push_back(VAXCommand("jsb", "unwind_apply"));
    output->push_back(VAXCommand("ret"));
    output->push_back(VAXCommand("eval_fun:"));
    output->push_back(VAXCommand("cmpl", "@(2(%ep))", "#0"));
    output->push_back(VAXCommand("jlss", "eval_fun0"));
    output->push_back(VAXCommand("ret"));
    output->push_back(VAXCommand("eval_fun0:"));
    output->push_back(VAXCommand("moval", "1(%ep)", "(%sp)"));
    output->push_back(VAXCommand("movl", "(%ep)", "r0"));
    output->push_back(VAXCommand("moval", "#1", "(%ep)"));
    output->push_back(VAXCommand("movl", "r0", "(%ep)"));
    output->push_back(VAXCommand("ret"));

    return true;
}

bool VAXCommand::Unwind(QList<VAXCommand>* output)
{
    output->push_back(VAXCommand("jmp", "unwind_label"));
    return true;
}

bool VAXCommand::Unwind2(QList<VAXCommand>* output)
{
    output->push_back(VAXCommand("unwind:"));
    output->push_back(VAXCommand("cmpl", "@(%ep)", "APPLY"));
    output->push_back(VAXCommand("jlss", "unwind_apply"));
    output->push_back(VAXCommand("cmpl", "@(%ep)", "FUNCTION"));
    output->push_back(VAXCommand("jlss", "unwind_function"));
    output->push_back(VAXCommand("cmpl", "@(%ep)", "CONS"));
    output->push_back(VAXCommand("jlss", "unwind_cons"));
    output->push_back(VAXCommand("cmpl", "@(%ep)", "INTEGER"));
    output->push_back(VAXCommand("jlss", "unwind_integer"));
    output->push_back(VAXCommand("rsb"));
    output->push_back(VAXCommand("unwind_integer:"));
    output->push_back(VAXCommand("movl", "(%ep)", "r0"));
    output->push_back(VAXCommand("moval", "(%sp)", "(%ep)"));
    output->push_back(VAXCommand("incl", "(%ep)"));
    output->push_back(VAXCommand("movl", "r0", "(%ep)"));
    output->push_back(VAXCommand("rsb"));
    output->push_back(VAXCommand("unwind_cons:"));
    output->push_back(VAXCommand("movl", "(%ep)", "r0"));
    output->push_back(VAXCommand("moval", "(%sp)", "(%ep)"));
    output->push_back(VAXCommand("incl", "(%ep)"));
    output->push_back(VAXCommand("movl", "r0", "(%ep)"));
    output->push_back(VAXCommand("rsb"));
    output->push_back(VAXCommand("unwind_apply:"));
    output->push_back(VAXCommand("incl", "(%ep)"));
    output->push_back(VAXCommand("movl", "2(%ep)", "(%ep)"));
    output->push_back(VAXCommand("jsb", "unwind"));
    output->push_back(VAXCommand("rsb"));
    output->push_back(VAXCommand("unwind_function:"));
    output->push_back(VAXCommand("movl", "@(2(%ep))", "r0"));
    output->push_back(VAXCommand("decl", "r0"));
    output->push_back(VAXCommand("cmpl", "(%ep)", "r0"));
    output->push_back(VAXCommand("jlss", "unwind_function_noargs")); //proveriti
    output->push_back(VAXCommand("incl", "r0"));
    output->push_back(VAXCommand("iter:"));
    output->push_back(VAXCommand("decl", "r0"));
    output->push_back(VAXCommand("moval", "(x+1)(%ep)", "r1"));
    output->push_back(VAXCommand("movl", "2(r1)", "x(%ep)"));
    output->push_back(VAXCommand("cmpl", "r0", "#0"));
    output->push_back(VAXCommand("jlss", "iter"));
    output->push_back(VAXCommand("ret"));
    output->push_back(VAXCommand("unwind_function_noargs:"));
    output->push_back(VAXCommand("moval", "#1", "(%ep)"));
    output->push_back(VAXCommand("movl", "(%ep)", "r0"));
    output->push_back(VAXCommand("moval", "(%sp)", "(%ep)"));
    output->push_back(VAXCommand("incl", "(%ep)"));
    output->push_back(VAXCommand("movl", "r0", "(%ep)"));
    output->push_back(VAXCommand("ret"));

    return true;
}

bool VAXCommand::Return(QList<VAXCommand>* output)
{
    output->push_back(VAXCommand("moval", "#1", "(%ep)"));
    output->push_back(VAXCommand("movl", "(%ep)", "r0"));
    output->push_back(VAXCommand("moval", "(%sp)", "(%ep)"));
    output->push_back(VAXCommand("incl", "(%ep)"));
    output->push_back(VAXCommand("movl", "r0", "(%ep)"));

    return true;
}

bool VAXCommand::Label(QList<VAXCommand>* output, QString value)
{
    output->push_back(VAXCommand(value + ":"));
    return true;
}

bool VAXCommand::Jump(QList<VAXCommand>* output, QString value)
{
    output->push_back(VAXCommand("jmp", value));
    return true;
}

bool VAXCommand::JFalse(QList<VAXCommand>* output, QString value)
{
    output->push_back(VAXCommand("jlss", value));
    return true;
}

VAXArgument::VAXArgument(QString value)
    :Value(value)
{
}

VAXArgument::~VAXArgument()
{
}

QString VAXArgument::ToString() const
{
    return this->Value;
}


