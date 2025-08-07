
#include <stdio.h>
#include "cloop.h"

// -------------
//  inheritance.h
// -------------

cloop_class(ParentObject, 

    #define ParentObject_METHODS(T, f) \
        f(T, int, get_y, (T* self))

    #define ParentObject_ATTRIBUTES(T, f) \
        f(T, int, _y)
    
    #define ParentObject_CTOR(T, f) \
        f(T, void, ctor, (T* self, int y))
    
    #define ParentObject_DTOR(T, f) \
        f(T, void, dtor, (T* self))

)

cloop_class(MyObject, 
    
    #define MyObject_METHODS(T, f) \
        f(T, ParentObject*, super, (T* self))

    #define MyObject_ATTRIBUTES(T, f) \
        f(T, ParentObject*, _par) 

    #define MyObject_CTOR(T, f) \
        f(T, void, ctor, (T* self, int x))

    #define MyObject_DTOR(T, f) \
        f(T, void, dtor, (T* self))

    ,

    cloop_def(MyObject, 
        ParentObject*, super, (MyObject* self), {
            return self->_par;
        }
    )

    cloop_def(MyObject, 
        void, ctor, (MyObject* self), {
            cloop_new(ParentObject)
        }
    )

    cloop_def(MyObject, 
        void, dtor, (MyObject* self), {
            printf("DTOR\n");
        }
    );

);



// -------------
//  main.c
// -------------



int main(void){
    
    MyObject* my_obj = cloop_new(MyObject, 1);  // heap allocation

    for (int i=0; i<10; i++){
        
        my_obj->vt.inc_x(my_obj);           // access vtable directly
        cloop_call(my_obj, inc_x);          // or use call macro

        int x;
        x = my_obj->vt.get_x(my_obj);       // access vtable directly
        x = cloop_call(my_obj, get_x);      // or use call macro

        printf("x: %d\n", x);

    }

    cloop_del(my_obj); // calls destructor and frees memory
    return 0;
}