#ifndef TABLE_H
#define TABLE_H

#include "../../includes/binary_files/file_record.h"
#include "../../includes/binary_files/utilities.h"
#include "../../includes/bplustree/map.h"
#include "../../includes/bplustree/multimap.h"
#include "typedefs.h"
#include "../shunting_yard/shunting_yard.h"

using namespace std;

class Table{
    public:
    Table();
    Table(const string& name);
    Table(const string& name, const vector<string> fields);
    void insert_into(vector<string> field_values);
    void set_fields(vector<string> field_name);
    void reindex(vector<string> field_values, long recno);


    Table select_all();
    Table select(vectorstr fields);
    void select_all() const;
    
    Table select(vectorstr fields, string field, string condition, const string& entry);
    
    
    Table select(vectorstr fields, const Queue<Token*>& post);



    Table select(vectorstr fields, const vectorstr& condition);

    friend ostream& operator<<(ostream& outs, const Table& t);

    vector<long> select_recnos() const;


    
    private:
    vector<string> field_names;
    vector<MMap<string, long> > indicies_mmap;
    Map<string, long> field_map;
    
    string table_name;
    FileRecord r;
    int size;
    vector<long> selected_recno;
    Queue<Token*>queue_rpn;
    
};




#endif