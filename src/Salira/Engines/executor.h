#ifndef EXECUTOR_H
#define EXECUTOR_H
#include <QList>
#include <Data/state.h>
#include <Data/gcommand.h>

using namespace std;

class Executor
{
private:
    Executor();

    QList<State> _states;
    State _currentState;


    void Execute(bool forward);

    int valueOfGraphNode(int id, State state);

public:
    static Executor& Instance();

    QList<State> states();
    State currentState();


    bool Init(QList<GCommand> commands, QString& errorMessage);
    void ExecuteNext();
    void ExecutePrevious();
    void Reset();
};

#endif // EXECUTOR_H
