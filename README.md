# Lexeme Counter

This C++ project is designed to count leximes (lexical items) in a given source code file. Leximes include reserved words, operators, and identifiers. The project provides insights into the distribution of these elements in the code, helping developers analyze and understand their codebase better.

## Features

- Counts and categorizes C++ reserved words, operators, and identifiers.
- Handles common C++ operators and reserved words.
- Supports user input for the source code file.
- Outputs detailed information about the leximes found in the code.

## Usage

**Clone the Repository:**

   ```bash
   git clone https://github.com/Samibltc/LexemeCounter
```
## Code Structure
 - lexime_counter.cpp: Contains the main C++ code for lexime counting.
 - cppReservedWords: Vector containing common C++ reserved words.
 - cppOperators: Vector containing common C++ operators.
 - tokenize: Function for tokenizing a line of code.
 - isValidIdentifier: Function to check the validity of an identifier.
 - countLexemes: Function to count and categorize leximes in the given source code file.

## Contributors

- [Sami Balatacı](https://github.com/Samibltc)
- [Semih Apaydın](https://github.com/byrani)
