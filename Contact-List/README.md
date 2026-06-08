#Comp 1700 Project: Contact List Manager

## Authors
**Oliver Pham**

## Description
This program manages a list of contacts, storing information such as last name, first name, phone number, and email as simple strings. The contact list data is stored in a Comma-Separated Value (CSV) file, and the user interacts with the program by typing case-insensitive commands (ADD, UPDATE, SHOW, LIST, SORT, FIND, DELETE, SAVE, QUIT) via the command line to perform common management tasks.

## External Resources
- Class notes
- stringmanip.hpp and stringmanip.cpp samples
- [Examples of Lambda Expressions](https://learn.microsoft.com/en-us/cpp/cpp/examples-of-lambda-expressions?view=msvc-170)
- [Constructors and member initializer lists](https://en.cppreference.com/w/cpp/language/initializer_list.html)

## Instructions
Kinda self-explanatory but here's how to use the commands (follow it exactly and sub *italics* for your own info)
- ADD
- UPDATE
- SHOW *first-name* *last-name*
- SORT *field*
- FIND *substring*
- DELETE *first-name* *last-name*
- SAVE
- QUIT
- HELP
- HELP *command*

## Shortcomings
- The console outputs get pretty lengthy, so adding a claer command would help.

## Extras
- The SORT Command can use all four fields (first, last, phone, email)
- HELP command
