
#include <stdio.h>
#include "cloop.h"

// -------------
//  inheritance.h
// -------------

cloop_class(ParentObject, 

    #define ParentObject_SUPER void*

    #define ParentObject_METHODS(T, f) \
        f(T, int, get_y, (T* self))

    #define ParentObject_ATTRIBUTES(T, f) \
        f(T, int, _y)
    
    #define ParentObject_CTOR(T, f) \
        f(T, void, ctor, (T* self, int y))
    
    #define ParentObject_DTOR(T, f) \
        f(T, void, dtor, (T* self))
    ,

    cloop_def(ParentObject, 
        int, get_y, (ParentObject* self), {
            return self->_y;
        }
    )
    
    cloop_def(ParentObject, 
        void, ctor, (ParentObject* self, int y), {
            self->_y = y;
        }
    )
    
    
    cloop_def(ParentObject, 
        void, dtor, (ParentObject* self), {
            
        }
    )

)


cloop_class(MyObject, 

    #define MyObject_SUPER ParentObject
    
    #define MyObject_METHODS(T, f) \

    #define MyObject_ATTRIBUTES(T, f) \

    #define MyObject_CTOR(T, f) \
        f(T, void, ctor, (T* self, int x))

    #define MyObject_DTOR(T, f) \
        f(T, void, dtor, (T* self))
    ,

    cloop_def(MyObject, 
        void, ctor, (MyObject* self, int x), {
            self->super = *cloop_new(ParentObject, x);
        }
    )
    cloop_def(MyObject, 
        void, dtor, (MyObject* self), {
            printf("DTOR\n");
        }
    )
);



// -------------
//  main.c
// -------------



int main(void){
    
    MyObject* my_obj = cloop_new(MyObject, 1);  // heap allocation

    cloop_superclass(MyObject)* my_obj_par = cloop_to_super(MyObject, my_obj);

    printf("n: %d", cloop_call(my_obj_par, get_y));

    cloop_del(my_obj); // calls destructor and frees memory
    return 0;
}