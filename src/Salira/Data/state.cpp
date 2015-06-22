#include "state.h"

int State::_maxID = 0;

State::State()
    :_command(GCommand(""))
{
    this->_ep = 0;
    this->_hp = 0;
    this->_sp = 0;
    this->_op = 0;
}

State::State(int id)
    :_command(GCommand(""))
{
    this->_id = id;
    this->_ep = 0;
    this->_hp = 0;
    this->_sp = 0;
    this->_op = 0;
}

State::State(const State& state)
    :_command(state._command)
{
    this->_id = state._id;
    this->_ep = state._ep;
    this->_hp = state._hp;
    this->_sp = state._sp;
    this->_op = state._op;
    this->_stack = QStack<int>(state._stack);
    this->_graph = QVector<GraphNode>(state._graph);
    this->_dump = QVector<DumpNode>(state._dump);
    this->_command = state._command;
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

bool State::GetNext(GCommand command, State& nextState)
{
    this->_maxID++;
    if(command.value() == "")
        return true;

    if(command.value() == "PUSHINT")
        return this->PushInt(command, nextState);

    if(command.value() == "PUSHGLOBAL")
        return this->PushGlobal(command, nextState);

    if(command.value() == "GLOBSTART")
        return this->GlobStart(command, nextState);

    if(command.value() == "PUSH")
        return this->Push(command, nextState);

    if(command.value() == "POP")
        return this->Pop(command, nextState);

    if(command.value() == "SLIDE")
        return this->Slide(command, nextState);

    if(command.value() == "ALLOC")
        return this->Alloc(command, nextState);

    if(command.value() == "UPDATE")
        return this->Update(command, nextState);

    if(command.value() == "MKAP")
        return this->Mkap(command, nextState);

    if(command.value() == "CONS")
        return this->Cons(command, nextState);

    if(command.value() == "ADD")
        return this->Add(command, nextState);

    if(command.value() == "SUB")
        return this->Sub(command, nextState);

    if(command.value() == "MUL")
        return this->Mul(command, nextState);

    if(command.value() == "DIV")
        return this->Div(command, nextState);

    if(command.value() == "NEG")
        return this->Neg(command, nextState);

    if(command.value() == "HEAD")
        return this->Head(command, nextState);

    if(command.value() == "END")
        return this->End(command, nextState);

    if(command.value() == "BEGIN")
        return this->Begin(command, nextState);

    if(command.value() == "PRINT")
        return this->Print(command, nextState);

    if(command.value() == "MIN")
        return Min(command, nextState);

    if(command.value() == "MAX")
        return this->Max(command, nextState);

    if(command.value() == "EVAL")
        return this->Eval(command, nextState);

    if(command.value() == "EVAL2")
        return this->Eval2(command, nextState);

    if(command.value() == "UNWIND")
        return this->Unwind(command, nextState);

    if(command.value() == "UNWIND2")//treba videti kako radi
        return this->Unwind2(command, nextState);

    if(command.value() == "RETURN")
        return this->Return(command, nextState);

    if(command.value() == "LABEL")
        return this->Label(command, nextState);

    if(command.value() == "JUMP")
        return this->Jump(command, nextState);

    if(command.value() == "JFALSE")
        return this->JFalse(command, nextState);

    return false;
}

bool State::PushInt(GCommand command, State& state)
{
    state = State(*this);
    state._command = command;
    state._id = _maxID;
    state._stack.push_back((state._hp)++);
    state._graph.push_back(GraphNode(state._hp, GraphNodeType::Integer, command.args()[0]->ToString().toInt()));

    return true;
}

bool State::PushGlobal(GCommand command, State& state)
{
    return true;
}

bool State::GlobStart(GCommand command, State& state)
{
    return true;
}

bool State::Push(GCommand command, State& state)
{
    return true;
}

bool State::Pop(GCommand command, State& state)
{
    return true;
}

bool State::Slide(GCommand command, State& state)
{
    return true;
}

bool State::Alloc(GCommand command, State& state)
{
    return true;
}

bool State::Update(GCommand command, State& state)
{
    return true;
}

bool State::Mkap(GCommand command, State& state)
{
    return true;
}

bool State::Cons(GCommand command, State& state)
{
    return true;
}

bool State::Add(GCommand command, State& state)
{
    return true;
}

bool State::Sub(GCommand command, State& state)
{
    return true;
}

bool State::Mul(GCommand command, State& state)
{
    return true;
}

bool State::Div(GCommand command, State& state)
{
    return true;
}

bool State::Neg(GCommand command, State& state)
{
    return true;
}

bool State::Head(GCommand command, State& state)
{
    return true;
}

bool State::End(GCommand command, State& state)
{
    return true;
}

bool State::Begin(GCommand command, State& state)
{
    return true;
}

bool State::Print(GCommand command, State& state)
{
    if(this->graph()[this->_stack[this->_stack.length() - 1]].type() != GraphNodeType::Integer)
    {
        this->_errorMessage = "Nije int!";
        return false;
    }

    state = State(*this);
    state._command = command;
    state._id = _maxID;
    state._stack.pop();

    return true;
}

bool State::Min(GCommand command, State& state)
{
    return true;
}

bool State::Max(GCommand command, State& state)
{
    return true;
}

bool State::Eval(GCommand command, State& state)
{
    return true;
}

bool State::Eval2(GCommand command, State& state)
{
    return true;
}

bool State::Unwind(GCommand command, State& state)
{
    return true;
}

bool State::Unwind2(GCommand command, State& state)
{
    return true;
}

bool State::Return(GCommand command, State& state)
{
    return true;
}

bool State::Label(GCommand command, State& state)
{
    return true;
}

bool State::Jump(GCommand command, State& state)
{
    return true;
}

bool State::JFalse(GCommand command, State& state)
{
    return true;
}

