/*
 *	interface f12: a collection of C functions.
 *	manually translated into plain C, using libdl
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <dlfcn.h>

#include "f12.h"
#include "lookup.h"


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
f12 *f12_bind( char *module, char *errmsg )
{
	char libname[1024];
	sprintf( libname, "lib%s.so", module );
	void *dl = dlopen( libname, RTLD_NOW );
	if( dl == NULL )
	{
		sprintf( errmsg, "f12_bind: dlopen of %s failed", libname );
		return NULL;
	}

	f12 *in = malloc(sizeof(*in));
	if( in == NULL )
	{
		strcpy( errmsg, "f12_bind: malloc() failed" );
		return NULL;
	}

	pkg_info   info;
	info.dl        = dl;
	info.module    = module;
	info.libname   = libname;
	info.errmsg    = errmsg;

	in->f1 = (f12_void_void_f) lookup_function( &info, "f1" );
	if( in->f1 == NULL )
	{
		free(in);
		return NULL;
	}

	in->f2 = (f12_int_void_f) lookup_function( &info, "f2" );
	if( in->f2 == NULL )
	{
		free(in);
		return NULL;
	}

	return in;
}
