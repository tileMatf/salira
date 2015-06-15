#ifndef STATE_H
#define STATE_H
#include<Data/stack.h>
#include<Data/graph.h>
#include<Data/dump.h>

class State
{
public:
    State();
    State(int ep, int hp, int sp, int op, Stack stack, Graph graph, Dump dump);
    int id;
    int ep;
    int hp;
    int sp;
    int op;
    Stack stack;
    Graph graph;
    Dump dump;
    static int maxID;
};

#endif // STATE_H
