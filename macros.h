#ifndef macros_h
#define macros_h

#define TK_EOF 0
#define TK_EOLN 1

//CONTROL KEYWORDS
#define TK_BEGIN 2
#define TK_END 3
#define TK_IF 4
#define TK_ELSE 5
#define TK_GOTO 6
#define TK_FOR 7
#define TK_REPEAT 8
#define TK_WRITE 9
#define TK_ASSIGN 10
#define TK_UNTIL 11
#define TK_DO 12
#define TK_THEN 13
#define TK_WHILE 14
#define TK_CASE 15
#define TK_OF 16

//OPERATOR KEYWORDS
#define TK_AND 17
#define TK_BAND 18
#define TK_OR 19
#define TK_XOR 20
#define TK_NOT 21
#define TK_IN 22
#define TK_SHL 23
#define TK_SHR 24
#define TK_DIV 25
#define TK_MOD 26

//SYMBOLS
#define TK_PLUS 27
#define TK_MINUS 28
#define TK_MULTIPLY 29
#define TK_DIVIDE 30
#define TK_COMMA 31
#define TK_SEMICOLON 32
#define TK_PERIOD 33
#define TK_LPAREN 34
#define TK_RPAREN 35
#define TK_LB 36
#define TK_RB 37
#define TK_COLON 38
#define TK_DOT 39
#define TK_EQ 40
#define TK_NEQ 41
#define TK_LESSER 42
#define TK_GREATER 43
#define TK_GEQ 44
#define TK_LEQ 45
#define TK_RANGE 46

//CLASSIFIERS
#define TK_INTLIT 47
#define TK_CHARLIT 48
#define TK_REALLIT 49
#define TK_STRLIT 50
#define TK_LABEL 51
#define TK_VAR 52
#define TK_A_LABEL 53
#define TK_CONST 54
#define TK_TYPE 55
#define TK_PROCEDURE 56
#define TK_FUNCTION 57
#define TK_UNKNOWN 58
#define TK_INTEGER 59
#define TK_REAL 60
#define TK_A_VAR 61
#define TK_BOOLEAN 62
#define TK_STRING 63
#define TK_CHAR 64
#define TK_PROGNAME 87

//OTHER KEYWORDS
#define TK_ASM 65
#define TK_ARRAY 66
#define TK_BREAK 67
#define TK_DESTRUCTOR 68
#define TK_FALSE 69
#define TK_FILE 70
#define TK_IMPLEMENTATION 71
#define TK_INLINE 72
#define TK_INTERFACE 73
#define TK_NIL 74
#define TK_OBJECT 75
#define TK_ON 76
#define TK_OPERATOR 77
#define TK_PACKED 78
#define TK_PROGRAM 79
#define TK_RECORD 80
#define TK_SET 81

#define TK_TO 82
#define TK_TRUE 83
#define TK_UNIT 84
#define TK_USES 85
#define TK_WITH 86

//LIMITS
#define MAXNAME 32
#define MAXLEN 255

//TYPES
#define TP_INT 1
#define TP_REAL 2
#define TP_LABEL 3
#define TP_CHAR 4
#define TP_BOOL 5
#define TP_ENUM 6
#define TP_ARR 7
#define TP_STR 8
#define TP_TYPE 9
#define TP_PTR 10
#define TP_REC 11
#define TP_SET 12
#define TP_PROC 13
#define TP_FUNC 14
#define TP_FILE 15
#define TP_CLASS 16

//OPCODES
#define OP_HALT 0
#define OP_PUSH 1
#define OP_POP 2
#define OP_ADD 3
#define OP_SUB 4
#define OP_MUL 5
#define OP_DIV 6
#define OP_ADDI 7
#define OP_SUBI 8
#define OP_PUSHI 9
#define OP_PUT 10
#define OP_JMP 11
#define OP_JFALSE 12
#define OP_GET 13
#define OP_PRINTINT 14
#define OP_PRINTCHAR 15
#define OP_PRINTSTR 16
#define OP_PRINTBOOL 17
#define OP_PRINTREAL 18


#endif
