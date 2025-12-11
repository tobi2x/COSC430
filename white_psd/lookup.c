/*
 *	lookup: helper to search for a function symbol in a dl
 */

#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

#include "lookup.h"


//
// void *p = lookup_function( pkg_info *info, char *funcname );
//	look within info->dl, a dynamic library opened by dlopen(), for
//	either the global symbol <funcname> or the global symbol
//	<modulename_funcname>.
//	If we find either, return a pointer to the first one we found.
//	If not, return NULL.
//
void *lookup_function( pkg_info *info, char *funcname )
{
	// can we look up the symbol funcname inside the dl?
	void *p = dlsym( info->dl, funcname );
	if( p != NULL )
	{
		return p;
	}

	// can we look up the module-qualified symbol inside the dl?
	char fullname[1024];
	sprintf( fullname, "%s_%s", info->module, funcname );
	p = dlsym( info->dl, fullname );
	if( p != NULL )
	{
		return p;
	}

	sprintf( info->errmsg,
		"No symbol '%s' or '%s' in %s",
		funcname, fullname, info->libname );

	return NULL;
}
