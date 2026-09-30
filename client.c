#include "student.h"
#include <stdio.h>
#include <stdlib.h>

void add_student(CLIENT *client)
{
    Student student;
    StudentResponse *response;

    char name[50];
    char department[50];

    printf("\n--- Add Student ---\n");

    printf("Enter ID: ");
    scanf("%d", &student.id);

    printf("Enter Name: ");
    scanf("%49s", name);

    printf("Enter Department: ");
    scanf("%49s", department);

    printf("Enter CGPA: ");
    scanf("%f", &student.cgpa);

    student.name = name;
    student.department = department;

    response = add_student_1(&student, client);

    if (response == NULL)
    {
        clnt_perror(client, "RPC call failed");
        return;
    }

    printf("Server: %s\n", response->message);
}


void search_student(CLIENT *client)
{
    StudentRequest request;
    StudentResponse *response;

    printf("\n--- Search Student ---\n");

    printf("Enter ID: ");
    scanf("%d", &request.id);

    response = search_student_1(&request, client);

    if (response == NULL)
    {
        clnt_perror(client, "RPC call failed");
        return;
    }

    printf("Server: %s\n", response->message);

    if (response->success)
    {
        printf("ID: %d\n", response->student_id);
        printf("Name: %s\n", response->student_name);
        printf("Department: %s\n", response->student_department);
        printf("CGPA: %.2f\n", response->student_cgpa);
    }
}


void update_student(CLIENT *client)
{
    Student student;
    StudentResponse *response;

    char name[50];
    char department[50];

    printf("\n--- Update Student ---\n");

    printf("Enter ID: ");
    scanf("%d", &student.id);

    printf("Enter New Name: ");
    scanf("%49s", name);

    printf("Enter New Department: ");
    scanf("%49s", department);

    printf("Enter New CGPA: ");
    scanf("%f", &student.cgpa);

    student.name = name;
    student.department = department;

    response = update_student_1(&student, client);

    if (response == NULL)
    {
        clnt_perror(client, "RPC call failed");
        return;
    }

    printf("Server: %s\n", response->message);
}


void delete_student(CLIENT *client)
{
    StudentRequest request;
    StudentResponse *response;

    printf("\n--- Delete Student ---\n");

    printf("Enter ID: ");
    scanf("%d", &request.id);

    response = delete_student_1(&request, client);

    if (response == NULL)
    {
        clnt_perror(client, "RPC call failed");
        return;
    }

    printf("Server: %s\n", response->message);
}


int main()
{
    CLIENT *client;
    int choice;

    client = clnt_create("localhost",
                         STUDENT_DATABASE,
                         STUDENT_DATABASE_V1,
                         "tcp");

    if (client == NULL)
    {
        clnt_pcreateerror("localhost");
        exit(1);
    }

    while (1)
    {
        printf("\n==============================\n");
        printf("     STUDENT DATABASE RPC\n");
        printf("==============================\n");
        printf("1. Add Student\n");
        printf("2. Search Student\n");
        printf("3. Update Student\n");
        printf("4. Delete Student\n");
        printf("5. Exit\n");
        printf("==============================\n");
        printf("Enter choice: ");

        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                add_student(client);
                break;

            case 2:
                search_student(client);
                break;

            case 3:
                update_student(client);
                break;

            case 4:
                delete_student(client);
                break;

            case 5:
                printf("Exiting...\n");
                clnt_destroy(client);
                return 0;

            default:
                printf("Invalid choice. Try again.\n");
        }
    }
}
