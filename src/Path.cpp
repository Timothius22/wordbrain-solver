#include "Path.hpp"
#include "Location.hpp"
#include "Board.hpp"
#include "Node.hpp"
#include <vector>
#include <list>
#include <iostream>

Path::Path(Board &b, unsigned int exp_len, unsigned int row, unsigned int col, Node* node, unsigned int len)
: board(b),
  expectedLength(exp_len),
  row(row),
  col(col),
  currentNode(node),
  currentLength(len)
{
    locations = std::vector<Location>();
    locations.push_back(Location(row,col,b.getTile(row,col)));
    word = std::string();
    word.append(1,b.getTile(row,col));
}

Path::Path(Board &b, unsigned int exp_len, unsigned int row, unsigned int col, Node* node, unsigned int len, std::vector<Location> location_list, std::string oldword)
: board(b),
  expectedLength(exp_len),
  row(row),
  col(col),
  currentNode(node),
  currentLength(len),
  word(oldword)
{
    locations = location_list;
    locations.push_back(Location(row,col,b.getTile(row,col)));
    word.append(1,b.getTile(row,col));
}

Path::Path(const Path &p)
: board(p.board),
  expectedLength(p.expectedLength),
  locations(p.locations),
  row(p.row),
  col(p.col),
  word(p.word),
  currentNode(p.currentNode),
  currentLength(p.currentLength)
{
    
    
}
    
Path &Path::operator=(const Path &p)               
{
    if (this != &p)
    {
        board = p.board;
        expectedLength = p.expectedLength;
        locations = p.locations;
        row = p.row;
        col = p.col;
        word = p.word;
        currentNode = p.currentNode;
        currentLength = p.currentLength;
    }
    return *this;
}
    
Path::~Path()
{
    
}


std::list<Path> Path::search(void)
{
    unsigned int boardsize;
    bool newLoc;
    Node *n;
    int deltarow;
    int deltacol;
    std::list<Path> newpaths = {};
    Location loc = Location(0,0,'a');
    const std::vector<int> addrow = {1,0,1,-1,0,-1,1,-1};
    const std::vector<int> addcol = {0,1,1,0,-1,-1,-1,1};
    const unsigned int addlen = 8;
    
    boardsize = board.getSize();
       
    for(int i=0;i<addlen;i++)
    {
        deltarow = ((int)row+addrow[i]);
        deltacol = ((int)col+addcol[i]);
        if ((deltarow < boardsize && deltarow >= 0) && (deltacol < boardsize && deltacol >= 0))
        {
            loc.setRC(deltarow,deltacol);            
            newLoc = true;
            for (auto it=locations.begin(); it!=locations.end(); ++it)
            {
                if ((*it) == loc)
                {
                    newLoc = false;
                }
            }
            if (newLoc && board.getTile(deltarow,deltacol) != board.emptySpace)
            {
                n = currentNode->advance(board.getTile(deltarow,deltacol));
                if (n != nullptr)
                {    
                    newpaths.push_back(Path(board, expectedLength, deltarow, deltacol, n, currentLength+1,locations, word));
                }
            }
        }
    }

    return newpaths;
}

void Path::search(std::back_insert_iterator<std::list<Path>> iter)
{
    unsigned int boardsize;
    bool newLoc;
    Node *n;
    int deltarow;
    int deltacol;
    std::list<Path> newpaths = {};
    Location loc = Location(0,0,'a');
    const std::vector<int> addrow = {1,0,1,-1,0,-1,1,-1};
    const std::vector<int> addcol = {0,1,1,0,-1,-1,-1,1};
    const unsigned int addlen = 8;
    
    boardsize = board.getSize();
       
    for(int i=0;i<addlen;i++)
    {
        deltarow = ((int)row+addrow[i]);
        deltacol = ((int)col+addcol[i]);
        if ((deltarow < boardsize && deltarow >= 0) && (deltacol < boardsize && deltacol >= 0))
        {
            loc.setRC(deltarow,deltacol);            
            newLoc = true;
            for (auto it=locations.begin(); it!=locations.end(); ++it)
            {
                if ((*it) == loc)
                {
                    newLoc = false;
                }
            }
            if (newLoc && board.getTile(deltarow,deltacol) != board.emptySpace)
            {
                n = currentNode->advance(board.getTile(deltarow,deltacol));
                if (n != nullptr)
                {   
                    *iter++ = Path(board, expectedLength, deltarow, deltacol, n, currentLength+1,locations, word);
                }
            }
        }
    }

}




bool Path::complete(void)
{
    return (currentLength == expectedLength) && currentNode->isWordEnd();
}

const unsigned int Path::getRow(void) const
{
    return row;
}
    
const unsigned int Path::getCol(void) const
{
    return col;
}
    
const unsigned int Path::getCurrentLength(void) const
{
    return currentLength;
}
    
const unsigned int Path::getExpectedLength(void) const
{
    return expectedLength;
}

const std::string& Path::getWord(void) const
{
    return word;
}

const std::vector<Location> Path::getLocations(void) const
{
    return locations;
}