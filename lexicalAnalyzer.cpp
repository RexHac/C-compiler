#include<stdlib.h>
#include<stdio.h>
#include<iostream>
#include "lexicalAnalyzer.h"
#include "symbleTable.h"
using namespace std;

symbleTable *mySymbleTable;

const char* operatorTable[]=
{
    "+", "-", "*", "/", "%","++","--",
    ">", "<", ">=", "<=", "!=", "==",
    "&&", "||" ,"!",
    "&", "|", "~", "^", "<<", ">>",
    "+=", "-=", "*=", "/=", "%=", 
    "&=", "|=", "^=", "<<=", ">>=",
    "?", ":",
    ",",
    "(", ")", "[", "]", "{", "}", 
    "->", 
    ";", ".",
    "\0"
};

const char* keywordTable[]=
{
	"auto",    "break",   "case",    "char",
    "const",   "continue","default", "do",
    "double",  "else",    "enum",    "extern",
    "float",   "for",     "goto",    "if",
    "int",     "long",    "register","return",
    "short",   "signed",  "static",  "sizeof",
    "struct",  "switch",  "typedef", "union",
    "unsigned","void",    "volatile","while",
    "\0"
};

void lexicalAnalyzer::init()
{

    lread = rread = isEndOfFile = false;
    lineNum = forward = 0;
    endOfFile = -1;
    state = NORMAL;
    mySymbleTable = initSymbleTable();
}
void lexicalAnalyzer::fillBuffer()
{
    if(!lread)
    {
        lread = true;
        rread = false;
        for (int i = 0; i < L_END; i++)
        {
            if((buffer[i] = fgetc(fin)) == EOF)
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
            if((buffer[i] = fgetc(fin)) == EOF)
            {
                endOfFile = i;
                isEndOfFile = true;
                break;
            }
        }
    }
}
bool lexicalAnalyzer::getChar()
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
        else if (forward == R_END)
        {
            forward = START;
        }
    }
}

void lexicalAnalyzer::retract()
{
    if(forward == START)
    {
        forward = R_END - 1;
    }
    else
    {
        forward--;
        if(forward == L_END)
        {
            forward--;
        }
    }
    //注意这里可能有问题
    // curChar = buffer[forward - 1]; shirley version
    curChar = buffer[forward];
    
}
//判断下一个是否和当前的字符相同
bool lexicalAnalyzer::tryNext(char c)
{
    if (getChar())
    {
        if(curChar == c)
        {
            return true;
        }
        retract();
    }
    return false;
}

bool isOperator(char c)
{

}


void lexicalAnalyzer::analyze()
{
    char curWord[MAXBUF];
    int inPtr = 0;
    symble::TYPE curSymbleType = symble::NONE;
    while(getChar())
    {
        if (state == lexicalAnalyzer::NORMAL)
        {
            if(curChar == '#')
            {
                curWord[inPtr++] = curChar;
                state = lexicalAnalyzer::MACRO;
            }
            if(curChar == '/')
            {
                curWord[inPtr++] = curChar;
                if(tryNext('/'))
                {
                    state = lexicalAnalyzer::ANNOTATION;
                }
                else if(tryNext('*'))
                {
                    state == lexicalAnalyzer::ANNOTATION;
                }
                else 
                {

                }
            }
        }
        else if(state == lexicalAnalyzer::MACRO)
        {
            curWord[inPtr++] = curChar;
            if (curChar == '\n')
            {
                curSymbleType = symble::MACRO;
                state = lexicalAnalyzer::NORMAL;
            }
        }
        if (curSymbleType != symble::NONE)
        {
            if(curSymbleType == symble::ANNOTATION)
            {
                fprintf(fdoc, curWord);
            }
            else
            {
                mySymbleTable->insertSymbleTable(initSymble(curWord, curSymbleType));
                if(curSymbleType == symble::ENDSYMBLE)
                {
                    break;
                }
                memset(curWord, 0, sizeof(curWord));
                curSymbleType = symble::NONE;
                inPtr = 0;
            }
        }
    }
    
}