#ifndef STATE_H
#define STATE_H
#include<Data/stack.h>
#include<Data/graph.h>
#include<Data/dump.h>
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
    Stack _stack;
    Graph _graph;
    Dump _dump;
    GCommand _command;
public:
    State();
    State(GCommand command);
    State(int ep, int hp, int sp, int op, Stack stack, Graph graph, Dump dump, GCommand command);

    static int maxID();
    static void setMaxID(int value);
    int id();
    int ep();
    int hp();
    int sp();
    int op();
    Stack stack();
    Graph graph();
    Dump dump();
    GCommand command();
};

#endif // STATE_H
