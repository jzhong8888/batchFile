#include "table.h"
#include "../shunting_yard/shunting_yard.h"

static long serial_num = 0;

Table::Table(){
    r = FileRecord();
    size = 0;
    table_name = "empty";
    //serial_num++;
}

// pass in an existing table
Table::Table(const string& name){
    fstream f;
    size = 0;
    table_name = name;
    string field_txt = name+"_field.txt";
    //open the field names file.
    open_fileRW(f, field_txt.c_str());
    int i = 0;
    // put one file record into r.
    // bytes_read will get the bytes read.
    long bytes_read = r.read(f, i); 
    // set fileds in the file
    set_fields(r.vector_string());
    f.close();

    //open the bin file for all the records
    string bin_name = table_name+".bin";
    open_fileRW(f, bin_name.c_str());
    i=0;

    // fill the datas from table into r. 
    //bytes_read = how many bytes was read.
    bytes_read =r.read(f,i);
    // after the very last file record, there will be noting to read.
    // so, bytes_read will become zero.
    while(bytes_read>0){
        reindex(r.vector_string(),i);
        i++;
        bytes_read = r.read(f,i);
        size++;
    }
    f.close();  
    serial_num++;
}

// new a table with a name and field names
Table::Table(const string& name, const vector<string> fields){
    fstream f;
    table_name = name;
    size = 0;

    // open the bin file
    string bin_file = table_name + ".bin";
    open_fileW(f, bin_file.c_str());
    f.close();
    

    string field_txt=name+"_field.txt";
    // open the field name txt file
    open_fileW(f, field_txt.c_str());
    // build and write the file record with the fields provided into the file.
    FileRecord r(fields);
    r.write(f);
    f.close();

    //set fields for the table
    set_fields(fields);
    serial_num++;
}

// set up (insert into) the indicies mmap.
void Table::reindex(vector<string> field_values, long recno){
    for (int i = 0; i < field_values.size(); i++){
        indicies_mmap[i].insert(field_values[i], recno);
    }
}

// insert the values into the table.
void Table::insert_into(vector<string> field_values){
    fstream f;
    string bin_file = table_name + ".bin";
    open_fileRW(f, bin_file.c_str());
    r=FileRecord(field_values);
    long recno;
    recno = r.write(f);
    // for (int i = 0; i < field_values.size(); i++){
    //     field_indices[i].insert(field_values[i], recno);
    // }
    reindex(field_values, recno);
    f.close();
    size++;
}

// set fields for the table
// set the field names and the indicies mmap and field map.
void Table::set_fields(vector<string> field_name){
    field_names = field_name;
    for (int i = 0; i < field_name.size();i++){
        indicies_mmap.push_back(MMap<string, long>());
        field_map.insert(field_name[i], i);
    }
}

// select all for the table
// return a same table
Table Table::select_all(){
    selected_recno.clear();
    fstream f;
    FileRecord r;
    string name = "_select_table_" + to_string(serial_num);
    //create a table
    Table t(name, field_names);

    //open the binary file
    string bin_name = table_name + ".bin";
    open_fileRW(f, bin_name.c_str());
    int i = 0;
    vector<string> record;
    
    //fill in datas into r and get the bytes read
    long bytes_read = r.read(f, i);
    // after the very last file record, there will be noting to read.
    // so, bytes_read will become zero.
    while (bytes_read > 0){
        // record variable get only one FileRecord info including First, Last, Department.
        record = r.vector_string();
        vector<string> content;
        // content variable get the values (field by field) of First, Last, Department.
        for (int j=0; j<field_names.size(); j++){
            content += record[field_map[field_names[j]]];
        }
        // insert content into the table
        t.insert_into(content);
        // put all the selected record numbers into indices.
        selected_recno.push_back(i);
        i++;
        // update bytes_read. bytes_read will be zero if reach the end.
        bytes_read = r.read(f, i);
    }
    f.close();
    serial_num++;
    return t;
}


void Table::select_all() const{
    fstream f;
    FileRecord r2;
    // open the field name txt
    string field_txt = table_name+"_field.txt";
    if(file_exists(field_txt.c_str())){
        // open the binary file for reading the file record.
        open_fileRW(f, field_txt.c_str());
        int i = 0;
        // fill in datas into r2
        long bytes_read = r2.read(f, i);
        // after the very last file record, there will be noting to read.
        // so, bytes_read will become zero.
        cout << setw(26) << "record";
        while (bytes_read > 0){
            cout <<setw(26)<<  r2 << endl;
            i++;
            bytes_read = r2.read(f, i);
        }
        f.close();

        // open the binary file
        string bin_name = table_name + ".bin";
        open_fileRW(f, bin_name.c_str());
        i = 0;
        // fill in datas into r2 from table
        bytes_read = r2.read(f, i);
        // after the very last file record, there will be noting to read.
        // so, bytes_read will become zero.
        while(bytes_read > 0){
            cout << setw(26) << i  << r2 << endl;
            i++;
            bytes_read = r2.read(f, i);
        }
        f.close();
    }
    
}

// select fuction with condition
Table Table::select(vectorstr fields, string field, string condition, const string& entry){
    Queue<Token*> post_fix;
    post_fix.push(new TokenStr(field));
    post_fix.push(new TokenStr(entry));
    post_fix.push(new Relational(condition));
    return select(fields, post_fix);
}



ostream& operator<<(ostream& outs, const Table& t)
{
    outs<<"Table name: "<<t.table_name <<", records: "<<t.size<<endl;
    t.select_all();
    return outs;
}

// select some fields from the table.
Table Table::select(vectorstr fields)
{
    // clear the selected record numbers first.
    selected_recno.clear();
    fstream f;
    FileRecord r;
    // create a table called select.
    string name ="_select_table_";
    Table t(name,fields);
    // open the binary file
    string bin_name = table_name + ".bin";
    open_fileRW(f, bin_name.c_str());
    int i = 0;
    vector <string> record;
    // fill the information of the table into r. (one file record)
    // the bytes_read saved the bytes read. (one file record)
    long bytes_read = r.read(f, i); 
    // after the very last file record, there will be noting to read.
    // so, bytes_read will become zero.
    while (bytes_read > 0){
        // convert the one file record into vector of string and put them into record.
        record=r.vector_string();
        // use variable content to store the values from each field.
        vector<string> content;
        // put the information into content field by field.
        for(int j=0; j<fields.size(); j++)
        {
            content+=record[field_map[fields[j]]];
        }
        // insert the content information into the table.
        t.insert_into(content);
        // store the selected record numbers.
        selected_recno.push_back(i);
        // update i and bytes_read to see is there more things to read.
        i++;
        bytes_read = r.read(f, i);
    }
    f.close();
    serial_num++;
    return t;
}

Table Table::select(vectorstr fields, const Queue<Token*>& post){
    // clear the selected record numbers first.
    selected_recno.clear();
    fstream f;
    string name = "_select_table_" + to_string(serial_num);
    Table t(name, fields);
    // put the Queue of Token* into the queue_rpn private variable,
    // so, it is ready to run through rpn.
    //queue_rpn = post;
    RPN rpn(post);
    vector<long> recno;
    recno = rpn.evaluate(field_map, indicies_mmap);
 
    vector<string> record_holder;

    // open the binary file
    string bin_name = table_name + ".bin";
    open_fileRW(f, bin_name.c_str());
    for (int i = 0; i < recno.size(); i++){
        r.read(f, recno[i]);
        // each time put one record into the record holder.
        record_holder = r.vector_string();
        vector<string> content;
        for (int j=0; j < fields.size(); j++){
            content += record_holder[field_map[fields[j]]];
        }
        t.insert_into(content);
        selected_recno.push_back(recno[i]);
    }
    serial_num++;
    return t;
}


Table Table::select(vector<string> fields, const vector<string>& condition){
    Queue<Token*> condi;
    for (int i = 0; i < condition.size(); i++){
        if (condition[i] == "<" || condition[i] == ">" || condition[i] == "<=" ||condition[i]==">="||condition[i]=="="){
            condi.push(new Relational(condition[i]));
        }
        else if(condition[i] == "and"|| condition[i] == "or")
        {
            condi.push(new Logical(condition[i]));
        }
        else if(condition[i] == "(")
        {
            condi.push(new LeftParen());
        }
        else if(condition[i] == ")")
        {
            condi.push(new RightParen());
        }
        else
        {
            condi.push(new TokenStr(condition[i]));
        }
    }
    ShuntingYard sy(condi);
    Queue<Token*> condi_sy = sy.postfix();
    serial_num++;
    return select(fields, condi_sy);
}

vector<long> Table::select_recnos() const
{
    return selected_recno;
}
