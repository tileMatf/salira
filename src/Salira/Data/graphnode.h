#ifndef GRAPHNODE_H
#define GRAPHNODE_H
#include <QString>

enum GraphNodeType
{
    None = 0,
    Integer = 1,
    Function = 2,
    Cons = 3,
    Application = 4
};

class GraphNode
{
private:
    int _id;
    GraphNodeType _type;
    QString _functionName;
    int _value;
public:
    GraphNode();
    GraphNode(int id, GraphNodeType type, int value);
    ~GraphNode();

    GraphNodeType type();
    QString functionName();
    int value();
};

#endif // GRAPHNODE_H
