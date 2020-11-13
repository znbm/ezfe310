#ifndef DEBUG
#	ifdef NDEBUG
#		define assert( e ) ((void)( 0 ))
#	else
#		define assert( e ) ((e) ?\
		(void)( 0 ) :\
		assertfunc( __FILE__, __LINE__, __func__, #e ) )
#	endif
#endif

void _Noreturn assertfunc( const char * file, const uint line, const char * func, const char * expr )
{
	if ( uart_enabled )
	{
		print( "assertion failed at line " );
		print( uintstr( line ) );
		print( " of file " );
		print( file );
		print( " in function " );
		print( func );
		print( ": " );
		printline( expr );
	}

	exit( 1 );
}
