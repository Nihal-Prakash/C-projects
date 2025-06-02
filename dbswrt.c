#include <stdio.h>
#include <string.h>
#include "sqlite/sqlite3.h"

int main(void){

    sqlite3 *db;
    char *err_msg = 0;

    int conn;
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
        " firstname TEXT,"
        " lastname TEXT"
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

    char sql[512];
    int student_id;
    char firstname[64];
    char lastname[64];
    int num;

    printf("----WELCOME TO STUDENT RECORD SYSTEM----\n");
    printf("Enter how many student to be recorded: ");
    scanf("%d", &num);

    for (int i = 0; i < num; i++) {

        sqlite3 *db;
        char *err_msg = 0;

        int conn;
        conn = sqlite3_open("Student_Records.db", &db);
        

        printf("Enter Student ID: ");
        scanf("%d", &student_id);
        printf("Enter your first name: ");
        getchar();
        fgets(firstname, sizeof(firstname), stdin);
        firstname[strlen(firstname) - 1] = '\0';
        printf("Enter your last name: ");
        fgets(lastname, sizeof(lastname), stdin);
        lastname[strlen(lastname) - 1] = '\0';

        sprintf(sql, "INSERT INTO records VALUES (%d, '%s', '%s');", student_id, firstname, lastname);
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
    return 0;
}