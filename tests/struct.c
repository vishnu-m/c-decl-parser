/* Ordinary struct */
struct coordinates {
    int x,y;
};

/* Struct with enum declaration inside */
struct rainbow {
    enum Fruit{Violet, Indigo, Blue, Green, Yellow, Red}field1;
};

/* Anonymous struct */
struct {
   char alpha;
   int num;
};

/* Nested Struct */
struct Student {
    char name[50];
    int age;
    struct marks{
        int physics;        
    }m1, m2;
    struct Student *pointer;
    struct Student **double_pointer;
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

/* Forward declaration */
struct context;

struct funcptrs{
  void (*func0)(struct context *ctx);
  void (*func1)(void);
};

struct context{
    struct funcptrs fps;
}; 