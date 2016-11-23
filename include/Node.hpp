#ifndef __NODEHPP__
#define __NODEHPP__

#include <set>


class Node
{
public:
    Node(char nodechar);
    Node(char nodechar, bool wordEnd);
    Node(const Node &p);    
    Node &operator=(const Node &p);    
    ~Node();
    bool operator<(const Node &p) const;
    bool operator==(const Node &p) const;
    Node *addNode(char nodechar);
    Node *addNode(char nodechar, bool wordEnd);
    Node *addNode(Node &nodetoadd);
    char getChar(void);
    Node *advance(char nextchar);
    void printChildren(void);
    bool isWordEnd(void);
    void setWordEnd(bool wordEnd);
private:
    char nodeChar;
    bool endWord;
    std::set<Node> children;
};

#endif // __NODEHPP__