#include <stdio.h>
#include "sqlite/sqlite3.h"

int main(void){

    printf("%s \n", sqlite3_libversion());

    //Create a database
    sqlite3 *db;
    int conn;
    conn = sqlite3_open("students.db", &db);

    printf("Created successfully!");



    //close database
    sqlite3_close(db);
    return 0;
}