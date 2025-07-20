
#include <stdio.h>
#include "cloop.h"


CLASS_BEGIN(MyObject);

    #define MyObject_METHODS(T, f)     \
        f(T, void, inc_x, (T* self)) \
        f(T, int,  get_x, (T* self)) \

    #define MyObject_ATTRIBUTES(T, f) \
        f(T, int, _x) \

    #define MyObject_CTOR(T, f) \
        f(T, void, ctor, (T* self, int x)) \

    #define MyObject_DTOR(T, f) \
        f(T, void, dtor, (T* self))

CLASS_END(MyObject);


static void MyObject_ctor(MyObject* self, int x){

}

static void MyObject_dtor(MyObject* self){

}

static void MyObject_inc_x(MyObject* self){
    self->_x++;
}

static int MyObject_get_x(MyObject* self){
    return self->_x;
}



int main(void){
    MyObject* my_obj = cloop_new(MyObject, 1);

    for (int i=0; i<10; i++){
        
        cloop_call(my_obj, inc_x);
        printf("x: %d", cloop_call(my_obj, get_x));
    }

    cloop_del(MyObject, (my_obj));
    return 0;
}