/*
    C Lightweight Object Oriented Programming
                    [CLOOP]

                  by Leon Bass
                 [github/Le-o-n]
                
*/


#ifndef CLOOP_H_
#define CLOOP_H_

/*

=========== Includes ===========

*/

#include <stdarg.h>
#include <stdio.h> 
#include <string.h>

#ifndef CLOOP_MAX_BUFFER_SIZE
    #define CLOOP_MAX_BUFFER_SIZE 512
#endif


#if defined(_WIN32) || defined(_WIN64)
    #define CLOOP_ON_WINDOWS 1
#else
    #define CLOOP_ON_WINDOWS 0
#endif

#if !CLOOP_ON_WINDOWS
    #include <stdlib.h>
#else
    // Windows    
    #ifndef perror
        #include <windows.h>
        static inline void _perror_win(const char *msg) {
            
            char buf[CLOOP_MAX_BUFFER_SIZE];
            snprintf(buf, sizeof(buf), "%s: (error code %lu)\n", msg, GetLastError());
            fputs(buf, stderr);
        }

        #define perror(msg) _perror_win((msg))
    #endif

    #ifndef abort
        #include <windows.h>
        static inline void _abort_win(void){
            ExitProcess(3);
        }
        #define abort() _abort_win()
    #endif

#endif



/*

=========== Misc. Macros ===========

*/

#define _CLOOP_NARG_IMPL(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,N,...) N
#define CLOOP_NARG(...) \
    _CLOOP_NARG_IMPL(__VA_ARGS__,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0)

#define CLOOP_JOIN_(X, Y) X ## Y
#define CLOOP_JOIN(X, Y) CLOOP_JOIN_(X, Y)

#define CLOOP_BRANCH_IF_ZERO_0(zero, nonzero) zero
#define CLOOP_BRANCH_IF_ZERO_1(zero, nonzero) nonzero
#define CLOOP_BRANCH_IF_ZERO_2(zero, nonzero) nonzero
#define CLOOP_BRANCH_IF_ZERO_3(zero, nonzero) nonzero
#define CLOOP_BRANCH_IF_ZERO_4(zero, nonzero) nonzero
#define CLOOP_BRANCH_IF_ZERO_5(zero, nonzero) nonzero
#define CLOOP_BRANCH_IF_ZERO_6(zero, nonzero) nonzero
#define CLOOP_BRANCH_IF_ZERO_7(zero, nonzero) nonzero
#define CLOOP_BRANCH_IF_ZERO_8(zero, nonzero) nonzero
#define CLOOP_BRANCH_IF_ZERO_9(zero, nonzero) nonzero
#define CLOOP_BRANCH_IF_ZERO_10(zero, nonzero) nonzero
#define CLOOP_BRANCH_IF_ZERO_11(zero, nonzero) nonzero
#define CLOOP_BRANCH_IF_ZERO_12(zero, nonzero) nonzero
#define CLOOP_BRANCH_IF_ZERO_13(zero, nonzero) nonzero
#define CLOOP_BRANCH_IF_ZERO_14(zero, nonzero) nonzero
#define CLOOP_BRANCH_IF_ZERO_15(zero, nonzero) nonzero
#define CLOOP_BRANCH_IF_ZERO_16(zero, nonzero) nonzero

#define CLOOP_BRANCH_IF_ZERO(count, zero, nonzero) CLOOP_BRANCH_IF_ZERO_IMPL(count, zero, nonzero)
#define CLOOP_BRANCH_IF_ZERO_IMPL(count, zero, nonzero) CLOOP_BRANCH_IF_ZERO_##count(zero, nonzero)

/*

=========== Class Declaration ===========

*/

#define CLOOP_METHOD_DECLARE(obj_type,ret,name,args) \
    static ret obj_type##_##name args ;

#define CLOOP_METHOD_IMPLEMENT(obj_type,ret,name,args, body)  \
    static ret obj_type##_##name args { body }

#define CLOOP_METHOD_POINTER_IN_VTABLE(obj_type,ret,name,args) \
    ret (* name) args ;

#define CLOOP_METHOD_ARGS(obj_type,ret,name,args) \
    args

#define CLOOP_METHOD_REGISTER(obj_type,ret,name,args) \
    ->vt. name = obj_type ## _ ## name ;


#define CLOOP_ATTRIBUTE_DECLARE(obj_type,type,name) \
    type name ;

#define CLOOP_VTABLE_CLASS_DISPATCH(branch, ParentClass, ...) \
    CLOOP_VTABLE_CLASS_ ## branch (ParentClass)

#define CLOOP_VTABLE_CLASS_0(...) void
#define CLOOP_VTABLE_CLASS_1(ParentClass) ParentClass ## _VTable





#define CLOOP_DEFINE_CLASS(ObjType)\
    typedef struct ObjType ObjType;\
    typedef struct ObjType##_VTable {                                   \
        void (*ctor) ObjType##_CTOR (ObjType, CLOOP_METHOD_ARGS);       \
        void (*dtor) ObjType##_DTOR (ObjType, CLOOP_METHOD_ARGS);       \
        ObjType##_METHODS (ObjType, CLOOP_METHOD_POINTER_IN_VTABLE)     \
    } ObjType##_VTable;                                             \
    typedef struct ObjType {                                            \
        ObjType##_VTable vt;                                            \
        ObjType##_ATTRIBUTES (ObjType, CLOOP_ATTRIBUTE_DECLARE)         \
        int _is_heap_allocated : 1;                                     \
        int _is_subclass : 1;                                           \
    } ObjType;                                                          \
                                                                        \
                                                                        \
                                                 \
                                                                        \
                                                                        \
                                                                        \
    ObjType##_CTOR (ObjType, CLOOP_METHOD_DECLARE)                      \
    ObjType##_DTOR (ObjType, CLOOP_METHOD_DECLARE)                      \
    ObjType##_METHODS (ObjType, CLOOP_METHOD_DECLARE)




/*

=========== Class Instantiation ===========

*/

#define cloop_init(ObjType, obj_ptr, ...) \
    ({\
        memset((void *)obj_ptr, 0, sizeof(ObjType));          \
        obj_ptr->vt.ctor = ObjType##_ctor; \
        obj_ptr->vt.dtor = ObjType##_dtor; \
        ObjType ## _METHODS(ObjType, obj_ptr CLOOP_METHOD_REGISTER)\
        ObjType##_ctor(obj_ptr, __VA_ARGS__);\
        obj_ptr;\
    })


#define cloop_new_(ObjType, CT, ...) \
    (\
        {\
            ObjType* CLOOP_JOIN(__tmp, CT) = (ObjType*) malloc(sizeof(ObjType));\
            if (! CLOOP_JOIN(__tmp, CT) ){perror("Could not allocate memory!");abort();}\
            cloop_init(ObjType, CLOOP_JOIN(__tmp, CT), __VA_ARGS__);\
            CLOOP_JOIN(__tmp, CT)->_is_heap_allocated = 1; \
            CLOOP_JOIN(__tmp, CT); \
        }\
    )
#define cloop_new(ObjType, ...) cloop_new_(ObjType, __COUNTER__, __VA_ARGS__)


#define cloop_del(obj_ptr, ...)                                 \
  do {                                                            \
    if ((obj_ptr) == NULL) {                                             \
      perror("Freeing NULL ptr!");                                \
      abort();                                                    \
    }                                                             \
                                                                  \
    (obj_ptr)->vt.dtor(obj_ptr __VA_OPT__(,) __VA_ARGS__);                     \
    if ((obj_ptr)->_is_heap_allocated) {                          \
      free(obj_ptr);                                              \
    }                                                             \
  } while (0)

#define cloop_call(obj_ptr, func, ...) \
    ({ (obj_ptr)->vt.func((obj_ptr) __VA_OPT__(,) __VA_ARGS__);})

#define cloop_def(ObjType, ret, func, args, body) \
   static ret ObjType ## _ ## func args body

#define CLOOP_CLASS_BEGIN(classname)              \
    CLOOP_DEFINE_CLASS(classname); \
    classname##_ATTRIBUTES(classname, CLOOP_ATTRIBUTE_DECLARE) \
    classname##_METHODS(classname, CLOOP_METHOD_DECLARE)
    

#define CLOOP_CLASS_END(classname, ...) \
    

#define cloop_class(classname, class_implementation) \
    CLOOP_CLASS_BEGIN(classname) \
    class_implementation \
    CLOOP_CLASS_END(classname) 

#define cloop_class_extends(classname, extends, class_definition) \
    CLOOP_CLASS_BEGIN(classname) \
    class_definition \
    CLOOP_CLASS_END(classname, extends) 

#endif // CLOOP_H_