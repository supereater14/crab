/******************************************
Author: Riley Mulford
CS3141 Team Software
2/8/2017
Dynamic String Library Implementation
******************************************/

#include "crabstr.h"

void setstr(string *s, char* c)
{
	s->s = c;
	s->size = strlen(c);
	return;
}

/* 	Returns the size of a crab string */
size_t strsize(string *s)
{
	if(isNaS(s))
	{
		return 0;
	}
	return s->size;
}

/* 	Allocates memory for a crab string */
string strmalloc(size_t size)
{
	if(size < 16)
	{
		size = 16;
	}
	return (string) {malloc(size), 0, size | STR_FREEABLE};
}

/* 	Reallocate memory for a crab string */
void strrealloc(string *s)
{
	char *b; /* temp buffer */

	/* check if it is a valid string */
	if(isNaS(s))
	{
		return;
	}

	/* check to see if realloc is possible */
	if(!(s->buf_size & STR_FREEABLE))
	{
		return;
	}

	/* make sure memory is allocated for string */
	if(!s->size)
	{
		free(s->s);
		s->s = malloc(16);
	}
	else
	{
		b = realloc(s->s, s->size);
		if(b)
		{
			s->s = b;
		}
	}
}

/* 	Resize a crab string */
void strresize(string *s, size_t size)
{
	char *b;
	size_t bsize;
	
	if (isNaS(s)) return;
	
	/* Not resizable */
	if (!(s->buf_size & STR_FREEABLE))
	{
		string s2;
		
		if (size <= s->size) return;
		
		s2 = strmalloc(size);
		
		/* Copy into new string */
		memcpy(s2.s, s->s, s->size);
		
		/* Point to new string */
		s->s = s2.s;
		s->buf_size = s2.buf_size;
		
		return;
	}
	
	/* string will be too large after resize */
	if (size & STR_FREEABLE)
	{
		free(s->s);
		*s = NaS;
		return;
	}
	
	bsize = s->buf_size - STR_FREEABLE;
	
	/* Keep at least 16 bytes */
	if (size < 16) size = 16;
	
	/* string does not need to be resized */
	if ((4 * size > 3 * bsize) && (size <= bsize)) return;
	
	/* double buffer size */
	if ((size > bsize) && (size < bsize * 2)) size = bsize * 2;
	
	/* Keep at least 16 bytes */
	if (size < 16) size = 16;

	b = realloc(s->s, size);
	
	/* if failure, not a string */
	if (!b)
	{
		free(s->s);
		*s = NaS;
	}
	else
	{
		s->s = b;
		s->buf_size = size | STR_FREEABLE;
	}
}

/* Free memory for a crab string */
void strfree(string *s)
{
	if (s->buf_size & STR_FREEABLE) free(s->s);
	
	*s = NaS;
}

/* 	Converts a C-style string to a crab string */
string strcstr_aux(char *c, size_t len)
{
	return (string) {c, len, len + 1};
}

/* Converts a C-style string to a crab string */
string strcstr(char *c)
{
	size_t len = strlen(c);
	return strcstr_aux(c, len);
}

/* 	Create a new string as a copy of an old one */
string strdupstr(string *s)
{
	string s2;
	
	if (isNaS(s)) return NaS;
	
	s2 = strmalloc(s->size);
	s2.size = s->size;
	memcpy(s2.s, s->s, s->size);
	
	return s2;
}

/* 	Copy the memory from the source string into the dest string */
void strcpystr(string *dest, string *src)
{
	if (isNaS(src)) return;
	
	strresize(dest, src->size);
	
	if (isNaS(dest)) return;
	dest->size = src->size;
	memcpy(dest->s, src->s, src->size);
}

/* 	Convert a crab string into a C-style character array */
char *strtocstr(string *s)
{
	size_t bsize;
	
	if (isNaS(s)) return NULL;
	
	/* Get real buffer size */
	bsize = s->buf_size & ~STR_FREEABLE;
	
	if (s->size == bsize)
	{
		/* Increase buffer size */
		strresize(s, bsize + 1);
		
		if (isNaS(s)) return NULL;
	}
	
	/* Add null byte to the end */
	s->s[s->size] = 0;
	
	/* the buffer can be reused as long as nothing else is appended */
	return s->s;
}

/* 	Concatenate C-style string to a crab string */
 void strncatcstr(string *s, size_t len, const char *str)
{
	size_t bsize;
	
	if (isNaS(s)) return;
	
	/* Nothing to do? */
	if (!str || !len) return;
	
	/* Get real buffer size */
	bsize = s->buf_size & ~STR_FREEABLE;
	
	if (s->size + len >= bsize)
	{
		strresize(s, s->size + len);
		
		if (isNaS(s)) return;
	}
	
	memcpy(&s->s[s->size], str, len);
	s->size += len;
}

/* 	Concatenate C-style string to a crab string */
 void strcatcstr(string *s, const char *str)
{
	if (str) strncatcstr(s, strlen(str), str);
}

/* 	Concatenate crab string to another crab string */
 void strcatstr(string *s, const string *s2)
{
	strncatcstr(s, s2->size, s2->s);
}

/* 	Concatenate variable number of C-style strings to another crab string */
 void strcatcstrs(string *s, ...)
{
	const char *str;
	va_list v;
	
	if (isNaS(s)) return;
	
	va_start(v, s);
	
	for (str = va_arg(v, const char *); str; str = va_arg(v, const char *))
	{
		strncatcstr(s, strlen(str), str);
	}
	
	va_end(v);
}

/* 	Concatenate variable number of crab strings to another crab string */
 void strcatstrs(string *s1, ...)
{
	const string *s2;
	va_list v;
	
	if (isNaS(s1)) return;
	
	va_start(v, s1);
	
	for (s2 = va_arg(v, const string *); s2; s2 = va_arg(v, const string *))
	{
		strncatcstr(s1, s2->size, s2->s);
	}
	
	va_end(v);
}

/* a crab string version of sprintf() */
 void strprintf(string *s, const char *fmt, ...)
{
	va_list v;
	size_t len;
	
	if (isNaS(s)) *s = STRINIT;
	
	if (!fmt) return;
	
	va_start(v, fmt);
	len = vsnprintf(NULL, 0, fmt, v) + 1;
	va_end(v);
	
	strresize(s, len);
		
	if (isNaS(s)) return;

	va_start(v, fmt);
	vsnprintf(s->s, len, fmt, v);
	va_end(v);
	s->size = len - 1;
}