#include<stdlib.h>
#include<stdio.h>
#include<iostream>

using namespace std;
const int FILENAME=105;
const int MAXBUF=82;
const int L_END=40;
const int R_END=81;
const int START=0;   
//词法分析器类
class lexical_analyzer
{
    public:
    enum STATE
    {
        NORMAL, OPERATOR, ANNOTATION, STRING, 
        IDENTIFIER, NUMBER, MACRO
    }
    char buffer[MAXBUF];
    char filename[FILENAME];
    FILE *fin,*ferr,*fdoc;
    int forward, lineNum;
    char curChar;
    bool lread, rread,isEndOfFile;
    int endOfFile;
    STATE state;
    lexical_analyzer(char *filename, char *filerr, char *filedoc)
    {
        fin = fopen(filename, "r");
        ferr = fopen(filerr, "w");
        fdoc = fopen(filedoc, "w");
    }
    void fillBuffer();
    bool getChar();
    void init();
    void analyze();
    
    
}
void lexical_analyzer::init()
{

    lread = rread = isEndOfFile = false;
    lineNum = forward = 0;
    endOfFile = -1;
    state = NORMAL;
}
void lexical_analyzer::fillBuffer()
{
    if(!lread)
    {
        lread = true;
        rread = false;
        for (int i = 0; i < L_END; i++)
        {
            if(buffer[i] = fgetc(fin)) == EOF)
            {
                endOfFile = i;
                isEndOfFile = true;
                break;
            }
        }
    }
    else if(lread && !rread)
    {
        rread = true;
        lread = false;
        for (int i = L_END + 1; i < R_END; i++)
        {
            if(buffer[i] = fgetc(fin)) == EOF)
            {
                endOfFile = i;
                isEndOfFile = true
                break;
            }
        }
    }
}
bool lexical_analyzer::getChar()
{
    if(forward == endOfFile && isEndOfFile)
    {
        return false;
    }
    curChar = buffer[forward];
    if (curChar == '\n')
    {
        lineNum++;
    }
    forward++;
    if(buffer[forward] == EOF)
    {
        if (!isEndOfFile)
        {
            fillBuffer();
        }
        if (forward == L_END)
        {
            forward++;
        }
        else if (forward == R_LED)
        {
            forward = START;
        }
    }
}

void lexical_analyzer::analyze()
{
    char curWord[MAXBUF];
    int inPtr = 0;
    
}