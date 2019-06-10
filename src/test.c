// enum week{Mon=99, Tue, Wed, Thur, Fri, Sat, Sun};

struct Student
{
    char name[50];
    int age;
    struct marks{
        int physics;        
    }m1, m2;
    struct Student *pointer;
    enum Fruit{Apple, Banana=23};
    
};

enum colours{Red, Black, Yellow};
