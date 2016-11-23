#include <set>
#include <Node.hpp>

#include <iostream>

    
Node::Node(char nodechar)
: nodeChar(nodechar),
  children(std::set<Node>()),
  endWord(false)
{
    
}

Node::Node(char nodechar, bool wordEnd)
: nodeChar(nodechar),
  children(std::set<Node>()),
  endWord(wordEnd)
{
    
}

Node::Node(const Node &p)
: nodeChar(p.nodeChar),
  children(p.children),
  endWord(p.endWord)
{
    
}

Node &Node::operator=(const Node &p)    
{
    if (this != &p)
    {
        nodeChar = p.nodeChar;
        children = p.children;
        endWord = p.endWord;
    }
    return *this;
}
    
Node::~Node()
{
    
}

bool Node::operator<(const Node &p) const
{
    return nodeChar < p.nodeChar;
}

bool Node::operator==(const Node &p) const
{
    return (nodeChar == p.nodeChar);
}

Node *Node::addNode(char nodechar)
{   
    return addNode(nodechar, false);
}

Node *Node::addNode(char nodechar, bool wordEnd)
{    
    Node *n;
    n = advance(nodechar);
    if (n == nullptr)
    {
        children.insert(Node(nodechar, wordEnd));
        auto it = children.find(nodechar);
        return (Node*)&(*it);
    } 
    else
    {
        if (wordEnd && !n->isWordEnd())
        {
            n->setWordEnd(true);
        }
        return n;
    }
    
}
    
Node *Node::addNode(Node &nodetoadd)
{
    children.insert(nodetoadd);
    auto it = children.find(nodetoadd.nodeChar);
    return (Node*)&(*it);
}

char Node::getChar(void)
{
    return nodeChar;
}
    
Node *Node::advance(char nextchar)
{
    auto it=children.find(nextchar);
    if ((*it).nodeChar != nextchar) // showing final value - not found
    {
        return nullptr;
    }
    
    return (Node*)&(*it);
}

void Node::printChildren(void)
{
    std::cout << "Children:";
    for (auto it=children.begin(); it!=children.end(); ++it)
        std::cout << ' ' << (*it).nodeChar;
    std::cout << '\n';
}

bool Node::isWordEnd(void)
{
    return endWord;
}

void Node::setWordEnd(bool wordEnd)
{
    endWord = wordEnd;
}
