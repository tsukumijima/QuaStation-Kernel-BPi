/*
 * memory.h
 *
 * Copyright (c) 2017 Realtek Semiconductor Corp.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 */

#ifndef __ASM_ARCH_MEMORY_H
#define __ASM_ARCH_MEMORY_H

#define RTK_FLAG_NONCACHED (1U << 0)
#define RTK_FLAG_SCPUACC (1U << 1)
#define RTK_FLAG_ACPUACC (1U << 2)
#define RTK_FLAG_HWIPACC (1U << 3)
#define RTK_FLAG_VE_SPEC (1U << 4)
#define RTK_FLAG_SECURE_AUDIO (1U << 5)
#define RTK_FLAG_SECURE_TPACC (1U << 6)
#define RTK_FLAG_DEAULT         (/*RTK_FLAG_NONCACHED | */RTK_FLAG_SCPUACC | RTK_FLAG_ACPUACC | RTK_FLAG_HWIPACC)

#if !defined(CONFIG_ARCH_MULTI_V7)
#define PLAT_PHYS_OFFSET (0x00000000)
#define PLAT_MEM_SIZE (512*1024*1024)
#endif

/* 0x00000000 ~ 0x0001efff */ // (X) ALL
#define SYS_BOOTCODE_MEMBASE    (PLAT_PHYS_OFFSET)
#define SYS_BOOTCODE_MEMSIZE    (0x00030000)
/* 0x0001f000 ~ 0x0001ffff */
#define RPC_COMM_PHYS           (0x0001F000)
#define RPC_COMM_SIZE           (0x00001000)
/* 0x00030000 ~ 0x000fffff */
#define RESERVED_832KB_PHYS     (0x00030000)
#define RESERVED_832KB_SIZE     (0x000D0000)
/* 0x01ffe000 ~ 0x02001fff */
#define RPC_RINGBUF_PHYS        (0x01ffe000)
#define RPC_RINGBUF_SIZE        (0x00004000)

#define ROOTFS_NORMAL_START     (0x02200000)
#define ROOTFS_NORMAL_SIZE      (0x00400000) //4MB
#define ROOTFS_NORMAL_END       (ROOTFS_NORMAL_START + ROOTFS_NORMAL_SIZE)

#define ROOTFS_RESCUE_START     (0x02200000)
#define ROOTFS_RESCUE_SIZE      (0x00C00000) //12MB
#define ROOTFS_RESCUE_END       (ROOTFS_NORMAL_START + ROOTFS_RESCUE_SIZE)

// ↓↓↓ Memory address definitions not present in kernel 4.1.17 ↓↓↓
/* 0x02600000 ~ 0x02bfffff */
#define MEM_SLOT_PHYS_1 (0x02600000)
#define MEM_SLOT_SIZE_1	 (0x00c00000) // Max : 12M
#define MEM_SLOT_FLAG_1 (RTK_FLAG_SCPUACC | RTK_FLAG_ACPUACC | \
		RTK_FLAG_HWIPACC)
/* 0x03200000 ~ 0x0f8fffff */
#define MEM_SLOT_PHYS_0 (0x03200000)
#define MEM_SLOT_SIZE_0	 (0x0c700000) // Max : 199M
#define MEM_SLOT_FLAG_0 (RTK_FLAG_SCPUACC | RTK_FLAG_ACPUACC | \
		RTK_FLAG_HWIPACC)
// ↑↑↑ Memory address definitions not present in kernel 4.1.17 ↑↑↑

/* 0x01b00000 ~ 0x01efffff */
#define ACPU_FIREWARE_PHYS      (0x01B00000)
#define ACPU_FIREWARE_SIZE      (0x00400000)
/* 0x10000000 ~ 0x10013fff */ // (X) ALL
#define ACPU_IDMEM_PHYS         (0x10000000)
#define ACPU_IDMEM_SIZE         (0x00014000)

// ↓↓↓ Memory address definitions not present in kernel 4.1.17 ↓↓↓
/* 0x10100000 ~ 0x141fffff */ // (X) ALL
/* Kernel will resrved memory for TEE OS if kernel config is for DRM */
#define TEE_OS_PHYS     (0x10100000)
#define TEE_OS_SIZE     (0x04100000)
/* Kernel will resrved memory for TEE OS if kernel config is for 1GB ATV w/ DRM */
#define TEE_OS_30MB_PHYS   (0x10100000)
#define TEE_OS_30MB_SIZE   (0x01E00000)
/* For memtester tool */
#define MEMTESTER_RSV_PHYS (0x22000000)
#define MEMTESTER_RSV_SIZE (0x04000000)
// ↑↑↑ Memory address definitions not present in kernel 4.1.17 ↑↑↑

// ↓↓↓ Memory address definitions not present in kernel 4.1.17 ↓↓↓
/* 0x14200000 ~ 0x1e7fffff */
#define MEM_SLOT_PHYS_2 (0x14200000)
#define MEM_SLOT_SIZE_2	(0x0a600000) // Max : 166M
#define MEM_SLOT_FLAG_2 (RTK_FLAG_SCPUACC | RTK_FLAG_ACPUACC | \
		RTK_FLAG_HWIPACC)
/* 0x1e800000 ~ 0x1effffff */
#define MEM_SLOT_PHYS_3 (0x1e800000)
#define MEM_SLOT_SIZE_3	 (0x00800000) // Max : 8M
#define MEM_SLOT_FLAG_3 (RTK_FLAG_SCPUACC | RTK_FLAG_ACPUACC | \
		RTK_FLAG_HWIPACC)
/* 0x45700000 ~ 0x48700000 */
#define MEM_SLOT_PHYS_5 (MEM_SLOT_PHYS_4 + MEM_SLOT_SIZE_4)
#define MEM_SLOT_SIZE_5 (0x03000000) // Max : 48MB
#define MEM_SLOT_FLAG_5 (RTK_FLAG_SCPUACC | RTK_FLAG_HWIPACC)
// ↑↑↑ Memory address definitions not present in kernel 4.1.17 ↑↑↑

/* 0x1fc00000 ~ 0x1fc00fff */ // (X) ALL
#define ACPU_BOOTCODE_PHYS      (0x1FC00000)
#define ACPU_BOOTCODE_SIZE      (0x00001000)

// ↓↓↓ Memory address definitions not present in kernel 4.1.17 ↓↓↓
/* 0x32800000 ~ 0x3effffff */
#define MEM_SLOT_PHYS_4 (0x32b00000)
#define MEM_SLOT_SIZE_4 (0x12c00000)
#define MEM_SLOT_FLAG_4 (RTK_FLAG_SCPUACC | RTK_FLAG_HWIPACC)
// ↑↑↑ Memory address definitions not present in kernel 4.1.17 ↑↑↑

/* 0x80000000 ~ 0x80007fff */
#define PLAT_SECURE_PHYS        (0x80000000)
#define PLAT_SECURE_SIZE        (0x00008000)
/* 0x88100000 ~ 0x88107fff */
#define PLAT_NOR_PHYS           (0x88100000)
#define PLAT_NOR_SIZE           (0x00008000)
/* 0x98000000 ~ 0x981fffff */
#define RBUS_BASE_PHYS          (0x98000000)
#define RBUS_BASE_SIZE          (0x00200000)

#define RBUS_BASE_VIRT          (0xFE000000)

// ↓↓↓ Memory address definitions not present in kernel 4.1.17 ↓↓↓
#define ROOTFS_BIST_START (0x30000000)
#define ROOTFS_BIST_SIZE (0x00C00000) //12MB
#define ROOTFS_BIST_END (ROOTFS_BIST_START + ROOTFS_BIST_SIZE)
// ↑↑↑ Memory address definitions not present in kernel 4.1.17 ↑↑↑

#define HW_LIMITATION_PHYS      (0x3FFFF000)
#define HW_LIMITATION_SIZE      (0x00001000) //4KB
#define HW_LIMITATION_START     (HW_LIMITATION_PHYS)
#define HW_LIMITATION_END       (HW_LIMITATION_START + HW_LIMITATION_SIZE)

// ↓↓↓ Memory address definitions not present in kernel 4.1.17 ↓↓↓
#define HW_LIMITATION_3GB_PHYS (0x7FFFF000)
#define HW_LIMITATION_3GB_SIZE (0x00001000) //4KB
#define HW_LIMITATION_3GB_START (HW_LIMITATION_3GB_PHYS)
#define HW_LIMITATION_3GB_END (HW_LIMITATION_3GB_START + HW_LIMITATION_3GB_SIZE)

#define HW_SECURE_RAM_PHYS PLAT_SECURE_PHYS
#define HW_SECURE_RAM_SIZE PLAT_SECURE_SIZE
#define HW_SECURE_RAM_START (HW_SECURE_RAM_PHYS)
#define HW_SECURE_RAM_END (HW_SECURE_RAM_START + HW_SECURE_RAM_SIZE)

#define HW_NOR_REMAP_PHYS (0x88100000)
#define HW_NOR_REMAP_SIZE (0x02000000) //32MB
#define HW_NOR_REMAP_START (HW_NOR_REMAP_PHYS)
#define HW_NOR_REMAP_END (HW_NOR_REMAP_START + HW_NOR_REMAP_SIZE)

#define MEM_SLOT_PHYS_BY(_nr, req_size) (MEM_SLOT_PHYS_##_nr##)
#define MEM_SLOT_SIZE_BY(_nr, req_size) ( \
		(req_size  > MEM_SLOT_SIZE_##_nr##) ? MEM_SLOT_SIZE_##_nr## : \
		req_size)
#define MEM_SLOT_FLAG_BY(_nr, req_size) (MEM_SLOT_FLAG_##_nr##)
#define MEM_SLOT(_nr, _type, req_size) \
	MEM_SLOT_##_type##_BY(_nr, req_size)
// ↑↑↑ Memory address definitions not present in kernel 4.1.17 ↑↑↑

/* 0x02c00000 ~ 0x0e3fffff */
#define ION_MEDIA_HEAP_PHYS1    (0x02C00000)
#define ION_MEDIA_HEAP_SIZE1    (0x0b800000)//184MB
#define ION_MEDIA_HEAP_FLAG1    (RTK_FLAG_DEAULT)

/* 0x02600000 ~ 0x02bfffff */ // 6MB
#define ION_AUDIO_HEAP_PHYS     (0x02600000)
#define ION_AUDIO_HEAP_SIZE     (0x00600000)
#define ION_AUDIO_HEAP_FLAG    (RTK_FLAG_DEAULT)

/* 0x11000000 ~ 0x1a1fffff */
#define ION_MEDIA_HEAP_PHYS2    (0x11000000)
#define ION_MEDIA_HEAP_SIZE2    (0x09200000)//146MB
#define ION_MEDIA_HEAP_FLAG2    (RTK_FLAG_DEAULT)

/* 0x1a200000 ~ 0x1a9fffff */
#define ION_MEDIA_HEAP_PHYS3    (ION_MEDIA_HEAP_PHYS2+ION_MEDIA_HEAP_SIZE2)
#define ION_MEDIA_HEAP_SIZE3    (0x00800000)//8MB
#define ION_MEDIA_HEAP_FLAG3    (RTK_FLAG_DEAULT|RTK_FLAG_VE_SPEC)

/* 0x32800000 ~ 0x3effffff */
#define ION_SECURE_HEAP_PHYS    (0x32800000)
#define ION_SECURE_HEAP_SIZE    (0x0c800000)//200MB
#define ION_SECURE_HEAP_FLAG    (RTK_FLAG_HWIPACC)

#else	//phoenix rtd119x memory.h include file path

#include "../../../arch/arm/mach-rtd119x/include/mach/memory.h"

#endif

