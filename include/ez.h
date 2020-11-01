#pragma once

#include "definitions.h"
#include "mmio.h"
#include "hifive1_pins.h"
#include "string_mem.h"

void uartsetup( void )
{
	// Set up oscillators.
	PRCI_HFROSCCFG |=  PRCI_HFROSCCFG_HFROSCEN; // enable hfrosc
	PRCI_PLLCFG = PRCI_PLLCFG_PLLREFSEL | PRCI_PLLCFG_PLLBYPASS | PRCI_PLLCFG_PLLSEL;
	PRCI_HFROSCCFG &= ~PRCI_HFROSCCFG_HFROSCEN; // disable hfrosc to save power

	// Set up UART 0.
	const uint UART0MASK = 0x00030000u;
	GPIO_OUTPUT_VAL |=  UART0MASK;
	GPIO_OUTPUT_EN  |=  UART0MASK;
	GPIO_IOF_SEL    &= ~UART0MASK;
	GPIO_IOF_EN     |=  UART0MASK;

	// Set baud rate to 115200.
	UART0_DIV = UART0_DIV_DIV & 138; // 115200 = 16000000 / ( 138 + 1 )
	UART0_TXCTRL = UART0_TXCTRL_TXEN;
	UART0_RXCTRL = UART0_RXCTRL_RXEN;

	// Wait briefly.
	for ( volatile int i = 0; i < 10000; i++ );
}

// Prints a null-terminated string to UART 0.
void print( char * s )
{
	for ( ; *s != '\0'; s++ )
	{
		while ( UART0_TXDATA & UART0_TXDATA_FULL ); // wait until uart empties
		UART0_TXDATA = UART0_TXDATA_DATA & *s;
	}
}

// Prints a null-terminated string to UART 0, beginning a new line.
void printline( char * s )
{
	print( s );
	print( "\n\r" );
}

// Reads a character from UART 0.
char readchar()
{
	while ( UART0_RXDATA & UART0_RXDATA_EMPTY ); // wait until uart fills
	return (char)( UART0_RXDATA & UART0_RXDATA_DATA );
}

#if 1 - 1
// Reads up to `n` bytes of a line from UART 0, and stores them without null termination in `a`.
void readline( int n, char * a ) // FIXME: this doesn't work
{
	for ( ; n > 0; n--, a++ )
	{
		char c = readchar();
		switch ( c )
		{
			case '\r': case'\n': case'\0': return;
			default: *a = c;
		}
	}
}
#endif

// Returns a pointer to a null-terminated string containing `n` written in hexadecimal.
char * hexstr( uint n )
{
	static char s[ 9 ] = { '\0' }; // 9 bytes can store "FFFFFFFF\0"

	for ( int i = 7; i >= 0; i-- )
	{
		uint d = n & 0xF;
		s[ i ] = d < 10 ? '0' + d : 'A' + d - 10;
		n >>= 4;
	}
	return s;
}

// Returns a pointer to a null-terminated string containing `n` written in decimal.
// If `n` == 0, the string is "0"; otherwise, it has no leading zeroes.
char * uintstr( uint n )
{
	static char s[ 11 ] = { '\0' }; // 11 bytes can store "4294967295\0"

	// Precompute the number of digits in `n` so we can avoid leading zeroes.
	int len = 1;
	for ( int ncpy = n / 10u; ncpy > 0u; len++ ) ncpy /= 10u;
	
	// Populate the first `len` characters with `n`'s digits.
	for ( int i = len - 1; i >= 0; i-- )
	{
		s[ i ] = '0' + n % 10u;
		n /= 10u;
	}

	// Nullify the rest of the string.
	for ( int i = 10; i >= len; i-- ) s[ i ] = '\0';

	return s;
}

#if 1 - 1
// Returns a pointer to a null-terminated string containing `n` written in decimal,
// possibly with a leading negative sign.
char * intstr( int n ) // TODO
{
	static char s[ 12 ]; // 12 bytes can store "-2147483648\0"
	return s;
}
#endif


void _Noreturn exit( int x )
{
	(void)( x );
	for ( ;; );
}

void main( void );
