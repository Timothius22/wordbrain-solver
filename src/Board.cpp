#include "Board.hpp"
#include "Path.hpp"
#include "Location.hpp"
#include "Node.hpp"
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include <iterator>

Board::Board(unsigned int width, Node* tree)
: size(width),
  tiles(std::vector<std::vector<char>>()),
  words(std::vector<std::string>()),
  numWords(0),
  currentWord(0),
  wordTree(tree)
{
    tiles.resize(size, std::vector<char>(size, emptySpace));
}

Board::Board(std::string filename, Node* tree)
{
    size = 0;
    tiles = std::vector<std::vector<char>>();
    wordTree = tree;
    if (!loadBoardFromFile(filename))
    {
        size = 0;
        tiles = std::vector<std::vector<char>>();
    }        
}

Board::Board(const Board &b, const Path &p)
: size (b.size),
  tiles (b.tiles),
  words (b.words),
  numWords (b.numWords),
  currentWord (b.currentWord),
  wordTree (b.wordTree)
{
    this->collapse(p.getLocations());
    words[currentWord] = p.getWord();
    currentWord++;
}

Board::Board(const Board &p)
: size (p.size),
  tiles (p.tiles),
  words (p.words),
  numWords (p.numWords),
  currentWord (p.currentWord),
  wordTree (p.wordTree)
{

    
}
    
Board &Board::operator=(const Board &p)               
{
    if (this != &p)
    {
        size = p.size;
        tiles = p.tiles;
        words = p.words;
        numWords = p.numWords;
        currentWord = p.currentWord;       
        wordTree = p.wordTree;
    }
    return *this;
}
    
Board::~Board()
{
    
}

char Board::getTile(unsigned int row, unsigned int col)
{
    if (row < size && col < size)
    {
        return tiles[row][col];
    }
    return '\0';
}

void Board::enterBoard(void)
{
    std::string line;
    bool unacceptable;
    
    for(unsigned int i = 0; i<size; i++)
    {
        do
        {
            std::cout << "Enter Line" << i+1 << ":";
            std::cin >> line;
            std::transform(line.begin(), line.end(), line.begin(), ::tolower);
            if (isValidLine(line) && line.length()==size)
            {
                unacceptable = false;
            }
            else
            {
                std::cout << "Invalid board line. Please re-enter." << std::endl;
                unacceptable = true;                
                std::cout << std::endl;
            }            
        } while (unacceptable);
        for (unsigned int k = 0; k<size; k++)
        {
            tiles[i][k] = line[k];
        }
    }
}

bool Board::isValidLine(std::string line)
{
    bool good;
    
    good = true;
    for (unsigned int i=0;i<line.length();i++)
    {
        if (line[i] < 'a' || line[i] > 'z')
        {
            good = false;
        }      
    }
    return good;
}

Board &Board::collapse(std::vector<Location> locations)
{
    Board &b = *this;
    unsigned int row;
    unsigned int col;
    
    for(auto it=locations.begin(); it!=locations.end();++it)
    {
        col = it->getCol();
        row = it->getRow();
        //std::cout << "Removing (" << row << "," << col << ") = " << b.tiles[row][col] << " = " << it->getLetter() << std::endl;
        b.tiles[row][col] = b.emptySpace;
    }

    
    for (unsigned int c=0;c<b.size;c++)
    {
        for (unsigned int r=b.size-1;r>0;r--)
        {
            while (b.tiles[r][c] == b.emptySpace)
            {
                for (int k=r-1;k>=0;k--)
                {
                    b.tiles[k+1][c] = b.tiles[k][c];
                }
                b.tiles[0][c] = (b.emptySpace+1);              
            }
        }
        for (unsigned int r=0;r<b.size;r++)
        {
            if (b.tiles[r][c] == (b.emptySpace+1))
            {
                b.tiles[r][c] = b.emptySpace;
            }
        }
    }
        
    return b;
}



bool Board::loadBoardFromFile(std::string filename)
{
    std::ifstream infile;
    std::string line;
    unsigned int row;
    unsigned int temp;
    unsigned int len;
    bool failure;
    
    //std::cout << "Loading board from file..." << std::endl;
    
    infile.open(filename, std::ios::in);
    
    if (!infile.is_open())
    {
        std::cout << "File " << filename << " not found" << std::endl;
        return false;
    }
    
    failure = false;
    getline(infile,line);
    try
    {
        size = (unsigned int)std::stoul(line);
    }
    catch (std::invalid_argument)
    {
        failure = true;        
    }
    
    if (size < minSize || size > maxSize || failure)
    {
        std::cout << "Invalid board size." << std::endl;
        infile.close();
        return false;
    }
   
    

    tiles.resize(size, std::vector<char>(size, emptySpace));
    
    failure = false;
    getline(infile,line);
    try
    {
        numWords = (unsigned int)std::stoul(line);
    }
    catch (std::invalid_argument)
    {
        failure = true;
    }
    
    if (failure)
    {
        std::cout << "Invalid number of words" << std::endl;
        infile.close();
        return false;
    }
    
    

    
    words = std::vector<std::string>(numWords);
    
    len = 0;
    
    for(int i=0;i<numWords;i++)
    {
        failure = false;
        getline(infile,line);
        try
        {
            temp = (unsigned int)std::stoul(line);
        }
        catch (std::invalid_argument)
        {
            failure = true;
        }
        
        if (temp < minWordLength || temp > maxWordLength || failure)
        {
            std::cout << "Invalid word length." << std::endl;
            infile.close();
            return false;
        }
        len += temp;

        words[i] = std::string(temp,'_');

    }
    
    if (len != size*size)
    {
        std::cout << "Invalid total word length." << std::endl;
        infile.close();
        return false;
    }
    

    
    row = 0;
    while (getline(infile, line))
    {
        if (size == 0) 
        {
            tiles.resize(size, std::vector<char>(size, emptySpace));
            if (line.length() >= minSize && line.length() <= maxSize && isValidLine(line))
            {
                size = line.length();
                tiles.resize(size, std::vector<char>(size, emptySpace));
                for(int i=0;i<size;i++)
                {
                    tiles[row][i] = line[i];
                }
                row++;
            }
            else
            {
                if (!isValidLine(line))
                {
                    std::cout << "Failed. Invalid characters in board file" << std::endl;
                }
                else
                {
                    std::cout << "Failed. Board too big" << std::endl;
                }
                infile.close();
                return false;
            }
        }
        else
        {

            if (line.length() == size && isValidLine(line))
            {
                for(int i=0;i<size;i++)
                {
                    tiles[row][i] = line[i];
                } 
                row++;
            }
            else
            {
                if (!isValidLine(line))
                {
                    std::cout << "Failed. Invalid characters in board file" << std::endl;
                }
                else
                {
                    std::cout << "Failed. Inconsistent size." << std::endl;    
                }
                infile.close();
                return false;
            }
        }
    }
    infile.close();
    
    if (row != size)
    {
        std::cout << "Failed. Board not square." << std::endl;    
        return false;
    }
    
    
    currentWord = 0;
    
    return true;    
    
}

unsigned int Board::getSize(void)
{
    return size;
}

unsigned int Board::getWordLength(unsigned int wordNum)
{
    return (unsigned int)words[wordNum].length();
}

unsigned int Board::getCurrentWord(void)
{
    return currentWord;
}

bool Board::complete(void)
{
    return (currentWord == numWords);  
}

std::list<Board> Board::findWord(void)
{
    std::list<Path> paths = {};
    std::list<Path> successfulPaths = {};
    std::list<Path> newpaths;
    std::list<Board> newBoards = {};
    
    
    for (unsigned int i=0;i<size;i++)
    {
        for (unsigned int k=0;k<size;k++)
        {
            if (tiles[i][k] != emptySpace)
            {                
                paths.push_back(Path((*this),words[currentWord].length(),i,k,wordTree->advance(tiles[i][k]),1));
            }
        }
    }
    
    
    do
    {
        if (paths.front().complete())
        {
            successfulPaths.push_back(paths.front());
        }
        else
        {
            /*newpaths = paths.front().search(); 
            while (!newpaths.empty())
            {
                
                paths.push_back(newpaths.front());                
                newpaths.pop_front();
            }*/ 
            paths.front().search(std::back_inserter(paths));
        }
        paths.pop_front();
        
    } while (!paths.empty());
    
    
    while (!successfulPaths.empty()) 
    {
        newBoards.emplace_back((*this), successfulPaths.front());
        successfulPaths.pop_front();
    }       
    return newBoards;
}

unsigned int Board::findWord(std::front_insert_iterator<std::list<Board>> iter)
{
    std::list<Path> paths = {};
    std::list<Path> successfulPaths = {};

    unsigned int added;
    
    added = 0;
    
    
    for (unsigned int i=0;i<size;i++)
    {
        for (unsigned int k=0;k<size;k++)
        {
            if (tiles[i][k] != emptySpace)
            {                
                paths.push_back(Path((*this),words[currentWord].length(),i,k,wordTree->advance(tiles[i][k]),1));
            }
        }
    }
    
    
    do
    {
        if (paths.front().complete())
        {
            successfulPaths.push_back(paths.front());
        }
        else
        {
            paths.front().search(std::back_inserter(paths));
        }
        paths.pop_front();
        
    } while (!paths.empty());
    
    
    while (!successfulPaths.empty()) 
    {
        //newBoards.emplace_back((*this), successfulPaths.front());
        *iter++ = Board((*this), successfulPaths.front());
        added++;
        successfulPaths.pop_front();
    }       
    return added;
}


void Board::printWordList(void)
{
    for (unsigned int i=0;i<numWords;i++)
    {
        std::cout << words[i] << " ";
    }
    std::cout << std::endl;   
}
