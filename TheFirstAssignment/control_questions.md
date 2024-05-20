
---

1. **What is structural programming paradigm?**
---
Structured programming is a programming paradigm that uses blocks of code, such as functions, loops, and conditions, to create a clear and logical structure of the program. The main principles include sequence, branching, and iteration.

   ```c
   #include <stdio.h>

   void printNumbers(int limit) {
       for (int i = 1; i <= limit; i++) {
           printf("%d ", i);
       }
       printf("\n");
   }

   int main() {
       printNumbers(10); // Calling a function that uses a loop to print numbers
       return 0;
   }
   ```

---
2. **What is procedural programming paradigm?**
---
Procedural programming is a programming paradigm based on the concept of calling procedures or subroutines. The program is divided into procedures (functions, methods), each of which performs a specific task.

   ```c
   #include <stdio.h>

   void greet() {
       printf("Hello, World!\n");
   }

   void farewell() {
       printf("Goodbye, World!\n");
   }

   int main() {
       greet(); // Calling the procedure
       farewell(); // Calling another procedure
       return 0;
   }
   ```

---
3. **Which primitive data types do you know? Key differences between them?**
---
Primitive data types include:
- **Integers (int)**: Store whole numbers.
- **Floating-point numbers (float, double)**: Store real numbers with floating points.
- **Characters (char)**: Store individual characters.
- **Boolean values (bool)**: Store true or false values.

The main differences are in the amount of memory they occupy and the range of values they can store. Typically, the sizes of primitive data types are as follows:

- **Bool**: 1 byte
- **Char**: 1 byte
- **Short**: 2 bytes
- **Int**: 4 bytes
- **Long**: 4 bytes
- **Float**: 4 bytes
- **Double**: 8 bytes

   ```c
   #include <stdio.h>
   #include <stdbool.h>

   int main() {
       bool flag = true;
       char letter = 'A';
       short numberShort = 10;
       int numberInt = 100;
       long numberLong = 1000L;
       float numberFloat = 10.5f;
       double numberDouble = 20.5;

       printf("Bool: %d\n", flag);
       printf("Char: %c\n", letter);
       printf("Short: %d\n", numberShort);
       printf("Int: %d\n", numberInt);
       printf("Long: %ld\n", numberLong);
       printf("Float: %.2f\n", numberFloat);
       printf("Double: %.2f\n", numberDouble);

       return 0;
   }
   ```

---
4. **Which segments does the process memory have?**
---
The process memory usually consists of the following segments:
- **Code segment**: Stores the executable code of the program.
- **Data segment**: Stores global and static variables.
- **Heap segment**: Used for dynamic memory allocation.
- **Stack segment**: Used for storing local variables and managing function calls.

---
5. **What is the virtual memory space?**
---
Virtual address space is an abstraction that allows programs to use more memory than is physically available through the use of a paging mechanism. This allows programs to operate in an isolated environment.

---
6. **How to allocate the memory in each segment?**
---
- **Code segment**: Memory is allocated when the executable file is loaded.
- **Data segment**: Memory is allocated during variable initialization.
- **Heap**: Memory is dynamically allocated using functions like malloc(), calloc(), realloc() in C;

  ```c
  #include <stdlib.h>
  #include <stdio.h>

  int main() {
      int *ptr = (int *)malloc(4 * sizeof(int)); // Allocating memory for 4 int elements
      if (ptr == NULL) {
          printf("Memory allocation error\n");
          return 1;
      }

      // Using the allocated memory
      for (int i = 0; i < 4; i++) {
          ptr[i] = i + 1;
          printf("%d ", ptr[i]);
      }

      // Freeing the memory
      free(ptr);
      return 0;
  }
  ```

- **Stack**: Memory is automatically allocated during function calls.

---
7. **How to reallocate the memory in case we don’t have enough space?**
---
If there is not enough space in the heap, the realloc() function is used to expand the allocated memory. If it is not possible to expand the existing block, realloc() creates a new block of the required size, copies the content of the old block, and frees the old block of memory.

   ```c
   #include <stdlib.h>
   #include <stdio.h>

   int main() {
       int *ptr = (int *)malloc(2 * sizeof(int)); // Initial memory allocation
       if (ptr == NULL) {
           printf("Memory allocation error\n");
           return 1;
       }

       // Using the allocated memory
       ptr[0] = 1;
       ptr[1] = 2;

       // Reallocating memory for 4 elements
       ptr = (int *)realloc(ptr, 4 * sizeof(int));
       if (ptr == NULL) {
           printf("Memory reallocation error\n");
           return 1;
       }

       // Using the additional memory
       ptr[2] = 3;
       ptr[3] = 4;

       // Printing the values
       for (int i = 0; i < 4; i++) {
           printf("%d ", ptr[i]);
       }

       // Freeing the memory
       free(ptr);
       return 0;
   }
   ```

---
8. **What is a runtime stack?**
---
The runtime stack is a data structure used for managing function calls and storing local variables during the program execution. Each function call adds a frame to the stack, which stores the return address, function parameters, and local variables.