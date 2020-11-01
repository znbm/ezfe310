void main( void )
{
	// This is a partial translation of led_fade.c,
	// from the Freedom-E-SDK's v1.0 branch.
	
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
	}
}

