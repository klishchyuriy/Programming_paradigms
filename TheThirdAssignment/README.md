# Caesar Encryption Algorithm (Structured and Procedural Programming)

## Purpose of Work

Gain experience in programming using a structured and procedural paradigm by implementing a Caesar encryption/decryption algorithm. Learn the compilation and linking processes by developing a dynamic library.

## Task

In this lab, you are going to create 2 projects: an executable file and a dynamic-link library (DLL) for encrypting and decrypting messages using the Caesar algorithm in the C/C++ programming language. You need to define the user command line interface of the executable file yourself.

### Task Milestones

The task can be split into four subtasks:

1. **Encrypt function**

   Create a function `encrypt` which takes two arguments:
    1. An input char array with raw text, which is going to be encrypted.
    2. The encryption key (an integer value).

   The prototype of the function will look as follows:

    ```cpp
    char* encrypt(char* rawText, int key);
    ```

   The Caesar cipher is one of the simplest ciphers. To encrypt the message, the user provides the message itself and the encryption key. The encryption key is simply an integer that shows how much the letters in the input message should be shifted alphabetically.

   Example:
    - Input: "Roses are red, violets are blue", Key: 1
    - Output: "Sptft bsf sfe, wjpmfut bsf cmvf"

2. **Decryption algorithm**

   Create a function `decrypt` which takes two arguments:
    1. An input char array with encrypted text, which is going to be decrypted.
    2. The encryption key (an integer value).

   The prototype of the function will look as follows:

    ```cpp
    char* decrypt(char* encryptedText, int key);
    ```

   The decryption algorithm is similar to the encryption algorithm, but the alphabetical shift is performed in the opposite direction.

   Example:
    - Input: "Sptft bsf sfe, wjpmfut bsf cmvf", Key: 1
    - Output: "Roses are red, violets are blue"

3. **Caesar cipher DLL**

   In this part of the task, wrap the code into a single dynamic-link library (DLL). DLLs are modular libraries that can be used across multiple projects. Developers often put CPU-intensive functionality into a DLL to import it using a programming language with another paradigm.

   Your task is to create `caesar.so` with exported `encrypt` and `decrypt` functions.

   Example code for creating a DLL:

    ```cpp
    // caesar.h
    #ifndef CAESAR_H
    #define CAESAR_H

    extern "C" {
    __declspec(dllexport) char* encrypt(char* rawText, int key);
    __declspec(dllexport) char* decrypt(char* encryptedText, int key);
    }

    #endif 
    ```

4. **Testing the dynamic library**

   Create a separate program that uses the exported functions from `caesar.so` to encrypt and decrypt messages. A simple Command Line Interface (CLI) would be enough for testing purposes. The user should be able to:
    1. Encrypt the input message using the key.
    2. Decrypt the message using the key.

## Compilation and Linking

To create the shared library on a MacBook:

1. **Compile the shared library**

    ```sh
    g++ -fPIC -shared -o /path/to/output/caesar.so /path/to/source/caesar.cpp
   
   klishchyuriy@MacBook-Pro-Yuriy cmake-build-debug % g++ -fPIC -shared -o /Users/klishchyuriy/Desktop/Programming_paradigms/TheThirdAssignment/cmake-build-debug/caesar.so /Users/klishchyuriy/Desktop/Programming_paradigms/TheThirdAssignment/caesar.cpp

    ```

2. **Compile the executable**

    ```sh
    g++ -o /path/to/output/main /path/to/source/main.cpp -ldl
   
   klishchyuriy@MacBook-Pro-Yuriy cmake-build-debug % g++ -o /Users/klishchyuriy/Desktop/Programming_paradigms/TheThirdAssignment/cmake-build-debug/main /Users/klishchyuriy/Desktop/Programming_paradigms/TheThirdAssignment/main.cpp -ldl
    ```

3. **Run the executable**

    ```sh
    cd /path/to/output/
    ./main
   
   klishchyuriy@MacBook-Pro-Yuriy cmake-build-debug % cd /Users/klishchyuriy/Desktop/Programming_paradigms/TheThirdAssignment/cmake-build-debug/
   ./main
    ```


## Theory Questions

1. **What is a low-level language?**
    - A low-level language is a programming language that provides little or no abstraction from a computer's instruction set architecture. Examples include assembly language and machine code.

2. **Key characteristics of procedural, structured, and imperative languages:**
    - **Procedural languages:** Focus on a sequence of procedures or routines to perform tasks.
    - **Structured languages:** Use a clear structure, often with functions and blocks, to enhance readability and maintainability.
    - **Imperative languages:** Describe computation in terms of statements that change a program’s state.

3. **What is a dynamic library?**
    - A dynamic library is a collection of compiled code that can be used by programs at runtime. They allow code to be shared among multiple programs, reducing memory usage and disk space.

4. **What is a static library?**
    - A static library is a collection of object files that are linked into the executable at compile time. The code from the library becomes part of the executable, resulting in a larger file size.

5. **What is a compiler?**
    - A compiler is a program that translates source code written in a high-level programming language into machine code, object code, or an intermediate code.

6. **What is a linker?**
    - A linker is a program that combines object files generated by a compiler into a single executable or library. It resolves references to undefined symbols by finding the appropriate code in other object files or libraries.

7. **Why do we need `extern "C"` construct in the code?**
    - The `extern "C"` construct is used to prevent C++ name mangling when exporting functions for use in C programs. It ensures that the function names in the object code are the same as the ones declared in the header file.

8. **What is a function pointer?**
    - A function pointer is a pointer that points to the address of a function. It can be used to call the function indirectly and to pass functions as arguments to other functions.
