#include "parser.h"
#include "string"

int Parser::_table[MAX_ROWS][MAX_COLUMNS];

Parser::Parser(){
    make_table();
    build_keyword_list();
    flag = false;
}

Parser::Parser(char* str){
    set_string(str);
}

bool Parser::success()
{
    return flag;
} 

void Parser::set_string(char* str){
    // make sure nothing is stored in here first.
    _ptree.clear();
    _keywords.clear();
    _input_queue.clear();
    // copy str to internal buffer
    strcpy(_buffer, str);


    STokenizer stk(_buffer);
    Token_Par t;
    string hold;

    // tokenize input buffer into input queue.
    while(stk.more()){
        Token_Par t;
        stk >> t;
        // if it is string, then erase the "" at begin and end.
        if(t.type_string()=="STRING"){
        hold = t.token_str();
        // cout << "hold: " << hold << endl;
        hold.erase(hold.begin());
        // cout << "hold after erase: " << hold << endl;
        hold.pop_back();
        _input_queue.push_back(hold);
        }
        else if(t.type_string()!="SPACE" && t.type_string()!="PUNC")
        {
            _input_queue.push_back(t.token_str());
        }
    }

    // make adjacency table.
    make_table();

    // build keyword list.
    build_keyword_list();

    // calls get_parser_tree and reset fail flag.
    flag = get_parser_tree();
}


// maps tokens to keyword constants like: SELECT, FROM, or SYM(symbol).
long Parser::get_column(string str)
{
    bool flag;
    flag =_keywords.contains(str);
    if(flag){
            return _keywords[str];
    }
    else{
        return SYM;
    }
}

bool Parser::get_parser_tree(){
    
    int state = 0;
    int column;
    string yes = "yes";
    //cout<<"input queue is "<<input_queue<<endl;
    for(int i=0; i<_input_queue.size(); i++)
    {
        column = get_column(_input_queue[i]);
        if(_table[state][column] != -1)
        {
            switch(state){
                case 0:
                {
                    _ptree["command"]+=_input_queue[i];
                    state=_table[state][column];
                    break;
                }
                case 1:
                {
                    if(column==FROM || column==TABLE || column==INTO)
                    {
                        state=_table[state][column];
                        break;
                    }
                    _ptree["fields"]+=_input_queue[i];
                    state=_table[state][column];
                    break;
                }
                case 2:
                {
                    _ptree["cols"]+=_input_queue[i];
                    state=_table[state][column];
                    break;
                }
                case 3:
                {
                    _ptree["table_name"]+=_input_queue[i];
                    state=_table[state][column];
                    break;
                }
                case 4:
                {
                    if(column==WHERE)
                    {
                        _ptree["where"]+=yes;
                        state=_table[state][column];
                        break;
                    }
                    else if(column==FIELDS)
                    {
                        _ptree["cols"];
                        state=_table[state][column];
                        break;
                    }
                    else if(column==VALUES)
                    {
                        _ptree["values"];
                        state=_table[state][column];
                        break;
                    }
                    else if(column==SYM)
                    {
                        _ptree["condition"];
                        state=_table[state][column];
                        break;
                    }
                }
                case 5:
                {
                    _ptree["condition"]+=_input_queue[i];
                    state=_table[state][column];
                    break;
                }
                case 6:
                {
                    _ptree["values"]+=_input_queue[i];
                    state=_table[state][column];
                    break;
                }
                default:
                {
                    state=_table[state][column];
                    break;
                }  
            }
        }
    }
    if(_table[state][0] == 1){
        return true;
    }
    else
    {
        _ptree.clear();
        return false;
    }
}


void Parser::build_keyword_list()
{
    _keywords.insert("select", SELECT);
    _keywords.insert("from", FROM);
    _keywords.insert("*", STAR);
    _keywords.insert("where", WHERE);
    _keywords.insert("make", MAKE);
    _keywords.insert("into", INTO);
    _keywords.insert("insert", INSERT);
    _keywords.insert("table", TABLE);
    _keywords.insert("values", VALUES);
    _keywords.insert("fields", FIELDS);
     
}

void Parser::make_table()
{
    init_table(_table);
    mark_fail(_table,0);
    mark_fail(_table,1);
    mark_fail(_table,3);
    mark_success(_table,4);
    mark_success(_table,2);
    mark_success(_table,6);
    mark_success(_table,5);

    // stage 1 is Command: Select, Make and Insert
    mark_cell(0,_table,SELECT,1);
    mark_cell(0,_table,MAKE,1);
    mark_cell(0,_table,INSERT,1);

    // stage 3 is the preposition: into, from, OR pronoun: table （not the table name).
    mark_cell(1,_table,TABLE,3);
    mark_cell(1,_table,INTO,3);
    // stage 1 + SYM = field names
    mark_cell(1,_table,SYM,1);
    mark_cell(1,_table,STAR,1);
    mark_cell(1,_table,FROM,3);
    // stage 3 + SYM = table name.
    mark_cell(3,_table,SYM,4);
    mark_cell(4,_table,SYM,4);
    // stage 4 (table name) + where = ready to get the condition
    mark_cell(4,_table,WHERE,5);
    //stage 4 + values = pronoun: values (not the actual value)
    mark_cell(4,_table,VALUES,6);
    // stage 4 (table name) + fields = pronoun: fields (not field names)
    mark_cell(4,_table,FIELDS,2);
    // stage 2 (fields) + symbol = field names
    mark_cell(2,_table,SYM,2);
    // stage 6 (pronoun: value) + Symbol = actual value
    mark_cell(6,_table,SYM,6);
    // stage 5 (where) + Symbol = condition
    mark_cell(5,_table,SYM,5);
}

MMap<string,string> Parser::parse_tree(){
    return _ptree;
}