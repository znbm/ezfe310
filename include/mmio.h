#pragma once

// I wish I could use this macro, but GCC somethimes refuses to expand it.
#define MMIO( address ) ( *( (volatile unsigned int *)( address ) ) )
#undef MMIO

// PRCI //

#define PRCI_HFROSCCFG				(*((volatile unsigned int *)(0x10008000ul)))
#	define PRCI_HFROSCCFG_HFROSCDIV						0x0000003Fu
#	define PRCI_HFROSCCFG_HFROSCTRIM					0x001F0000u
#	define PRCI_HFROSCCFG_HFROSCEN						0x40000000u
#	define PRCI_HFROSCCFG_HFROSCRDY						0x80000000u
#define PRCI_HFXOSCCFG				(*((volatile unsigned int *)(0x10008004ul)))
#	define PRCI_HFXOSCCFG_HFXOSCEN						0x40000000u
#	define PRCI_HFXOSCCFG_HFXOSCRDY						0x80000000u
#define PRCI_PLLCFG				(*((volatile unsigned int *)(0x10008008ul)))
#	define PRCI_PLLCFG_PLLR							0x00000007u
#	define PRCI_PLLCFG_PLLF							0x000003F0u
#	define PRCI_PLLCFG_PLLQ							0x00000C00u
#	define PRCI_PLLCFG_PLLSEL						0x00010000u
#	define PRCI_PLLCFG_PLLREFSEL						0x00020000u
#	define PRCI_PLLCFG_PLLBYPASS						0x00040000u
#	define PRCI_PLLCFG_PLLLOCK						0x80000000u
#define PRCI_PLLOUTDIV				(*((volatile unsigned int *)(0x1000800Cul)))
#	define PRCI_PLLOUTDIV_PLLOUTDIV						0x0000003Fu
#	define PRCI_PLLOUTDIV_PLLOUTDIVBY1					0x00003F00u
#define PRCI_LFROSCCFG				(*((volatile unsigned int *)(0x10008070ul)))
#	define PRCI_LFROSCCFG_LFROSCDIV						0x0000003Fu
#	define PRCI_LFROSCCFG_LFROSCTRIM					0x001F0000u
#	define PRCI_LFROSCCFG_LFROSCEN						0x40000000u
#	define PRCI_LFROSCCFG_LFROSCRDY						0x80000000u

// Interrupts //
// TODO, although basically everything is held in CSRs.

// CLINT //
#define CLINT_MSIP				(*((volatile unsigned int *)(0x02000000ull)))
#	define CLINT_MSIP_MSIP							0x00000001u
#define CLINT_MTIMECMP			  (*((volatile unsigned long long *)(0x02004000ull)))
#define CLINT_MTIME			  (*((volatile unsigned long long *)(0x0200BFF8ull)))

// PLIC //
// TODO

// OTP is intentionally omitted -- 'Arduino' isn't a great form factor for a paperweight.

// AON is partially omitted -- I think that erratum `[AON-1]` basically makes it a waste of time.

// Watchdog //
#define AON_WDOGCFG				(*((volatile unsigned int *)(0x10000000ul)))
#	define AON_WDOGCFG_WDOGSCALE						0x00000007u
#	define AON_WDOGCFG_WDOGRSTEN						0x00000100u
#	define AON_WDOGCFG_WDOGZEROCMP						0x00000200u
#	define AON_WDOGCFG_WDOGENALWAYS						0x00001000u
#	define AON_WDOGCFG_WDOGCOREAWAKE					0x00002000u
#	define AON_WDOGCFG_WDOGIP0						0x10000000u
#define AON_WDOGCOUNT				(*((volatile unsigned int *)(0x10000008ul)))
#define AON_WDOGS				(*((volatile unsigned int *)(0x10000010ul)))
#define AON_WDOGFEED				(*((volatile unsigned int *)(0x10000018ul)))
#	define AON_WDOGFEED_DOGFOOD						0xD09F00Du
#define AON_WDOGKEY				(*((volatile unsigned int *)(0x1000001Cul)))
#define AON_WDOGCMP0				(*((volatile unsigned int *)(0x10000020ul)))
#	define AON_WDOGCMP0_WDOGCMP0						0x0000FFFFu

// PMU is omitted -- see above.

// RTC //
#define AON_RTCCFG				(*((volatile unsigned int *)(0x10000040ul)))
#	define AON_RTCCFG_RTCSCALE						0x0000000Fu
#	define AON_RTCCFG_RTCENALWAYS						0x00001000u
#	define AON_RTCCFG_RTCIP0						0x10000000u
#define AON_RTCCOUNTLO				(*((volatile unsigned int *)(0x10000048ul)))
#define AON_RTCCOUNTHI				(*((volatile unsigned int *)(0x1000004Cul)))
#define AON_RTCS				(*((volatile unsigned int *)(0x10000050ul)))
#define AON_RTCCMP0				(*((volatile unsigned int *)(0x10000060ul)))

// GPIO //

#define GPIO_INPUT_VAL				(*((volatile unsigned int *)(0x10012000ul)))
#define GPIO_INPUT_EN				(*((volatile unsigned int *)(0x10012004ul)))
#define GPIO_OUTPUT_EN				(*((volatile unsigned int *)(0x10012008ul)))
#define GPIO_OUTPUT_VAL				(*((volatile unsigned int *)(0x1001200Cul)))
#define GPIO_PUE				(*((volatile unsigned int *)(0x10012010ul)))
#define GPIO_DS					(*((volatile unsigned int *)(0x10012014ul)))
#define GPIO_RISE_IE				(*((volatile unsigned int *)(0x10012018ul)))
#define GPIO_RISE_IP				(*((volatile unsigned int *)(0x1001201Cul)))
#define GPIO_FALL_IE				(*((volatile unsigned int *)(0x10012020ul)))
#define GPIO_FALL_IP				(*((volatile unsigned int *)(0x10012024ul)))
#define GPIO_HIGH_IE				(*((volatile unsigned int *)(0x10012028ul)))
#define GPIO_HIGH_IP				(*((volatile unsigned int *)(0x1001202Cul)))
#define GPIO_LOW_IE				(*((volatile unsigned int *)(0x10012030ul)))
#define GPIO_LOW_IP				(*((volatile unsigned int *)(0x10012034ul)))
#define GPIO_IOF_EN				(*((volatile unsigned int *)(0x10012038ul))) /* undocumented in manual! */
#define GPIO_IOF_SEL				(*((volatile unsigned int *)(0x1001203Cul))) /* undocumented in manual! */
#define GPIO_OUT_XOR				(*((volatile unsigned int *)(0x10012040ul)))

// UART //

#define UART0_TXDATA				(*((volatile unsigned int *)(0x10013000ul)))
#	define UART0_TXDATA_DATA						0x000000FFu
#	define UART0_TXDATA_FULL						0x80000000u
#define UART0_RXDATA				(*((volatile unsigned int *)(0x10013004ul)))
#	define UART0_RXDATA_DATA						0x000000FFu
#	define UART0_RXDATA_EMPTY						0x80000000u
#define UART0_TXCTRL				(*((volatile unsigned int *)(0x10013008ul)))
#	define UART0_TXCTRL_TXEN						0x00000001u
#	define UART0_TXCTRL_NSTOP						0x00000002u
#	define UART0_TXCTRL_TXCNT						0x00070000u
#define UART0_RXCTRL				(*((volatile unsigned int *)(0x1001300Cul)))
#	define UART0_RXCTRL_RXEN						0x00000001u
#	define UART0_RXCTRL_RXCNT						0x00070000u
#define UART0_IE				(*((volatile unsigned int *)(0x10013010ul)))
#	define UART0_IE_TXWM							0x00000001u
#	define UART0_IE_RXWM							0x00000002u
#define UART0_IP				(*((volatile unsigned int *)(0x10013014ul)))
#	define UART0_IP_TXWM							0x00000001u
#	define UART0_IP_RXWM							0x00000002u
#define UART0_DIV				(*((volatile unsigned int *)(0x10013018ul)))
#	define UART0_DIV_DIV							0x0000FFFFu

#define UART1_TXDATA				(*((volatile unsigned int *)(0x10023000ul)))
#	define UART1_TXDATA_DATA						0x000000FFu
#	define UART1_TXDATA_FULL						0x80000000u
#define UART1_RXDATA				(*((volatile unsigned int *)(0x10023004ul)))
#	define UART1_RXDATA_DATA						0x000000FFu
#	define UART1_RXDATA_EMPTY						0x80000000u
#define UART1_TXCTRL				(*((volatile unsigned int *)(0x10023008ul)))
#	define UART1_TXCTRL_TXEN						0x00000001u
#	define UART1_TXCTRL_NSTOP						0x00000002u
#	define UART1_TXCTRL_TXCNT						0x00070000u
#define UART1_RXCTRL				(*((volatile unsigned int *)(0x1002300Cul)))
#	define UART1_RXCTRL_RXEN						0x00000001u
#	define UART1_RXCTRL_RXCNT						0x00070000u
#define UART1_IE				(*((volatile unsigned int *)(0x10023010ul)))
#	define UART1_IE_TXWM							0x00000001u
#	define UART1_IE_RXWM							0x00000002u
#define UART1_IP				(*((volatile unsigned int *)(0x10023014ul)))
#	define UART1_IP_TXWM							0x00000001u
#	define UART1_IP_RXWM							0x00000002u
#define UART1_DIV				(*((volatile unsigned int *)(0x10023018ul)))
#	define UART1_DIV_DIV							0x0000FFFFu

// SPI //

// I'm pretty sure QSPI 0 is used for the HiFive1's flash, so we'll just expose 1 and 2.

#define QSPI1_SCKDIV				(*((volatile unsigned int *)(0x10024000ul)))
#	define QSPI1_SCKDIV_DIV							0x00000FFFu
#define QSPI1_SCKMODE				(*((volatile unsigned int *)(0x10024004ul)))
#	define QSPI1_SCKDIV_PHA							0x00000001u
#	define QSPI1_SCKDIV_POL							0x00000002u
#define QSPI1_CSID				(*((volatile unsigned int *)(0x10024010ul)))
#define QSPI1_CSDEF				(*((volatile unsigned int *)(0x10024014ul)))
#define QSPI1_CSMODE				(*((volatile unsigned int *)(0x10024018ul)))
#	define QSPI1_CSMODE_MODE						0x0000003u
#define QSPI1_DELAY0				(*((volatile unsigned int *)(0x10024028ul)))
#	define QSPI1_DELAY0_CSSCK						0x000000FFu
#	define QSPI1_DELAY0_SCKCS						0x00FF0000u
#define QSPI1_DELAY1				(*((volatile unsigned int *)(0x1002402Cul)))
#	define QSPI1_DELAY1_INTERCS						0x000000FFu
#	define QSPI1_DELAY1_INTERXFR						0x00FF0000u
#define QSPI1_FMT				(*((volatile unsigned int *)(0x10024040ul)))
#	define QSPI1_FMT_PROTO							0x00000003u
#	define QSPI1_FMT_ENDIAN							0x00000004u
#	define QSPI1_FMT_DIR							0x00000008u
#	define QSPI1_FMT_LEN							0x00070000u
#define QSPI1_TXDATA				(*((volatile unsigned int *)(0x10024048ul)))
#	define QSPI1_TXDATA_DATA						0x000000FFu
#	define QSPI1_TXDATA_FULL						0x80000000u
#define QSPI1_RXDATA				(*((volatile unsigned int *)(0x1002404Cul)))
#	define QSPI1_RXDATA_DATA						0x000000FFu
#	define QSPI1_RXDATA_EMPTY						0x80000000u
#define QSPI1_TXMARK				(*((volatile unsigned int *)(0x10024050ul)))
#	define QSPI1_TXMARK_TXMARK						0x00000007u
#define QSPI1_RXMARK				(*((volatile unsigned int *)(0x10024054ul)))
#	define QSPI1_RXMARK_RXMARK						0x00000007u
#define QSPI1_FCTRL				(*((volatile unsigned int *)(0x10024060ul)))
#	define QSPI1_FCTRL_EN							0x00000001u
#define QSPI1_FFMT				(*((volatile unsigned int *)(0x10024064ul)))
#	define QSPI1_FFMT_CMD_EN						0x00000001u
#	define QSPI1_FFMT_ADDR_LEN						0x0000000Eu
#	define QSPI1_FFMT_PAD_CNT						0x000000F0u
#	define QSPI1_FFMT_CMD_PROTO						0x00000300u
#	define QSPI1_FFMT_ADDR_PROTO						0x00000C00u
#	define QSPI1_FFMT_DATA_PROTO						0x00003000u
#	define QSPI1_FFMT_FMT_CODE						0x00FF0000u
#	define QSPI1_FFMT_PAD_CODE						0xFF000000u
#define QSPI1_IE				(*((volatile unsigned int *)(0x10024070ul)))
#	define QSPI1_IE_TXWM							0x00000001u
#	define QSPI1_IE_RXWM							0x00000002u
#define QSPI1_IP				(*((volatile unsigned int *)(0x10024074ul)))
#	define QSPI1_IP_TXWM							0x00000001u
#	define QSPI1_IP_RXWM							0x00000002u

#define QSPI2_SCKDIV				(*((volatile unsigned int *)(0x10034000ul)))
#	define QSPI2_SCKDIV_DIV							0x00000FFFu
#define QSPI2_SCKMODE				(*((volatile unsigned int *)(0x10034004ul)))
#	define QSPI2_SCKDIV_PHA							0x00000001u
#	define QSPI2_SCKDIV_POL							0x00000002u
#define QSPI2_CSID				(*((volatile unsigned int *)(0x10034010ul)))
#define QSPI2_CSDEF				(*((volatile unsigned int *)(0x10034014ul)))
#define QSPI2_CSMODE				(*((volatile unsigned int *)(0x10034018ul)))
#	define QSPI2_CSMODE_MODE						0x0000003u
#define QSPI2_DELAY0				(*((volatile unsigned int *)(0x10034028ul)))
#	define QSPI2_DELAY0_CSSCK						0x000000FFu
#	define QSPI2_DELAY0_SCKCS						0x00FF0000u
#define QSPI2_DELAY1				(*((volatile unsigned int *)(0x1003402Cul)))
#	define QSPI2_DELAY1_INTERCS						0x000000FFu
#	define QSPI2_DELAY1_INTERXFR						0x00FF0000u
#define QSPI2_FMT				(*((volatile unsigned int *)(0x10034040ul)))
#	define QSPI2_FMT_PROTO							0x00000003u
#	define QSPI2_FMT_ENDIAN							0x00000004u
#	define QSPI2_FMT_DIR							0x00000008u
#	define QSPI2_FMT_LEN							0x00070000u
#define QSPI2_TXDATA				(*((volatile unsigned int *)(0x10034048ul)))
#	define QSPI2_TXDATA_DATA						0x000000FFu
#	define QSPI2_TXDATA_FULL						0x80000000u
#define QSPI2_RXDATA				(*((volatile unsigned int *)(0x1003404Cul)))
#	define QSPI2_RXDATA_DATA						0x000000FFu
#	define QSPI2_RXDATA_EMPTY						0x80000000u
#define QSPI2_TXMARK				(*((volatile unsigned int *)(0x10034050ul)))
#	define QSPI2_TXMARK_TXMARK						0x00000007u
#define QSPI2_RXMARK				(*((volatile unsigned int *)(0x10034054ul)))
#	define QSPI2_RXMARK_RXMARK						0x00000007u
#define QSPI2_FCTRL				(*((volatile unsigned int *)(0x10034060ul)))
#	define QSPI2_FCTRL_EN							0x00000001u
#define QSPI2_FFMT				(*((volatile unsigned int *)(0x10034064ul)))
#	define QSPI2_FFMT_CMD_EN						0x00000001u
#	define QSPI2_FFMT_ADDR_LEN						0x0000000Eu
#	define QSPI2_FFMT_PAD_CNT						0x000000F0u
#	define QSPI2_FFMT_CMD_PROTO						0x00000300u
#	define QSPI2_FFMT_ADDR_PROTO						0x00000C00u
#	define QSPI2_FFMT_DATA_PROTO						0x00003000u
#	define QSPI2_FFMT_FMT_CODE						0x00FF0000u
#	define QSPI2_FFMT_PAD_CODE						0xFF000000u
#define QSPI2_IE				(*((volatile unsigned int *)(0x10034070ul)))
#	define QSPI2_IE_TXWM							0x00000001u
#	define QSPI2_IE_RXWM							0x00000002u
#define QSPI2_IP				(*((volatile unsigned int *)(0x10034074ul)))
#	define QSPI2_IP_TXWM							0x00000001u
#	define QSPI2_IP_RXWM							0x00000002u

// PWM //

#define PWM0_PWMCFG				(*((volatile unsigned int *)(0x10015000ul)))
#	define PWM0_PWMCFG_PWMSCALE						0x0000000Fu
#	define PWM0_PWMCFG_PWMSTICKY						0x00000100u
#	define PWM0_PWMCFG_PWMZEROCMP						0x00000200u
#	define PWM0_PWMCFG_PWMDEGLITCH						0x00000400u
#	define PWM0_PWMCFG_PWMENALWAYS						0x00001000u
#	define PWM0_PWMCFG_PWMENONESHOT						0x00002000u
#	define PWM0_PWMCFG_PWMCMP0CENTER					0x00010000u
#	define PWM0_PWMCFG_PWMCMP1CENTER					0x00020000u
#	define PWM0_PWMCFG_PWMCMP2CENTER					0x00040000u
#	define PWM0_PWMCFG_PWMCMP3CENTER					0x00080000u
#	define PWM0_PWMCFG_PWMCMP0GANG						0x01000000u
#	define PWM0_PWMCFG_PWMCMP1GANG						0x02000000u
#	define PWM0_PWMCFG_PWMCMP2GANG						0x04000000u
#	define PWM0_PWMCFG_PWMCMP3GANG						0x08000000u
#	define PWM0_PWMCFG_PWMCMP0IP						0x10000000u
#	define PWM0_PWMCFG_PWMCMP1IP						0x20000000u
#	define PWM0_PWMCFG_PWMCMP2IP						0x40000000u
#	define PWM0_PWMCFG_PWMCMP3IP						0x80000000u
#define PWM0_PWMCOUNT				(*((volatile unsigned int *)(0x10015008ul)))
#	define PWM0_PWMCOUNT_PWMCOUNT						0x007FFFFFu
#define PWM0_PWMS				(*((volatile unsigned int *)(0x10015010ul)))
#define PWM0_PWMCMP0				(*((volatile unsigned int *)(0x10015020ul)))
#	define PWM0_PWMCMP0_PWMCMP0						0x0000FFFFu
#define PWM0_PWMCMP1				(*((volatile unsigned int *)(0x10015024ul)))
#	define PWM0_PWMCMP1_PWMCMP1						0x0000FFFFu
#define PWM0_PWMCMP2				(*((volatile unsigned int *)(0x10015028ul)))
#	define PWM0_PWMCMP2_PWMCMP2						0x0000FFFFu
#define PWM0_PWMCMP3				(*((volatile unsigned int *)(0x1001502Cul)))
#	define PWM0_PWMCMP3_PWMCMP3						0x0000FFFFu

#define PWM1_PWMCFG				(*((volatile unsigned int *)(0x10025000ul)))
#	define PWM1_PWMCFG_PWMSCALE						0x0000000Fu
#	define PWM1_PWMCFG_PWMSTICKY						0x00000100u
#	define PWM1_PWMCFG_PWMZEROCMP						0x00000200u
#	define PWM1_PWMCFG_PWMDEGLITCH						0x00000400u
#	define PWM1_PWMCFG_PWMENALWAYS						0x00001000u
#	define PWM1_PWMCFG_PWMENONESHOT						0x00002000u
#	define PWM1_PWMCFG_PWMCMP0CENTER					0x00010000u
#	define PWM1_PWMCFG_PWMCMP1CENTER					0x00020000u
#	define PWM1_PWMCFG_PWMCMP2CENTER					0x00040000u
#	define PWM1_PWMCFG_PWMCMP3CENTER					0x00080000u
#	define PWM1_PWMCFG_PWMCMP0GANG						0x01000000u
#	define PWM1_PWMCFG_PWMCMP1GANG						0x02000000u
#	define PWM1_PWMCFG_PWMCMP2GANG						0x04000000u
#	define PWM1_PWMCFG_PWMCMP3GANG						0x08000000u
#	define PWM1_PWMCFG_PWMCMP0IP						0x10000000u
#	define PWM1_PWMCFG_PWMCMP1IP						0x20000000u
#	define PWM1_PWMCFG_PWMCMP2IP						0x40000000u
#	define PWM1_PWMCFG_PWMCMP3IP						0x80000000u
#define PWM1_PWMCOUNT				(*((volatile unsigned int *)(0x10025008ul)))
#	define PWM1_PWMCOUNT_PWMCOUNT						0x7FFFFFFFu
#define PWM1_PWMS				(*((volatile unsigned int *)(0x10025010ul)))
#define PWM1_PWMCMP0				(*((volatile unsigned int *)(0x10025020ul)))
#	define PWM1_PWMCMP0_PWMCMP0						0x0000FFFFu
#define PWM1_PWMCMP1				(*((volatile unsigned int *)(0x10025024ul)))
#	define PWM1_PWMCMP1_PWMCMP1						0x0000FFFFu
#define PWM1_PWMCMP2				(*((volatile unsigned int *)(0x10025028ul)))
#	define PWM1_PWMCMP2_PWMCMP2						0x0000FFFFu
#define PWM1_PWMCMP3				(*((volatile unsigned int *)(0x1002502Cul)))
#	define PWM1_PWMCMP3_PWMCMP3						0x0000FFFFu

#define PWM2_PWMCFG				(*((volatile unsigned int *)(0x10035000ul)))
#	define PWM2_PWMCFG_PWMSCALE						0x0000000Fu
#	define PWM2_PWMCFG_PWMSTICKY						0x00000100u
#	define PWM2_PWMCFG_PWMZEROCMP						0x00000200u
#	define PWM2_PWMCFG_PWMDEGLITCH						0x00000400u
#	define PWM2_PWMCFG_PWMENALWAYS						0x00001000u
#	define PWM2_PWMCFG_PWMENONESHOT						0x00002000u
#	define PWM2_PWMCFG_PWMCMP0CENTER					0x00010000u
#	define PWM2_PWMCFG_PWMCMP1CENTER					0x00020000u
#	define PWM2_PWMCFG_PWMCMP2CENTER					0x00040000u
#	define PWM2_PWMCFG_PWMCMP3CENTER					0x00080000u
#	define PWM2_PWMCFG_PWMCMP0GANG						0x01000000u
#	define PWM2_PWMCFG_PWMCMP1GANG						0x02000000u
#	define PWM2_PWMCFG_PWMCMP2GANG						0x04000000u
#	define PWM2_PWMCFG_PWMCMP3GANG						0x08000000u
#	define PWM2_PWMCFG_PWMCMP0IP						0x10000000u
#	define PWM2_PWMCFG_PWMCMP1IP						0x20000000u
#	define PWM2_PWMCFG_PWMCMP2IP						0x40000000u
#	define PWM2_PWMCFG_PWMCMP3IP						0x80000000u
#define PWM2_PWMCOUNT				(*((volatile unsigned int *)(0x10035008ul)))
#	define PWM2_PWMCOUNT_PWMCOUNT						0x7FFFFFFFu
#define PWM2_PWMS				(*((volatile unsigned int *)(0x10035010ul)))
#define PWM2_PWMCMP0				(*((volatile unsigned int *)(0x10035020ul)))
#	define PWM2_PWMCMP0_PWMCMP0						0x0000FFFFu
#define PWM2_PWMCMP1				(*((volatile unsigned int *)(0x10035024ul)))
#	define PWM2_PWMCMP1_PWMCMP1						0x0000FFFFu
#define PWM2_PWMCMP2				(*((volatile unsigned int *)(0x10035028ul)))
#	define PWM2_PWMCMP2_PWMCMP2						0x0000FFFFu
#define PWM2_PWMCMP3				(*((volatile unsigned int *)(0x1003502Cul)))
#	define PWM2_PWMCMP3_PWMCMP3						0x0000FFFFu

// Debug //
// TODO
