int __attribute((optimize("no-optimize-sibling-calls"))) recursive( int n )
{
	if ( n >= 10 ) return 10;
	else return recursive( n + 1 );
}

#define DEBUG

void main( void )
{
	uartsetup();

	// Test the stack we set up with a recursive function.
	assert( recursive( 0 ) == 10 );

	// Test `hexstr`.
	assert( strsame( hexstr( 0x00000000U ), "00000000" ) );
	assert( strsame( hexstr( 0x00000001U ), "00000001" ) );
	assert( strsame( hexstr( 0x1234ABCDU ), "1234ABCD" ) );
	assert( strsame( hexstr( 0xDEADBEEFU ), "DEADBEEF" ) );
	assert( strsame( hexstr( 0xFFFFFFFEU ), "FFFFFFFE" ) );
	assert( strsame( hexstr( 0xFFFFFFFFU ), "FFFFFFFF" ) );

	// Test `uintstr`.
	assert( strsame( uintstr( 0U ), "0" ) );
	assert( strsame( uintstr( 1U ), "1" ) );
	assert( strsame( uintstr( 123456789U ), "123456789" ) );
	assert( strsame( uintstr( 4294967294U ), "4294967294" ) );
	assert( strsame( uintstr( 4294967295U ), "4294967295" ) );

	// Test `intstr`.
	assert( strsame( intstr( -2147483647 - 1 ), "-2147483648" ) );
	assert( strsame( intstr( -2147483647 ), "-2147483647" ) );
	assert( strsame( intstr( -123456789 ), "-123456789" ) );
	assert( strsame( intstr( -1 ), "-1" ) );
	assert( strsame( intstr( 0 ), "0" ) );
	assert( strsame( intstr( 1 ), "1" ) );
	assert( strsame( intstr( 123456789 ), "123456789" ) );
	assert( strsame( intstr( 2147483646 ), "2147483646" ) );
	assert( strsame( intstr( 2147483647 ), "2147483647" ) );

#define INT_MAX		2147483647
#define INT_MIN		(-INT_MAX - 1)

	// Recreate the HiFive1 LEDTest.
	printline( "Does the LED work? (Y/N)" );

	PWM1_PWMCFG = 0;
	PWM1_PWMCFG = PWM1_PWMCFG_PWMENALWAYS | PWM1_PWMCFG_PWMCMP2CENTER;

	PWM1_PWMCOUNT = 0;
	
	PWM1_PWMCMP0 = 0;

	GPIO_IOF_SEL |= GPIO_REDLED | GPIO_GREENLED | GPIO_BLUELED;
	GPIO_IOF_EN  |= GPIO_REDLED | GPIO_GREENLED | GPIO_BLUELED;
	GPIO_OUT_XOR &= ~GPIO_GREENLED & ~GPIO_BLUELED;
	GPIO_OUT_XOR |= GPIO_REDLED;

	unsigned short r = 0x00FF;
	unsigned short g = 0x0000;
	unsigned short b = 0x0000;
	for ( ;; )
	{
		volatile unsigned long long then = CLINT_MTIME + 100;
		while ( CLINT_MTIME < then );

		if ( r > 0 && b == 0 ) { r--; g++; }
		if ( g > 0 && r == 0 ) { g--; b++; }
		if ( b > 0 && g == 0 ) { r++; b--; }

		PWM1_PWMCMP1 = (uint)( r ) << 4;
		PWM1_PWMCMP2 = (uint)( g ) << 4;
		PWM1_PWMCMP3 = 0xFFFF - ( (uint)( r ) << 4 );

		if ( !( UART0_RXDATA & UART0_RXDATA_EMPTY ) )
		{
			if ( ( UART0_RXDATA & UART0_RXDATA_DATA | 0x20 ) == 'y' ) printline( "PASS" );
			else printline( "FAIL" );
		}
	}
}
