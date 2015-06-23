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

State::State(const State& state, GCommand command, int id)
    :_command(command), _id(id)
{
    this->_ep = state._ep;
    this->_hp = state._hp;
    this->_sp = state._sp;
    this->_op = state._op;
    this->_stack = QStack<int>(state._stack);
    this->_graph = QVector<GraphNode>(state._graph);
    this->_dump = QVector<DumpNode>(state._dump);
    this->_output = QVector<QString>(state._output);
}

State::~State()
{
    this->_stack.clear();
    this->_graph.clear();
    this->_dump.clear();
    this->_output.clear();
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

QVector<QString> State::output()
{
    return this->_output;
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
    state = State(*this, command, _maxID);
    state._stack.push_back((state._hp)++);
    state._ep++;
    state._graph.push_back(GraphNode(state._hp, GraphNodeType::Integer, command.args()[0]->ToString().toInt()));

    return true;
}

bool State::PushGlobal(GCommand command, State& state)
{
    state = State(*this, command, _maxID);
    state._stack.push_back((state._hp)++);
    state._ep++;
    state._graph.push_back(GraphNode(state._hp, GraphNodeType::Function, command.args()[1]->ToString().toInt()));

    return true;
}

bool State::GlobStart(GCommand command, State& state)
{

    return true;
}

bool State::Push(GCommand command, State& state)
{
    int arg = command.args()[0]->ToString().toInt();

    state = State(*this, command, _maxID);
    state._stack.push_back(state._ep - arg - 1);
    state._ep++;

    return true;
}

bool State::Pop(GCommand command, State& state)
{
    int arg = command.args()[0]->ToString().toInt();

    state = State(*this, command, _maxID);
    state._ep -= arg;

    return true;
}

bool State::Slide(GCommand command, State& state)
{
    int arg = command.args()[0]->ToString().toInt();

    state = State(*this, command, _maxID);
    state._stack[state._ep - arg] = state._stack.at(state._ep);
    state._ep -= arg;

    return true;
}

bool State::Alloc(GCommand command, State& state)
{
    int arg = command.args()[0]->ToString().toInt();

    for(int i = 0; i < arg; i++)
    {
        state = State(*this, command, _maxID++);
        state._stack.push_back((state._hp)++);
        state._ep++;
        state._graph.push_back(GraphNode(GraphNodeType::None));
    }
    return true;
}

bool State::Update(GCommand command, State& state)
{
    int k = command.args()[0]->ToString().toInt();

    GraphNodeType nodeType = state._graph[state._stack.at(state._ep)].type();
    int id = state._graph[state._stack.at(state._ep - k)].id();
    int value = state._graph[state._stack.at(state._ep)].value();

    state = State(*this, command, _maxID);
    state._graph.at(k).~GraphNode();

    QVector<GraphNode>::iterator it = state._graph.begin() + k;

    state._graph.insert(it, GraphNode(id, nodeType, value));
    state._ep--;

    return true;
}

bool State::Mkap(GCommand command, State& state)
{
    state = State(*this, command, _maxID);
    int id1 = state._graph[state._stack.at(state._ep)].id();
    int id2 = state._graph[state._stack.at(state._ep-1)].id();

    state._graph.push_back(GraphNode(state._hp, id1, id2, GraphNodeType::Application, 0));
    state._hp++;
    state._ep--;
    state._stack[state._ep] = state._hp;

    return true;
}

bool State::Cons(GCommand command, State& state)
{
    state = State(*this, command, _maxID);
    int id1 = state._graph[state._stack.at(state._ep)].id();
    int id2 = state._graph[state._stack.at(state._ep-1)].id();

    state._graph.push_back(GraphNode(state._hp, id1, id2, GraphNodeType::Cons, 0));
    state._hp ++;
    state._ep --;
    state._stack[state._ep] = state._hp;

    return true;
}

bool State::Add(GCommand command, State& state)
{
    GraphNodeType arg1Type = state._graph[state._stack.at(state._ep)].type();
    GraphNodeType arg2Type = state._graph[state._stack.at(state._ep - 1)].type();

    if(arg1Type != GraphNodeType::Integer || arg2Type != GraphNodeType::Integer)
    {
        this->_errorMessage = "Error: ADD instruction on non-INT node.";
        return false;
    }
    int arg1 = state._graph[state._stack.at(state._ep)].value();
    int arg2 = state._graph[state._stack.at(state._ep - 1)].value();

    state._graph.push_back(GraphNode(state._hp, GraphNodeType::Integer, arg1 + arg2));
    state._hp++;
    state._ep--;
    state._stack[state._ep] = state._hp;

    return true;
}

bool State::Sub(GCommand command, State& state)
{
    GraphNodeType arg1Type = state._graph[state._stack.at(state._ep)].type();
    GraphNodeType arg2Type = state._graph[state._stack.at(state._ep - 1)].type();

    if(arg1Type != GraphNodeType::Integer || arg2Type != GraphNodeType::Integer)
    {
        this->_errorMessage = "Error: SUB instruction on non-INT node.";
        return false;
    }
    int arg1 = state._graph[state._stack.at(state._ep)].value();
    int arg2 = state._graph[state._stack.at(state._ep - 1)].value();

    state._graph.push_back(GraphNode(state._hp, GraphNodeType::Integer, arg1 - arg2));
    state._hp++;
    state._ep--;
    state._stack[state._ep] = state._hp;

    return true;
}

bool State::Mul(GCommand command, State& state)
{
    GraphNodeType arg1Type = state._graph[state._stack.at(state._ep)].type();
    GraphNodeType arg2Type = state._graph[state._stack.at(state._ep - 1)].type();

    if(arg1Type != GraphNodeType::Integer || arg2Type != GraphNodeType::Integer)
    {
        this->_errorMessage = "Error: MUL instruction on non-INT node.";
        return false;
    }
    int arg1 = state._graph[state._stack.at(state._ep)].value();
    int arg2 = state._graph[state._stack.at(state._ep - 1)].value();

    state._graph.push_back(GraphNode(state._hp, GraphNodeType::Integer, arg1 * arg2));
    state._hp++;
    state._ep--;
    state._stack[state._ep] = state._hp;

    return true;
}

bool State::Div(GCommand command, State& state)
{
    GraphNodeType arg1Type = state._graph[state._stack.at(state._ep)].type();
    GraphNodeType arg2Type = state._graph[state._stack.at(state._ep - 1)].type();

    if(arg1Type != GraphNodeType::Integer || arg2Type != GraphNodeType::Integer)
    {
        this->_errorMessage = "Error: DIV instruction on non-INT node.";
        return false;
    }

    int arg1 = state._graph[state._stack.at(state._ep)].value();
    int arg2 = state._graph[state._stack.at(state._ep - 1)].value();

    if(arg2 == 0)
    {
        this->_errorMessage = "Error: DIV instruction with zero second argument";
        return false;
    }

    state._graph.push_back(GraphNode(state._hp, GraphNodeType::Integer, arg1 / arg2));
    state._hp++;
    state._ep--;
    state._stack[state._ep] = state._hp;

    return true;
}

bool State::Neg(GCommand command, State& state)
{
    GraphNodeType argType = state._graph[state._stack.at(state._ep)].type();

    if(argType != GraphNodeType::Integer)
    {
        this->_errorMessage = "Error: NEG instruction on non-INT node.";
        return false;
    }

    int arg = state._graph[state._stack.at(state._ep)].value();

    state._graph.push_back(GraphNode(state._hp, GraphNodeType::Integer, -arg));
    state._hp++;
    state._stack[state._ep] = state._hp;

    return true;
}

bool State::Head(GCommand command, State& state)
{
    GraphNodeType argType = state._graph[state._stack.at(state._ep)].type();

    if(argType != GraphNodeType::Cons)
    {
        this->_errorMessage = "Error: HEAD instruction on non-CONST node.";
        return false;
    }

    state._stack[state.ep()] = state._graph[state.stack().at(state.ep())].idRef1();

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
        this->_errorMessage = "Error: PRINT instruction on non-INT node";
        return false;
    }

    state = State(*this, state._command, _maxID);
    state._output.push_back(QString::number(state._graph[state._stack.pop()].value()));

    return true;
}

bool State::Min(GCommand command, State& state)
{
    GraphNodeType arg1Type = state._graph[state._stack.at(state._ep)].type();
    GraphNodeType arg2Type = state._graph[state._stack.at(state._ep - 1)].type();

    if(arg1Type != GraphNodeType::Integer || arg2Type != GraphNodeType::Integer)
    {
        this->_errorMessage = "Error: MIN instruction on non-INT node.";
        return false;
    }
    int arg1 = state._graph[state._stack.at(state._ep)].value();
    int arg2 = state._graph[state._stack.at(state._ep - 1)].value();

    state._graph.push_back(GraphNode(state._hp, GraphNodeType::Integer, arg1 < arg2 ? arg1 : arg2));
    state._hp++;
    state._ep--;
    state._stack[state._ep] = state._hp;

    return true;
}

bool State::Max(GCommand command, State& state)
{
    GraphNodeType arg1Type = state._graph[state._stack.at(state._ep)].type();
    GraphNodeType arg2Type = state._graph[state._stack.at(state._ep - 1)].type();

    if(arg1Type != GraphNodeType::Integer || arg2Type != GraphNodeType::Integer)
    {
        this->_errorMessage = "Error: MIN instruction on non-INT node.";
        return false;
    }
    int arg1 = state._graph[state._stack.at(state._ep)].value();
    int arg2 = state._graph[state._stack.at(state._ep - 1)].value();

    state._graph.push_back(GraphNode(state._hp, GraphNodeType::Integer, arg1 > arg2 ? arg1 : arg2));
    state._hp++;
    state._ep--;
    state._stack[state._ep] = state._hp;

    return true;
}

bool State::Eval(GCommand command, State& state)
{
    /*GraphNodeType argType = state._graph[state._stack.at(state._ep)].type();

    if(argType == GraphNodeType::Integer || argType == GraphNodeType::Cons)
        return true;
    if(argType == GraphNodeType::Application)
    {
        state._sp ++;
        DumpNode dump = new DumpNode();
        for(int i = 1; i < state._ep; i++)
            dump.stack().push_back(state._stack.at(i));

        state._dump.push_back(DumpNode());
    }*/

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
    /*GraphNodeType argType = state._graph[state._stack.at(state._ep)].type();

    if(argType != GraphNodeType::Integer)
    {
        this->_errorMessage = "Error: JFALSE instruction on non-INT node.";
        return false;
    }
    //negde mora da se cuva ceo kod da bi moglo da se se proverava da li postoji npr. trazena labela
    */

    return true;
}

