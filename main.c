#include <stdio.h>
#include <stdlib.h>

struct Student
{
    int id;
    char name[50];
    float marks;
};

char calculateGrade(float marks)
{
    if (marks >= 90)
        return 'A';
    else if (marks >= 75)
        return 'B';
    else if (marks >= 60)
        return 'C';
    else if (marks >= 40)
        return 'D';
    else
        return 'F';
}

void addStudent()
{
    struct Student s;
    FILE *fp = fopen("data.txt", "a");

    printf("\nEnter Student ID: ");
    scanf("%d", &s.id);

    printf("Enter Student Name: ");
    scanf("%s", s.name);

    printf("Enter Student Marks: ");
    scanf("%f", &s.marks);

    fprintf(fp, "%d %s %.2f\n", s.id, s.name, s.marks);

    fclose(fp);

    printf("\nStudent Added Successfully!\n");
}

void viewStudents()
{
    struct Student s;
    FILE *fp = fopen("data.txt", "r");

    if (fp == NULL)
    {
        printf("\nNo Records Found!\n");
        return;
    }

    printf("\nID\tName\tMarks\tGrade\n");
    printf("----------------------------------\n");

    while (fscanf(fp, "%d %s %f", &s.id, s.name, &s.marks) != EOF)
    {
        printf("%d\t%s\t%.2f\t%c\n",
               s.id,
               s.name,
               s.marks,
               calculateGrade(s.marks));
    }

    fclose(fp);
}

void searchStudent()
{
    struct Student s;
    int id, found = 0;

    FILE *fp = fopen("data.txt", "r");

    if (fp == NULL)
    {
        printf("\nNo Records Found!\n");
        return;
    }

    printf("\nEnter Student ID to Search: ");
    scanf("%d", &id);

    while (fscanf(fp, "%d %s %f", &s.id, s.name, &s.marks) != EOF)
    {
        if (s.id == id)
        {
            printf("\nStudent Found!\n");
            printf("ID    : %d\n", s.id);
            printf("Name  : %s\n", s.name);
            printf("Marks : %.2f\n", s.marks);
            printf("Grade : %c\n", calculateGrade(s.marks));
            found = 1;
            break;
        }
    }

    if (!found)
        printf("\nStudent Not Found!\n");

    fclose(fp);
}

void updateStudent()
{
    struct Student s;
    int id, found = 0;

    FILE *fp = fopen("data.txt", "r");
    FILE *temp = fopen("temp.txt", "w");

    if (fp == NULL)
    {
        printf("\nNo Records Found!\n");
        return;
    }

    printf("\nEnter Student ID to Update: ");
    scanf("%d", &id);

    while (fscanf(fp, "%d %s %f", &s.id, s.name, &s.marks) != EOF)
    {
        if (s.id == id)
        {
            found = 1;

            printf("Enter New Name: ");
            scanf("%s", s.name);

            printf("Enter New Marks: ");
            scanf("%f", &s.marks);
        }

        fprintf(temp, "%d %s %.2f\n", s.id, s.name, s.marks);
    }

    fclose(fp);
    fclose(temp);

    remove("data.txt");
    rename("temp.txt", "data.txt");

    if (found)
        printf("\nStudent Updated Successfully!\n");
    else
        printf("\nStudent Not Found!\n");
}

void deleteStudent()
{
    struct Student s;
    int id, found = 0;

    FILE *fp = fopen("data.txt", "r");
    FILE *temp = fopen("temp.txt", "w");

    if (fp == NULL)
    {
        printf("\nNo Records Found!\n");
        return;
    }

    printf("\nEnter Student ID to Delete: ");
    scanf("%d", &id);

    while (fscanf(fp, "%d %s %f", &s.id, s.name, &s.marks) != EOF)
    {
        if (s.id == id)
        {
            found = 1;
            continue;
        }

        fprintf(temp, "%d %s %.2f\n", s.id, s.name, s.marks);
    }

    fclose(fp);
    fclose(temp);

    remove("data.txt");
    rename("temp.txt", "data.txt");

    if (found)
        printf("\nStudent Deleted Successfully!\n");
    else
        printf("\nStudent Not Found!\n");
}

void totalStudents()
{
    struct Student s;
    int count = 0;

    FILE *fp = fopen("data.txt", "r");

    if (fp == NULL)
    {
        printf("\nNo Records Found!\n");
        return;
    }

    while (fscanf(fp, "%d %s %f", &s.id, s.name, &s.marks) != EOF)
    {
        count++;
    }

    fclose(fp);

    printf("\nTotal Students = %d\n", count);
}

void topScorer()
{
    struct Student s, top;
    int first = 1;

    FILE *fp = fopen("data.txt", "r");

    if (fp == NULL)
    {
        printf("\nNo Records Found!\n");
        return;
    }

    while (fscanf(fp, "%d %s %f", &s.id, s.name, &s.marks) != EOF)
    {
        if (first || s.marks > top.marks)
        {
            top = s;
            first = 0;
        }
    }

    fclose(fp);

    printf("\nTop Scorer Details\n");
    printf("------------------\n");
    printf("ID    : %d\n", top.id);
    printf("Name  : %s\n", top.name);
    printf("Marks : %.2f\n", top.marks);
    printf("Grade : %c\n", calculateGrade(top.marks));
}

int main()
{
    int choice;

    while (1)
    {
        printf("\n====================================");
        printf("\n STUDENT MANAGEMENT SYSTEM");
        printf("\n====================================");
        printf("\n1. Add Student");
        printf("\n2. View Students");
        printf("\n3. Search Student");
        printf("\n4. Update Student");
        printf("\n5. Delete Student");
        printf("\n6. Total Students");
        printf("\n7. Top Scorer");
        printf("\n8. Exit");
        printf("\n====================================");

        printf("\nEnter Your Choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            addStudent();
            break;

        case 2:
            viewStudents();
            break;

        case 3:
            searchStudent();
            break;

        case 4:
            updateStudent();
            break;

        case 5:
            deleteStudent();
            break;

        case 6:
            totalStudents();
            break;

        case 7:
            topScorer();
            break;

        case 8:
            printf("\nThank You!\n");
            exit(0);

        default:
            printf("\nInvalid Choice!\n");
        }
    }

    return 0;
}