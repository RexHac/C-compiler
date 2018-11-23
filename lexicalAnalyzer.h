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
class lexicalAnalyzer
{
    public:
    enum STATE
    {
        NORMAL, OPERATOR, ANNOTATION, STRING, 
        IDENTIFIER, NUMBER, MACRO
    };
    char buffer[MAXBUF];
    char filename[FILENAME];
    FILE *fin,*ferr,*fdoc;
    int forward, lineNum;
    char curChar;
    bool lread, rread,isEndOfFile;
    int endOfFile;
    STATE state;
    lexicalAnalyzer(char *filename, char *filerr, char *filedoc)
    {
        fin = fopen(filename, "r");
        ferr = fopen(filerr, "w");
        fdoc = fopen(filedoc, "w");
    }
    void fillBuffer();
    bool getChar();
    void init();
    void analyze();
    bool tryNext(char c);
    void retract();
};