#ifndef symbol_table_h
#define symbol_table_h

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "macros.h"

#define H 256

struct Node{
	char symbol_name[32];
	int token_type;
	int is_static;
	int data_type;
	int address;
	int flags;
	int index_type;
	int low;
	int high;
	int component_type;
	struct Node *next;
};

void insert_node(struct Node **h, char* s_n, int t_t, int i_s, int d_t, int a, int f){
	struct Node *s1 = malloc( sizeof( struct Node ) );
    int success = s1 != NULL;

    if ( success )
    {
    	strcpy(s1->symbol_name, s_n);
    	s1->token_type = t_t;
    	s1->is_static = i_s;
    	s1->data_type = d_t;
    	s1->address = a;
    	s1->flags = f;
    	s1->index_type = -1;
    	s1->low = -1;
    	s1->high = -1;
    	s1->component_type = -1;
    	s1->next = *h;
    	*h = s1;
    }
}

int delete_note(struct Node *h, char *n){
	struct Node *temp = h;
	struct Node *prev = NULL;
	if(h != NULL){
		while(temp != NULL && n != temp->symbol_name) {
			prev = temp;
			temp = temp->next;
		}
		if(temp != NULL){
			prev->next = temp->next;
			temp->next = NULL;
			free(temp);
			return 1;
		}
		else return 0;
	}
	else return 0;
}

int in_list(struct Node *h, char *n){
	struct Node *temp = h;
	if(h != NULL){
		while(temp->next != NULL && n != temp->symbol_name) temp = temp->next;
		if(temp != NULL) return 1;
		else return 0;
	}
	else return 0;
}

struct Node *get_node(struct Node *h, char *n) {
	struct Node *temp = h;
	if(h != NULL){
		while(temp != NULL && strcmp(n, temp->symbol_name)) temp = temp->next;
		return temp;
	}
	else return NULL;
}


int get_type(struct Node *h, char *n) {
	return h->data_type;
}

struct Hash_Table{
	int scope_level;
	struct Node *entries[H];
};

int hash_function(char *n){
	int len = strlen(n);
	return (n[0] + n[len - 1] + n[len/2]) % H;
}

struct Scope_Tree_Node{
	struct Scope_Tree_Node *parent;
	//struct Hash_Table table;
	int scope_level;
	struct Node *entries[H];
	struct Scope_Tree_Node *next;
};

struct Scope_Tree_Node *enter_scope(struct Scope_Tree_Node *h) {
	//struct Hash_Table new_table;
	//new_table.scope_level = h->scope_level + 1;
	struct Node *(*new_entries)[H] = {NULL};
	struct Scope_Tree_Node n_scope = {h, h->scope_level + 1, new_entries, NULL};
	struct Scope_Tree_Node *new_scope = &n_scope;
	return new_scope;
}

struct Scope_Tree_Node *exit_scope(struct Scope_Tree_Node *h) {
	struct Scope_Tree_Node *new_scope = h->parent;
	new_scope->next = NULL;
	free(h);
	return new_scope;
}

int lookup(struct Scope_Tree_Node *h, char *n) {
	int key = hash_function(n);
	if(in_list(h->entries[key], n)) return 1;
	else
		if(h->parent == NULL) return 0;
		else return lookup(h->parent, n);
}

int scope_lookup(struct Scope_Tree_Node *h, char *n) {
	int key = hash_function(n);
	return in_list(h->entries[key], n);
}

void insert(struct Scope_Tree_Node *h, char *n, int t_t, int i_s, int d_t, int a, int f){
	int key = hash_function(n);
	if(in_list(h->entries[key], n)) {
		printf("Error. Variable already defined.");
		exit(-1);
	}
	else insert_node(&h->entries[key], n, t_t, i_s, d_t, a, f);
}

struct Node *get(struct Scope_Tree_Node *h, char *n){
	int key = hash_function(n);
	return get_node(h->entries[key], n);
}

#endif
