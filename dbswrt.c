#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sqlite/sqlite3.h"

int insert_st(void);
int read_st(void);
static int callback(void *record, int argc, char **argv, char **nameRef);

int main(void){

    sqlite3 *db;
    char *err_msg = 0;

    int conn;
    char mode = '\0';
    conn = sqlite3_open("Student_Records.db", &db);

    //check connection to database
    if(conn != SQLITE_OK){
        fprintf(stderr, "Cannot connect to database %s \n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    //Create a table
    char *sql_qry = "CREATE TABLE IF NOT EXISTS records("
        " student_id INT,"
        " firstname VARCHAR,"
        " lastname VARCHAR,"
        " Year INT"
        ");";

    conn = sqlite3_exec(db, sql_qry, 0, 0, &err_msg);

    //Check query implementation
  /*  if(conn != SQLITE_OK){
        fprintf(stderr, "Unable to create table: %s \n", sqlite3_errmsg(db));

        sqlite3_free(err_msg);
        sqlite3_close(db);
        return 1;
    }else{
        fprintf(stderr, "Table created");
    } */

    sqlite3_close(db);

    printf("----WELCOME TO STUDENT RECORD SYSTEM----\n");
    printf("Enter mode: [I]nsertion, [R]ead");
    scanf(" %c", &mode);

    switch (mode)
    {
    case 'I':
    case 'i':
        insert_st();
        break;

    case 'R':
    case 'r':
        read_st();
        break;

    default:
        printf("Invalid input\n");
        break;
    }

    return 0;
}

int insert_st(void) {
    
    char sql[512];
    int student_id;
    char firstname[64];
    char lastname[64];
    int year;
    int num;

    printf("Enter how many student to be recorded: ");
    scanf("%d", &num);

    for (int i = 0; i < num; i++) {

        sqlite3 *db;
        char *err_msg = 0;

        int conn;
        conn = sqlite3_open("Student_Records.db", &db);
        
        student_id = i+1;
        printf("Enter Year student currently in: ");
        scanf("%d", &year);
        printf("Enter your first name: ");
        getchar();
        fgets(firstname, sizeof(firstname), stdin);
        firstname[strlen(firstname) - 1] = '\0';
        printf("Enter your last name: ");
        fgets(lastname, sizeof(lastname), stdin);
        lastname[strlen(lastname) - 1] = '\0';

        sprintf(sql, "INSERT INTO records VALUES (%d, '%s', '%s', %d);", student_id, firstname, lastname, year);
        conn = sqlite3_exec(db, sql, 0, 0, &err_msg);

        if(conn != SQLITE_OK){
            fprintf(stderr, "Unable to create table: %s \n", sqlite3_errmsg(db));

            sqlite3_free(err_msg);
            sqlite3_close(db);
            return 1;
        }else{
            fprintf(stderr, "Data inserted successfully\n");
        }

        sqlite3_close(db);
    }
}

int read_st(void){

    sqlite3 *db;
    char *err_msg = 0;
    int conn;

    //Callback function called
    const char* record = "\n";

    //Open database
    conn = sqlite3_open("Student_Records.db", &db);

    //Do a check for database connection
    if(conn != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s \n", sqlite3_errmsg(db));
        return 1;
    } else {
        fprintf (stderr, "Database was opened successfully \n");
    }

    //Create Sql query
    char *sql_qry = "SELECT * FROM records";

    conn = sqlite3_exec(db, sql_qry, callback, (void*) record, &err_msg);

    if(conn != SQLITE_OK){
        fprintf(stderr, "SQL error: %s \n", err_msg);
        sqlite3_free(err_msg);
    } else{
        fprintf(stdout, "Query successful");
    }
    
    sqlite3_close(db);

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