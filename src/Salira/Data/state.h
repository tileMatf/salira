#ifndef STATE_H
#define STATE_H
#include <QStack>
#include <QVector>
#include<Data/graphnode.h>
#include<Data/dumpnode.h>
#include<Data/gcommand.h>

class State
{
private:
    static int _maxID;
    int _id;
    int _ep;
    int _hp;
    int _sp;
    int _op;
    QStack<int> _stack;
    QVector<GraphNode> _graph;
    QVector<DumpNode> _dump;
    QVector<QString> _output;
    GCommand _command;
    QString _errorMessage;
public:
    State();
    State(int id);
    State(const State& state, GCommand command, int id);
    ~State();

    static int maxID();
    static void setMaxID(int value);
    int id();
    int ep();
    int hp();
    int sp();
    int op();
    QStack<int> stack();
    QVector<GraphNode> graph();
    QVector<DumpNode> dump();
    QVector<QString> output();
    GCommand command();
    QString errorMessage();

    bool GetNext(GCommand command, State& nextState);
    bool PushInt(GCommand command, State& state);
    bool PushGlobal(GCommand command, State& state);
    bool GlobStart(GCommand command, State& state);
    bool Push(GCommand command, State& state);
    bool Pop(GCommand command, State& state);
    bool Slide(GCommand command, State& state);
    bool Alloc(GCommand command, State& state);
    bool Update(GCommand command, State& state);
    bool Mkap(GCommand command, State& state);
    bool Cons(GCommand command, State& state);
    bool Add(GCommand command, State& state);
    bool Sub(GCommand command, State& state);
    bool Mul(GCommand command, State& state);
    bool Div(GCommand command, State& state);
    bool Neg(GCommand command, State& state);
    bool Head(GCommand command, State& state);
    bool End(GCommand command, State& state);
    bool Begin(GCommand command, State& state);
    bool Print(GCommand command, State& state);
    bool Min(GCommand command, State& state);
    bool Max(GCommand command, State& state);
    bool Eval(GCommand command, State& state);
    bool Eval2(GCommand command, State& state);
    bool Unwind(GCommand command, State& state);
    bool Unwind2(GCommand command, State& state);
    bool Return(GCommand command, State& state);
    bool Label(GCommand command, State& state);
    bool Jump(GCommand command, State& state);
    bool JFalse(GCommand command, State& state);
};

#endif // STATE_H
