#include "student.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
    CLIENT *client;
    Student student;
    StudentResponse *response;

    client = clnt_create("localhost",
                         STUDENT_DATABASE,
                         STUDENT_DATABASE_V1,
                         "tcp");

    if (client == NULL)
    {
        clnt_pcreateerror("localhost");
        exit(1);
    }

    student.id = 101;

    student.name = "Palson";
    student.department = "CSE";
    student.cgpa = 8.50;

    response = add_student_1(&student, client);

    if (response == NULL)
    {
        clnt_perror(client, "RPC call failed");
    }
    else
    {
        printf("Server: %s\n", response->message);
    }

    clnt_destroy(client);

    return 0;
}
