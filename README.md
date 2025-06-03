# C-projects
## Student Record System

[[C-Website]]

*Features*
1. Add students 🟢
2. Deleting students
3. getting data of a student from their Roll.no or name 🟢
4. assigning a Roll.no 🟢
5. Student Records database 🟢

***Learnings!*** 
1. for say char name[50]  if we want to take input we have to write scanf("%49s", student->name) but for int age we have to write scanf("%d", **&** student->age); this is because **C*** decays student->name into the pointer for thew first element of the string array name[0] but not for int and others
2. strcmp is used to compare strings pointed to by the pointers
3. Databases: SQLite
	   https://www.sqlite.org/cintro.html
	   https://www.sqlite.org/capi3ref.html
	   https://zetcode.com/db/sqlitec/
	   https://www.tutorialspoint.com/sqlite/sqlite_c_cpp.htm
	   ZebraCode series
4. MySQL