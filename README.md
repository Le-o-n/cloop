# CLOOP — C Lightweight Object-Oriented Programming

**CLOOP** is a **header-only** library that brings object-oriented programming concepts to the C language.  
It allows you to define **classes**, **methods**, and **constructors/destructors** using familiar OOP syntax,  
while keeping the implementation pure C.

> No external dependencies. No bloat. No compiler-specific hacks. Just portable, macro-powered OOP in C.


---

## Features

- **Header-only** — simply include `cloop.h` in your project.
- **Object-oriented style** — define classes, methods, constructors, and destructors.
- **Supports inheritance** — via `super` pointers.
- **Heap or stack allocation** — choose between `cloop_init` and `cloop_new`.
- **Method calls** — invoke methods using `cloop_call` or manually navigate the Virtual Table of function pointers.
- **Portable** — works on Linux, macOS, and Windows.
- **Small footprint** — minimal runtime overhead.

---

## Getting Started

### 1. Include CLOOP
```c
#include "cloop.h"
```

### 2. Define a Class
```c

typedef struct { } MyClass_SUPER;

cloop_class(MyClass,
    // Methods implementation

    #define MyClass_ATTRIBUTES(cls, DECLARE)\
        DECLARE(cls, int, value)

    #define MyClass_METHODS(cls, DECLARE)\
        DECLARE(cls, void, print_value, (cls *self))

    #define MyClass_CTOR(cls, DECLARE)\
        DECLARE(cls, void, ctor, (cls *self, int value))

    #define MyClass_DTOR(cls, DECLARE)\
        DECLARE(cls, void, dtor, (cls *self))

    ,

    cloop_def(MyClass, void, ctor, (MyClass *self, int value), {
        self->value = value;
    });

    cloop_def(MyClass, void, dtor, (MyClass *self), {
        // cleanup if needed
    });

    cloop_def(MyClass, void, print_value, (MyClass *self), {
        printf("Value: %d\n", self->value);
    });
);
```

### 3. Use the Class
```c
int main(void) {
    // Create object on heap
    MyClass* obj_heap = cloop_new(MyClass, 42);
    
    // Create object on stack
    MyClass obj_stack = {0};
    MyClass* obj_stack_ptr = &obj_stack;

    cloop_init(MyClass, obj_stack_ptr, ...);    
    
    ...
    
    // Call a method
    cloop_call(obj_ptr, print_value);
    obj_ptr->vt.print_value()
    
    // Destroy object
    cloop_del(obj_ptr);

    return 0;
}
```

---

## Public API

| Macro         | Description |
|---------------|-------------|
| `cloop_init(ObjType, obj_ptr, ...)` | Initialise an object on the stack. |
| `cloop_new(ObjType, ...)` | Allocate and initialise an object on the heap. |
| `cloop_del(obj_ptr, ...)` | Call destructor and free if heap-allocated. |
| `cloop_call(obj_ptr, func, ...)` | Call an object method. Passes the pointer to the object as the first parameter. |
| `cloop_staticcall(ObjType, func, ...)` | Calls a static method. |
| `cloop_def(ObjType, ret, func, args, body)` | Define a method for a class. |
| `cloop_class(classname, prototype, ...)` | Implement a full class definition. |

---

## Why CLOOP?

C doesn't have built-in OOP features — no classes, no inheritance, no virtual methods.  
CLOOP gives you a **clean, minimal, and macro-driven** way to write OOP-style code **without rewriting your brain in C++**.

You still get:
- Familiar syntax for defining classes and methods.
- Virtual method tables (vtables) for dynamic dispatch.
- Support for stack and heap objects.
- Full control over memory.

---

## Supported Platforms

- **Linux**
- **macOS**
- **Windows** (with native error handling)

---

## Installation

Just drop [`cloop.h`](./cloop.h) into your project and `#include` it.

---

## License

MIT License.  
See [LICENSE](./LICENSE) for details.

---

## Author

**Leon Bass**  
[GitHub Profile](https://github.com/Le-o-n)
