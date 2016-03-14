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

    bool allow_terminate = false;
    bool terminate = false;

    printk_uart_base = UART_BASE;
    printk("Hello world\n");

    while (!terminate) {
        asm volatile("hlt");

        if (cache_pollution)
            pollute_cache();

        switch (comm_region->msg_to_cell) {
        case JAILHOUSE_MSG_SHUTDOWN_REQUEST:
            if (!allow_terminate) {
                printk("Rejecting first shutdown request - "
                       "try again!\n");
                jailhouse_send_reply_from_cell(comm_region,
                                               JAILHOUSE_MSG_REQUEST_DENIED);
                allow_terminate = true;
            } else
                terminate = true;
            break;
        default:
            jailhouse_send_reply_from_cell(comm_region,
                                           JAILHOUSE_MSG_UNKNOWN);
            break;
        }
    }

    printk("Stopped APIC demo\n");
    comm_region->cell_state = JAILHOUSE_CELL_SHUT_DOWN;
}
