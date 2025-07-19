
#include <stdio.h>
#include "cloop.h"

#define MyObject_METHODS(X)     \
    X(MyObject, void, inc_x,   (void* self)) \
    X(MyObject, int,  get_x,   (void* self))

#define MyObject_ATTRIBUTES(X) \
    X(MyObject, int, _x) \
    X(MyObject, int, y) 

#define MyObject_CTOR(X) \
    X(MyObject, (void* self, int x, long y))

#define MyObject_DTOR(X) \
    X(MyObject, (void* self))
 

CLOOP_DEFINE_CLASS(MyObject)

static void MyObject_ctor(void* self, int x, long y){

}

int main(void){
    printf("HI!\n");
    return 0;
}