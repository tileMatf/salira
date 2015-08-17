#ifndef STATE_H
#define STATE_H
#include <QStack>
#include <QVector>
#include <Data/graphnode.h>
#include <Data/dumpnode.h>
#include <Data/gcommand.h>

class State
{
private:
    static int _maxID;
    static int _cBegin;
    int _id;
    int _ep;
    int _hp;
    int _sp;
    int _op;
    QStack<int> _stack;
    QVector<GraphNode> _graph;
    QVector<DumpNode> _dump;
    QVector<QString> _output;
    GCommand _command;
    QString _errorMessage;
    int _currentLineNumber;

    int functionExists(QString functionName, QList<GCommand> commands);
    int functionExistsWithZero(QString functionName, QList<GCommand> commands);
    int labelExists(QList<GCommand> commands, QString labelName);
    int findPrint(QList<GCommand> commands);

public:
    static QStack<unsigned> _returnTo;

    State();
    State(int id);
    State(const State& state, GCommand command, int id, int jumpTo = -1);
    ~State();

    static int maxID();
    static void setMaxID(int value);
    static int cBegin();
    static void setCBegin(int value);
    static QStack<unsigned> returnTo();
    int id();
    int ep();
    int hp();
    int sp();
    int op();
    QStack<int> stack();
    QVector<GraphNode> graph();
    QVector<DumpNode> dump();
    QVector<QString> output();
    GCommand command();
    QString errorMessage();
    int currentLineNumber();

    bool GetNext(GCommand command, State& nextState, QList<GCommand> commands, int lineNumber);
    bool PushInt(GCommand command, State& state, int lineNumber);
    bool PushGlobal(GCommand command, State& state, int lineNumber);
    bool GlobStart(GCommand command, State& state, int lineNumber);
    bool Push(GCommand command, State& state, int lineNumber);
    bool Pop(GCommand command, State& state, int lineNumber);
    bool Slide(GCommand command, State& state, int lineNumber);
    bool Alloc(GCommand command, State& state, int lineNumber);
    bool Update(GCommand command, State& state, int lineNumber);
    bool Mkap(GCommand command, State& state, int lineNumber);
    bool Cons(GCommand command, State& state, int lineNumber);
    bool Add(GCommand command, State& state, int lineNumber);
    bool Sub(GCommand command, State& state, int lineNumber);
    bool Mul(GCommand command, State& state, int lineNumber);
    bool Div(GCommand command, State& state, int lineNumber);
    bool Neg(GCommand command, State& state, int lineNumber);
    bool Head(GCommand command, State& state, int lineNumber);
    bool End(GCommand command, State& state, int lineNumber);
    bool Begin(GCommand command, State& state, int lineNumber);
    bool Print(GCommand command, State& state, int lineNumber);
    bool Min(GCommand command, State& state, int lineNumber);
    bool Max(GCommand command, State& state, int lineNumber);
    bool Eval(GCommand command, State& state, QList<GCommand> commands, int lineNumber);
    bool Unwind(GCommand command, State& state, QList<GCommand> commands, int lineNumber);
    bool Return(GCommand command, State& state, QList<GCommand> commands,int lineNumber);
    bool Label(GCommand command, State& state, QList<GCommand> commands, int lineNumber);
    bool Jump(GCommand command, State& state, QList<GCommand> commands, int lineNumber);
    bool JFalse(GCommand command, State& state, QList<GCommand> commands,int lineNumber);
};

#endif // STATE_H
