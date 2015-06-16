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

State::State(GCommand command)
    :_command(command)
{
    this->_id = ++_maxID;
    this->_ep = 0;
    this->_hp = 0;
    this->_sp = 0;
    this->_op = 0;
}

State::State(int ep, int hp, int sp, int op, Stack stack, Graph graph, Dump dump, GCommand command)
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

Stack State::stack()
{
    return this->_stack;
}

Graph State::graph()
{
    return this->_graph;
}

Dump State::dump()
{
    return this->_dump;
}

GCommand State::command()
{
    return this->_command;
}


