#ifndef __LOCATIONHPP__
#define __LOCATIONHPP__

class Location
{
public:
    Location(unsigned int r, unsigned int c, char l);
    Location(const Location &p);    
    ~Location();
    Location &operator=(const Location &p);   
    bool operator==(const Location &p);
    unsigned int getRow(void);
    unsigned int getCol(void);
    char getLetter(void);
    void setRC(unsigned int r, unsigned int c);
private:
    unsigned int row;
    unsigned int col;
    char letter;
};

#endif // __LOCATIONHPP__