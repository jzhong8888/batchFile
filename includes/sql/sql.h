#ifndef SQL_H
#define SQL_H

#include "../table/typedefs.h"
#include "../table/table.h"
#include "../parser/parser.h"
#include <iostream>
#include <iomanip>
using namespace std;

class SQL
{
    public:
    SQL();
    Table command(const string& command);
    // get the selected recnos.
    vector <long> select_recnos() const;
   
    private:
    Table _table;
};


#endif