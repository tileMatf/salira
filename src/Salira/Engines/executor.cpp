#include "executor.h"

static Executor *instance = nullptr;

Executor::Executor()
{
}

Executor& Executor::Instance()
{
    static Executor instance;
    return instance;
}

void Executor::Init(QList<GCommand> commands)
{
    this->Reset();
    foreach (GCommand command, commands)
        this->states.push_back(State());
    if(this->states.length() > 0)
        this->currentState = this->states[0];
}

void Executor::Execute()
{

}

void Executor::ExecuteNext()
{
    Execute();
    if(currentState.id < State::maxID)
        currentState = this->states[currentState.id + 1];
}

void Executor::ExecutePrevious()
{
    Execute();
    if(currentState.id > 0)
        currentState = this->states[currentState.id - 1];
}

void Executor::Reset()
{
    states.clear();
    State::maxID = -1;
}



