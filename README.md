# C-projects
Learning C in production

*Features*
1. Add students 🟢
2. Deleting students
3. getting data of a student from their Roll.no or name
4. assigning a Roll.no



:LiAlertCircle: ***Learnings!*** 
1. for say char name[50]  if we want to take input we have to write scanf("%49s", student->name) but for int age we have to write scanf("%d", **&** student->age); this is because **C*** decays student->name into the pointer for thew first element of the string array name[0] but not for int and others
2. 
