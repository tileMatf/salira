#include "state.h"
#include <iostream>

int State::_maxID = 0;
int State::_cBegin = 0;
QStack<unsigned> State::_returnTo;

State::State()
    :_command(GCommand("")), _ep(0), _hp(0), _sp(0), _op(0), _currentLineNumber(0)
{
}

State::State(int id)
    :_command(GCommand("")), _id(id), _ep(0), _hp(0), _sp(0), _op(0), _currentLineNumber(0)
{
}

State::State(const State& state, GCommand command, int id, int jumpTo)
    :_command(command), _id(id), _ep(state._ep), _hp(state._hp), _sp(state._sp), _op(state._op)
{
    if(jumpTo > 0)
        this->_currentLineNumber = jumpTo;
    else
        this->_currentLineNumber = state._currentLineNumber + 1;

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

QStack<unsigned> State::returnTo()
{
    return State::_returnTo;
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

int State::currentLineNumber()
{
    return this->_currentLineNumber;
}

int State::functionExists(QString functionName, QList<GCommand> commands)
{
    for(int i = 0; i < commands.length(); i++) {
        if(commands[i].args().length() > 0)
            if(QString(commands[i].value() + " " + commands[i].args()[0]->ToString()) ==
                    QString("GLOBSTART " + functionName))
            return i;
    }
    return -1;
}

int State::functionExistsWithZero(QString functionName, QList<GCommand> commands)
{
    for(int i = 0; i < commands.length(); i++) {
        if(commands[i].args().length() > 0)
            if(commands[i].ToString() == QString("GLOBSTART " + functionName + " 0;"))
            return i;
    }
    return -1;
}

int State::labelExists(QList<GCommand> commands, QString labelName)
{
    for(int i = 0; i < commands.length(); i++) {
        if(commands[i].ToString() == QString("LABEL " + labelName + ";"))
            return i;
    }
    return -1;
}

int State::findPrint(QList<GCommand> commands)
{
    for(int i = 0; i < commands.length(); i++) {
        if(commands[i].ToString() == QString("PRINT;"))
            return i;
    }
    return -1;
}

bool State::GetNext(GCommand command, State& nextState, QList<GCommand> commands, int lineNumber)
{
    this->_maxID++;
    if(command.value() == "")
    {
        nextState = State(*this, command, _maxID, lineNumber);
        return true;
    }

    if(command.value() == "PUSHINT")
        return this->PushInt(command, nextState, lineNumber);

    if(command.value() == "PUSHGLOBAL")
        return this->PushGlobal(command, nextState, lineNumber);

    if(command.value() == "GLOBSTART")
        return this->GlobStart(command, nextState, lineNumber);

    if(command.value() == "PUSH")
        return this->Push(command, nextState, lineNumber);

    if(command.value() == "POP")
        return this->Pop(command, nextState, lineNumber);

    if(command.value() == "SLIDE")
        return this->Slide(command, nextState, lineNumber);

    if(command.value() == "ALLOC")
        return this->Alloc(command, nextState, lineNumber);

    if(command.value() == "UPDATE")
        return this->Update(command, nextState, lineNumber);

    if(command.value() == "MKAP")
        return this->Mkap(command, nextState, lineNumber);

    if(command.value() == "CONS")
        return this->Cons(command, nextState, lineNumber);

    if(command.value() == "ADD")
        return this->Add(command, nextState, lineNumber);

    if(command.value() == "SUB")
        return this->Sub(command, nextState, lineNumber);

    if(command.value() == "MUL")
        return this->Mul(command, nextState, lineNumber);

    if(command.value() == "DIV")
        return this->Div(command, nextState, lineNumber);

    if(command.value() == "NEG")
        return this->Neg(command, nextState, lineNumber);

    if(command.value() == "HEAD")
        return this->Head(command, nextState, lineNumber);

    if(command.value() == "END")
        return this->End(command, nextState, lineNumber);

    if(command.value() == "BEGIN")
        return this->Begin(command, nextState, lineNumber);

    if(command.value() == "PRINT")
        return this->Print(command, nextState, lineNumber);

    if(command.value() == "MIN")
        return Min(command, nextState, lineNumber);

    if(command.value() == "MAX")
        return this->Max(command, nextState, lineNumber);

    if(command.value() == "EVAL")
        return this->Eval(command, nextState, commands, lineNumber);

    if(command.value() == "UNWIND")
        return this->Unwind(command, nextState, commands, lineNumber);

    if(command.value() == "RETURN")
        return this->Return(command, nextState, commands, lineNumber);

    if(command.value() == "LABEL")
        return this->Label(command, nextState, commands, lineNumber);

    if(command.value() == "JUMP")
        return this->Jump(command, nextState, commands, lineNumber);

    if(command.value() == "JFALSE")
        return this->JFalse(command, nextState, commands, lineNumber);

    return false;
}

bool State::PushInt(GCommand command, State& state, int lineNumber)
{
    state = State(*this, command, _maxID, lineNumber + 1);
    state._stack.push_back(state.hp());
    state._graph.push_back(GraphNode(state.hp(), GraphNodeType::Integer, command.args()[0]->ToString().toInt()));
    state._hp++;

    return true;
}

bool State::PushGlobal(GCommand command, State& state, int lineNumber)
{
    state = State(*this, command, _maxID, lineNumber + 1);
    state._stack.push_back(state.hp());
    state._graph.push_back(GraphNode(state.hp(),0,0,GraphNodeType::Function, command.args()[1]->ToString().toInt(), command.args()[0]->ToString()));
    state._hp++;

    return true;
}

bool State::GlobStart(GCommand command, State& state, int lineNumber)
{
    state = State(*this, command, _maxID, lineNumber + 1);
    return true;
}

bool State::Push(GCommand command, State& state, int lineNumber)
{
    int arg = command.args()[0]->ToString().toInt();

    state = State(*this, command, _maxID, lineNumber + 1);
    state._stack.push_back(state.hp() - arg - 1);

    return true;
}

bool State::Pop(GCommand command, State& state, int lineNumber)
{
    int arg = command.args()[0]->ToString().toInt();

    state = State(*this, command, _maxID, lineNumber + 1);

    if(state.stack().length() < arg)
    {
        state._errorMessage = "Error on line " + QString::number(currentLineNumber()) + ": Invalid argument in command POP.";
        return false;
    }

    for(int i = 0; i < arg; i++)
        state._stack.pop();

    return true;
}

bool State::Slide(GCommand command, State& state, int lineNumber)
{
    int arg = command.args()[0]->ToString().toInt();

    state = State(*this, command, _maxID, lineNumber + 1);

    if(state.stack().length() < arg)
    {
        state._errorMessage = "Error on line " + QString::number(currentLineNumber()) + ": Invalid command SLIDE";
        return false;
    }

    state._stack[state.stack().length() - arg - 1] = state.stack().last();
    for(int i = 0; i < arg; i++)
        state._stack.pop();

    return true;
}

bool State::Alloc(GCommand command, State& state, int lineNumber)
{
    int arg = command.args()[0]->ToString().toInt();

    state = State(*this, command, _maxID, lineNumber + 1);

    for(int i = 0; i < arg; i++)
    {
        state._stack.push_back(state.hp() + i);
        state._graph.push_back(GraphNode(state.hp() + i, GraphNodeType::None, 0));
    }

    state._hp += arg;

    return true;
}

bool State::Update(GCommand command, State& state, int lineNumber) //proveriti jos jednom
{
    state = State(*this, command, _maxID, lineNumber + 1);

    int k = command.args()[0]->ToString().toInt();

    GraphNodeType nodeType;

    int value;
    int idRef1;
    int idRef2;
    QString funName;

    foreach (GraphNode node, state.graph()) {
        if(node.id() == state.stack().last())
       {
            nodeType = node.type();
            value = node.value();
            idRef1 = node.idRef1();
            idRef2 = node.idRef2();
            funName = node.functionName();
       }
    }

    int id = state._graph[state.stack().at(state.stack().length() - k - 1)].id();
    int index = state._stack.at(state.stack().length() - k - 1);

    state._graph.at(index).~GraphNode();
    state._stack.pop();

    state._graph[index] = GraphNode(id, idRef1, idRef2, nodeType, value, funName);

    return true;
}

bool State::Mkap(GCommand command, State& state, int lineNumber)
{
    state = State(*this, command, _maxID, lineNumber + 1);

    int id1, id2;
    foreach(GraphNode node, state.graph())
    {
        if(node.id() == state.stack().last())
            id1 = node.id();
        if(node.id() == state.stack()[state.stack().length() - 2])
            id2 = node.id();
    }

    state._stack.pop();
    state._stack.pop();
    state._stack.push_back(state.hp());

    state._graph.push_back(GraphNode(state.hp(), id1, id2, GraphNodeType::Application, 0, NULL));
    state._hp++;

    return true;
}

bool State::Cons(GCommand command, State& state, int lineNumber)
{
    state = State(*this, command, _maxID, lineNumber + 1);
    int id1, id2;
    foreach(GraphNode node, state.graph())
    {
        if(node.id() == state.stack().last())
            id1 = node.id();
        if(node.id() == state.stack()[state.stack().length() - 2])
            id2 = node.id();
    }

    state._stack.pop();
    state._stack.pop();
    state._stack.push_back(state.hp());

    state._graph.push_back(GraphNode(state.hp(), id1, id2, GraphNodeType::Cons, 0, NULL));
    state._hp++;

    return true;
}

bool State::Add(GCommand command, State& state, int lineNumber)
{
    state = State(*this, command, _maxID, lineNumber + 1);

    GraphNodeType arg1Type, arg2Type;

    foreach(GraphNode node, state.graph())
    {
        if(node.id() == state.stack().last())
            arg1Type = node.type();
        if(node.id() == state.stack()[state.stack().length() - 2])
            arg2Type = node.type();
    }

    if(arg1Type != GraphNodeType::Integer || arg2Type != GraphNodeType::Integer)
    {
        state._errorMessage = "Error on line " + QString::number(currentLineNumber()) + ": ADD instruction on non-INT node.";
        return false;
    }

    int arg1, arg2;

    foreach(GraphNode node, state.graph())
    {
        if(node.id() == state.stack().last())
            arg1 = node.value();
        if(node.id() == state.stack()[state.stack().length() - 2])
            arg2 = node.value();
    }

    state._stack.pop();
    state._stack.pop();
    state._stack.push_back(state.hp());

    state._graph.push_back(GraphNode(state.hp(), GraphNodeType::Integer, arg1 + arg2));
    state._hp++;

    return true;
}

bool State::Sub(GCommand command, State& state, int lineNumber)
{
    state = State(*this, command, _maxID, lineNumber + 1);

    GraphNodeType arg1Type, arg2Type;

    foreach(GraphNode node, state.graph())
    {
        if(node.id() == state.stack().last())
            arg1Type = node.type();
        if(node.id() == state.stack()[state.stack().length() - 2])
            arg2Type = node.type();
    }

    if(arg1Type != GraphNodeType::Integer || arg2Type != GraphNodeType::Integer)
    {
        state._errorMessage = "Error on line " + QString::number(currentLineNumber()) + ": SUB instruction on non-INT node.";
        return false;
    }

    int arg1, arg2;

    foreach(GraphNode node, state.graph())
    {
        if(node.id() == state.stack().last())
            arg1 = node.value();
        if(node.id() == state.stack()[state.stack().length() - 2])
            arg2 = node.value();
    }

    state._stack.pop();
    state._stack.pop();
    state._stack.push_back(state.hp());

    state._graph.push_back(GraphNode(state.hp(), GraphNodeType::Integer, arg1 - arg2));
    state._hp++;

    return true;
}

bool State::Mul(GCommand command, State& state, int lineNumber)
{
    state = State(*this, command, _maxID, lineNumber);

    GraphNodeType arg1Type, arg2Type;

    foreach(GraphNode node, state.graph())
    {
        if(node.id() == state.stack().last())
            arg1Type = node.type();
        if(node.id() == state.stack()[state.stack().length() - 2])
            arg2Type = node.type();
    }

    if(arg1Type != GraphNodeType::Integer || arg2Type != GraphNodeType::Integer)
    {
        state._errorMessage = "Error on line " + QString::number(currentLineNumber()) + ": MUL instruction on non-INT node.";
        return false;
    }

    int arg1, arg2;

    foreach(GraphNode node, state.graph())
    {
        if(node.id() == state.stack().last())
            arg1 = node.value();
        if(node.id() == state.stack()[state.stack().length() - 2])
            arg2 = node.value();
    }

    state._stack.pop();
    state._stack.pop();
    state._stack.push_back(state.hp());

    state._graph.push_back(GraphNode(state.hp(), GraphNodeType::Integer, arg1 * arg2));
    state._hp++;

    return true;
}

bool State::Div(GCommand command, State& state, int lineNumber)
{
    state = State(*this, command, _maxID, lineNumber + 1);

    GraphNodeType arg1Type, arg2Type;

    foreach(GraphNode node, state.graph())
    {
        if(node.id() == state.stack().last())
            arg1Type = node.type();
        if(node.id() == state.stack()[state.stack().length() - 2])
            arg2Type = node.type();
     }
    if(arg1Type != GraphNodeType::Integer || arg2Type != GraphNodeType::Integer)
    {
        state._errorMessage = "Error on line " + QString::number(currentLineNumber()) + ": DIV instruction on non-INT node.";
        return false;
    }

    int arg1, arg2;

    foreach(GraphNode node, state.graph())
    {
        if(node.id() == state.stack().last())
            arg1 = node.value();
        if(node.id() == state.stack()[state.stack().length() - 2])
            arg2 = node.value();
    }

    if(arg2 == 0)
    {
        state._errorMessage = "Error on line " + QString::number(currentLineNumber()) + ": DIV instruction with zero second argument";
        return false;
    }

    state._stack.pop();
    state._stack.pop();
    state._stack.push_back(state.hp() - 1);

    state._graph.push_back(GraphNode(state.hp(), GraphNodeType::Integer, arg1 / arg2));
    state._hp++;

    return true;
}

bool State::Neg(GCommand command, State& state, int lineNumber)
{
    state = State(*this, command, _maxID, lineNumber + 1);

    GraphNodeType argType;

    foreach(GraphNode node, state.graph())
    {
        if(node.id() == state.stack().last())
            argType = node.type();
    }

    if(argType != GraphNodeType::Integer)
    {
        state._errorMessage = "Error on line " + QString::number(currentLineNumber()) + ": NEG instruction on non-INT node.";
        return false;
    }

    int arg;

    foreach(GraphNode node, state.graph())
    {
        if(node.id() == state.stack().last())
            arg = node.value();
    }

    state._stack[state.stack().length() - 1] = state.hp();

    state._graph.push_back(GraphNode(state.hp(), GraphNodeType::Integer, -arg));
    state._hp++;

    return true;
}

bool State::Head(GCommand command, State& state, int lineNumber)
{
    state = State(*this, command, _maxID, lineNumber + 1);
    GraphNodeType argType;
    int id;

    foreach(GraphNode node, state.graph())
    {
        if(node.id() == state.stack().last())
        {
            argType = node.type();
            id = node.idRef1();
        }
    }

    if(argType != GraphNodeType::Cons)
    {
        state._errorMessage = "Error on line " + QString::number(currentLineNumber()) + ": HEAD instruction on non-CONST node.";
        return false;
    }

    state._stack[state.stack().length() - 1] = id;

    return true;
}

bool State::End(GCommand command, State& state, int lineNumber)
{
    state = State(*this, command, _maxID, lineNumber + 1);
    return true;
}

bool State::Begin(GCommand command, State& state, int lineNumber)
{
    state = State(*this, command, _maxID, lineNumber + 1);
    state._stack.clear();
    state._graph.clear();
    state._dump.clear();
    state._hp = 0;
    state._returnTo.clear();

    return true;
}

bool State::Print(GCommand command, State& state, int lineNumber)
{
    GraphNodeType argType;
    int value;
    foreach (GraphNode node, state.graph()) {
        if(node.id() == state.stack().last())
        {
            argType = node.type();
            value = node.value();
        }
    }
    if(argType != GraphNodeType::Integer)
    {
        state._errorMessage = "Error on line " + QString::number(currentLineNumber()) + ": PRINT instruction on non-INT node";
        return false;
    }

    state = State(*this, state._command, _maxID, lineNumber + 1);
    state._stack.pop();
    state._output.push_back(QString::number(value));

    return true;
}

bool State::Min(GCommand command, State& state, int lineNumber)
{
    state = State(*this, command, _maxID, lineNumber + 1);

    GraphNodeType arg1Type, arg2Type;
    int arg1, arg2;

    foreach (GraphNode node, state.graph()) {
        if(node.id() == state.stack().last())
        {
            arg1Type = node.type();
            arg1 = node.value();
        }
        if(node.id() == state.stack()[state.stack().length() - 2])
        {
            arg2Type = node.type();
            arg2 = node.value();
        }
    }

    if(arg1Type != GraphNodeType::Integer || arg2Type != GraphNodeType::Integer)
    {
        state._errorMessage = "Error on line " + QString::number(currentLineNumber()) + ": MIN instruction on non-INT node.";
        return false;
    }

    state._stack.pop();
    state._stack.pop();
    state._stack.push_back(state.hp());

    state._graph.push_back(GraphNode(state.hp(), GraphNodeType::Integer, arg1 < arg2 ? arg1 : arg2));
    state._hp++;

    return true;
}

bool State::Max(GCommand command, State& state, int lineNumber)
{
    state = State(*this, command, _maxID, lineNumber + 1);

    GraphNodeType arg1Type, arg2Type;
    int arg1, arg2;

    foreach (GraphNode node, state.graph()) {
        if(node.id() == state.stack().last())
        {
            arg1Type = node.type();
            arg1 = node.value();
        }
        if(node.id() == state.stack()[state.stack().length() - 2])
        {
            arg2Type = node.type();
            arg2 = node.value();
        }
    }

    if(arg1Type != GraphNodeType::Integer || arg2Type != GraphNodeType::Integer)
    {
        state._errorMessage = "Error on line " + QString::number(currentLineNumber()) + ": MAX instruction on non-INT node.";
        return false;
    }

    state._stack.pop();
    state._stack.pop();
    state._stack.push_back(state.hp());

    state._graph.push_back(GraphNode(state.hp(), GraphNodeType::Integer, arg1 > arg2 ? arg1 : arg2));
    state._hp++;

    return true;
}

bool State::Eval(GCommand command, State& state, QList<GCommand> commands, int lineNumber)
{
    state = State(*this, command, _maxID, lineNumber + 1);

    GraphNodeType argType;
    QString funName;


    foreach (GraphNode node, state.graph()) {
        if(node.id() == state.stack().last())
        {
            argType = node.type();
            funName = node.functionName();
        }
    }

    if(argType == GraphNodeType::Cons || argType == GraphNodeType::Integer)
    {
        return true;
    }

    DumpNode dump;
    QVector<int> dumpStack;
    QVector<QString> dumpCode;

    if(argType == GraphNodeType::Application)
    {
        int tmp;
        if(state.stack().last() > 0)
            tmp = state.stack().last();

        if(state.stack().length() > 1)
            for(int i = 0; i < state.stack().length()-1; i++)
                dumpStack.push_back(state.stack()[i]);

        for(int i = currentLineNumber()+1; i < commands.length(); i++)
            dumpCode.push_back(commands[i].ToString());

        dump = DumpNode(dumpStack, dumpCode);
        state._dump.push_back(dump);

        state._stack.clear();
        state._stack.push_back(tmp);


        return Unwind(GCommand("Unwind;"), state, commands, lineNumber);
    }

    if(argType == GraphNodeType::Function)
    {
        state._returnTo.push(_currentLineNumber+1);
        int index = functionExists(funName, commands);

        if(index == -1)
        {
            state._errorMessage = "Error on line " + QString::number(currentLineNumber())
                    + ": EVAL instruction on non-existent function " + funName + ".";
            return false;
        }

        if(functionExistsWithZero(funName, commands) != -1)
        {
            if(state.stack().length() > 1)
                for(int i = 0; i < state.stack().length() - 1; i++)
                    dumpStack.push_back(state.stack()[i]);
            for(int i = currentLineNumber()+1; i < commands.length(); i++)
                dumpCode.push_back(commands[i].ToString());

            dump = DumpNode(dumpStack, dumpCode);

            state._dump.push_back(dump);
            state._stack[0] = state._stack.last();
        }
    }
    return true;
}

bool State::Unwind(GCommand command, State& state, QList<GCommand> commands, int lineNumber)
{
    state = State(state, command, _maxID, lineNumber + 1);
    GraphNodeType argType;
    int id1, id2;
    QString funName;

    foreach (GraphNode node, state.graph()) {
        if(node.id() == state.stack().last())
        {
            argType = node.type();
            id1 = node.idRef1();
            funName = node.functionName();
        }
        if(state.stack().length() > 1)
            if(node.id() == state.stack()[state.stack().length()-2])
                id2 = node.idRef2();
    }

    if(argType == GraphNodeType::Cons || argType == GraphNodeType::Integer)
    {
        int tmp = state.stack().last();
        state._stack.clear();

        if(state.dump().length() > 0)
        {
            for(int i = 0; i < state.dump().last().stack().length(); i++)
                state._stack.push_back(state._dump.last().stack()[i]);

            state._stack.push_back(tmp);
            state._dump.pop_back();
        }

        return true;
    }

    if(argType == GraphNodeType::Application)
    {
        state._stack.push_back(id1);
        state = State(state, command, _maxID, lineNumber);
        return Unwind(command, state, commands, lineNumber);
    }

    if(argType == GraphNodeType::Function)
    {
        if(funName == QString("$NEG"))
        {
            state._stack.pop();
            GraphNodeType nodeType = state._graph[state.stack().last()].type();
            if(nodeType != GraphNodeType::Application)
            {
                state._errorMessage = "Error on line " + QString::number(currentLineNumber())
                        + ": NEG instruction on non-integer node.";
                return false;
            }
            state._stack.push_back(state._graph[state.stack().last()].idRef2());

            return state.Neg(command, state, lineNumber-1);

//            int index = findPrint(commands);

//            if(index != -1)
//                return Print(GCommand("Print;"), state, lineNumber);
//            return true;
        }


        int index = functionExists(funName, commands);
        if(index == -1)
        {
            state._errorMessage = "Error on line " + QString::number(currentLineNumber())
                    + ": UNWIND instruction on non-existent function " + funName + ".";
            return false;
        }


        int arg = commands[index].args().at(1)->ToString().toInt();
        if(state.stack().length() > arg )
        {
            for(int i = state.stack().length() - 1; i > state.stack().length() - 1 - arg; i--)
                state._stack[i] = state._graph[state.stack()[i-1]].idRef2();
            state._returnTo.push_back(index);

            return true;
        }

        int tmp = state.stack().first();
        state._stack.clear();

        if(state.dump().length() > 0)
        {
            for(int i = 0; i < state.dump().last().stack().length(); i++)
                state._stack.push_back(state._dump.last().stack()[i]);

            state._stack.push_back(tmp);
            state._dump.pop_back();
        }
    }
    return true;
}

bool State::Return(GCommand command, State& state, QList<GCommand> commands, int lineNumber)
{
    int tmp = state.stack().first();
    state._stack.clear();

    if(state.dump().length() > 0)
    {
        for(int i = 0; i < state.dump().last().stack().length(); i++)
            state._stack.push_back(state._dump.last().stack()[i]);

        state._stack.push_back(tmp);
        state._dump.clear();
    }

    return true;
}

bool State::Label(GCommand command, State& state, QList<GCommand> commands, int lineNumber)
{
    state = State(*this, command, _maxID, lineNumber + 1);
    return true;
}


bool State::Jump(GCommand command, State& state, QList<GCommand> commands, int lineNumber)
{
    int index = labelExists(commands, command.args()[0]->ToString());

    if(index == -1)
    {
        state._errorMessage = "Error on line " + QString::number(this->currentLineNumber()) + ": No appropriate label " +
                command.args()[0]->ToString() + " for JUMP instruction.";
        return false;
    }

    state = State(*this, command, _maxID, lineNumber + 1);
    return true;
}

bool State::JFalse(GCommand command, State& state, QList<GCommand> commands, int lineNumber)
{
    GraphNodeType argType;
    GraphNode currentNode;

    foreach(GraphNode node, state.graph())
        if(node.id() == state.stack().last())
        {
            argType = state.graph()[state.stack().last()].type();
            currentNode = node;
        }

    if(argType != GraphNodeType::Integer)
    {
        state._errorMessage = "Error on line " + QString::number(this->currentLineNumber())
                + ": JFALSE instruction on non-INT node.";
        return false;
    }

    if(currentNode.value() == 0)
    {
        int index = labelExists(commands, command.args()[0]->ToString());

        if(index == -1)
        {
            state._errorMessage = "Error on line " + QString::number(this->currentLineNumber()) + ": No appropriate label " +
                    command.args()[0]->ToString() + " for JFALSE instruction.";
            return false;
        }
    }

    state = State(*this, command, _maxID, lineNumber + 1);
    state._stack.pop();

    return true;
}

