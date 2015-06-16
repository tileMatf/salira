#include "vaxcommand.h"

VAXCommand::VAXCommand(QString command, QString arg1, QString arg2)
{
    this->_value = command;
    if(arg1.length() > 0)
        this->_args.push_back(arg1);
    if(arg2.length() > 0)
        this->_args.push_back(arg2);
    this->_valid = true;
}

VAXCommand::~VAXCommand()
{
    this->_value = "";
    this->_args.clear();
    this->_valid = false;
}

QString VAXCommand::ToString() const
{
    QString retValue;

    if(this->_value.length() > 0)
    {
        retValue += this->_value;

        if(this->_args.length() > 0)
            retValue += " ";

        int i = 1;
        foreach (VAXArgument argument, this->_args)
            retValue += argument.ToString() + (i++ < this->_args.length() ? "," : "");
    }

    return retValue;
}

bool VAXCommand::GetCommands(GCommand input, QList<VAXCommand>* output)
{
    if(input.value() == "")
        return true;

    if(input.value() == "PUSHINT")
        return PushInt(output, input.args()[0]->ToString());

    if(input.value() == "PUSHGLOBAL")
        return PushGlobal(output, input.args()[0]->ToString());

    if(input.value() == "GLOBSTART")
        return GlobStart(output, input.args()[0]->ToString());

    if(input.value() == "PUSH")
        return Push(output,input.args()[0]->ToString());

    if(input.value() == "POP")
        return Pop(output, input.args()[0]->ToString());

    if(input.value() == "SLIDE")
        return Slide(output, input.args()[0]->ToString());

    if(input.value() == "ALLOC")
        return Alloc(output, (int)input.args()[0]->ToString().toInt());

    if(input.value() == "UPDATE")
        return Update(output, input.args()[0]->ToString());

    if(input.value() == "MKAP")
        return Mkap(output);

    if(input.value() == "CONS")
        return Cons(output);

    if(input.value() == "ADD")
        return Add(output);

    if(input.value() == "SUB")
        return Sub(output);

    if(input.value() == "MUL")
        return Mul(output);

    if(input.value() == "DIV")
        return Div(output);

    if(input.value() == "NEG")
        return Neg(output);

    if(input.value() == "HEAD")
        return Head(output);

    if(input.value() == "END")
        return End(output);

    if(input.value() == "BEGIN")
        return Begin(output);

    if(input.value() == "PRINT")
        return Print(output);

    if(input.value() == "MIN")
        return Min(output);

    if(input.value() == "MAX")
        return Max(output);

    if(input.value() == "EVAL")
        return Eval(output);

    if(input.value() == "EVAL2")
        return Eval2(output);

    if(input.value() == "UNWIND")
        return Unwind(output);

    if(input.value() == "UNWIND2")//treba videti kako radi
        return Unwind2(output);

    if(input.value() == "RETURN")
        return Return(output);

    if(input.value() == "LABEL")
        return Label(output, input.args()[0]->ToString());

    if(input.value() == "JUMP")
        return Jump(output, input.args()[0]->ToString());

    if(input.value() == "JFALSE")
        return JFalse(output, input.args()[0]->ToString());

    return false;
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
    :_value(value)
{
}

VAXArgument::~VAXArgument()
{
}

QString VAXArgument::ToString() const
{
    return this->_value;
}


