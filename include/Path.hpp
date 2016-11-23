#ifndef __PATHHPP__
#define __PATHHPP__

#include <vector>
#include <list>
#include <ostream>
#include <string>
#include <iterator>
#include "Location.hpp"
#include "Board.hpp"
#include "Node.hpp"

class Path
{
public:
    Path(Board &b, unsigned int exp_len, unsigned int row, unsigned int col, Node* node, unsigned int len);
    Path(Board &b, unsigned int exp_len, unsigned int row, unsigned int col, Node* node, unsigned int len, std::vector<Location> location_list, std::string oldword);
    Path(const Path &p);    
    ~Path();
    Path &operator=(const Path &p);  
    std::list<Path> search(void);
    void search(std::back_insert_iterator<std::list<Path>> iter);
    bool complete(void);
    const unsigned int getRow(void) const;
    const unsigned int getCol(void) const;
    const unsigned int getCurrentLength(void) const;
    const unsigned int getExpectedLength(void) const;
    const std::string& getWord(void) const;
    const std::vector<Location> getLocations(void) const;
    
    friend std::ostream& operator<<(std::ostream& os, const Path &path)
    {
        os << "Path at (" << path.row << "," << path.col << ") representing word " << path.word << " of length " << path.currentLength << " expecting " << path.expectedLength << ".";
        return os;
    }
private:
    std::vector<Location> locations;
    unsigned int expectedLength;
    unsigned int currentLength;
    Board &board;
    unsigned int row;
    unsigned int col;
    Node* currentNode;
    std::string word;
};



#endif // __PATHHPP__