
#include <stdio.h>
#include "cloop.h"

// -------------
//  staticmethod.h
// -------------


#ifndef x
    #define x 1
#endif

cloop_class(MyObject, 
    
    #define MyObject_SUPER void*

    #define MyObject_METHODS(T, f) \
        f(T, int, return_x, (void)) /*static method (no instance passed)*/

    #define MyObject_ATTRIBUTES(T, f)

    #define MyObject_CTOR(T, f) \
        f(T, void, ctor, (T* self))

    #define MyObject_DTOR(T, f) \
        f(T, void, dtor, (T* self))

)



// -------------
//  staticmethod.c
// -------------

cloop_def(MyObject, 
    void, ctor, (MyObject* self), {
        printf("CTOR\n");
    }
)

cloop_def(MyObject, 
    void, dtor, (MyObject* self), {
        printf("DTOR\n");
    }
);

cloop_def(MyObject, 
    int, return_x, (void), {
        return x;
    }
);




int main(void){
    MyObject* my_obj = cloop_new(MyObject);

    printf("x: %d\n", cloop_staticcall(MyObject, return_x));

    cloop_del(my_obj);
    return 0;
}