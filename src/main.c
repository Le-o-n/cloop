
#include <stdio.h>
#include "cloop.h"


CLASS_BEGIN(MyObject);

    #define MyObject_METHODS(X)     \
        X(MyObject, void, inc_x, (MyObject* self)) \
        X(MyObject, int,  get_x, (MyObject* self)) \

    #define MyObject_ATTRIBUTES(X) \
        X(MyObject, int, _x) \

    #define MyObject_CTOR(X) \
        X(MyObject, void, ctor, (MyObject* self, int x)) \

    #define MyObject_DTOR(X) \
        X(MyObject, void, dtor, (MyObject* self))

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