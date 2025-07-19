/*
    C Lightweight Object Oriented Programming
                    [CLOOP]

                  by Leon Bass
                 [github/Le-on]
                
*/


#ifndef CLOOP_H_
#define CLOOP_H_

#include <stdarg.h>
#include <stdio.h> 

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


#define CLOOP_METHOD_DECLARE(obj,ret,name,args) \
  static ret obj##_##name args;

#define CLOOP_METHOD_IMPLEMENT(obj,ret,name,args, body)  \
  static ret obj##_##name args { body }

#define CLOOP_METHOD_POINTER_IN_VTABLE(obj,ret,name,args) \
  ret (* name) args;


#define CLOOP_ATTRIBUTE_DECLARE(obj,type,name) \
    type name ;

#define CLOOP_DEFINE_CLASS(ObjType)                                 \
                                                                     \
typedef struct ObjType##_VTable {                                   \
    void (*ctor) CTOR_ARGS;                                         \
    void (*dtor) DTOR_ARGS;                                         \
    ObjType##_METHODS (CLOOP_METHOD_POINTER_IN_VTABLE)              \
} ObjType##_VTable;                                                 \
                                                                     \
typedef struct ObjType {                                            \
    ObjType##_VTable *vt;                                           \
    ObjType##_ATTRIBUTES (CLOOP_ATTRIBUTE_DECLARE)                  \
} ObjType;                                                          \
                                                                     \
static void ObjType##_ctor CTOR_ARGS ;                        \
static void ObjType##_dtor DTOR_ARGS ;                          \
                                                                \
ObjType##_METHODS (CLOOP_METHOD_DECLARE)


#endif // CLOOP_H_