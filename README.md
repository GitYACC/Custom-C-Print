# Custom-C-Print

This is a custom `print` implementation for C. It supports all the usual printing, as well as registering new `repr` functions for custom structs.

---
### Get Started

You can clone these files into your workspace with `git clone github.com/GitYACC/Custom-C-Print`

There are two important parts to this library

Normal printing
```c
#include "print.h"

/* BASE SPECIFIERS
%i = int
%I = unsigned int
%f = float
%d = double
%D = long double
%c = char
%C = unsigned char
%l = long
%L = unsigned long
%x = short
%X = unsigned short
%s = string
%p = pointer
*/

int main() {
    print("%s is %i years old\n", "Steve", 20);
}
```
The reason why some of the specifier letters were changed was to keep all specifiers one letter long. You can also remember the base types better, such as `int => %i` or `double => %d`

Custom Struct Printing
```c
#include "print.h"
#include <stdlib.h>

typedef struct vector {
    int *array;
    int size;
} vector;

// returns a string
// takes a void pointer to recieve 
// the struct instance as a parameter
char *vector_repr(void *arg) {
    vector *vec = (vector *)arg; // cast to your type
    
    char *result = malloc(sizeof(char) * vec->size); // repr string
    for(int i = 0; i < vec->size; i++) {
        result[0] = '[';
        if(i == vec->size - 1)
            asprintf(&result, "%s%d%c", result, vec->array[i], ']');
        else
            asprintf(&result, "%s%d%c", result, vec->array[i], ' ');
    }
    
    return result;
}

int main() {
    register_fmt('v', &vector_repr); // register your type specifier
    
    vector *vec = malloc(sizeof(vector));
    vec->array = malloc(sizeof(int) * 3);
    
    vec->array[0] = 1;
    vec->array[1] = 2;
    vec->array[2] = 3;
    vec->size = 3;
    
    print("List: %v\n", vec); // print the cusstom struct with a registered specifier
}
```
