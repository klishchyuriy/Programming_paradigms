### 1. Think about possible classes in your project, define fields and methods that can be inside each one, think about object’s lifetime

**Theory**:
- **Object-Oriented Design**: In object-oriented programming, the design involves breaking down the program into objects and classes. A class serves as a blueprint for objects, encapsulating data for the object and methods to manipulate that data.
- **Fields and Methods**: Fields (or attributes) are variables that hold data for the object, and methods (or functions) define the behavior of the object.
- **Object Lifetime**: The lifetime of an object includes its creation (instantiation), usage, and destruction. Proper management of an object's lifetime ensures efficient memory usage and program stability.

**Classes for Text Editor**:
- **Class**: `TextEditor`
    - **Fields**:
        - `Line* head`: Pointer to the head of the linked list of text lines.
        - `char clipboard[1024]`: Buffer to store cut/copied text.
        - `std::stack<Line*> undoStack`: Stack to store undo states.
        - `std::stack<Line*> redoStack`: Stack to store redo states.
        - `int cursorLine`: Current line of the cursor.
        - `int cursorIndex`: Current index of the cursor in the line.
    - **Methods**:
        - `appendText`: Appends text to the end.
        - `startNewLine`: Starts a new line.
        - `saveToFile`: Saves current text to a file.
        - `loadFromFile`: Loads text from a file.
        - `printCurrentText`: Prints the current text.
        - `insertText`: Inserts text at a specific position.
        - `insertTextWithReplacement`: Inserts text with replacement at a specific position.
        - `searchText`: Searches for text.
        - `clearText`: Clears all text.
        - `deleteText`: Deletes a specified number of characters.
        - `deleteTextAtCursor`: Deletes a specified number of characters at the cursor position.
        - `cutText`: Cuts a specified number of characters.
        - `cutTextAtCursor`: Cuts a specified number of characters at the cursor position.
        - `copyText`: Copies a specified number of characters.
        - `copyTextAtCursor`: Copies a specified number of characters at the cursor position.
        - `pasteText`: Pastes text at a specified position.
        - `pasteTextAtCursor`: Pastes text at the cursor position.
        - `moveCursor`: Moves the cursor to a specified position.
        - `moveCursorBy`: Moves the cursor by specified offsets.
        - `undo`: Undoes the last command.
        - `redo`: Redoes the last undone command.

**Object Lifetime**:
- **Creation**: When an instance of `TextEditor` is created.
- **Usage**: Throughout the program's execution, as the user interacts with the text editor.
- **Destruction**: When the program ends or the `TextEditor` object is no longer needed and is destroyed.

### 2. Rewrite the existing code by using object-oriented approach

**Theory**:
- **Encapsulation**: Encapsulation is the principle of bundling data and methods that operate on the data within one unit, such as a class, and restricting access to some of the object's components.
- **Inheritance**: Inheritance allows a class to inherit fields and methods from another class.
- **Polymorphism**: Polymorphism allows methods to do different things based on the object it is acting upon, even if they share the same name.

**Practical Steps**:
- Define classes and move related functions and variables into these classes.
- Ensure each class has a clear responsibility.
- Use encapsulation to protect data integrity.

**Implementation**:
Classes and methods have been defined in the provided `text_editor.h` and `text_editor.cpp` files, as detailed earlier.

### 3. Upgrade the existing Insert command with Insert + replacement mode

**Theory**:
- **Insert with Replacement**: This involves inserting new text at a specified position while replacing the existing text starting from that position.

**Example**:
1. **Append text**:
    ```cpp
    > Choose the command:
    > 1
    Enter text to append: Hello, my text editor!
    ```
2. **Print current text**:
    ```cpp
    > Choose the command:
    > 5
    Hello, my text editor!
    ```
3. **Move cursor to beginning**:
    ```cpp
    > Choose the command:
    > 15
    Enter line number: 0
    Enter character index: 0
    Cursor moved to line 0, index 0
    ```
4. **Insert text with replacement**:
    ```cpp
    > Choose the command:
    > 14
    Enter line number: 0
    Enter character index: 0
    Enter text to replace: Welcome!
    ```
5. **Print current text**:
    ```cpp
    > Choose the command:
    > 5
    Welcome! my text editor!
    ```

### 4. Implement Undo/Redo commands, consider the possible way of saving the file state before starting the implementation (note: ignore Save/Load commands for Undo/Redo)

**Theory**:
- **Undo/Redo**: Undo and redo functionality involves maintaining a history of states. When a change is made, the current state is saved. Undo reverts to the previous state, and redo reapplies a reverted state.

**Example**:
1. **Append text**:
    ```cpp
    > Choose the command:
    > 1
    Enter text to append: Hello, my text editor!
    ```
2. **Print current text**:
    ```cpp
    > Choose the command:
    > 5
    Hello, my text editor!
    ```
3. **Delete 6 characters starting at index 0**:
    ```cpp
    > Choose the command:
    > 8
    Enter line number: 0
    Enter character index: 0
    Enter number of characters to delete: 6
    ```
4. **Print current text**:
    ```cpp
    > Choose the command:
    > 5
    my text editor!
    ```
5. **Undo the last command**:
    ```cpp
    > Choose the command:
    > 9
    ```
6. **Print current text**:
    ```cpp
    > Choose the command:
    > 5
    Hello, my text editor!
    ```
7. **Redo the last command**:
    ```cpp
    > Choose the command:
    > 10
    ```
8. **Print current text**:
    ```cpp
    > Choose the command:
    > 5
    my text editor!
    ```

### 5. Implement the Delete command

**Theory**:
- **Delete Command**: This involves removing a specified number of characters from the text starting at a given position. This requires string manipulation to adjust the text content accordingly.

**Example**:
1. **Append text**:
    ```cpp
    > Choose the command:
    > 1
    Enter text to append: Hello, my text editor!
    ```
2. **Print current text**:
    ```cpp
    > Choose the command:
    > 5
    Hello, my text editor!
    ```
3. **Delete 7 characters starting at index 0**:
    ```cpp
    > Choose the command:
    > 8
    Enter line number: 0
    Enter character index: 0
    Enter number of characters to delete: 7
    ```
4. **Print current text**:
    ```cpp
    > Choose the command:
    > 5
    my text editor!
    ```

### 6. Implement Cut/Copy/Paste commands, think about reusing existing commands

**Theory**:
- **Cut/Copy/Paste**: These operations involve a clipboard buffer to temporarily store text. Cut is essentially a combination of copy and delete, while paste involves inserting text from the clipboard at a specified position.

**Example**:
1. **Append text**:
    ```cpp
    > Choose the command:
    > 1
    Enter text to append: Hello, my text editor!
    ```
2. **Print current text**:
    ```cpp
    > Choose the command:
    > 5
    Hello, my text editor!
    ```
3. **Cut the text "Hello," starting at index 0**:
    ```cpp
    > Choose the command:
    > 16
    Enter number of characters to cut: 6
    ```
4. **Print current text**:
    ```cpp
    > Choose the command:
    > 5
    my text editor!
    ```
5. **Move cursor to the end of the text**:
    ```cpp
    > Choose the command:
    > 15
    Enter line number: 0
    Enter character index: 14
    Cursor moved to line 0, index 14
    ```
6. **Paste the previously cut text at the end**:
    ```cpp
    > Choose the command:
    > 18
    ```
7. **Print current text**:
    ```cpp
    > Choose the command:
    > 5
    my text editor!Hello,
    ```
8. **Copy the text "my" starting at index 0**:
    ```cpp
    > Choose the command:
    > 17
    Enter number of characters to copy: 2
    ```
9. **Paste the copied text

at the beginning**:
```cpp
> Choose the command:
> 18
```
10. **Print current text**:
    ```cpp
    > Choose the command:
    > 5
    my my text editor!Hello,
    ```