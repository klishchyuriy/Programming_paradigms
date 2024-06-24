## Overview

This project implements a Caesar cipher for file encryption and decryption using a dynamic library. The Caesar cipher is a simple substitution cipher where each letter in the plaintext is shifted a certain number of places down or up the alphabet. The project also includes chunk mode processing to handle large files efficiently.

## Caesar Cipher Theory

The Caesar cipher is a substitution cipher in which each letter in the plaintext is shifted a certain number of places down or up the alphabet.

### Example

- Plaintext: "HELLO"
- Shift: 3
- Ciphertext: "KHOOR"

### Formula

For encryption:
\[ \text{Encrypted\_char} = (\text{Plain\_char} - \text{base} + \text{key}) \% 26 + \text{base} \]

For decryption:
\[ \text{Decrypted\_char} = (\text{Encrypted\_char} - \text{base} - \text{key} + 26) \% 26 + \text{base} \]

Where:
- `base` is 'A' for uppercase letters or 'a' for lowercase letters.
- `key` is the shift value.

### The Role of the Key

The key in the Caesar cipher determines how many positions each letter in the plaintext is shifted. Changing the key changes the resulting ciphertext. For example, with a key of 3, 'A' becomes 'D', 'B' becomes 'E', and so on. If the key is changed to 5, 'A' would become 'F', 'B' would become 'G', etc.

### Examples of Different Keys

- **Key = 3**
  - Plaintext: "HELLO"
  - Ciphertext: "KHOOR"

- **Key = 5**
  - Plaintext: "HELLO"
  - Ciphertext: "MJQQT"

If the key value exceeds 25, it wraps around using the modulo operation. For instance, a key of 29 is equivalent to a key of 3 (since 29 % 26 = 3).

## Implementation Details

### Dynamic Library (`libcaesar.dylib`)

The encryption and decryption logic is implemented in a dynamic library to separate concerns and facilitate reuse.

**Key Parts of `caesar.cpp`**:
```cpp
extern "C" {
    void encrypt(const char* input, char* output, int key) {
        key = key % 26;  // Reduce the key to the range [0, 25]
        // Encryption logic
    }

    void decrypt(const char* input, char* output, int key) {
        key = key % 26;  // Reduce the key to the range [0, 25]
        // Decryption logic
    }
}
```

### In order to make the Caesar cipher work with the text files, you need to implement several classes:

1. **CaesarCipher**:
    - Handles the core logic for encryption and decryption.
    - Uses the dynamic library for the actual encryption/decryption operations.

   **Key Parts of `caesar_cipher.h`**:
   ```cpp
   class CaesarCipher {
   public:
       CaesarCipher(const char* libraryPath);
       ~CaesarCipher();

       void encrypt(const char* input, char* output, int key);
       void decrypt(const char* input, char* output, int key);

   private:
       typedef void (*EncryptDecryptFunc)(const char*, char*, int);
       EncryptDecryptFunc encryptFunc;
       EncryptDecryptFunc decryptFunc;
       void* libraryHandle;

       void loadLibrary(const char* libraryPath);
       void unloadLibrary();
   };
   ```

2. **TextEditor**:
    - Encapsulates the functionality to read from and write to files.
    - Encrypts and decrypts files in chunks to handle large files efficiently.

   **Key Parts of `text_editor.cpp`**:
   ```cpp
   void TextEditor::encryptFile(const char* inputFile, const char* outputFile, int key) {
       const size_t CHUNK_SIZE = 1024;
       char inputChunk[CHUNK_SIZE];
       char outputChunk[CHUNK_SIZE];

       std::ifstream inFile(inputFile, std::ios::binary);
       std::ofstream outFile(outputFile, std::ios::binary);

       while (inFile.read(inputChunk, CHUNK_SIZE) || inFile.gcount() > 0) {
           size_t bytesRead = inFile.gcount();
           caesarCipher.encrypt(inputChunk, outputChunk, key);
           outFile.write(outputChunk, bytesRead);
       }

       inFile.close();
       outFile.close();
   }

   void TextEditor::decryptFile(const char* inputFile, const char* outputFile, int key) {
       const size_t CHUNK_SIZE = 1024;
       char inputChunk[CHUNK_SIZE];
       char outputChunk[CHUNK_SIZE];

       std::ifstream inFile(inputFile, std::ios::binary);
       std::ofstream outFile(outputFile, std::ios::binary);

       while (inFile.read(inputChunk, CHUNK_SIZE) || inFile.gcount() > 0) {
           size_t bytesRead = inFile.gcount();
           caesarCipher.decrypt(inputChunk, outputChunk, key);
           outFile.write(outputChunk, bytesRead);
       }

       inFile.close();
       outFile.close();
   }
   ```

### Optional: Chunk Mode for Files Encryption/Decryption

Chunk mode is implemented to handle large files efficiently by processing them in smaller chunks (e.g., 1024 bytes). This prevents high memory usage and allows the program to handle files larger than the available memory.

**Benefits**:
- **Memory Efficiency**: Processes large files without loading the entire file into memory.
- **Scalability**: Handles files of arbitrary size by processing them in manageable chunks.

### Conclusion

This project demonstrates the implementation of the Caesar cipher using a dynamic library and includes the capability to process files in chunks. The dynamic library approach modularizes the encryption/decryption logic, making it reusable and maintainable. The chunk mode enhances the program's ability to handle large files efficiently, making it a robust solution for file encryption and decryption tasks.

---
