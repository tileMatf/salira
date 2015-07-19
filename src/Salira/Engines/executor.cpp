#include "executor.h"
#include <iostream>

static Executor *instance = nullptr;
const int STACK_SIZE = 256;

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

GCommand Executor::previousPushInt(QList<GCommand> commands, int currentLine)
{
    for(int i = currentLine - 1; i >= 0; i--)
        if(commands[i].value() == "PUSHINT")
            return commands[i];
    return GCommand("");
}

bool Executor::Init(QList<GCommand> commands, QString& errorMessage)
{
    this->Reset();

    bool error = false;
    State initialState = State(0);
    this->_states.push_back(initialState);

    State nextState;
    for (int i = 0; i < commands.length(); i++)
    {
        GCommand command = commands[i];
        if(!(this->_states.last().GetNext(command, nextState, commands, i)))
        {
            error = true;
            break;
        }

        if(nextState.command().value() == "JUMP")
        {
            QString labelName = nextState.command().args()[0]->ToString();

            for(int j = 0; j < commands.length(); j++)
            {
                if(commands[j].ToString() == QString("LABEL " + labelName + ";"))
                {
                    i = j - 1;
                    break;
                }
            }
        }

        bool ok;
        if(nextState.command().value() == "JFALSE" && previousPushInt(commands, i).args()[0]->ToString().toInt(&ok, 10) == 0)
        {
            QString labelName = nextState.command().args()[0]->ToString();

            for(int j = 0; j < commands.length(); j++)
            {
                if(commands[j].ToString() == QString("LABEL " + labelName + ";"))
                {
                    i = j - 1;
                    break;
                }
            }
        }

/*        if(nextState.command().value() == "EVAL" )
        {

        }
*/
        this->_states.push_back(nextState);
        if(_states.length() >= STACK_SIZE)
        {
            errorMessage = "Error: Stack or Graph overflow! It is possible that there is an infinite loop on input!";
            return false;
        }
    }

    if(this->_states.length() > 0 && !error)
    {
        this->_currentState = this->_states[0];
        return true;
    }
    else if(error)
    {
        errorMessage = nextState.errorMessage();
        return false;
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
    this->currentState() = State();
    State::setMaxID(0);
}



