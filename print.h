#define _GNU_SOURCE

#ifndef PRINT_H
#define PRINT_H


#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#define REG_SIZE (10000)

extern char specifiers[];
extern int spec_amt;
extern char *(*function_registry[])(void *);


void register_fmt(char type, char *(*func)(void *));
void print(const char *fmt, ...);

#endif