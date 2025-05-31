#include <stdio.h>
#include <stdbool.h>

typedef struct {
    char name[50];
    int age;
    float gpa;
    bool isFullTime;
} Student;

FILE *pfile;
void printStudent(Student student);
void scanStudent(Student* student);

int main(void) {
    Student student1 = {"", 0, 0.0, true};
    Student student2 = {"", 0, 0.0, true};
    
    scanStudent(&student1);
    scanStudent(&student2);

    pfile = fopen("Student_records.txt", "a");

    if (pfile == NULL) {
        printf("Error opening file\n");
        return 1;
    }

    printStudent(student1);
    printStudent(student2);

    fclose(pfile);
    return 0;
}

void printStudent(Student student) {
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
    // Use %49s to avoid buffer overflow
    printf("Age: ");
    scanf("%d", &student->age);
    printf("GPA: ");
    scanf("%f", &student->gpa);
    printf("Is full-time (1 for Yes, 0 for No): ");
    int fullTime;
    scanf("%d", &fullTime);
    student->isFullTime = (fullTime != 0);
}
