#ifndef __WORDTREEHPP__
#define __WORDTREEHPP__

#include <Node.hpp>
#include <string>

class Wordtree: public Node
{
public:
    Wordtree(std::string filename);
    Wordtree(const Wordtree &p);    
    ~Wordtree();
    Wordtree &operator=(const Wordtree &p);
    
    bool populate(void);    
    bool findWord(std::string word);
    bool isValidWord(std::string word); 
    
    const unsigned int minLength = 2;
    const unsigned int maxLength = 8;
private:
    std::string fileName;
};

#endif // __WORDTREEHPP__