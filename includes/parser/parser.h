#ifndef PARSER_H
#define PARSER_H

#include "../tokenizer/stokenize.h"
#include "../table/table.h"
#include "../table/typedefs.h"

class Parser
{
    public:
    Parser();
    Parser(char* str);
    void set_string(char* str);
    void build_keyword_list();
    void make_table();
    bool get_parser_tree();
    long get_column(string str);
    bool success();
    MMap<string,string> parse_tree();

    


    private:
    MMap<string, string> _ptree;
    Map<string, long> _keywords;
    bool flag;
    vector<string> _input_queue;
    enum Keys{ZERO, SELECT, FROM, STAR, SYM, WHERE, INTO, INSERT, MAKE, TABLE, VALUES, FIELDS,RELATIONAL,LOGICAL,PAREN,UNKNOWN};

    static int _table[MAX_ROWS][MAX_COLUMNS];
    char _buffer[MAX_BUFFER];
};

#endif