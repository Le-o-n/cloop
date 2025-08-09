/*

    =================================================

        C Lightweight Object-Oriented Programming
                        [CLOOP]

                    by Leon Bass
                    [github/Le-o-n]

    =================================================

    -------------------
        Public API
    -------------------

    ===================
        cloop_init
    ===================
    Parameters:
        ObjType         - Name of the class (user-defined).
        obj_ptr         - Pointer to the object instance (struct).
        __VA_ARGS__     - Optional arguments forwarded to the constructor.

    Description:
        Initialises a class of type <ObjType> using the object pointer <obj_ptr>.
        All arguments in <__VA_ARGS__> are forwarded to the user-defined
        constructor.

    ===================
        cloop_new
    ===================
    Parameters:
        ObjType         - Name of the class (user-defined).
        __VA_ARGS__     - Optional arguments forwarded to the constructor.

    Description:
        Allocates and initialises a class of type <ObjType> on the heap.
        The object must later be freed using `cloop_del`.
        All arguments in <__VA_ARGS__> are forwarded to the user-defined
        constructor.

    ===================
        cloop_del
    ===================
    Parameters:
        obj_ptr         - Pointer to the class instance.
        __VA_ARGS__     - Optional arguments forwarded to the destructor.

    Description:
        Calls the object's destructor. If the object was allocated on the heap,
        its memory is freed.

    ===================
        cloop_call
    ===================
    Parameters:
        obj_ptr         - Pointer to the class instance.
        func            - Method name to call.
        __VA_ARGS__     - Optional arguments forwarded to the method.

    Description:
        Calls the specified method on the given object.

    ===================
        cloop_def
    ===================
    Parameters:
        ObjType         - Object type that owns the method.
        ret             - Return type of the method.
        func            - Method name.
        args            - Parameter list, enclosed in parentheses.
        body            - Function body, enclosed in curly braces.

    Description:
        Defines a method belonging to an object.

    ===================
        cloop_class
    ===================
    Parameters:
        classname               - Name of the class/object.
        class_implementation    - Implementation of the class.

    Description:
        Defines the full implementation of a class.

*/



#ifndef CLOOP_H_
#define CLOOP_H_

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
            ExitProcess(1);
        }
        #define abort() _abort_win()
    #endif

#endif



/*

=========== Misc. Macros ===========

*/

#define _CLOOP_NARG_IMPL(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19,_20,_21,_22,_23,_24,_25,_26,_27,_28,_29,_30,_31,_32,_33,N,...) N
#define CLOOP_NARG(...) \
    _CLOOP_NARG_IMPL(__VA_ARGS__,33,32,31,30,29,28,27,26,25,24,23,22,21,20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0)

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
#define CLOOP_BRANCH_IF_ZERO_17(zero, nonzero) nonzero
#define CLOOP_BRANCH_IF_ZERO_18(zero, nonzero) nonzero
#define CLOOP_BRANCH_IF_ZERO_19(zero, nonzero) nonzero
#define CLOOP_BRANCH_IF_ZERO_20(zero, nonzero) nonzero
#define CLOOP_BRANCH_IF_ZERO_21(zero, nonzero) nonzero
#define CLOOP_BRANCH_IF_ZERO_22(zero, nonzero) nonzero
#define CLOOP_BRANCH_IF_ZERO_23(zero, nonzero) nonzero
#define CLOOP_BRANCH_IF_ZERO_24(zero, nonzero) nonzero
#define CLOOP_BRANCH_IF_ZERO_25(zero, nonzero) nonzero
#define CLOOP_BRANCH_IF_ZERO_26(zero, nonzero) nonzero
#define CLOOP_BRANCH_IF_ZERO_27(zero, nonzero) nonzero
#define CLOOP_BRANCH_IF_ZERO_28(zero, nonzero) nonzero
#define CLOOP_BRANCH_IF_ZERO_29(zero, nonzero) nonzero
#define CLOOP_BRANCH_IF_ZERO_30(zero, nonzero) nonzero
#define CLOOP_BRANCH_IF_ZERO_31(zero, nonzero) nonzero
#define CLOOP_BRANCH_IF_ZERO_32(zero, nonzero) nonzero
#define CLOOP_BRANCH_IF_ZERO_33(zero, nonzero) nonzero

#define CLOOP_BRANCH_IF_ZERO(count, zero, nonzero) CLOOP_BRANCH_IF_ZERO_IMPL(count, zero, nonzero)
#define CLOOP_BRANCH_IF_ZERO_IMPL(count, zero, nonzero) CLOOP_BRANCH_IF_ZERO_##count(zero, nonzero)

/*

=========== Private API ===========

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


#define CLOOP_CLASS_BEGIN(ObjType)\
    typedef struct ObjType ObjType;\
    typedef struct ObjType##_VTable {                                   \
        void (*ctor) ObjType##_CTOR (ObjType, CLOOP_METHOD_ARGS);       \
        void (*dtor) ObjType##_DTOR (ObjType, CLOOP_METHOD_ARGS);       \
        ObjType##_METHODS (ObjType, CLOOP_METHOD_POINTER_IN_VTABLE)     \
    } ObjType##_VTable;                                             \
    typedef struct ObjType {\
        ObjType##_SUPER super;                                            \
        ObjType##_VTable vt;                                            \
        ObjType##_ATTRIBUTES (ObjType, CLOOP_ATTRIBUTE_DECLARE)         \
        int _is_heap_allocated : 1;                                     \
    } ObjType;                                                          \
                                                                        \
    ObjType##_CTOR (ObjType, CLOOP_METHOD_DECLARE)                      \
    ObjType##_DTOR (ObjType, CLOOP_METHOD_DECLARE)                      \
    ObjType##_METHODS (ObjType, CLOOP_METHOD_DECLARE)


#define CLOOP_CLASS_END(classname, ...)

/*

============================================

               Public API             

============================================
*/

#define cloop_init(ObjType, obj_ptr, ...) \
    ({\
        memset((void *)(obj_ptr), 0, sizeof(ObjType));          \
        (obj_ptr)->vt.ctor = ObjType##_ctor; \
        (obj_ptr)->vt.dtor = ObjType##_dtor; \
        ObjType ## _METHODS(ObjType, (obj_ptr) CLOOP_METHOD_REGISTER)\
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


#define cloop_class(classname, prototype, ...) \
    prototype \
    CLOOP_CLASS_BEGIN(classname) \
    __VA_ARGS__ \
    CLOOP_CLASS_END(classname)
    

#define cloop_to_super(cls, obj_ptr) \
  ((cls##_SUPER * ) obj_ptr)
  
#define cloop_to_super_l(cls, obj_ptr) \
  cloop_to_super(cls, obj_ptr)

#define cloop_to_super_r(cls, obj) \
  ((cls##_SUPER) obj)

#define cloop_superclass(cls) \
  cls ## _SUPER
  

#endif // CLOOP_H_