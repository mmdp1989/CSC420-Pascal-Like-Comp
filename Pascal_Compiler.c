#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "macros.h"
#include "symbol_table.h"

int curtoken;
int curvalue;
float curfloat;
char curname[MAXNAME];
char curstr[MAXLEN];
char cursymbol[5];
int curfile;
int curline;
int curcol;
int curpos;

int addr;
int seen;
unsigned char *scanp;

unsigned char CODE[2056];
int IP = 0;

unsigned char DATA[2056];
int DP = 0;

unsigned char STACK[2056];
int SP = 0;
int BP;


struct Scope_Tree_Node *current_scope;
struct Scope_Tree_Node *global_scope;

void initialize();
void gettoken();
void printtoken();
void match(int t);
void error();
void G();
int R();
int E();
int T();
int F();
void compile();
void header();

void declarations();
void declaration();
void var_declaration();
void label_declaration();

void const_declaration();
void type_declaration();
void procedure_declaration();
void function_declaration();
void begin_statement();

void statements();
void statement();
int find_token();
void assignment();
void write_statement();
void for_statement();
void repeat_statement();
void condition();
void while_statement();
void if_statement();
void process_a_label();
//void goto_statement();
int find_token();

void do_ADD(int t1, int t2);
void do_SUB(int t1, int t2);
void do_MUL(int t1, int t2);
void do_DIV(int t1, int t2);
void do_OR(int t1, int t2);
void do_AND(int t1, int t2);
void do_XOR(int t1, int t2);
void do_NOP(int t1);
void do_NEG(int t1);
void do_NOT(int t1);
void do_LIT(int t1);
void do_EQ(int t1, int t2);
void do_NEQ(int t1, int t2);
void do_LESSER(int t1, int t2);
void do_GREATER(int t1, int t2);
void do_LEQ(int t1, int t2);
void do_GEQ(int t1, int t2);

void emit_opcode(int code);
void emit_int(int val);
int size(int val);

int main(void) {

	initialize();
	/*
	do {
		gettoken();
		printtoken();
	}while(curtoken != TK_EOF);
	*/
	compile();
	system("PAUSE");
	exit(0);
}

//Done
void initialize() {
	FILE *f = fopen("var_example.txt", "rb");
	if(!f) printf("Source file not found");
	fseek(f, 0, SEEK_END);
	int sz = ftell(f);
	fseek(f, 0, SEEK_SET);
	unsigned char *buff = malloc(sz + 1);
	fread(buff, sz, 1, f);
	fclose(f);
	buff[sz] = 0;
	scanp = buff;
}

//Done(?)
void gettoken() {
	unsigned char c;
	unsigned char *temp;
	char token[MAXNAME];
	char str[MAXLEN];
	int i = 0;
	int j = 0;
	int value = 0;
	int base = 10;
	float dec = 0;

	curcol = 0;
	restart:
	switch (c = *scanp++) {
		case 'a':
		case 'A':
			memset(token, '\0', sizeof(token));
			i = 0;
			do{
				token[i] = tolower(c);
				temp = scanp;
				c = *scanp++;
				i++;
			}while((isalpha(c) || c == '_') && i < 32);
			scanp = temp;
			if (i == 32) {
				printf("Identifier too long.");
				error();
			}
			else if(!strcmp(token, "and")) curtoken = TK_AND;
			else if(!strcmp(token, "array")) curtoken = TK_ARRAY;
			else if(!strcmp(token, "asm")) curtoken = TK_ASM;
			else curtoken = TK_UNKNOWN;
			strcpy(curname, token);
			break;
		case 'b':
		case 'B':
			memset(token, '\0', sizeof(token));
			i = 0;
			do{
				token[i] = tolower(c);
				temp = scanp;
				c = *scanp++;
				i++;
			}while((isalpha(c) || c == '_') && i < 32);
			scanp = temp;
			if (i == 32) {
				printf("Identifier too long.");
				error();
			}
			else if(!strcmp(token, "begin")) curtoken = TK_BEGIN;
			else if(!strcmp(token, "boolean")) curtoken = TK_BOOLEAN;
			else if(!strcmp(token, "break")) curtoken = TK_BREAK;
			else curtoken = TK_UNKNOWN;
			strcpy(curname, token);
			break;
		case 'c':
		case 'C':
			memset(token, '\0', sizeof(token));
			i = 0;
			do{
				token[i] = tolower(c);
				temp = scanp;
				c = *scanp++;
				i++;
			}while((isalpha(c) || c == '_') && i < 32);
			scanp = temp;
			if (i == 32) {
				printf("Identifier too long.");
				error();
			}
			else if(!strcmp(token, "case")) curtoken = TK_CASE;
			else if(!strcmp(token, "const")) curtoken = TK_CONST;
			else curtoken = TK_UNKNOWN;
			strcpy(curname, token);
			break;
		case 'd':
		case 'D':
			memset(token, '\0', sizeof(token));
			i = 0;
			do{
				token[i] = tolower(c);
				temp = scanp;
				c = *scanp++;
				i++;
			}while((isalpha(c) || c == '_') && i < 32);
			scanp = temp;
			if (i == 32) {
				printf("Identifier too long.");
				error();
			}
			else if(!strcmp(token, "destructor")) curtoken = TK_DESTRUCTOR;
			else if(!strcmp(token, "div")) curtoken = TK_DIV;
			else if(!strcmp(token, "do")) curtoken = TK_DO;
			else curtoken = TK_UNKNOWN;
			strcpy(curname, token);
			break;
		case 'e':
		case 'E':
			memset(token, '\0', sizeof(token));
			i = 0;
			do{
				token[i] = tolower(c);
				temp = scanp;
				c = *scanp++;
				i++;
			}while((isalpha(c) || c == '_') && i < 32);
			scanp = temp;
			if (i == 32) {
				printf("Identifier too long.");
				error();
			}
			else if(!strcmp(token, "else")) curtoken = TK_ELSE;
			else if(!strcmp(token, "end")) curtoken = TK_END;
			else curtoken = TK_UNKNOWN;
			strcpy(curname, token);
			break;
		case 'f':
		case 'F':
			memset(token, '\0', sizeof(token));
			i = 0;
			do{
				token[i] = tolower(c);
				temp = scanp;
				c = *scanp++;
				i++;
			}while((isalpha(c) || c == '_') && i < 32);
			scanp = temp;
			if (i == 32) {
				printf("Identifier too long.");
				error();
			}
			else if(!strcmp(token, "false")) curtoken = TK_FALSE;
			else if(!strcmp(token, "file")) curtoken = TK_FILE;
			else if(!strcmp(token, "for")) curtoken = TK_FOR;
			else if(!strcmp(token, "function")) curtoken = TK_FUNCTION;
			else curtoken = TK_UNKNOWN;
			strcpy(curname, token);
			break;
		case 'g':
		case 'G':
			memset(token, '\0', sizeof(token));
			i = 0;
			do{
				token[i] = tolower(c);
				temp = scanp;
				c = *scanp++;
				i++;
			}while((isalpha(c) || c == '_') && i < 32);
			scanp = temp;
			if (i == 32) {
				printf("Identifier too long.");
				error();
			}
			else if(!strcmp(token, "goto")) curtoken = TK_GOTO;
			else curtoken = TK_UNKNOWN;
			strcpy(curname, token);
			break;
		case 'i':
		case 'I':
			memset(token, '\0', sizeof(token));
			i = 0;
			do{
				token[i] = tolower(c);
				temp = scanp;
				c = *scanp++;
				i++;
			}while((isalpha(c) || c == '_') && i < 32);
			scanp = temp;
			if (i == 32) {
				printf("Identifier too long.");
				error();
			}
			else if(!strcmp(token, "if")) curtoken = TK_IF;
			else if(!strcmp(token, "implementation")) curtoken = TK_IMPLEMENTATION;
			else if(!strcmp(token, "in")) curtoken = TK_IN;
			else if(!strcmp(token, "inline")) curtoken = TK_INLINE;
			else if(!strcmp(token, "integer")) curtoken = TK_INTEGER;
			else if(!strcmp(token, "interface")) curtoken = TK_INTERFACE;
			else curtoken = TK_UNKNOWN;
			strcpy(curname, token);
			break;
		case 'l':
		case 'L':
			memset(token, '\0', sizeof(token));
			i = 0;
			do{
				token[i] = tolower(c);
				temp = scanp;
				c = *scanp++;
				i++;
			}while((isalpha(c) || c == '_') && i < 32);
			scanp = temp;
			if (i == 32) {
				printf("Identifier too long.");
				error();
			}
			else if(!strcmp(token, "label")) curtoken = TK_LABEL;
			else curtoken = TK_UNKNOWN;
			strcpy(curname, token);
			break;
		case 'm':
		case 'M':
			memset(token, '\0', sizeof(token));
			i = 0;
			do{
				token[i] = tolower(c);
				temp = scanp;
				c = *scanp++;
				i++;
			}while((isalpha(c) || c == '_') && i < 32);
			scanp = temp;
			if (i == 32) {
				printf("Identifier too long.");
				error();
			}
			else if(!strcmp(token, "mod")) curtoken = TK_MOD;
			else curtoken = TK_UNKNOWN;
			strcpy(curname, token);
			break;
		case 'n':
		case 'N':
			memset(token, '\0', sizeof(token));
			i = 0;
			do{
				token[i] = tolower(c);
				temp = scanp;
				c = *scanp++;
				i++;
			}while((isalpha(c) || c == '_') && i < 32);
			scanp = temp;
			if (i == 32) {
				printf("Identifier too long.");
				error();
			}
			else if(!strcmp(token, "not")) curtoken = TK_NOT;
			else if(!strcmp(token, "nil")) curtoken = TK_NIL;
			else curtoken = TK_UNKNOWN;
			strcpy(curname, token);
			break;
		case 'o':
		case 'O':
			memset(token, '\0', sizeof(token));
			i = 0;
			do{
				token[i] = tolower(c);
				temp = scanp;
				c = *scanp++;
				i++;
			}while((isalpha(c) || c == '_') && i < 32);
			scanp = temp;
			if (i == 32) {
				printf("Identifier too long.");
				error();
			}
			else if(!strcmp(token, "object")) curtoken = TK_OBJECT;
			else if(!strcmp(token, "of")) curtoken = TK_OF;
			else if(!strcmp(token, "on")) curtoken = TK_ON;
			else if(!strcmp(token, "operator")) curtoken = TK_OPERATOR;
			else if(!strcmp(token, "or")) curtoken = TK_OR;
			else curtoken = TK_UNKNOWN;
			strcpy(curname, token);
			break;
		case 'p':
		case 'P':
			memset(token, '\0', sizeof(token));
			i = 0;
			do{
				token[i] = tolower(c);
				temp = scanp;
				c = *scanp++;
				i++;
			}while((isalpha(c) || c == '_') && i < 32);
			scanp = temp;
			if (i == 32) {
				printf("Identifier too long.");
				error();
			}
			else if(!strcmp(token, "packed")) curtoken = TK_PACKED;
			else if(!strcmp(token, "procedure")) curtoken = TK_PROCEDURE;
			else if(!strcmp(token, "program")) curtoken = TK_PROGRAM;
			else curtoken = TK_UNKNOWN;
			strcpy(curname, token);
			break;
		case 'r':
		case 'R':
			memset(token, '\0', sizeof(token));
			i = 0;
			do{
				token[i] = tolower(c);
				temp = scanp;
				c = *scanp++;
				i++;
			}while((isalpha(c) || c == '_') && i < 32);
			scanp = temp;
			if (i == 32) {
				printf("Identifier too long.");
				error();
			}
			else if(!strcmp(token, "record")) curtoken = TK_RECORD;
			else if(!strcmp(token, "repeat")) curtoken = TK_REPEAT;
			else curtoken = TK_UNKNOWN;
			strcpy(curname, token);
			break;
		case 's':
		case 'S':
			memset(token, '\0', sizeof(token));
			i = 0;
			do{
				token[i] = tolower(c);
				temp = scanp;
				c = *scanp++;
				i++;
			}while((isalpha(c) || c == '_') && i < 32);
			scanp = temp;
			if (i == 32) {
				printf("Identifier too long.");
				error();
			}
			else if(!strcmp(token, "set")) curtoken = TK_SET;
			else if(!strcmp(token, "shl")) curtoken = TK_SHL;
			else if(!strcmp(token, "shr")) curtoken = TK_SHR;
			else if(!strcmp(token, "string")) curtoken = TK_STRING;
			else curtoken = TK_UNKNOWN;
			strcpy(curname, token);
			break;
		case 't':
		case 'T':
			memset(token, '\0', sizeof(token));
			i = 0;
			do{
				token[i] = tolower(c);
				temp = scanp;
				c = *scanp++;
				i++;
			}while((isalpha(c) || c == '_') && i < 32);
			scanp = temp;
			if (i == 32) {
				printf("Identifier too long.");
				error();
			}
			else if(!strcmp(token, "to")) curtoken = TK_TO;
			else if(!strcmp(token, "true")) curtoken = TK_TRUE;
			else if(!strcmp(token, "type")) curtoken = TK_TYPE;
			else curtoken = TK_UNKNOWN;
			strcpy(curname, token);
			break;
		case 'u':
		case 'U':
			memset(token, '\0', sizeof(token));
			i = 0;
			do{
				token[i] = tolower(c);
				temp = scanp;
				c = *scanp++;
				i++;
			}while(isalpha(c) && i < 32);
			scanp = temp;
			if (i == 32) printf("Identifier too long.");
			else if(!strcmp(token, "unit")) curtoken = TK_UNIT;
			else if(!strcmp(token, "until")) curtoken = TK_UNTIL;
			else if(!strcmp(token, "uses")) curtoken = TK_USES;
			else curtoken = TK_UNKNOWN;
			strcpy(curname, token);
			break;
		case 'v':
		case 'V':
			memset(token, '\0', sizeof(token));
			i = 0;
			do{
				token[i] = tolower(c);
				temp = scanp;
				c = *scanp++;
				i++;
			}while((isalpha(c) || c == '_') && i < 32);
			scanp = temp;
			if (i == 32) {
				printf("Identifier too long.");
				error();
			}
			else if(!strcmp(token, "var")) curtoken = TK_VAR;
			else curtoken = TK_UNKNOWN;
			strcpy(curname, token);
			break;
		case 'w':
		case 'W':
			memset(token, '\0', sizeof(token));
			i = 0;
			do{
				token[i] = tolower(c);
				temp = scanp;
				c = *scanp++;
				i++;
			}while((isalpha(c) || c == '_') && i < 32);
			scanp = temp;
			if (i == 32) {
				printf("Identifier too long.");
				error();
			}
			else if(!strcmp(token, "while")) curtoken = TK_WHILE;
			else if(!strcmp(token, "with")) curtoken = TK_WITH;
			else curtoken = TK_UNKNOWN;
			strcpy(curname, token);
			break;
		case 'x':
		case 'X':
			memset(token, '\0', sizeof(token));
			i = 0;
			do{
				token[i] = tolower(c);
				temp = scanp;
				c = *scanp++;
				i++;
			}while((isalpha(c) || c == '_') && i < 32);
			scanp = temp;
			if (i == 32) {
				printf("Identifier too long.");
				error();
			}
			else if(!strcmp(token, "xor")) curtoken = TK_XOR;
			else curtoken = TK_UNKNOWN;
			strcpy(curname, token);
			break;
		case 'h':
		case 'H':
		case 'j':
		case 'J':
		case 'k':
		case 'K':
		case 'q':
		case 'Q':
		case 'y':
		case 'Y':
		case 'z':
		case 'Z':
			memset(token, '\0', sizeof(token));
			i = 0;
			do{
				token[i] = tolower(c);
				temp = scanp;
				c = *scanp++;
				i++;
			}while((isalpha(c) || c == '_') && i < 32);
			scanp = temp;
			if (i == 32) {
				printf("Identifier too long.");
				error();
			}
			else {
				strcpy(curname, token);
				//if(find_token()) curtoken = TK_A_VAR;
				curtoken = TK_UNKNOWN;
			}
			break;
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			value = 0; base = 10;
			while(c >= '0' && c <= '9') {
				value = value * base + c - '0';
				temp = scanp;
				c = *scanp++;
			}
			if(isalpha(c)) printf("Syntax Error");
			else if (c != '.') {
				curtoken = TK_INTLIT;
				curvalue = value;
				scanp = temp;
			}
			else {
				dec = 0; j = 0;
				while(c >= '0' && c <= '9'){
					dec = dec * base + c - '0';
					temp = scanp;
					c = *scanp++;
					j++;
				}
				dec = dec/(10*j);
				scanp = temp;
				if(isalpha(c)) error();
				else {
					curtoken = TK_REALLIT;
					curfloat = dec + value;
				}
			}
			break;
		case '=':
			strcpy(cursymbol, "=");
			curtoken = TK_EQ;
			break;
		case '+':
			strcpy(cursymbol, "+");
			curtoken = TK_PLUS;
			break;
		case '-':
			strcpy(cursymbol, "-");
			curtoken = TK_MINUS;
			break;
		case ',':
			strcpy(cursymbol, ",");
			curtoken = TK_COMMA;
			break;
		case ';':
			strcpy(cursymbol, ";");
			curtoken = TK_SEMICOLON;
			break;
		case ':':
			temp = scanp;
			c = *scanp++;
			if(c == '=') {
				strcpy(cursymbol, ":=");
				curtoken = TK_ASSIGN;
			}
			else {
				strcpy(cursymbol, ":");
				curtoken = TK_COLON;
				scanp = temp;
			}
			break;
		case '.':
			temp = scanp;
			c = *scanp++;
			if(c == '.') {
				strcpy(cursymbol, "..");
				curtoken = TK_RANGE;
			}
			else {
				strcpy(cursymbol, ".");
				curtoken = TK_PERIOD;
				scanp = temp;
			}
			break;
		case '<':
			temp = scanp;
			c = *scanp++;
			if(c == '=') {
				strcpy(cursymbol, "<=");
				curtoken = TK_LEQ;
			}
			else if(c == '>') {
				strcpy(cursymbol, "<>");
				curtoken = TK_NEQ;
			}
			else if(c == '<') {
				strcpy(cursymbol, "<<");
				curtoken = TK_SHL;
			}
			else {
				strcpy(cursymbol, "<");
				curtoken = TK_LESSER;
				scanp = temp;
			}
			break;
		case '>':
			temp = scanp;
			c = *scanp++;
			if(c == '=') {
				strcpy(cursymbol, ">=");
				curtoken = TK_GEQ;
			}
			else if(c == '>') {
				strcpy(cursymbol, ">>");
				curtoken = TK_SHR;
			}
			else {
				strcpy(cursymbol, ">");
				curtoken = TK_GREATER;
				scanp = temp;
			}
			break;
		case '(':
			temp = scanp;
			c = *scanp++;
			if(c == '*'){
				do{
					temp = scanp;
					c = *scanp++;
				}while(c != '*');
				c = *scanp++;
				goto restart;
			}
			else {
				strcpy(cursymbol, "(");
				curtoken = TK_LPAREN;
				scanp = temp;
			}
			break;
		case ')':
			strcpy(cursymbol, ")");
			curtoken = TK_RPAREN;
			break;
		case '\'':
			memset(str, '\0', sizeof(str));
			i = 0;
			temp = scanp;
			c = *scanp++;
			reread:
			while(c != '\'') {
				str[i] = c;
				temp = scanp;
				c = *scanp++;
				i++;
			}
			temp = scanp;
			c = *scanp++;
			if(c == '\'') {
				str[i] = c;
				goto reread;
				i++;
			}
			else {
				curtoken = TK_STRLIT;
				strcpy(curstr, str);
				scanp = temp;
			}
			break;
		case ' ':
			goto restart;
		case '\r':
			c = *scanp++;
			curcol++;
			//curtoken = TK_EOLN;
			goto restart;
			break;
		case 0:
			curtoken = TK_EOF;
	}
}

//Only for diagnostics
void printtoken() {
	switch(curtoken){
		case 0:
			printf("Token ID: %d\nToken Value: End of File\n\n", curtoken);
			break;
		case 1:
			printf("Token ID: %d\nToken Value: End of Line\n\n", curtoken);
			break;
		case 2:
			printf("Token ID: %d\nToken Value: Begin\n\n", curtoken);
			break;
		case 3:
			printf("Token ID: %d\nToken Value: End\n\n", curtoken);
			break;
		case 4:
			printf("Token ID: %d\nToken Value: If\n\n", curtoken);
			break;
		case 5:
			printf("Token ID: %d\nToken Value: Else\n\n", curtoken);
			break;
		case 8:
			printf("Token ID: %d\nToken Value: Repeat\n\n", curtoken);
			break;
		case 9:
			printf("Token ID: %d\nToken Value: Write\n\n", curtoken);
			break;
		case 10:
			printf("Token ID: %d\nToken Value: Assign\n\n", curtoken);
			break;
		case 11:
			printf("Token ID: %d\nToken Value: Until\n\n", curtoken);
			break;
		case 12:
			printf("Token ID: %d\nToken Value: Do\n\n", curtoken);
			break;
		case 13:
			printf("Token ID: %d\nToken Value: Then\n\n", curtoken);
			break;
		case 14:
			printf("Token ID: %d\nToken Value: While\n\n", curtoken);
			break;
		case 17:
			printf("Token ID: %d\nToken Value: And\n\n", curtoken);
			break;
		case 27:
			printf("Token ID: %d\nToken Value: +\n\n", curtoken);
			break;
		case 28:
			printf("Token ID: %d\nToken Value: -\n\n", curtoken);
			break;
		case 31:
			printf("Token ID: %d\nToken Value: ,\n\n", curtoken);
			break;
		case 32:
			printf("Token ID: %d\nToken Value: ;\n\n", curtoken);
			break;
		case 33:
			printf("Token ID: %d\nToken Value: .\n\n", curtoken);
			break;
		case 34:
			printf("Token ID: %d\nToken Value: (\n\n", curtoken);
			break;
		case 35:
			printf("Token ID: %d\nToken Value: )\n\n", curtoken);
			break;
		case 38:
			printf("Token ID: %d\nToken Value: :\n\n", curtoken);
			break;
		case 40:
			printf("Token ID: %d\nToken Value: =\n\n", curtoken);
			break;
		case 42:
			printf("Token ID: %d\nToken Value: <\n\n", curtoken);
			break;
		case 47:
			printf("Token ID: %d\nToken Value: %d\n\n", curtoken, curvalue);
			break;
		case 49:
			printf("Token ID: %d\nToken Value: %f\n\n", curtoken, curfloat);
			break;
		case 50:
			printf("Token ID: %d\nToken Value: %s\n\n", curtoken, curstr);
			break;
		case 52:
			printf("Token ID: %d\nToken Value: var\n\n", curtoken);
			break;
		case 54:
			printf("Token ID: %d\nToken Value: const\n\n", curtoken);
			break;
		case 58:
			printf("Token ID: %d\nToken Value: %s\n\n", curtoken, curname);
			break;
		case 59:
			printf("Token ID: %d\nToken Value: Integer\n\n", curtoken);
			break;
		case 62:
			printf("Token ID: %d\nToken Value: Boolean\n\n", curtoken);
			break;
		case 79:
			printf("Token ID: %d\nToken Value: Program\n\n", curtoken);
			break;
		default:
			printf("Unknown token\n\n");
	}
}

//Done(?)
void G() {
	E();
	if(curtoken == TK_EOF) return;
	else error(); //error
}

int R() {
	int t1;
	int t2;
	t1 = E();
	while(curtoken == TK_EQ || curtoken == TK_NEQ || curtoken == TK_LESSER ||
		  curtoken == TK_GREATER || curtoken == TK_LEQ || curtoken == TK_GEQ){
			switch(curtoken){
				case TK_EQ:
					match(TK_EQ); t2=E(); do_EQ(t1, t2); t1 = TP_BOOL; break;
				case TK_NEQ:
					match(TK_EQ); t2=E(); do_NEQ(t1, t2); t1 = TP_BOOL; break;
				case TK_LESSER:
					match(TK_LESSER); t2=E(); do_LESSER(t1, t2); t1 = TP_BOOL; break;
				case TK_GREATER:
					match(TK_GREATER); t2=E(); do_GREATER(t1, t2); t1 = TP_BOOL; break;
				case TK_LEQ:
					match(TK_LEQ); t2=E(); do_LEQ(t1, t2); t1 = TP_BOOL; break;
				case TK_GEQ:
					match(TK_GEQ); t2=E(); do_GEQ(t1, t2); t1 = TP_BOOL; break;
				default:
					;
			}
	}
	return t1;
}

int E() {
	int t1;
	int t2;
	t1 = T();
	while(curtoken == TK_PLUS || curtoken == TK_MINUS || curtoken == TK_OR || curtoken == TK_XOR){
		switch(curtoken){
			case TK_PLUS:
				match(TK_PLUS); t2=T(); do_ADD(t1, t2); break;
			case TK_MINUS:
				match(TK_MINUS); t2=T(); do_SUB(t1, t2); break;
			case TK_OR:
				match(TK_OR); t2=T(); do_OR(t1, t2); break;
			case TK_XOR:
				match(TK_XOR); t2=T(); do_XOR(t1, t2); break;
			default:
				;
		}
	}
	return t1;
}

int T() {
	int t1;
	int t2;
	t1 = F();
	while(curtoken == TK_MULTIPLY || curtoken == TK_DIVIDE || curtoken == TK_AND){
		switch(curtoken){
			case TK_MULTIPLY:
				match(TK_MULTIPLY); t2 = T(); do_MUL(t1, t2); break;
			case TK_DIVIDE:
				match(TK_DIVIDE); t2 = T(); do_DIV(t1, t2); break;
			case TK_AND:
				match(TK_AND); t2 = T(); do_AND(t1, t2); break;
			default:
				;
		}
	}
	return t1;
}

int F() {
	int t1;
	if(curtoken == TK_UNKNOWN) {
		if(find_token(current_scope, curname)) curtoken = TK_A_VAR;
		else error();
	}
	while(curtoken == TK_PLUS || curtoken == TK_MINUS || curtoken == TK_LPAREN || curtoken == TK_INTLIT || curtoken == TK_NOT || curtoken == TK_A_VAR) {
		//int lo;
		//int hi;
		//int addr;
		//int index_type;
		//int component_type;
		struct Node *temp;
		int cur_level;
		switch(curtoken){
			case TK_PLUS:
				match(TK_PLUS); F(); do_NOP(t1); break;
			case TK_MINUS:
				match(TK_MINUS); F(); do_NEG(t1); break;
			case TK_NOT:
				match(TK_NOT); F(); do_NOT(t1); break;
			case TK_LPAREN:
				match(TK_LPAREN); E();
				gettoken();
				match(TK_RPAREN); break;
			case TK_INTLIT:
				match(TK_INTLIT); t1 = TP_INT; do_LIT(t1); break;
			case TK_A_VAR:
				if(scope_lookup(current_scope, curname)) {
					struct Node *val = get(current_scope, curname);
					temp = val;
					cur_level = current_scope->scope_level;
					t1 = val->data_type;
				}
				else if(scope_lookup(global_scope, curname)) {
					struct Node *val = get_node(global_scope->entries[hash_function(curname)], curname);
					temp = val;
					cur_level = global_scope->scope_level;
					t1 = val->data_type;
				}
				else error();
				gettoken();
			break;
		}
	}
	return t1;
}

void do_ADD(int t1, int t2) {

}

void do_SUB(int t1, int t2) {

}

void do_MUL(int t1, int t2) {

}

void do_DIV(int t1, int t2) {

}

void do_OR(int t1, int t2) {

}

void do_AND(int t1, int t2) {

}

void do_XOR(int t1, int t2) {

}

void do_NOP(int t1) {

}

void do_NEG(int t1) {

}

void do_NOT(int t1) {

}

void do_LIT(int t1) {
	printf("Literal of type %d with %d", t1, curvalue);
}

void do_EQ(int t1, int t2){

}

void do_NEQ(int t1, int t2) {

}

void do_LESSER(int t1, int t2){
	printf("Less than comparison of type %d with %d", t1, t2);
}

void do_GREATER(int t1, int t2){

}

void do_LEQ(int t1, int t2) {

}

void do_GEQ(int t1, int t2){

}

//Done
void error() {
	printf("\n\n\n Syntax Error!"); exit(-1);
}

//Done
void match(int t) {
	if(curtoken != t) error();
	else{
		printf("\n%c", curtoken);
		gettoken();
	}
}

//Done for now
void compile() {
	struct Node *array[H] = {NULL};
	struct Scope_Tree_Node new_scope = {NULL, 0, array, NULL};
	global_scope = &new_scope;
	current_scope = global_scope;
	header();
	declarations();
	begin_statement();
	match(TK_END);
	match(TK_PERIOD);
	emit_opcode(OP_HALT);
}

//Done for now
void header() {
	gettoken();
	match(TK_PROGRAM);
	insert(global_scope, curname, TK_PROGNAME, 1, 8, DP, 0);
	strcat((char*)DATA, curname);
	DP += 32;
	gettoken();
	match(TK_SEMICOLON);
}

//Done for now
void declarations() {
	while(curtoken == TK_LABEL || curtoken == TK_VAR || curtoken == TK_CONST
		  || curtoken == TK_TYPE || curtoken == TK_PROCEDURE || curtoken == TK_FUNCTION) {
		declaration();
	}
}

//Done for now
//Need Procedures and Functions
//Need to deal with ranges/subranges/arrays
void declaration() {
	restart:
	switch(curtoken){
		case TK_LABEL:
			label_declaration(); goto restart;
		case TK_VAR:
			var_declaration(); goto restart;
		case TK_CONST:
			const_declaration(); goto restart;
		case TK_TYPE:
			type_declaration(); goto restart;
		case TK_PROCEDURE:
			procedure_declaration(); goto restart;
		case TK_FUNCTION:
			function_declaration(); goto restart;
		default:
			;
	}
}

//Done for now
//Need TK_A_VAR
void var_declaration() {
	match(TK_VAR);
	restart:
	if(curtoken != TK_UNKNOWN) error();
	char token_list[32][32];
	int i = 0;
	int size = 0;

	do {
		if(curtoken == TK_COMMA) gettoken();
		if(scope_lookup(current_scope, curname)) error();
		else {
			if(curtoken != TK_UNKNOWN) error();
			strcpy(token_list[i], curname);
			i++;
			gettoken();
		}
	}while(curtoken == TK_COMMA);

	if(curtoken != TK_COLON) error();
	match(TK_COLON);
	int type;
	switch (curtoken) {
		case TK_CHAR:
			type = TP_CHAR;
			size = 1;
			break;
		case TK_INTEGER:
			type = TP_INT;
			size = 4;
			break;
		case TK_REAL:
			type = TP_REAL;
			size = 4;
			break;
		case TK_BOOLEAN:
			type = TP_BOOL;
			size = 1;
			break;
		case TK_STRING:
			type = TP_STR;
			size = 256;
			break;
		case TK_A_VAR:
			//enums
			printf("No enum support sorry.\n");
			exit(-1);
			/*
			struct Node *temp = get_node(current_scope.table.entries[hash_functio(curname)], curname);
			if(temp->data.data_type != TP_TYPE) error();
			else type = TP_TYPE;*/
			break;
		default:
			error();
			break;
	}
	gettoken();
	match(TK_SEMICOLON);
	int j = 0;
	while(j < i) {
		insert(current_scope, token_list[j], TK_A_VAR, 0, type, DP+size, 0);
		DP += size;
		j++;
	}
	if(curtoken == TK_UNKNOWN) goto restart;
}

//Done for now
//Can parse labels but may serve no purpose if gotos are skipped
void label_declaration() {
	match(TK_LABEL);
	if(curtoken != TK_UNKNOWN) error();
	char token_list[32][32];
	int i = 0;
	int size = 4;
	do {
		if(curtoken == TK_COMMA) gettoken();
		if(scope_lookup(current_scope, curname)) error();
		else {
			if(curtoken != TK_UNKNOWN) error();
			strcpy(token_list[i], curname);
			i++;
			gettoken();
		}
	}while(curtoken == TK_COMMA);
	match(TK_SEMICOLON);
	int j = 0;
	while(j < i) {
		//add actual parameters here and adjust symbol tables if doing goto
		insert(current_scope, token_list[j], TK_A_LABEL, 0, TP_LABEL, DP+size, 0);
		DP += size;
		j++;
	}
}

//Done for now
//Need TK A VAR
void const_declaration() {
	match(TK_CONST);
	restart:
	if(curtoken != TK_UNKNOWN) error();
	char token_list[32][32];
	int i = 0;
	int size = 0;

	do {
		if(curtoken == TK_COMMA) gettoken();
		if(scope_lookup(current_scope, curname)) error();
		else {
			if(curtoken != TK_UNKNOWN) error();
			strcpy(token_list[i], curname);
			i++;
			gettoken();
		}
	}while(curtoken == TK_COMMA);

	if(curtoken != TK_EQ) error();
	match(TK_EQ);
	int type;
	switch (curtoken) {
		case TK_INTLIT:
			type = TP_INT;
			size = 4;
			break;
		case TK_REALLIT:
			type = TP_REAL;
			size = 4;
			break;
		case TK_PLUS:
			type = F();
			size = 4;
			break;
		case TK_MINUS:
			type = F();
			size = 4;
			break;
		case TK_CHARLIT:
			type = TP_CHAR;
			size = 1;
			break;
		case TK_TRUE:
			type = TP_BOOL;
			size = 1;
			break;
		case TK_FALSE:
			type = TP_BOOL;
			size = 1;
			break;
		case TK_A_VAR:
			//get val from symbol table
			//must be of the types given above
			break;
		case TK_STRLIT:
			type = TP_STR;
			size = 256;
			break;
	}
	gettoken();
	match(TK_SEMICOLON);
	int j = 0;
	while(j < i) {
		insert(current_scope, token_list[j], TK_A_VAR, 0, type, DP+size, 1);
		DP += size;
		j++;
	}
	if(curtoken == TK_UNKNOWN) goto restart;
}

//Done for now
void type_declaration() {
	match(TK_TYPE);
	restart:
	if(curtoken != TK_UNKNOWN) error();
	char token_list[32][32];
	int i = 0;
	int size = 0;

	do {
		if(curtoken == TK_COMMA) gettoken();
		if(scope_lookup(current_scope, curname)) error();
		else {
			if(curtoken != TK_UNKNOWN) error();
			strcpy(token_list[i], curname);
			i++;
			gettoken();
		}
	}while(curtoken == TK_COMMA);

	if(curtoken != TK_EQ) error();
	match(TK_EQ);
	int type;
	switch (curtoken) {
		case TK_INTEGER:
		case TK_REAL:
		case TK_STRING:
		case TK_CHAR:
		case TK_BOOLEAN:
			size = 4;
			type = TP_TYPE;
			break;
		default:
			error();
	}
	gettoken();
	match(TK_SEMICOLON);
	int j = 0;
	while(j < i) {
		insert(current_scope, token_list[j], TK_A_VAR, 0, type, DP+size, 1);
		DP += size;
		j++;
	}
	if(curtoken == TK_UNKNOWN) goto restart;
}

//For later
void procedure_declaration() {

}

//For later
void function_declaration() {

}

//Optional for now
void begin_statement() {
	if(curtoken != TK_BEGIN) error();
	match(TK_BEGIN);
	statements();
}

//Done for now
//Need to check for TK unknowns to TK_A_Vars
void statements() {
	if(curtoken == TK_UNKNOWN) {
		if(find_token(current_scope, curname)) curtoken = TK_A_VAR;
		else error();
	}
	while(curtoken == TK_IF || curtoken == TK_WHILE || curtoken == TK_FOR
		  || curtoken == TK_REPEAT || curtoken == TK_A_VAR || curtoken == TK_A_LABEL ||
		  curtoken == TK_WRITE || curtoken == TK_UNKNOWN) {
		statement();
	}
}

void statement() {
	restart:
	switch(curtoken) {
		case TK_IF:
			if_statement(); goto restart;
		case TK_WHILE:
			while_statement(); goto restart;
		//goto not implemented probably
		//case TK_GOTO:
			//goto_statement(); goto restart;
		case TK_FOR:
			for_statement(); goto restart;
		case TK_REPEAT:
			repeat_statement(); goto restart;
		case TK_A_VAR:
			assignment(); goto restart;
		case TK_A_LABEL:
			//process_a_label();
			goto restart;
		case TK_WRITE:
			write_statement(); goto restart;
		default:
			return;
	}
}

//Done for now
//only supports single argument write
void write_statement() {
	match(TK_WRITE);
	match(TK_LPAREN);
	int t = E();
	match(TK_RPAREN);
	switch(t) {
		case TP_INT:
			emit_opcode(OP_PRINTINT);
			break;
		case TP_CHAR:
			emit_opcode(OP_PRINTCHAR);
			break;
		case TP_STR:
			emit_opcode(OP_PRINTSTR);
			break;
		case TP_BOOL:
			emit_opcode(OP_PRINTBOOL);
			break;
		case TP_REAL:
			emit_opcode(OP_PRINTREAL);
			break;
		default:
			error();
	}
}

//Done for now
void repeat_statement() {
	match(TK_REPEAT);
	int target = IP;
	statements();
	gettoken();
	match(TK_UNTIL);
	condition();
	match(TK_SEMICOLON);
	emit_opcode(OP_JFALSE);
	emit_int(target);
}

//Done for now
void while_statement() {
	match(TK_WHILE);
	int target = IP;
	condition();
	emit_opcode(OP_JFALSE);
	int hole = IP;
	emit_int(0);
	match(TK_DO);
	statement();
	emit_opcode(OP_JMP);
	emit_int(target);
	int save_IP = IP;
	IP = hole;
	emit_int(save_IP);
	IP = save_IP;
}

//Done for now
void if_statement() {
	match(TK_IF);
	condition();
	emit_opcode(OP_JFALSE);
	int hole = IP;
	emit_int(0);
	match(TK_THEN);
	statement();

	int hole_2;
	int save_IP;
	switch(curtoken) {
		case TK_ELSE:
			hole_2 = IP;
			emit_opcode(OP_JMP);
			emit_int(0);
			save_IP = IP;
			IP = hole;
			emit_int(save_IP);
			IP = save_IP;
			statement();
			int save_IP_2 = IP;
			IP = hole_2;
			emit_int(save_IP_2);
			IP = save_IP_2;
			match(TK_SEMICOLON);
			break;
		case TK_SEMICOLON:
			save_IP = IP;
			IP = hole;
			emit_int(save_IP);
			IP = save_IP;
			break;
	}
}

//Done(?)
void condition() {
	if(R() != TP_BOOL) error();
}

int find_token() {
	return lookup(current_scope, curname);
}

void for_statement() {

}

//Variable assignment done for now
void assignment() {
	struct Node *temp;
	int cur_level;

	if(scope_lookup(current_scope, curname)) {
		struct Node *val = get(current_scope, curname);
		temp = val;
		cur_level = current_scope->scope_level;
	}
	else if(scope_lookup(global_scope, curname)) {
		struct Node *val = get_node(global_scope->entries[hash_function(curname)], curname);
		temp = val;
		cur_level = global_scope->scope_level;
	}
	else error();

	int tLHS = temp->data_type;
	gettoken();
	match(TK_ASSIGN);
	int tRHS = E();
	switch(tLHS) {
		case TP_INT:
			//truncates values after the decimal point
			if(tRHS == TP_REAL) {
				DATA[temp->address] = (int)curfloat;
			}
			else if(tRHS == TP_BOOL || tRHS == TP_INT) {
				DATA[temp->address] = curvalue;
			}
			else error();
			break;
		case TP_BOOL:
			if(tRHS == TP_REAL || tRHS == TP_INT || tRHS == TP_BOOL) {
				if (curfloat > 0)
					DATA[temp->address] = 1;
				else
					DATA[temp->address] = 0;
			}
			else error();
			break;
		case TP_CHAR:
			if(tRHS == TP_CHAR || tRHS == TP_INT) {
				DATA[temp->address] = (char)curvalue;
			}
			else error();
			break;
		case TP_STR:
			if(tRHS == TP_STR) {
				DATA[temp->address] = curstr;
			}
			else error();
			break;
		case TP_REAL:
			if(tRHS == TP_BOOL || tRHS == TP_INT) {
				DATA[temp->address] = (float)curvalue;
			}
			else if(tRHS == TP_REAL) {
				DATA[temp->address] = curfloat;
			}
			else error();
			break;
	}
	/*
	//set_data(var, curname, tRHS);

	//if array
	int lo; //from symbol table
	int hi; //from symbol table
	int addr; //from symbol table
	int index_type; //from symbol table
	int component_type; //from symbol table

	match(TK_LB);
	int t = E();
	if(t!=index_type)
		error();

	if(lo != 0) {
		emit_opcode(OP_PUSHI);
		emit_int(lo);
		emit_opcode(OP_SUB);
	}

	if(size(component_type) != 1) {
		emit_opcode(OP_PUSHI);
		emit_int(size(component_type));
		emit_opcode(OP_MUL);
	}

	emit_opcode(OP_PUSHI);
	emit_int(addr);
	emit_opcode(OP_ADD);

	match(TK_RB);
	match(TK_ASSIGN);

	t = E();

	if(t != component_type)
		error();

	emit_opcode(OP_PUT);
	*/
}


void case_statement() {
	match(TK_CASE);
	int tE=E();
	match(TK_OF);
	match(TK_END);
}

void emit_opcode(int code) {
	switch(code){
		case OP_HALT:
			printf("Program terminated normally. Exit code 0.\n");
			break;
		default:
			printf("Other.\n");
			break;
	}
}

void emit_int(int val) {

}

int size(int val) {
	return 0;
}

/*
void E() {
	T();
	while(curtoken == TK_PLUS || curtoken == TK_MINUS || curtoken == TK_OR || curtoken == TK_XOR){
		switch(curtoken){
			case TK_PLUS:
				match(TK_PLUS); T(); action(ADD); break;
			case TK_MINUS:
				match(TK_MINUS); T(); action(SUB); break;
			case TK_OR:
				match(TK_OR); T(); action(OR); break;
			case TK_XOR:
				match(TK_XOR); T(); action(XOR); break;
			default:
				;
		}
	}
}

void T() {
	F();
	while(curtoken == TK_MULTIPLY || curtoken == TK_DIVIDE || curtoken == TK_AND){
		switch(curtoken){
			case TK_MULTIPLY:
				match(TK_MULTIPLY); T(); action(MUL); break;
			case TK_DIVIDE:
				match(TK_DIVIDE); T(); action(DIV); break;
			case TK_AND:
				match(TK_AND); T(); action(AND); break;
			default:
				;
		}
	}
}

void F() {
	while(curtoken == TK_PLUS || curtoken == TK_MINUS || curtoken == TK_LPAREN || curtoken == TK_INTLIT || curtoken == TK_NOT) {
		switch(curtoken){
			case TK_PLUS:
				match(TK_PLUS); F(); action(NOP); break;
			case TK_MINUS:
				match(TK_MINUS); F(); action(NEG); break;
			case TK_NOT:
				match(TK_NOT); F(); action(NOT); break;
			case TK_LPAREN:
				match(TK_LPAREN); E();
				gettoken();
				match(TK_RPAREN); break;
			case TK_INTLIT:
				match(TK_INTLIT); action(LIT);
			case TK_A_VAR:
				int lo;
				int hi;
				int addr;
				TYPE index_type;
				TYPE component_type;

				match(TK_LB);
				TYPE t = E();
				if (t != index_type)
					error();

				if(lo != 0) {
					emit_opcode(OP_PUSHI);
					emit_int(lo);
					emit_opcode(OP_SUB);
				}

				if(size(component_type) != 1) {
					emit_opcode(OP_PUSHI);
					emit_int(size(component_type));
					emit_opcode(OP_MUL);
				}

				emit_opcode(OP_PUSHI);
				emit_int(addr);
				emit_opcode(OP_ADD);

				emit_opcode(OP_GET);

				return component_type;
		}
	}
}


void process_a_label() {
	if(seen) error(); else seen = true;
	addr = IP;
	//save scope information
}

void goto_statement() {
	match(TK_GOTO);
	if(curtoken != TK_A_LABEL) error();
	//generate dummy jump
	//append location of a dummy jump.
	//source ref, and
	//scope information to goto list
	//in the symbol table
	gettoken();
}

void resolve_gotos() {
	for(all labels in local symbol table) {
		if(gotolist != NULL %% !seen) error();
		for(all entires in gotolist) patch;
	}
}
*/
