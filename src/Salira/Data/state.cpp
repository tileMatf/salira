#include "state.h"

int State::maxID = -1;

State::State()
{
    this->id = ++maxID;
    this->ep = 0;
    this->hp = 0;
    this->sp = 0;
    this->op = 0;
}

State::State(int ep, int hp, int sp, int op, Stack stack, Graph graph, Dump dump)
{
    this->id = ++maxID;
    this->ep = ep;
    this->hp = hp;
    this->sp = sp;
    this->op = op;
    this->stack = stack;
    this->graph = graph;
    this->dump = dump;
}

