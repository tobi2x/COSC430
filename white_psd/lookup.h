// pkg_info: information record about what we're binding to/from..
typedef struct
{
	void *dl;		// result of dlopen on libname
	char *module;		// name of the module we're binding to
	char *errmsg;		// pointer to space for error message
	char *libname;		// name of the library we're binding to
} pkg_info;

//
// void *p = lookup_function( pkg_info *info, char *funcname );
//	look within info->dl, a dynamic library opened by dlopen(), for
//	either the global symbol <funcname> or the global symbol
//	<modulename_funcname>.
//	If we find either, return a pointer to the first one we found.
//	If not, return NULL.
//
extern void *lookup_function( pkg_info *info, char *funcname );
