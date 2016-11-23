#ifndef __BOARDHPP__
#define __BOARDHPP__

#include <vector>
#include <list>
#include <string>
#include "Location.hpp"
#include "Node.hpp"
#include <string>
#include <ostream>
#include <iterator>

class Path;

class Board
{
public:
    Board(unsigned int width, Node* tree);
    Board(std::string filename, Node* tree);
    Board(const Board &b, const Path &p);    
    Board(const Board &p);    
    ~Board();
    Board &operator=(const Board &p);    
    
    char getTile(unsigned int row, unsigned int col);
    void enterBoard(void);
    bool isValidLine(std::string line);
    Board &collapse(std::vector<Location> locations);
    bool loadBoardFromFile(std::string filename);
    unsigned int getSize(void);
    unsigned int getWordLength(unsigned int wordNum);
    unsigned int getCurrentWord(void);
    bool complete(void);
    std::list<Board> findWord(void);
    unsigned int findWord(std::front_insert_iterator<std::list<Board>> iter);
    void printWordList(void);

    friend std::ostream& operator<<(std::ostream& os, const Board &board)
    {
    
        for(unsigned int i=0;i<board.size;i++)
        {
            for(unsigned int k=0;k<board.size;k++)
            {
                os << board.tiles[i][k];
            }
            os << std::endl;
        }
        
        os << std::endl;
        
        for(unsigned int i=0;i<board.numWords;i++)
        {
            for(unsigned int k=0;k<board.words[i].length();k++)
            {
                os << board.words[i][k] << " ";    
            }
            os << std::endl;
        }
        
        os << std::endl;
        return os;
    }
    
    const char emptySpace = '+';
    const unsigned int minSize = 2;
    const unsigned int maxSize = 8;    
    const unsigned int minWordLength = 2;
    const unsigned int maxWordLength = 8;    
private:
    std::vector<std::vector<char>> tiles;
    std::vector<std::string> words;
    unsigned int numWords;
    unsigned int currentWord;
    unsigned int size;
    Node *wordTree;
};

#endif // __BOARDHPP__
