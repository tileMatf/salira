#include "executor.h"
#include <iostream>

static Executor *instance = nullptr;

Executor::Executor()
{
}

Executor& Executor::Instance()
{
    static Executor instance;
    return instance;
}

QList<State> Executor::states()
{
    return this->_states;
}

State Executor::currentState()
{
    return this->_currentState;
}

void Executor::Init(QList<GCommand> commands)
{
    this->Reset();

    bool error = false;
    State initialState = State(0);
    this->_states.push_back(initialState);
    foreach(GCommand command, commands)
    {
        State nextState;
        if(!(this->_states.last().GetNext(command, nextState, commands)))
        {
            error = true;
            break;
        }

        this->_states.push_back(nextState);
    }

    if(this->_states.length() > 0 && !error)
        this->_currentState = this->_states[0];
    else if(error)
    {
        //ovde treba da se ispise error poruka i odradi neka invalidacija
    }
}

void Executor::Execute(bool forward)
{
    if(forward)
    {
        while(_currentState.id() < State::maxID() && this->_states[this->_currentState.id() + 1].command().value() == "")
            _currentState = this->_states[_currentState.id() + 1];
    }
    else
    {
        while(_currentState.id() > 0 && this->_states[this->_currentState.id() - 1].command().value() == "")
            _currentState = this->_states[_currentState.id() - 1];
    }
}

void Executor::ExecuteNext()
{
    this->Execute(true);
    if(_currentState.id() < State::maxID())
        _currentState = this->_states[_currentState.id() + 1];
}

void Executor::ExecutePrevious()
{
    this->Execute(false);
    if(_currentState.id() > 0)
        _currentState = this->_states[_currentState.id() - 1];
}

void Executor::Reset()
{
    this->_states.clear();
    State::setMaxID(0);
}



