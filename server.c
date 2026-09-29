#include "student.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

StudentResponse *add_student_1_svc(Student *student, struct svc_req *req)
{
    static StudentResponse response;

    memset(&response, 0, sizeof(response));

    FILE *file = fopen("students.dat", "a");

    if (file == NULL)
    {
        response.success = 0;
        response.message = strdup("Could not open database");
        response.student_name = strdup("");
        response.student_department = strdup("");
        return &response;
    }

    fprintf(file, "%d|%s|%s|%.2f\n",
            student->id,
            student->name,
            student->department,
            student->cgpa);

    fclose(file);

    response.success = 1;
    response.message = strdup("Student added successfully");

    response.student_id = student->id;
    response.student_name = strdup(student->name);
    response.student_department = strdup(student->department);
    response.student_cgpa = student->cgpa;

    return &response;
}


StudentResponse *search_student_1_svc(StudentRequest *request, struct svc_req *req)
{
    static StudentResponse response;

    memset(&response, 0, sizeof(response));

    FILE *file = fopen("students.dat", "r");

    if (file == NULL)
    {
        response.success = 0;
        response.message = strdup("Database not found");
        response.student_name = strdup("");
        response.student_department = strdup("");
        return &response;
    }

    int id;
    char name[50];
    char department[50];
    float cgpa;

    while (fscanf(file, "%d|%49[^|]|%49[^|]|%f",
                  &id,
                  name,
                  department,
                  &cgpa) == 4)
    {
        if (id == request->id)
        {
            response.success = 1;
            response.message = strdup("Student found");

            response.student_id = id;
            response.student_name = strdup(name);
            response.student_department = strdup(department);
            response.student_cgpa = cgpa;

            fclose(file);
            return &response;
        }
    }

    fclose(file);

    response.success = 0;
    response.message = strdup("Student not found");
    response.student_name = strdup("");
    response.student_department = strdup("");

    return &response;
}


StudentResponse *update_student_1_svc(Student *student, struct svc_req *req)
{
    static StudentResponse response;
    static char temp_file[] = "students_temp.dat";

    memset(&response, 0, sizeof(response));

    FILE *file = fopen("students.dat", "r");
    FILE *temp = fopen(temp_file, "w");

    if (file == NULL || temp == NULL)
    {
        response.success = 0;
        response.message = strdup("Could not open database");
        response.student_name = strdup("");
        response.student_department = strdup("");

        if (file)
            fclose(file);

        if (temp)
            fclose(temp);

        return &response;
    }

    int found = 0;
    int id;
    char name[50];
    char department[50];
    float cgpa;

    while (fscanf(file, "%d|%49[^|]|%49[^|]|%f",
                  &id,
                  name,
                  department,
                  &cgpa) == 4)
    {
        if (id == student->id)
        {
            fprintf(temp, "%d|%s|%s|%.2f\n",
                    student->id,
                    student->name,
                    student->department,
                    student->cgpa);

            found = 1;
        }
        else
        {
            fprintf(temp, "%d|%s|%s|%.2f\n",
                    id,
                    name,
                    department,
                    cgpa);
        }
    }

    fclose(file);
    fclose(temp);

    if (found)
    {
        remove("students.dat");
        rename(temp_file, "students.dat");

        response.success = 1;
        response.message = strdup("Student updated successfully");

        response.student_id = student->id;
        response.student_name = strdup(student->name);
        response.student_department = strdup(student->department);
        response.student_cgpa = student->cgpa;
    }
    else
    {
        remove(temp_file);

        response.success = 0;
        response.message = strdup("Student not found");
        response.student_name = strdup("");
        response.student_department = strdup("");
    }

    return &response;
}


StudentResponse *delete_student_1_svc(StudentRequest *request, struct svc_req *req)
{
    static StudentResponse response;
    static char temp_file[] = "students_temp.dat";

    memset(&response, 0, sizeof(response));

    FILE *file = fopen("students.dat", "r");
    FILE *temp = fopen(temp_file, "w");

    if (file == NULL || temp == NULL)
    {
        response.success = 0;
        response.message = strdup("Could not open database");
        response.student_name = strdup("");
        response.student_department = strdup("");

        if (file)
            fclose(file);

        if (temp)
            fclose(temp);

        return &response;
    }

    int found = 0;
    int id;
    char name[50];
    char department[50];
    float cgpa;

    while (fscanf(file, "%d|%49[^|]|%49[^|]|%f",
                  &id,
                  name,
                  department,
                  &cgpa) == 4)
    {
        if (id == request->id)
        {
            found = 1;
            continue;
        }

        fprintf(temp, "%d|%s|%s|%.2f\n",
                id,
                name,
                department,
                cgpa);
    }

    fclose(file);
    fclose(temp);

    if (found)
    {
        remove("students.dat");
        rename(temp_file, "students.dat");

        response.success = 1;
        response.message = strdup("Student deleted successfully");

        response.student_id = 0;
        response.student_name = strdup("");
        response.student_department = strdup("");
        response.student_cgpa = 0.0;
    }
    else
    {
        remove(temp_file);

        response.success = 0;
        response.message = strdup("Student not found");

        response.student_id = 0;
        response.student_name = strdup("");
        response.student_department = strdup("");
        response.student_cgpa = 0.0;
    }

    return &response;
}
