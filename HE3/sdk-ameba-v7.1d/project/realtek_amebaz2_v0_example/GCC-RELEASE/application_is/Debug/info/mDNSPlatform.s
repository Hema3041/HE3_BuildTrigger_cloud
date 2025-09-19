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
	.file	"mDNSPlatform.c"
	.text
.Ltext0:
	.cfi_sections	.debug_frame
	.section	.text.mDNSPlatformCustomInit,"ax",%progbits
	.align	1
	.p2align 2,,3
	.global	mDNSPlatformCustomInit
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	mDNSPlatformCustomInit, %function
mDNSPlatformCustomInit:
.LFB1:
	.file 1 "../../../component/common/network/mDNS/mDNSPlatform.c"
	.loc 1 12 0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	.loc 1 13 0
	ldr	r2, .L2
	ldrb	r3, [r2, #55]	@ zero_extendqisi2
	orr	r3, r3, #32
	strb	r3, [r2, #55]
	bx	lr
.L3:
	.align	2
.L2:
	.word	xnetif
	.cfi_endproc
.LFE1:
	.size	mDNSPlatformCustomInit, .-mDNSPlatformCustomInit
	.section	.text.mDNSPlatformHtons,"ax",%progbits
	.align	1
	.p2align 2,,3
	.global	mDNSPlatformHtons
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	mDNSPlatformHtons, %function
mDNSPlatformHtons:
.LFB2:
	.loc 1 17 0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
.LVL0:
	.loc 1 18 0
	b	lwip_htons
.LVL1:
	.cfi_endproc
.LFE2:
	.size	mDNSPlatformHtons, .-mDNSPlatformHtons
	.section	.text.mDNSPlatformInetAddr,"ax",%progbits
	.align	1
	.p2align 2,,3
	.global	mDNSPlatformInetAddr
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	mDNSPlatformInetAddr, %function
mDNSPlatformInetAddr:
.LFB3:
	.loc 1 22 0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
.LVL2:
	.loc 1 23 0
	b	ipaddr_addr
.LVL3:
	.cfi_endproc
.LFE3:
	.size	mDNSPlatformInetAddr, .-mDNSPlatformInetAddr
	.section	.text.mDNSPlatformHostname,"ax",%progbits
	.align	1
	.p2align 2,,3
	.global	mDNSPlatformHostname
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	mDNSPlatformHostname, %function
mDNSPlatformHostname:
.LFB4:
	.loc 1 29 0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	.loc 1 35 0
	ldr	r0, .L7
	bx	lr
.L8:
	.align	2
.L7:
	.word	.LC0
	.cfi_endproc
.LFE4:
	.size	mDNSPlatformHostname, .-mDNSPlatformHostname
	.section	.rodata.mDNSPlatformHostname.str1.4,"aMS",%progbits,1
	.align	2
.LC0:
	.ascii	"ameba\000"
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
	.file 10 "../../../component/common/network/lwip/lwip_v2.0.2/port/realtek/arch/cc.h"
	.file 11 "../../../component/common/network/lwip/lwip_v2.0.2/src/include/lwip/ip4_addr.h"
	.file 12 "../../../component/common/network/lwip/lwip_v2.0.2/src/include/lwip/ip_addr.h"
	.file 13 "../../../component/common/network/lwip/lwip_v2.0.2/src/include/lwip/err.h"
	.file 14 "../../../component/common/network/lwip/lwip_v2.0.2/src/include/lwip/inet.h"
	.file 15 "../../../component/common/network/lwip/lwip_v2.0.2/src/include/lwip/errno.h"
	.file 16 "../../../component/common/network/lwip/lwip_v2.0.2/src/include/lwip/pbuf.h"
	.file 17 "../../../component/common/network/lwip/lwip_v2.0.2/src/include/lwip/priv/memp_priv.h"
	.file 18 "../../../component/common/network/lwip/lwip_v2.0.2/src/include/lwip/memp.h"
	.file 19 "../../../component/common/network/lwip/lwip_v2.0.2/src/include/lwip/netif.h"
	.file 20 "../../../component/common/network/lwip/lwip_v2.0.2/src/include/lwip/def.h"
	.section	.debug_info,"",%progbits
.Ldebug_info0:
	.4byte	0xddc
	.2byte	0x3
	.4byte	.Ldebug_abbrev0
	.byte	0x4
	.uleb128 0x1
	.4byte	.LASF181
	.byte	0xc
	.4byte	.LASF182
	.4byte	.LASF183
	.4byte	.Ldebug_ranges0+0
	.4byte	0
	.4byte	0
	.4byte	.Ldebug_line0
	.uleb128 0x2
	.byte	0x1
	.byte	0x6
	.4byte	.LASF0
	.uleb128 0x2
	.byte	0x1
	.byte	0x8
	.4byte	.LASF1
	.uleb128 0x2
	.byte	0x2
	.byte	0x5
	.4byte	.LASF2
	.uleb128 0x3
	.4byte	.LASF5
	.byte	0x2
	.byte	0x39
	.4byte	0x49
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
	.4byte	0x30
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
	.4byte	0x30
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
	.4byte	0x37
	.byte	0xc
	.uleb128 0xb
	.4byte	.LASF52
	.byte	0x6
	.byte	0xba
	.4byte	0x37
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
	.4byte	0x30
	.4byte	0x605
	.uleb128 0x9
	.4byte	0xe8
	.byte	0x2
	.byte	0
	.uleb128 0x8
	.4byte	0x30
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
	.4byte	.LASF184
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
	.byte	0x24
	.4byte	0x3e
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
	.byte	0x25
	.4byte	0x30
	.uleb128 0x3
	.4byte	.LASF129
	.byte	0xa
	.byte	0x26
	.4byte	0x29
	.uleb128 0x3
	.4byte	.LASF130
	.byte	0xa
	.byte	0x27
	.4byte	0x49
	.uleb128 0x3
	.4byte	.LASF131
	.byte	0xa
	.byte	0x29
	.4byte	0x7e
	.uleb128 0xd
	.4byte	.LASF132
	.byte	0x4
	.byte	0xb
	.byte	0x33
	.4byte	0x955
	.uleb128 0xb
	.4byte	.LASF133
	.byte	0xb
	.byte	0x34
	.4byte	0x931
	.byte	0
	.byte	0
	.uleb128 0x3
	.4byte	.LASF134
	.byte	0xb
	.byte	0x39
	.4byte	0x93c
	.uleb128 0x15
	.4byte	0x955
	.uleb128 0x3
	.4byte	.LASF135
	.byte	0xc
	.byte	0xf4
	.4byte	0x955
	.uleb128 0x15
	.4byte	0x965
	.uleb128 0x1f
	.4byte	.LASF136
	.byte	0xc
	.2byte	0x158
	.4byte	0x970
	.byte	0x1
	.byte	0x1
	.uleb128 0x1f
	.4byte	.LASF137
	.byte	0xc
	.2byte	0x159
	.4byte	0x970
	.byte	0x1
	.byte	0x1
	.uleb128 0x3
	.4byte	.LASF138
	.byte	0xd
	.byte	0x39
	.4byte	0x91b
	.uleb128 0x6
	.byte	0x10
	.byte	0xe
	.byte	0x3f
	.4byte	0x9bb
	.uleb128 0x7
	.4byte	.LASF139
	.byte	0xe
	.byte	0x40
	.4byte	0x9bb
	.uleb128 0x7
	.4byte	.LASF140
	.byte	0xe
	.byte	0x41
	.4byte	0x9cb
	.byte	0
	.uleb128 0x8
	.4byte	0x931
	.4byte	0x9cb
	.uleb128 0x9
	.4byte	0xe8
	.byte	0x3
	.byte	0
	.uleb128 0x8
	.4byte	0x910
	.4byte	0x9db
	.uleb128 0x9
	.4byte	0xe8
	.byte	0xf
	.byte	0
	.uleb128 0xd
	.4byte	.LASF141
	.byte	0x10
	.byte	0xe
	.byte	0x3e
	.4byte	0x9f3
	.uleb128 0xe
	.ascii	"un\000"
	.byte	0xe
	.byte	0x42
	.4byte	0x99c
	.byte	0
	.byte	0
	.uleb128 0x15
	.4byte	0x9db
	.uleb128 0x20
	.4byte	.LASF142
	.byte	0xe
	.byte	0x56
	.4byte	0x9f3
	.byte	0x1
	.byte	0x1
	.uleb128 0x20
	.4byte	.LASF143
	.byte	0xf
	.byte	0xb8
	.4byte	0x77
	.byte	0x1
	.byte	0x1
	.uleb128 0x8
	.4byte	0x578
	.4byte	0xa22
	.uleb128 0x9
	.4byte	0xe8
	.byte	0x1
	.byte	0
	.uleb128 0xd
	.4byte	.LASF144
	.byte	0x10
	.byte	0x10
	.byte	0x8e
	.4byte	0xa83
	.uleb128 0xb
	.4byte	.LASF145
	.byte	0x10
	.byte	0x90
	.4byte	0xa83
	.byte	0
	.uleb128 0xb
	.4byte	.LASF146
	.byte	0x10
	.byte	0x93
	.4byte	0x126
	.byte	0x4
	.uleb128 0xb
	.4byte	.LASF147
	.byte	0x10
	.byte	0x9c
	.4byte	0x926
	.byte	0x8
	.uleb128 0xe
	.ascii	"len\000"
	.byte	0x10
	.byte	0x9f
	.4byte	0x926
	.byte	0xa
	.uleb128 0xb
	.4byte	.LASF148
	.byte	0x10
	.byte	0xa2
	.4byte	0x910
	.byte	0xc
	.uleb128 0xb
	.4byte	.LASF149
	.byte	0x10
	.byte	0xa5
	.4byte	0x910
	.byte	0xd
	.uleb128 0xe
	.ascii	"ref\000"
	.byte	0x10
	.byte	0xac
	.4byte	0x926
	.byte	0xe
	.byte	0
	.uleb128 0xf
	.byte	0x4
	.4byte	0xa22
	.uleb128 0xd
	.4byte	.LASF150
	.byte	0x4
	.byte	0x11
	.byte	0x5b
	.4byte	0xaa2
	.uleb128 0xb
	.4byte	.LASF145
	.byte	0x11
	.byte	0x5c
	.4byte	0xaa2
	.byte	0
	.byte	0
	.uleb128 0xf
	.byte	0x4
	.4byte	0xa89
	.uleb128 0xd
	.4byte	.LASF151
	.byte	0xc
	.byte	0x11
	.byte	0x82
	.4byte	0xae5
	.uleb128 0xb
	.4byte	.LASF152
	.byte	0x11
	.byte	0x8d
	.4byte	0x926
	.byte	0
	.uleb128 0xe
	.ascii	"num\000"
	.byte	0x11
	.byte	0x91
	.4byte	0x926
	.byte	0x2
	.uleb128 0xb
	.4byte	.LASF153
	.byte	0x11
	.byte	0x94
	.4byte	0xaea
	.byte	0x4
	.uleb128 0xe
	.ascii	"tab\000"
	.byte	0x11
	.byte	0x97
	.4byte	0xaf0
	.byte	0x8
	.byte	0
	.uleb128 0x15
	.4byte	0xaa8
	.uleb128 0xf
	.byte	0x4
	.4byte	0x910
	.uleb128 0xf
	.byte	0x4
	.4byte	0xaa2
	.uleb128 0x8
	.4byte	0xb11
	.4byte	0xb06
	.uleb128 0x9
	.4byte	0xe8
	.byte	0xf
	.byte	0
	.uleb128 0x15
	.4byte	0xaf6
	.uleb128 0xf
	.byte	0x4
	.4byte	0xae5
	.uleb128 0x15
	.4byte	0xb0b
	.uleb128 0x20
	.4byte	.LASF154
	.byte	0x12
	.byte	0x3d
	.4byte	0xb06
	.byte	0x1
	.byte	0x1
	.uleb128 0x21
	.4byte	.LASF185
	.byte	0x1
	.4byte	0x30
	.byte	0x13
	.byte	0x95
	.4byte	0xb40
	.uleb128 0x22
	.4byte	.LASF155
	.byte	0
	.uleb128 0x22
	.4byte	.LASF156
	.byte	0x1
	.byte	0
	.uleb128 0xf
	.byte	0x4
	.4byte	0xb46
	.uleb128 0xd
	.4byte	.LASF157
	.byte	0x40
	.byte	0x13
	.byte	0xe7
	.4byte	0xc2a
	.uleb128 0xb
	.4byte	.LASF145
	.byte	0x13
	.byte	0xe9
	.4byte	0xb40
	.byte	0
	.uleb128 0xb
	.4byte	.LASF132
	.byte	0x13
	.byte	0xed
	.4byte	0x965
	.byte	0x4
	.uleb128 0xb
	.4byte	.LASF158
	.byte	0x13
	.byte	0xee
	.4byte	0x965
	.byte	0x8
	.uleb128 0xe
	.ascii	"gw\000"
	.byte	0x13
	.byte	0xef
	.4byte	0x965
	.byte	0xc
	.uleb128 0xb
	.4byte	.LASF159
	.byte	0x13
	.byte	0xfa
	.4byte	0xc2a
	.byte	0x10
	.uleb128 0x17
	.4byte	.LASF160
	.byte	0x13
	.2byte	0x100
	.4byte	0xc50
	.byte	0x14
	.uleb128 0x17
	.4byte	.LASF161
	.byte	0x13
	.2byte	0x105
	.4byte	0xc81
	.byte	0x18
	.uleb128 0x17
	.4byte	.LASF162
	.byte	0x13
	.2byte	0x11d
	.4byte	0x126
	.byte	0x1c
	.uleb128 0x17
	.4byte	.LASF163
	.byte	0x13
	.2byte	0x11f
	.4byte	0xcd2
	.byte	0x20
	.uleb128 0x17
	.4byte	.LASF164
	.byte	0x13
	.2byte	0x127
	.4byte	0x910
	.byte	0x2c
	.uleb128 0x23
	.ascii	"mtu\000"
	.byte	0x13
	.2byte	0x131
	.4byte	0x926
	.byte	0x2e
	.uleb128 0x17
	.4byte	.LASF165
	.byte	0x13
	.2byte	0x133
	.4byte	0x910
	.byte	0x30
	.uleb128 0x17
	.4byte	.LASF166
	.byte	0x13
	.2byte	0x135
	.4byte	0xce2
	.byte	0x31
	.uleb128 0x17
	.4byte	.LASF149
	.byte	0x13
	.2byte	0x137
	.4byte	0x910
	.byte	0x37
	.uleb128 0x17
	.4byte	.LASF167
	.byte	0x13
	.2byte	0x139
	.4byte	0xa12
	.byte	0x38
	.uleb128 0x23
	.ascii	"num\000"
	.byte	0x13
	.2byte	0x13b
	.4byte	0x910
	.byte	0x3a
	.uleb128 0x17
	.4byte	.LASF168
	.byte	0x13
	.2byte	0x149
	.4byte	0xca7
	.byte	0x3c
	.byte	0
	.uleb128 0x3
	.4byte	.LASF169
	.byte	0x13
	.byte	0xa8
	.4byte	0xc35
	.uleb128 0xf
	.byte	0x4
	.4byte	0xc3b
	.uleb128 0x13
	.byte	0x1
	.4byte	0x991
	.4byte	0xc50
	.uleb128 0x14
	.4byte	0xa83
	.uleb128 0x14
	.4byte	0xb40
	.byte	0
	.uleb128 0x3
	.4byte	.LASF170
	.byte	0x13
	.byte	0xb3
	.4byte	0xc5b
	.uleb128 0xf
	.byte	0x4
	.4byte	0xc61
	.uleb128 0x13
	.byte	0x1
	.4byte	0x991
	.4byte	0xc7b
	.uleb128 0x14
	.4byte	0xb40
	.uleb128 0x14
	.4byte	0xa83
	.uleb128 0x14
	.4byte	0xc7b
	.byte	0
	.uleb128 0xf
	.byte	0x4
	.4byte	0x960
	.uleb128 0x3
	.4byte	.LASF171
	.byte	0x13
	.byte	0xca
	.4byte	0xc8c
	.uleb128 0xf
	.byte	0x4
	.4byte	0xc92
	.uleb128 0x13
	.byte	0x1
	.4byte	0x991
	.4byte	0xca7
	.uleb128 0x14
	.4byte	0xb40
	.uleb128 0x14
	.4byte	0xa83
	.byte	0
	.uleb128 0x3
	.4byte	.LASF172
	.byte	0x13
	.byte	0xcf
	.4byte	0xcb2
	.uleb128 0xf
	.byte	0x4
	.4byte	0xcb8
	.uleb128 0x13
	.byte	0x1
	.4byte	0x991
	.4byte	0xcd2
	.uleb128 0x14
	.4byte	0xb40
	.uleb128 0x14
	.4byte	0xc7b
	.uleb128 0x14
	.4byte	0xb23
	.byte	0
	.uleb128 0x8
	.4byte	0x126
	.4byte	0xce2
	.uleb128 0x9
	.4byte	0xe8
	.byte	0x2
	.byte	0
	.uleb128 0x8
	.4byte	0x910
	.4byte	0xcf2
	.uleb128 0x9
	.4byte	0xe8
	.byte	0x5
	.byte	0
	.uleb128 0x1f
	.4byte	.LASF173
	.byte	0x13
	.2byte	0x167
	.4byte	0xb40
	.byte	0x1
	.byte	0x1
	.uleb128 0x1f
	.4byte	.LASF174
	.byte	0x13
	.2byte	0x169
	.4byte	0xb40
	.byte	0x1
	.byte	0x1
	.uleb128 0x8
	.4byte	0xb46
	.4byte	0xd19
	.uleb128 0x24
	.byte	0
	.uleb128 0x20
	.4byte	.LASF175
	.byte	0x1
	.byte	0x3
	.4byte	0xd0e
	.byte	0x1
	.byte	0x1
	.uleb128 0x25
	.byte	0x1
	.4byte	.LASF186
	.byte	0x1
	.byte	0x1c
	.byte	0x1
	.4byte	0x572
	.4byte	.LFB4
	.4byte	.LFE4
	.byte	0x1
	.byte	0x9c
	.byte	0x1
	.uleb128 0x26
	.byte	0x1
	.4byte	.LASF176
	.byte	0x1
	.byte	0x15
	.byte	0x1
	.4byte	0x8c1
	.4byte	.LFB3
	.4byte	.LFE3
	.byte	0x1
	.byte	0x9c
	.byte	0x1
	.4byte	0xd7b
	.uleb128 0x27
	.ascii	"cp\000"
	.byte	0x1
	.byte	0x15
	.4byte	0x572
	.4byte	.LLST1
	.uleb128 0x28
	.4byte	.LVL3
	.byte	0x1
	.4byte	0xdc5
	.uleb128 0x29
	.byte	0x1
	.byte	0x50
	.byte	0x3
	.byte	0xf3
	.uleb128 0x1
	.byte	0x50
	.byte	0
	.byte	0
	.uleb128 0x26
	.byte	0x1
	.4byte	.LASF177
	.byte	0x1
	.byte	0x10
	.byte	0x1
	.4byte	0x8b6
	.4byte	.LFB2
	.4byte	.LFE2
	.byte	0x1
	.byte	0x9c
	.byte	0x1
	.4byte	0xdb1
	.uleb128 0x2a
	.4byte	.LASF178
	.byte	0x1
	.byte	0x10
	.4byte	0x8b6
	.4byte	.LLST0
	.uleb128 0x2b
	.4byte	.LVL1
	.byte	0x1
	.4byte	0xdd2
	.byte	0
	.uleb128 0x2c
	.byte	0x1
	.4byte	.LASF187
	.byte	0x1
	.byte	0xb
	.byte	0x1
	.4byte	.LFB1
	.4byte	.LFE1
	.byte	0x1
	.byte	0x9c
	.byte	0x1
	.uleb128 0x2d
	.byte	0x1
	.byte	0x1
	.4byte	.LASF179
	.4byte	.LASF179
	.byte	0xb
	.byte	0xd7
	.uleb128 0x2d
	.byte	0x1
	.byte	0x1
	.4byte	.LASF180
	.4byte	.LASF180
	.byte	0x14
	.byte	0x55
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
	.uleb128 0x3
	.uleb128 0xe
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
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
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
	.uleb128 0x24
	.uleb128 0x21
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x25
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
	.byte	0
	.byte	0
	.uleb128 0x26
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
	.uleb128 0x27
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
	.uleb128 0x28
	.uleb128 0x4109
	.byte	0x1
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x2115
	.uleb128 0xc
	.uleb128 0x31
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x29
	.uleb128 0x410a
	.byte	0
	.uleb128 0x2
	.uleb128 0xa
	.uleb128 0x2111
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0x2a
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
	.uleb128 0x2b
	.uleb128 0x4109
	.byte	0
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x2115
	.uleb128 0xc
	.uleb128 0x31
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x2c
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
	.uleb128 0x2d
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
.LLST1:
	.4byte	.LVL2
	.4byte	.LVL3-1
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL3-1
	.4byte	.LFE3
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x50
	.byte	0x9f
	.4byte	0
	.4byte	0
.LLST0:
	.4byte	.LVL0
	.4byte	.LVL1-1
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL1-1
	.4byte	.LFE2
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x50
	.byte	0x9f
	.4byte	0
	.4byte	0
	.section	.debug_aranges,"",%progbits
	.4byte	0x34
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
	.4byte	.LFB4
	.4byte	.LFE4-.LFB4
	.4byte	0
	.4byte	0
	.section	.debug_ranges,"",%progbits
.Ldebug_ranges0:
	.4byte	.LFB1
	.4byte	.LFE1
	.4byte	.LFB2
	.4byte	.LFE2
	.4byte	.LFB3
	.4byte	.LFE3
	.4byte	.LFB4
	.4byte	.LFE4
	.4byte	0
	.4byte	0
	.section	.debug_line,"",%progbits
.Ldebug_line0:
	.section	.debug_str,"MS",%progbits,1
.LASF150:
	.ascii	"memp\000"
.LASF167:
	.ascii	"name\000"
.LASF159:
	.ascii	"input\000"
.LASF175:
	.ascii	"xnetif\000"
.LASF181:
	.ascii	"GNU C11 6.5.0 -march=armv8-m.main+dsp -mthumb -mcms"
	.ascii	"e -mfloat-abi=soft -mabi=aapcs -g -gdwarf-3 -gdwarf"
	.ascii	"-3 -O3 -fstack-usage -fdata-sections -ffunction-sec"
	.ascii	"tions\000"
.LASF39:
	.ascii	"_on_exit_args\000"
.LASF125:
	.ascii	"_daylight\000"
.LASF107:
	.ascii	"_wctomb_state\000"
.LASF149:
	.ascii	"flags\000"
.LASF104:
	.ascii	"_r48\000"
.LASF143:
	.ascii	"errno\000"
.LASF109:
	.ascii	"_signal_buf\000"
.LASF10:
	.ascii	"unsigned int\000"
.LASF145:
	.ascii	"next\000"
.LASF138:
	.ascii	"err_t\000"
.LASF53:
	.ascii	"_lbfsize\000"
.LASF51:
	.ascii	"_flags\000"
.LASF161:
	.ascii	"linkoutput\000"
.LASF178:
	.ascii	"hostshort\000"
.LASF68:
	.ascii	"_errno\000"
.LASF130:
	.ascii	"u16_t\000"
.LASF12:
	.ascii	"_LOCK_RECURSIVE_T\000"
.LASF55:
	.ascii	"_read\000"
.LASF111:
	.ascii	"_mbrlen_state\000"
.LASF170:
	.ascii	"netif_output_fn\000"
.LASF180:
	.ascii	"lwip_htons\000"
.LASF70:
	.ascii	"_stdout\000"
.LASF14:
	.ascii	"_fpos_t\000"
.LASF137:
	.ascii	"ip_addr_broadcast\000"
.LASF46:
	.ascii	"_fns\000"
.LASF54:
	.ascii	"_cookie\000"
.LASF28:
	.ascii	"_Bigint\000"
.LASF36:
	.ascii	"__tm_wday\000"
.LASF183:
	.ascii	"/cygdrive/d/PUYA/HE3/sdk-ameba-v7.1d/project/realte"
	.ascii	"k_amebaz2_v0_example/GCC-RELEASE\000"
.LASF78:
	.ascii	"_result\000"
.LASF123:
	.ascii	"uint32_t\000"
.LASF32:
	.ascii	"__tm_hour\000"
.LASF177:
	.ascii	"mDNSPlatformHtons\000"
.LASF19:
	.ascii	"__count\000"
.LASF31:
	.ascii	"__tm_min\000"
.LASF120:
	.ascii	"_impure_ptr\000"
.LASF153:
	.ascii	"base\000"
.LASF117:
	.ascii	"_nextf\000"
.LASF94:
	.ascii	"_rand48\000"
.LASF173:
	.ascii	"netif_list\000"
.LASF166:
	.ascii	"hwaddr\000"
.LASF79:
	.ascii	"_result_k\000"
.LASF9:
	.ascii	"long long unsigned int\000"
.LASF100:
	.ascii	"_asctime_buf\000"
.LASF50:
	.ascii	"__sFILE\000"
.LASF27:
	.ascii	"_wds\000"
.LASF5:
	.ascii	"__uint16_t\000"
.LASF90:
	.ascii	"__FILE\000"
.LASF165:
	.ascii	"hwaddr_len\000"
.LASF62:
	.ascii	"_offset\000"
.LASF73:
	.ascii	"_emergency\000"
.LASF179:
	.ascii	"ipaddr_addr\000"
.LASF147:
	.ascii	"tot_len\000"
.LASF146:
	.ascii	"payload\000"
.LASF30:
	.ascii	"__tm_sec\000"
.LASF160:
	.ascii	"output\000"
.LASF127:
	.ascii	"suboptarg\000"
.LASF37:
	.ascii	"__tm_yday\000"
.LASF72:
	.ascii	"_inc\000"
.LASF45:
	.ascii	"_ind\000"
.LASF24:
	.ascii	"_next\000"
.LASF113:
	.ascii	"_mbsrtowcs_state\000"
.LASF129:
	.ascii	"s8_t\000"
.LASF126:
	.ascii	"_tzname\000"
.LASF20:
	.ascii	"__value\000"
.LASF80:
	.ascii	"_p5s\000"
.LASF115:
	.ascii	"_wcsrtombs_state\000"
.LASF105:
	.ascii	"_mblen_state\000"
.LASF163:
	.ascii	"client_data\000"
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
.LASF168:
	.ascii	"igmp_mac_filter\000"
.LASF22:
	.ascii	"_flock_t\000"
.LASF156:
	.ascii	"NETIF_ADD_MAC_FILTER\000"
.LASF16:
	.ascii	"__wch\000"
.LASF93:
	.ascii	"_iobs\000"
.LASF58:
	.ascii	"_close\000"
.LASF76:
	.ascii	"__sdidinit\000"
.LASF124:
	.ascii	"_timezone\000"
.LASF69:
	.ascii	"_stdin\000"
.LASF102:
	.ascii	"_gamma_signgam\000"
.LASF158:
	.ascii	"netmask\000"
.LASF8:
	.ascii	"long long int\000"
.LASF48:
	.ascii	"_base\000"
.LASF81:
	.ascii	"_freelist\000"
.LASF96:
	.ascii	"_mult\000"
.LASF23:
	.ascii	"__ULong\000"
.LASF114:
	.ascii	"_wcrtomb_state\000"
.LASF128:
	.ascii	"u8_t\000"
.LASF52:
	.ascii	"_file\000"
.LASF77:
	.ascii	"__cleanup\000"
.LASF21:
	.ascii	"_mbstate_t\000"
.LASF154:
	.ascii	"memp_pools\000"
.LASF152:
	.ascii	"size\000"
.LASF142:
	.ascii	"in6addr_any\000"
.LASF38:
	.ascii	"__tm_isdst\000"
.LASF116:
	.ascii	"_h_errno\000"
.LASF174:
	.ascii	"netif_default\000"
.LASF155:
	.ascii	"NETIF_DEL_MAC_FILTER\000"
.LASF34:
	.ascii	"__tm_mon\000"
.LASF11:
	.ascii	"long double\000"
.LASF122:
	.ascii	"uint16_t\000"
.LASF56:
	.ascii	"_write\000"
.LASF44:
	.ascii	"_atexit\000"
.LASF65:
	.ascii	"_mbstate\000"
.LASF131:
	.ascii	"u32_t\000"
.LASF2:
	.ascii	"short int\000"
.LASF134:
	.ascii	"ip4_addr_t\000"
.LASF4:
	.ascii	"long int\000"
.LASF88:
	.ascii	"__sf\000"
.LASF26:
	.ascii	"_sign\000"
.LASF63:
	.ascii	"_data\000"
.LASF17:
	.ascii	"__wchb\000"
.LASF121:
	.ascii	"_global_impure_ptr\000"
.LASF187:
	.ascii	"mDNSPlatformCustomInit\000"
.LASF35:
	.ascii	"__tm_year\000"
.LASF132:
	.ascii	"ip4_addr\000"
.LASF101:
	.ascii	"_localtime_buf\000"
.LASF119:
	.ascii	"_unused\000"
.LASF84:
	.ascii	"_new\000"
.LASF82:
	.ascii	"_cvtlen\000"
.LASF25:
	.ascii	"_maxwds\000"
.LASF108:
	.ascii	"_l64a_buf\000"
.LASF171:
	.ascii	"netif_linkoutput_fn\000"
.LASF164:
	.ascii	"rs_count\000"
.LASF61:
	.ascii	"_blksize\000"
.LASF29:
	.ascii	"__tm\000"
.LASF64:
	.ascii	"_lock\000"
.LASF141:
	.ascii	"in6_addr\000"
.LASF18:
	.ascii	"sizetype\000"
.LASF7:
	.ascii	"long unsigned int\000"
.LASF185:
	.ascii	"netif_mac_filter_action\000"
.LASF92:
	.ascii	"_niobs\000"
.LASF15:
	.ascii	"wint_t\000"
.LASF140:
	.ascii	"u8_addr\000"
.LASF182:
	.ascii	"../../../component/common/network/mDNS/mDNSPlatform"
	.ascii	".c\000"
.LASF41:
	.ascii	"_dso_handle\000"
.LASF162:
	.ascii	"state\000"
.LASF148:
	.ascii	"type\000"
.LASF83:
	.ascii	"_cvtbuf\000"
.LASF1:
	.ascii	"unsigned char\000"
.LASF6:
	.ascii	"__uint32_t\000"
.LASF169:
	.ascii	"netif_input_fn\000"
.LASF176:
	.ascii	"mDNSPlatformInetAddr\000"
.LASF110:
	.ascii	"_getdate_err\000"
.LASF144:
	.ascii	"pbuf\000"
.LASF97:
	.ascii	"_add\000"
.LASF133:
	.ascii	"addr\000"
.LASF139:
	.ascii	"u32_addr\000"
.LASF47:
	.ascii	"__sbuf\000"
.LASF91:
	.ascii	"_glue\000"
.LASF157:
	.ascii	"netif\000"
.LASF136:
	.ascii	"ip_addr_any\000"
.LASF87:
	.ascii	"__sglue\000"
.LASF99:
	.ascii	"_strtok_last\000"
.LASF106:
	.ascii	"_mbtowc_state\000"
.LASF186:
	.ascii	"mDNSPlatformHostname\000"
.LASF172:
	.ascii	"netif_igmp_mac_filter_fn\000"
.LASF75:
	.ascii	"_locale\000"
.LASF151:
	.ascii	"memp_desc\000"
.LASF40:
	.ascii	"_fnargs\000"
.LASF0:
	.ascii	"signed char\000"
.LASF67:
	.ascii	"_reent\000"
.LASF3:
	.ascii	"short unsigned int\000"
.LASF42:
	.ascii	"_fntypes\000"
.LASF49:
	.ascii	"_size\000"
.LASF135:
	.ascii	"ip_addr_t\000"
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
.LASF95:
	.ascii	"_seed\000"
.LASF103:
	.ascii	"_rand_next\000"
.LASF184:
	.ascii	"__locale_t\000"
.LASF57:
	.ascii	"_seek\000"
.LASF71:
	.ascii	"_stderr\000"
.LASF118:
	.ascii	"_nmalloc\000"
.LASF59:
	.ascii	"_ubuf\000"
	.ident	"GCC: (Realtek ASDK-6.5.0 Build 3215) 6.5.0"
