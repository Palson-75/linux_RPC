struct Student {
    int id;
    string name<50>;
    string department<50>;
    float cgpa;
};

struct StudentRequest {
    int id;
};

struct StudentResponse {
    int success;
    string message<100>;
    int student_id;
    string student_name<50>;
    string student_department<50>;
    float student_cgpa;
};

program STUDENT_DATABASE {
    version STUDENT_DATABASE_V1 {
        StudentResponse ADD_STUDENT(Student) = 1;
        StudentResponse SEARCH_STUDENT(StudentRequest) = 2;
        StudentResponse UPDATE_STUDENT(Student) = 3;
        StudentResponse DELETE_STUDENT(StudentRequest) = 4;
    } = 1;
} = 0x20000001;
