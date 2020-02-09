#include"symtab.h"
#include<stdio.h>
#include"bst.h"
#include<string.h>


struct symtabCDT {
	bstADT bst;
};

static string CreateString(int len)
{
	return ((string)GetBlock(len + 1));
}

string CopyString(string s);
string CopyString(string s)
{
	string newstr;

	if (s == NULL) Error("NULL string passed to CopyString");
	newstr = CreateString(strlen(s));
	strcpy_s(newstr,1000, s);
	return (newstr);
}

#define UNDEFINED ((void *) undefined_object)
extern char undefined_object[];

typedef struct {
	string key;
	void *value;
}symtabNodeT;

//私人函数
cmpFnT StringCmpFn(const void *p1, const void *p2) {
	return(int)(strcmp(*(string *)p1, *((string *)p2)));
}

nodeInitFnT symInit(void *np, void *kp, void *clientData) {

	((symtabNodeT *)np)->key = CopyString(*((string *)kp));
}

nodeFnT freeStringNode(void *np, void *clientData) {
	free(((symtabNodeT *)np)->key);
	free(((symtabNodeT *)np)->value);
}
 //树实现符号表
symtabADT NewSymbolTable(void) {
	symtabADT table;
	table = (symtabADT)malloc(sizeof(struct symtabCDT));
	table->bst = NewBst(sizeof(symtabNodeT), StringCmpFn, symInit);
	return(table);
}

void FreeSymbolTable(symtabADT table)
{
	FreeBst(table->bst, freeStringNode);
}


void Enter(symtabADT table, string key, void *value) {
	symtabNodeT *np;
	np = InsertBSTNode(table->bst, &key, NULL);
	np->value = value;
	
}

void * Lookup(symtabADT table, string key)
{
	symtabNodeT *np;
	np = FindBSTNode(table->bst, &key);
	if (np == NULL)
		return(UNDEFINED);
	return(np->value);
}

nodeFnT fn2(void *np, void *clientData) {
	symtabNodeT *np2;
	np2 = np;
	symtabFnT fn;
	fn = clientData;
	fn(np2->key, np2->value, NULL);
}

void MapSymbolTable(symtabFnT fn, symtabADT table, void *clientData) {
	MapBst(fn2, table->bst, PreOrder, fn);
	MapBst(fn2, table->bst, PostOrder, fn);
	MapBst(fn2, table->bst, InOrder, fn);
}
