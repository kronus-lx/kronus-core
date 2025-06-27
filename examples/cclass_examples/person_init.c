#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cclass.h"

class(Person, {
    char* name;
    int age;
});

class_construct(Person, (const char* name, int age), {
#ifdef _WIN32
    self->name = _strdup(name);
#else
    self->name = strdup(name);
#endif

self->age = age;
}, {
    free(ptr->name);
});

void class_function(Person, print_attr);

void Person_increment(Person* self) {
    self->age++;
}

int main(int argc, char* argv[]) {

    Person* person = new(Person, "John Doe", 30);
    if (person) {
        Person_increment(person);
        destruct(Person, person);
    }
    return 0;
}