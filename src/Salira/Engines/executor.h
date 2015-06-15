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
    void Execute();
    QList<State> states;
public:
    static Executor& Instance();
    void Init(QList<GCommand> commands);
    void ExecuteNext();
    void ExecutePrevious();
    void Reset();
    State currentState;
};

#endif // EXECUTOR_H
