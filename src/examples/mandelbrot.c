void main( void )
{
	// We'll perform this calculation in signed Q8.8 fixed point, sign-extended to 32 bits.
	// This is more than enough precision, and lets us perform multiplication without 64-bit registers.

	uartsetup();

	const char ramp[ 16 + 1 ] = " .,-:;+=/[UH8NM#";

	for ( int iy = -0x100; iy < 0x100; iy += 0x10 )
	{
		for ( int ix = -0x280; ix < 0x100; ix += 0x08 )
		{
			int xsq = 0;
			int ysq = 0;
			int x = 0;
			int y;
      
			int i = 0;
			for ( ; xsq + ysq <= 0x400 && i < 16; i++ )
			{
				y = ( ( x * y ) >> 7 ) + iy;

				x = xsq - ysq + ix;
				
				xsq = ( x * x ) >> 8;
				ysq = ( y * y ) >> 8;
			}

			while ( UART0_TXDATA & UART0_TXDATA_FULL );
			UART0_TXDATA = UART0_TXDATA_DATA & ramp[ i ];
		}

		while ( UART0_TXDATA & UART0_TXDATA_FULL );
		UART0_TXDATA = UART0_TXDATA_DATA & '\n';
		while ( UART0_TXDATA & UART0_TXDATA_FULL );
		UART0_TXDATA = UART0_TXDATA_DATA & '\r';
	}

	// For whatever reason, the back half of the Mandelbrot kinda disappears, but I think it's good enough.
}

