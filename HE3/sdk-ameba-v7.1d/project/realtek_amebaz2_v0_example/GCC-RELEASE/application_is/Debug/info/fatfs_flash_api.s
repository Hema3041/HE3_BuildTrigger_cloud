	.arch armv8-m.main
	.arch_extension dsp
	.eabi_attribute 20, 1
	.eabi_attribute 21, 1
	.eabi_attribute 23, 3
	.eabi_attribute 24, 1
	.eabi_attribute 25, 1
	.eabi_attribute 26, 1
	.eabi_attribute 30, 2
	.eabi_attribute 34, 1
	.eabi_attribute 18, 4
	.file	"fatfs_flash_api.c"
	.text
.Ltext0:
	.cfi_sections	.debug_frame
	.section	.text.fatfs_flash_close,"ax",%progbits
	.align	1
	.p2align 2,,3
	.global	fatfs_flash_close
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	fatfs_flash_close, %function
fatfs_flash_close:
.LFB1:
	.file 1 "../../../component/common/file_system/fatfs/fatfs_flash_api.c"
	.loc 1 22 0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, lr}
	.cfi_def_cfa_offset 8
	.cfi_offset 4, -8
	.cfi_offset 14, -4
	.loc 1 23 0
	ldr	r4, .L19
	ldrb	r3, [r4]	@ zero_extendqisi2
	cbnz	r3, .L16
	.loc 1 34 0
	movs	r0, #0
	pop	{r4, pc}
.L16:
.LBB7:
.LBB8:
	.loc 1 24 0
	movs	r2, #1
	ldr	r1, .L19+4
	movs	r0, #0
	bl	f_mount
.LVL0:
	cbnz	r0, .L17
	.loc 1 28 0
	ldr	r3, .L19+8
	ldrb	r0, [r3]	@ zero_extendqisi2
	bl	FATFS_UnRegisterDiskDriver
.LVL1:
	cbnz	r0, .L18
.L4:
	.loc 1 31 0
	movs	r3, #0
	strb	r3, [r4]
.LBE8:
.LBE7:
	.loc 1 34 0
	movs	r0, #0
	pop	{r4, pc}
.L17:
.LBB10:
.LBB9:
	.loc 1 25 0
	ldr	r0, .L19+12
	bl	__wrap_printf
.LVL2:
	.loc 1 28 0
	ldr	r3, .L19+8
	ldrb	r0, [r3]	@ zero_extendqisi2
	bl	FATFS_UnRegisterDiskDriver
.LVL3:
	cmp	r0, #0
	beq	.L4
.L18:
	.loc 1 29 0
	ldr	r0, .L19+16
	bl	__wrap_printf
.LVL4:
	b	.L4
.L20:
	.align	2
.L19:
	.word	.LANCHOR0
	.word	fatfs_flash_param+4
	.word	fatfs_flash_param
	.word	.LC0
	.word	.LC1
.LBE9:
.LBE10:
	.cfi_endproc
.LFE1:
	.size	fatfs_flash_close, .-fatfs_flash_close
	.section	.text.fatfs_flash_init,"ax",%progbits
	.align	1
	.p2align 2,,3
	.global	fatfs_flash_init
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	fatfs_flash_init, %function
fatfs_flash_init:
.LFB2:
	.loc 1 37 0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 128
	@ frame_needed = 0, uses_anonymous_args = 0
.LVL5:
	push	{r4, r5, r6, r7, r8, lr}
	.cfi_def_cfa_offset 24
	.cfi_offset 4, -24
	.cfi_offset 5, -20
	.cfi_offset 6, -16
	.cfi_offset 7, -12
	.cfi_offset 8, -8
	.cfi_offset 14, -4
	.loc 1 40 0
	ldr	r8, .L48+60
	.loc 1 37 0
	sub	sp, sp, #128
	.cfi_def_cfa_offset 152
	.loc 1 40 0
	ldrb	r7, [r8]	@ zero_extendqisi2
	cbz	r7, .L43
	.loc 1 93 0
	movs	r4, #0
.LVL6:
.L21:
	.loc 1 98 0
	mov	r0, r4
	add	sp, sp, #128
	.cfi_remember_state
	.cfi_def_cfa_offset 24
	@ sp needed
	pop	{r4, r5, r6, r7, r8, pc}
.LVL7:
.L43:
	.cfi_restore_state
.LBB16:
	.loc 1 44 0
	ldr	r5, .L48
	add	r4, sp, #64
	ldmia	r5!, {r0, r1, r2, r3}
	stmia	r4!, {r0, r1, r2, r3}
	ldm	r5, {r0, r1}
	str	r0, [r4], #4
	movs	r2, #43
	strb	r1, [r4]
	add	r0, sp, #85
	mov	r1, r7
	bl	memset
.LVL8:
	.loc 1 47 0
	ldr	r0, .L48+4
	bl	__wrap_printf
.LVL9:
	.loc 1 48 0
	ldr	r0, .L48+8
	bl	FATFS_RegisterDiskDriver
.LVL10:
	ldr	r6, .L48+12
	.loc 1 50 0
	cmp	r0, #0
	.loc 1 48 0
	str	r0, [r6]
	.loc 1 50 0
	blt	.L44
.LVL11:
	.loc 1 56 0
	movs	r3, #47
	.loc 1 55 0
	movs	r2, #58
	.loc 1 54 0
	adds	r0, r0, #48
	.loc 1 59 0
	adds	r1, r6, #4
	.loc 1 54 0
	strb	r0, [r6, #4]
	.loc 1 59 0
	ldr	r0, .L48+16
	.loc 1 56 0
	strb	r3, [r6, #6]
	.loc 1 55 0
	strb	r2, [r6, #5]
	.loc 1 57 0
	strb	r7, [r6, #7]
	.loc 1 59 0
	bl	__wrap_printf
.LVL12:
	.loc 1 65 0
	movs	r2, #1
	adds	r1, r6, #4
	add	r0, r6, #8
	bl	f_mount
.LVL13:
	mov	r4, r0
.LVL14:
	.loc 1 68 0
	add	r1, sp, #64
	ldr	r0, .L48+20
	bl	__wrap_printf
.LVL15:
	.loc 1 69 0
	adds	r1, r6, #4
	mov	r0, sp
	bl	stpcpy
.LVL16:
	.loc 1 70 0
	add	r1, sp, #64
	bl	strcpy
.LVL17:
	.loc 1 71 0
	mov	r1, sp
	movs	r2, #19
	ldr	r0, .L48+24
	bl	f_open
.LVL18:
	.loc 1 72 0
	cbnz	r4, .L25
	.loc 1 72 0 is_stmt 0 discriminator 1
	cbz	r0, .L26
.L25:
	.loc 1 73 0 is_stmt 1
	mov	r2, #4096
	movs	r1, #1
	ldr	r0, .L48+28
.LVL19:
	bl	f_mkfs
.LVL20:
	.loc 1 74 0
	mov	r4, r0
.LVL21:
	cbnz	r0, .L45
	.loc 1 78 0
	ldr	r1, .L48+28
	mov	r2, r0
	adds	r0, r1, #4
.LVL22:
	bl	f_mount
.LVL23:
	cbz	r0, .L28
	.loc 1 79 0
	ldr	r0, .L48+32
	bl	__wrap_printf
.LVL24:
	.loc 1 80 0
	b	.L24
.LVL25:
.L44:
	.loc 1 51 0
	ldr	r0, .L48+36
	bl	__wrap_printf
.LVL26:
	.loc 1 62 0
	mov	r4, #-1
.LVL27:
.L24:
.LDL1:
.LBE16:
.LBB17:
.LBB18:
	.loc 1 23 0
	ldrb	r3, [r8]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L21
.LBB19:
.LBB20:
	.loc 1 24 0
	movs	r2, #1
	ldr	r1, .L48+28
	movs	r0, #0
	bl	f_mount
.LVL28:
	cbnz	r0, .L46
.L30:
	.loc 1 28 0
	ldrb	r0, [r6]	@ zero_extendqisi2
	bl	FATFS_UnRegisterDiskDriver
.LVL29:
	cbnz	r0, .L47
.L31:
	.loc 1 31 0
	movs	r3, #0
.LBE20:
.LBE19:
.LBE18:
.LBE17:
	.loc 1 98 0
	mov	r0, r4
.LBB27:
.LBB25:
.LBB23:
.LBB21:
	.loc 1 31 0
	strb	r3, [r8]
.LBE21:
.LBE23:
.LBE25:
.LBE27:
	.loc 1 98 0
	add	sp, sp, #128
	.cfi_remember_state
	.cfi_def_cfa_offset 24
	@ sp needed
	pop	{r4, r5, r6, r7, r8, pc}
.LVL30:
.L45:
	.cfi_restore_state
.LBB28:
	.loc 1 75 0
	mov	r1, r0
	ldr	r0, .L48+40
.LVL31:
	bl	__wrap_printf
.LVL32:
	.loc 1 76 0
	b	.L24
.LVL33:
.L26:
	.loc 1 85 0
	ldr	r0, .L48+44
.LVL34:
	bl	__wrap_printf
.LVL35:
.L29:
	.loc 1 87 0
	movs	r3, #1
.LBE28:
	.loc 1 93 0
	movs	r4, #0
.LBB29:
	.loc 1 87 0
	strb	r3, [r8]
.LBE29:
	b	.L21
.LVL36:
.L46:
.LBB30:
.LBB26:
.LBB24:
.LBB22:
	.loc 1 25 0
	ldr	r0, .L48+48
	bl	__wrap_printf
.LVL37:
	b	.L30
.L47:
	.loc 1 29 0
	ldr	r0, .L48+52
	bl	__wrap_printf
.LVL38:
	b	.L31
.LVL39:
.L28:
.LBE22:
.LBE24:
.LBE26:
.LBE30:
.LBB31:
	.loc 1 82 0
	ldr	r0, .L48+56
	bl	__wrap_printf
.LVL40:
	b	.L29
.L49:
	.align	2
.L48:
	.word	.LANCHOR1
	.word	.LC3
	.word	FLASH_disk_Driver
	.word	fatfs_flash_param
	.word	.LC5
	.word	.LC6
	.word	fatfs_flash_file
	.word	fatfs_flash_param+4
	.word	.LC8
	.word	.LC4
	.word	.LC7
	.word	.LC10
	.word	.LC0
	.word	.LC1
	.word	.LC9
	.word	.LANCHOR0
.LBE31:
	.cfi_endproc
.LFE2:
	.size	fatfs_flash_init, .-fatfs_flash_init
	.section	.text.fatfs_flash_get_param,"ax",%progbits
	.align	1
	.p2align 2,,3
	.global	fatfs_flash_get_param
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	fatfs_flash_get_param, %function
fatfs_flash_get_param:
.LFB3:
	.loc 1 101 0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
.LVL41:
	push	{r3, lr}
	.cfi_def_cfa_offset 8
	.cfi_offset 3, -8
	.cfi_offset 14, -4
	.loc 1 102 0
	ldr	r3, .L54
	.loc 1 103 0
	movw	r2, #4152
	.loc 1 102 0
	ldrb	r1, [r3]	@ zero_extendqisi2
	cbz	r1, .L51
	.loc 1 103 0
	ldr	r1, .L54+4
	bl	memcpy
.LVL42:
	.loc 1 104 0
	movs	r0, #0
	pop	{r3, pc}
.LVL43:
.L51:
	.loc 1 107 0
	bl	memset
.LVL44:
	.loc 1 108 0
	mov	r0, #-1
	.loc 1 110 0
	pop	{r3, pc}
.L55:
	.align	2
.L54:
	.word	.LANCHOR0
	.word	fatfs_flash_param
	.cfi_endproc
.LFE3:
	.size	fatfs_flash_get_param, .-fatfs_flash_get_param
	.section	.rodata
	.align	2
	.set	.LANCHOR1,. + 0
.LC2:
	.ascii	"flash_drive_test.txt\000"
	.space	43
	.section	.bss.fatfs_flash_file,"aw",%nobits
	.align	2
	.type	fatfs_flash_file, %object
	.size	fatfs_flash_file, 4132
fatfs_flash_file:
	.space	4132
	.section	.bss.fatfs_flash_init_done,"aw",%nobits
	.set	.LANCHOR0,. + 0
	.type	fatfs_flash_init_done, %object
	.size	fatfs_flash_init_done, 1
fatfs_flash_init_done:
	.space	1
	.section	.bss.fatfs_flash_param,"aw",%nobits
	.align	2
	.type	fatfs_flash_param, %object
	.size	fatfs_flash_param, 4152
fatfs_flash_param:
	.space	4152
	.section	.rodata.fatfs_flash_close.str1.4,"aMS",%progbits,1
	.align	2
.LC0:
	.ascii	"FATFS unmount flash logical drive fail.\012\000"
	.space	3
.LC1:
	.ascii	"Unregister flash disk driver from FATFS fail.\012\000"
	.section	.rodata.fatfs_flash_init.str1.4,"aMS",%progbits,1
	.align	2
.LC3:
	.ascii	"Register flash disk driver to Fatfs.\012\015\000"
	.space	1
.LC4:
	.ascii	"Register flash disk driver to FATFS fail.\012\015\000"
.LC5:
	.ascii	"Flash drive path: %s\012\000"
	.space	2
.LC6:
	.ascii	"Test flash drive (file: %s)\012\012\000"
	.space	2
.LC7:
	.ascii	"Create FAT volume on Flash fail. (%d)\012\015\000"
.LC8:
	.ascii	"FATFS mount logical drive on Flash fail.\012\015\000"
	.space	1
.LC9:
	.ascii	"flash mkfs and mount OK\012\015\000"
	.space	2
.LC10:
	.ascii	"flash mount OK\012\015\000"
	.text
.Letext0:
	.file 2 "/cygdrive/d/PUYA/HE3/sdk-ameba-v7.1d/tools/arm-none-eabi-gcc/asdk/cygwin/newlib/arm-none-eabi/include/machine/_default_types.h"
	.file 3 "/cygdrive/d/PUYA/HE3/sdk-ameba-v7.1d/tools/arm-none-eabi-gcc/asdk/cygwin/newlib/arm-none-eabi/include/sys/lock.h"
	.file 4 "/cygdrive/d/PUYA/HE3/sdk-ameba-v7.1d/tools/arm-none-eabi-gcc/asdk/cygwin/newlib/arm-none-eabi/include/sys/_types.h"
	.file 5 "/cygdrive/d/PUYA/HE3/sdk-ameba-v7.1d/tools/arm-none-eabi-gcc/asdk/cygwin/newlib/lib/gcc/arm-none-eabi/6.5.0/include/stddef.h"
	.file 6 "/cygdrive/d/PUYA/HE3/sdk-ameba-v7.1d/tools/arm-none-eabi-gcc/asdk/cygwin/newlib/arm-none-eabi/include/sys/reent.h"
	.file 7 "/cygdrive/d/PUYA/HE3/sdk-ameba-v7.1d/tools/arm-none-eabi-gcc/asdk/cygwin/newlib/arm-none-eabi/include/sys/_stdint.h"
	.file 8 "/cygdrive/d/PUYA/HE3/sdk-ameba-v7.1d/tools/arm-none-eabi-gcc/asdk/cygwin/newlib/arm-none-eabi/include/time.h"
	.file 9 "/cygdrive/d/PUYA/HE3/sdk-ameba-v7.1d/tools/arm-none-eabi-gcc/asdk/cygwin/newlib/arm-none-eabi/include/stdlib.h"
	.file 10 "../../../component/common/file_system/fatfs/r0.10c/include/integer.h"
	.file 11 "../../../component/common/file_system/fatfs/r0.10c/include/ff.h"
	.file 12 "../../../component/common/file_system/fatfs/r0.10c/include/diskio.h"
	.file 13 "../../../component/common/file_system/fatfs/fatfs_ext/inc/ff_driver.h"
	.file 14 "../../../component/common/file_system/fatfs/fatfs_flash_api.h"
	.file 15 "../../../component/common/file_system/fatfs/disk_if/inc/flash_fatfs.h"
	.file 16 "../../../component/common/api/platform/platform_stdlib_rtl8710c.h"
	.file 17 "<built-in>"
	.section	.debug_info,"",%progbits
.Ldebug_info0:
	.4byte	0x11b3
	.2byte	0x3
	.4byte	.Ldebug_abbrev0
	.byte	0x4
	.uleb128 0x1
	.4byte	.LASF220
	.byte	0xc
	.4byte	.LASF221
	.4byte	.LASF222
	.4byte	.Ldebug_ranges0+0x48
	.4byte	0
	.4byte	0
	.4byte	.Ldebug_line0
	.uleb128 0x2
	.byte	0x1
	.byte	0x6
	.4byte	.LASF0
	.uleb128 0x3
	.4byte	.LASF5
	.byte	0x2
	.byte	0x2b
	.4byte	0x3b
	.uleb128 0x2
	.byte	0x1
	.byte	0x8
	.4byte	.LASF1
	.uleb128 0x2
	.byte	0x2
	.byte	0x5
	.4byte	.LASF2
	.uleb128 0x2
	.byte	0x2
	.byte	0x7
	.4byte	.LASF3
	.uleb128 0x2
	.byte	0x4
	.byte	0x5
	.4byte	.LASF4
	.uleb128 0x3
	.4byte	.LASF6
	.byte	0x2
	.byte	0x4f
	.4byte	0x62
	.uleb128 0x2
	.byte	0x4
	.byte	0x7
	.4byte	.LASF7
	.uleb128 0x2
	.byte	0x8
	.byte	0x5
	.4byte	.LASF8
	.uleb128 0x2
	.byte	0x8
	.byte	0x7
	.4byte	.LASF9
	.uleb128 0x4
	.byte	0x4
	.byte	0x5
	.ascii	"int\000"
	.uleb128 0x2
	.byte	0x4
	.byte	0x7
	.4byte	.LASF10
	.uleb128 0x2
	.byte	0x8
	.byte	0x4
	.4byte	.LASF11
	.uleb128 0x3
	.4byte	.LASF12
	.byte	0x3
	.byte	0x7
	.4byte	0x77
	.uleb128 0x3
	.4byte	.LASF13
	.byte	0x4
	.byte	0x2c
	.4byte	0x50
	.uleb128 0x3
	.4byte	.LASF14
	.byte	0x4
	.byte	0x72
	.4byte	0x50
	.uleb128 0x5
	.4byte	.LASF15
	.byte	0x5
	.2byte	0x165
	.4byte	0x7e
	.uleb128 0x6
	.byte	0x4
	.byte	0x4
	.byte	0xa6
	.4byte	0xd8
	.uleb128 0x7
	.4byte	.LASF16
	.byte	0x4
	.byte	0xa8
	.4byte	0xad
	.uleb128 0x7
	.4byte	.LASF17
	.byte	0x4
	.byte	0xa9
	.4byte	0xd8
	.byte	0
	.uleb128 0x8
	.4byte	0x3b
	.4byte	0xe8
	.uleb128 0x9
	.4byte	0xe8
	.byte	0x3
	.byte	0
	.uleb128 0x2
	.byte	0x4
	.byte	0x7
	.4byte	.LASF18
	.uleb128 0xa
	.byte	0x8
	.byte	0x4
	.byte	0xa3
	.4byte	0x110
	.uleb128 0xb
	.4byte	.LASF19
	.byte	0x4
	.byte	0xa5
	.4byte	0x77
	.byte	0
	.uleb128 0xb
	.4byte	.LASF20
	.byte	0x4
	.byte	0xaa
	.4byte	0xb9
	.byte	0x4
	.byte	0
	.uleb128 0x3
	.4byte	.LASF21
	.byte	0x4
	.byte	0xab
	.4byte	0xef
	.uleb128 0x3
	.4byte	.LASF22
	.byte	0x4
	.byte	0xaf
	.4byte	0x8c
	.uleb128 0xc
	.byte	0x4
	.uleb128 0x3
	.4byte	.LASF23
	.byte	0x6
	.byte	0x16
	.4byte	0x62
	.uleb128 0xd
	.4byte	.LASF28
	.byte	0x18
	.byte	0x6
	.byte	0x2f
	.4byte	0x186
	.uleb128 0xb
	.4byte	.LASF24
	.byte	0x6
	.byte	0x31
	.4byte	0x186
	.byte	0
	.uleb128 0xe
	.ascii	"_k\000"
	.byte	0x6
	.byte	0x32
	.4byte	0x77
	.byte	0x4
	.uleb128 0xb
	.4byte	.LASF25
	.byte	0x6
	.byte	0x32
	.4byte	0x77
	.byte	0x8
	.uleb128 0xb
	.4byte	.LASF26
	.byte	0x6
	.byte	0x32
	.4byte	0x77
	.byte	0xc
	.uleb128 0xb
	.4byte	.LASF27
	.byte	0x6
	.byte	0x32
	.4byte	0x77
	.byte	0x10
	.uleb128 0xe
	.ascii	"_x\000"
	.byte	0x6
	.byte	0x33
	.4byte	0x18c
	.byte	0x14
	.byte	0
	.uleb128 0xf
	.byte	0x4
	.4byte	0x133
	.uleb128 0x8
	.4byte	0x128
	.4byte	0x19c
	.uleb128 0x9
	.4byte	0xe8
	.byte	0
	.byte	0
	.uleb128 0xd
	.4byte	.LASF29
	.byte	0x24
	.byte	0x6
	.byte	0x37
	.4byte	0x215
	.uleb128 0xb
	.4byte	.LASF30
	.byte	0x6
	.byte	0x39
	.4byte	0x77
	.byte	0
	.uleb128 0xb
	.4byte	.LASF31
	.byte	0x6
	.byte	0x3a
	.4byte	0x77
	.byte	0x4
	.uleb128 0xb
	.4byte	.LASF32
	.byte	0x6
	.byte	0x3b
	.4byte	0x77
	.byte	0x8
	.uleb128 0xb
	.4byte	.LASF33
	.byte	0x6
	.byte	0x3c
	.4byte	0x77
	.byte	0xc
	.uleb128 0xb
	.4byte	.LASF34
	.byte	0x6
	.byte	0x3d
	.4byte	0x77
	.byte	0x10
	.uleb128 0xb
	.4byte	.LASF35
	.byte	0x6
	.byte	0x3e
	.4byte	0x77
	.byte	0x14
	.uleb128 0xb
	.4byte	.LASF36
	.byte	0x6
	.byte	0x3f
	.4byte	0x77
	.byte	0x18
	.uleb128 0xb
	.4byte	.LASF37
	.byte	0x6
	.byte	0x40
	.4byte	0x77
	.byte	0x1c
	.uleb128 0xb
	.4byte	.LASF38
	.byte	0x6
	.byte	0x41
	.4byte	0x77
	.byte	0x20
	.byte	0
	.uleb128 0x10
	.4byte	.LASF39
	.2byte	0x108
	.byte	0x6
	.byte	0x4a
	.4byte	0x255
	.uleb128 0xb
	.4byte	.LASF40
	.byte	0x6
	.byte	0x4b
	.4byte	0x255
	.byte	0
	.uleb128 0xb
	.4byte	.LASF41
	.byte	0x6
	.byte	0x4c
	.4byte	0x255
	.byte	0x80
	.uleb128 0x11
	.4byte	.LASF42
	.byte	0x6
	.byte	0x4e
	.4byte	0x128
	.2byte	0x100
	.uleb128 0x11
	.4byte	.LASF43
	.byte	0x6
	.byte	0x51
	.4byte	0x128
	.2byte	0x104
	.byte	0
	.uleb128 0x8
	.4byte	0x126
	.4byte	0x265
	.uleb128 0x9
	.4byte	0xe8
	.byte	0x1f
	.byte	0
	.uleb128 0x10
	.4byte	.LASF44
	.2byte	0x190
	.byte	0x6
	.byte	0x5d
	.4byte	0x2a3
	.uleb128 0xb
	.4byte	.LASF24
	.byte	0x6
	.byte	0x5e
	.4byte	0x2a3
	.byte	0
	.uleb128 0xb
	.4byte	.LASF45
	.byte	0x6
	.byte	0x5f
	.4byte	0x77
	.byte	0x4
	.uleb128 0xb
	.4byte	.LASF46
	.byte	0x6
	.byte	0x61
	.4byte	0x2a9
	.byte	0x8
	.uleb128 0xb
	.4byte	.LASF39
	.byte	0x6
	.byte	0x62
	.4byte	0x215
	.byte	0x88
	.byte	0
	.uleb128 0xf
	.byte	0x4
	.4byte	0x265
	.uleb128 0x8
	.4byte	0x2b9
	.4byte	0x2b9
	.uleb128 0x9
	.4byte	0xe8
	.byte	0x1f
	.byte	0
	.uleb128 0xf
	.byte	0x4
	.4byte	0x2bf
	.uleb128 0x12
	.byte	0x1
	.uleb128 0xd
	.4byte	.LASF47
	.byte	0x8
	.byte	0x6
	.byte	0x75
	.4byte	0x2e6
	.uleb128 0xb
	.4byte	.LASF48
	.byte	0x6
	.byte	0x76
	.4byte	0x2e6
	.byte	0
	.uleb128 0xb
	.4byte	.LASF49
	.byte	0x6
	.byte	0x77
	.4byte	0x77
	.byte	0x4
	.byte	0
	.uleb128 0xf
	.byte	0x4
	.4byte	0x3b
	.uleb128 0xd
	.4byte	.LASF50
	.byte	0x68
	.byte	0x6
	.byte	0xb5
	.4byte	0x416
	.uleb128 0xe
	.ascii	"_p\000"
	.byte	0x6
	.byte	0xb6
	.4byte	0x2e6
	.byte	0
	.uleb128 0xe
	.ascii	"_r\000"
	.byte	0x6
	.byte	0xb7
	.4byte	0x77
	.byte	0x4
	.uleb128 0xe
	.ascii	"_w\000"
	.byte	0x6
	.byte	0xb8
	.4byte	0x77
	.byte	0x8
	.uleb128 0xb
	.4byte	.LASF51
	.byte	0x6
	.byte	0xb9
	.4byte	0x42
	.byte	0xc
	.uleb128 0xb
	.4byte	.LASF52
	.byte	0x6
	.byte	0xba
	.4byte	0x42
	.byte	0xe
	.uleb128 0xe
	.ascii	"_bf\000"
	.byte	0x6
	.byte	0xbb
	.4byte	0x2c1
	.byte	0x10
	.uleb128 0xb
	.4byte	.LASF53
	.byte	0x6
	.byte	0xbc
	.4byte	0x77
	.byte	0x18
	.uleb128 0xb
	.4byte	.LASF54
	.byte	0x6
	.byte	0xc3
	.4byte	0x126
	.byte	0x1c
	.uleb128 0xb
	.4byte	.LASF55
	.byte	0x6
	.byte	0xc5
	.4byte	0x584
	.byte	0x20
	.uleb128 0xb
	.4byte	.LASF56
	.byte	0x6
	.byte	0xc7
	.4byte	0x5af
	.byte	0x24
	.uleb128 0xb
	.4byte	.LASF57
	.byte	0x6
	.byte	0xca
	.4byte	0x5d4
	.byte	0x28
	.uleb128 0xb
	.4byte	.LASF58
	.byte	0x6
	.byte	0xcb
	.4byte	0x5ef
	.byte	0x2c
	.uleb128 0xe
	.ascii	"_ub\000"
	.byte	0x6
	.byte	0xce
	.4byte	0x2c1
	.byte	0x30
	.uleb128 0xe
	.ascii	"_up\000"
	.byte	0x6
	.byte	0xcf
	.4byte	0x2e6
	.byte	0x38
	.uleb128 0xe
	.ascii	"_ur\000"
	.byte	0x6
	.byte	0xd0
	.4byte	0x77
	.byte	0x3c
	.uleb128 0xb
	.4byte	.LASF59
	.byte	0x6
	.byte	0xd3
	.4byte	0x5f5
	.byte	0x40
	.uleb128 0xb
	.4byte	.LASF60
	.byte	0x6
	.byte	0xd4
	.4byte	0x605
	.byte	0x43
	.uleb128 0xe
	.ascii	"_lb\000"
	.byte	0x6
	.byte	0xd7
	.4byte	0x2c1
	.byte	0x44
	.uleb128 0xb
	.4byte	.LASF61
	.byte	0x6
	.byte	0xda
	.4byte	0x77
	.byte	0x4c
	.uleb128 0xb
	.4byte	.LASF62
	.byte	0x6
	.byte	0xdb
	.4byte	0x97
	.byte	0x50
	.uleb128 0xb
	.4byte	.LASF63
	.byte	0x6
	.byte	0xde
	.4byte	0x435
	.byte	0x54
	.uleb128 0xb
	.4byte	.LASF64
	.byte	0x6
	.byte	0xe2
	.4byte	0x11b
	.byte	0x58
	.uleb128 0xb
	.4byte	.LASF65
	.byte	0x6
	.byte	0xe4
	.4byte	0x110
	.byte	0x5c
	.uleb128 0xb
	.4byte	.LASF66
	.byte	0x6
	.byte	0xe5
	.4byte	0x77
	.byte	0x64
	.byte	0
	.uleb128 0x13
	.byte	0x1
	.4byte	0x77
	.4byte	0x435
	.uleb128 0x14
	.4byte	0x435
	.uleb128 0x14
	.4byte	0x126
	.uleb128 0x14
	.4byte	0x572
	.uleb128 0x14
	.4byte	0x77
	.byte	0
	.uleb128 0xf
	.byte	0x4
	.4byte	0x440
	.uleb128 0x15
	.4byte	0x435
	.uleb128 0x16
	.4byte	.LASF67
	.2byte	0x428
	.byte	0x6
	.2byte	0x239
	.4byte	0x572
	.uleb128 0x17
	.4byte	.LASF68
	.byte	0x6
	.2byte	0x23b
	.4byte	0x77
	.byte	0
	.uleb128 0x17
	.4byte	.LASF69
	.byte	0x6
	.2byte	0x240
	.4byte	0x65c
	.byte	0x4
	.uleb128 0x17
	.4byte	.LASF70
	.byte	0x6
	.2byte	0x240
	.4byte	0x65c
	.byte	0x8
	.uleb128 0x17
	.4byte	.LASF71
	.byte	0x6
	.2byte	0x240
	.4byte	0x65c
	.byte	0xc
	.uleb128 0x17
	.4byte	.LASF72
	.byte	0x6
	.2byte	0x242
	.4byte	0x77
	.byte	0x10
	.uleb128 0x17
	.4byte	.LASF73
	.byte	0x6
	.2byte	0x243
	.4byte	0x83e
	.byte	0x14
	.uleb128 0x17
	.4byte	.LASF74
	.byte	0x6
	.2byte	0x246
	.4byte	0x77
	.byte	0x30
	.uleb128 0x17
	.4byte	.LASF75
	.byte	0x6
	.2byte	0x247
	.4byte	0x854
	.byte	0x34
	.uleb128 0x17
	.4byte	.LASF76
	.byte	0x6
	.2byte	0x249
	.4byte	0x77
	.byte	0x38
	.uleb128 0x17
	.4byte	.LASF77
	.byte	0x6
	.2byte	0x24b
	.4byte	0x866
	.byte	0x3c
	.uleb128 0x17
	.4byte	.LASF78
	.byte	0x6
	.2byte	0x24e
	.4byte	0x186
	.byte	0x40
	.uleb128 0x17
	.4byte	.LASF79
	.byte	0x6
	.2byte	0x24f
	.4byte	0x77
	.byte	0x44
	.uleb128 0x17
	.4byte	.LASF80
	.byte	0x6
	.2byte	0x250
	.4byte	0x186
	.byte	0x48
	.uleb128 0x17
	.4byte	.LASF81
	.byte	0x6
	.2byte	0x251
	.4byte	0x86c
	.byte	0x4c
	.uleb128 0x17
	.4byte	.LASF82
	.byte	0x6
	.2byte	0x254
	.4byte	0x77
	.byte	0x50
	.uleb128 0x17
	.4byte	.LASF83
	.byte	0x6
	.2byte	0x255
	.4byte	0x572
	.byte	0x54
	.uleb128 0x17
	.4byte	.LASF84
	.byte	0x6
	.2byte	0x278
	.4byte	0x81c
	.byte	0x58
	.uleb128 0x18
	.4byte	.LASF44
	.byte	0x6
	.2byte	0x27c
	.4byte	0x2a3
	.2byte	0x148
	.uleb128 0x18
	.4byte	.LASF85
	.byte	0x6
	.2byte	0x27d
	.4byte	0x265
	.2byte	0x14c
	.uleb128 0x18
	.4byte	.LASF86
	.byte	0x6
	.2byte	0x281
	.4byte	0x87e
	.2byte	0x2dc
	.uleb128 0x18
	.4byte	.LASF87
	.byte	0x6
	.2byte	0x286
	.4byte	0x621
	.2byte	0x2e0
	.uleb128 0x18
	.4byte	.LASF88
	.byte	0x6
	.2byte	0x287
	.4byte	0x88a
	.2byte	0x2ec
	.byte	0
	.uleb128 0xf
	.byte	0x4
	.4byte	0x578
	.uleb128 0x2
	.byte	0x1
	.byte	0x8
	.4byte	.LASF89
	.uleb128 0x15
	.4byte	0x578
	.uleb128 0xf
	.byte	0x4
	.4byte	0x416
	.uleb128 0x13
	.byte	0x1
	.4byte	0x77
	.4byte	0x5a9
	.uleb128 0x14
	.4byte	0x435
	.uleb128 0x14
	.4byte	0x126
	.uleb128 0x14
	.4byte	0x5a9
	.uleb128 0x14
	.4byte	0x77
	.byte	0
	.uleb128 0xf
	.byte	0x4
	.4byte	0x57f
	.uleb128 0xf
	.byte	0x4
	.4byte	0x58a
	.uleb128 0x13
	.byte	0x1
	.4byte	0xa2
	.4byte	0x5d4
	.uleb128 0x14
	.4byte	0x435
	.uleb128 0x14
	.4byte	0x126
	.uleb128 0x14
	.4byte	0xa2
	.uleb128 0x14
	.4byte	0x77
	.byte	0
	.uleb128 0xf
	.byte	0x4
	.4byte	0x5b5
	.uleb128 0x13
	.byte	0x1
	.4byte	0x77
	.4byte	0x5ef
	.uleb128 0x14
	.4byte	0x435
	.uleb128 0x14
	.4byte	0x126
	.byte	0
	.uleb128 0xf
	.byte	0x4
	.4byte	0x5da
	.uleb128 0x8
	.4byte	0x3b
	.4byte	0x605
	.uleb128 0x9
	.4byte	0xe8
	.byte	0x2
	.byte	0
	.uleb128 0x8
	.4byte	0x3b
	.4byte	0x615
	.uleb128 0x9
	.4byte	0xe8
	.byte	0
	.byte	0
	.uleb128 0x5
	.4byte	.LASF90
	.byte	0x6
	.2byte	0x11f
	.4byte	0x2ec
	.uleb128 0x19
	.4byte	.LASF91
	.byte	0xc
	.byte	0x6
	.2byte	0x123
	.4byte	0x656
	.uleb128 0x17
	.4byte	.LASF24
	.byte	0x6
	.2byte	0x125
	.4byte	0x656
	.byte	0
	.uleb128 0x17
	.4byte	.LASF92
	.byte	0x6
	.2byte	0x126
	.4byte	0x77
	.byte	0x4
	.uleb128 0x17
	.4byte	.LASF93
	.byte	0x6
	.2byte	0x127
	.4byte	0x65c
	.byte	0x8
	.byte	0
	.uleb128 0xf
	.byte	0x4
	.4byte	0x621
	.uleb128 0xf
	.byte	0x4
	.4byte	0x615
	.uleb128 0x19
	.4byte	.LASF94
	.byte	0xe
	.byte	0x6
	.2byte	0x13f
	.4byte	0x697
	.uleb128 0x17
	.4byte	.LASF95
	.byte	0x6
	.2byte	0x140
	.4byte	0x697
	.byte	0
	.uleb128 0x17
	.4byte	.LASF96
	.byte	0x6
	.2byte	0x141
	.4byte	0x697
	.byte	0x6
	.uleb128 0x17
	.4byte	.LASF97
	.byte	0x6
	.2byte	0x142
	.4byte	0x49
	.byte	0xc
	.byte	0
	.uleb128 0x8
	.4byte	0x49
	.4byte	0x6a7
	.uleb128 0x9
	.4byte	0xe8
	.byte	0x2
	.byte	0
	.uleb128 0x1a
	.byte	0xd0
	.byte	0x6
	.2byte	0x259
	.4byte	0x7a8
	.uleb128 0x17
	.4byte	.LASF98
	.byte	0x6
	.2byte	0x25b
	.4byte	0x7e
	.byte	0
	.uleb128 0x17
	.4byte	.LASF99
	.byte	0x6
	.2byte	0x25c
	.4byte	0x572
	.byte	0x4
	.uleb128 0x17
	.4byte	.LASF100
	.byte	0x6
	.2byte	0x25d
	.4byte	0x7a8
	.byte	0x8
	.uleb128 0x17
	.4byte	.LASF101
	.byte	0x6
	.2byte	0x25e
	.4byte	0x19c
	.byte	0x24
	.uleb128 0x17
	.4byte	.LASF102
	.byte	0x6
	.2byte	0x25f
	.4byte	0x77
	.byte	0x48
	.uleb128 0x17
	.4byte	.LASF103
	.byte	0x6
	.2byte	0x260
	.4byte	0x70
	.byte	0x50
	.uleb128 0x17
	.4byte	.LASF104
	.byte	0x6
	.2byte	0x261
	.4byte	0x662
	.byte	0x58
	.uleb128 0x17
	.4byte	.LASF105
	.byte	0x6
	.2byte	0x262
	.4byte	0x110
	.byte	0x68
	.uleb128 0x17
	.4byte	.LASF106
	.byte	0x6
	.2byte	0x263
	.4byte	0x110
	.byte	0x70
	.uleb128 0x17
	.4byte	.LASF107
	.byte	0x6
	.2byte	0x264
	.4byte	0x110
	.byte	0x78
	.uleb128 0x17
	.4byte	.LASF108
	.byte	0x6
	.2byte	0x265
	.4byte	0x7b8
	.byte	0x80
	.uleb128 0x17
	.4byte	.LASF109
	.byte	0x6
	.2byte	0x266
	.4byte	0x7c8
	.byte	0x88
	.uleb128 0x17
	.4byte	.LASF110
	.byte	0x6
	.2byte	0x267
	.4byte	0x77
	.byte	0xa0
	.uleb128 0x17
	.4byte	.LASF111
	.byte	0x6
	.2byte	0x268
	.4byte	0x110
	.byte	0xa4
	.uleb128 0x17
	.4byte	.LASF112
	.byte	0x6
	.2byte	0x269
	.4byte	0x110
	.byte	0xac
	.uleb128 0x17
	.4byte	.LASF113
	.byte	0x6
	.2byte	0x26a
	.4byte	0x110
	.byte	0xb4
	.uleb128 0x17
	.4byte	.LASF114
	.byte	0x6
	.2byte	0x26b
	.4byte	0x110
	.byte	0xbc
	.uleb128 0x17
	.4byte	.LASF115
	.byte	0x6
	.2byte	0x26c
	.4byte	0x110
	.byte	0xc4
	.uleb128 0x17
	.4byte	.LASF116
	.byte	0x6
	.2byte	0x26d
	.4byte	0x77
	.byte	0xcc
	.byte	0
	.uleb128 0x8
	.4byte	0x578
	.4byte	0x7b8
	.uleb128 0x9
	.4byte	0xe8
	.byte	0x19
	.byte	0
	.uleb128 0x8
	.4byte	0x578
	.4byte	0x7c8
	.uleb128 0x9
	.4byte	0xe8
	.byte	0x7
	.byte	0
	.uleb128 0x8
	.4byte	0x578
	.4byte	0x7d8
	.uleb128 0x9
	.4byte	0xe8
	.byte	0x17
	.byte	0
	.uleb128 0x1a
	.byte	0xf0
	.byte	0x6
	.2byte	0x272
	.4byte	0x7fc
	.uleb128 0x17
	.4byte	.LASF117
	.byte	0x6
	.2byte	0x275
	.4byte	0x7fc
	.byte	0
	.uleb128 0x17
	.4byte	.LASF118
	.byte	0x6
	.2byte	0x276
	.4byte	0x80c
	.byte	0x78
	.byte	0
	.uleb128 0x8
	.4byte	0x2e6
	.4byte	0x80c
	.uleb128 0x9
	.4byte	0xe8
	.byte	0x1d
	.byte	0
	.uleb128 0x8
	.4byte	0x7e
	.4byte	0x81c
	.uleb128 0x9
	.4byte	0xe8
	.byte	0x1d
	.byte	0
	.uleb128 0x1b
	.byte	0xf0
	.byte	0x6
	.2byte	0x257
	.4byte	0x83e
	.uleb128 0x1c
	.4byte	.LASF67
	.byte	0x6
	.2byte	0x26e
	.4byte	0x6a7
	.uleb128 0x1c
	.4byte	.LASF119
	.byte	0x6
	.2byte	0x277
	.4byte	0x7d8
	.byte	0
	.uleb128 0x8
	.4byte	0x578
	.4byte	0x84e
	.uleb128 0x9
	.4byte	0xe8
	.byte	0x18
	.byte	0
	.uleb128 0x1d
	.4byte	.LASF223
	.byte	0x1
	.uleb128 0xf
	.byte	0x4
	.4byte	0x84e
	.uleb128 0x1e
	.byte	0x1
	.4byte	0x866
	.uleb128 0x14
	.4byte	0x435
	.byte	0
	.uleb128 0xf
	.byte	0x4
	.4byte	0x85a
	.uleb128 0xf
	.byte	0x4
	.4byte	0x186
	.uleb128 0x1e
	.byte	0x1
	.4byte	0x87e
	.uleb128 0x14
	.4byte	0x77
	.byte	0
	.uleb128 0xf
	.byte	0x4
	.4byte	0x884
	.uleb128 0xf
	.byte	0x4
	.4byte	0x872
	.uleb128 0x8
	.4byte	0x615
	.4byte	0x89a
	.uleb128 0x9
	.4byte	0xe8
	.byte	0x2
	.byte	0
	.uleb128 0x1f
	.4byte	.LASF120
	.byte	0x6
	.2byte	0x2fe
	.4byte	0x435
	.byte	0x1
	.byte	0x1
	.uleb128 0x1f
	.4byte	.LASF121
	.byte	0x6
	.2byte	0x2ff
	.4byte	0x43b
	.byte	0x1
	.byte	0x1
	.uleb128 0x3
	.4byte	.LASF122
	.byte	0x7
	.byte	0x18
	.4byte	0x30
	.uleb128 0x3
	.4byte	.LASF123
	.byte	0x7
	.byte	0x30
	.4byte	0x57
	.uleb128 0x20
	.4byte	.LASF124
	.byte	0x8
	.byte	0x9a
	.4byte	0x50
	.byte	0x1
	.byte	0x1
	.uleb128 0x20
	.4byte	.LASF125
	.byte	0x8
	.byte	0x9b
	.4byte	0x77
	.byte	0x1
	.byte	0x1
	.uleb128 0x8
	.4byte	0x572
	.4byte	0x8f6
	.uleb128 0x9
	.4byte	0xe8
	.byte	0x1
	.byte	0
	.uleb128 0x20
	.4byte	.LASF126
	.byte	0x8
	.byte	0x9e
	.4byte	0x8e6
	.byte	0x1
	.byte	0x1
	.uleb128 0x20
	.4byte	.LASF127
	.byte	0x9
	.byte	0x63
	.4byte	0x572
	.byte	0x1
	.byte	0x1
	.uleb128 0x3
	.4byte	.LASF128
	.byte	0xa
	.byte	0x10
	.4byte	0x3b
	.uleb128 0x15
	.4byte	0x910
	.uleb128 0x3
	.4byte	.LASF129
	.byte	0xa
	.byte	0x14
	.4byte	0x49
	.uleb128 0x3
	.4byte	.LASF130
	.byte	0xa
	.byte	0x1a
	.4byte	0x7e
	.uleb128 0x3
	.4byte	.LASF131
	.byte	0xa
	.byte	0x1e
	.4byte	0x62
	.uleb128 0x21
	.2byte	0x1030
	.byte	0xb
	.byte	0x51
	.4byte	0xa2e
	.uleb128 0xb
	.4byte	.LASF132
	.byte	0xb
	.byte	0x52
	.4byte	0x910
	.byte	0
	.uleb128 0xe
	.ascii	"drv\000"
	.byte	0xb
	.byte	0x53
	.4byte	0x910
	.byte	0x1
	.uleb128 0xb
	.4byte	.LASF133
	.byte	0xb
	.byte	0x54
	.4byte	0x910
	.byte	0x2
	.uleb128 0xb
	.4byte	.LASF134
	.byte	0xb
	.byte	0x55
	.4byte	0x910
	.byte	0x3
	.uleb128 0xb
	.4byte	.LASF135
	.byte	0xb
	.byte	0x56
	.4byte	0x910
	.byte	0x4
	.uleb128 0xb
	.4byte	.LASF136
	.byte	0xb
	.byte	0x57
	.4byte	0x910
	.byte	0x5
	.uleb128 0xe
	.ascii	"id\000"
	.byte	0xb
	.byte	0x58
	.4byte	0x920
	.byte	0x6
	.uleb128 0xb
	.4byte	.LASF137
	.byte	0xb
	.byte	0x59
	.4byte	0x920
	.byte	0x8
	.uleb128 0xb
	.4byte	.LASF138
	.byte	0xb
	.byte	0x5b
	.4byte	0x920
	.byte	0xa
	.uleb128 0xb
	.4byte	.LASF139
	.byte	0xb
	.byte	0x61
	.4byte	0x936
	.byte	0xc
	.uleb128 0xb
	.4byte	.LASF140
	.byte	0xb
	.byte	0x62
	.4byte	0x936
	.byte	0x10
	.uleb128 0xb
	.4byte	.LASF141
	.byte	0xb
	.byte	0x67
	.4byte	0x936
	.byte	0x14
	.uleb128 0xb
	.4byte	.LASF142
	.byte	0xb
	.byte	0x68
	.4byte	0x936
	.byte	0x18
	.uleb128 0xb
	.4byte	.LASF143
	.byte	0xb
	.byte	0x69
	.4byte	0x936
	.byte	0x1c
	.uleb128 0xb
	.4byte	.LASF144
	.byte	0xb
	.byte	0x6a
	.4byte	0x936
	.byte	0x20
	.uleb128 0xb
	.4byte	.LASF145
	.byte	0xb
	.byte	0x6b
	.4byte	0x936
	.byte	0x24
	.uleb128 0xb
	.4byte	.LASF146
	.byte	0xb
	.byte	0x6c
	.4byte	0x936
	.byte	0x28
	.uleb128 0xb
	.4byte	.LASF147
	.byte	0xb
	.byte	0x6d
	.4byte	0x936
	.byte	0x2c
	.uleb128 0xe
	.ascii	"win\000"
	.byte	0xb
	.byte	0x71
	.4byte	0xa2e
	.byte	0x30
	.byte	0
	.uleb128 0x8
	.4byte	0x910
	.4byte	0xa3f
	.uleb128 0x22
	.4byte	0xe8
	.2byte	0xfff
	.byte	0
	.uleb128 0x3
	.4byte	.LASF148
	.byte	0xb
	.byte	0x73
	.4byte	0x941
	.uleb128 0x21
	.2byte	0x1024
	.byte	0xb
	.byte	0x79
	.4byte	0xae2
	.uleb128 0xe
	.ascii	"fs\000"
	.byte	0xb
	.byte	0x7a
	.4byte	0xae2
	.byte	0
	.uleb128 0xe
	.ascii	"id\000"
	.byte	0xb
	.byte	0x7b
	.4byte	0x920
	.byte	0x4
	.uleb128 0xb
	.4byte	.LASF149
	.byte	0xb
	.byte	0x7c
	.4byte	0x910
	.byte	0x6
	.uleb128 0xe
	.ascii	"err\000"
	.byte	0xb
	.byte	0x7d
	.4byte	0x910
	.byte	0x7
	.uleb128 0xb
	.4byte	.LASF150
	.byte	0xb
	.byte	0x7e
	.4byte	0x936
	.byte	0x8
	.uleb128 0xb
	.4byte	.LASF142
	.byte	0xb
	.byte	0x7f
	.4byte	0x936
	.byte	0xc
	.uleb128 0xb
	.4byte	.LASF151
	.byte	0xb
	.byte	0x80
	.4byte	0x936
	.byte	0x10
	.uleb128 0xb
	.4byte	.LASF152
	.byte	0xb
	.byte	0x81
	.4byte	0x936
	.byte	0x14
	.uleb128 0xb
	.4byte	.LASF153
	.byte	0xb
	.byte	0x82
	.4byte	0x936
	.byte	0x18
	.uleb128 0xb
	.4byte	.LASF154
	.byte	0xb
	.byte	0x84
	.4byte	0x936
	.byte	0x1c
	.uleb128 0xb
	.4byte	.LASF155
	.byte	0xb
	.byte	0x85
	.4byte	0xae8
	.byte	0x20
	.uleb128 0xe
	.ascii	"buf\000"
	.byte	0xb
	.byte	0x91
	.4byte	0xa2e
	.byte	0x24
	.byte	0
	.uleb128 0xf
	.byte	0x4
	.4byte	0xa3f
	.uleb128 0xf
	.byte	0x4
	.4byte	0x910
	.uleb128 0x23
	.ascii	"FIL\000"
	.byte	0xb
	.byte	0x94
	.4byte	0xa4a
	.uleb128 0x24
	.byte	0x1
	.4byte	0x3b
	.byte	0xb
	.byte	0xc0
	.4byte	0xb7e
	.uleb128 0x25
	.4byte	.LASF156
	.byte	0
	.uleb128 0x25
	.4byte	.LASF157
	.byte	0x1
	.uleb128 0x25
	.4byte	.LASF158
	.byte	0x2
	.uleb128 0x25
	.4byte	.LASF159
	.byte	0x3
	.uleb128 0x25
	.4byte	.LASF160
	.byte	0x4
	.uleb128 0x25
	.4byte	.LASF161
	.byte	0x5
	.uleb128 0x25
	.4byte	.LASF162
	.byte	0x6
	.uleb128 0x25
	.4byte	.LASF163
	.byte	0x7
	.uleb128 0x25
	.4byte	.LASF164
	.byte	0x8
	.uleb128 0x25
	.4byte	.LASF165
	.byte	0x9
	.uleb128 0x25
	.4byte	.LASF166
	.byte	0xa
	.uleb128 0x25
	.4byte	.LASF167
	.byte	0xb
	.uleb128 0x25
	.4byte	.LASF168
	.byte	0xc
	.uleb128 0x25
	.4byte	.LASF169
	.byte	0xd
	.uleb128 0x25
	.4byte	.LASF170
	.byte	0xe
	.uleb128 0x25
	.4byte	.LASF171
	.byte	0xf
	.uleb128 0x25
	.4byte	.LASF172
	.byte	0x10
	.uleb128 0x25
	.4byte	.LASF173
	.byte	0x11
	.uleb128 0x25
	.4byte	.LASF174
	.byte	0x12
	.uleb128 0x25
	.4byte	.LASF175
	.byte	0x13
	.byte	0
	.uleb128 0x3
	.4byte	.LASF176
	.byte	0xb
	.byte	0xd5
	.4byte	0xaf9
	.uleb128 0x3
	.4byte	.LASF177
	.byte	0xc
	.byte	0x13
	.4byte	0x910
	.uleb128 0x24
	.byte	0x1
	.4byte	0x3b
	.byte	0xc
	.byte	0x16
	.4byte	0xbbf
	.uleb128 0x25
	.4byte	.LASF178
	.byte	0
	.uleb128 0x25
	.4byte	.LASF179
	.byte	0x1
	.uleb128 0x25
	.4byte	.LASF180
	.byte	0x2
	.uleb128 0x25
	.4byte	.LASF181
	.byte	0x3
	.uleb128 0x25
	.4byte	.LASF182
	.byte	0x4
	.byte	0
	.uleb128 0x3
	.4byte	.LASF183
	.byte	0xc
	.byte	0x1c
	.4byte	0xb94
	.uleb128 0xa
	.byte	0x20
	.byte	0xd
	.byte	0xb
	.4byte	0xc33
	.uleb128 0xb
	.4byte	.LASF184
	.byte	0xd
	.byte	0xc
	.4byte	0xc39
	.byte	0
	.uleb128 0xb
	.4byte	.LASF185
	.byte	0xd
	.byte	0xd
	.4byte	0xc39
	.byte	0x4
	.uleb128 0xb
	.4byte	.LASF186
	.byte	0xd
	.byte	0xe
	.4byte	0xc39
	.byte	0x8
	.uleb128 0xb
	.4byte	.LASF187
	.byte	0xd
	.byte	0xf
	.4byte	0xc59
	.byte	0xc
	.uleb128 0xb
	.4byte	.LASF188
	.byte	0xd
	.byte	0x11
	.4byte	0xc7f
	.byte	0x10
	.uleb128 0xb
	.4byte	.LASF189
	.byte	0xd
	.byte	0x14
	.4byte	0xc9a
	.byte	0x14
	.uleb128 0xe
	.ascii	"TAG\000"
	.byte	0xd
	.byte	0x16
	.4byte	0x2e6
	.byte	0x18
	.uleb128 0xb
	.4byte	.LASF190
	.byte	0xd
	.byte	0x17
	.4byte	0x3b
	.byte	0x1c
	.byte	0
	.uleb128 0x26
	.byte	0x1
	.4byte	0xb89
	.uleb128 0xf
	.byte	0x4
	.4byte	0xc33
	.uleb128 0x13
	.byte	0x1
	.4byte	0xbbf
	.4byte	0xc59
	.uleb128 0x14
	.4byte	0xae8
	.uleb128 0x14
	.4byte	0x936
	.uleb128 0x14
	.4byte	0x92b
	.byte	0
	.uleb128 0xf
	.byte	0x4
	.4byte	0xc3f
	.uleb128 0x13
	.byte	0x1
	.4byte	0xbbf
	.4byte	0xc79
	.uleb128 0x14
	.4byte	0xc79
	.uleb128 0x14
	.4byte	0x936
	.uleb128 0x14
	.4byte	0x92b
	.byte	0
	.uleb128 0xf
	.byte	0x4
	.4byte	0x91b
	.uleb128 0xf
	.byte	0x4
	.4byte	0xc5f
	.uleb128 0x13
	.byte	0x1
	.4byte	0xbbf
	.4byte	0xc9a
	.uleb128 0x14
	.4byte	0x910
	.uleb128 0x14
	.4byte	0x126
	.byte	0
	.uleb128 0xf
	.byte	0x4
	.4byte	0xc85
	.uleb128 0x3
	.4byte	.LASF191
	.byte	0xd
	.byte	0x18
	.4byte	0xbca
	.uleb128 0xa
	.byte	0x8
	.byte	0xd
	.byte	0x1a
	.4byte	0xccc
	.uleb128 0xe
	.ascii	"drv\000"
	.byte	0xd
	.byte	0x1b
	.4byte	0xccc
	.byte	0
	.uleb128 0xe
	.ascii	"nbr\000"
	.byte	0xd
	.byte	0x1c
	.4byte	0x7e
	.byte	0x4
	.byte	0
	.uleb128 0x8
	.4byte	0xcdc
	.4byte	0xcdc
	.uleb128 0x9
	.4byte	0xe8
	.byte	0
	.byte	0
	.uleb128 0xf
	.byte	0x4
	.4byte	0xca0
	.uleb128 0x3
	.4byte	.LASF192
	.byte	0xd
	.byte	0x1d
	.4byte	0xcab
	.uleb128 0x20
	.4byte	.LASF193
	.byte	0xd
	.byte	0x1e
	.4byte	0xce2
	.byte	0x1
	.byte	0x1
	.uleb128 0x10
	.4byte	.LASF194
	.2byte	0x1038
	.byte	0xe
	.byte	0x5
	.4byte	0xd2b
	.uleb128 0xb
	.4byte	.LASF190
	.byte	0xe
	.byte	0x6
	.4byte	0x77
	.byte	0
	.uleb128 0xe
	.ascii	"drv\000"
	.byte	0xe
	.byte	0x7
	.4byte	0xd2b
	.byte	0x4
	.uleb128 0xe
	.ascii	"fs\000"
	.byte	0xe
	.byte	0x8
	.4byte	0xa3f
	.byte	0x8
	.byte	0
	.uleb128 0x8
	.4byte	0x578
	.4byte	0xd3b
	.uleb128 0x9
	.4byte	0xe8
	.byte	0x3
	.byte	0
	.uleb128 0x3
	.4byte	.LASF195
	.byte	0xe
	.byte	0x9
	.4byte	0xcfa
	.uleb128 0x20
	.4byte	.LASF196
	.byte	0xf
	.byte	0x5
	.4byte	0xca0
	.byte	0x1
	.byte	0x1
	.uleb128 0x27
	.4byte	.LASF197
	.byte	0x1
	.byte	0xd
	.4byte	0xd3b
	.byte	0x5
	.byte	0x3
	.4byte	fatfs_flash_param
	.uleb128 0x27
	.4byte	.LASF198
	.byte	0x1
	.byte	0xe
	.4byte	0x8b6
	.byte	0x5
	.byte	0x3
	.4byte	fatfs_flash_init_done
	.uleb128 0x27
	.4byte	.LASF199
	.byte	0x1
	.byte	0xf
	.4byte	0xaee
	.byte	0x5
	.byte	0x3
	.4byte	fatfs_flash_file
	.uleb128 0x28
	.4byte	.LASF200
	.byte	0x1
	.byte	0x10
	.4byte	0x572
	.byte	0
	.uleb128 0x29
	.4byte	.LASF201
	.byte	0x1
	.byte	0x11
	.4byte	0x8c1
	.uleb128 0x29
	.4byte	.LASF202
	.byte	0x1
	.byte	0x12
	.4byte	0x8c1
	.uleb128 0x2a
	.byte	0x1
	.4byte	.LASF224
	.byte	0x1
	.byte	0x64
	.byte	0x1
	.4byte	0x77
	.4byte	.LFB3
	.4byte	.LFE3
	.byte	0x1
	.byte	0x9c
	.byte	0x1
	.4byte	0xe02
	.uleb128 0x2b
	.4byte	.LASF225
	.byte	0x1
	.byte	0x64
	.4byte	0xe02
	.4byte	.LLST4
	.uleb128 0x2c
	.4byte	.LVL42
	.4byte	0x1130
	.4byte	0xdf8
	.uleb128 0x2d
	.byte	0x1
	.byte	0x50
	.byte	0x3
	.byte	0xf3
	.uleb128 0x1
	.byte	0x50
	.uleb128 0x2d
	.byte	0x1
	.byte	0x51
	.byte	0x5
	.byte	0x3
	.4byte	fatfs_flash_param
	.uleb128 0x2d
	.byte	0x1
	.byte	0x52
	.byte	0x3
	.byte	0xa
	.2byte	0x1038
	.byte	0
	.uleb128 0x2e
	.4byte	.LVL44
	.4byte	0x113b
	.byte	0
	.uleb128 0xf
	.byte	0x4
	.4byte	0xd3b
	.uleb128 0x2f
	.byte	0x1
	.4byte	.LASF226
	.byte	0x1
	.byte	0x24
	.4byte	0x77
	.4byte	.LFB2
	.4byte	.LFE2
	.byte	0x1
	.byte	0x9c
	.byte	0x1
	.4byte	0x10a1
	.uleb128 0x30
	.ascii	"ret\000"
	.byte	0x1
	.byte	0x26
	.4byte	0x77
	.4byte	.LLST0
	.uleb128 0x31
	.4byte	.LASF227
	.byte	0x1
	.byte	0x5f
	.4byte	.LDL1
	.uleb128 0x32
	.4byte	.Ldebug_ranges0+0
	.4byte	0x103c
	.uleb128 0x33
	.4byte	.LASF203
	.byte	0x1
	.byte	0x29
	.4byte	0x77
	.4byte	.LLST1
	.uleb128 0x33
	.4byte	.LASF204
	.byte	0x1
	.byte	0x2a
	.4byte	0xb7e
	.4byte	.LLST2
	.uleb128 0x33
	.4byte	.LASF205
	.byte	0x1
	.byte	0x2a
	.4byte	0xb7e
	.4byte	.LLST3
	.uleb128 0x27
	.4byte	.LASF206
	.byte	0x1
	.byte	0x2b
	.4byte	0x10a1
	.byte	0x3
	.byte	0x91
	.sleb128 -152
	.uleb128 0x27
	.4byte	.LASF207
	.byte	0x1
	.byte	0x2c
	.4byte	0x10a1
	.byte	0x3
	.byte	0x91
	.sleb128 -88
	.uleb128 0x2c
	.4byte	.LVL8
	.4byte	0x113b
	.4byte	0xeb2
	.uleb128 0x2d
	.byte	0x1
	.byte	0x50
	.byte	0x3
	.byte	0x91
	.sleb128 -67
	.uleb128 0x2d
	.byte	0x1
	.byte	0x51
	.byte	0x2
	.byte	0x77
	.sleb128 0
	.uleb128 0x2d
	.byte	0x1
	.byte	0x52
	.byte	0x2
	.byte	0x8
	.byte	0x2b
	.byte	0
	.uleb128 0x2c
	.4byte	.LVL9
	.4byte	0x1146
	.4byte	0xec9
	.uleb128 0x2d
	.byte	0x1
	.byte	0x50
	.byte	0x5
	.byte	0x3
	.4byte	.LC3
	.byte	0
	.uleb128 0x2e
	.4byte	.LVL10
	.4byte	0x1153
	.uleb128 0x2c
	.4byte	.LVL12
	.4byte	0x1146
	.4byte	0xeef
	.uleb128 0x2d
	.byte	0x1
	.byte	0x50
	.byte	0x5
	.byte	0x3
	.4byte	.LC5
	.uleb128 0x2d
	.byte	0x1
	.byte	0x51
	.byte	0x2
	.byte	0x76
	.sleb128 4
	.byte	0
	.uleb128 0x2c
	.4byte	.LVL13
	.4byte	0x1160
	.4byte	0xf0e
	.uleb128 0x2d
	.byte	0x1
	.byte	0x50
	.byte	0x2
	.byte	0x76
	.sleb128 8
	.uleb128 0x2d
	.byte	0x1
	.byte	0x51
	.byte	0x2
	.byte	0x76
	.sleb128 4
	.uleb128 0x2d
	.byte	0x1
	.byte	0x52
	.byte	0x1
	.byte	0x31
	.byte	0
	.uleb128 0x2c
	.4byte	.LVL15
	.4byte	0x1146
	.4byte	0xf2c
	.uleb128 0x2d
	.byte	0x1
	.byte	0x50
	.byte	0x5
	.byte	0x3
	.4byte	.LC6
	.uleb128 0x2d
	.byte	0x1
	.byte	0x51
	.byte	0x3
	.byte	0x91
	.sleb128 -88
	.byte	0
	.uleb128 0x2c
	.4byte	.LVL16
	.4byte	0x116d
	.4byte	0xf46
	.uleb128 0x2d
	.byte	0x1
	.byte	0x50
	.byte	0x2
	.byte	0x7d
	.sleb128 0
	.uleb128 0x2d
	.byte	0x1
	.byte	0x51
	.byte	0x2
	.byte	0x76
	.sleb128 4
	.byte	0
	.uleb128 0x2c
	.4byte	.LVL17
	.4byte	0x117e
	.4byte	0xf5b
	.uleb128 0x2d
	.byte	0x1
	.byte	0x51
	.byte	0x3
	.byte	0x91
	.sleb128 -88
	.byte	0
	.uleb128 0x2c
	.4byte	.LVL18
	.4byte	0x118f
	.4byte	0xf7d
	.uleb128 0x2d
	.byte	0x1
	.byte	0x50
	.byte	0x5
	.byte	0x3
	.4byte	fatfs_flash_file
	.uleb128 0x2d
	.byte	0x1
	.byte	0x51
	.byte	0x2
	.byte	0x7d
	.sleb128 0
	.uleb128 0x2d
	.byte	0x1
	.byte	0x52
	.byte	0x1
	.byte	0x43
	.byte	0
	.uleb128 0x2c
	.4byte	.LVL20
	.4byte	0x119c
	.4byte	0xfa0
	.uleb128 0x2d
	.byte	0x1
	.byte	0x50
	.byte	0x5
	.byte	0x3
	.4byte	fatfs_flash_param+4
	.uleb128 0x2d
	.byte	0x1
	.byte	0x51
	.byte	0x1
	.byte	0x31
	.uleb128 0x2d
	.byte	0x1
	.byte	0x52
	.byte	0x3
	.byte	0xa
	.2byte	0x1000
	.byte	0
	.uleb128 0x2c
	.4byte	.LVL23
	.4byte	0x1160
	.4byte	0xfc6
	.uleb128 0x2d
	.byte	0x1
	.byte	0x50
	.byte	0x5
	.byte	0x3
	.4byte	fatfs_flash_param+8
	.uleb128 0x2d
	.byte	0x1
	.byte	0x51
	.byte	0x5
	.byte	0x3
	.4byte	fatfs_flash_param+4
	.uleb128 0x2d
	.byte	0x1
	.byte	0x52
	.byte	0x2
	.byte	0x74
	.sleb128 0
	.byte	0
	.uleb128 0x2c
	.4byte	.LVL24
	.4byte	0x1146
	.4byte	0xfdd
	.uleb128 0x2d
	.byte	0x1
	.byte	0x50
	.byte	0x5
	.byte	0x3
	.4byte	.LC8
	.byte	0
	.uleb128 0x2c
	.4byte	.LVL26
	.4byte	0x1146
	.4byte	0xff4
	.uleb128 0x2d
	.byte	0x1
	.byte	0x50
	.byte	0x5
	.byte	0x3
	.4byte	.LC4
	.byte	0
	.uleb128 0x2c
	.4byte	.LVL32
	.4byte	0x1146
	.4byte	0x1011
	.uleb128 0x2d
	.byte	0x1
	.byte	0x50
	.byte	0x5
	.byte	0x3
	.4byte	.LC7
	.uleb128 0x2d
	.byte	0x1
	.byte	0x51
	.byte	0x2
	.byte	0x74
	.sleb128 0
	.byte	0
	.uleb128 0x2c
	.4byte	.LVL35
	.4byte	0x1146
	.4byte	0x1028
	.uleb128 0x2d
	.byte	0x1
	.byte	0x50
	.byte	0x5
	.byte	0x3
	.4byte	.LC10
	.byte	0
	.uleb128 0x34
	.4byte	.LVL40
	.4byte	0x1146
	.uleb128 0x2d
	.byte	0x1
	.byte	0x50
	.byte	0x5
	.byte	0x3
	.4byte	.LC9
	.byte	0
	.byte	0
	.uleb128 0x35
	.4byte	0x10b1
	.4byte	.LBB17
	.4byte	.Ldebug_ranges0+0x28
	.byte	0x1
	.byte	0x60
	.uleb128 0x2c
	.4byte	.LVL28
	.4byte	0x1160
	.4byte	0x106c
	.uleb128 0x2d
	.byte	0x1
	.byte	0x50
	.byte	0x1
	.byte	0x30
	.uleb128 0x2d
	.byte	0x1
	.byte	0x51
	.byte	0x5
	.byte	0x3
	.4byte	fatfs_flash_param+4
	.uleb128 0x2d
	.byte	0x1
	.byte	0x52
	.byte	0x1
	.byte	0x31
	.byte	0
	.uleb128 0x2e
	.4byte	.LVL29
	.4byte	0x11a9
	.uleb128 0x2c
	.4byte	.LVL37
	.4byte	0x1146
	.4byte	0x108c
	.uleb128 0x2d
	.byte	0x1
	.byte	0x50
	.byte	0x5
	.byte	0x3
	.4byte	.LC0
	.byte	0
	.uleb128 0x34
	.4byte	.LVL38
	.4byte	0x1146
	.uleb128 0x2d
	.byte	0x1
	.byte	0x50
	.byte	0x5
	.byte	0x3
	.4byte	.LC1
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x8
	.4byte	0x578
	.4byte	0x10b1
	.uleb128 0x9
	.4byte	0xe8
	.byte	0x3f
	.byte	0
	.uleb128 0x36
	.byte	0x1
	.4byte	.LASF228
	.byte	0x1
	.byte	0x15
	.4byte	0x77
	.byte	0x1
	.uleb128 0x37
	.4byte	0x10b1
	.4byte	.LFB1
	.4byte	.LFE1
	.byte	0x1
	.byte	0x9c
	.byte	0x1
	.4byte	0x1130
	.uleb128 0x2c
	.4byte	.LVL0
	.4byte	0x1160
	.4byte	0x10f3
	.uleb128 0x2d
	.byte	0x1
	.byte	0x50
	.byte	0x1
	.byte	0x30
	.uleb128 0x2d
	.byte	0x1
	.byte	0x51
	.byte	0x5
	.byte	0x3
	.4byte	fatfs_flash_param+4
	.uleb128 0x2d
	.byte	0x1
	.byte	0x52
	.byte	0x1
	.byte	0x31
	.byte	0
	.uleb128 0x2e
	.4byte	.LVL1
	.4byte	0x11a9
	.uleb128 0x2c
	.4byte	.LVL2
	.4byte	0x1146
	.4byte	0x1113
	.uleb128 0x2d
	.byte	0x1
	.byte	0x50
	.byte	0x5
	.byte	0x3
	.4byte	.LC0
	.byte	0
	.uleb128 0x2e
	.4byte	.LVL3
	.4byte	0x11a9
	.uleb128 0x34
	.4byte	.LVL4
	.4byte	0x1146
	.uleb128 0x2d
	.byte	0x1
	.byte	0x50
	.byte	0x5
	.byte	0x3
	.4byte	.LC1
	.byte	0
	.byte	0
	.uleb128 0x38
	.byte	0x1
	.byte	0x1
	.4byte	.LASF208
	.4byte	.LASF208
	.uleb128 0x38
	.byte	0x1
	.byte	0x1
	.4byte	.LASF209
	.4byte	.LASF209
	.uleb128 0x39
	.byte	0x1
	.byte	0x1
	.4byte	.LASF210
	.4byte	.LASF210
	.byte	0x10
	.byte	0x1a
	.uleb128 0x39
	.byte	0x1
	.byte	0x1
	.4byte	.LASF211
	.4byte	.LASF211
	.byte	0xd
	.byte	0x20
	.uleb128 0x39
	.byte	0x1
	.byte	0x1
	.4byte	.LASF212
	.4byte	.LASF212
	.byte	0xb
	.byte	0xf3
	.uleb128 0x3a
	.byte	0x1
	.byte	0x1
	.4byte	.LASF213
	.4byte	.LASF215
	.byte	0x11
	.byte	0
	.4byte	.LASF213
	.uleb128 0x3a
	.byte	0x1
	.byte	0x1
	.4byte	.LASF214
	.4byte	.LASF216
	.byte	0x11
	.byte	0
	.4byte	.LASF214
	.uleb128 0x39
	.byte	0x1
	.byte	0x1
	.4byte	.LASF217
	.4byte	.LASF217
	.byte	0xb
	.byte	0xdc
	.uleb128 0x39
	.byte	0x1
	.byte	0x1
	.4byte	.LASF218
	.4byte	.LASF218
	.byte	0xb
	.byte	0xf4
	.uleb128 0x39
	.byte	0x1
	.byte	0x1
	.4byte	.LASF219
	.4byte	.LASF219
	.byte	0xd
	.byte	0x21
	.byte	0
	.section	.debug_abbrev,"",%progbits
.Ldebug_abbrev0:
	.uleb128 0x1
	.uleb128 0x11
	.byte	0x1
	.uleb128 0x25
	.uleb128 0xe
	.uleb128 0x13
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1b
	.uleb128 0xe
	.uleb128 0x55
	.uleb128 0x6
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x52
	.uleb128 0x1
	.uleb128 0x10
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x2
	.uleb128 0x24
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.byte	0
	.byte	0
	.uleb128 0x3
	.uleb128 0x16
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x4
	.uleb128 0x24
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0x8
	.byte	0
	.byte	0
	.uleb128 0x5
	.uleb128 0x16
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x6
	.uleb128 0x17
	.byte	0x1
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x7
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x8
	.uleb128 0x1
	.byte	0x1
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x9
	.uleb128 0x21
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2f
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0xa
	.uleb128 0x13
	.byte	0x1
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xb
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0xc
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0xd
	.uleb128 0x13
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xe
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0xf
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x10
	.uleb128 0x13
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0xb
	.uleb128 0x5
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x11
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0x5
	.byte	0
	.byte	0
	.uleb128 0x12
	.uleb128 0x15
	.byte	0
	.uleb128 0x27
	.uleb128 0xc
	.byte	0
	.byte	0
	.uleb128 0x13
	.uleb128 0x15
	.byte	0x1
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x14
	.uleb128 0x5
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x15
	.uleb128 0x26
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x16
	.uleb128 0x13
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0xb
	.uleb128 0x5
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x17
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x18
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0x5
	.byte	0
	.byte	0
	.uleb128 0x19
	.uleb128 0x13
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1a
	.uleb128 0x13
	.byte	0x1
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1b
	.uleb128 0x17
	.byte	0x1
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1c
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1d
	.uleb128 0x13
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3c
	.uleb128 0xc
	.byte	0
	.byte	0
	.uleb128 0x1e
	.uleb128 0x15
	.byte	0x1
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1f
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3c
	.uleb128 0xc
	.byte	0
	.byte	0
	.uleb128 0x20
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3c
	.uleb128 0xc
	.byte	0
	.byte	0
	.uleb128 0x21
	.uleb128 0x13
	.byte	0x1
	.uleb128 0xb
	.uleb128 0x5
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x22
	.uleb128 0x21
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2f
	.uleb128 0x5
	.byte	0
	.byte	0
	.uleb128 0x23
	.uleb128 0x16
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x24
	.uleb128 0x4
	.byte	0x1
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x25
	.uleb128 0x28
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1c
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x26
	.uleb128 0x15
	.byte	0
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x27
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0x28
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x1c
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x29
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x2a
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0xa
	.uleb128 0x2117
	.uleb128 0xc
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x2b
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x2c
	.uleb128 0x4109
	.byte	0x1
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x2d
	.uleb128 0x410a
	.byte	0
	.uleb128 0x2
	.uleb128 0xa
	.uleb128 0x2111
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0x2e
	.uleb128 0x4109
	.byte	0
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x31
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x2f
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0xa
	.uleb128 0x2117
	.uleb128 0xc
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x30
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x31
	.uleb128 0xa
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x11
	.uleb128 0x1
	.byte	0
	.byte	0
	.uleb128 0x32
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x55
	.uleb128 0x6
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x33
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x34
	.uleb128 0x4109
	.byte	0x1
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x31
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x35
	.uleb128 0x1d
	.byte	0x1
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x52
	.uleb128 0x1
	.uleb128 0x55
	.uleb128 0x6
	.uleb128 0x58
	.uleb128 0xb
	.uleb128 0x59
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x36
	.uleb128 0x2e
	.byte	0
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x20
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x37
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0xa
	.uleb128 0x2117
	.uleb128 0xc
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x38
	.uleb128 0x2e
	.byte	0
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3c
	.uleb128 0xc
	.uleb128 0x2007
	.uleb128 0xe
	.uleb128 0x3
	.uleb128 0xe
	.byte	0
	.byte	0
	.uleb128 0x39
	.uleb128 0x2e
	.byte	0
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3c
	.uleb128 0xc
	.uleb128 0x2007
	.uleb128 0xe
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x3a
	.uleb128 0x2e
	.byte	0
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3c
	.uleb128 0xc
	.uleb128 0x2007
	.uleb128 0xe
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x2007
	.uleb128 0xe
	.byte	0
	.byte	0
	.byte	0
	.section	.debug_loc,"",%progbits
.Ldebug_loc0:
.LLST4:
	.4byte	.LVL41
	.4byte	.LVL42-1
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL42-1
	.4byte	.LVL43
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x50
	.byte	0x9f
	.4byte	.LVL43
	.4byte	.LVL44-1
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL44-1
	.4byte	.LFE3
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x50
	.byte	0x9f
	.4byte	0
	.4byte	0
.LLST0:
	.4byte	.LVL5
	.4byte	.LVL6
	.2byte	0x2
	.byte	0x30
	.byte	0x9f
	.4byte	.LVL7
	.4byte	.LVL20
	.2byte	0x2
	.byte	0x30
	.byte	0x9f
	.4byte	.LVL20
	.4byte	.LVL22
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL22
	.4byte	.LVL23-1
	.2byte	0x1
	.byte	0x52
	.4byte	.LVL23-1
	.4byte	.LVL25
	.2byte	0x1
	.byte	0x54
	.4byte	.LVL25
	.4byte	.LVL27
	.2byte	0x2
	.byte	0x30
	.byte	0x9f
	.4byte	.LVL27
	.4byte	.LVL30
	.2byte	0x1
	.byte	0x54
	.4byte	.LVL30
	.4byte	.LVL31
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL31
	.4byte	.LVL33
	.2byte	0x1
	.byte	0x54
	.4byte	.LVL33
	.4byte	.LVL35
	.2byte	0x2
	.byte	0x30
	.byte	0x9f
	.4byte	.LVL36
	.4byte	.LFE2
	.2byte	0x1
	.byte	0x54
	.4byte	0
	.4byte	0
.LLST1:
	.4byte	.LVL7
	.4byte	.LVL11
	.2byte	0x2
	.byte	0x30
	.byte	0x9f
	.4byte	.LVL11
	.4byte	.LVL25
	.2byte	0x2
	.byte	0x31
	.byte	0x9f
	.4byte	.LVL25
	.4byte	.LVL27
	.2byte	0x2
	.byte	0x30
	.byte	0x9f
	.4byte	.LVL30
	.4byte	.LVL36
	.2byte	0x2
	.byte	0x31
	.byte	0x9f
	.4byte	.LVL39
	.4byte	.LFE2
	.2byte	0x2
	.byte	0x31
	.byte	0x9f
	.4byte	0
	.4byte	0
.LLST2:
	.4byte	.LVL14
	.4byte	.LVL21
	.2byte	0x1
	.byte	0x54
	.4byte	.LVL33
	.4byte	.LVL35
	.2byte	0x1
	.byte	0x54
	.4byte	0
	.4byte	0
.LLST3:
	.4byte	.LVL18
	.4byte	.LVL19
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL33
	.4byte	.LVL34
	.2byte	0x1
	.byte	0x50
	.4byte	0
	.4byte	0
	.section	.debug_aranges,"",%progbits
	.4byte	0x2c
	.2byte	0x2
	.4byte	.Ldebug_info0
	.byte	0x4
	.byte	0
	.2byte	0
	.2byte	0
	.4byte	.LFB1
	.4byte	.LFE1-.LFB1
	.4byte	.LFB2
	.4byte	.LFE2-.LFB2
	.4byte	.LFB3
	.4byte	.LFE3-.LFB3
	.4byte	0
	.4byte	0
	.section	.debug_ranges,"",%progbits
.Ldebug_ranges0:
	.4byte	.LBB16
	.4byte	.LBE16
	.4byte	.LBB28
	.4byte	.LBE28
	.4byte	.LBB29
	.4byte	.LBE29
	.4byte	.LBB31
	.4byte	.LBE31
	.4byte	0
	.4byte	0
	.4byte	.LBB17
	.4byte	.LBE17
	.4byte	.LBB27
	.4byte	.LBE27
	.4byte	.LBB30
	.4byte	.LBE30
	.4byte	0
	.4byte	0
	.4byte	.LFB1
	.4byte	.LFE1
	.4byte	.LFB2
	.4byte	.LFE2
	.4byte	.LFB3
	.4byte	.LFE3
	.4byte	0
	.4byte	0
	.section	.debug_line,"",%progbits
.Ldebug_line0:
	.section	.debug_str,"MS",%progbits,1
.LASF201:
	.ascii	"fatfs_flash_buf_size\000"
.LASF220:
	.ascii	"GNU C11 6.5.0 -march=armv8-m.main+dsp -mthumb -mcms"
	.ascii	"e -mfloat-abi=soft -mabi=aapcs -g -gdwarf-3 -gdwarf"
	.ascii	"-3 -O3 -fstack-usage -fdata-sections -ffunction-sec"
	.ascii	"tions\000"
.LASF39:
	.ascii	"_on_exit_args\000"
.LASF56:
	.ascii	"_write\000"
.LASF213:
	.ascii	"stpcpy\000"
.LASF125:
	.ascii	"_daylight\000"
.LASF107:
	.ascii	"_wctomb_state\000"
.LASF159:
	.ascii	"FR_NOT_READY\000"
.LASF148:
	.ascii	"FATFS\000"
.LASF104:
	.ascii	"_r48\000"
.LASF109:
	.ascii	"_signal_buf\000"
.LASF10:
	.ascii	"unsigned int\000"
.LASF167:
	.ascii	"FR_INVALID_DRIVE\000"
.LASF134:
	.ascii	"n_fats\000"
.LASF53:
	.ascii	"_lbfsize\000"
.LASF51:
	.ascii	"_flags\000"
.LASF68:
	.ascii	"_errno\000"
.LASF227:
	.ascii	"fatfs_init_err\000"
.LASF203:
	.ascii	"Fatfs_ok\000"
.LASF149:
	.ascii	"flag\000"
.LASF170:
	.ascii	"FR_MKFS_ABORTED\000"
.LASF153:
	.ascii	"dsect\000"
.LASF147:
	.ascii	"winsect\000"
.LASF12:
	.ascii	"_LOCK_RECURSIVE_T\000"
.LASF55:
	.ascii	"_read\000"
.LASF111:
	.ascii	"_mbrlen_state\000"
.LASF70:
	.ascii	"_stdout\000"
.LASF221:
	.ascii	"../../../component/common/file_system/fatfs/fatfs_f"
	.ascii	"lash_api.c\000"
.LASF174:
	.ascii	"FR_TOO_MANY_OPEN_FILES\000"
.LASF46:
	.ascii	"_fns\000"
.LASF54:
	.ascii	"_cookie\000"
.LASF186:
	.ascii	"disk_status\000"
.LASF198:
	.ascii	"fatfs_flash_init_done\000"
.LASF28:
	.ascii	"_Bigint\000"
.LASF36:
	.ascii	"__tm_wday\000"
.LASF222:
	.ascii	"/cygdrive/d/PUYA/HE3/sdk-ameba-v7.1d/project/realte"
	.ascii	"k_amebaz2_v0_example/GCC-RELEASE\000"
.LASF78:
	.ascii	"_result\000"
.LASF123:
	.ascii	"uint32_t\000"
.LASF214:
	.ascii	"strcpy\000"
.LASF32:
	.ascii	"__tm_hour\000"
.LASF136:
	.ascii	"fsi_flag\000"
.LASF19:
	.ascii	"__count\000"
.LASF154:
	.ascii	"dir_sect\000"
.LASF31:
	.ascii	"__tm_min\000"
.LASF120:
	.ascii	"_impure_ptr\000"
.LASF117:
	.ascii	"_nextf\000"
.LASF131:
	.ascii	"DWORD\000"
.LASF94:
	.ascii	"_rand48\000"
.LASF79:
	.ascii	"_result_k\000"
.LASF9:
	.ascii	"long long unsigned int\000"
.LASF100:
	.ascii	"_asctime_buf\000"
.LASF158:
	.ascii	"FR_INT_ERR\000"
.LASF50:
	.ascii	"__sFILE\000"
.LASF27:
	.ascii	"_wds\000"
.LASF184:
	.ascii	"disk_initialize\000"
.LASF215:
	.ascii	"__builtin_stpcpy\000"
.LASF195:
	.ascii	"fatfs_flash_params_t\000"
.LASF90:
	.ascii	"__FILE\000"
.LASF62:
	.ascii	"_offset\000"
.LASF132:
	.ascii	"fs_type\000"
.LASF144:
	.ascii	"fatbase\000"
.LASF200:
	.ascii	"fatfs_flash_buf\000"
.LASF73:
	.ascii	"_emergency\000"
.LASF164:
	.ascii	"FR_EXIST\000"
.LASF191:
	.ascii	"ll_diskio_drv\000"
.LASF30:
	.ascii	"__tm_sec\000"
.LASF217:
	.ascii	"f_open\000"
.LASF127:
	.ascii	"suboptarg\000"
.LASF37:
	.ascii	"__tm_yday\000"
.LASF72:
	.ascii	"_inc\000"
.LASF45:
	.ascii	"_ind\000"
.LASF190:
	.ascii	"drv_num\000"
.LASF24:
	.ascii	"_next\000"
.LASF113:
	.ascii	"_mbsrtowcs_state\000"
.LASF172:
	.ascii	"FR_LOCKED\000"
.LASF206:
	.ascii	"path\000"
.LASF126:
	.ascii	"_tzname\000"
.LASF20:
	.ascii	"__value\000"
.LASF80:
	.ascii	"_p5s\000"
.LASF228:
	.ascii	"fatfs_flash_close\000"
.LASF115:
	.ascii	"_wcsrtombs_state\000"
.LASF105:
	.ascii	"_mblen_state\000"
.LASF226:
	.ascii	"fatfs_flash_init\000"
.LASF89:
	.ascii	"char\000"
.LASF33:
	.ascii	"__tm_mday\000"
.LASF86:
	.ascii	"_sig_func\000"
.LASF112:
	.ascii	"_mbrtowc_state\000"
.LASF85:
	.ascii	"_atexit0\000"
.LASF216:
	.ascii	"__builtin_strcpy\000"
.LASF145:
	.ascii	"dirbase\000"
.LASF194:
	.ascii	"fatfs_flash_param_s\000"
.LASF189:
	.ascii	"disk_ioctl\000"
.LASF22:
	.ascii	"_flock_t\000"
.LASF16:
	.ascii	"__wch\000"
.LASF93:
	.ascii	"_iobs\000"
.LASF122:
	.ascii	"uint8_t\000"
.LASF179:
	.ascii	"RES_ERROR\000"
.LASF211:
	.ascii	"FATFS_RegisterDiskDriver\000"
.LASF58:
	.ascii	"_close\000"
.LASF139:
	.ascii	"last_clust\000"
.LASF76:
	.ascii	"__sdidinit\000"
.LASF124:
	.ascii	"_timezone\000"
.LASF140:
	.ascii	"free_clust\000"
.LASF69:
	.ascii	"_stdin\000"
.LASF102:
	.ascii	"_gamma_signgam\000"
.LASF169:
	.ascii	"FR_NO_FILESYSTEM\000"
.LASF8:
	.ascii	"long long int\000"
.LASF142:
	.ascii	"fsize\000"
.LASF48:
	.ascii	"_base\000"
.LASF81:
	.ascii	"_freelist\000"
.LASF96:
	.ascii	"_mult\000"
.LASF23:
	.ascii	"__ULong\000"
.LASF143:
	.ascii	"volbase\000"
.LASF114:
	.ascii	"_wcrtomb_state\000"
.LASF175:
	.ascii	"FR_INVALID_PARAMETER\000"
.LASF135:
	.ascii	"wflag\000"
.LASF52:
	.ascii	"_file\000"
.LASF160:
	.ascii	"FR_NO_FILE\000"
.LASF128:
	.ascii	"BYTE\000"
.LASF197:
	.ascii	"fatfs_flash_param\000"
.LASF129:
	.ascii	"WORD\000"
.LASF209:
	.ascii	"memset\000"
.LASF77:
	.ascii	"__cleanup\000"
.LASF133:
	.ascii	"csize\000"
.LASF21:
	.ascii	"_mbstate_t\000"
.LASF208:
	.ascii	"memcpy\000"
.LASF182:
	.ascii	"RES_PARERR\000"
.LASF193:
	.ascii	"disk\000"
.LASF150:
	.ascii	"fptr\000"
.LASF225:
	.ascii	"param\000"
.LASF38:
	.ascii	"__tm_isdst\000"
.LASF155:
	.ascii	"dir_ptr\000"
.LASF141:
	.ascii	"n_fatent\000"
.LASF207:
	.ascii	"flash_test_fn\000"
.LASF180:
	.ascii	"RES_WRPRT\000"
.LASF116:
	.ascii	"_h_errno\000"
.LASF163:
	.ascii	"FR_DENIED\000"
.LASF34:
	.ascii	"__tm_mon\000"
.LASF218:
	.ascii	"f_mkfs\000"
.LASF11:
	.ascii	"long double\000"
.LASF14:
	.ascii	"_fpos_t\000"
.LASF188:
	.ascii	"disk_write\000"
.LASF161:
	.ascii	"FR_NO_PATH\000"
.LASF44:
	.ascii	"_atexit\000"
.LASF65:
	.ascii	"_mbstate\000"
.LASF168:
	.ascii	"FR_NOT_ENABLED\000"
.LASF183:
	.ascii	"DRESULT\000"
.LASF157:
	.ascii	"FR_DISK_ERR\000"
.LASF2:
	.ascii	"short int\000"
.LASF212:
	.ascii	"f_mount\000"
.LASF173:
	.ascii	"FR_NOT_ENOUGH_CORE\000"
.LASF4:
	.ascii	"long int\000"
.LASF196:
	.ascii	"FLASH_disk_Driver\000"
.LASF88:
	.ascii	"__sf\000"
.LASF26:
	.ascii	"_sign\000"
.LASF162:
	.ascii	"FR_INVALID_NAME\000"
.LASF63:
	.ascii	"_data\000"
.LASF17:
	.ascii	"__wchb\000"
.LASF121:
	.ascii	"_global_impure_ptr\000"
.LASF185:
	.ascii	"disk_deinitialize\000"
.LASF35:
	.ascii	"__tm_year\000"
.LASF219:
	.ascii	"FATFS_UnRegisterDiskDriver\000"
.LASF101:
	.ascii	"_localtime_buf\000"
.LASF119:
	.ascii	"_unused\000"
.LASF5:
	.ascii	"__uint8_t\000"
.LASF84:
	.ascii	"_new\000"
.LASF137:
	.ascii	"n_rootdir\000"
.LASF82:
	.ascii	"_cvtlen\000"
.LASF25:
	.ascii	"_maxwds\000"
.LASF108:
	.ascii	"_l64a_buf\000"
.LASF130:
	.ascii	"UINT\000"
.LASF61:
	.ascii	"_blksize\000"
.LASF29:
	.ascii	"__tm\000"
.LASF64:
	.ascii	"_lock\000"
.LASF18:
	.ascii	"sizetype\000"
.LASF7:
	.ascii	"long unsigned int\000"
.LASF176:
	.ascii	"FRESULT\000"
.LASF92:
	.ascii	"_niobs\000"
.LASF15:
	.ascii	"wint_t\000"
.LASF156:
	.ascii	"FR_OK\000"
.LASF41:
	.ascii	"_dso_handle\000"
.LASF192:
	.ascii	"ff_disk_drv\000"
.LASF152:
	.ascii	"clust\000"
.LASF83:
	.ascii	"_cvtbuf\000"
.LASF1:
	.ascii	"unsigned char\000"
.LASF6:
	.ascii	"__uint32_t\000"
.LASF110:
	.ascii	"_getdate_err\000"
.LASF97:
	.ascii	"_add\000"
.LASF138:
	.ascii	"ssize\000"
.LASF171:
	.ascii	"FR_TIMEOUT\000"
.LASF202:
	.ascii	"fatfs_flash_buf_pos\000"
.LASF47:
	.ascii	"__sbuf\000"
.LASF199:
	.ascii	"fatfs_flash_file\000"
.LASF91:
	.ascii	"_glue\000"
.LASF177:
	.ascii	"DSTATUS\000"
.LASF204:
	.ascii	"res1\000"
.LASF205:
	.ascii	"res2\000"
.LASF178:
	.ascii	"RES_OK\000"
.LASF87:
	.ascii	"__sglue\000"
.LASF99:
	.ascii	"_strtok_last\000"
.LASF106:
	.ascii	"_mbtowc_state\000"
.LASF181:
	.ascii	"RES_NOTRDY\000"
.LASF75:
	.ascii	"_locale\000"
.LASF40:
	.ascii	"_fnargs\000"
.LASF0:
	.ascii	"signed char\000"
.LASF187:
	.ascii	"disk_read\000"
.LASF67:
	.ascii	"_reent\000"
.LASF3:
	.ascii	"short unsigned int\000"
.LASF146:
	.ascii	"database\000"
.LASF42:
	.ascii	"_fntypes\000"
.LASF165:
	.ascii	"FR_INVALID_OBJECT\000"
.LASF224:
	.ascii	"fatfs_flash_get_param\000"
.LASF49:
	.ascii	"_size\000"
.LASF13:
	.ascii	"_off_t\000"
.LASF60:
	.ascii	"_nbuf\000"
.LASF98:
	.ascii	"_unused_rand\000"
.LASF74:
	.ascii	"_unspecified_locale_info\000"
.LASF66:
	.ascii	"_flags2\000"
.LASF43:
	.ascii	"_is_cxa\000"
.LASF166:
	.ascii	"FR_WRITE_PROTECTED\000"
.LASF95:
	.ascii	"_seed\000"
.LASF103:
	.ascii	"_rand_next\000"
.LASF223:
	.ascii	"__locale_t\000"
.LASF57:
	.ascii	"_seek\000"
.LASF210:
	.ascii	"__wrap_printf\000"
.LASF71:
	.ascii	"_stderr\000"
.LASF118:
	.ascii	"_nmalloc\000"
.LASF59:
	.ascii	"_ubuf\000"
.LASF151:
	.ascii	"sclust\000"
	.ident	"GCC: (Realtek ASDK-6.5.0 Build 3215) 6.5.0"
