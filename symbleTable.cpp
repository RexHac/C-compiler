#include "symbleTable.h"
#include<iostream>
#include<stdio.h>
#include<stdlib.h>
using namespace std;


//初始化一个符号结点
symble* initSymble(char *curSymble = NULL, symble::TYPE type = symble::NONE)
{
    symble *newSymble = (symble*)malloc(sizeof(symble));
    newSymble->type = type;
    newSymble->next = NULL;
    if(curSymble == NULL)
    {
        newSymble->length = -1;
        newSymble->value = NULL;
        return newSymble;
    }
    char *temp = curSymble;
    int length = 0;
    while(*temp != '\0')
    {
        temp++;
        length++;
    }
    newSymble->length = length;
    newSymble->value = (char*)malloc(sizeof(char)*length);
    for(int i = 0; i< length; i++)
    {
        *(newSymble->value + i) = *(curSymble + i); 
    }
    return newSymble;
}

//初始化一个符号表
symbleTable* initSymbleTable()
{
    symbleTable *newTable = (symbleTable*)malloc(sizeof(symbleTable));
    newTable->head = initSymble();
    return newTable;
}

//往符号表里插入一个符号，该符号是在插入前已经被初始化，重复的符号不再插入
void symbleTable::insertSymbleTable(symble *curSymble)
{
    symble *findP = head;
    // if(curSymble->type == symble::NUMBER || curSymble->type == symble::KEYWORD)
    // {
    bool isDuplicate = false;
    while(findP->next != NULL)
    {
        findP = findP->next;
        if((findP->length == curSymble->length)&&(findP->type == curSymble->type))
        {
            for(int i = 0; i < findP->length; i++)
            {
                if(*(findP->value + i) != *(curSymble->value + i))
                {
                    isDuplicate = true;
                    break;
                } 
            }
        }
        if(isDuplicate)
        {
            break;
        }
    }
    findP->next = curSymble;
    // }
}

//打印符号表
void symbleTable::printSymbleTable()
{
    symble *temp = head;
    while (temp->next != NULL)
    {
        temp = temp->next;
        printf("%-18s%s\n",
            temp->type == symble::MACRO ? "MACRO" :
            temp->type == symble::KEYWORD ? "KEYWORD" :
            temp->type == symble::INT ? "INT" :
            temp->type == symble::FLOAT ? "FLOAT" :
            temp->type == symble::IDENTIFIER ? "IDENTIFIER" :
            temp->type == symble::ANNOTATION ? "ANNOTATION" :
            temp->type == symble::OPERATOR ? "OPERATOR" :
            temp->type == symble::STRING ? "STRING" :
            temp->type == symble::ENDSYMBLE ? "ENDSYMBLE" :
            "Wrong syntax", temp->value);
    }
}
