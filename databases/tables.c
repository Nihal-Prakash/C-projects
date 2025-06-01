#include <stdio.h>
#include "sqlite/sqlite3.h"

int main(void){

    sqlite3 *db;
    char *err_msg = 0;

    int conn;
    conn = sqlite3_open("students.db", &db);

    //check connection to database
    if(conn != SQLITE_OK){
        fprintf(stderr, "Cannot connect to database %s \n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    //Create a table
    char *sql_qry = "DROP TABLE IF EXISTS degree;"
    "CREATE TABLE degree(student_id INT, firstname TEXT, lastname TEXT);"
    "INSERT INTO degree VALUES (0001, 'Harry', 'Potter');"
    "INSERT INTO degree VALUES (0002, 'Hermione', 'Granger');"
    "INSERT INTO degree VALUES (0003, 'Ronald', 'Wesley');";

    //Execute the query
    conn = sqlite3_exec(db, sql_qry, 0, 0, &err_msg);

    //Check query implementation
    if(conn != SQLITE_OK){
        fprintf(stderr, "Unable to create table: %s \n", sqlite3_errmsg(db));

        sqlite3_free(err_msg);
        sqlite3_close(db);
        return 1;
    }else{
        fprintf(stderr, "Table created and data inserted successfully");
    }


    sqlite3_close(db);
    return 0;
}