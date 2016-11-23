#include <vector>

using namespace std;

class Node
{
public:
    Node();
    Node(char nodechar);
    ~Node();
    void addNode(char nodechar);
    void addNode(Node &nodetoadd);
    char getChar(void);
    Node &advance(char nextchar);
private:
    char nodeChar;
    vector<Node> children;
};