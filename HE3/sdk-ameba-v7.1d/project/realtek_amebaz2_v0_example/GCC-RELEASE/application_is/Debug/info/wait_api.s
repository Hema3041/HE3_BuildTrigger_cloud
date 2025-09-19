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
	.file	"wait_api.c"
	.text
.Ltext0:
	.cfi_sections	.debug_frame
	.global	__aeabi_fmul
	.global	__aeabi_f2iz
	.section	.text.wait,"ax",%progbits
	.align	1
	.p2align 2,,3
	.global	wait
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	wait, %function
wait:
.LFB0:
	.file 1 "../../../component/common/mbed/targets/hal/rtl8710c/wait_api.c"
	.loc 1 20 0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
.LVL0:
	push	{r3, r4, r5, lr}
	.cfi_def_cfa_offset 16
	.cfi_offset 3, -16
	.cfi_offset 4, -12
	.cfi_offset 5, -8
	.cfi_offset 14, -4
	.loc 1 20 0
	mov	r4, r0
.LVL1:
.LBB4:
.LBB5:
	.loc 1 31 0
	bl	us_ticker_read
.LVL2:
.LBE5:
.LBE4:
	.loc 1 21 0
	ldr	r1, .L6
.LBB8:
.LBB6:
	.loc 1 31 0
	mov	r5, r0
.LVL3:
.LBE6:
.LBE8:
	.loc 1 21 0
	mov	r0, r4
.LVL4:
	bl	__aeabi_fmul
.LVL5:
	bl	__aeabi_f2iz
.LVL6:
	mov	r4, r0
.LVL7:
.L2:
.LBB9:
.LBB7:
	.loc 1 33 0
	bl	us_ticker_read
.LVL8:
	subs	r0, r0, r5
	cmp	r4, r0
	bhi	.L2
.LBE7:
.LBE9:
	.loc 1 22 0
	pop	{r3, r4, r5, pc}
.LVL9:
.L7:
	.align	2
.L6:
	.word	1232348160
	.cfi_endproc
.LFE0:
	.size	wait, .-wait
	.section	.text.wait_ms,"ax",%progbits
	.align	1
	.p2align 2,,3
	.global	wait_ms
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	wait_ms, %function
wait_ms:
.LFB1:
	.loc 1 25 0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
.LVL10:
	push	{r4, r5, r6, lr}
	.cfi_def_cfa_offset 16
	.cfi_offset 4, -16
	.cfi_offset 5, -12
	.cfi_offset 6, -8
	.cfi_offset 14, -4
	.loc 1 25 0
	mov	r6, r0
.LVL11:
.LBB12:
.LBB13:
	.loc 1 31 0
	bl	us_ticker_read
.LVL12:
.LBE13:
.LBE12:
	.loc 1 26 0
	mov	r4, #1000
.LBB16:
.LBB14:
	.loc 1 31 0
	mov	r5, r0
.LVL13:
.LBE14:
.LBE16:
	.loc 1 26 0
	mul	r4, r4, r6
.LVL14:
.L9:
.LBB17:
.LBB15:
	.loc 1 33 0
	bl	us_ticker_read
.LVL15:
	subs	r0, r0, r5
	cmp	r4, r0
	bhi	.L9
.LBE15:
.LBE17:
	.loc 1 27 0
	pop	{r4, r5, r6, pc}
	.cfi_endproc
.LFE1:
	.size	wait_ms, .-wait_ms
	.section	.text.wait_us,"ax",%progbits
	.align	1
	.p2align 2,,3
	.global	wait_us
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	wait_us, %function
wait_us:
.LFB2:
	.loc 1 30 0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
.LVL16:
	push	{r3, r4, r5, lr}
	.cfi_def_cfa_offset 16
	.cfi_offset 3, -16
	.cfi_offset 4, -12
	.cfi_offset 5, -8
	.cfi_offset 14, -4
	.loc 1 30 0
	mov	r5, r0
	.loc 1 31 0
	bl	us_ticker_read
.LVL17:
	mov	r4, r0
.LVL18:
.L13:
	.loc 1 33 0 discriminator 1
	bl	us_ticker_read
.LVL19:
	subs	r0, r0, r4
	cmp	r0, r5
	bcc	.L13
	.loc 1 34 0
	pop	{r3, r4, r5, pc}
	.cfi_endproc
.LFE2:
	.size	wait_us, .-wait_us
	.text
.Letext0:
	.file 2 "/cygdrive/d/PUYA/HE3/sdk-ameba-v7.1d/tools/arm-none-eabi-gcc/asdk/cygwin/newlib/arm-none-eabi/include/machine/_default_types.h"
	.file 3 "/cygdrive/d/PUYA/HE3/sdk-ameba-v7.1d/tools/arm-none-eabi-gcc/asdk/cygwin/newlib/arm-none-eabi/include/sys/lock.h"
	.file 4 "/cygdrive/d/PUYA/HE3/sdk-ameba-v7.1d/tools/arm-none-eabi-gcc/asdk/cygwin/newlib/arm-none-eabi/include/sys/_types.h"
	.file 5 "/cygdrive/d/PUYA/HE3/sdk-ameba-v7.1d/tools/arm-none-eabi-gcc/asdk/cygwin/newlib/lib/gcc/arm-none-eabi/6.5.0/include/stddef.h"
	.file 6 "/cygdrive/d/PUYA/HE3/sdk-ameba-v7.1d/tools/arm-none-eabi-gcc/asdk/cygwin/newlib/arm-none-eabi/include/sys/reent.h"
	.file 7 "/cygdrive/d/PUYA/HE3/sdk-ameba-v7.1d/tools/arm-none-eabi-gcc/asdk/cygwin/newlib/arm-none-eabi/include/sys/_stdint.h"
	.file 8 "/cygdrive/d/PUYA/HE3/sdk-ameba-v7.1d/tools/arm-none-eabi-gcc/asdk/cygwin/newlib/arm-none-eabi/include/time.h"
	.file 9 "../../../component/common/mbed/hal/us_ticker_api.h"
	.section	.debug_info,"",%progbits
.Ldebug_info0:
	.4byte	0xa1a
	.2byte	0x3
	.4byte	.Ldebug_abbrev0
	.byte	0x4
	.uleb128 0x1
	.4byte	.LASF128
	.byte	0xc
	.4byte	.LASF129
	.4byte	.LASF130
	.4byte	.Ldebug_ranges0+0x40
	.4byte	0
	.4byte	0
	.4byte	.Ldebug_line0
	.uleb128 0x2
	.byte	0x4
	.byte	0x4
	.4byte	.LASF0
	.uleb128 0x3
	.byte	0x4
	.byte	0x5
	.ascii	"int\000"
	.uleb128 0x2
	.byte	0x1
	.byte	0x6
	.4byte	.LASF1
	.uleb128 0x2
	.byte	0x1
	.byte	0x8
	.4byte	.LASF2
	.uleb128 0x2
	.byte	0x2
	.byte	0x5
	.4byte	.LASF3
	.uleb128 0x2
	.byte	0x2
	.byte	0x7
	.4byte	.LASF4
	.uleb128 0x2
	.byte	0x4
	.byte	0x5
	.4byte	.LASF5
	.uleb128 0x4
	.4byte	.LASF11
	.byte	0x2
	.byte	0x4f
	.4byte	0x65
	.uleb128 0x2
	.byte	0x4
	.byte	0x7
	.4byte	.LASF6
	.uleb128 0x2
	.byte	0x8
	.byte	0x5
	.4byte	.LASF7
	.uleb128 0x2
	.byte	0x8
	.byte	0x7
	.4byte	.LASF8
	.uleb128 0x2
	.byte	0x4
	.byte	0x7
	.4byte	.LASF9
	.uleb128 0x2
	.byte	0x8
	.byte	0x4
	.4byte	.LASF10
	.uleb128 0x4
	.4byte	.LASF12
	.byte	0x3
	.byte	0x7
	.4byte	0x30
	.uleb128 0x4
	.4byte	.LASF13
	.byte	0x4
	.byte	0x2c
	.4byte	0x53
	.uleb128 0x4
	.4byte	.LASF14
	.byte	0x4
	.byte	0x72
	.4byte	0x53
	.uleb128 0x5
	.4byte	.LASF15
	.byte	0x5
	.2byte	0x165
	.4byte	0x7a
	.uleb128 0x6
	.byte	0x4
	.byte	0x4
	.byte	0xa6
	.4byte	0xd4
	.uleb128 0x7
	.4byte	.LASF16
	.byte	0x4
	.byte	0xa8
	.4byte	0xa9
	.uleb128 0x7
	.4byte	.LASF17
	.byte	0x4
	.byte	0xa9
	.4byte	0xd4
	.byte	0
	.uleb128 0x8
	.4byte	0x3e
	.4byte	0xe4
	.uleb128 0x9
	.4byte	0xe4
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
	.4byte	0x10c
	.uleb128 0xb
	.4byte	.LASF19
	.byte	0x4
	.byte	0xa5
	.4byte	0x30
	.byte	0
	.uleb128 0xb
	.4byte	.LASF20
	.byte	0x4
	.byte	0xaa
	.4byte	0xb5
	.byte	0x4
	.byte	0
	.uleb128 0x4
	.4byte	.LASF21
	.byte	0x4
	.byte	0xab
	.4byte	0xeb
	.uleb128 0x4
	.4byte	.LASF22
	.byte	0x4
	.byte	0xaf
	.4byte	0x88
	.uleb128 0xc
	.byte	0x4
	.uleb128 0x4
	.4byte	.LASF23
	.byte	0x6
	.byte	0x16
	.4byte	0x65
	.uleb128 0xd
	.4byte	.LASF28
	.byte	0x18
	.byte	0x6
	.byte	0x2f
	.4byte	0x182
	.uleb128 0xb
	.4byte	.LASF24
	.byte	0x6
	.byte	0x31
	.4byte	0x182
	.byte	0
	.uleb128 0xe
	.ascii	"_k\000"
	.byte	0x6
	.byte	0x32
	.4byte	0x30
	.byte	0x4
	.uleb128 0xb
	.4byte	.LASF25
	.byte	0x6
	.byte	0x32
	.4byte	0x30
	.byte	0x8
	.uleb128 0xb
	.4byte	.LASF26
	.byte	0x6
	.byte	0x32
	.4byte	0x30
	.byte	0xc
	.uleb128 0xb
	.4byte	.LASF27
	.byte	0x6
	.byte	0x32
	.4byte	0x30
	.byte	0x10
	.uleb128 0xe
	.ascii	"_x\000"
	.byte	0x6
	.byte	0x33
	.4byte	0x188
	.byte	0x14
	.byte	0
	.uleb128 0xf
	.byte	0x4
	.4byte	0x12f
	.uleb128 0x8
	.4byte	0x124
	.4byte	0x198
	.uleb128 0x9
	.4byte	0xe4
	.byte	0
	.byte	0
	.uleb128 0xd
	.4byte	.LASF29
	.byte	0x24
	.byte	0x6
	.byte	0x37
	.4byte	0x211
	.uleb128 0xb
	.4byte	.LASF30
	.byte	0x6
	.byte	0x39
	.4byte	0x30
	.byte	0
	.uleb128 0xb
	.4byte	.LASF31
	.byte	0x6
	.byte	0x3a
	.4byte	0x30
	.byte	0x4
	.uleb128 0xb
	.4byte	.LASF32
	.byte	0x6
	.byte	0x3b
	.4byte	0x30
	.byte	0x8
	.uleb128 0xb
	.4byte	.LASF33
	.byte	0x6
	.byte	0x3c
	.4byte	0x30
	.byte	0xc
	.uleb128 0xb
	.4byte	.LASF34
	.byte	0x6
	.byte	0x3d
	.4byte	0x30
	.byte	0x10
	.uleb128 0xb
	.4byte	.LASF35
	.byte	0x6
	.byte	0x3e
	.4byte	0x30
	.byte	0x14
	.uleb128 0xb
	.4byte	.LASF36
	.byte	0x6
	.byte	0x3f
	.4byte	0x30
	.byte	0x18
	.uleb128 0xb
	.4byte	.LASF37
	.byte	0x6
	.byte	0x40
	.4byte	0x30
	.byte	0x1c
	.uleb128 0xb
	.4byte	.LASF38
	.byte	0x6
	.byte	0x41
	.4byte	0x30
	.byte	0x20
	.byte	0
	.uleb128 0x10
	.4byte	.LASF39
	.2byte	0x108
	.byte	0x6
	.byte	0x4a
	.4byte	0x251
	.uleb128 0xb
	.4byte	.LASF40
	.byte	0x6
	.byte	0x4b
	.4byte	0x251
	.byte	0
	.uleb128 0xb
	.4byte	.LASF41
	.byte	0x6
	.byte	0x4c
	.4byte	0x251
	.byte	0x80
	.uleb128 0x11
	.4byte	.LASF42
	.byte	0x6
	.byte	0x4e
	.4byte	0x124
	.2byte	0x100
	.uleb128 0x11
	.4byte	.LASF43
	.byte	0x6
	.byte	0x51
	.4byte	0x124
	.2byte	0x104
	.byte	0
	.uleb128 0x8
	.4byte	0x122
	.4byte	0x261
	.uleb128 0x9
	.4byte	0xe4
	.byte	0x1f
	.byte	0
	.uleb128 0x10
	.4byte	.LASF44
	.2byte	0x190
	.byte	0x6
	.byte	0x5d
	.4byte	0x29f
	.uleb128 0xb
	.4byte	.LASF24
	.byte	0x6
	.byte	0x5e
	.4byte	0x29f
	.byte	0
	.uleb128 0xb
	.4byte	.LASF45
	.byte	0x6
	.byte	0x5f
	.4byte	0x30
	.byte	0x4
	.uleb128 0xb
	.4byte	.LASF46
	.byte	0x6
	.byte	0x61
	.4byte	0x2a5
	.byte	0x8
	.uleb128 0xb
	.4byte	.LASF39
	.byte	0x6
	.byte	0x62
	.4byte	0x211
	.byte	0x88
	.byte	0
	.uleb128 0xf
	.byte	0x4
	.4byte	0x261
	.uleb128 0x8
	.4byte	0x2b5
	.4byte	0x2b5
	.uleb128 0x9
	.4byte	0xe4
	.byte	0x1f
	.byte	0
	.uleb128 0xf
	.byte	0x4
	.4byte	0x2bb
	.uleb128 0x12
	.byte	0x1
	.uleb128 0xd
	.4byte	.LASF47
	.byte	0x8
	.byte	0x6
	.byte	0x75
	.4byte	0x2e2
	.uleb128 0xb
	.4byte	.LASF48
	.byte	0x6
	.byte	0x76
	.4byte	0x2e2
	.byte	0
	.uleb128 0xb
	.4byte	.LASF49
	.byte	0x6
	.byte	0x77
	.4byte	0x30
	.byte	0x4
	.byte	0
	.uleb128 0xf
	.byte	0x4
	.4byte	0x3e
	.uleb128 0xd
	.4byte	.LASF50
	.byte	0x68
	.byte	0x6
	.byte	0xb5
	.4byte	0x412
	.uleb128 0xe
	.ascii	"_p\000"
	.byte	0x6
	.byte	0xb6
	.4byte	0x2e2
	.byte	0
	.uleb128 0xe
	.ascii	"_r\000"
	.byte	0x6
	.byte	0xb7
	.4byte	0x30
	.byte	0x4
	.uleb128 0xe
	.ascii	"_w\000"
	.byte	0x6
	.byte	0xb8
	.4byte	0x30
	.byte	0x8
	.uleb128 0xb
	.4byte	.LASF51
	.byte	0x6
	.byte	0xb9
	.4byte	0x45
	.byte	0xc
	.uleb128 0xb
	.4byte	.LASF52
	.byte	0x6
	.byte	0xba
	.4byte	0x45
	.byte	0xe
	.uleb128 0xe
	.ascii	"_bf\000"
	.byte	0x6
	.byte	0xbb
	.4byte	0x2bd
	.byte	0x10
	.uleb128 0xb
	.4byte	.LASF53
	.byte	0x6
	.byte	0xbc
	.4byte	0x30
	.byte	0x18
	.uleb128 0xb
	.4byte	.LASF54
	.byte	0x6
	.byte	0xc3
	.4byte	0x122
	.byte	0x1c
	.uleb128 0xb
	.4byte	.LASF55
	.byte	0x6
	.byte	0xc5
	.4byte	0x580
	.byte	0x20
	.uleb128 0xb
	.4byte	.LASF56
	.byte	0x6
	.byte	0xc7
	.4byte	0x5ab
	.byte	0x24
	.uleb128 0xb
	.4byte	.LASF57
	.byte	0x6
	.byte	0xca
	.4byte	0x5d0
	.byte	0x28
	.uleb128 0xb
	.4byte	.LASF58
	.byte	0x6
	.byte	0xcb
	.4byte	0x5eb
	.byte	0x2c
	.uleb128 0xe
	.ascii	"_ub\000"
	.byte	0x6
	.byte	0xce
	.4byte	0x2bd
	.byte	0x30
	.uleb128 0xe
	.ascii	"_up\000"
	.byte	0x6
	.byte	0xcf
	.4byte	0x2e2
	.byte	0x38
	.uleb128 0xe
	.ascii	"_ur\000"
	.byte	0x6
	.byte	0xd0
	.4byte	0x30
	.byte	0x3c
	.uleb128 0xb
	.4byte	.LASF59
	.byte	0x6
	.byte	0xd3
	.4byte	0x5f1
	.byte	0x40
	.uleb128 0xb
	.4byte	.LASF60
	.byte	0x6
	.byte	0xd4
	.4byte	0x601
	.byte	0x43
	.uleb128 0xe
	.ascii	"_lb\000"
	.byte	0x6
	.byte	0xd7
	.4byte	0x2bd
	.byte	0x44
	.uleb128 0xb
	.4byte	.LASF61
	.byte	0x6
	.byte	0xda
	.4byte	0x30
	.byte	0x4c
	.uleb128 0xb
	.4byte	.LASF62
	.byte	0x6
	.byte	0xdb
	.4byte	0x93
	.byte	0x50
	.uleb128 0xb
	.4byte	.LASF63
	.byte	0x6
	.byte	0xde
	.4byte	0x431
	.byte	0x54
	.uleb128 0xb
	.4byte	.LASF64
	.byte	0x6
	.byte	0xe2
	.4byte	0x117
	.byte	0x58
	.uleb128 0xb
	.4byte	.LASF65
	.byte	0x6
	.byte	0xe4
	.4byte	0x10c
	.byte	0x5c
	.uleb128 0xb
	.4byte	.LASF66
	.byte	0x6
	.byte	0xe5
	.4byte	0x30
	.byte	0x64
	.byte	0
	.uleb128 0x13
	.byte	0x1
	.4byte	0x30
	.4byte	0x431
	.uleb128 0x14
	.4byte	0x431
	.uleb128 0x14
	.4byte	0x122
	.uleb128 0x14
	.4byte	0x56e
	.uleb128 0x14
	.4byte	0x30
	.byte	0
	.uleb128 0xf
	.byte	0x4
	.4byte	0x43c
	.uleb128 0x15
	.4byte	0x431
	.uleb128 0x16
	.4byte	.LASF67
	.2byte	0x428
	.byte	0x6
	.2byte	0x239
	.4byte	0x56e
	.uleb128 0x17
	.4byte	.LASF68
	.byte	0x6
	.2byte	0x23b
	.4byte	0x30
	.byte	0
	.uleb128 0x17
	.4byte	.LASF69
	.byte	0x6
	.2byte	0x240
	.4byte	0x658
	.byte	0x4
	.uleb128 0x17
	.4byte	.LASF70
	.byte	0x6
	.2byte	0x240
	.4byte	0x658
	.byte	0x8
	.uleb128 0x17
	.4byte	.LASF71
	.byte	0x6
	.2byte	0x240
	.4byte	0x658
	.byte	0xc
	.uleb128 0x17
	.4byte	.LASF72
	.byte	0x6
	.2byte	0x242
	.4byte	0x30
	.byte	0x10
	.uleb128 0x17
	.4byte	.LASF73
	.byte	0x6
	.2byte	0x243
	.4byte	0x83a
	.byte	0x14
	.uleb128 0x17
	.4byte	.LASF74
	.byte	0x6
	.2byte	0x246
	.4byte	0x30
	.byte	0x30
	.uleb128 0x17
	.4byte	.LASF75
	.byte	0x6
	.2byte	0x247
	.4byte	0x850
	.byte	0x34
	.uleb128 0x17
	.4byte	.LASF76
	.byte	0x6
	.2byte	0x249
	.4byte	0x30
	.byte	0x38
	.uleb128 0x17
	.4byte	.LASF77
	.byte	0x6
	.2byte	0x24b
	.4byte	0x862
	.byte	0x3c
	.uleb128 0x17
	.4byte	.LASF78
	.byte	0x6
	.2byte	0x24e
	.4byte	0x182
	.byte	0x40
	.uleb128 0x17
	.4byte	.LASF79
	.byte	0x6
	.2byte	0x24f
	.4byte	0x30
	.byte	0x44
	.uleb128 0x17
	.4byte	.LASF80
	.byte	0x6
	.2byte	0x250
	.4byte	0x182
	.byte	0x48
	.uleb128 0x17
	.4byte	.LASF81
	.byte	0x6
	.2byte	0x251
	.4byte	0x868
	.byte	0x4c
	.uleb128 0x17
	.4byte	.LASF82
	.byte	0x6
	.2byte	0x254
	.4byte	0x30
	.byte	0x50
	.uleb128 0x17
	.4byte	.LASF83
	.byte	0x6
	.2byte	0x255
	.4byte	0x56e
	.byte	0x54
	.uleb128 0x17
	.4byte	.LASF84
	.byte	0x6
	.2byte	0x278
	.4byte	0x818
	.byte	0x58
	.uleb128 0x18
	.4byte	.LASF44
	.byte	0x6
	.2byte	0x27c
	.4byte	0x29f
	.2byte	0x148
	.uleb128 0x18
	.4byte	.LASF85
	.byte	0x6
	.2byte	0x27d
	.4byte	0x261
	.2byte	0x14c
	.uleb128 0x18
	.4byte	.LASF86
	.byte	0x6
	.2byte	0x281
	.4byte	0x87a
	.2byte	0x2dc
	.uleb128 0x18
	.4byte	.LASF87
	.byte	0x6
	.2byte	0x286
	.4byte	0x61d
	.2byte	0x2e0
	.uleb128 0x18
	.4byte	.LASF88
	.byte	0x6
	.2byte	0x287
	.4byte	0x886
	.2byte	0x2ec
	.byte	0
	.uleb128 0xf
	.byte	0x4
	.4byte	0x574
	.uleb128 0x2
	.byte	0x1
	.byte	0x8
	.4byte	.LASF89
	.uleb128 0x15
	.4byte	0x574
	.uleb128 0xf
	.byte	0x4
	.4byte	0x412
	.uleb128 0x13
	.byte	0x1
	.4byte	0x30
	.4byte	0x5a5
	.uleb128 0x14
	.4byte	0x431
	.uleb128 0x14
	.4byte	0x122
	.uleb128 0x14
	.4byte	0x5a5
	.uleb128 0x14
	.4byte	0x30
	.byte	0
	.uleb128 0xf
	.byte	0x4
	.4byte	0x57b
	.uleb128 0xf
	.byte	0x4
	.4byte	0x586
	.uleb128 0x13
	.byte	0x1
	.4byte	0x9e
	.4byte	0x5d0
	.uleb128 0x14
	.4byte	0x431
	.uleb128 0x14
	.4byte	0x122
	.uleb128 0x14
	.4byte	0x9e
	.uleb128 0x14
	.4byte	0x30
	.byte	0
	.uleb128 0xf
	.byte	0x4
	.4byte	0x5b1
	.uleb128 0x13
	.byte	0x1
	.4byte	0x30
	.4byte	0x5eb
	.uleb128 0x14
	.4byte	0x431
	.uleb128 0x14
	.4byte	0x122
	.byte	0
	.uleb128 0xf
	.byte	0x4
	.4byte	0x5d6
	.uleb128 0x8
	.4byte	0x3e
	.4byte	0x601
	.uleb128 0x9
	.4byte	0xe4
	.byte	0x2
	.byte	0
	.uleb128 0x8
	.4byte	0x3e
	.4byte	0x611
	.uleb128 0x9
	.4byte	0xe4
	.byte	0
	.byte	0
	.uleb128 0x5
	.4byte	.LASF90
	.byte	0x6
	.2byte	0x11f
	.4byte	0x2e8
	.uleb128 0x19
	.4byte	.LASF91
	.byte	0xc
	.byte	0x6
	.2byte	0x123
	.4byte	0x652
	.uleb128 0x17
	.4byte	.LASF24
	.byte	0x6
	.2byte	0x125
	.4byte	0x652
	.byte	0
	.uleb128 0x17
	.4byte	.LASF92
	.byte	0x6
	.2byte	0x126
	.4byte	0x30
	.byte	0x4
	.uleb128 0x17
	.4byte	.LASF93
	.byte	0x6
	.2byte	0x127
	.4byte	0x658
	.byte	0x8
	.byte	0
	.uleb128 0xf
	.byte	0x4
	.4byte	0x61d
	.uleb128 0xf
	.byte	0x4
	.4byte	0x611
	.uleb128 0x19
	.4byte	.LASF94
	.byte	0xe
	.byte	0x6
	.2byte	0x13f
	.4byte	0x693
	.uleb128 0x17
	.4byte	.LASF95
	.byte	0x6
	.2byte	0x140
	.4byte	0x693
	.byte	0
	.uleb128 0x17
	.4byte	.LASF96
	.byte	0x6
	.2byte	0x141
	.4byte	0x693
	.byte	0x6
	.uleb128 0x17
	.4byte	.LASF97
	.byte	0x6
	.2byte	0x142
	.4byte	0x4c
	.byte	0xc
	.byte	0
	.uleb128 0x8
	.4byte	0x4c
	.4byte	0x6a3
	.uleb128 0x9
	.4byte	0xe4
	.byte	0x2
	.byte	0
	.uleb128 0x1a
	.byte	0xd0
	.byte	0x6
	.2byte	0x259
	.4byte	0x7a4
	.uleb128 0x17
	.4byte	.LASF98
	.byte	0x6
	.2byte	0x25b
	.4byte	0x7a
	.byte	0
	.uleb128 0x17
	.4byte	.LASF99
	.byte	0x6
	.2byte	0x25c
	.4byte	0x56e
	.byte	0x4
	.uleb128 0x17
	.4byte	.LASF100
	.byte	0x6
	.2byte	0x25d
	.4byte	0x7a4
	.byte	0x8
	.uleb128 0x17
	.4byte	.LASF101
	.byte	0x6
	.2byte	0x25e
	.4byte	0x198
	.byte	0x24
	.uleb128 0x17
	.4byte	.LASF102
	.byte	0x6
	.2byte	0x25f
	.4byte	0x30
	.byte	0x48
	.uleb128 0x17
	.4byte	.LASF103
	.byte	0x6
	.2byte	0x260
	.4byte	0x73
	.byte	0x50
	.uleb128 0x17
	.4byte	.LASF104
	.byte	0x6
	.2byte	0x261
	.4byte	0x65e
	.byte	0x58
	.uleb128 0x17
	.4byte	.LASF105
	.byte	0x6
	.2byte	0x262
	.4byte	0x10c
	.byte	0x68
	.uleb128 0x17
	.4byte	.LASF106
	.byte	0x6
	.2byte	0x263
	.4byte	0x10c
	.byte	0x70
	.uleb128 0x17
	.4byte	.LASF107
	.byte	0x6
	.2byte	0x264
	.4byte	0x10c
	.byte	0x78
	.uleb128 0x17
	.4byte	.LASF108
	.byte	0x6
	.2byte	0x265
	.4byte	0x7b4
	.byte	0x80
	.uleb128 0x17
	.4byte	.LASF109
	.byte	0x6
	.2byte	0x266
	.4byte	0x7c4
	.byte	0x88
	.uleb128 0x17
	.4byte	.LASF110
	.byte	0x6
	.2byte	0x267
	.4byte	0x30
	.byte	0xa0
	.uleb128 0x17
	.4byte	.LASF111
	.byte	0x6
	.2byte	0x268
	.4byte	0x10c
	.byte	0xa4
	.uleb128 0x17
	.4byte	.LASF112
	.byte	0x6
	.2byte	0x269
	.4byte	0x10c
	.byte	0xac
	.uleb128 0x17
	.4byte	.LASF113
	.byte	0x6
	.2byte	0x26a
	.4byte	0x10c
	.byte	0xb4
	.uleb128 0x17
	.4byte	.LASF114
	.byte	0x6
	.2byte	0x26b
	.4byte	0x10c
	.byte	0xbc
	.uleb128 0x17
	.4byte	.LASF115
	.byte	0x6
	.2byte	0x26c
	.4byte	0x10c
	.byte	0xc4
	.uleb128 0x17
	.4byte	.LASF116
	.byte	0x6
	.2byte	0x26d
	.4byte	0x30
	.byte	0xcc
	.byte	0
	.uleb128 0x8
	.4byte	0x574
	.4byte	0x7b4
	.uleb128 0x9
	.4byte	0xe4
	.byte	0x19
	.byte	0
	.uleb128 0x8
	.4byte	0x574
	.4byte	0x7c4
	.uleb128 0x9
	.4byte	0xe4
	.byte	0x7
	.byte	0
	.uleb128 0x8
	.4byte	0x574
	.4byte	0x7d4
	.uleb128 0x9
	.4byte	0xe4
	.byte	0x17
	.byte	0
	.uleb128 0x1a
	.byte	0xf0
	.byte	0x6
	.2byte	0x272
	.4byte	0x7f8
	.uleb128 0x17
	.4byte	.LASF117
	.byte	0x6
	.2byte	0x275
	.4byte	0x7f8
	.byte	0
	.uleb128 0x17
	.4byte	.LASF118
	.byte	0x6
	.2byte	0x276
	.4byte	0x808
	.byte	0x78
	.byte	0
	.uleb128 0x8
	.4byte	0x2e2
	.4byte	0x808
	.uleb128 0x9
	.4byte	0xe4
	.byte	0x1d
	.byte	0
	.uleb128 0x8
	.4byte	0x7a
	.4byte	0x818
	.uleb128 0x9
	.4byte	0xe4
	.byte	0x1d
	.byte	0
	.uleb128 0x1b
	.byte	0xf0
	.byte	0x6
	.2byte	0x257
	.4byte	0x83a
	.uleb128 0x1c
	.4byte	.LASF67
	.byte	0x6
	.2byte	0x26e
	.4byte	0x6a3
	.uleb128 0x1c
	.4byte	.LASF119
	.byte	0x6
	.2byte	0x277
	.4byte	0x7d4
	.byte	0
	.uleb128 0x8
	.4byte	0x574
	.4byte	0x84a
	.uleb128 0x9
	.4byte	0xe4
	.byte	0x18
	.byte	0
	.uleb128 0x1d
	.4byte	.LASF131
	.byte	0x1
	.uleb128 0xf
	.byte	0x4
	.4byte	0x84a
	.uleb128 0x1e
	.byte	0x1
	.4byte	0x862
	.uleb128 0x14
	.4byte	0x431
	.byte	0
	.uleb128 0xf
	.byte	0x4
	.4byte	0x856
	.uleb128 0xf
	.byte	0x4
	.4byte	0x182
	.uleb128 0x1e
	.byte	0x1
	.4byte	0x87a
	.uleb128 0x14
	.4byte	0x30
	.byte	0
	.uleb128 0xf
	.byte	0x4
	.4byte	0x880
	.uleb128 0xf
	.byte	0x4
	.4byte	0x86e
	.uleb128 0x8
	.4byte	0x611
	.4byte	0x896
	.uleb128 0x9
	.4byte	0xe4
	.byte	0x2
	.byte	0
	.uleb128 0x1f
	.4byte	.LASF120
	.byte	0x6
	.2byte	0x2fe
	.4byte	0x431
	.byte	0x1
	.byte	0x1
	.uleb128 0x1f
	.4byte	.LASF121
	.byte	0x6
	.2byte	0x2ff
	.4byte	0x437
	.byte	0x1
	.byte	0x1
	.uleb128 0x4
	.4byte	.LASF122
	.byte	0x7
	.byte	0x30
	.4byte	0x5a
	.uleb128 0x20
	.4byte	.LASF123
	.byte	0x8
	.byte	0x9a
	.4byte	0x53
	.byte	0x1
	.byte	0x1
	.uleb128 0x20
	.4byte	.LASF124
	.byte	0x8
	.byte	0x9b
	.4byte	0x30
	.byte	0x1
	.byte	0x1
	.uleb128 0x8
	.4byte	0x56e
	.4byte	0x8e7
	.uleb128 0x9
	.4byte	0xe4
	.byte	0x1
	.byte	0
	.uleb128 0x20
	.4byte	.LASF125
	.byte	0x8
	.byte	0x9e
	.4byte	0x8d7
	.byte	0x1
	.byte	0x1
	.uleb128 0x21
	.byte	0x1
	.4byte	.LASF132
	.byte	0x1
	.byte	0x1d
	.byte	0x1
	.byte	0x1
	.4byte	0x918
	.uleb128 0x22
	.ascii	"us\000"
	.byte	0x1
	.byte	0x1d
	.4byte	0x30
	.uleb128 0x23
	.4byte	.LASF133
	.byte	0x1
	.byte	0x1f
	.4byte	0x8b2
	.byte	0
	.uleb128 0x24
	.byte	0x1
	.4byte	.LASF126
	.byte	0x1
	.byte	0x18
	.byte	0x1
	.4byte	.LFB1
	.4byte	.LFE1
	.byte	0x1
	.byte	0x9c
	.byte	0x1
	.4byte	0x979
	.uleb128 0x25
	.ascii	"ms\000"
	.byte	0x1
	.byte	0x18
	.4byte	0x30
	.4byte	.LLST3
	.uleb128 0x26
	.4byte	0x8f4
	.4byte	.LBB12
	.4byte	.Ldebug_ranges0+0x20
	.byte	0x1
	.byte	0x1a
	.uleb128 0x27
	.4byte	0x902
	.4byte	.LLST4
	.uleb128 0x28
	.4byte	.Ldebug_ranges0+0x20
	.uleb128 0x29
	.4byte	0x90c
	.4byte	.LLST5
	.uleb128 0x2a
	.4byte	.LVL12
	.4byte	0xa10
	.uleb128 0x2a
	.4byte	.LVL15
	.4byte	0xa10
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x2b
	.byte	0x1
	.4byte	.LASF127
	.byte	0x1
	.byte	0x13
	.byte	0x1
	.4byte	.LFB0
	.4byte	.LFE0
	.byte	0x1
	.byte	0x9c
	.byte	0x1
	.4byte	0x9d9
	.uleb128 0x25
	.ascii	"s\000"
	.byte	0x1
	.byte	0x13
	.4byte	0x29
	.4byte	.LLST0
	.uleb128 0x26
	.4byte	0x8f4
	.4byte	.LBB4
	.4byte	.Ldebug_ranges0+0
	.byte	0x1
	.byte	0x15
	.uleb128 0x27
	.4byte	0x902
	.4byte	.LLST1
	.uleb128 0x28
	.4byte	.Ldebug_ranges0+0
	.uleb128 0x29
	.4byte	0x90c
	.4byte	.LLST2
	.uleb128 0x2a
	.4byte	.LVL2
	.4byte	0xa10
	.uleb128 0x2a
	.4byte	.LVL8
	.4byte	0xa10
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x2c
	.4byte	0x8f4
	.4byte	.LFB2
	.4byte	.LFE2
	.byte	0x1
	.byte	0x9c
	.byte	0x1
	.4byte	0xa10
	.uleb128 0x27
	.4byte	0x902
	.4byte	.LLST6
	.uleb128 0x2d
	.4byte	0x90c
	.byte	0x1
	.byte	0x54
	.uleb128 0x2a
	.4byte	.LVL17
	.4byte	0xa10
	.uleb128 0x2a
	.4byte	.LVL19
	.4byte	0xa10
	.byte	0
	.uleb128 0x2e
	.byte	0x1
	.byte	0x1
	.4byte	.LASF134
	.4byte	.LASF134
	.byte	0x9
	.byte	0x1b
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
	.uleb128 0x4
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
	.uleb128 0x20
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x22
	.uleb128 0x5
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
	.uleb128 0x23
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
	.uleb128 0x24
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
	.uleb128 0x25
	.uleb128 0x5
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
	.uleb128 0x26
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
	.uleb128 0x27
	.uleb128 0x5
	.byte	0
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x28
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x55
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x29
	.uleb128 0x34
	.byte	0
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x2a
	.uleb128 0x4109
	.byte	0
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x31
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x2b
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
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0xa
	.uleb128 0x2116
	.uleb128 0xc
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x2c
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
	.uleb128 0x2d
	.uleb128 0x34
	.byte	0
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0x2e
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
.LLST3:
	.4byte	.LVL10
	.4byte	.LVL12-1
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL12-1
	.4byte	.LFE1
	.2byte	0x1
	.byte	0x56
	.4byte	0
	.4byte	0
.LLST4:
	.4byte	.LVL11
	.4byte	.LVL12-1
	.2byte	0x7
	.byte	0x70
	.sleb128 0
	.byte	0xa
	.2byte	0x3e8
	.byte	0x1e
	.byte	0x9f
	.4byte	.LVL12-1
	.4byte	.LVL14
	.2byte	0x7
	.byte	0x76
	.sleb128 0
	.byte	0xa
	.2byte	0x3e8
	.byte	0x1e
	.byte	0x9f
	.4byte	.LVL14
	.4byte	.LFE1
	.2byte	0x1
	.byte	0x54
	.4byte	0
	.4byte	0
.LLST5:
	.4byte	.LVL13
	.4byte	.LVL14
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL14
	.4byte	.LFE1
	.2byte	0x1
	.byte	0x55
	.4byte	0
	.4byte	0
.LLST0:
	.4byte	.LVL0
	.4byte	.LVL2-1
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL2-1
	.4byte	.LVL7
	.2byte	0x1
	.byte	0x54
	.4byte	.LVL7
	.4byte	.LFE0
	.2byte	0x6
	.byte	0xf3
	.uleb128 0x3
	.byte	0xf5
	.uleb128 0
	.uleb128 0x29
	.byte	0x9f
	.4byte	0
	.4byte	0
.LLST1:
	.4byte	.LVL1
	.4byte	.LVL2-1
	.2byte	0x10
	.byte	0xf5
	.uleb128 0
	.uleb128 0x29
	.byte	0xf4
	.uleb128 0x29
	.byte	0x4
	.4byte	0x49742400
	.byte	0x1e
	.byte	0xf7
	.uleb128 0x30
	.byte	0xf7
	.uleb128 0
	.byte	0x9f
	.4byte	.LVL2-1
	.4byte	.LVL7
	.2byte	0x10
	.byte	0xf5
	.uleb128 0x4
	.uleb128 0x29
	.byte	0xf4
	.uleb128 0x29
	.byte	0x4
	.4byte	0x49742400
	.byte	0x1e
	.byte	0xf7
	.uleb128 0x30
	.byte	0xf7
	.uleb128 0
	.byte	0x9f
	.4byte	.LVL7
	.4byte	.LFE0
	.2byte	0x12
	.byte	0xf3
	.uleb128 0x3
	.byte	0xf5
	.uleb128 0
	.uleb128 0x29
	.byte	0xf4
	.uleb128 0x29
	.byte	0x4
	.4byte	0x49742400
	.byte	0x1e
	.byte	0xf7
	.uleb128 0x30
	.byte	0xf7
	.uleb128 0
	.byte	0x9f
	.4byte	0
	.4byte	0
.LLST2:
	.4byte	.LVL3
	.4byte	.LVL4
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL4
	.4byte	.LVL9
	.2byte	0x1
	.byte	0x55
	.4byte	0
	.4byte	0
.LLST6:
	.4byte	.LVL16
	.4byte	.LVL17-1
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL17-1
	.4byte	.LFE2
	.2byte	0x1
	.byte	0x55
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
	.4byte	.LFB0
	.4byte	.LFE0-.LFB0
	.4byte	.LFB1
	.4byte	.LFE1-.LFB1
	.4byte	.LFB2
	.4byte	.LFE2-.LFB2
	.4byte	0
	.4byte	0
	.section	.debug_ranges,"",%progbits
.Ldebug_ranges0:
	.4byte	.LBB4
	.4byte	.LBE4
	.4byte	.LBB8
	.4byte	.LBE8
	.4byte	.LBB9
	.4byte	.LBE9
	.4byte	0
	.4byte	0
	.4byte	.LBB12
	.4byte	.LBE12
	.4byte	.LBB16
	.4byte	.LBE16
	.4byte	.LBB17
	.4byte	.LBE17
	.4byte	0
	.4byte	0
	.4byte	.LFB0
	.4byte	.LFE0
	.4byte	.LFB1
	.4byte	.LFE1
	.4byte	.LFB2
	.4byte	.LFE2
	.4byte	0
	.4byte	0
	.section	.debug_line,"",%progbits
.Ldebug_line0:
	.section	.debug_str,"MS",%progbits,1
.LASF41:
	.ascii	"_dso_handle\000"
.LASF49:
	.ascii	"_size\000"
.LASF94:
	.ascii	"_rand48\000"
.LASF73:
	.ascii	"_emergency\000"
.LASF124:
	.ascii	"_daylight\000"
.LASF132:
	.ascii	"wait_us\000"
.LASF63:
	.ascii	"_data\000"
.LASF114:
	.ascii	"_wcrtomb_state\000"
.LASF115:
	.ascii	"_wcsrtombs_state\000"
.LASF8:
	.ascii	"long long unsigned int\000"
.LASF53:
	.ascii	"_lbfsize\000"
.LASF131:
	.ascii	"__locale_t\000"
.LASF112:
	.ascii	"_mbrtowc_state\000"
.LASF125:
	.ascii	"_tzname\000"
.LASF107:
	.ascii	"_wctomb_state\000"
.LASF30:
	.ascii	"__tm_sec\000"
.LASF7:
	.ascii	"long long int\000"
.LASF1:
	.ascii	"signed char\000"
.LASF59:
	.ascii	"_ubuf\000"
.LASF48:
	.ascii	"_base\000"
.LASF32:
	.ascii	"__tm_hour\000"
.LASF88:
	.ascii	"__sf\000"
.LASF39:
	.ascii	"_on_exit_args\000"
.LASF54:
	.ascii	"_cookie\000"
.LASF87:
	.ascii	"__sglue\000"
.LASF5:
	.ascii	"long int\000"
.LASF51:
	.ascii	"_flags\000"
.LASF43:
	.ascii	"_is_cxa\000"
.LASF69:
	.ascii	"_stdin\000"
.LASF130:
	.ascii	"/cygdrive/d/PUYA/HE3/sdk-ameba-v7.1d/project/realte"
	.ascii	"k_amebaz2_v0_example/GCC-RELEASE\000"
.LASF61:
	.ascii	"_blksize\000"
.LASF128:
	.ascii	"GNU C11 6.5.0 -march=armv8-m.main+dsp -mthumb -mcms"
	.ascii	"e -mfloat-abi=soft -mabi=aapcs -g -gdwarf-3 -gdwarf"
	.ascii	"-3 -O3 -fstack-usage -fdata-sections -ffunction-sec"
	.ascii	"tions\000"
.LASF83:
	.ascii	"_cvtbuf\000"
.LASF62:
	.ascii	"_offset\000"
.LASF113:
	.ascii	"_mbsrtowcs_state\000"
.LASF111:
	.ascii	"_mbrlen_state\000"
.LASF40:
	.ascii	"_fnargs\000"
.LASF46:
	.ascii	"_fns\000"
.LASF11:
	.ascii	"__uint32_t\000"
.LASF26:
	.ascii	"_sign\000"
.LASF22:
	.ascii	"_flock_t\000"
.LASF71:
	.ascii	"_stderr\000"
.LASF28:
	.ascii	"_Bigint\000"
.LASF102:
	.ascii	"_gamma_signgam\000"
.LASF55:
	.ascii	"_read\000"
.LASF79:
	.ascii	"_result_k\000"
.LASF29:
	.ascii	"__tm\000"
.LASF9:
	.ascii	"unsigned int\000"
.LASF17:
	.ascii	"__wchb\000"
.LASF70:
	.ascii	"_stdout\000"
.LASF82:
	.ascii	"_cvtlen\000"
.LASF6:
	.ascii	"long unsigned int\000"
.LASF52:
	.ascii	"_file\000"
.LASF92:
	.ascii	"_niobs\000"
.LASF4:
	.ascii	"short unsigned int\000"
.LASF85:
	.ascii	"_atexit0\000"
.LASF109:
	.ascii	"_signal_buf\000"
.LASF100:
	.ascii	"_asctime_buf\000"
.LASF78:
	.ascii	"_result\000"
.LASF16:
	.ascii	"__wch\000"
.LASF15:
	.ascii	"wint_t\000"
.LASF64:
	.ascii	"_lock\000"
.LASF66:
	.ascii	"_flags2\000"
.LASF56:
	.ascii	"_write\000"
.LASF35:
	.ascii	"__tm_year\000"
.LASF18:
	.ascii	"sizetype\000"
.LASF10:
	.ascii	"long double\000"
.LASF117:
	.ascii	"_nextf\000"
.LASF34:
	.ascii	"__tm_mon\000"
.LASF44:
	.ascii	"_atexit\000"
.LASF76:
	.ascii	"__sdidinit\000"
.LASF13:
	.ascii	"_off_t\000"
.LASF0:
	.ascii	"float\000"
.LASF81:
	.ascii	"_freelist\000"
.LASF123:
	.ascii	"_timezone\000"
.LASF12:
	.ascii	"_LOCK_RECURSIVE_T\000"
.LASF2:
	.ascii	"unsigned char\000"
.LASF84:
	.ascii	"_new\000"
.LASF116:
	.ascii	"_h_errno\000"
.LASF3:
	.ascii	"short int\000"
.LASF37:
	.ascii	"__tm_yday\000"
.LASF47:
	.ascii	"__sbuf\000"
.LASF93:
	.ascii	"_iobs\000"
.LASF90:
	.ascii	"__FILE\000"
.LASF21:
	.ascii	"_mbstate_t\000"
.LASF50:
	.ascii	"__sFILE\000"
.LASF65:
	.ascii	"_mbstate\000"
.LASF103:
	.ascii	"_rand_next\000"
.LASF105:
	.ascii	"_mblen_state\000"
.LASF72:
	.ascii	"_inc\000"
.LASF45:
	.ascii	"_ind\000"
.LASF75:
	.ascii	"_locale\000"
.LASF77:
	.ascii	"__cleanup\000"
.LASF74:
	.ascii	"_unspecified_locale_info\000"
.LASF25:
	.ascii	"_maxwds\000"
.LASF67:
	.ascii	"_reent\000"
.LASF95:
	.ascii	"_seed\000"
.LASF19:
	.ascii	"__count\000"
.LASF20:
	.ascii	"__value\000"
.LASF57:
	.ascii	"_seek\000"
.LASF120:
	.ascii	"_impure_ptr\000"
.LASF14:
	.ascii	"_fpos_t\000"
.LASF129:
	.ascii	"../../../component/common/mbed/targets/hal/rtl8710c"
	.ascii	"/wait_api.c\000"
.LASF68:
	.ascii	"_errno\000"
.LASF89:
	.ascii	"char\000"
.LASF31:
	.ascii	"__tm_min\000"
.LASF127:
	.ascii	"wait\000"
.LASF96:
	.ascii	"_mult\000"
.LASF134:
	.ascii	"us_ticker_read\000"
.LASF24:
	.ascii	"_next\000"
.LASF99:
	.ascii	"_strtok_last\000"
.LASF42:
	.ascii	"_fntypes\000"
.LASF97:
	.ascii	"_add\000"
.LASF23:
	.ascii	"__ULong\000"
.LASF110:
	.ascii	"_getdate_err\000"
.LASF121:
	.ascii	"_global_impure_ptr\000"
.LASF122:
	.ascii	"uint32_t\000"
.LASF98:
	.ascii	"_unused_rand\000"
.LASF27:
	.ascii	"_wds\000"
.LASF36:
	.ascii	"__tm_wday\000"
.LASF91:
	.ascii	"_glue\000"
.LASF118:
	.ascii	"_nmalloc\000"
.LASF108:
	.ascii	"_l64a_buf\000"
.LASF86:
	.ascii	"_sig_func\000"
.LASF60:
	.ascii	"_nbuf\000"
.LASF119:
	.ascii	"_unused\000"
.LASF38:
	.ascii	"__tm_isdst\000"
.LASF101:
	.ascii	"_localtime_buf\000"
.LASF58:
	.ascii	"_close\000"
.LASF104:
	.ascii	"_r48\000"
.LASF133:
	.ascii	"start\000"
.LASF106:
	.ascii	"_mbtowc_state\000"
.LASF80:
	.ascii	"_p5s\000"
.LASF33:
	.ascii	"__tm_mday\000"
.LASF126:
	.ascii	"wait_ms\000"
	.ident	"GCC: (Realtek ASDK-6.5.0 Build 3215) 6.5.0"
