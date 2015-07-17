#include "state.h"
#include <iostream>

int State::_maxID = 0;
int State::_cBegin = 0;

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

int State::cBegin()
{
    return _cBegin;
}

void State::setCBegin(int value)
{
    _cBegin = value;
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

int State::commandExists(State& state, QList<GCommand> commands)
{
    int nodeID = state.stack().at(state.stack().length() - 1);

    for(int i = 0; i < commands.length(); i++) {
        if(commands[i].ToString() == QString("GLOBSTART " + state.graph()[nodeID].functionName() + " "
                + QString::number(state.graph()[nodeID].value()) + ";"))
            return i;
    }
    return -1;
}

int State::labelExists(QList<GCommand> commands)
{
    QString labelName = commands[_maxID-1].args()[0]->ToString();

    for(int i = 0; i < commands.length(); i++) {
        if(commands[i].ToString() == QString("LABEL " + labelName + ";"))
            return i;
    }
    return -1;
}

bool State::GetNext(GCommand command, State& nextState, QList<GCommand> commands)
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
        return this->Eval(command, nextState, commands);

    if(command.value() == "EVAL2")
        return this->Eval2(command, nextState, commands);

    if(command.value() == "UNWIND")
        return this->Unwind(command, nextState, commands);

    if(command.value() == "UNWIND2")//treba videti kako radi
        return this->Unwind2(command, nextState, commands);

    if(command.value() == "RETURN")
        return this->Return(command, nextState, commands);

    if(command.value() == "LABEL")
        return this->Label(command, nextState, commands);

    if(command.value() == "JUMP")
        return this->Jump(command, nextState, commands);

    if(command.value() == "JFALSE")
        return this->JFalse(command, nextState, commands);

    return false;
}

bool State::PushInt(GCommand command, State& state)
{
    state = State(*this, command, _maxID);
    state._stack.push_back(state.hp());
    state._ep++;
    state._graph.push_back(GraphNode(state.hp(), GraphNodeType::Integer, command.args()[0]->ToString().toInt()));
    state._hp++;
    state._cBegin++;

    return true;
}

bool State::PushGlobal(GCommand command, State& state)
{
    state = State(*this, command, _maxID);
    state._stack.push_back(state.hp());
    state._ep++;
    state._graph.push_back(GraphNode(state.hp(),0,0,GraphNodeType::Function, command.args()[1]->ToString().toInt(), command.args()[0]->ToString()));
    state._hp++;
    state._cBegin++;

    return true;
}

bool State::GlobStart(GCommand command, State& state)
{
    state = State(*this, command, _maxID);
    state._cBegin++;
    return true;
}

bool State::Push(GCommand command, State& state)
{
    int arg = command.args()[0]->ToString().toInt();

    state = State(*this, command, _maxID);
    state._stack.push_back(state.hp() - arg - 1);
    state._ep++;
    state._cBegin++;

    return true;
}

bool State::Pop(GCommand command, State& state)
{
    int arg = command.args()[0]->ToString().toInt();

    state = State(*this, command, _maxID);
    for(int i = 0; i < arg; i++)
        state._stack.pop();
    state._ep -= arg;
    state._cBegin++;

    return true;
}

bool State::Slide(GCommand command, State& state)
{
    int arg = command.args()[0]->ToString().toInt();

    if(arg < state.stack().length())
    {
        this->_errorMessage = "Error: Invalid command SLIDE";
        return false;
    }
    state = State(*this, command, _maxID);
    state._stack[state.stack().length() - arg - 1] = state.stack().at(state.stack().length() - 1);
    for(int i = 0; i < arg; i++)
        state._stack.pop();
    state._ep -= arg;
    state._cBegin++;

    return true;
}

bool State::Alloc(GCommand command, State& state)
{
    int arg = command.args()[0]->ToString().toInt();

    state = State(*this, command, _maxID);
    for(int i = 0; i < arg; i++)
    {
        state._stack.push_back(maxID() - 1 + i);
        state._ep++;
        state._graph.push_back(GraphNode(state.hp() + i, GraphNodeType::None, 0));
    }
    state._hp += arg;
    state._cBegin++;

    return true;
}

bool State::Update(GCommand command, State& state) //proveriti jos jednom
{
    state = State(*this, command, _maxID);

    int k = command.args()[0]->ToString().toInt();

    GraphNodeType nodeType = state._graph[state.stack().at(state.stack().length() - 1)].type();
    int id = state._graph[state.stack().at(state.stack().length() - k - 1)].id();
    int value = state._graph[state.stack().at(state.stack().length() - 1)].value();
    int idRef1 = state._graph[state.stack().at(state.stack().length() - 1)].idRef1();
    int idRef2 = state._graph[state.stack().at(state.stack().length() - 1)].idRef2();
    int index = state._stack.at(state.stack().length() - k - 1);
    QString name = state._graph[state.stack().at(state.stack().length() - 1 )].functionName();

    state._graph.at(index).~GraphNode();
    state._stack.pop();

    state._graph[index] = GraphNode(id, idRef1, idRef2, nodeType, value, name);
    state._ep--;
    state._cBegin++;

    return true;
}

bool State::Mkap(GCommand command, State& state) //proveriti jos jednom
{
    state = State(*this, command, _maxID);
    int id1 = state.graph()[state.stack().at(state.stack().length() - 1)].id();
    int id2 = state.graph()[state.stack().at(state.stack().length() - 2)].id();

    state._stack.pop();
    state._stack.pop();
    state._stack.push_back(state.hp());


    state._graph.push_back(GraphNode(state.hp(), id1, id2, GraphNodeType::Application, 0, NULL));
    state._hp++;
    state._ep--;
    state._cBegin++;

    return true;
}

bool State::Cons(GCommand command, State& state)
{
    state = State(*this, command, _maxID);
    int id1 = state._graph[state._stack.at(state.stack().length() - 1)].id();
    int id2 = state._graph[state._stack.at(state.stack().length() - 2)].id();

    state._stack.pop();
    state._stack.pop();
    state._stack.push_back(state.hp());

    state._graph.push_back(GraphNode(state.hp(), id1, id2, GraphNodeType::Cons, 0, NULL));
    state._hp ++;
    state._ep --;
    state._cBegin++;
    return true;
}

bool State::Add(GCommand command, State& state)
{
    state = State(*this, command, _maxID);
    GraphNodeType arg1Type = state._graph[state._stack.at(state.stack().length() - 1)].type();
    GraphNodeType arg2Type = state._graph[state._stack.at(state.stack().length() - 2)].type();

    if(arg1Type != GraphNodeType::Integer || arg2Type != GraphNodeType::Integer)
    {
        this->_errorMessage = "Error: ADD instruction on non-INT node.";
        return false;
    }
    int arg1 = state._graph[state._stack.at(state.stack().length() - 1)].value();
    int arg2 = state._graph[state._stack.at(state.stack().length() - 2)].value();

    state._stack.pop();
    state._stack.pop();
    state._stack.push_back(state.hp());

    state._graph.push_back(GraphNode(state.hp(), GraphNodeType::Integer, arg1 + arg2));
    state._hp++;
    state._ep--;
    state._cBegin++;

    return true;
}

bool State::Sub(GCommand command, State& state)
{
    state = State(*this, command, _maxID);
    GraphNodeType arg1Type = state._graph[state._stack.at(state.stack().length() - 1)].type();
    GraphNodeType arg2Type = state._graph[state._stack.at(state.stack().length() - 2)].type();

    if(arg1Type != GraphNodeType::Integer || arg2Type != GraphNodeType::Integer)
    {
        this->_errorMessage = "Error: SUB instruction on non-INT node.";
        return false;
    }
    int arg1 = state._graph[state._stack.at(state.stack().length() - 1)].value();
    int arg2 = state._graph[state._stack.at(state.stack().length() - 2)].value();

    state._stack.pop();
    state._stack.pop();
    state._stack.push_back(state.hp());

    state._graph.push_back(GraphNode(state.hp(), GraphNodeType::Integer, arg1 - arg2));
    state._hp++;
    state._ep--;
    state._cBegin++;

    return true;
}

bool State::Mul(GCommand command, State& state)
{
    state = State(*this, command, _maxID);
    GraphNodeType arg1Type = state._graph[state._stack.at(state.stack().length() - 1)].type();
    GraphNodeType arg2Type = state._graph[state._stack.at(state.stack().length() - 2)].type();

    if(arg1Type != GraphNodeType::Integer || arg2Type != GraphNodeType::Integer)
    {
        this->_errorMessage = "Error: MUL instruction on non-INT node.";
        return false;
    }
    int arg1 = state._graph[state._stack.at(state.stack().length() - 1)].value();
    int arg2 = state._graph[state._stack.at(state.stack().length() - 2)].value();

    state._stack.pop();
    state._stack.pop();
    state._stack.push_back(state.hp());

    state._graph.push_back(GraphNode(state.hp(), GraphNodeType::Integer, arg1 * arg2));
    state._hp++;
    state._ep--;
    state._cBegin++;

    return true;
}

bool State::Div(GCommand command, State& state)
{
    state = State(*this, command, _maxID);
    GraphNodeType arg1Type = state._graph[state._stack.at(state.stack().length() - 1)].type();
    GraphNodeType arg2Type = state._graph[state._stack.at(state.stack().length() - 2)].type();

    if(arg1Type != GraphNodeType::Integer || arg2Type != GraphNodeType::Integer)
    {
        this->_errorMessage = "Error: DIV instruction on non-INT node.";
        return false;
    }

    int arg1 = state._graph[state._stack.at(state.stack().length() - 1)].value();
    int arg2 = state._graph[state._stack.at(state.stack().length() - 2)].value();

    if(arg2 == 0)
    {
        this->_errorMessage = "Error: DIV instruction with zero second argument";
        return false;
    }

    state._stack.pop();
    state._stack.pop();
    state._stack.push_back(state.hp() - 1);

    state._graph.push_back(GraphNode(state.hp(), GraphNodeType::Integer, arg1 / arg2));
    state._hp++;
    state._ep--;
    state._cBegin++;

    return true;
}

bool State::Neg(GCommand command, State& state) //mozda treba da se izbaci i cvor iz grafa, ne samo sa steka
{
    state = State(*this, command, _maxID);
    GraphNodeType argType = state._graph[state._stack.at(state.stack().length() - 1)].type();

    if(argType != GraphNodeType::Integer)
    {
        this->_errorMessage = "Error: NEG instruction on non-INT node.";
        return false;
    }

    int arg = state._graph[state._stack.at(state.stack().length() - 1)].value();

    state._stack[state.stack().length() - 1] = state.hp();

    state._graph.push_back(GraphNode(state.hp(), GraphNodeType::Integer, -arg));
    state._hp++;
    state._cBegin++;

    return true;
}

bool State::Head(GCommand command, State& state) //mozda treba da se izbaci i cvor iz grafa
{
    state = State(*this, command, _maxID);
    GraphNodeType argType = state._graph[state._stack.at(state.stack().length() - 1)].type();

    if(argType != GraphNodeType::Cons)
    {
        this->_errorMessage = "Error: HEAD instruction on non-CONST node.";
        return false;
    }

    state._stack[state.stack().length() - 1] = state._graph[state.stack().at(state.stack().length() - 1)].idRef1();
    state._cBegin++;

    return true;
}

bool State::End(GCommand command, State& state)
{
    state = State(*this, command, _maxID);
    state._cBegin++;
    return true;
}

bool State::Begin(GCommand command, State& state)
{
    state = State(*this, command, _maxID);
    state._stack.clear();
    state._graph.clear();
    state._dump.clear();
    state._ep = 0;
    state._sp = 0;
    state._hp = 0;
    state._cBegin++;

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
    state._ep --;
    state._cBegin++;

    return true;
}

bool State::Min(GCommand command, State& state)
{
    state = State(*this, command, _maxID);
    GraphNodeType arg1Type = state.graph()[state.stack().at(state.stack().length() - 1)].type();
    GraphNodeType arg2Type = state.graph()[state.stack().at(state.stack().length() - 2)].type();

    if(arg1Type != GraphNodeType::Integer || arg2Type != GraphNodeType::Integer)
    {
        this->_errorMessage = "Error: MIN instruction on non-INT node.";
        return false;
    }
    int arg1 = state.graph()[state.stack().at(state.stack().length() - 1)].value();
    int arg2 = state.graph()[state.stack().at(state.stack().length() - 2)].value();

    state._stack.pop();
    state._stack.pop();
    state._stack.push_back(state.hp());

    state._graph.push_back(GraphNode(state.hp(), GraphNodeType::Integer, arg1 < arg2 ? arg1 : arg2));
    state._hp++;
    state._ep--;

    return true;
}

bool State::Max(GCommand command, State& state)
{
    state = State(*this, command, _maxID);
    GraphNodeType arg1Type = state.graph()[state.stack().at(state.stack().length() - 1)].type();
    GraphNodeType arg2Type = state.graph()[state.stack().at(state.stack().length() - 2)].type();

    if(arg1Type != GraphNodeType::Integer || arg2Type != GraphNodeType::Integer)
    {
        this->_errorMessage = "Error: MAX instruction on non-INT node.";
        return false;
    }
    int arg1 = state.graph()[state.stack().at(state.stack().length() - 1)].value();
    int arg2 = state.graph()[state.stack().at(state.stack().length() - 2)].value();

    state._stack.pop();
    state._stack.pop();
    state._stack.push_back(state.hp());

    state._graph.push_back(GraphNode(state.hp(), GraphNodeType::Integer, arg1 > arg2 ? arg1 : arg2));
    state._hp++;
    state._ep--;

    return true;
}

bool State::Eval(GCommand command, State& state, QList<GCommand> commands)
{
    state = State(*this, command, _maxID);
    GraphNodeType argType = state.graph()[state.stack().at(state.stack().length() - 1)].type();

   /* if(argType == GraphNodeType::Cons || argType == GraphNodeType::Integer)
    {
        state._cBegin++;
        return true;
    }

    if(argType == GraphNodeType::Application)
    {
        DumpNode dump;
        QVector<int> stack;
        QVector<QString> code;
        for(int i = 0; i < state.stack().length(); i++)
            stack.push_back(state.stack().at(i));
        for(int i = 0; i < state.stack().length(); i++)
            state._stack.pop();
        for(int i = cBegin(); i < commands.length(); i++)
            code.push_back(commands[i].ToString());  //proveriti dump

        state._cBegin = 0; //nije uradjeno
        return true;
    }

    if(argType == GraphNodeType::Function)
    {
        int nodeID = state.stack().at(state.stack().length() - 1);
        int index = commandExists(state, commands);

        DumpNode dump;
        QVector<int> stack;
        QVector<QString> code;
        for(int i = 0; i < state.stack().length(); i++)
            stack.push_back(state.stack().at(i));
        for(int i = 0; i < state.stack().length(); i++)
            state._stack.pop();
        for(int i = cBegin(); i < commands.length(); i++)
            code.push_back(commands[i].ToString());  //proveriti dump

        state._stack.push_back(stack.at(stack.length() - 1));

        dump = DumpNode(stack, code);
        state._dump.push_back(dump);

        state._cBegin = index;  // ovde treba da se preusmeri da izvrsava ono sto se nalazi u commands[index]

        return true;
    }
    else
    {
        state._cBegin++;
        return true;
    }
*/
    return true;
}

bool State::Eval2(GCommand command, State& state, QList<GCommand> commands)
{
    return true;
}

bool State::Unwind(GCommand command, State& state, QList<GCommand> commands)
{

    return true;
}

bool State::Unwind2(GCommand command, State& state, QList<GCommand> commands)
{
    return true;
}

bool State::Return(GCommand command, State& state, QList<GCommand> commands)
{

    return true;
}

bool State::Label(GCommand command, State& state, QList<GCommand> commands)
{
    state = State(*this, command, _maxID);

    //state._cBegin++;
    return true;
}


bool State::Jump(GCommand command, State& state, QList<GCommand> commands)
{
    //state = State(*this, command, _maxID);
    int index = labelExists(commands);

    if(index == -1)
    {
        this->_errorMessage = "Error: No appropriate label for JUMP instruction.";
        return false;
    }

    state = State(*this, commands[index], index);  //index je pozicija labele na koju treba da se skoci
                                                   //treba da se ode na to stanje, ali ovo ne radi ovako
    return true;
}

bool State::JFalse(GCommand command, State& state, QList<GCommand> commands)
{
    /*GraphNodeType argType = state._graph[state._stack.at(state._ep)].type();

    if(argType != GraphNodeType::Integer)
    {
        this->_errorMessage = "Error: JFALSE instruction on non-INT node.";
        return false;
    }
    */
    return true;
}

