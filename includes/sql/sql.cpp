#include "sql.h"

SQL::SQL(){

}

Table SQL::command(const string& command)
{
    char s[300];
    vector<string> table_name;
    vector<string> fields;
    vector<string> field_values;
    // copy the command statement.
    strcpy(s,command.c_str());
    // call parser constructor and generate ptree.
    Parser parser(s);
    MMap<string, string> ptree;
    // get the ptree
    ptree = parser.parse_tree();

    if(parser.success()){
        // get the table names from ptree.
        table_name = ptree["table_name"];
        if(ptree["command"][0] == "make"){
            // get the fields that need to make table for from ptree. 
            fields = ptree["cols"];
            // make a table as private variable and return it.
            _table = Table(table_name[0], fields);
            return _table;
        }
        else if(ptree["command"][0] == "insert"){
            // get the field values that need to be inserted from ptree.
            field_values = ptree["values"];
            // pass the table into private variable.
            _table = Table(table_name[0]);
            // insert the field values and return the table.
            _table.insert_into(field_values);
            return _table;
        }
        else if(ptree["command"][0] == "select"){
            // pass the table into the private variable.
            _table = Table(table_name[0]);
            // get the fields that need to be selected from ptree.
            fields = ptree["fields"];
            bool condition_flag = ptree.contains("condition");
            if(condition_flag == false)
            {
                if (fields[0] == "*"){
                    cout << "There is no condition" << endl;
                    //cout<<_table.select_all();
                    return _table.select_all();
                }
                else{
                    cout << "There is no condition" << endl;
                    return _table.select(fields);
                }
                
            }
            else // there is condition
            {
                // call table select function with vector <string> conditions.
                return _table.select(fields, ptree["condition"]);
            }
        }
        else{
            // command is wrong.
            cout << "The command is wrong!!!" << endl;
            return Table();
        }
    }
    else // not getting a ptee.
    {
        cout<<"The command is wrong!!!"<<endl;
        _table = Table();
        return _table;
    }
}

vector<long> SQL::select_recnos()const
{
    // get selected record numbers from the table.
    return _table.select_recnos();
}

