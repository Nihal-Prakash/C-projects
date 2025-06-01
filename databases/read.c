#include <stdio.h>
#include <stdlib.h>
#include "sqlite/sqlite3.h"

static int callback(void *record, int argc, char **argv, char **nameRef);

int main(void){

    printf("%s \n", sqlite3_libversion());

    //Create a database
    sqlite3 *db;
    char *err_msg = 0;
    int conn;

    //Callback function called
    const char* record = "Student record \n";

    //Open database
    conn = sqlite3_open("students.db", &db);

    //Do a check for database connection
    if(conn != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s \n", sqlite3_errmsg(db));
        return 1;
    } else {
        fprintf (stderr, "Database was opened successfully \n");
    }

    //Create Sql query
    char *sql_qry = "SELECT * FROM degree";

    conn = sqlite3_exec(db, sql_qry, callback, (void*) record, &err_msg);

    if(conn != SQLITE_OK){
        fprintf(stderr, "SQL error: %s \n", err_msg);
        sqlite3_free(err_msg);
    }else{
        fprintf(stdout, "Query successful");
    }
    
    sqlite3_close(db);

    return 0;
}

//Create callback function
static int callback(void *record, int argc, char **argv, char **nameRef){
    // 1. Print out the 'record' string (cast from void* to const char*),
    //    sending it to stderr
    fprintf(stderr, "%s\n", (const char*) record );

    // 2. Loop over each column in this row
    for (int i = 0; i < argc; i++)
    {
        // nameRef[i] is the column name (C‐string),
        // argv[i] is the column value (C‐string or NULL).
        printf("%s = %s \n",
               nameRef[i],
               argv[i] ? argv[i] : "NULL");
    }

    // 3. Print a blank line to separate rows
    printf("\n");

    // 4. Return 0 to tell SQLite: "Everything is fine, keep going."
    return 0;
}