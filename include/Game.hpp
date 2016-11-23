#ifndef __GAMEHPP__
#define __GAMEHPP__

#include "Board.hpp"
#include "Wordtree.hpp"
#include <list>

class Game
{
public:
    Game(Board &b, Wordtree *wt);
    Game(const Game &p);    
    ~Game();
    Game &operator=(const Game &p);    
    void solve(void);
private:
    Board &initialBoard;
    Wordtree *wordTree;
    std::list<Board> activeBoards;
};

#endif // __GAMEHPP__