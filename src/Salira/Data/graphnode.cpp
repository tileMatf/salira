#include "graphnode.h"

GraphNode::GraphNode()
{

}

GraphNode::GraphNode(int id, GraphNodeType type, int value)
    :_id(id), _type(type), _value(value)
{

}

GraphNode::~GraphNode()
{

}

GraphNodeType GraphNode::type()
{
    return this->_type;
}

QString GraphNode::functionName()
{
    return this->_functionName;
}

int GraphNode::value()
{
    return this->_value;
}

