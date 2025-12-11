/*
 *	pkg3: a third collection of C functions, that may accidentally satisfy
 *	      one or more interfaces that don't yet exist..
 */

#include <stdio.h>
#include <stdlib.h>

void f1( void )
{
	printf( "pkg3::f1\n" );
}

void *f4( int n )
{
	printf( "pkg3::f4, x=%d, returning malloc(n)\n", n );
	return malloc(n);
}
