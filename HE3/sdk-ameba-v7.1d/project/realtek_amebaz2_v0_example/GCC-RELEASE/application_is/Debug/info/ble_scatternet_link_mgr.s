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
	.file	"ble_scatternet_link_mgr.c"
	.text
.Ltext0:
	.cfi_sections	.debug_frame
	.section	.text.ble_scatternet_link_mgr_add_device,"ax",%progbits
	.align	1
	.p2align 2,,3
	.global	ble_scatternet_link_mgr_add_device
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	ble_scatternet_link_mgr_add_device, %function
ble_scatternet_link_mgr_add_device:
.LFB0:
	.file 1 "../../../component/common/bluetooth/realtek/sdk/example/ble_scatternet/ble_scatternet_link_mgr.c"
	.loc 1 57 0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
.LVL0:
	push	{r4, r5, r6, r7, r8, lr}
	.cfi_def_cfa_offset 24
	.cfi_offset 4, -24
	.cfi_offset 5, -20
	.cfi_offset 6, -16
	.cfi_offset 7, -12
	.cfi_offset 8, -8
	.cfi_offset 14, -4
	.loc 1 59 0
	ldr	r7, .L24
	ldrb	r4, [r7]	@ zero_extendqisi2
	cmp	r4, #5
	bhi	.L4
.LVL1:
	mov	r5, r0
	mov	r8, r1
.LBB2:
	.loc 1 65 0 discriminator 1
	ldr	r6, .L24+4
	.loc 1 63 0 discriminator 1
	cbz	r4, .L3
	.loc 1 65 0
	movs	r2, #6
	mov	r1, r6
.LVL2:
	bl	memcmp
.LVL3:
	cbz	r0, .L9
.LVL4:
	.loc 1 63 0
	cmp	r4, #1
	beq	.L3
	.loc 1 65 0
	movs	r2, #6
	adds	r1, r6, #7
	mov	r0, r5
	bl	memcmp
.LVL5:
	cbz	r0, .L9
.LVL6:
	.loc 1 63 0
	cmp	r4, #2
	beq	.L3
	.loc 1 65 0
	movs	r2, #6
	add	r1, r6, #14
	mov	r0, r5
	bl	memcmp
.LVL7:
	cbz	r0, .L9
.LVL8:
	.loc 1 63 0
	cmp	r4, #3
	beq	.L3
	.loc 1 65 0
	movs	r2, #6
	add	r1, r6, #21
	mov	r0, r5
	bl	memcmp
.LVL9:
	cbz	r0, .L9
.LVL10:
	.loc 1 63 0
	cmp	r4, #5
	bne	.L3
	.loc 1 65 0
	movs	r2, #6
	add	r1, r6, #28
	mov	r0, r5
	bl	memcmp
.LVL11:
	cbz	r0, .L9
.LVL12:
.L3:
	.loc 1 72 0
	ldr	r2, [r5]	@ unaligned
	rsb	r3, r4, r4, lsl #3
	str	r2, [r6, r3]	@ unaligned
	ldrh	r2, [r5, #4]	@ unaligned
	add	r3, r3, r6
	.loc 1 76 0
	adds	r4, r4, #1
	.loc 1 72 0
	strh	r2, [r3, #4]	@ unaligned
	.loc 1 76 0
	strb	r4, [r7]
	.loc 1 73 0
	strb	r8, [r3, #6]
.LBE2:
	.loc 1 82 0
	movs	r0, #1
	pop	{r4, r5, r6, r7, r8, pc}
.LVL13:
.L4:
	.loc 1 80 0
	movs	r0, #0
.LVL14:
	pop	{r4, r5, r6, r7, r8, pc}
.LVL15:
.L9:
.LBB3:
	.loc 1 67 0
	movs	r0, #1
.LBE3:
	.loc 1 83 0
	pop	{r4, r5, r6, r7, r8, pc}
.LVL16:
.L25:
	.align	2
.L24:
	.word	.LANCHOR0
	.word	ble_scatternet_dev_list
	.cfi_endproc
.LFE0:
	.size	ble_scatternet_link_mgr_add_device, .-ble_scatternet_link_mgr_add_device
	.section	.text.ble_scatternet_link_mgr_clear_device_list,"ax",%progbits
	.align	1
	.p2align 2,,3
	.global	ble_scatternet_link_mgr_clear_device_list
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	ble_scatternet_link_mgr_clear_device_list, %function
ble_scatternet_link_mgr_clear_device_list:
.LFB1:
	.loc 1 90 0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	.loc 1 91 0
	movs	r2, #0
	ldr	r3, .L27
	strb	r2, [r3]
	bx	lr
.L28:
	.align	2
.L27:
	.word	.LANCHOR0
	.cfi_endproc
.LFE1:
	.size	ble_scatternet_link_mgr_clear_device_list, .-ble_scatternet_link_mgr_clear_device_list
	.global	ble_scatternet_dev_list_count
	.comm	ble_scatternet_dev_list,42,4
	.comm	ble_scatternet_app_link_table,18,4
	.section	.bss.ble_scatternet_dev_list_count,"aw",%nobits
	.set	.LANCHOR0,. + 0
	.type	ble_scatternet_dev_list_count, %object
	.size	ble_scatternet_dev_list_count, 1
ble_scatternet_dev_list_count:
	.space	1
	.text
.Letext0:
	.file 2 "/cygdrive/d/PUYA/HE3/sdk-ameba-v7.1d/tools/arm-none-eabi-gcc/asdk/cygwin/newlib/arm-none-eabi/include/machine/_default_types.h"
	.file 3 "/cygdrive/d/PUYA/HE3/sdk-ameba-v7.1d/tools/arm-none-eabi-gcc/asdk/cygwin/newlib/arm-none-eabi/include/sys/lock.h"
	.file 4 "/cygdrive/d/PUYA/HE3/sdk-ameba-v7.1d/tools/arm-none-eabi-gcc/asdk/cygwin/newlib/arm-none-eabi/include/sys/_types.h"
	.file 5 "/cygdrive/d/PUYA/HE3/sdk-ameba-v7.1d/tools/arm-none-eabi-gcc/asdk/cygwin/newlib/lib/gcc/arm-none-eabi/6.5.0/include/stddef.h"
	.file 6 "/cygdrive/d/PUYA/HE3/sdk-ameba-v7.1d/tools/arm-none-eabi-gcc/asdk/cygwin/newlib/arm-none-eabi/include/sys/reent.h"
	.file 7 "/cygdrive/d/PUYA/HE3/sdk-ameba-v7.1d/tools/arm-none-eabi-gcc/asdk/cygwin/newlib/arm-none-eabi/include/sys/_stdint.h"
	.file 8 "/cygdrive/d/PUYA/HE3/sdk-ameba-v7.1d/tools/arm-none-eabi-gcc/asdk/cygwin/newlib/arm-none-eabi/include/time.h"
	.file 9 "../../../component/common/bluetooth/realtek/sdk/inc/bluetooth/gap/gap.h"
	.file 10 "../../../component/common/bluetooth/realtek/sdk/inc/bluetooth/gap/gap_storage_le.h"
	.file 11 "../../../component/common/bluetooth/realtek/sdk/inc/bluetooth/gap/gap_msg.h"
	.file 12 "../../../component/common/bluetooth/realtek/sdk/inc/bluetooth/gap/gap_conn_le.h"
	.file 13 "../../../component/common/bluetooth/realtek/sdk/example/ble_scatternet/ble_scatternet_link_mgr.h"
	.file 14 "/cygdrive/d/PUYA/HE3/sdk-ameba-v7.1d/tools/arm-none-eabi-gcc/asdk/cygwin/newlib/arm-none-eabi/include/string.h"
	.section	.debug_info,"",%progbits
.Ldebug_info0:
	.4byte	0xb76
	.2byte	0x3
	.4byte	.Ldebug_abbrev0
	.byte	0x4
	.uleb128 0x1
	.4byte	.LASF148
	.byte	0xc
	.4byte	.LASF149
	.4byte	.LASF150
	.4byte	.Ldebug_ranges0+0x18
	.4byte	0
	.4byte	0
	.4byte	.Ldebug_line0
	.uleb128 0x2
	.byte	0x1
	.byte	0x6
	.4byte	.LASF0
	.uleb128 0x3
	.4byte	.LASF10
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
	.uleb128 0x2
	.byte	0x4
	.byte	0x7
	.4byte	.LASF5
	.uleb128 0x2
	.byte	0x8
	.byte	0x5
	.4byte	.LASF6
	.uleb128 0x2
	.byte	0x8
	.byte	0x7
	.4byte	.LASF7
	.uleb128 0x4
	.byte	0x4
	.byte	0x5
	.ascii	"int\000"
	.uleb128 0x2
	.byte	0x4
	.byte	0x7
	.4byte	.LASF8
	.uleb128 0x2
	.byte	0x8
	.byte	0x4
	.4byte	.LASF9
	.uleb128 0x3
	.4byte	.LASF11
	.byte	0x3
	.byte	0x7
	.4byte	0x6c
	.uleb128 0x3
	.4byte	.LASF12
	.byte	0x4
	.byte	0x2c
	.4byte	0x50
	.uleb128 0x3
	.4byte	.LASF13
	.byte	0x4
	.byte	0x72
	.4byte	0x50
	.uleb128 0x5
	.4byte	.LASF14
	.byte	0x5
	.2byte	0x165
	.4byte	0x73
	.uleb128 0x6
	.byte	0x4
	.byte	0x4
	.byte	0xa6
	.4byte	0xcd
	.uleb128 0x7
	.4byte	.LASF15
	.byte	0x4
	.byte	0xa8
	.4byte	0xa2
	.uleb128 0x7
	.4byte	.LASF16
	.byte	0x4
	.byte	0xa9
	.4byte	0xcd
	.byte	0
	.uleb128 0x8
	.4byte	0x3b
	.4byte	0xdd
	.uleb128 0x9
	.4byte	0xdd
	.byte	0x3
	.byte	0
	.uleb128 0x2
	.byte	0x4
	.byte	0x7
	.4byte	.LASF17
	.uleb128 0xa
	.byte	0x8
	.byte	0x4
	.byte	0xa3
	.4byte	0x105
	.uleb128 0xb
	.4byte	.LASF18
	.byte	0x4
	.byte	0xa5
	.4byte	0x6c
	.byte	0
	.uleb128 0xb
	.4byte	.LASF19
	.byte	0x4
	.byte	0xaa
	.4byte	0xae
	.byte	0x4
	.byte	0
	.uleb128 0x3
	.4byte	.LASF20
	.byte	0x4
	.byte	0xab
	.4byte	0xe4
	.uleb128 0x3
	.4byte	.LASF21
	.byte	0x4
	.byte	0xaf
	.4byte	0x81
	.uleb128 0xc
	.byte	0x4
	.uleb128 0x3
	.4byte	.LASF22
	.byte	0x6
	.byte	0x16
	.4byte	0x57
	.uleb128 0xd
	.4byte	.LASF27
	.byte	0x18
	.byte	0x6
	.byte	0x2f
	.4byte	0x17b
	.uleb128 0xb
	.4byte	.LASF23
	.byte	0x6
	.byte	0x31
	.4byte	0x17b
	.byte	0
	.uleb128 0xe
	.ascii	"_k\000"
	.byte	0x6
	.byte	0x32
	.4byte	0x6c
	.byte	0x4
	.uleb128 0xb
	.4byte	.LASF24
	.byte	0x6
	.byte	0x32
	.4byte	0x6c
	.byte	0x8
	.uleb128 0xb
	.4byte	.LASF25
	.byte	0x6
	.byte	0x32
	.4byte	0x6c
	.byte	0xc
	.uleb128 0xb
	.4byte	.LASF26
	.byte	0x6
	.byte	0x32
	.4byte	0x6c
	.byte	0x10
	.uleb128 0xe
	.ascii	"_x\000"
	.byte	0x6
	.byte	0x33
	.4byte	0x181
	.byte	0x14
	.byte	0
	.uleb128 0xf
	.byte	0x4
	.4byte	0x128
	.uleb128 0x8
	.4byte	0x11d
	.4byte	0x191
	.uleb128 0x9
	.4byte	0xdd
	.byte	0
	.byte	0
	.uleb128 0xd
	.4byte	.LASF28
	.byte	0x24
	.byte	0x6
	.byte	0x37
	.4byte	0x20a
	.uleb128 0xb
	.4byte	.LASF29
	.byte	0x6
	.byte	0x39
	.4byte	0x6c
	.byte	0
	.uleb128 0xb
	.4byte	.LASF30
	.byte	0x6
	.byte	0x3a
	.4byte	0x6c
	.byte	0x4
	.uleb128 0xb
	.4byte	.LASF31
	.byte	0x6
	.byte	0x3b
	.4byte	0x6c
	.byte	0x8
	.uleb128 0xb
	.4byte	.LASF32
	.byte	0x6
	.byte	0x3c
	.4byte	0x6c
	.byte	0xc
	.uleb128 0xb
	.4byte	.LASF33
	.byte	0x6
	.byte	0x3d
	.4byte	0x6c
	.byte	0x10
	.uleb128 0xb
	.4byte	.LASF34
	.byte	0x6
	.byte	0x3e
	.4byte	0x6c
	.byte	0x14
	.uleb128 0xb
	.4byte	.LASF35
	.byte	0x6
	.byte	0x3f
	.4byte	0x6c
	.byte	0x18
	.uleb128 0xb
	.4byte	.LASF36
	.byte	0x6
	.byte	0x40
	.4byte	0x6c
	.byte	0x1c
	.uleb128 0xb
	.4byte	.LASF37
	.byte	0x6
	.byte	0x41
	.4byte	0x6c
	.byte	0x20
	.byte	0
	.uleb128 0x10
	.4byte	.LASF38
	.2byte	0x108
	.byte	0x6
	.byte	0x4a
	.4byte	0x24a
	.uleb128 0xb
	.4byte	.LASF39
	.byte	0x6
	.byte	0x4b
	.4byte	0x24a
	.byte	0
	.uleb128 0xb
	.4byte	.LASF40
	.byte	0x6
	.byte	0x4c
	.4byte	0x24a
	.byte	0x80
	.uleb128 0x11
	.4byte	.LASF41
	.byte	0x6
	.byte	0x4e
	.4byte	0x11d
	.2byte	0x100
	.uleb128 0x11
	.4byte	.LASF42
	.byte	0x6
	.byte	0x51
	.4byte	0x11d
	.2byte	0x104
	.byte	0
	.uleb128 0x8
	.4byte	0x11b
	.4byte	0x25a
	.uleb128 0x9
	.4byte	0xdd
	.byte	0x1f
	.byte	0
	.uleb128 0x10
	.4byte	.LASF43
	.2byte	0x190
	.byte	0x6
	.byte	0x5d
	.4byte	0x298
	.uleb128 0xb
	.4byte	.LASF23
	.byte	0x6
	.byte	0x5e
	.4byte	0x298
	.byte	0
	.uleb128 0xb
	.4byte	.LASF44
	.byte	0x6
	.byte	0x5f
	.4byte	0x6c
	.byte	0x4
	.uleb128 0xb
	.4byte	.LASF45
	.byte	0x6
	.byte	0x61
	.4byte	0x29e
	.byte	0x8
	.uleb128 0xb
	.4byte	.LASF38
	.byte	0x6
	.byte	0x62
	.4byte	0x20a
	.byte	0x88
	.byte	0
	.uleb128 0xf
	.byte	0x4
	.4byte	0x25a
	.uleb128 0x8
	.4byte	0x2ae
	.4byte	0x2ae
	.uleb128 0x9
	.4byte	0xdd
	.byte	0x1f
	.byte	0
	.uleb128 0xf
	.byte	0x4
	.4byte	0x2b4
	.uleb128 0x12
	.byte	0x1
	.uleb128 0xd
	.4byte	.LASF46
	.byte	0x8
	.byte	0x6
	.byte	0x75
	.4byte	0x2db
	.uleb128 0xb
	.4byte	.LASF47
	.byte	0x6
	.byte	0x76
	.4byte	0x2db
	.byte	0
	.uleb128 0xb
	.4byte	.LASF48
	.byte	0x6
	.byte	0x77
	.4byte	0x6c
	.byte	0x4
	.byte	0
	.uleb128 0xf
	.byte	0x4
	.4byte	0x3b
	.uleb128 0xd
	.4byte	.LASF49
	.byte	0x68
	.byte	0x6
	.byte	0xb5
	.4byte	0x40b
	.uleb128 0xe
	.ascii	"_p\000"
	.byte	0x6
	.byte	0xb6
	.4byte	0x2db
	.byte	0
	.uleb128 0xe
	.ascii	"_r\000"
	.byte	0x6
	.byte	0xb7
	.4byte	0x6c
	.byte	0x4
	.uleb128 0xe
	.ascii	"_w\000"
	.byte	0x6
	.byte	0xb8
	.4byte	0x6c
	.byte	0x8
	.uleb128 0xb
	.4byte	.LASF50
	.byte	0x6
	.byte	0xb9
	.4byte	0x42
	.byte	0xc
	.uleb128 0xb
	.4byte	.LASF51
	.byte	0x6
	.byte	0xba
	.4byte	0x42
	.byte	0xe
	.uleb128 0xe
	.ascii	"_bf\000"
	.byte	0x6
	.byte	0xbb
	.4byte	0x2b6
	.byte	0x10
	.uleb128 0xb
	.4byte	.LASF52
	.byte	0x6
	.byte	0xbc
	.4byte	0x6c
	.byte	0x18
	.uleb128 0xb
	.4byte	.LASF53
	.byte	0x6
	.byte	0xc3
	.4byte	0x11b
	.byte	0x1c
	.uleb128 0xb
	.4byte	.LASF54
	.byte	0x6
	.byte	0xc5
	.4byte	0x579
	.byte	0x20
	.uleb128 0xb
	.4byte	.LASF55
	.byte	0x6
	.byte	0xc7
	.4byte	0x5a4
	.byte	0x24
	.uleb128 0xb
	.4byte	.LASF56
	.byte	0x6
	.byte	0xca
	.4byte	0x5c9
	.byte	0x28
	.uleb128 0xb
	.4byte	.LASF57
	.byte	0x6
	.byte	0xcb
	.4byte	0x5e4
	.byte	0x2c
	.uleb128 0xe
	.ascii	"_ub\000"
	.byte	0x6
	.byte	0xce
	.4byte	0x2b6
	.byte	0x30
	.uleb128 0xe
	.ascii	"_up\000"
	.byte	0x6
	.byte	0xcf
	.4byte	0x2db
	.byte	0x38
	.uleb128 0xe
	.ascii	"_ur\000"
	.byte	0x6
	.byte	0xd0
	.4byte	0x6c
	.byte	0x3c
	.uleb128 0xb
	.4byte	.LASF58
	.byte	0x6
	.byte	0xd3
	.4byte	0x5ea
	.byte	0x40
	.uleb128 0xb
	.4byte	.LASF59
	.byte	0x6
	.byte	0xd4
	.4byte	0x5fa
	.byte	0x43
	.uleb128 0xe
	.ascii	"_lb\000"
	.byte	0x6
	.byte	0xd7
	.4byte	0x2b6
	.byte	0x44
	.uleb128 0xb
	.4byte	.LASF60
	.byte	0x6
	.byte	0xda
	.4byte	0x6c
	.byte	0x4c
	.uleb128 0xb
	.4byte	.LASF61
	.byte	0x6
	.byte	0xdb
	.4byte	0x8c
	.byte	0x50
	.uleb128 0xb
	.4byte	.LASF62
	.byte	0x6
	.byte	0xde
	.4byte	0x42a
	.byte	0x54
	.uleb128 0xb
	.4byte	.LASF63
	.byte	0x6
	.byte	0xe2
	.4byte	0x110
	.byte	0x58
	.uleb128 0xb
	.4byte	.LASF64
	.byte	0x6
	.byte	0xe4
	.4byte	0x105
	.byte	0x5c
	.uleb128 0xb
	.4byte	.LASF65
	.byte	0x6
	.byte	0xe5
	.4byte	0x6c
	.byte	0x64
	.byte	0
	.uleb128 0x13
	.byte	0x1
	.4byte	0x6c
	.4byte	0x42a
	.uleb128 0x14
	.4byte	0x42a
	.uleb128 0x14
	.4byte	0x11b
	.uleb128 0x14
	.4byte	0x567
	.uleb128 0x14
	.4byte	0x6c
	.byte	0
	.uleb128 0xf
	.byte	0x4
	.4byte	0x435
	.uleb128 0x15
	.4byte	0x42a
	.uleb128 0x16
	.4byte	.LASF66
	.2byte	0x428
	.byte	0x6
	.2byte	0x239
	.4byte	0x567
	.uleb128 0x17
	.4byte	.LASF67
	.byte	0x6
	.2byte	0x23b
	.4byte	0x6c
	.byte	0
	.uleb128 0x17
	.4byte	.LASF68
	.byte	0x6
	.2byte	0x240
	.4byte	0x651
	.byte	0x4
	.uleb128 0x17
	.4byte	.LASF69
	.byte	0x6
	.2byte	0x240
	.4byte	0x651
	.byte	0x8
	.uleb128 0x17
	.4byte	.LASF70
	.byte	0x6
	.2byte	0x240
	.4byte	0x651
	.byte	0xc
	.uleb128 0x17
	.4byte	.LASF71
	.byte	0x6
	.2byte	0x242
	.4byte	0x6c
	.byte	0x10
	.uleb128 0x17
	.4byte	.LASF72
	.byte	0x6
	.2byte	0x243
	.4byte	0x833
	.byte	0x14
	.uleb128 0x17
	.4byte	.LASF73
	.byte	0x6
	.2byte	0x246
	.4byte	0x6c
	.byte	0x30
	.uleb128 0x17
	.4byte	.LASF74
	.byte	0x6
	.2byte	0x247
	.4byte	0x849
	.byte	0x34
	.uleb128 0x17
	.4byte	.LASF75
	.byte	0x6
	.2byte	0x249
	.4byte	0x6c
	.byte	0x38
	.uleb128 0x17
	.4byte	.LASF76
	.byte	0x6
	.2byte	0x24b
	.4byte	0x85b
	.byte	0x3c
	.uleb128 0x17
	.4byte	.LASF77
	.byte	0x6
	.2byte	0x24e
	.4byte	0x17b
	.byte	0x40
	.uleb128 0x17
	.4byte	.LASF78
	.byte	0x6
	.2byte	0x24f
	.4byte	0x6c
	.byte	0x44
	.uleb128 0x17
	.4byte	.LASF79
	.byte	0x6
	.2byte	0x250
	.4byte	0x17b
	.byte	0x48
	.uleb128 0x17
	.4byte	.LASF80
	.byte	0x6
	.2byte	0x251
	.4byte	0x861
	.byte	0x4c
	.uleb128 0x17
	.4byte	.LASF81
	.byte	0x6
	.2byte	0x254
	.4byte	0x6c
	.byte	0x50
	.uleb128 0x17
	.4byte	.LASF82
	.byte	0x6
	.2byte	0x255
	.4byte	0x567
	.byte	0x54
	.uleb128 0x17
	.4byte	.LASF83
	.byte	0x6
	.2byte	0x278
	.4byte	0x811
	.byte	0x58
	.uleb128 0x18
	.4byte	.LASF43
	.byte	0x6
	.2byte	0x27c
	.4byte	0x298
	.2byte	0x148
	.uleb128 0x18
	.4byte	.LASF84
	.byte	0x6
	.2byte	0x27d
	.4byte	0x25a
	.2byte	0x14c
	.uleb128 0x18
	.4byte	.LASF85
	.byte	0x6
	.2byte	0x281
	.4byte	0x873
	.2byte	0x2dc
	.uleb128 0x18
	.4byte	.LASF86
	.byte	0x6
	.2byte	0x286
	.4byte	0x616
	.2byte	0x2e0
	.uleb128 0x18
	.4byte	.LASF87
	.byte	0x6
	.2byte	0x287
	.4byte	0x87f
	.2byte	0x2ec
	.byte	0
	.uleb128 0xf
	.byte	0x4
	.4byte	0x56d
	.uleb128 0x2
	.byte	0x1
	.byte	0x8
	.4byte	.LASF88
	.uleb128 0x15
	.4byte	0x56d
	.uleb128 0xf
	.byte	0x4
	.4byte	0x40b
	.uleb128 0x13
	.byte	0x1
	.4byte	0x6c
	.4byte	0x59e
	.uleb128 0x14
	.4byte	0x42a
	.uleb128 0x14
	.4byte	0x11b
	.uleb128 0x14
	.4byte	0x59e
	.uleb128 0x14
	.4byte	0x6c
	.byte	0
	.uleb128 0xf
	.byte	0x4
	.4byte	0x574
	.uleb128 0xf
	.byte	0x4
	.4byte	0x57f
	.uleb128 0x13
	.byte	0x1
	.4byte	0x97
	.4byte	0x5c9
	.uleb128 0x14
	.4byte	0x42a
	.uleb128 0x14
	.4byte	0x11b
	.uleb128 0x14
	.4byte	0x97
	.uleb128 0x14
	.4byte	0x6c
	.byte	0
	.uleb128 0xf
	.byte	0x4
	.4byte	0x5aa
	.uleb128 0x13
	.byte	0x1
	.4byte	0x6c
	.4byte	0x5e4
	.uleb128 0x14
	.4byte	0x42a
	.uleb128 0x14
	.4byte	0x11b
	.byte	0
	.uleb128 0xf
	.byte	0x4
	.4byte	0x5cf
	.uleb128 0x8
	.4byte	0x3b
	.4byte	0x5fa
	.uleb128 0x9
	.4byte	0xdd
	.byte	0x2
	.byte	0
	.uleb128 0x8
	.4byte	0x3b
	.4byte	0x60a
	.uleb128 0x9
	.4byte	0xdd
	.byte	0
	.byte	0
	.uleb128 0x5
	.4byte	.LASF89
	.byte	0x6
	.2byte	0x11f
	.4byte	0x2e1
	.uleb128 0x19
	.4byte	.LASF90
	.byte	0xc
	.byte	0x6
	.2byte	0x123
	.4byte	0x64b
	.uleb128 0x17
	.4byte	.LASF23
	.byte	0x6
	.2byte	0x125
	.4byte	0x64b
	.byte	0
	.uleb128 0x17
	.4byte	.LASF91
	.byte	0x6
	.2byte	0x126
	.4byte	0x6c
	.byte	0x4
	.uleb128 0x17
	.4byte	.LASF92
	.byte	0x6
	.2byte	0x127
	.4byte	0x651
	.byte	0x8
	.byte	0
	.uleb128 0xf
	.byte	0x4
	.4byte	0x616
	.uleb128 0xf
	.byte	0x4
	.4byte	0x60a
	.uleb128 0x19
	.4byte	.LASF93
	.byte	0xe
	.byte	0x6
	.2byte	0x13f
	.4byte	0x68c
	.uleb128 0x17
	.4byte	.LASF94
	.byte	0x6
	.2byte	0x140
	.4byte	0x68c
	.byte	0
	.uleb128 0x17
	.4byte	.LASF95
	.byte	0x6
	.2byte	0x141
	.4byte	0x68c
	.byte	0x6
	.uleb128 0x17
	.4byte	.LASF96
	.byte	0x6
	.2byte	0x142
	.4byte	0x49
	.byte	0xc
	.byte	0
	.uleb128 0x8
	.4byte	0x49
	.4byte	0x69c
	.uleb128 0x9
	.4byte	0xdd
	.byte	0x2
	.byte	0
	.uleb128 0x1a
	.byte	0xd0
	.byte	0x6
	.2byte	0x259
	.4byte	0x79d
	.uleb128 0x17
	.4byte	.LASF97
	.byte	0x6
	.2byte	0x25b
	.4byte	0x73
	.byte	0
	.uleb128 0x17
	.4byte	.LASF98
	.byte	0x6
	.2byte	0x25c
	.4byte	0x567
	.byte	0x4
	.uleb128 0x17
	.4byte	.LASF99
	.byte	0x6
	.2byte	0x25d
	.4byte	0x79d
	.byte	0x8
	.uleb128 0x17
	.4byte	.LASF100
	.byte	0x6
	.2byte	0x25e
	.4byte	0x191
	.byte	0x24
	.uleb128 0x17
	.4byte	.LASF101
	.byte	0x6
	.2byte	0x25f
	.4byte	0x6c
	.byte	0x48
	.uleb128 0x17
	.4byte	.LASF102
	.byte	0x6
	.2byte	0x260
	.4byte	0x65
	.byte	0x50
	.uleb128 0x17
	.4byte	.LASF103
	.byte	0x6
	.2byte	0x261
	.4byte	0x657
	.byte	0x58
	.uleb128 0x17
	.4byte	.LASF104
	.byte	0x6
	.2byte	0x262
	.4byte	0x105
	.byte	0x68
	.uleb128 0x17
	.4byte	.LASF105
	.byte	0x6
	.2byte	0x263
	.4byte	0x105
	.byte	0x70
	.uleb128 0x17
	.4byte	.LASF106
	.byte	0x6
	.2byte	0x264
	.4byte	0x105
	.byte	0x78
	.uleb128 0x17
	.4byte	.LASF107
	.byte	0x6
	.2byte	0x265
	.4byte	0x7ad
	.byte	0x80
	.uleb128 0x17
	.4byte	.LASF108
	.byte	0x6
	.2byte	0x266
	.4byte	0x7bd
	.byte	0x88
	.uleb128 0x17
	.4byte	.LASF109
	.byte	0x6
	.2byte	0x267
	.4byte	0x6c
	.byte	0xa0
	.uleb128 0x17
	.4byte	.LASF110
	.byte	0x6
	.2byte	0x268
	.4byte	0x105
	.byte	0xa4
	.uleb128 0x17
	.4byte	.LASF111
	.byte	0x6
	.2byte	0x269
	.4byte	0x105
	.byte	0xac
	.uleb128 0x17
	.4byte	.LASF112
	.byte	0x6
	.2byte	0x26a
	.4byte	0x105
	.byte	0xb4
	.uleb128 0x17
	.4byte	.LASF113
	.byte	0x6
	.2byte	0x26b
	.4byte	0x105
	.byte	0xbc
	.uleb128 0x17
	.4byte	.LASF114
	.byte	0x6
	.2byte	0x26c
	.4byte	0x105
	.byte	0xc4
	.uleb128 0x17
	.4byte	.LASF115
	.byte	0x6
	.2byte	0x26d
	.4byte	0x6c
	.byte	0xcc
	.byte	0
	.uleb128 0x8
	.4byte	0x56d
	.4byte	0x7ad
	.uleb128 0x9
	.4byte	0xdd
	.byte	0x19
	.byte	0
	.uleb128 0x8
	.4byte	0x56d
	.4byte	0x7bd
	.uleb128 0x9
	.4byte	0xdd
	.byte	0x7
	.byte	0
	.uleb128 0x8
	.4byte	0x56d
	.4byte	0x7cd
	.uleb128 0x9
	.4byte	0xdd
	.byte	0x17
	.byte	0
	.uleb128 0x1a
	.byte	0xf0
	.byte	0x6
	.2byte	0x272
	.4byte	0x7f1
	.uleb128 0x17
	.4byte	.LASF116
	.byte	0x6
	.2byte	0x275
	.4byte	0x7f1
	.byte	0
	.uleb128 0x17
	.4byte	.LASF117
	.byte	0x6
	.2byte	0x276
	.4byte	0x801
	.byte	0x78
	.byte	0
	.uleb128 0x8
	.4byte	0x2db
	.4byte	0x801
	.uleb128 0x9
	.4byte	0xdd
	.byte	0x1d
	.byte	0
	.uleb128 0x8
	.4byte	0x73
	.4byte	0x811
	.uleb128 0x9
	.4byte	0xdd
	.byte	0x1d
	.byte	0
	.uleb128 0x1b
	.byte	0xf0
	.byte	0x6
	.2byte	0x257
	.4byte	0x833
	.uleb128 0x1c
	.4byte	.LASF66
	.byte	0x6
	.2byte	0x26e
	.4byte	0x69c
	.uleb128 0x1c
	.4byte	.LASF118
	.byte	0x6
	.2byte	0x277
	.4byte	0x7cd
	.byte	0
	.uleb128 0x8
	.4byte	0x56d
	.4byte	0x843
	.uleb128 0x9
	.4byte	0xdd
	.byte	0x18
	.byte	0
	.uleb128 0x1d
	.4byte	.LASF151
	.byte	0x1
	.uleb128 0xf
	.byte	0x4
	.4byte	0x843
	.uleb128 0x1e
	.byte	0x1
	.4byte	0x85b
	.uleb128 0x14
	.4byte	0x42a
	.byte	0
	.uleb128 0xf
	.byte	0x4
	.4byte	0x84f
	.uleb128 0xf
	.byte	0x4
	.4byte	0x17b
	.uleb128 0x1e
	.byte	0x1
	.4byte	0x873
	.uleb128 0x14
	.4byte	0x6c
	.byte	0
	.uleb128 0xf
	.byte	0x4
	.4byte	0x879
	.uleb128 0xf
	.byte	0x4
	.4byte	0x867
	.uleb128 0x8
	.4byte	0x60a
	.4byte	0x88f
	.uleb128 0x9
	.4byte	0xdd
	.byte	0x2
	.byte	0
	.uleb128 0x1f
	.4byte	.LASF119
	.byte	0x6
	.2byte	0x2fe
	.4byte	0x42a
	.byte	0x1
	.byte	0x1
	.uleb128 0x1f
	.4byte	.LASF120
	.byte	0x6
	.2byte	0x2ff
	.4byte	0x430
	.byte	0x1
	.byte	0x1
	.uleb128 0x3
	.4byte	.LASF121
	.byte	0x7
	.byte	0x18
	.4byte	0x30
	.uleb128 0x20
	.4byte	.LASF122
	.byte	0x8
	.byte	0x9a
	.4byte	0x50
	.byte	0x1
	.byte	0x1
	.uleb128 0x20
	.4byte	.LASF123
	.byte	0x8
	.byte	0x9b
	.4byte	0x6c
	.byte	0x1
	.byte	0x1
	.uleb128 0x8
	.4byte	0x567
	.4byte	0x8e0
	.uleb128 0x9
	.4byte	0xdd
	.byte	0x1
	.byte	0
	.uleb128 0x20
	.4byte	.LASF124
	.byte	0x8
	.byte	0x9e
	.4byte	0x8d0
	.byte	0x1
	.byte	0x1
	.uleb128 0x21
	.byte	0x1
	.4byte	0x3b
	.byte	0x9
	.byte	0x8a
	.4byte	0x906
	.uleb128 0x22
	.4byte	.LASF125
	.byte	0
	.uleb128 0x22
	.4byte	.LASF126
	.byte	0x1
	.byte	0
	.uleb128 0x3
	.4byte	.LASF127
	.byte	0x9
	.byte	0x91
	.4byte	0x8ed
	.uleb128 0x2
	.byte	0x1
	.byte	0x2
	.4byte	.LASF128
	.uleb128 0x8
	.4byte	0x8ab
	.4byte	0x928
	.uleb128 0x9
	.4byte	0xdd
	.byte	0x5
	.byte	0
	.uleb128 0x20
	.4byte	.LASF129
	.byte	0xa
	.byte	0x89
	.4byte	0x8ab
	.byte	0x1
	.byte	0x1
	.uleb128 0x21
	.byte	0x1
	.4byte	0x3b
	.byte	0xb
	.byte	0x7d
	.4byte	0x95a
	.uleb128 0x22
	.4byte	.LASF130
	.byte	0
	.uleb128 0x22
	.4byte	.LASF131
	.byte	0x1
	.uleb128 0x22
	.4byte	.LASF132
	.byte	0x2
	.uleb128 0x22
	.4byte	.LASF133
	.byte	0x3
	.byte	0
	.uleb128 0x3
	.4byte	.LASF134
	.byte	0xb
	.byte	0x82
	.4byte	0x935
	.uleb128 0x21
	.byte	0x1
	.4byte	0x3b
	.byte	0xc
	.byte	0x3a
	.4byte	0x984
	.uleb128 0x22
	.4byte	.LASF135
	.byte	0
	.uleb128 0x22
	.4byte	.LASF136
	.byte	0x1
	.uleb128 0x22
	.4byte	.LASF137
	.byte	0x2
	.byte	0
	.uleb128 0x3
	.4byte	.LASF138
	.byte	0xc
	.byte	0x3e
	.4byte	0x965
	.uleb128 0xa
	.byte	0x9
	.byte	0xd
	.byte	0x23
	.4byte	0x9c8
	.uleb128 0xb
	.4byte	.LASF139
	.byte	0xd
	.byte	0x25
	.4byte	0x95a
	.byte	0
	.uleb128 0xb
	.4byte	.LASF140
	.byte	0xd
	.byte	0x26
	.4byte	0x906
	.byte	0x1
	.uleb128 0xb
	.4byte	.LASF141
	.byte	0xd
	.byte	0x27
	.4byte	0x918
	.byte	0x2
	.uleb128 0xb
	.4byte	.LASF142
	.byte	0xd
	.byte	0x28
	.4byte	0x984
	.byte	0x8
	.byte	0
	.uleb128 0x3
	.4byte	.LASF143
	.byte	0xd
	.byte	0x29
	.4byte	0x98f
	.uleb128 0xa
	.byte	0x7
	.byte	0xd
	.byte	0x2f
	.4byte	0x9f4
	.uleb128 0xb
	.4byte	.LASF141
	.byte	0xd
	.byte	0x31
	.4byte	0x918
	.byte	0
	.uleb128 0xb
	.4byte	.LASF140
	.byte	0xd
	.byte	0x32
	.4byte	0x8ab
	.byte	0x6
	.byte	0
	.uleb128 0x3
	.4byte	.LASF144
	.byte	0xd
	.byte	0x33
	.4byte	0x9d3
	.uleb128 0x8
	.4byte	0x9c8
	.4byte	0xa0f
	.uleb128 0x9
	.4byte	0xdd
	.byte	0x1
	.byte	0
	.uleb128 0x20
	.4byte	.LASF145
	.byte	0xd
	.byte	0x46
	.4byte	0x9ff
	.byte	0x1
	.byte	0x1
	.uleb128 0x8
	.4byte	0x9f4
	.4byte	0xa2c
	.uleb128 0x9
	.4byte	0xdd
	.byte	0x5
	.byte	0
	.uleb128 0x20
	.4byte	.LASF146
	.byte	0xd
	.byte	0x47
	.4byte	0xa1c
	.byte	0x1
	.byte	0x1
	.uleb128 0x20
	.4byte	.LASF147
	.byte	0xd
	.byte	0x49
	.4byte	0x8ab
	.byte	0x1
	.byte	0x1
	.uleb128 0x23
	.4byte	0xa0f
	.byte	0x1
	.byte	0x24
	.byte	0x5
	.byte	0x3
	.4byte	ble_scatternet_app_link_table
	.uleb128 0x23
	.4byte	0xa2c
	.byte	0x1
	.byte	0x26
	.byte	0x5
	.byte	0x3
	.4byte	ble_scatternet_dev_list
	.uleb128 0x23
	.4byte	0xa39
	.byte	0x1
	.byte	0x27
	.byte	0x5
	.byte	0x3
	.4byte	ble_scatternet_dev_list_count
	.uleb128 0x24
	.byte	0x1
	.4byte	.LASF152
	.byte	0x1
	.byte	0x59
	.byte	0x1
	.4byte	.LFB1
	.4byte	.LFE1
	.byte	0x1
	.byte	0x9c
	.byte	0x1
	.uleb128 0x25
	.byte	0x1
	.4byte	.LASF153
	.byte	0x1
	.byte	0x38
	.byte	0x1
	.4byte	0x911
	.4byte	.LFB0
	.4byte	.LFE0
	.byte	0x1
	.byte	0x9c
	.byte	0x1
	.4byte	0xb66
	.uleb128 0x26
	.4byte	.LASF141
	.byte	0x1
	.byte	0x38
	.4byte	0xb66
	.4byte	.LLST0
	.uleb128 0x26
	.4byte	.LASF140
	.byte	0x1
	.byte	0x38
	.4byte	0x8ab
	.4byte	.LLST1
	.uleb128 0x27
	.4byte	.Ldebug_ranges0+0
	.uleb128 0x28
	.ascii	"i\000"
	.byte	0x1
	.byte	0x3d
	.4byte	0x8ab
	.4byte	.LLST2
	.uleb128 0x29
	.4byte	.LVL3
	.4byte	0xb6c
	.4byte	0xaec
	.uleb128 0x2a
	.byte	0x1
	.byte	0x50
	.byte	0x2
	.byte	0x75
	.sleb128 0
	.uleb128 0x2a
	.byte	0x1
	.byte	0x51
	.byte	0x2
	.byte	0x76
	.sleb128 0
	.uleb128 0x2a
	.byte	0x1
	.byte	0x52
	.byte	0x1
	.byte	0x36
	.byte	0
	.uleb128 0x29
	.4byte	.LVL5
	.4byte	0xb6c
	.4byte	0xb0b
	.uleb128 0x2a
	.byte	0x1
	.byte	0x50
	.byte	0x2
	.byte	0x75
	.sleb128 0
	.uleb128 0x2a
	.byte	0x1
	.byte	0x51
	.byte	0x2
	.byte	0x76
	.sleb128 7
	.uleb128 0x2a
	.byte	0x1
	.byte	0x52
	.byte	0x1
	.byte	0x36
	.byte	0
	.uleb128 0x29
	.4byte	.LVL7
	.4byte	0xb6c
	.4byte	0xb2a
	.uleb128 0x2a
	.byte	0x1
	.byte	0x50
	.byte	0x2
	.byte	0x75
	.sleb128 0
	.uleb128 0x2a
	.byte	0x1
	.byte	0x51
	.byte	0x2
	.byte	0x76
	.sleb128 14
	.uleb128 0x2a
	.byte	0x1
	.byte	0x52
	.byte	0x1
	.byte	0x36
	.byte	0
	.uleb128 0x29
	.4byte	.LVL9
	.4byte	0xb6c
	.4byte	0xb49
	.uleb128 0x2a
	.byte	0x1
	.byte	0x50
	.byte	0x2
	.byte	0x75
	.sleb128 0
	.uleb128 0x2a
	.byte	0x1
	.byte	0x51
	.byte	0x2
	.byte	0x76
	.sleb128 21
	.uleb128 0x2a
	.byte	0x1
	.byte	0x52
	.byte	0x1
	.byte	0x36
	.byte	0
	.uleb128 0x2b
	.4byte	.LVL11
	.4byte	0xb6c
	.uleb128 0x2a
	.byte	0x1
	.byte	0x50
	.byte	0x2
	.byte	0x75
	.sleb128 0
	.uleb128 0x2a
	.byte	0x1
	.byte	0x51
	.byte	0x2
	.byte	0x76
	.sleb128 28
	.uleb128 0x2a
	.byte	0x1
	.byte	0x52
	.byte	0x1
	.byte	0x36
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0xf
	.byte	0x4
	.4byte	0x8ab
	.uleb128 0x2c
	.byte	0x1
	.byte	0x1
	.4byte	.LASF154
	.4byte	.LASF154
	.byte	0xe
	.byte	0x1a
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
	.uleb128 0x22
	.uleb128 0x28
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1c
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x23
	.uleb128 0x34
	.byte	0
	.uleb128 0x47
	.uleb128 0x13
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x2
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0x24
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
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0xa
	.uleb128 0x2117
	.uleb128 0xc
	.byte	0
	.byte	0
	.uleb128 0x25
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
	.uleb128 0x26
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
	.uleb128 0x27
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x55
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x28
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
	.uleb128 0x29
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
	.uleb128 0x2a
	.uleb128 0x410a
	.byte	0
	.uleb128 0x2
	.uleb128 0xa
	.uleb128 0x2111
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0x2b
	.uleb128 0x4109
	.byte	0x1
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x31
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x2c
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
	.byte	0
	.section	.debug_loc,"",%progbits
.Ldebug_loc0:
.LLST0:
	.4byte	.LVL0
	.4byte	.LVL3-1
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL3-1
	.4byte	.LVL13
	.2byte	0x1
	.byte	0x55
	.4byte	.LVL13
	.4byte	.LVL14
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL14
	.4byte	.LVL15
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x50
	.byte	0x9f
	.4byte	.LVL15
	.4byte	.LVL16
	.2byte	0x1
	.byte	0x55
	.4byte	.LVL16
	.4byte	.LFE0
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x50
	.byte	0x9f
	.4byte	0
	.4byte	0
.LLST1:
	.4byte	.LVL0
	.4byte	.LVL2
	.2byte	0x1
	.byte	0x51
	.4byte	.LVL2
	.4byte	.LVL13
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x51
	.byte	0x9f
	.4byte	.LVL13
	.4byte	.LVL15
	.2byte	0x1
	.byte	0x51
	.4byte	.LVL15
	.4byte	.LFE0
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x51
	.byte	0x9f
	.4byte	0
	.4byte	0
.LLST2:
	.4byte	.LVL1
	.4byte	.LVL4
	.2byte	0x2
	.byte	0x30
	.byte	0x9f
	.4byte	.LVL4
	.4byte	.LVL6
	.2byte	0x2
	.byte	0x31
	.byte	0x9f
	.4byte	.LVL6
	.4byte	.LVL8
	.2byte	0x2
	.byte	0x32
	.byte	0x9f
	.4byte	.LVL8
	.4byte	.LVL10
	.2byte	0x2
	.byte	0x33
	.byte	0x9f
	.4byte	.LVL10
	.4byte	.LVL12
	.2byte	0x2
	.byte	0x34
	.byte	0x9f
	.4byte	0
	.4byte	0
	.section	.debug_aranges,"",%progbits
	.4byte	0x24
	.2byte	0x2
	.4byte	.Ldebug_info0
	.byte	0x4
	.byte	0
	.2byte	0
	.2byte	0
	.4byte	.LFB0
	.4byte	.LFE0-.LFB0
	.4byte	.LFB1
	.4byte	.LFE1-.LFB1
	.4byte	0
	.4byte	0
	.section	.debug_ranges,"",%progbits
.Ldebug_ranges0:
	.4byte	.LBB2
	.4byte	.LBE2
	.4byte	.LBB3
	.4byte	.LBE3
	.4byte	0
	.4byte	0
	.4byte	.LFB0
	.4byte	.LFE0
	.4byte	.LFB1
	.4byte	.LFE1
	.4byte	0
	.4byte	0
	.section	.debug_line,"",%progbits
.Ldebug_line0:
	.section	.debug_str,"MS",%progbits,1
.LASF127:
	.ascii	"T_GAP_REMOTE_ADDR_TYPE\000"
.LASF145:
	.ascii	"ble_scatternet_app_link_table\000"
.LASF148:
	.ascii	"GNU C11 6.5.0 -march=armv8-m.main+dsp -mthumb -mcms"
	.ascii	"e -mfloat-abi=soft -mabi=aapcs -g -gdwarf-3 -gdwarf"
	.ascii	"-3 -O3 -fstack-usage -fdata-sections -ffunction-sec"
	.ascii	"tions\000"
.LASF38:
	.ascii	"_on_exit_args\000"
.LASF55:
	.ascii	"_write\000"
.LASF123:
	.ascii	"_daylight\000"
.LASF106:
	.ascii	"_wctomb_state\000"
.LASF103:
	.ascii	"_r48\000"
.LASF108:
	.ascii	"_signal_buf\000"
.LASF8:
	.ascii	"unsigned int\000"
.LASF52:
	.ascii	"_lbfsize\000"
.LASF50:
	.ascii	"_flags\000"
.LASF67:
	.ascii	"_errno\000"
.LASF153:
	.ascii	"ble_scatternet_link_mgr_add_device\000"
.LASF11:
	.ascii	"_LOCK_RECURSIVE_T\000"
.LASF54:
	.ascii	"_read\000"
.LASF110:
	.ascii	"_mbrlen_state\000"
.LASF69:
	.ascii	"_stdout\000"
.LASF13:
	.ascii	"_fpos_t\000"
.LASF45:
	.ascii	"_fns\000"
.LASF53:
	.ascii	"_cookie\000"
.LASF27:
	.ascii	"_Bigint\000"
.LASF35:
	.ascii	"__tm_wday\000"
.LASF126:
	.ascii	"GAP_REMOTE_ADDR_LE_RANDOM\000"
.LASF150:
	.ascii	"/cygdrive/d/PUYA/HE3/sdk-ameba-v7.1d/project/realte"
	.ascii	"k_amebaz2_v0_example/GCC-RELEASE\000"
.LASF77:
	.ascii	"_result\000"
.LASF31:
	.ascii	"__tm_hour\000"
.LASF18:
	.ascii	"__count\000"
.LASF30:
	.ascii	"__tm_min\000"
.LASF119:
	.ascii	"_impure_ptr\000"
.LASF147:
	.ascii	"ble_scatternet_dev_list_count\000"
.LASF116:
	.ascii	"_nextf\000"
.LASF93:
	.ascii	"_rand48\000"
.LASF78:
	.ascii	"_result_k\000"
.LASF7:
	.ascii	"long long unsigned int\000"
.LASF99:
	.ascii	"_asctime_buf\000"
.LASF49:
	.ascii	"__sFILE\000"
.LASF26:
	.ascii	"_wds\000"
.LASF89:
	.ascii	"__FILE\000"
.LASF61:
	.ascii	"_offset\000"
.LASF72:
	.ascii	"_emergency\000"
.LASF154:
	.ascii	"memcmp\000"
.LASF29:
	.ascii	"__tm_sec\000"
.LASF139:
	.ascii	"conn_state\000"
.LASF36:
	.ascii	"__tm_yday\000"
.LASF71:
	.ascii	"_inc\000"
.LASF44:
	.ascii	"_ind\000"
.LASF144:
	.ascii	"T_DEV_INFO\000"
.LASF23:
	.ascii	"_next\000"
.LASF112:
	.ascii	"_mbsrtowcs_state\000"
.LASF124:
	.ascii	"_tzname\000"
.LASF19:
	.ascii	"__value\000"
.LASF79:
	.ascii	"_p5s\000"
.LASF114:
	.ascii	"_wcsrtombs_state\000"
.LASF104:
	.ascii	"_mblen_state\000"
.LASF88:
	.ascii	"char\000"
.LASF32:
	.ascii	"__tm_mday\000"
.LASF85:
	.ascii	"_sig_func\000"
.LASF111:
	.ascii	"_mbrtowc_state\000"
.LASF84:
	.ascii	"_atexit0\000"
.LASF130:
	.ascii	"GAP_CONN_STATE_DISCONNECTED\000"
.LASF146:
	.ascii	"ble_scatternet_dev_list\000"
.LASF152:
	.ascii	"ble_scatternet_link_mgr_clear_device_list\000"
.LASF21:
	.ascii	"_flock_t\000"
.LASF142:
	.ascii	"role\000"
.LASF15:
	.ascii	"__wch\000"
.LASF92:
	.ascii	"_iobs\000"
.LASF121:
	.ascii	"uint8_t\000"
.LASF57:
	.ascii	"_close\000"
.LASF138:
	.ascii	"T_GAP_ROLE\000"
.LASF75:
	.ascii	"__sdidinit\000"
.LASF122:
	.ascii	"_timezone\000"
.LASF136:
	.ascii	"GAP_LINK_ROLE_MASTER\000"
.LASF68:
	.ascii	"_stdin\000"
.LASF101:
	.ascii	"_gamma_signgam\000"
.LASF6:
	.ascii	"long long int\000"
.LASF47:
	.ascii	"_base\000"
.LASF80:
	.ascii	"_freelist\000"
.LASF95:
	.ascii	"_mult\000"
.LASF22:
	.ascii	"__ULong\000"
.LASF113:
	.ascii	"_wcrtomb_state\000"
.LASF51:
	.ascii	"_file\000"
.LASF135:
	.ascii	"GAP_LINK_ROLE_UNDEFINED\000"
.LASF137:
	.ascii	"GAP_LINK_ROLE_SLAVE\000"
.LASF131:
	.ascii	"GAP_CONN_STATE_CONNECTING\000"
.LASF76:
	.ascii	"__cleanup\000"
.LASF20:
	.ascii	"_mbstate_t\000"
.LASF37:
	.ascii	"__tm_isdst\000"
.LASF115:
	.ascii	"_h_errno\000"
.LASF128:
	.ascii	"_Bool\000"
.LASF33:
	.ascii	"__tm_mon\000"
.LASF9:
	.ascii	"long double\000"
.LASF149:
	.ascii	"../../../component/common/bluetooth/realtek/sdk/exa"
	.ascii	"mple/ble_scatternet/ble_scatternet_link_mgr.c\000"
.LASF43:
	.ascii	"_atexit\000"
.LASF64:
	.ascii	"_mbstate\000"
.LASF2:
	.ascii	"short int\000"
.LASF134:
	.ascii	"T_GAP_CONN_STATE\000"
.LASF4:
	.ascii	"long int\000"
.LASF87:
	.ascii	"__sf\000"
.LASF25:
	.ascii	"_sign\000"
.LASF62:
	.ascii	"_data\000"
.LASF16:
	.ascii	"__wchb\000"
.LASF120:
	.ascii	"_global_impure_ptr\000"
.LASF34:
	.ascii	"__tm_year\000"
.LASF100:
	.ascii	"_localtime_buf\000"
.LASF118:
	.ascii	"_unused\000"
.LASF10:
	.ascii	"__uint8_t\000"
.LASF83:
	.ascii	"_new\000"
.LASF81:
	.ascii	"_cvtlen\000"
.LASF24:
	.ascii	"_maxwds\000"
.LASF107:
	.ascii	"_l64a_buf\000"
.LASF60:
	.ascii	"_blksize\000"
.LASF28:
	.ascii	"__tm\000"
.LASF63:
	.ascii	"_lock\000"
.LASF125:
	.ascii	"GAP_REMOTE_ADDR_LE_PUBLIC\000"
.LASF133:
	.ascii	"GAP_CONN_STATE_DISCONNECTING\000"
.LASF17:
	.ascii	"sizetype\000"
.LASF5:
	.ascii	"long unsigned int\000"
.LASF91:
	.ascii	"_niobs\000"
.LASF14:
	.ascii	"wint_t\000"
.LASF40:
	.ascii	"_dso_handle\000"
.LASF82:
	.ascii	"_cvtbuf\000"
.LASF1:
	.ascii	"unsigned char\000"
.LASF109:
	.ascii	"_getdate_err\000"
.LASF141:
	.ascii	"bd_addr\000"
.LASF96:
	.ascii	"_add\000"
.LASF46:
	.ascii	"__sbuf\000"
.LASF90:
	.ascii	"_glue\000"
.LASF132:
	.ascii	"GAP_CONN_STATE_CONNECTED\000"
.LASF129:
	.ascii	"bond_storage_num\000"
.LASF86:
	.ascii	"__sglue\000"
.LASF98:
	.ascii	"_strtok_last\000"
.LASF105:
	.ascii	"_mbtowc_state\000"
.LASF74:
	.ascii	"_locale\000"
.LASF39:
	.ascii	"_fnargs\000"
.LASF0:
	.ascii	"signed char\000"
.LASF66:
	.ascii	"_reent\000"
.LASF3:
	.ascii	"short unsigned int\000"
.LASF41:
	.ascii	"_fntypes\000"
.LASF48:
	.ascii	"_size\000"
.LASF12:
	.ascii	"_off_t\000"
.LASF59:
	.ascii	"_nbuf\000"
.LASF97:
	.ascii	"_unused_rand\000"
.LASF73:
	.ascii	"_unspecified_locale_info\000"
.LASF65:
	.ascii	"_flags2\000"
.LASF42:
	.ascii	"_is_cxa\000"
.LASF143:
	.ascii	"T_APP_LINK\000"
.LASF140:
	.ascii	"bd_type\000"
.LASF94:
	.ascii	"_seed\000"
.LASF102:
	.ascii	"_rand_next\000"
.LASF151:
	.ascii	"__locale_t\000"
.LASF56:
	.ascii	"_seek\000"
.LASF70:
	.ascii	"_stderr\000"
.LASF117:
	.ascii	"_nmalloc\000"
.LASF58:
	.ascii	"_ubuf\000"
	.ident	"GCC: (Realtek ASDK-6.5.0 Build 3215) 6.5.0"
