#include "Game.hpp"
#include "Board.hpp"
#include "Wordtree.hpp"
#include "Path.hpp"
#include <list>
#include <iostream>
#include <iterator>

Game::Game(Board &b, Wordtree *wt)
: initialBoard(b),
  wordTree(wt),
  activeBoards(std::list<Board>())
{
    
}

Game::Game(const Game &p)
: initialBoard(p.initialBoard),
  wordTree(p.wordTree),
  activeBoards(p.activeBoards)
{

    
}
    
Game &Game::operator=(const Game &p)               
{
    if (this != &p)
    {
        initialBoard = p.initialBoard;
        wordTree = p.wordTree;
        activeBoards = p.activeBoards;
    }
    return *this;
}
    
Game::~Game()
{
    
}

void Game::solve(void)
{
    std::list<Board> boards = {};
    std::list<Board> successfulBoards = {};
    std::list<Board> newboards;
    unsigned int added;
    
    boards.push_back(initialBoard);
    

    do
    {
        if (boards.front().complete())
        {
            successfulBoards.push_back(boards.front());
            boards.pop_front();
        }
        else
        {
            auto it = boards.begin();
            added = boards.front().findWord(std::front_inserter(boards));
            boards.erase(it);
        }
        
       
        
    } while (!boards.empty());
   
    std::cout << "Found " << successfulBoards.size() << " possible outcomes.\n"; 
    
    unsigned int i = 1;
    while (!successfulBoards.empty())
    {
        std::cout << i++ << ": ";
        successfulBoards.front().printWordList();
        successfulBoards.pop_front();
    }
    
}

