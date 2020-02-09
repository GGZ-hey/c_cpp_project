#pragma once
#ifndef _symtab_h
#define _symtab_h

#include"genlib.h"

typedef struct symtabCDT  *symtabADT;

typedef void(*symtabFnT)(string key, void *value, void *clientData);

symtabADT NewSymbolTable(void);//新符号表
void FreeSymbolTable(symtabADT table);

void Enter(symtabADT table, string key, void *value);
void *Lookup(symtabADT table, string key);

void MapSymbolTable(symtabFnT fn, symtabADT table, void *clientData);//遍历符号表

#endif // !_symtab_h
