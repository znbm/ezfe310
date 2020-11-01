OUTPUT_ARCH( "riscv" )

ENTRY( _start )

MEMORY
{
	/* Quad SPI 0 Flash, hereafter `rom`. */
	rom (r xai): ORIGIN = 0x20000000, LENGTH = 512M

	/* Data Tightly Integrated Memory, hereafter `ram`. */
	ram (rw a ): ORIGIN = 0x80000000, LENGTH = 16K
}

SECTIONS
{
	/* Technically, the HiFive1's rom begins at 0x20000000. However, 	  *
	 * it ships with an inbuilt anti-bricking mechanism there that jumps to a *
	 * "main user portion" at 0x20400000, which we'll henceforth consider the *
	 * practical start of rom. If you think the extra 4 MiB is worth $70,     *
	 * go ahead and remove the `. += 0x00400000;`.				  */
	. = ORIGIN( rom );
	. += 0x00400000;
	
	/* `.text`, placed in rom, contains our program's machine instructions.     *
	 * The FE310 supports the 'C' extension, so this section is 2-byte aligned. */
	. = ALIGN( 2 );
	.text :
	{
		build/crt0.o
		. = ALIGN( 2 );
		*( .text .text.* )
	} > rom

	/* `.rodata` contains read-only program data. 			 *
	 * It's placed solely in rom, unlike 'regular' data (see below). *
	 * These sections are kept 8-byte aligned mostly to accomodate	 * 
	 * the 64-bit `long long`s that might end up in C programs.	 */
	. = ALIGN( 8 );
	.rodata :
	{
		*( .rodata .rodata.* )
	} > rom

	. = ORIGIN( ram );

	/* `.data` contains mutable program data. Storing it is a problem --	*
	 * rom is read-only, but ram is volatile and clears upon power cycling. *
	 * The solution is to store it in rom (at its "logical memory address")	*
	 * and then promise to have our runtime copy it into ram at startup.	*/ 

	. = ALIGN( 8 );
	PROVIDE( _data_start = ADDR( .data ) );
	.data :
	{
		*( .data .data.* )
		. = ALIGN( 8 );
		PROVIDE( __global_pointer$ = . + 0x800 );
		*( .sdata )
	} > ram AT > rom
	PROVIDE( _data_end = . );
	PROVIDE( _data_lma = LOADADDR( .data ) );

	/* `.bss` contains any mutable program data with value zero.  *
	 * Unlike `.data`, we don't have to store anything in rom,    *
	 * but our runtime will still write zeroes to ram at startup. */

	. = ALIGN( 8 );
	PROVIDE( _bss_start = ADDR( .bss ) );
	.bss :
	{
		*( .bss .bss.* )
		*( .sbss .sbss.* )
		*( COMMON ) /* We'll also pass `-fno-common` to the compiler. */
	} > ram
	. = ALIGN( 8 );
	PROVIDE( _bss_end = . );

	/* Finally, we set up the stack -- 16-byte aligned per the ABI, *
	 * and limited arbitrarally to 2048 bytes -- and, between that  *
	 * and the bss, the heap. 					*/

	PROVIDE( _heap_start = . );

	PROVIDE( _stack_size = 2K );

	. = ORIGIN( ram ) + LENGTH( ram ) - _stack_size;
	. = ALIGN( 16 );

	PROVIDE( _heap_end = . );

	. = ORIGIN( ram ) + LENGTH( ram );
	. = ALIGN( 16 );

	PROVIDE( _sp_init = . );
}

