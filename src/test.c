//enum week{Mon=99, Tue, Wed, Thur, Fri, Sat, Sun};

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

union n{
    int x, y;
};

// struct 
// {
//     int x, y;
// };

// struct S {
//  unsigned int b : 3;
//  unsigned int a : 9;    
// };

// enum colours{Red, Black, Yellow};
