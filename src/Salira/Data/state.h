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
    GCommand _command;
    QString _errorMessage;
public:
    State();
    State(int ep, int hp, int sp, int op, QStack<int> stack, QVector<GraphNode> graph, QVector<DumpNode> dump, GCommand command);
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
    GCommand command();
    QString errorMessage();

    bool GetNext(GCommand command, State* nextState);
    bool PushInt(State* state);
    bool PushGlobal(State* state);
    bool GlobStart(State* state);
    bool Push(State* state);
    bool Pop(State* state);
    bool Slide(State* state);
    bool Alloc(State* state);
    bool Update(State* state);
    bool Mkap(State* state);
    bool Cons(State* state);
    bool Add(State* state);
    bool Sub(State* state);
    bool Mul(State* state);
    bool Div(State* state);
    bool Neg(State* state);
    bool Head(State* state);
    bool End(State* state);
    bool Begin(State* state);
    bool Print(State* state);
    bool Min(State* state);
    bool Max(State* state);
    bool Eval(State* state);
    bool Eval2(State* state);
    bool Unwind(State* state);
    bool Unwind2(State* state);
    bool Return(State* state);
    bool Label(State* state);
    bool Jump(State* state);
    bool JFalse(State* state);
};

#endif // STATE_H
