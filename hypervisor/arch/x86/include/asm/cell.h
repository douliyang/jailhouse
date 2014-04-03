/*
 * Jailhouse, a Linux-based partitioning hypervisor
 *
 * Copyright (c) Siemens AG, 2013
 *
 * Authors:
 *  Jan Kiszka <jan.kiszka@siemens.com>
 *
 * This work is licensed under the terms of the GNU GPL, version 2.  See
 * the COPYING file in the top-level directory.
 */

#ifndef _JAILHOUSE_ASM_CELL_H
#define _JAILHOUSE_ASM_CELL_H

#include <jailhouse/paging.h>

#include <jailhouse/cell-config.h>
#include <jailhouse/hypercall.h>

struct cell {
	struct {
		/* should be first as it requires page alignment */
		u8 __attribute__((aligned(PAGE_SIZE))) io_bitmap[2*PAGE_SIZE];
		struct paging_structures ept_structs;
	} vmx;

	struct {
		struct paging_structures pg_structs;
	} vtd;

	unsigned int id;
	unsigned int data_pages;
	struct jailhouse_cell_desc *config;

	struct cpu_set *cpu_set;
	struct cpu_set small_cpu_set;

	struct cell *next;

	union {
		struct jailhouse_comm_region comm_region;
		u8 padding[PAGE_SIZE];
	} __attribute__((aligned(PAGE_SIZE))) comm_page;
};

extern struct cell root_cell;

#endif /* !_JAILHOUSE_ASM_CELL_H */
