#ifndef GRAPHNODE_H
#define GRAPHNODE_H
#include <QString>

class GraphNode
{
public:
    enum Type
    {
        None = 0,
        Integer = 1,
        Function = 2,
        Cons = 3,
        Application = 4
    };
private:
    Type _type;
    QString _functionName;
    double _value;
public:
    GraphNode();
    ~GraphNode();
};

#endif // GRAPHNODE_H
