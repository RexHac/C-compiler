
class symble
{
    public:
    enum TYPE
    {
        NONE, KEYWORD, NUMBER, IDENTIFIER, 
        OPERATOR, ANNOTATION, STRING, 
        ENDSYMBLE, INT, FLOAT, MACRO
    };
    TYPE type;
    char *value;
    int length;
    symble *next;
    
};
symble *initSymble(char *curSymble, symble::TYPE type);

class symbleTable
{
    public:
    symble *head;
    void printSymbleTable();
    void insertSymbleTable(symble *curSymble);
};
symbleTable* initSymbleTable();
