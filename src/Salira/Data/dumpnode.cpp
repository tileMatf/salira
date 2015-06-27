#include "dumpnode.h"

DumpNode::DumpNode()
{

}

DumpNode::DumpNode(QVector<int> stack, QVector<QString> code)
{
    this->_stack = QVector<int>(stack);
    this->_code = QVector<QString>(code);
}

DumpNode::~DumpNode()
{
    this->_stack.clear();
    this->_code.clear();
}

QVector<int> DumpNode::stack()
{
    return this->_stack;
}

QVector<QString> DumpNode::code()
{
    return this->_code;
}

