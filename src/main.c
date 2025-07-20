
#include <stdio.h>
#include "cloop.h"


cloop_class(MyObject,

    #define MyObject_METHODS(T, f)     \
        f(T, void, inc_x, (T* self)) \
        f(T, int,  get_x, (T* self)) 

    #define MyObject_ATTRIBUTES(T, f) \
        f(T, int, _x) 

    #define MyObject_CTOR(T, f) \
        f(T, void, ctor, (T* self, int x)) 

    #define MyObject_DTOR(T, f) \
        f(T, void, dtor, (T* self))
    
    
    
    cloop_def(MyObject, 
        void, ctor, (MyObject* self, int x), {
            printf("CTOR");
        }
    )

    cloop_def(MyObject, 
        void, dtor, (MyObject* self), {
            printf("DTOR");
        }
    )

    cloop_def(MyObject, 
        void, inc_x, (MyObject* self), {
            printf("incrementing x");
            self->_x++;
        }
    )
    
    cloop_def(MyObject, 
        int, get_x, (MyObject* self), {
            printf("getting x");
            return self->_x;
        }
    )
    
)





int main(void){
    MyObject* my_obj = cloop_new(MyObject, 1);

    for (int i=0; i<10; i++){
        
        my_obj->vt.inc_x(my_obj);
        
        printf("x: %d\n", my_obj->vt.get_x(my_obj));
        

        cloop_call(my_obj, inc_x);
        printf("x: %d\n", cloop_call(my_obj, get_x));
    }

    cloop_del(my_obj);
    return 0;
}