#include <iostream>
#include "Node.hpp"
#include "Wordtree.hpp"
#include "Board.hpp"
#include "Game.hpp"
#include <string>
#include <ctime>

using namespace std;

int main(int argc, char* argv[])
{
    Node *n, *p;
    Board *b;
    string dictfile;
    time_t start, end;
    
    
    cout << "Wordbrain solver" << endl;

    
    if (argc > 3 || argc < 2)
    {
        cout << "Usage: wordbrain boardfile <dictionary_file>" << endl;
    }
    else
    {

        Wordtree *wt;
        
        dictfile = "linuxwords.txt";
        
        if (argc == 3)
        {
            dictfile = argv[2];
        }
        
        wt = new Wordtree(dictfile);
        wt->populate();
    
        
        
    //b = new Board("testboard.txt", (Node*)wt);
        b = new Board(argv[1], (Node*)wt);
        
        cout << (*b);
            
        Game *g = new Game((*b),wt);
        
        time(&start);
        g->solve();
        time(&end);
        cout << "Time taken: " << difftime(end,start) << "s\n";
        
        
        cout << "Wordfind over.\n";
        
        
        delete b;

        delete g;
        delete wt;
    }
}