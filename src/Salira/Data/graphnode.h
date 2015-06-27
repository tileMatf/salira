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
    int _idRef1;
    int _idRef2;
    GraphNodeType _type;
    QString _functionName;
    int _value;

public:
    GraphNode();
    GraphNode(GraphNodeType type);
    GraphNode(int id, GraphNodeType type, int value);
    GraphNode(int id, int idRef1, int idRef2, GraphNodeType type, int value, QString name);
    ~GraphNode();

    int id();
    int idRef1();
    int idRef2();
    GraphNodeType type();
    QString functionName();
    int value();
};

#endif // GRAPHNODE_H
