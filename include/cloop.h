/*
    C Lightweight Object Oriented Programming
                    [CLOOP]

                  by Leon Bass
                 [github/Le-o-n]
                
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
            ExitProcess(3);
        }
        #define abort() _abort_win()
    #endif

#endif

#define CLOOP_JOIN_(X, Y) X ## Y
#define CLOOP_JOIN(X, Y) CLOOP_JOIN_(X, Y)


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

#define CLOOP_DEFINE_CLASS(ObjType)                                 \
                                                                     \
typedef struct ObjType##_VTable {                                   \
    void (*ctor) ObjType##_CTOR (CLOOP_METHOD_ARGS);                                         \
    void (*dtor) ObjType##_DTOR (CLOOP_METHOD_ARGS);                                         \
    ObjType##_METHODS (CLOOP_METHOD_POINTER_IN_VTABLE)              \
} ObjType##_VTable;                                                 \
                                                                     \
typedef struct ObjType {                                            \
    ObjType##_VTable vt;                                           \
    ObjType##_ATTRIBUTES (CLOOP_ATTRIBUTE_DECLARE)                  \
    int _is_heap_allocated : 1;                                     \
} ObjType;                                                          \
                                                                     \
ObjType##_CTOR (CLOOP_METHOD_DECLARE)                         \
ObjType##_DTOR (CLOOP_METHOD_DECLARE)                                                                  \
ObjType##_METHODS (CLOOP_METHOD_DECLARE)

#define cloop_init(ObjType, obj_ptr, ...) \
    ({\
        memset((void *)obj_ptr, 0, sizeof(ObjType));          \
        obj_ptr->vt.ctor = ObjType##_ctor; \
        obj_ptr->vt.dtor = ObjType##_dtor; \
        ObjType ## _METHODS(obj_ptr CLOOP_METHOD_REGISTER)\
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


#define cloop_del(ObjType, obj_ptr, ...)                                 \
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
    ({ (obj_ptr)->vt. func ((obj_ptr) __VA_OPT__(,) __VA_ARGS__);})

#define CLASS_BEGIN(classname)              \
    typedef struct classname classname; 

#define CLASS_END(classname) \
    CLOOP_DEFINE_CLASS(classname);

#define CLOOP_MANGLE(name) __ ## name


#endif // CLOOP_H_