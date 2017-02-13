/******************************************
Author: Riley Mulford
CS3141 Team Software
2/8/2017
Dynamic String Library Implementation
******************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

/* if string cannot be defined, the string will become NaS (not a string) */
#define NaS ((string) {NULL, 0, 0})
#define isNaS(S) (!(S)->s)

/* string buffer size: 2^63-1 */
#define STR_FREEABLE (1ULL << 63)

/* init empty struct string */
#define STRINIT ((string) {malloc(16), 0, (16)})

/* Allocate room for a struct string on the stack */
#define stralloca(S) ((string) {alloca(S), 0, (S)})

/* Crab string structure definition */
typedef struct string string;
struct string
{
	char *s;
	size_t size; /* length of string */
	size_t buf_size; /* size of buffer containing string */
};

extern size_t strsize(string *s);
extern string strmalloc(size_t size);
extern void strrealloc(string *s);
extern void strresize(string *s, size_t size);
extern void strfree(string *s);
extern string strcstr_aux(char *c, size_t len);
extern string strcstr(char *c);
extern string strdupstr(string *s);
extern void strcpystr(string *dest, string *src);
extern char *strtocstr(string *s);
extern void strncatcstr(string *s, size_t len, const char *str);
extern void strcatcstr(string *s, const char *str);
extern void strcatstr(string *s, const string *s2);
extern void strcatcstrs(string *s, ...);
extern void strcatstrs(string *s1, ...);
extern void strprintf(string *s, const char *fmt, ...);
extern void setstr(string *s, char* c);