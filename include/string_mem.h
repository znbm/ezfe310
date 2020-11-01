#pragma once

// Apparently, it's impossible to prevent GCC from emitting calls to the
// "mem" family of functions, so we get to implement part of `string.h`.
// None of these are optimized (or well tested), so let's hope it doesn't.
// At some point, we'll implement more of the standard library.

void * memset( void * dest, int b, uint n )
{
	byte * d = (byte *)( dest );
	for ( uint i = 0; i < n; i++ ) d[ i ] = (byte)( b & 0xFF );
	return dest;
}

int memcmp( const void * v1, const void * v2, uint n )
{
	const byte * b1 = v1; 
	const byte * b2 = v2;
	for ( ; n > 0; n--, b1++, b2++ ) if ( *b1 != *b2 ) return *b1 - *b2;
	return 0;
}

void * memcpy( void * dest, const void * src, uint n )
{
	const byte * s = src;
	byte * d = dest;

	for ( ; n > 0; n--, d++, s++ ) *d = *s;

	return dest;
}

void * memmove( void * dest, const void * src, uint n )
{
	const byte * s = src;
	byte * d = dest;

	if ( s < d && s + n > d ) // overlapping?
	{
		s += n; d += n;
		for ( ; n > 0; n-- ) 
		{
			d--; s--;
			*d = *s;
		}
		return dest;
	}
	else return memcpy( dest, src, n );
}

uint strlen( char * s )
{
	uint len = 0;
	for ( ; s[ len ] != '\0'; len++ );
	return len;
}

