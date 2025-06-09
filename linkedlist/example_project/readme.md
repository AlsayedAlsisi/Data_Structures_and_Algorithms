* How to compile
Provided two folders:
[1] First folder: contains all implementation files(.c and .h) as plain text files.
Add to any already existing project, link them, and run.
Name of the folder: implementation_files_plain

[2] Code::Blocks project
Open with Code::Blocks and run
CodeBlock versonused 20.3
The entire solution should is implemented in pure C (C89/C90 standard). No other compilation conditions or pre-requisites exist.
Name of the folder: c_container_CodeBlocks_project


* Design
The dynamic array solution is based on LinkedList data structure and dynamic memory allocation to make best use of memory.
Especial care was made to prevent against dynamic memory allocation problems and dangling pointers.

* Tests
All tests are implemented in Test component(test. and test.h) and can be run by calling test_run() API from main application(provided main.c).