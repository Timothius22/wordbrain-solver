#ifndef __WORDLISTHPP__
#define __WORDLISTHPP__

class Wordlist
{
public:
    Wordlist();
    Wordlist(const Wordlist &p);    
    ~Wordlist();
    Wordlist &operator=(const Wordlist &p);
};

#endif // __WORDLISTHPP__