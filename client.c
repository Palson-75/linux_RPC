#include "student.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
    CLIENT *client;
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

    request.id = 101;

    response = delete_student_1(&request, client);

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
