# CSC420-Pascal-Like-Comp

This is a university project that I was not able to finish but have decided to continue working on it in my spare time. The compiler is Pascal-like in the sense that some features are of a different syntax such as C styled headers and does not read the entire Pascal grammar. These will be properly documented over time as I make more progress. Below is the readme straight from my final submission with minor modifications.

Overall Status: Incomplete\
Scanner - Complete\
Symbol Table - Complete\
Parser - Partially complete\
Emitter - None

Note\
The executable is not very clean, it has simply been able to show that 
the program will "compile" without crashing as there is no proper 
emitter implemented. Most of the work is on the code itself.

Scanner\
-Fully functional

Header\
-Can read program start\
-No header includes, C nor Pascal-like

Grammar\
-Relational Grammar implemented\
-No emitter

Symbol Table\
-Can check for declared variables\
-Scope checking unverified as there is no procedure or function support

Declarations\
-Variables, const, types fully supported\
-No enum, range, and array support\
-Labels can be declared, but there is no goto support\
-No procedure support\
-No function support

Statements\
-Can parse assignments, repeat, 1 statement while, if..then..else, 1 argument write\
-Halfway complete with assignments\
-No goto support\
-No for support\
-No case support

