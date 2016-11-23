#include "Location.hpp"

Location::Location(unsigned int r, unsigned int c, char l)
: row(r),
  col(c),
  letter(l)
{
    
}

Location::Location(const Location &p)
: row(p.row),
  col(p.col),
  letter(p.letter)
{

    
}
    
Location &Location::operator=(const Location &p)               
{
    if (this != &p)
    {
        row = p.row;
        col = p.col;
        letter = p.letter;
    }
    return *this;
}
    
Location::~Location()
{
    
}

bool Location::operator==(const Location &p)
{   
    return ((p.row == row) && (p.col == col));
}



unsigned int Location::getRow(void)
{
    return row;
}

unsigned int Location::getCol(void)
{
    return col;
}

char Location::getLetter(void)
{
    return letter;
}

void Location::setRC(unsigned int r, unsigned int c)
{
    row = r;
    col = c;
}