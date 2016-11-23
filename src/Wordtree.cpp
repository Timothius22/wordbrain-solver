#include "Wordtree.hpp"
#include "Node.hpp"
#include <string>
#include <fstream>
#include <iostream>

Wordtree::Wordtree(std::string filename)
: Node('\0'), 
  fileName(filename)
{
}

Wordtree::Wordtree(const Wordtree &p)
: Node('\0'),
  fileName(p.fileName)
{
    
}

Wordtree &Wordtree::operator=(const Wordtree &p)    
{
    if (this != &p)
    {
        fileName = p.fileName;
    }
    return *this;
}

Wordtree::~Wordtree()
{
}

bool Wordtree::populate(void)
{
    std::ifstream infile;
    std::string line;
    Node *currentNode;
    
    std::cout << "Populating word tree..." << std::endl;
    
    infile.open(fileName, std::ios::in);
    
    if (!infile.is_open())
    {
        return false;
    }
    while (getline(infile, line))
    {
        if (isValidWord(line))
        {
            if (line.length() >= minLength && line.length() <= maxLength)
            {
                currentNode = addNode(line[0]);
                for(unsigned int i = 1; i < line.length()-1; i++)
                {
                    currentNode = currentNode->addNode(line[i]);
                }
                currentNode = currentNode->addNode(line.back(), true);
            }
        }
    }
    infile.close();
    return true;
}

bool Wordtree::findWord(std::string word)
{
    Node *n;
    auto it = word.begin();
    unsigned int remaining;
    
    n = this;
    remaining = word.length();
    
    do
    { 
        n = n->advance((char)(*it));
        remaining--;
        if (!remaining && n->isWordEnd())
        {
            return true;
        }
        it++;
    } while (n != nullptr);
    return false;
}

bool Wordtree::isValidWord(std::string word)
{
    bool good;
    
    good = true;
    for (unsigned int i=0;i<word.length();i++)
    {
        if (word[i] < 'a' || word[i] > 'z')
        {
            good = false;
        }      
    }
    return good;
}