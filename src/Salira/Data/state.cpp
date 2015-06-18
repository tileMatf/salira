#include "state.h"

int State::_maxID = -1;

State::State()
    :_command(GCommand(""))
{
    this->_id = ++_maxID;
    this->_ep = 0;
    this->_hp = 0;
    this->_sp = 0;
    this->_op = 0;
}


State::State(int ep, int hp, int sp, int op, QStack<int> stack, QVector<GraphNode> graph, QVector<DumpNode> dump, GCommand command)
    :_command(command)
{
    this->_id = ++_maxID;
    this->_ep = ep;
    this->_hp = hp;
    this->_sp = sp;
    this->_op = op;
    this->_stack = stack;
    this->_graph = graph;
    this->_dump = dump;
    this->_command = command;
}

State::~State()
{
    this->_stack.clear();
    this->_graph.clear();
    this->_dump.clear();
}

int State::maxID()
{
    return _maxID;
}

void State::setMaxID(int value)
{
    _maxID = value;
}

int State::id()
{
    return this->_id;
}

int State::ep()
{
    return this->_ep;
}

int State::hp()
{
    return this->_hp;
}

int State::sp()
{
    return this->_sp;
}

int State::op()
{
    return this->_op;
}

QStack<int> State::stack()
{
    return this->_stack;
}

QVector<GraphNode> State::graph()
{
    return this->_graph;
}

QVector<DumpNode> State::dump()
{
    return this->_dump;
}

GCommand State::command()
{
    return this->_command;
}

QString State::errorMessage()
{
    return this->_errorMessage;
}

bool State::GetNext(GCommand command, State* nextState)
{
    nextState->_command = command;

    if(command.value() == "")
        return true;

    if(command.value() == "PUSHINT")
        return PushInt(nextState);

    if(command.value() == "PUSHGLOBAL")
        return PushGlobal(nextState);

    if(command.value() == "GLOBSTART")
        return GlobStart(nextState);
    if(command.value() == "PUSH")
        return Push(nextState);

    if(command.value() == "POP")
        return Pop(nextState);

    if(command.value() == "SLIDE")
        return Slide(nextState);

    if(command.value() == "ALLOC")
        return Alloc(nextState);

    if(command.value() == "UPDATE")
        return Update(nextState);

    if(command.value() == "MKAP")
        return Mkap(nextState);

    if(command.value() == "CONS")
        return Cons(nextState);

    if(command.value() == "ADD")
        return Add(nextState);

    if(command.value() == "SUB")
        return Sub(nextState);

    if(command.value() == "MUL")
        return Mul(nextState);

    if(command.value() == "DIV")
        return Div(nextState);

    if(command.value() == "NEG")
        return Neg(nextState);

    if(command.value() == "HEAD")
        return Head(nextState);

    if(command.value() == "END")
        return End(nextState);

    if(command.value() == "BEGIN")
        return Begin(nextState);

    if(command.value() == "PRINT")
        return Print(nextState);

    if(command.value() == "MIN")
        return Min(nextState);

    if(command.value() == "MAX")
        return Max(nextState);

    if(command.value() == "EVAL")
        return Eval(nextState);

    if(command.value() == "EVAL2")
        return Eval2(nextState);

    if(command.value() == "UNWIND")
        return Unwind(nextState);

    if(command.value() == "UNWIND2")//treba videti kako radi
        return Unwind2(nextState);

    if(command.value() == "RETURN")
        return Return(nextState);

    if(command.value() == "LABEL")
        return Label(nextState);

    if(command.value() == "JUMP")
        return Jump(nextState);

    if(command.value() == "JFALSE")
        return JFalse(nextState);

    return false;
}

bool State::PushInt(State* state)
{
    return true;
}

bool State::PushGlobal(State* state)
{
    return true;
}

bool State::GlobStart(State* state)
{
    return true;
}

bool State::Push(State* state)
{
    return true;
}

bool State::Pop(State* state)
{
    return true;
}

bool State::Slide(State* state)
{
    return true;
}

bool State::Alloc(State* state)
{
    return true;
}

bool State::Update(State* state)
{
    return true;
}

bool State::Mkap(State* state)
{
    return true;
}

bool State::Cons(State* state)
{
    return true;
}

bool State::Add(State* state)
{
    return true;
}

bool State::Sub(State* state)
{
    return true;
}

bool State::Mul(State* state)
{
    return true;
}

bool State::Div(State* state)
{
    return true;
}

bool State::Neg(State* state)
{
    return true;
}

bool State::Head(State* state)
{
    return true;
}

bool State::End(State* state)
{
    return true;
}

bool State::Begin(State* state)
{
    return true;
}

bool State::Print(State* state)
{
    return true;
}

bool State::Min(State* state)
{
    return true;
}

bool State::Max(State* state)
{
    return true;
}

bool State::Eval(State* state)
{
    return true;
}

bool State::Eval2(State* state)
{
    return true;
}

bool State::Unwind(State* state)
{
    return true;
}

bool State::Unwind2(State* state)
{
    return true;
}

bool State::Return(State* state)
{
    return true;
}

bool State::Label(State* state)
{
    return true;
}

bool State::Jump(State* state)
{
    return true;
}

bool State::JFalse(State* state)
{
    return true;
}

