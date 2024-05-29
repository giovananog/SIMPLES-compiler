# SIMPLES Compiler

![GitHub repo size](https://img.shields.io/github/repo-size/giovananog/SIMPLES-compiler?style=for-the-badge)
![GitHub language count](https://img.shields.io/github/languages/count/giovananog/SIMPLES-compiler?style=for-the-badge)
![GitHub forks](https://img.shields.io/github/forks/giovananog/SIMPLES-compiler?style=for-the-badge)

<br><br>
<img src="https://www.unifal-mg.edu.br/portal2/wp-content/uploads/sites/52/2018/04/cropped-logo-unifal-1.png" alt="Example image">

> This repository contains the implementation of a compiler for the SIMPLES language as part of the Compiler Theory and Language course, taught by Professor Luiz Eduardo da Silva at the Federal University of Alfenas (UNIFAL-MG).

<br><br>
## 💻 Objective

The objective of this project is to enhance the SIMPLES compiler to allow compilation of record types. Additionally, the compiler should include semantic actions for type checking in expressions containing records.

## 📋 Problem

Records are heterogeneous data structures that compose a set of variables that can have different types. Each element of the record set is individually accessed through the access expression: `<record-name>.<field-name>`. Fields can only be accessed in this way. Record fields can also be records themselves. When declaring a record, space must be reserved for each field, starting from a base address. The name of the record refers to this initial memory address. Therefore, each field corresponds to an offset from this initial address.

## 🛠️ Instructions

1. Modify the rules for variable declaration, reading variables, assignment command, and expressions to allow the use of records in the SIMPLES language.
   - Modify the variable declaration rules to allow declarations in this form:
     ```
     registro reg1
     def
       inteiro a
       logico b
     fim def c
     ```
   - This declaration should be stored in the symbol table for later translation of operations with variables of the record type. A suggested structure is the linked list of fields.

2. Modify the rules where access expressions with records and record fields can be used (reading, writing, assignment, and expressions in general) to translate the access expression to memory locations.

## 📁 Project Structure

The project directory should include the following files:

- `lexico.l`: Lexer file for lexical analysis.
- `sintatico.y`: Parser file for syntactic analysis.
- `utils.c`: Utility functions used in the compiler.
- `makefile`: Makefile for compiling the SIMPLES compiler.

## ⚙️ Compilation and Execution

To compile the SIMPLES compiler, use the following commands:

```bash
make simples
```
To clean the project directory, use:
```bash
make clean
```
To run the compiler, use the following command:
```bash
./simples <program-name>.simples
```

