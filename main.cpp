#include <iostream>
#include <iomanip>

#include "includes/sql/sql.h"


using namespace std;

int main(int argv, char** argc) {
    cout << "\n\n"
         << endl;

    SQL sql;
    sql.command("make table student fields last, first, age");
    sql.command("insert into student values Smith, John, 20");
    sql.command("insert into student values \"Zhong\", Jason, 22");

    sql.command("select first from student where age > 20");
    cout << "record numbers: " << sql.select_recnos() << endl;

    sql.command("select * from student");
    cout << "record numbers: " << sql.select_recnos() << endl;

    cout << "\n\n\n=====================" << endl;
    return 0;
}
