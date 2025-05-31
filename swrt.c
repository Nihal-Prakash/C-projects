#include <stdio.h>
#include <stdbool.h>

typedef struct {
    char name[50];
    int age;
    float gpa;
    bool isFullTime;
} Student;

FILE *pfile;
void printStudent(Student student, int roll);
void scanStudent(Student* student);

int main(void) {

    int num = 0;

    printf("Welcome to the Student Record System!\n");
    printf("Enter number of students to be registered: ");
    scanf("%d", &num);

    pfile = fopen("Student_records.txt", "a");

    if (pfile == NULL) {
        printf("Error opening file\n");
        return 1;
    }

    for (int i = 0; i < num; i++) {
        Student student;
        scanStudent(&student);

        printStudent(student, i+1);
    }

    fclose(pfile);

    return 0;
}

void printStudent(Student student, int roll) {
    fprintf(pfile, "Roll no.: %4d\n", roll);
    fprintf(pfile, "\n");
    fprintf(pfile, "Name: %s\n", student.name);
    fprintf(pfile, "Age: %d\n", student.age);
    fprintf(pfile, "GPA: %.2f\n", student.gpa);
    fprintf(pfile, "Fulltime? : %s\n", student.isFullTime ? "Yes" : "No");
    fprintf(pfile, "\n");
}

void scanStudent(Student* student) {
    printf("Name: ");
    scanf("%49s", student->name); 
    printf("Age: ");
    scanf("%d", &student->age);
    printf("GPA: ");
    scanf("%f", &student->gpa);
    printf("Is full-time (1 for Yes, 0 for No): ");
    int fullTime;
    scanf("%d", &fullTime);
    student->isFullTime = (fullTime != 0);
}

