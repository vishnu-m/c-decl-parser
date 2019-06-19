/* Ordinary struct */
struct coordinates{
    int x,y;
};

/* Struct with enum declaration inside  */
struct rainbow{
    enum Fruit{Violet, Indigo, Blue, Green, Yellow, Red};
};

/* Nested Struct */
struct Student
{
    char name[50];
    int age;
    struct marks{
        int physics;        
    }m1, m2;
    struct Student *pointer;
}; 

/*Function pointer */
struct mycallback {
  int (*f)(int);
};

/* Bit fields */
struct bits {
  int x: 5;
  int y: 1;
  int z: 2;
};

