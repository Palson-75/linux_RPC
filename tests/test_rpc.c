#include "../student.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
    CLIENT *client;

    Student student;
    Student updated_student;
    StudentRequest request;

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

    printf("\n===== RPC TEST START =====\n");

    /* TEST 1: ADD */
    printf("\n[TEST 1] ADD STUDENT\n");

    student.id = 999;
    student.name = "TestStudent";
    student.department = "CSE";
    student.cgpa = 8.00;

    response = add_student_1(&student, client);

    if (response == NULL)
    {
        clnt_perror(client, "ADD RPC failed");
        clnt_destroy(client);
        return 1;
    }

    printf("Result: %s\n", response->message);


    /* TEST 2: SEARCH */
    printf("\n[TEST 2] SEARCH STUDENT\n");

    request.id = 999;

    response = search_student_1(&request, client);

    if (response == NULL)
    {
        clnt_perror(client, "SEARCH RPC failed");
        clnt_destroy(client);
        return 1;
    }

    printf("Result: %s\n", response->message);

    if (response->success)
    {
        printf("ID: %d\n", response->student_id);
        printf("Name: %s\n", response->student_name);
        printf("Department: %s\n", response->student_department);
        printf("CGPA: %.2f\n", response->student_cgpa);
    }


    /* TEST 3: UPDATE */
    printf("\n[TEST 3] UPDATE STUDENT\n");

    updated_student.id = 999;
    updated_student.name = "UpdatedStudent";
    updated_student.department = "AIML";
    updated_student.cgpa = 9.20;

    response = update_student_1(&updated_student, client);

    if (response == NULL)
    {
        clnt_perror(client, "UPDATE RPC failed");
        clnt_destroy(client);
        return 1;
    }

    printf("Result: %s\n", response->message);


    /* TEST 4: SEARCH AFTER UPDATE */
    printf("\n[TEST 4] SEARCH AFTER UPDATE\n");

    request.id = 999;

    response = search_student_1(&request, client);

    if (response == NULL)
    {
        clnt_perror(client, "SEARCH RPC failed");
        clnt_destroy(client);
        return 1;
    }

    printf("Result: %s\n", response->message);

    if (response->success)
    {
        printf("ID: %d\n", response->student_id);
        printf("Name: %s\n", response->student_name);
        printf("Department: %s\n", response->student_department);
        printf("CGPA: %.2f\n", response->student_cgpa);
    }


    /* TEST 5: DELETE */
    printf("\n[TEST 5] DELETE STUDENT\n");

    request.id = 999;

    response = delete_student_1(&request, client);

    if (response == NULL)
    {
        clnt_perror(client, "DELETE RPC failed");
        clnt_destroy(client);
        return 1;
    }

    printf("Result: %s\n", response->message);


    /* TEST 6: SEARCH AFTER DELETE */
    printf("\n[TEST 6] SEARCH AFTER DELETE\n");

    request.id = 999;

    response = search_student_1(&request, client);

    if (response == NULL)
    {
        clnt_perror(client, "SEARCH RPC failed");
        clnt_destroy(client);
        return 1;
    }

    printf("Result: %s\n", response->message);


    printf("\n===== RPC TEST COMPLETE =====\n");

    clnt_destroy(client);

    return 0;
}
