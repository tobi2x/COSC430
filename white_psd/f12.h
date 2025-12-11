// void_void_f: a pointer to a void->void function
typedef void (*f12_void_void_f)( void );

// int_void_f: a pointer to a void->int function
typedef int (*f12_int_void_f)( void );

// This represents the "interface f12" at run-time.
// It's a container of SLOTS for the f12 functions..
typedef struct
{
	f12_void_void_f   f1;
	f12_int_void_f    f2;
} f12;

/*
 * f12 *in = f12_bind( char *module, char *errmsg );
 *	Attempt to "bind" lib<module>.so to the f12 interface:
 *	Load "lib<module>.so" into memory, and attempt to locate the
 *	required symbols f1 and f2 (or <module>_f1 and <module>_f2...)
 *	within it's namespace.  For now, we just check for existence
 *	of those function symbols, later on we'll try to check the
 *	compatibility of the function signatures with the interface.
 *
 *	If we fail: strcpy an error message into errmsg and return NULL
 *	If we succeed: return an newly malloc()d f12 object with the
 *	slot function pointers bound to the corresponding functions in
 *	lib<module>.so (now in memory)
 */
extern f12 *f12_bind( char * module, char * errmsg );
