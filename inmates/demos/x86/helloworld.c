/*
 * Jailhouse, a Linux-based partitioning hypervisor
 *
 * Copyright (c) Siemens AG, 2013-2016
 *
 * Authors:
 *  Jan Kiszka <jan.kiszka@siemens.com>
 *
 * This work is licensed under the terms of the GNU GPL, version 2.  See
 * the COPYING file in the top-level directory.
 */

#include <inmate.h>

#ifdef CONFIG_UART_OXPCIE952
#define UART_BASE		0xe010
#else
#define UART_BASE		0x3f8
#endif

void inmate_main(void)
{
	printk_uart_base = UART_BASE;
	printk("Hello world\n");
}
