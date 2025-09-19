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
	.file	"hids.c"
	.text
.Ltext0:
	.cfi_sections	.debug_frame
	.section	.text.hids_attr_read_cb,"ax",%progbits
	.align	1
	.p2align 2,,3
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	hids_attr_read_cb, %function
hids_attr_read_cb:
.LFB1:
	.file 1 "../../../component/common/bluetooth/realtek/sdk/src/ble/profile/server/hids.c"
	.loc 1 507 0
	.cfi_startproc
	@ args = 8, pretend = 0, frame = 16
	@ frame_needed = 0, uses_anonymous_args = 0
.LVL0:
	.loc 1 510 0
	movs	r3, #2
.LVL1:
	.loc 1 507 0
	push	{lr}
	.cfi_def_cfa_offset 4
	.cfi_offset 14, -4
	.loc 1 515 0
	subs	r2, r2, #2
.LVL2:
	.loc 1 507 0
	sub	sp, sp, #20
	.cfi_def_cfa_offset 24
	.loc 1 511 0
	strb	r0, [sp]
	.loc 1 510 0
	strb	r3, [sp, #1]
	.loc 1 515 0
	cmp	r2, #25
	bhi	.L2
	tbb	[pc, r2]
.L4:
	.byte	(.L3-.L4)/2
	.byte	(.L2-.L4)/2
	.byte	(.L8-.L4)/2
	.byte	(.L2-.L4)/2
	.byte	(.L2-.L4)/2
	.byte	(.L2-.L4)/2
	.byte	(.L8-.L4)/2
	.byte	(.L2-.L4)/2
	.byte	(.L2-.L4)/2
	.byte	(.L8-.L4)/2
	.byte	(.L2-.L4)/2
	.byte	(.L2-.L4)/2
	.byte	(.L8-.L4)/2
	.byte	(.L6-.L4)/2
	.byte	(.L2-.L4)/2
	.byte	(.L8-.L4)/2
	.byte	(.L2-.L4)/2
	.byte	(.L2-.L4)/2
	.byte	(.L8-.L4)/2
	.byte	(.L2-.L4)/2
	.byte	(.L8-.L4)/2
	.byte	(.L2-.L4)/2
	.byte	(.L2-.L4)/2
	.byte	(.L7-.L4)/2
	.byte	(.L2-.L4)/2
	.byte	(.L8-.L4)/2
	.p2align 1
.L8:
	.loc 1 508 0
	movs	r0, #0
.LVL3:
	.loc 1 568 0
	add	sp, sp, #20
	.cfi_remember_state
	.cfi_def_cfa_offset 4
.LVL4:
	@ sp needed
	ldr	pc, [sp], #4
.LVL5:
.L3:
	.cfi_restore_state
	.loc 1 522 0
	movs	r2, #2
	.loc 1 523 0
	ldr	r3, .L11
	.loc 1 522 0
	strb	r2, [sp, #4]
	.loc 1 523 0
	mov	r0, r1
.LVL6:
	ldr	r3, [r3]
	mov	r1, sp
.LVL7:
	blx	r3
.LVL8:
	.loc 1 525 0
	movs	r3, #1
	.loc 1 524 0
	ldr	r2, .L11+4
	ldr	r1, [sp, #28]
	str	r2, [r1]
	.loc 1 525 0
	ldr	r2, [sp, #24]
	strh	r3, [r2]	@ movhi
	.loc 1 568 0
	add	sp, sp, #20
	.cfi_remember_state
	.cfi_def_cfa_offset 4
	@ sp needed
	ldr	pc, [sp], #4
.LVL9:
.L7:
	.cfi_restore_state
	.loc 1 557 0
	movs	r2, #25
	.loc 1 558 0
	ldr	r3, .L11
	.loc 1 557 0
	strb	r2, [sp, #4]
	.loc 1 558 0
	mov	r0, r1
.LVL10:
	ldr	r3, [r3]
	mov	r1, sp
.LVL11:
	blx	r3
.LVL12:
	.loc 1 560 0
	movs	r3, #4
	.loc 1 559 0
	ldr	r2, .L11+8
	ldr	r1, [sp, #28]
	str	r2, [r1]
	.loc 1 560 0
	ldr	r2, [sp, #24]
	strh	r3, [r2]	@ movhi
	.loc 1 568 0
	add	sp, sp, #20
	.cfi_remember_state
	.cfi_def_cfa_offset 4
	@ sp needed
	ldr	pc, [sp], #4
.LVL13:
.L6:
	.cfi_restore_state
	.loc 1 541 0
	movs	r2, #15
	.loc 1 542 0
	ldr	r3, .L11
	.loc 1 541 0
	strb	r2, [sp, #4]
	.loc 1 542 0
	mov	r0, r1
.LVL14:
	ldr	r3, [r3]
	mov	r1, sp
.LVL15:
	blx	r3
.LVL16:
	.loc 1 544 0
	movs	r3, #2
	.loc 1 543 0
	ldr	r2, .L11+12
	ldr	r1, [sp, #28]
	str	r2, [r1]
	.loc 1 544 0
	ldr	r2, [sp, #24]
	strh	r3, [r2]	@ movhi
	.loc 1 568 0
	add	sp, sp, #20
	.cfi_remember_state
	.cfi_def_cfa_offset 4
	@ sp needed
	ldr	pc, [sp], #4
.LVL17:
.L2:
	.cfi_restore_state
	.loc 1 518 0
	movw	r0, #1034
.LVL18:
	.loc 1 568 0
	add	sp, sp, #20
	.cfi_def_cfa_offset 4
.LVL19:
	@ sp needed
	ldr	pc, [sp], #4
.LVL20:
.L12:
	.align	2
.L11:
	.word	.LANCHOR0
	.word	.LANCHOR1
	.word	.LANCHOR3
	.word	.LANCHOR2
	.cfi_endproc
.LFE1:
	.size	hids_attr_read_cb, .-hids_attr_read_cb
	.section	.text.hids_attr_write_cb,"ax",%progbits
	.align	1
	.p2align 2,,3
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	hids_attr_write_cb, %function
hids_attr_write_cb:
.LFB2:
	.loc 1 574 0
	.cfi_startproc
	@ args = 12, pretend = 0, frame = 16
	@ frame_needed = 0, uses_anonymous_args = 0
.LVL21:
	push	{r4, r5, lr}
	.cfi_def_cfa_offset 12
	.cfi_offset 4, -12
	.cfi_offset 5, -8
	.cfi_offset 14, -4
	.loc 1 577 0
	movs	r5, #3
	.loc 1 574 0
	sub	sp, sp, #20
	.cfi_def_cfa_offset 32
	.loc 1 574 0
	ldr	r4, [sp, #36]
.LVL22:
	.loc 1 577 0
	strb	r5, [sp, #1]
	.loc 1 579 0
	cbz	r4, .L17
	cmp	r2, #27
	bls	.L22
.LVL23:
.L19:
	movw	r0, #1034
.LVL24:
.L20:
	.loc 1 632 0
	add	sp, sp, #20
	.cfi_remember_state
	.cfi_def_cfa_offset 12
	@ sp needed
	pop	{r4, r5, pc}
.LVL25:
.L22:
	.cfi_restore_state
	movs	r0, #1
.LVL26:
	ldr	r5, .L24
	lsl	r2, r0, r2
.LVL27:
	ands	r5, r5, r2
	cbnz	r5, .L15
	lsls	r2, r2, #29
	bpl	.L19
	.loc 1 593 0
	ldrb	r2, [r4]	@ zero_extendqisi2
.LBB4:
.LBB5:
	.loc 1 455 0
	ldr	r0, .L24+4
.LBE5:
.LBE4:
	.loc 1 593 0
	strb	r2, [sp, #8]
.LVL28:
	.loc 1 592 0
	strb	r3, [sp, #4]
.LBB7:
.LBB6:
	.loc 1 455 0
	strb	r2, [r0]
.LVL29:
.L15:
.LBE6:
.LBE7:
	.loc 1 625 0
	ldr	r3, .L24+8
.LVL30:
	ldr	r3, [r3]
	cbz	r3, .L23
	mov	r0, r1
	.loc 1 627 0
	mov	r1, sp
.LVL31:
	blx	r3
.LVL32:
	movs	r0, #0
	.loc 1 632 0
	add	sp, sp, #20
	.cfi_remember_state
	.cfi_def_cfa_offset 12
	@ sp needed
	pop	{r4, r5, pc}
.LVL33:
.L17:
	.cfi_restore_state
	.loc 1 582 0
	movw	r0, #1028
.LVL34:
	.loc 1 632 0
	add	sp, sp, #20
	.cfi_remember_state
	.cfi_def_cfa_offset 12
	@ sp needed
	pop	{r4, r5, pc}
.LVL35:
.L23:
	.cfi_restore_state
	.loc 1 625 0
	mov	r0, r3
	b	.L20
.L25:
	.align	2
.L24:
	.word	173164816
	.word	.LANCHOR1
	.word	.LANCHOR0
	.cfi_endproc
.LFE2:
	.size	hids_attr_write_cb, .-hids_attr_write_cb
	.section	.text.hids_cccd_update_cb,"ax",%progbits
	.align	1
	.p2align 2,,3
	.global	hids_cccd_update_cb
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	hids_cccd_update_cb, %function
hids_cccd_update_cb:
.LFB3:
	.loc 1 635 0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 16
	@ frame_needed = 0, uses_anonymous_args = 0
.LVL36:
	push	{r4, r5, r6, r7, lr}
	.cfi_def_cfa_offset 20
	.cfi_offset 4, -20
	.cfi_offset 5, -16
	.cfi_offset 6, -12
	.cfi_offset 7, -8
	.cfi_offset 14, -4
	mov	r4, r2
	.loc 1 639 0
	movs	r6, #1
	.loc 1 635 0
	sub	sp, sp, #28
	.cfi_def_cfa_offset 48
.LBB8:
	.loc 1 641 0
	str	r3, [sp]
.LBE8:
	.loc 1 638 0
	strb	r0, [sp, #8]
	.loc 1 635 0
	mov	r5, r3
	mov	r7, r1
.LBB9:
	.loc 1 641 0
	mov	r3, r2
.LVL37:
	ldr	r1, .L40
.LVL38:
	movs	r2, #2
.LVL39:
	ldr	r0, .L40+4
.LVL40:
.LBE9:
	.loc 1 639 0
	strb	r6, [sp, #9]
.LBB10:
	.loc 1 641 0
	bl	trace_log_buffer
.LVL41:
.LBE10:
	.loc 1 643 0
	cmp	r4, #18
	beq	.L39
	cmp	r4, #23
	beq	.L39
	cmp	r4, #5
	beq	.L39
.L26:
	.loc 1 698 0
	add	sp, sp, #28
	.cfi_remember_state
	.cfi_def_cfa_offset 20
	@ sp needed
	pop	{r4, r5, r6, r7, pc}
.L39:
	.cfi_restore_state
	.loc 1 652 0
	lsls	r3, r5, #31
	.loc 1 654 0
	ite	mi
	movmi	r3, #0
	.loc 1 658 0
	movpl	r3, #1
	strb	r3, [sp, #13]
	.loc 1 692 0
	ldr	r3, .L40+8
	.loc 1 651 0
	strb	r4, [sp, #12]
	.loc 1 692 0
	ldr	r3, [r3]
	cmp	r3, #0
	beq	.L26
	.loc 1 694 0
	mov	r0, r7
	add	r1, sp, #8
	blx	r3
.LVL42:
	.loc 1 698 0
	add	sp, sp, #28
	.cfi_def_cfa_offset 20
	@ sp needed
	pop	{r4, r5, r6, r7, pc}
.L41:
	.align	2
.L40:
	.word	.LANCHOR4
	.word	1058025474
	.word	.LANCHOR0
	.cfi_endproc
.LFE3:
	.size	hids_cccd_update_cb, .-hids_cccd_update_cb
	.section	.text.hids_set_parameter,"ax",%progbits
	.align	1
	.p2align 2,,3
	.global	hids_set_parameter
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	hids_set_parameter, %function
hids_set_parameter:
.LFB0:
	.loc 1 448 0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
.LVL43:
	.loc 1 451 0
	subs	r0, r0, #1
.LVL44:
	.loc 1 448 0
	push	{r3, lr}
	.cfi_def_cfa_offset 8
	.cfi_offset 3, -8
	.cfi_offset 14, -4
	.loc 1 451 0
	cmp	r0, #10
	bhi	.L43
	tbb	[pc, r0]
.L45:
	.byte	(.L44-.L45)/2
	.byte	(.L50-.L45)/2
	.byte	(.L50-.L45)/2
	.byte	(.L50-.L45)/2
	.byte	(.L50-.L45)/2
	.byte	(.L47-.L45)/2
	.byte	(.L50-.L45)/2
	.byte	(.L50-.L45)/2
	.byte	(.L50-.L45)/2
	.byte	(.L48-.L45)/2
	.byte	(.L49-.L45)/2
	.p2align 1
.L50:
	.loc 1 449 0
	movs	r0, #1
.LVL45:
	.loc 1 501 0
	pop	{r3, pc}
.LVL46:
.L44:
	.loc 1 455 0
	ldrb	r2, [r2]	@ zero_extendqisi2
.LVL47:
	ldr	r3, .L52
	.loc 1 449 0
	movs	r0, #1
	.loc 1 455 0
	strb	r2, [r3]
	.loc 1 457 0
	pop	{r3, pc}
.LVL48:
.L49:
	.loc 1 493 0
	ldrb	r2, [r2]	@ zero_extendqisi2
.LVL49:
	ldr	r3, .L52+4
	.loc 1 449 0
	movs	r0, #1
	.loc 1 493 0
	strb	r2, [r3]
	.loc 1 494 0
	pop	{r3, pc}
.LVL50:
.L48:
	mov	r3, r2
	.loc 1 488 0
	ldr	r0, .L52+8
	mov	r2, r1
.LVL51:
	mov	r1, r3
.LVL52:
	bl	memcpy
.LVL53:
	.loc 1 449 0
	movs	r0, #1
	.loc 1 490 0
	pop	{r3, pc}
.LVL54:
.L47:
	.loc 1 473 0
	ldrh	r2, [r2]
.LVL55:
	ldr	r3, .L52+12
	.loc 1 449 0
	movs	r0, #1
	.loc 1 473 0
	strh	r2, [r3]	@ movhi
	.loc 1 475 0
	pop	{r3, pc}
.LVL56:
.L43:
	.loc 1 497 0
	movs	r0, #0
	pop	{r3, pc}
.L53:
	.align	2
.L52:
	.word	.LANCHOR1
	.word	.LANCHOR5
	.word	.LANCHOR3
	.word	.LANCHOR2
	.cfi_endproc
.LFE0:
	.size	hids_set_parameter, .-hids_set_parameter
	.section	.text.hids_send_report,"ax",%progbits
	.align	1
	.p2align 2,,3
	.global	hids_send_report
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	hids_send_report, %function
hids_send_report:
.LFB4:
	.loc 1 727 0
	.cfi_startproc
	@ args = 4, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
.LVL57:
	push	{r4, r5, r6, r7, r8, r9, lr}
	.cfi_def_cfa_offset 28
	.cfi_offset 4, -28
	.cfi_offset 5, -24
	.cfi_offset 6, -20
	.cfi_offset 7, -16
	.cfi_offset 8, -12
	.cfi_offset 9, -8
	.cfi_offset 14, -4
	mov	r6, r0
	mov	r7, r1
	mov	r8, r2
	mov	r9, r3
	.loc 1 729 0
	movs	r5, #1
	.loc 1 727 0
	sub	sp, sp, #12
	.cfi_def_cfa_offset 40
	.loc 1 727 0
	ldrh	r4, [sp, #40]
.LBB11:
	.loc 1 728 0
	movs	r2, #1
.LVL58:
	mov	r3, r4
.LVL59:
	ldr	r1, .L56
.LVL60:
	ldr	r0, .L56+4
.LVL61:
	bl	trace_log_buffer
.LVL62:
.LBE11:
	.loc 1 729 0
	str	r4, [sp]
	mov	r3, r9
	mov	r2, r8
	mov	r1, r7
	mov	r0, r6
	str	r5, [sp, #4]
	bl	server_send_data
.LVL63:
	.loc 1 730 0
	add	sp, sp, #12
	.cfi_def_cfa_offset 28
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r9, pc}
.LVL64:
.L57:
	.align	2
.L56:
	.word	.LANCHOR4+48
	.word	1058025474
	.cfi_endproc
.LFE4:
	.size	hids_send_report, .-hids_send_report
	.section	.text.hids_add_service,"ax",%progbits
	.align	1
	.p2align 2,,3
	.global	hids_add_service
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	hids_add_service, %function
hids_add_service:
.LFB5:
	.loc 1 762 0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 0, uses_anonymous_args = 0
.LVL65:
	push	{r4, lr}
	.cfi_def_cfa_offset 8
	.cfi_offset 4, -8
	.cfi_offset 14, -4
	.loc 1 764 0
	ldr	r3, .L62
	ldr	r2, .L62+4
	.loc 1 762 0
	sub	sp, sp, #16
	.cfi_def_cfa_offset 24
	.loc 1 764 0
	adds	r1, r3, #4
	ldrh	r2, [r2]
	.loc 1 762 0
	mov	r4, r0
	.loc 1 764 0
	ldm	r1, {r0, r1}
.LVL66:
	ldr	r3, [r3]
	stm	sp, {r0, r1}
	ldr	r1, .L62+8
	add	r0, sp, #15
	bl	server_add_service
.LVL67:
	.loc 1 764 0
	cbz	r0, .L59
	ldrb	r0, [sp, #15]	@ zero_extendqisi2
	.loc 1 770 0
	ldr	r3, .L62+12
	str	r4, [r3]
	.loc 1 772 0
	add	sp, sp, #16
	.cfi_remember_state
	.cfi_def_cfa_offset 8
	@ sp needed
	pop	{r4, pc}
.LVL68:
.L59:
	.cfi_restore_state
.LBB12:
	.loc 1 766 0
	ldrb	r3, [sp, #15]	@ zero_extendqisi2
	movs	r2, #1
	ldr	r1, .L62+16
	ldr	r0, .L62+20
	bl	trace_log_buffer
.LVL69:
	movs	r0, #255
.LBE12:
	.loc 1 770 0
	ldr	r3, .L62+12
	str	r4, [r3]
	.loc 1 772 0
	add	sp, sp, #16
	.cfi_def_cfa_offset 8
	@ sp needed
	pop	{r4, pc}
.LVL70:
.L63:
	.align	2
.L62:
	.word	.LANCHOR6
	.word	.LANCHOR7
	.word	.LANCHOR8
	.word	.LANCHOR0
	.word	.LANCHOR4+80
	.word	1058025472
	.cfi_endproc
.LFE5:
	.size	hids_add_service, .-hids_add_service
	.global	hids_cbs
	.global	hids_attr_tbl_len
	.global	external_report_refer
	.global	hid_suspand_mode
	.global	hid_protocol_mode
	.global	hid_info
	.section	.BTTRACE,"a",%progbits
	.align	2
	.set	.LANCHOR4,. + 0
	.type	format.5416, %object
	.size	format.5416, 46
format.5416:
	.ascii	"!**hids_cccd_update_cb index = %d ccc_bits %x\000"
	.space	2
	.type	format.5429, %object
	.size	format.5429, 32
format.5429:
	.ascii	"!**hids_send_report data_len %d\000"
	.type	format.5436, %object
	.size	format.5436, 34
format.5436:
	.ascii	"!!!hids_add_service: ServiceId %d\000"
	.section	.bss.external_report_refer,"aw",%nobits
	.align	1
	.set	.LANCHOR2,. + 0
	.type	external_report_refer, %object
	.size	external_report_refer, 2
external_report_refer:
	.space	2
	.section	.bss.hid_info,"aw",%nobits
	.align	2
	.set	.LANCHOR3,. + 0
	.type	hid_info, %object
	.size	hid_info, 4
hid_info:
	.space	4
	.section	.bss.hid_protocol_mode,"aw",%nobits
	.set	.LANCHOR1,. + 0
	.type	hid_protocol_mode, %object
	.size	hid_protocol_mode, 1
hid_protocol_mode:
	.space	1
	.section	.bss.hid_suspand_mode,"aw",%nobits
	.set	.LANCHOR5,. + 0
	.type	hid_suspand_mode, %object
	.size	hid_suspand_mode, 1
hid_suspand_mode:
	.space	1
	.section	.bss.pfn_hids_cb,"aw",%nobits
	.align	2
	.set	.LANCHOR0,. + 0
	.type	pfn_hids_cb, %object
	.size	pfn_hids_cb, 4
pfn_hids_cb:
	.space	4
	.section	.data.hids_attr_tbl_len,"aw",%progbits
	.align	1
	.set	.LANCHOR7,. + 0
	.type	hids_attr_tbl_len, %object
	.size	hids_attr_tbl_len, 2
hids_attr_tbl_len:
	.short	784
	.section	.rodata.hids_attr_tbl,"a",%progbits
	.align	2
	.set	.LANCHOR8,. + 0
	.type	hids_attr_tbl, %object
	.size	hids_attr_tbl, 784
hids_attr_tbl:
	.short	2050
	.byte	0
	.byte	40
	.byte	18
	.byte	24
	.space	12
	.short	2
	.word	0
	.word	1
	.short	2
	.byte	3
	.byte	40
	.byte	6
	.space	13
	.short	1
	.word	0
	.word	1
	.short	4
	.byte	78
	.byte	42
	.space	14
	.short	0
	.word	0
	.word	17
	.short	2
	.byte	3
	.byte	40
	.byte	26
	.space	13
	.short	1
	.word	0
	.word	1
	.short	4
	.byte	77
	.byte	42
	.space	14
	.short	0
	.word	0
	.word	17
	.short	18
	.byte	2
	.byte	41
	.byte	0
	.byte	0
	.space	12
	.short	2
	.word	0
	.word	17
	.short	18
	.byte	8
	.byte	41
	.byte	0
	.byte	1
	.space	12
	.short	2
	.word	0
	.word	1
	.short	2
	.byte	3
	.byte	40
	.byte	14
	.space	13
	.short	1
	.word	0
	.word	1
	.short	4
	.byte	77
	.byte	42
	.space	14
	.short	0
	.word	0
	.word	17
	.short	18
	.byte	8
	.byte	41
	.byte	0
	.byte	2
	.space	12
	.short	2
	.word	0
	.word	1
	.short	2
	.byte	3
	.byte	40
	.byte	10
	.space	13
	.short	1
	.word	0
	.word	1
	.short	4
	.byte	77
	.byte	42
	.space	14
	.short	0
	.word	0
	.word	17
	.short	18
	.byte	8
	.byte	41
	.byte	0
	.byte	3
	.space	12
	.short	2
	.word	0
	.word	1
	.short	2
	.byte	3
	.byte	40
	.byte	2
	.space	13
	.short	1
	.word	0
	.word	1
	.short	4
	.byte	75
	.byte	42
	.space	14
	.short	0
	.word	0
	.word	1
	.short	4
	.byte	7
	.byte	41
	.space	14
	.short	0
	.word	0
	.word	1
	.short	2
	.byte	3
	.byte	40
	.byte	26
	.space	13
	.short	1
	.word	0
	.word	2
	.short	4
	.byte	34
	.byte	42
	.space	14
	.short	0
	.word	0
	.word	34
	.short	18
	.byte	2
	.byte	41
	.byte	0
	.byte	0
	.space	12
	.short	2
	.word	0
	.word	34
	.short	2
	.byte	3
	.byte	40
	.byte	14
	.space	13
	.short	1
	.word	0
	.word	2
	.short	4
	.byte	50
	.byte	42
	.space	14
	.short	0
	.word	0
	.word	34
	.short	2
	.byte	3
	.byte	40
	.byte	26
	.space	13
	.short	1
	.word	0
	.word	1
	.short	4
	.byte	51
	.byte	42
	.space	14
	.short	0
	.word	0
	.word	17
	.short	18
	.byte	2
	.byte	41
	.byte	0
	.byte	0
	.space	12
	.short	2
	.word	0
	.word	34
	.short	2
	.byte	3
	.byte	40
	.byte	2
	.space	13
	.short	1
	.word	0
	.word	1
	.short	4
	.byte	74
	.byte	42
	.space	14
	.short	0
	.word	0
	.word	1
	.short	2
	.byte	3
	.byte	40
	.byte	4
	.space	13
	.short	1
	.word	0
	.word	1
	.short	4
	.byte	76
	.byte	42
	.space	14
	.short	0
	.word	0
	.word	17
	.section	.rodata.hids_cbs,"a",%progbits
	.align	2
	.set	.LANCHOR6,. + 0
	.type	hids_cbs, %object
	.size	hids_cbs, 12
hids_cbs:
	.word	hids_attr_read_cb
	.word	hids_attr_write_cb
	.word	hids_cccd_update_cb
	.text
.Letext0:
	.file 2 "/cygdrive/d/PUYA/HE3/sdk-ameba-v7.1d/tools/arm-none-eabi-gcc/asdk/cygwin/newlib/arm-none-eabi/include/machine/_default_types.h"
	.file 3 "/cygdrive/d/PUYA/HE3/sdk-ameba-v7.1d/tools/arm-none-eabi-gcc/asdk/cygwin/newlib/arm-none-eabi/include/sys/lock.h"
	.file 4 "/cygdrive/d/PUYA/HE3/sdk-ameba-v7.1d/tools/arm-none-eabi-gcc/asdk/cygwin/newlib/arm-none-eabi/include/sys/_types.h"
	.file 5 "/cygdrive/d/PUYA/HE3/sdk-ameba-v7.1d/tools/arm-none-eabi-gcc/asdk/cygwin/newlib/lib/gcc/arm-none-eabi/6.5.0/include/stddef.h"
	.file 6 "/cygdrive/d/PUYA/HE3/sdk-ameba-v7.1d/tools/arm-none-eabi-gcc/asdk/cygwin/newlib/arm-none-eabi/include/sys/reent.h"
	.file 7 "/cygdrive/d/PUYA/HE3/sdk-ameba-v7.1d/tools/arm-none-eabi-gcc/asdk/cygwin/newlib/arm-none-eabi/include/sys/_stdint.h"
	.file 8 "/cygdrive/d/PUYA/HE3/sdk-ameba-v7.1d/tools/arm-none-eabi-gcc/asdk/cygwin/newlib/arm-none-eabi/include/time.h"
	.file 9 "../../../component/common/bluetooth/realtek/sdk/inc/platform/trace.h"
	.file 10 "../../../component/common/bluetooth/realtek/sdk/inc/bluetooth/profile/gatt.h"
	.file 11 "../../../component/common/bluetooth/realtek/sdk/inc/bluetooth/gap/gap.h"
	.file 12 "../../../component/common/bluetooth/realtek/sdk/inc/bluetooth/gap/gap_storage_le.h"
	.file 13 "../../../component/common/bluetooth/realtek/sdk/inc/bluetooth/profile/profile_server.h"
	.file 14 "../../../component/common/bluetooth/realtek/sdk/inc/bluetooth/profile/server/hids.h"
	.section	.debug_info,"",%progbits
.Ldebug_info0:
	.4byte	0x1588
	.2byte	0x3
	.4byte	.Ldebug_abbrev0
	.byte	0x4
	.uleb128 0x1
	.4byte	.LASF322
	.byte	0xc
	.4byte	.LASF323
	.4byte	.LASF324
	.4byte	.Ldebug_ranges0+0x38
	.4byte	0
	.4byte	0
	.4byte	.Ldebug_line0
	.uleb128 0x2
	.byte	0x1
	.byte	0x6
	.4byte	.LASF0
	.uleb128 0x3
	.4byte	.LASF3
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
	.uleb128 0x3
	.4byte	.LASF4
	.byte	0x2
	.byte	0x39
	.4byte	0x54
	.uleb128 0x2
	.byte	0x2
	.byte	0x7
	.4byte	.LASF5
	.uleb128 0x2
	.byte	0x4
	.byte	0x5
	.4byte	.LASF6
	.uleb128 0x3
	.4byte	.LASF7
	.byte	0x2
	.byte	0x4f
	.4byte	0x6d
	.uleb128 0x2
	.byte	0x4
	.byte	0x7
	.4byte	.LASF8
	.uleb128 0x2
	.byte	0x8
	.byte	0x5
	.4byte	.LASF9
	.uleb128 0x2
	.byte	0x8
	.byte	0x7
	.4byte	.LASF10
	.uleb128 0x4
	.byte	0x4
	.byte	0x5
	.ascii	"int\000"
	.uleb128 0x2
	.byte	0x4
	.byte	0x7
	.4byte	.LASF11
	.uleb128 0x2
	.byte	0x8
	.byte	0x4
	.4byte	.LASF12
	.uleb128 0x3
	.4byte	.LASF13
	.byte	0x3
	.byte	0x7
	.4byte	0x82
	.uleb128 0x3
	.4byte	.LASF14
	.byte	0x4
	.byte	0x2c
	.4byte	0x5b
	.uleb128 0x3
	.4byte	.LASF15
	.byte	0x4
	.byte	0x72
	.4byte	0x5b
	.uleb128 0x5
	.4byte	.LASF16
	.byte	0x5
	.2byte	0x165
	.4byte	0x89
	.uleb128 0x6
	.byte	0x4
	.byte	0x4
	.byte	0xa6
	.4byte	0xe3
	.uleb128 0x7
	.4byte	.LASF17
	.byte	0x4
	.byte	0xa8
	.4byte	0xb8
	.uleb128 0x7
	.4byte	.LASF18
	.byte	0x4
	.byte	0xa9
	.4byte	0xe3
	.byte	0
	.uleb128 0x8
	.4byte	0x3b
	.4byte	0xf3
	.uleb128 0x9
	.4byte	0xf3
	.byte	0x3
	.byte	0
	.uleb128 0x2
	.byte	0x4
	.byte	0x7
	.4byte	.LASF19
	.uleb128 0xa
	.byte	0x8
	.byte	0x4
	.byte	0xa3
	.4byte	0x11b
	.uleb128 0xb
	.4byte	.LASF20
	.byte	0x4
	.byte	0xa5
	.4byte	0x82
	.byte	0
	.uleb128 0xb
	.4byte	.LASF21
	.byte	0x4
	.byte	0xaa
	.4byte	0xc4
	.byte	0x4
	.byte	0
	.uleb128 0x3
	.4byte	.LASF22
	.byte	0x4
	.byte	0xab
	.4byte	0xfa
	.uleb128 0x3
	.4byte	.LASF23
	.byte	0x4
	.byte	0xaf
	.4byte	0x97
	.uleb128 0xc
	.byte	0x4
	.uleb128 0x3
	.4byte	.LASF24
	.byte	0x6
	.byte	0x16
	.4byte	0x6d
	.uleb128 0xd
	.4byte	.LASF29
	.byte	0x18
	.byte	0x6
	.byte	0x2f
	.4byte	0x191
	.uleb128 0xb
	.4byte	.LASF25
	.byte	0x6
	.byte	0x31
	.4byte	0x191
	.byte	0
	.uleb128 0xe
	.ascii	"_k\000"
	.byte	0x6
	.byte	0x32
	.4byte	0x82
	.byte	0x4
	.uleb128 0xb
	.4byte	.LASF26
	.byte	0x6
	.byte	0x32
	.4byte	0x82
	.byte	0x8
	.uleb128 0xb
	.4byte	.LASF27
	.byte	0x6
	.byte	0x32
	.4byte	0x82
	.byte	0xc
	.uleb128 0xb
	.4byte	.LASF28
	.byte	0x6
	.byte	0x32
	.4byte	0x82
	.byte	0x10
	.uleb128 0xe
	.ascii	"_x\000"
	.byte	0x6
	.byte	0x33
	.4byte	0x197
	.byte	0x14
	.byte	0
	.uleb128 0xf
	.byte	0x4
	.4byte	0x13e
	.uleb128 0x8
	.4byte	0x133
	.4byte	0x1a7
	.uleb128 0x9
	.4byte	0xf3
	.byte	0
	.byte	0
	.uleb128 0xd
	.4byte	.LASF30
	.byte	0x24
	.byte	0x6
	.byte	0x37
	.4byte	0x220
	.uleb128 0xb
	.4byte	.LASF31
	.byte	0x6
	.byte	0x39
	.4byte	0x82
	.byte	0
	.uleb128 0xb
	.4byte	.LASF32
	.byte	0x6
	.byte	0x3a
	.4byte	0x82
	.byte	0x4
	.uleb128 0xb
	.4byte	.LASF33
	.byte	0x6
	.byte	0x3b
	.4byte	0x82
	.byte	0x8
	.uleb128 0xb
	.4byte	.LASF34
	.byte	0x6
	.byte	0x3c
	.4byte	0x82
	.byte	0xc
	.uleb128 0xb
	.4byte	.LASF35
	.byte	0x6
	.byte	0x3d
	.4byte	0x82
	.byte	0x10
	.uleb128 0xb
	.4byte	.LASF36
	.byte	0x6
	.byte	0x3e
	.4byte	0x82
	.byte	0x14
	.uleb128 0xb
	.4byte	.LASF37
	.byte	0x6
	.byte	0x3f
	.4byte	0x82
	.byte	0x18
	.uleb128 0xb
	.4byte	.LASF38
	.byte	0x6
	.byte	0x40
	.4byte	0x82
	.byte	0x1c
	.uleb128 0xb
	.4byte	.LASF39
	.byte	0x6
	.byte	0x41
	.4byte	0x82
	.byte	0x20
	.byte	0
	.uleb128 0x10
	.4byte	.LASF40
	.2byte	0x108
	.byte	0x6
	.byte	0x4a
	.4byte	0x260
	.uleb128 0xb
	.4byte	.LASF41
	.byte	0x6
	.byte	0x4b
	.4byte	0x260
	.byte	0
	.uleb128 0xb
	.4byte	.LASF42
	.byte	0x6
	.byte	0x4c
	.4byte	0x260
	.byte	0x80
	.uleb128 0x11
	.4byte	.LASF43
	.byte	0x6
	.byte	0x4e
	.4byte	0x133
	.2byte	0x100
	.uleb128 0x11
	.4byte	.LASF44
	.byte	0x6
	.byte	0x51
	.4byte	0x133
	.2byte	0x104
	.byte	0
	.uleb128 0x8
	.4byte	0x131
	.4byte	0x270
	.uleb128 0x9
	.4byte	0xf3
	.byte	0x1f
	.byte	0
	.uleb128 0x10
	.4byte	.LASF45
	.2byte	0x190
	.byte	0x6
	.byte	0x5d
	.4byte	0x2ae
	.uleb128 0xb
	.4byte	.LASF25
	.byte	0x6
	.byte	0x5e
	.4byte	0x2ae
	.byte	0
	.uleb128 0xb
	.4byte	.LASF46
	.byte	0x6
	.byte	0x5f
	.4byte	0x82
	.byte	0x4
	.uleb128 0xb
	.4byte	.LASF47
	.byte	0x6
	.byte	0x61
	.4byte	0x2b4
	.byte	0x8
	.uleb128 0xb
	.4byte	.LASF40
	.byte	0x6
	.byte	0x62
	.4byte	0x220
	.byte	0x88
	.byte	0
	.uleb128 0xf
	.byte	0x4
	.4byte	0x270
	.uleb128 0x8
	.4byte	0x2c4
	.4byte	0x2c4
	.uleb128 0x9
	.4byte	0xf3
	.byte	0x1f
	.byte	0
	.uleb128 0xf
	.byte	0x4
	.4byte	0x2ca
	.uleb128 0x12
	.byte	0x1
	.uleb128 0xd
	.4byte	.LASF48
	.byte	0x8
	.byte	0x6
	.byte	0x75
	.4byte	0x2f1
	.uleb128 0xb
	.4byte	.LASF49
	.byte	0x6
	.byte	0x76
	.4byte	0x2f1
	.byte	0
	.uleb128 0xb
	.4byte	.LASF50
	.byte	0x6
	.byte	0x77
	.4byte	0x82
	.byte	0x4
	.byte	0
	.uleb128 0xf
	.byte	0x4
	.4byte	0x3b
	.uleb128 0xd
	.4byte	.LASF51
	.byte	0x68
	.byte	0x6
	.byte	0xb5
	.4byte	0x421
	.uleb128 0xe
	.ascii	"_p\000"
	.byte	0x6
	.byte	0xb6
	.4byte	0x2f1
	.byte	0
	.uleb128 0xe
	.ascii	"_r\000"
	.byte	0x6
	.byte	0xb7
	.4byte	0x82
	.byte	0x4
	.uleb128 0xe
	.ascii	"_w\000"
	.byte	0x6
	.byte	0xb8
	.4byte	0x82
	.byte	0x8
	.uleb128 0xb
	.4byte	.LASF52
	.byte	0x6
	.byte	0xb9
	.4byte	0x42
	.byte	0xc
	.uleb128 0xb
	.4byte	.LASF53
	.byte	0x6
	.byte	0xba
	.4byte	0x42
	.byte	0xe
	.uleb128 0xe
	.ascii	"_bf\000"
	.byte	0x6
	.byte	0xbb
	.4byte	0x2cc
	.byte	0x10
	.uleb128 0xb
	.4byte	.LASF54
	.byte	0x6
	.byte	0xbc
	.4byte	0x82
	.byte	0x18
	.uleb128 0xb
	.4byte	.LASF55
	.byte	0x6
	.byte	0xc3
	.4byte	0x131
	.byte	0x1c
	.uleb128 0xb
	.4byte	.LASF56
	.byte	0x6
	.byte	0xc5
	.4byte	0x58f
	.byte	0x20
	.uleb128 0xb
	.4byte	.LASF57
	.byte	0x6
	.byte	0xc7
	.4byte	0x5ba
	.byte	0x24
	.uleb128 0xb
	.4byte	.LASF58
	.byte	0x6
	.byte	0xca
	.4byte	0x5df
	.byte	0x28
	.uleb128 0xb
	.4byte	.LASF59
	.byte	0x6
	.byte	0xcb
	.4byte	0x5fa
	.byte	0x2c
	.uleb128 0xe
	.ascii	"_ub\000"
	.byte	0x6
	.byte	0xce
	.4byte	0x2cc
	.byte	0x30
	.uleb128 0xe
	.ascii	"_up\000"
	.byte	0x6
	.byte	0xcf
	.4byte	0x2f1
	.byte	0x38
	.uleb128 0xe
	.ascii	"_ur\000"
	.byte	0x6
	.byte	0xd0
	.4byte	0x82
	.byte	0x3c
	.uleb128 0xb
	.4byte	.LASF60
	.byte	0x6
	.byte	0xd3
	.4byte	0x600
	.byte	0x40
	.uleb128 0xb
	.4byte	.LASF61
	.byte	0x6
	.byte	0xd4
	.4byte	0x610
	.byte	0x43
	.uleb128 0xe
	.ascii	"_lb\000"
	.byte	0x6
	.byte	0xd7
	.4byte	0x2cc
	.byte	0x44
	.uleb128 0xb
	.4byte	.LASF62
	.byte	0x6
	.byte	0xda
	.4byte	0x82
	.byte	0x4c
	.uleb128 0xb
	.4byte	.LASF63
	.byte	0x6
	.byte	0xdb
	.4byte	0xa2
	.byte	0x50
	.uleb128 0xb
	.4byte	.LASF64
	.byte	0x6
	.byte	0xde
	.4byte	0x440
	.byte	0x54
	.uleb128 0xb
	.4byte	.LASF65
	.byte	0x6
	.byte	0xe2
	.4byte	0x126
	.byte	0x58
	.uleb128 0xb
	.4byte	.LASF66
	.byte	0x6
	.byte	0xe4
	.4byte	0x11b
	.byte	0x5c
	.uleb128 0xb
	.4byte	.LASF67
	.byte	0x6
	.byte	0xe5
	.4byte	0x82
	.byte	0x64
	.byte	0
	.uleb128 0x13
	.byte	0x1
	.4byte	0x82
	.4byte	0x440
	.uleb128 0x14
	.4byte	0x440
	.uleb128 0x14
	.4byte	0x131
	.uleb128 0x14
	.4byte	0x57d
	.uleb128 0x14
	.4byte	0x82
	.byte	0
	.uleb128 0xf
	.byte	0x4
	.4byte	0x44b
	.uleb128 0x15
	.4byte	0x440
	.uleb128 0x16
	.4byte	.LASF68
	.2byte	0x428
	.byte	0x6
	.2byte	0x239
	.4byte	0x57d
	.uleb128 0x17
	.4byte	.LASF69
	.byte	0x6
	.2byte	0x23b
	.4byte	0x82
	.byte	0
	.uleb128 0x17
	.4byte	.LASF70
	.byte	0x6
	.2byte	0x240
	.4byte	0x667
	.byte	0x4
	.uleb128 0x17
	.4byte	.LASF71
	.byte	0x6
	.2byte	0x240
	.4byte	0x667
	.byte	0x8
	.uleb128 0x17
	.4byte	.LASF72
	.byte	0x6
	.2byte	0x240
	.4byte	0x667
	.byte	0xc
	.uleb128 0x17
	.4byte	.LASF73
	.byte	0x6
	.2byte	0x242
	.4byte	0x82
	.byte	0x10
	.uleb128 0x17
	.4byte	.LASF74
	.byte	0x6
	.2byte	0x243
	.4byte	0x849
	.byte	0x14
	.uleb128 0x17
	.4byte	.LASF75
	.byte	0x6
	.2byte	0x246
	.4byte	0x82
	.byte	0x30
	.uleb128 0x17
	.4byte	.LASF76
	.byte	0x6
	.2byte	0x247
	.4byte	0x85f
	.byte	0x34
	.uleb128 0x17
	.4byte	.LASF77
	.byte	0x6
	.2byte	0x249
	.4byte	0x82
	.byte	0x38
	.uleb128 0x17
	.4byte	.LASF78
	.byte	0x6
	.2byte	0x24b
	.4byte	0x871
	.byte	0x3c
	.uleb128 0x17
	.4byte	.LASF79
	.byte	0x6
	.2byte	0x24e
	.4byte	0x191
	.byte	0x40
	.uleb128 0x17
	.4byte	.LASF80
	.byte	0x6
	.2byte	0x24f
	.4byte	0x82
	.byte	0x44
	.uleb128 0x17
	.4byte	.LASF81
	.byte	0x6
	.2byte	0x250
	.4byte	0x191
	.byte	0x48
	.uleb128 0x17
	.4byte	.LASF82
	.byte	0x6
	.2byte	0x251
	.4byte	0x877
	.byte	0x4c
	.uleb128 0x17
	.4byte	.LASF83
	.byte	0x6
	.2byte	0x254
	.4byte	0x82
	.byte	0x50
	.uleb128 0x17
	.4byte	.LASF84
	.byte	0x6
	.2byte	0x255
	.4byte	0x57d
	.byte	0x54
	.uleb128 0x17
	.4byte	.LASF85
	.byte	0x6
	.2byte	0x278
	.4byte	0x827
	.byte	0x58
	.uleb128 0x18
	.4byte	.LASF45
	.byte	0x6
	.2byte	0x27c
	.4byte	0x2ae
	.2byte	0x148
	.uleb128 0x18
	.4byte	.LASF86
	.byte	0x6
	.2byte	0x27d
	.4byte	0x270
	.2byte	0x14c
	.uleb128 0x18
	.4byte	.LASF87
	.byte	0x6
	.2byte	0x281
	.4byte	0x889
	.2byte	0x2dc
	.uleb128 0x18
	.4byte	.LASF88
	.byte	0x6
	.2byte	0x286
	.4byte	0x62c
	.2byte	0x2e0
	.uleb128 0x18
	.4byte	.LASF89
	.byte	0x6
	.2byte	0x287
	.4byte	0x895
	.2byte	0x2ec
	.byte	0
	.uleb128 0xf
	.byte	0x4
	.4byte	0x583
	.uleb128 0x2
	.byte	0x1
	.byte	0x8
	.4byte	.LASF90
	.uleb128 0x15
	.4byte	0x583
	.uleb128 0xf
	.byte	0x4
	.4byte	0x421
	.uleb128 0x13
	.byte	0x1
	.4byte	0x82
	.4byte	0x5b4
	.uleb128 0x14
	.4byte	0x440
	.uleb128 0x14
	.4byte	0x131
	.uleb128 0x14
	.4byte	0x5b4
	.uleb128 0x14
	.4byte	0x82
	.byte	0
	.uleb128 0xf
	.byte	0x4
	.4byte	0x58a
	.uleb128 0xf
	.byte	0x4
	.4byte	0x595
	.uleb128 0x13
	.byte	0x1
	.4byte	0xad
	.4byte	0x5df
	.uleb128 0x14
	.4byte	0x440
	.uleb128 0x14
	.4byte	0x131
	.uleb128 0x14
	.4byte	0xad
	.uleb128 0x14
	.4byte	0x82
	.byte	0
	.uleb128 0xf
	.byte	0x4
	.4byte	0x5c0
	.uleb128 0x13
	.byte	0x1
	.4byte	0x82
	.4byte	0x5fa
	.uleb128 0x14
	.4byte	0x440
	.uleb128 0x14
	.4byte	0x131
	.byte	0
	.uleb128 0xf
	.byte	0x4
	.4byte	0x5e5
	.uleb128 0x8
	.4byte	0x3b
	.4byte	0x610
	.uleb128 0x9
	.4byte	0xf3
	.byte	0x2
	.byte	0
	.uleb128 0x8
	.4byte	0x3b
	.4byte	0x620
	.uleb128 0x9
	.4byte	0xf3
	.byte	0
	.byte	0
	.uleb128 0x5
	.4byte	.LASF91
	.byte	0x6
	.2byte	0x11f
	.4byte	0x2f7
	.uleb128 0x19
	.4byte	.LASF92
	.byte	0xc
	.byte	0x6
	.2byte	0x123
	.4byte	0x661
	.uleb128 0x17
	.4byte	.LASF25
	.byte	0x6
	.2byte	0x125
	.4byte	0x661
	.byte	0
	.uleb128 0x17
	.4byte	.LASF93
	.byte	0x6
	.2byte	0x126
	.4byte	0x82
	.byte	0x4
	.uleb128 0x17
	.4byte	.LASF94
	.byte	0x6
	.2byte	0x127
	.4byte	0x667
	.byte	0x8
	.byte	0
	.uleb128 0xf
	.byte	0x4
	.4byte	0x62c
	.uleb128 0xf
	.byte	0x4
	.4byte	0x620
	.uleb128 0x19
	.4byte	.LASF95
	.byte	0xe
	.byte	0x6
	.2byte	0x13f
	.4byte	0x6a2
	.uleb128 0x17
	.4byte	.LASF96
	.byte	0x6
	.2byte	0x140
	.4byte	0x6a2
	.byte	0
	.uleb128 0x17
	.4byte	.LASF97
	.byte	0x6
	.2byte	0x141
	.4byte	0x6a2
	.byte	0x6
	.uleb128 0x17
	.4byte	.LASF98
	.byte	0x6
	.2byte	0x142
	.4byte	0x54
	.byte	0xc
	.byte	0
	.uleb128 0x8
	.4byte	0x54
	.4byte	0x6b2
	.uleb128 0x9
	.4byte	0xf3
	.byte	0x2
	.byte	0
	.uleb128 0x1a
	.byte	0xd0
	.byte	0x6
	.2byte	0x259
	.4byte	0x7b3
	.uleb128 0x17
	.4byte	.LASF99
	.byte	0x6
	.2byte	0x25b
	.4byte	0x89
	.byte	0
	.uleb128 0x17
	.4byte	.LASF100
	.byte	0x6
	.2byte	0x25c
	.4byte	0x57d
	.byte	0x4
	.uleb128 0x17
	.4byte	.LASF101
	.byte	0x6
	.2byte	0x25d
	.4byte	0x7b3
	.byte	0x8
	.uleb128 0x17
	.4byte	.LASF102
	.byte	0x6
	.2byte	0x25e
	.4byte	0x1a7
	.byte	0x24
	.uleb128 0x17
	.4byte	.LASF103
	.byte	0x6
	.2byte	0x25f
	.4byte	0x82
	.byte	0x48
	.uleb128 0x17
	.4byte	.LASF104
	.byte	0x6
	.2byte	0x260
	.4byte	0x7b
	.byte	0x50
	.uleb128 0x17
	.4byte	.LASF105
	.byte	0x6
	.2byte	0x261
	.4byte	0x66d
	.byte	0x58
	.uleb128 0x17
	.4byte	.LASF106
	.byte	0x6
	.2byte	0x262
	.4byte	0x11b
	.byte	0x68
	.uleb128 0x17
	.4byte	.LASF107
	.byte	0x6
	.2byte	0x263
	.4byte	0x11b
	.byte	0x70
	.uleb128 0x17
	.4byte	.LASF108
	.byte	0x6
	.2byte	0x264
	.4byte	0x11b
	.byte	0x78
	.uleb128 0x17
	.4byte	.LASF109
	.byte	0x6
	.2byte	0x265
	.4byte	0x7c3
	.byte	0x80
	.uleb128 0x17
	.4byte	.LASF110
	.byte	0x6
	.2byte	0x266
	.4byte	0x7d3
	.byte	0x88
	.uleb128 0x17
	.4byte	.LASF111
	.byte	0x6
	.2byte	0x267
	.4byte	0x82
	.byte	0xa0
	.uleb128 0x17
	.4byte	.LASF112
	.byte	0x6
	.2byte	0x268
	.4byte	0x11b
	.byte	0xa4
	.uleb128 0x17
	.4byte	.LASF113
	.byte	0x6
	.2byte	0x269
	.4byte	0x11b
	.byte	0xac
	.uleb128 0x17
	.4byte	.LASF114
	.byte	0x6
	.2byte	0x26a
	.4byte	0x11b
	.byte	0xb4
	.uleb128 0x17
	.4byte	.LASF115
	.byte	0x6
	.2byte	0x26b
	.4byte	0x11b
	.byte	0xbc
	.uleb128 0x17
	.4byte	.LASF116
	.byte	0x6
	.2byte	0x26c
	.4byte	0x11b
	.byte	0xc4
	.uleb128 0x17
	.4byte	.LASF117
	.byte	0x6
	.2byte	0x26d
	.4byte	0x82
	.byte	0xcc
	.byte	0
	.uleb128 0x8
	.4byte	0x583
	.4byte	0x7c3
	.uleb128 0x9
	.4byte	0xf3
	.byte	0x19
	.byte	0
	.uleb128 0x8
	.4byte	0x583
	.4byte	0x7d3
	.uleb128 0x9
	.4byte	0xf3
	.byte	0x7
	.byte	0
	.uleb128 0x8
	.4byte	0x583
	.4byte	0x7e3
	.uleb128 0x9
	.4byte	0xf3
	.byte	0x17
	.byte	0
	.uleb128 0x1a
	.byte	0xf0
	.byte	0x6
	.2byte	0x272
	.4byte	0x807
	.uleb128 0x17
	.4byte	.LASF118
	.byte	0x6
	.2byte	0x275
	.4byte	0x807
	.byte	0
	.uleb128 0x17
	.4byte	.LASF119
	.byte	0x6
	.2byte	0x276
	.4byte	0x817
	.byte	0x78
	.byte	0
	.uleb128 0x8
	.4byte	0x2f1
	.4byte	0x817
	.uleb128 0x9
	.4byte	0xf3
	.byte	0x1d
	.byte	0
	.uleb128 0x8
	.4byte	0x89
	.4byte	0x827
	.uleb128 0x9
	.4byte	0xf3
	.byte	0x1d
	.byte	0
	.uleb128 0x1b
	.byte	0xf0
	.byte	0x6
	.2byte	0x257
	.4byte	0x849
	.uleb128 0x1c
	.4byte	.LASF68
	.byte	0x6
	.2byte	0x26e
	.4byte	0x6b2
	.uleb128 0x1c
	.4byte	.LASF120
	.byte	0x6
	.2byte	0x277
	.4byte	0x7e3
	.byte	0
	.uleb128 0x8
	.4byte	0x583
	.4byte	0x859
	.uleb128 0x9
	.4byte	0xf3
	.byte	0x18
	.byte	0
	.uleb128 0x1d
	.4byte	.LASF325
	.byte	0x1
	.uleb128 0xf
	.byte	0x4
	.4byte	0x859
	.uleb128 0x1e
	.byte	0x1
	.4byte	0x871
	.uleb128 0x14
	.4byte	0x440
	.byte	0
	.uleb128 0xf
	.byte	0x4
	.4byte	0x865
	.uleb128 0xf
	.byte	0x4
	.4byte	0x191
	.uleb128 0x1e
	.byte	0x1
	.4byte	0x889
	.uleb128 0x14
	.4byte	0x82
	.byte	0
	.uleb128 0xf
	.byte	0x4
	.4byte	0x88f
	.uleb128 0xf
	.byte	0x4
	.4byte	0x87d
	.uleb128 0x8
	.4byte	0x620
	.4byte	0x8a5
	.uleb128 0x9
	.4byte	0xf3
	.byte	0x2
	.byte	0
	.uleb128 0x1f
	.4byte	.LASF121
	.byte	0x6
	.2byte	0x2fe
	.4byte	0x440
	.byte	0x1
	.byte	0x1
	.uleb128 0x1f
	.4byte	.LASF122
	.byte	0x6
	.2byte	0x2ff
	.4byte	0x446
	.byte	0x1
	.byte	0x1
	.uleb128 0x3
	.4byte	.LASF123
	.byte	0x7
	.byte	0x18
	.4byte	0x30
	.uleb128 0x3
	.4byte	.LASF124
	.byte	0x7
	.byte	0x24
	.4byte	0x49
	.uleb128 0x3
	.4byte	.LASF125
	.byte	0x7
	.byte	0x30
	.4byte	0x62
	.uleb128 0x20
	.4byte	.LASF126
	.byte	0x8
	.byte	0x9a
	.4byte	0x5b
	.byte	0x1
	.byte	0x1
	.uleb128 0x20
	.4byte	.LASF127
	.byte	0x8
	.byte	0x9b
	.4byte	0x82
	.byte	0x1
	.byte	0x1
	.uleb128 0x8
	.4byte	0x57d
	.4byte	0x90c
	.uleb128 0x9
	.4byte	0xf3
	.byte	0x1
	.byte	0
	.uleb128 0x20
	.4byte	.LASF128
	.byte	0x8
	.byte	0x9e
	.4byte	0x8fc
	.byte	0x1
	.byte	0x1
	.uleb128 0x21
	.byte	0x1
	.4byte	0x3b
	.byte	0x9
	.byte	0x3b
	.4byte	0x98c
	.uleb128 0x22
	.4byte	.LASF129
	.byte	0
	.uleb128 0x22
	.4byte	.LASF130
	.byte	0x1
	.uleb128 0x22
	.4byte	.LASF131
	.byte	0x2
	.uleb128 0x22
	.4byte	.LASF132
	.byte	0x3
	.uleb128 0x22
	.4byte	.LASF133
	.byte	0x4
	.uleb128 0x22
	.4byte	.LASF134
	.byte	0x5
	.uleb128 0x22
	.4byte	.LASF135
	.byte	0x6
	.uleb128 0x22
	.4byte	.LASF136
	.byte	0x7
	.uleb128 0x22
	.4byte	.LASF137
	.byte	0x8
	.uleb128 0x22
	.4byte	.LASF138
	.byte	0x9
	.uleb128 0x22
	.4byte	.LASF139
	.byte	0xa
	.uleb128 0x22
	.4byte	.LASF140
	.byte	0xb
	.uleb128 0x22
	.4byte	.LASF141
	.byte	0xc
	.uleb128 0x22
	.4byte	.LASF142
	.byte	0xd
	.uleb128 0x22
	.4byte	.LASF143
	.byte	0xe
	.uleb128 0x22
	.4byte	.LASF144
	.byte	0x10
	.uleb128 0x22
	.4byte	.LASF145
	.byte	0x3f
	.byte	0
	.uleb128 0x21
	.byte	0x1
	.4byte	0x3b
	.byte	0x9
	.byte	0x59
	.4byte	0x9d5
	.uleb128 0x22
	.4byte	.LASF146
	.byte	0
	.uleb128 0x22
	.4byte	.LASF147
	.byte	0x10
	.uleb128 0x22
	.4byte	.LASF148
	.byte	0x11
	.uleb128 0x22
	.4byte	.LASF149
	.byte	0x12
	.uleb128 0x22
	.4byte	.LASF150
	.byte	0x20
	.uleb128 0x22
	.4byte	.LASF151
	.byte	0x28
	.uleb128 0x22
	.4byte	.LASF152
	.byte	0x30
	.uleb128 0x22
	.4byte	.LASF153
	.byte	0x40
	.uleb128 0x22
	.4byte	.LASF154
	.byte	0x50
	.uleb128 0x22
	.4byte	.LASF155
	.byte	0x60
	.byte	0
	.uleb128 0x21
	.byte	0x1
	.4byte	0x3b
	.byte	0x9
	.byte	0x78
	.4byte	0xae4
	.uleb128 0x22
	.4byte	.LASF156
	.byte	0
	.uleb128 0x22
	.4byte	.LASF157
	.byte	0x1
	.uleb128 0x22
	.4byte	.LASF158
	.byte	0x2
	.uleb128 0x22
	.4byte	.LASF159
	.byte	0x3
	.uleb128 0x22
	.4byte	.LASF160
	.byte	0x4
	.uleb128 0x22
	.4byte	.LASF161
	.byte	0x5
	.uleb128 0x22
	.4byte	.LASF162
	.byte	0x6
	.uleb128 0x22
	.4byte	.LASF163
	.byte	0xc
	.uleb128 0x22
	.4byte	.LASF164
	.byte	0xd
	.uleb128 0x22
	.4byte	.LASF165
	.byte	0xe
	.uleb128 0x22
	.4byte	.LASF166
	.byte	0xf
	.uleb128 0x22
	.4byte	.LASF167
	.byte	0x10
	.uleb128 0x22
	.4byte	.LASF168
	.byte	0x11
	.uleb128 0x22
	.4byte	.LASF169
	.byte	0x12
	.uleb128 0x22
	.4byte	.LASF170
	.byte	0x13
	.uleb128 0x22
	.4byte	.LASF171
	.byte	0x14
	.uleb128 0x22
	.4byte	.LASF172
	.byte	0x15
	.uleb128 0x22
	.4byte	.LASF173
	.byte	0x16
	.uleb128 0x22
	.4byte	.LASF174
	.byte	0x17
	.uleb128 0x22
	.4byte	.LASF175
	.byte	0x18
	.uleb128 0x22
	.4byte	.LASF176
	.byte	0x19
	.uleb128 0x22
	.4byte	.LASF177
	.byte	0x1a
	.uleb128 0x22
	.4byte	.LASF178
	.byte	0x1b
	.uleb128 0x22
	.4byte	.LASF179
	.byte	0x1c
	.uleb128 0x22
	.4byte	.LASF180
	.byte	0x1d
	.uleb128 0x22
	.4byte	.LASF181
	.byte	0x1e
	.uleb128 0x22
	.4byte	.LASF182
	.byte	0x30
	.uleb128 0x22
	.4byte	.LASF183
	.byte	0x31
	.uleb128 0x22
	.4byte	.LASF184
	.byte	0x32
	.uleb128 0x22
	.4byte	.LASF185
	.byte	0x33
	.uleb128 0x22
	.4byte	.LASF186
	.byte	0x34
	.uleb128 0x22
	.4byte	.LASF187
	.byte	0x35
	.uleb128 0x22
	.4byte	.LASF188
	.byte	0x36
	.uleb128 0x22
	.4byte	.LASF189
	.byte	0x37
	.uleb128 0x22
	.4byte	.LASF190
	.byte	0x38
	.uleb128 0x22
	.4byte	.LASF191
	.byte	0x39
	.uleb128 0x22
	.4byte	.LASF192
	.byte	0x3a
	.uleb128 0x22
	.4byte	.LASF193
	.byte	0x3b
	.uleb128 0x22
	.4byte	.LASF194
	.byte	0x3c
	.uleb128 0x22
	.4byte	.LASF195
	.byte	0x3d
	.uleb128 0x22
	.4byte	.LASF196
	.byte	0x3e
	.uleb128 0x22
	.4byte	.LASF197
	.byte	0x3f
	.uleb128 0x22
	.4byte	.LASF198
	.byte	0x40
	.byte	0
	.uleb128 0xa
	.byte	0x1c
	.byte	0xa
	.byte	0xfa
	.4byte	0xb2a
	.uleb128 0xb
	.4byte	.LASF199
	.byte	0xa
	.byte	0xfc
	.4byte	0x8cc
	.byte	0
	.uleb128 0xb
	.4byte	.LASF200
	.byte	0xa
	.byte	0xfd
	.4byte	0xb2a
	.byte	0x2
	.uleb128 0xb
	.4byte	.LASF201
	.byte	0xa
	.byte	0xfe
	.4byte	0x8cc
	.byte	0x12
	.uleb128 0xb
	.4byte	.LASF202
	.byte	0xa
	.byte	0xff
	.4byte	0x131
	.byte	0x14
	.uleb128 0x17
	.4byte	.LASF203
	.byte	0xa
	.2byte	0x101
	.4byte	0x8d7
	.byte	0x18
	.byte	0
	.uleb128 0x8
	.4byte	0x8c1
	.4byte	0xb3a
	.uleb128 0x9
	.4byte	0xf3
	.byte	0xf
	.byte	0
	.uleb128 0x5
	.4byte	.LASF204
	.byte	0xa
	.2byte	0x102
	.4byte	0xae4
	.uleb128 0x15
	.4byte	0xb3a
	.uleb128 0x21
	.byte	0x2
	.4byte	0x54
	.byte	0xb
	.byte	0xaf
	.4byte	0xbc0
	.uleb128 0x22
	.4byte	.LASF205
	.byte	0
	.uleb128 0x23
	.4byte	.LASF206
	.2byte	0xd01
	.uleb128 0x23
	.4byte	.LASF207
	.2byte	0xd03
	.uleb128 0x23
	.4byte	.LASF208
	.2byte	0xd04
	.uleb128 0x23
	.4byte	.LASF209
	.2byte	0xd05
	.uleb128 0x23
	.4byte	.LASF210
	.2byte	0x409
	.uleb128 0x23
	.4byte	.LASF211
	.2byte	0x407
	.uleb128 0x23
	.4byte	.LASF212
	.2byte	0x40d
	.uleb128 0x23
	.4byte	.LASF213
	.2byte	0x404
	.uleb128 0x23
	.4byte	.LASF214
	.2byte	0x40a
	.uleb128 0x23
	.4byte	.LASF215
	.2byte	0x40b
	.uleb128 0x23
	.4byte	.LASF216
	.2byte	0x411
	.uleb128 0x23
	.4byte	.LASF217
	.2byte	0x480
	.uleb128 0x23
	.4byte	.LASF218
	.2byte	0x4fd
	.uleb128 0x23
	.4byte	.LASF219
	.2byte	0x4fe
	.byte	0
	.uleb128 0x3
	.4byte	.LASF220
	.byte	0xb
	.byte	0xc0
	.4byte	0xb4b
	.uleb128 0x2
	.byte	0x1
	.byte	0x2
	.4byte	.LASF221
	.uleb128 0x20
	.4byte	.LASF222
	.byte	0xc
	.byte	0x89
	.4byte	0x8c1
	.byte	0x1
	.byte	0x1
	.uleb128 0x3
	.4byte	.LASF223
	.byte	0xd
	.byte	0x40
	.4byte	0x8c1
	.uleb128 0x21
	.byte	0x1
	.4byte	0x3b
	.byte	0xd
	.byte	0x44
	.4byte	0xc0f
	.uleb128 0x22
	.4byte	.LASF224
	.byte	0
	.uleb128 0x22
	.4byte	.LASF225
	.byte	0x1
	.uleb128 0x22
	.4byte	.LASF226
	.byte	0x2
	.uleb128 0x22
	.4byte	.LASF227
	.byte	0x3
	.byte	0
	.uleb128 0x3
	.4byte	.LASF228
	.byte	0xd
	.byte	0x49
	.4byte	0xbea
	.uleb128 0x21
	.byte	0x1
	.4byte	0x3b
	.byte	0xd
	.byte	0x4d
	.4byte	0xc39
	.uleb128 0x22
	.4byte	.LASF229
	.byte	0
	.uleb128 0x22
	.4byte	.LASF230
	.byte	0x1
	.uleb128 0x22
	.4byte	.LASF231
	.byte	0x2
	.byte	0
	.uleb128 0x21
	.byte	0x1
	.4byte	0x3b
	.byte	0xd
	.byte	0x55
	.4byte	0xc58
	.uleb128 0x22
	.4byte	.LASF232
	.byte	0x1
	.uleb128 0x22
	.4byte	.LASF233
	.byte	0x2
	.uleb128 0x22
	.4byte	.LASF234
	.byte	0x3
	.byte	0
	.uleb128 0x3
	.4byte	.LASF235
	.byte	0xd
	.byte	0x59
	.4byte	0xc39
	.uleb128 0x3
	.4byte	.LASF236
	.byte	0xd
	.byte	0x97
	.4byte	0xc6e
	.uleb128 0xf
	.byte	0x4
	.4byte	0xc74
	.uleb128 0x1e
	.byte	0x1
	.4byte	0xc94
	.uleb128 0x14
	.4byte	0x8c1
	.uleb128 0x14
	.4byte	0xbdf
	.uleb128 0x14
	.4byte	0x8cc
	.uleb128 0x14
	.4byte	0x8cc
	.uleb128 0x14
	.4byte	0xc94
	.byte	0
	.uleb128 0xf
	.byte	0x4
	.4byte	0x8c1
	.uleb128 0x3
	.4byte	.LASF237
	.byte	0xd
	.byte	0x9f
	.4byte	0xca5
	.uleb128 0xf
	.byte	0x4
	.4byte	0xcab
	.uleb128 0x13
	.byte	0x1
	.4byte	0xbc0
	.4byte	0xcd4
	.uleb128 0x14
	.4byte	0x8c1
	.uleb128 0x14
	.4byte	0xbdf
	.uleb128 0x14
	.4byte	0x8cc
	.uleb128 0x14
	.4byte	0x8cc
	.uleb128 0x14
	.4byte	0xcd4
	.uleb128 0x14
	.4byte	0xcda
	.byte	0
	.uleb128 0xf
	.byte	0x4
	.4byte	0x8cc
	.uleb128 0xf
	.byte	0x4
	.4byte	0xc94
	.uleb128 0x3
	.4byte	.LASF238
	.byte	0xd
	.byte	0xa2
	.4byte	0xceb
	.uleb128 0xf
	.byte	0x4
	.4byte	0xcf1
	.uleb128 0x13
	.byte	0x1
	.4byte	0xbc0
	.4byte	0xd1f
	.uleb128 0x14
	.4byte	0x8c1
	.uleb128 0x14
	.4byte	0xbdf
	.uleb128 0x14
	.4byte	0x8cc
	.uleb128 0x14
	.4byte	0xc0f
	.uleb128 0x14
	.4byte	0x8cc
	.uleb128 0x14
	.4byte	0xc94
	.uleb128 0x14
	.4byte	0xd1f
	.byte	0
	.uleb128 0xf
	.byte	0x4
	.4byte	0xc63
	.uleb128 0x3
	.4byte	.LASF239
	.byte	0xd
	.byte	0xa5
	.4byte	0xd30
	.uleb128 0xf
	.byte	0x4
	.4byte	0xd36
	.uleb128 0x1e
	.byte	0x1
	.4byte	0xd51
	.uleb128 0x14
	.4byte	0x8c1
	.uleb128 0x14
	.4byte	0xbdf
	.uleb128 0x14
	.4byte	0x8cc
	.uleb128 0x14
	.4byte	0x8cc
	.byte	0
	.uleb128 0x3
	.4byte	.LASF240
	.byte	0xd
	.byte	0xaf
	.4byte	0xd5c
	.uleb128 0xf
	.byte	0x4
	.4byte	0xd62
	.uleb128 0x13
	.byte	0x1
	.4byte	0xbc0
	.4byte	0xd77
	.uleb128 0x14
	.4byte	0xbdf
	.uleb128 0x14
	.4byte	0x131
	.byte	0
	.uleb128 0xa
	.byte	0xc
	.byte	0xd
	.byte	0xb4
	.4byte	0xda4
	.uleb128 0xb
	.4byte	.LASF241
	.byte	0xd
	.byte	0xb6
	.4byte	0xc9a
	.byte	0
	.uleb128 0xb
	.4byte	.LASF242
	.byte	0xd
	.byte	0xb8
	.4byte	0xce0
	.byte	0x4
	.uleb128 0xb
	.4byte	.LASF243
	.byte	0xd
	.byte	0xba
	.4byte	0xd25
	.byte	0x8
	.byte	0
	.uleb128 0x3
	.4byte	.LASF244
	.byte	0xd
	.byte	0xbb
	.4byte	0xd77
	.uleb128 0x15
	.4byte	0xda4
	.uleb128 0x21
	.byte	0x1
	.4byte	0x3b
	.byte	0xe
	.byte	0x54
	.4byte	0xe03
	.uleb128 0x22
	.4byte	.LASF245
	.byte	0x1
	.uleb128 0x22
	.4byte	.LASF246
	.byte	0x2
	.uleb128 0x22
	.4byte	.LASF247
	.byte	0x3
	.uleb128 0x22
	.4byte	.LASF248
	.byte	0x4
	.uleb128 0x22
	.4byte	.LASF249
	.byte	0x5
	.uleb128 0x22
	.4byte	.LASF250
	.byte	0x6
	.uleb128 0x22
	.4byte	.LASF251
	.byte	0x7
	.uleb128 0x22
	.4byte	.LASF252
	.byte	0x8
	.uleb128 0x22
	.4byte	.LASF253
	.byte	0x9
	.uleb128 0x22
	.4byte	.LASF254
	.byte	0xa
	.uleb128 0x22
	.4byte	.LASF255
	.byte	0xb
	.byte	0
	.uleb128 0x3
	.4byte	.LASF256
	.byte	0xe
	.byte	0x60
	.4byte	0xdb4
	.uleb128 0xa
	.byte	0x4
	.byte	0xe
	.byte	0x65
	.4byte	0xe3b
	.uleb128 0xb
	.4byte	.LASF257
	.byte	0xe
	.byte	0x67
	.4byte	0x8c1
	.byte	0
	.uleb128 0xb
	.4byte	.LASF199
	.byte	0xe
	.byte	0x68
	.4byte	0x8c1
	.byte	0x1
	.uleb128 0xb
	.4byte	.LASF258
	.byte	0xe
	.byte	0x69
	.4byte	0x8cc
	.byte	0x2
	.byte	0
	.uleb128 0x3
	.4byte	.LASF259
	.byte	0xe
	.byte	0x6a
	.4byte	0xe0e
	.uleb128 0x21
	.byte	0x1
	.4byte	0x3b
	.byte	0xe
	.byte	0x70
	.4byte	0xe65
	.uleb128 0x22
	.4byte	.LASF260
	.byte	0x1
	.uleb128 0x22
	.4byte	.LASF261
	.byte	0x2
	.uleb128 0x22
	.4byte	.LASF262
	.byte	0x3
	.byte	0
	.uleb128 0x21
	.byte	0x1
	.4byte	0x3b
	.byte	0xe
	.byte	0x83
	.4byte	0xe7e
	.uleb128 0x22
	.4byte	.LASF263
	.byte	0
	.uleb128 0x22
	.4byte	.LASF264
	.byte	0x1
	.byte	0
	.uleb128 0x3
	.4byte	.LASF265
	.byte	0xe
	.byte	0x86
	.4byte	0xe65
	.uleb128 0x21
	.byte	0x1
	.4byte	0x3b
	.byte	0xe
	.byte	0x8d
	.4byte	0xea2
	.uleb128 0x22
	.4byte	.LASF266
	.byte	0
	.uleb128 0x22
	.4byte	.LASF267
	.byte	0x1
	.byte	0
	.uleb128 0x3
	.4byte	.LASF268
	.byte	0xe
	.byte	0x90
	.4byte	0xe89
	.uleb128 0xa
	.byte	0x8
	.byte	0xe
	.byte	0x97
	.4byte	0xece
	.uleb128 0xb
	.4byte	.LASF269
	.byte	0xe
	.byte	0x99
	.4byte	0x8c1
	.byte	0
	.uleb128 0xb
	.4byte	.LASF270
	.byte	0xe
	.byte	0x9a
	.4byte	0xc94
	.byte	0x4
	.byte	0
	.uleb128 0x6
	.byte	0x8
	.byte	0xe
	.byte	0x92
	.4byte	0xf03
	.uleb128 0x7
	.4byte	.LASF271
	.byte	0xe
	.byte	0x94
	.4byte	0x8c1
	.uleb128 0x7
	.4byte	.LASF272
	.byte	0xe
	.byte	0x95
	.4byte	0x8c1
	.uleb128 0x7
	.4byte	.LASF273
	.byte	0xe
	.byte	0x96
	.4byte	0x8c1
	.uleb128 0x7
	.4byte	.LASF274
	.byte	0xe
	.byte	0x9b
	.4byte	0xead
	.byte	0
	.uleb128 0x3
	.4byte	.LASF275
	.byte	0xe
	.byte	0x9c
	.4byte	0xece
	.uleb128 0xa
	.byte	0xc
	.byte	0xe
	.byte	0x9e
	.4byte	0xf2f
	.uleb128 0xb
	.4byte	.LASF276
	.byte	0xe
	.byte	0xa0
	.4byte	0x8c1
	.byte	0
	.uleb128 0xb
	.4byte	.LASF277
	.byte	0xe
	.byte	0xa1
	.4byte	0xf03
	.byte	0x4
	.byte	0
	.uleb128 0x3
	.4byte	.LASF278
	.byte	0xe
	.byte	0xa2
	.4byte	0xf0e
	.uleb128 0xa
	.byte	0x2
	.byte	0xe
	.byte	0xa4
	.4byte	0xf5b
	.uleb128 0xb
	.4byte	.LASF279
	.byte	0xe
	.byte	0xa6
	.4byte	0x8c1
	.byte	0
	.uleb128 0xb
	.4byte	.LASF280
	.byte	0xe
	.byte	0xa7
	.4byte	0xea2
	.byte	0x1
	.byte	0
	.uleb128 0x3
	.4byte	.LASF281
	.byte	0xe
	.byte	0xa8
	.4byte	0xf3a
	.uleb128 0x6
	.byte	0xc
	.byte	0xe
	.byte	0xaa
	.4byte	0xf90
	.uleb128 0x7
	.4byte	.LASF282
	.byte	0xe
	.byte	0xac
	.4byte	0x8c1
	.uleb128 0x7
	.4byte	.LASF283
	.byte	0xe
	.byte	0xad
	.4byte	0xf2f
	.uleb128 0x7
	.4byte	.LASF284
	.byte	0xe
	.byte	0xae
	.4byte	0xf5b
	.byte	0
	.uleb128 0x3
	.4byte	.LASF285
	.byte	0xe
	.byte	0xaf
	.4byte	0xf66
	.uleb128 0xa
	.byte	0x10
	.byte	0xe
	.byte	0xb1
	.4byte	0xfc8
	.uleb128 0xb
	.4byte	.LASF286
	.byte	0xe
	.byte	0xb3
	.4byte	0x8c1
	.byte	0
	.uleb128 0xb
	.4byte	.LASF287
	.byte	0xe
	.byte	0xb4
	.4byte	0xc58
	.byte	0x1
	.uleb128 0xb
	.4byte	.LASF288
	.byte	0xe
	.byte	0xb5
	.4byte	0xf90
	.byte	0x4
	.byte	0
	.uleb128 0x3
	.4byte	.LASF289
	.byte	0xe
	.byte	0xb6
	.4byte	0xf9b
	.uleb128 0x24
	.4byte	.LASF294
	.byte	0x1
	.byte	0x20
	.4byte	0xd51
	.byte	0x5
	.byte	0x3
	.4byte	pfn_hids_cb
	.uleb128 0x25
	.4byte	.LASF290
	.byte	0x1
	.byte	0x22
	.4byte	0xe3b
	.byte	0x1
	.byte	0x5
	.byte	0x3
	.4byte	hid_info
	.uleb128 0x25
	.4byte	.LASF291
	.byte	0x1
	.byte	0x23
	.4byte	0xe7e
	.byte	0x1
	.byte	0x5
	.byte	0x3
	.4byte	hid_protocol_mode
	.uleb128 0x25
	.4byte	.LASF292
	.byte	0x1
	.byte	0x24
	.4byte	0x8c1
	.byte	0x1
	.byte	0x5
	.byte	0x3
	.4byte	hid_suspand_mode
	.uleb128 0x25
	.4byte	.LASF293
	.byte	0x1
	.byte	0x25
	.4byte	0x8cc
	.byte	0x1
	.byte	0x5
	.byte	0x3
	.4byte	external_report_refer
	.uleb128 0x8
	.4byte	0xb46
	.4byte	0x103c
	.uleb128 0x9
	.4byte	0xf3
	.byte	0x1b
	.byte	0
	.uleb128 0x15
	.4byte	0x102c
	.uleb128 0x24
	.4byte	.LASF295
	.byte	0x1
	.byte	0x27
	.4byte	0x103c
	.byte	0x5
	.byte	0x3
	.4byte	hids_attr_tbl
	.uleb128 0x26
	.4byte	.LASF296
	.byte	0x1
	.2byte	0x2de
	.4byte	0x8cc
	.byte	0x1
	.byte	0x5
	.byte	0x3
	.4byte	hids_attr_tbl_len
	.uleb128 0x26
	.4byte	.LASF297
	.byte	0x1
	.2byte	0x2e0
	.4byte	0xdaf
	.byte	0x1
	.byte	0x5
	.byte	0x3
	.4byte	hids_cbs
	.uleb128 0x27
	.byte	0x1
	.4byte	.LASF300
	.byte	0x1
	.2byte	0x2f9
	.byte	0x1
	.4byte	0xbdf
	.4byte	.LFB5
	.4byte	.LFE5
	.byte	0x1
	.byte	0x9c
	.byte	0x1
	.4byte	0x110d
	.uleb128 0x28
	.4byte	.LASF302
	.byte	0x1
	.2byte	0x2f9
	.4byte	0x131
	.4byte	.LLST31
	.uleb128 0x29
	.4byte	.LASF298
	.byte	0x1
	.2byte	0x2fb
	.4byte	0xbdf
	.sleb128 -1
	.uleb128 0x2a
	.4byte	.LBB12
	.4byte	.LBE12
	.4byte	0x10f3
	.uleb128 0x2b
	.4byte	.LASF299
	.byte	0x1
	.2byte	0x2fe
	.4byte	0x111d
	.byte	0x5
	.byte	0x3
	.4byte	format.5436
	.uleb128 0x2c
	.4byte	.LVL69
	.4byte	0x1557
	.uleb128 0x2d
	.byte	0x1
	.byte	0x50
	.byte	0x5
	.byte	0xc
	.4byte	0x3f103000
	.uleb128 0x2d
	.byte	0x1
	.byte	0x51
	.byte	0x5
	.byte	0x3
	.4byte	.LANCHOR4+80
	.uleb128 0x2d
	.byte	0x1
	.byte	0x52
	.byte	0x1
	.byte	0x31
	.byte	0
	.byte	0
	.uleb128 0x2c
	.4byte	.LVL67
	.4byte	0x1564
	.uleb128 0x2d
	.byte	0x1
	.byte	0x50
	.byte	0x2
	.byte	0x91
	.sleb128 -9
	.uleb128 0x2d
	.byte	0x1
	.byte	0x51
	.byte	0x5
	.byte	0x3
	.4byte	.LANCHOR8
	.byte	0
	.byte	0
	.uleb128 0x8
	.4byte	0x58a
	.4byte	0x111d
	.uleb128 0x9
	.4byte	0xf3
	.byte	0x21
	.byte	0
	.uleb128 0x15
	.4byte	0x110d
	.uleb128 0x27
	.byte	0x1
	.4byte	.LASF301
	.byte	0x1
	.2byte	0x2d5
	.byte	0x1
	.4byte	0xbcb
	.4byte	.LFB4
	.4byte	.LFE4
	.byte	0x1
	.byte	0x9c
	.byte	0x1
	.4byte	0x1208
	.uleb128 0x28
	.4byte	.LASF286
	.byte	0x1
	.2byte	0x2d5
	.4byte	0x8c1
	.4byte	.LLST26
	.uleb128 0x28
	.4byte	.LASF298
	.byte	0x1
	.2byte	0x2d5
	.4byte	0xbdf
	.4byte	.LLST27
	.uleb128 0x28
	.4byte	.LASF279
	.byte	0x1
	.2byte	0x2d5
	.4byte	0x8cc
	.4byte	.LLST28
	.uleb128 0x28
	.4byte	.LASF303
	.byte	0x1
	.2byte	0x2d5
	.4byte	0xc94
	.4byte	.LLST29
	.uleb128 0x28
	.4byte	.LASF304
	.byte	0x1
	.2byte	0x2d6
	.4byte	0x8cc
	.4byte	.LLST30
	.uleb128 0x2a
	.4byte	.LBB11
	.4byte	.LBE11
	.4byte	0x11d7
	.uleb128 0x2b
	.4byte	.LASF299
	.byte	0x1
	.2byte	0x2d8
	.4byte	0x1218
	.byte	0x5
	.byte	0x3
	.4byte	format.5429
	.uleb128 0x2c
	.4byte	.LVL62
	.4byte	0x1557
	.uleb128 0x2d
	.byte	0x1
	.byte	0x50
	.byte	0x5
	.byte	0xc
	.4byte	0x3f103002
	.uleb128 0x2d
	.byte	0x1
	.byte	0x51
	.byte	0x5
	.byte	0x3
	.4byte	.LANCHOR4+48
	.uleb128 0x2d
	.byte	0x1
	.byte	0x52
	.byte	0x2
	.byte	0x75
	.sleb128 0
	.uleb128 0x2d
	.byte	0x1
	.byte	0x53
	.byte	0x2
	.byte	0x74
	.sleb128 0
	.byte	0
	.byte	0
	.uleb128 0x2c
	.4byte	.LVL63
	.4byte	0x1572
	.uleb128 0x2d
	.byte	0x1
	.byte	0x50
	.byte	0x2
	.byte	0x76
	.sleb128 0
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
	.byte	0x78
	.sleb128 0
	.uleb128 0x2d
	.byte	0x1
	.byte	0x53
	.byte	0x2
	.byte	0x79
	.sleb128 0
	.uleb128 0x2d
	.byte	0x2
	.byte	0x7d
	.sleb128 0
	.byte	0x2
	.byte	0x74
	.sleb128 0
	.uleb128 0x2d
	.byte	0x2
	.byte	0x7d
	.sleb128 4
	.byte	0x2
	.byte	0x75
	.sleb128 0
	.byte	0
	.byte	0
	.uleb128 0x8
	.4byte	0x58a
	.4byte	0x1218
	.uleb128 0x9
	.4byte	0xf3
	.byte	0x1f
	.byte	0
	.uleb128 0x15
	.4byte	0x1208
	.uleb128 0x2e
	.byte	0x1
	.4byte	.LASF326
	.byte	0x1
	.2byte	0x27a
	.byte	0x1
	.4byte	.LFB3
	.4byte	.LFE3
	.byte	0x1
	.byte	0x9c
	.byte	0x1
	.4byte	0x12ef
	.uleb128 0x28
	.4byte	.LASF286
	.byte	0x1
	.2byte	0x27a
	.4byte	0x8c1
	.4byte	.LLST18
	.uleb128 0x28
	.4byte	.LASF298
	.byte	0x1
	.2byte	0x27a
	.4byte	0xbdf
	.4byte	.LLST19
	.uleb128 0x28
	.4byte	.LASF279
	.byte	0x1
	.2byte	0x27a
	.4byte	0x8cc
	.4byte	.LLST20
	.uleb128 0x28
	.4byte	.LASF305
	.byte	0x1
	.2byte	0x27a
	.4byte	0x8cc
	.4byte	.LLST21
	.uleb128 0x2f
	.4byte	.LASF306
	.byte	0x1
	.2byte	0x27c
	.4byte	0xbcb
	.byte	0x1
	.uleb128 0x2b
	.4byte	.LASF307
	.byte	0x1
	.2byte	0x27d
	.4byte	0xfc8
	.byte	0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0x30
	.4byte	.Ldebug_ranges0+0x18
	.4byte	0x12dc
	.uleb128 0x2b
	.4byte	.LASF299
	.byte	0x1
	.2byte	0x281
	.4byte	0x12ff
	.byte	0x5
	.byte	0x3
	.4byte	format.5416
	.uleb128 0x2c
	.4byte	.LVL41
	.4byte	0x1557
	.uleb128 0x2d
	.byte	0x1
	.byte	0x50
	.byte	0x5
	.byte	0xc
	.4byte	0x3f103002
	.uleb128 0x2d
	.byte	0x1
	.byte	0x51
	.byte	0x5
	.byte	0x3
	.4byte	.LANCHOR4
	.uleb128 0x2d
	.byte	0x1
	.byte	0x52
	.byte	0x1
	.byte	0x32
	.uleb128 0x2d
	.byte	0x1
	.byte	0x53
	.byte	0x2
	.byte	0x74
	.sleb128 0
	.uleb128 0x2d
	.byte	0x2
	.byte	0x7d
	.sleb128 0
	.byte	0x2
	.byte	0x75
	.sleb128 0
	.byte	0
	.byte	0
	.uleb128 0x31
	.4byte	.LVL42
	.uleb128 0x2d
	.byte	0x1
	.byte	0x50
	.byte	0x2
	.byte	0x77
	.sleb128 0
	.uleb128 0x2d
	.byte	0x1
	.byte	0x51
	.byte	0x2
	.byte	0x91
	.sleb128 -40
	.byte	0
	.byte	0
	.uleb128 0x8
	.4byte	0x58a
	.4byte	0x12ff
	.uleb128 0x9
	.4byte	0xf3
	.byte	0x2d
	.byte	0
	.uleb128 0x15
	.4byte	0x12ef
	.uleb128 0x32
	.4byte	.LASF312
	.byte	0x1
	.2byte	0x23b
	.byte	0x1
	.4byte	0xbc0
	.4byte	.LFB2
	.4byte	.LFE2
	.byte	0x1
	.byte	0x9c
	.byte	0x1
	.4byte	0x13f8
	.uleb128 0x28
	.4byte	.LASF286
	.byte	0x1
	.2byte	0x23b
	.4byte	0x8c1
	.4byte	.LLST7
	.uleb128 0x28
	.4byte	.LASF298
	.byte	0x1
	.2byte	0x23b
	.4byte	0xbdf
	.4byte	.LLST8
	.uleb128 0x28
	.4byte	.LASF308
	.byte	0x1
	.2byte	0x23c
	.4byte	0x8cc
	.4byte	.LLST9
	.uleb128 0x28
	.4byte	.LASF276
	.byte	0x1
	.2byte	0x23c
	.4byte	0xc0f
	.4byte	.LLST10
	.uleb128 0x28
	.4byte	.LASF309
	.byte	0x1
	.2byte	0x23d
	.4byte	0x8cc
	.4byte	.LLST11
	.uleb128 0x28
	.4byte	.LASF310
	.byte	0x1
	.2byte	0x23d
	.4byte	0xc94
	.4byte	.LLST12
	.uleb128 0x28
	.4byte	.LASF311
	.byte	0x1
	.2byte	0x23d
	.4byte	0xd1f
	.4byte	.LLST13
	.uleb128 0x2f
	.4byte	.LASF306
	.byte	0x1
	.2byte	0x23f
	.4byte	0xbc0
	.byte	0
	.uleb128 0x2b
	.4byte	.LASF307
	.byte	0x1
	.2byte	0x240
	.4byte	0xfc8
	.byte	0x2
	.byte	0x91
	.sleb128 -32
	.uleb128 0x33
	.4byte	0x14c0
	.4byte	.LBB4
	.4byte	.Ldebug_ranges0+0
	.byte	0x1
	.2byte	0x252
	.4byte	0x13eb
	.uleb128 0x34
	.4byte	0x14eb
	.4byte	.LLST14
	.uleb128 0x34
	.4byte	0x14df
	.4byte	.LLST15
	.uleb128 0x34
	.4byte	0x14d3
	.4byte	.LLST16
	.uleb128 0x35
	.4byte	.Ldebug_ranges0+0
	.uleb128 0x36
	.4byte	0x14f7
	.4byte	.LLST16
	.byte	0
	.byte	0
	.uleb128 0x31
	.4byte	.LVL32
	.uleb128 0x2d
	.byte	0x1
	.byte	0x51
	.byte	0x2
	.byte	0x7d
	.sleb128 0
	.byte	0
	.byte	0
	.uleb128 0x32
	.4byte	.LASF313
	.byte	0x1
	.2byte	0x1f8
	.byte	0x1
	.4byte	0xbc0
	.4byte	.LFB1
	.4byte	.LFE1
	.byte	0x1
	.byte	0x9c
	.byte	0x1
	.4byte	0x14c0
	.uleb128 0x28
	.4byte	.LASF286
	.byte	0x1
	.2byte	0x1f8
	.4byte	0x8c1
	.4byte	.LLST0
	.uleb128 0x28
	.4byte	.LASF298
	.byte	0x1
	.2byte	0x1f8
	.4byte	0xbdf
	.4byte	.LLST1
	.uleb128 0x28
	.4byte	.LASF308
	.byte	0x1
	.2byte	0x1f9
	.4byte	0x8cc
	.4byte	.LLST2
	.uleb128 0x28
	.4byte	.LASF314
	.byte	0x1
	.2byte	0x1fa
	.4byte	0x8cc
	.4byte	.LLST3
	.uleb128 0x28
	.4byte	.LASF315
	.byte	0x1
	.2byte	0x1fa
	.4byte	0xcd4
	.4byte	.LLST4
	.uleb128 0x28
	.4byte	.LASF316
	.byte	0x1
	.2byte	0x1fa
	.4byte	0xcda
	.4byte	.LLST5
	.uleb128 0x37
	.4byte	.LASF306
	.byte	0x1
	.2byte	0x1fc
	.4byte	0xbc0
	.4byte	.LLST6
	.uleb128 0x2b
	.4byte	.LASF307
	.byte	0x1
	.2byte	0x1fd
	.4byte	0xfc8
	.byte	0x2
	.byte	0x91
	.sleb128 -24
	.uleb128 0x38
	.4byte	.LVL8
	.4byte	0x14a3
	.uleb128 0x2d
	.byte	0x1
	.byte	0x51
	.byte	0x2
	.byte	0x7d
	.sleb128 0
	.byte	0
	.uleb128 0x38
	.4byte	.LVL12
	.4byte	0x14b3
	.uleb128 0x2d
	.byte	0x1
	.byte	0x51
	.byte	0x2
	.byte	0x7d
	.sleb128 0
	.byte	0
	.uleb128 0x31
	.4byte	.LVL16
	.uleb128 0x2d
	.byte	0x1
	.byte	0x51
	.byte	0x2
	.byte	0x7d
	.sleb128 0
	.byte	0
	.byte	0
	.uleb128 0x39
	.byte	0x1
	.4byte	.LASF327
	.byte	0x1
	.2byte	0x1bf
	.byte	0x1
	.4byte	0xbcb
	.byte	0x1
	.4byte	0x1504
	.uleb128 0x3a
	.4byte	.LASF317
	.byte	0x1
	.2byte	0x1bf
	.4byte	0xe03
	.uleb128 0x3a
	.4byte	.LASF309
	.byte	0x1
	.2byte	0x1bf
	.4byte	0x8c1
	.uleb128 0x3a
	.4byte	.LASF318
	.byte	0x1
	.2byte	0x1bf
	.4byte	0x131
	.uleb128 0x3b
	.ascii	"ret\000"
	.byte	0x1
	.2byte	0x1c1
	.4byte	0xbcb
	.byte	0
	.uleb128 0x3c
	.4byte	0x14c0
	.4byte	.LFB0
	.4byte	.LFE0
	.byte	0x1
	.byte	0x9c
	.byte	0x1
	.4byte	0x1557
	.uleb128 0x34
	.4byte	0x14d3
	.4byte	.LLST22
	.uleb128 0x34
	.4byte	0x14df
	.4byte	.LLST23
	.uleb128 0x34
	.4byte	0x14eb
	.4byte	.LLST24
	.uleb128 0x36
	.4byte	0x14f7
	.4byte	.LLST25
	.uleb128 0x2c
	.4byte	.LVL53
	.4byte	0x1580
	.uleb128 0x2d
	.byte	0x1
	.byte	0x50
	.byte	0x5
	.byte	0x3
	.4byte	.LANCHOR3
	.uleb128 0x2d
	.byte	0x1
	.byte	0x51
	.byte	0x3
	.byte	0xf3
	.uleb128 0x1
	.byte	0x52
	.byte	0
	.byte	0
	.uleb128 0x3d
	.byte	0x1
	.byte	0x1
	.4byte	.LASF319
	.4byte	.LASF319
	.byte	0x9
	.byte	0xe9
	.uleb128 0x3e
	.byte	0x1
	.byte	0x1
	.4byte	.LASF320
	.4byte	.LASF320
	.byte	0xd
	.2byte	0x10f
	.uleb128 0x3e
	.byte	0x1
	.byte	0x1
	.4byte	.LASF321
	.4byte	.LASF321
	.byte	0xd
	.2byte	0x180
	.uleb128 0x3f
	.byte	0x1
	.byte	0x1
	.4byte	.LASF328
	.4byte	.LASF328
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
	.uleb128 0x28
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1c
	.uleb128 0x5
	.byte	0
	.byte	0
	.uleb128 0x24
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
	.uleb128 0x25
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
	.uleb128 0x2
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0x26
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
	.uleb128 0x2
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0x27
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
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
	.uleb128 0x28
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x6
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
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x1c
	.uleb128 0xd
	.byte	0
	.byte	0
	.uleb128 0x2a
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x2b
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
	.uleb128 0x2
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0x2c
	.uleb128 0x4109
	.byte	0x1
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x31
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
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
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
	.uleb128 0x2f
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
	.uleb128 0x1c
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x30
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x55
	.uleb128 0x6
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x31
	.uleb128 0x4109
	.byte	0x1
	.uleb128 0x11
	.uleb128 0x1
	.byte	0
	.byte	0
	.uleb128 0x32
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
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
	.uleb128 0x33
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
	.uleb128 0x5
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x34
	.uleb128 0x5
	.byte	0
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x35
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x55
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x36
	.uleb128 0x34
	.byte	0
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x37
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
	.uleb128 0x2
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x38
	.uleb128 0x4109
	.byte	0x1
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x39
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x20
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x3a
	.uleb128 0x5
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
	.uleb128 0x3b
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x3c
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
	.uleb128 0x3d
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
	.uleb128 0x3e
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
	.uleb128 0x5
	.byte	0
	.byte	0
	.uleb128 0x3f
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
	.byte	0
	.section	.debug_loc,"",%progbits
.Ldebug_loc0:
.LLST31:
	.4byte	.LVL65
	.4byte	.LVL66
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL66
	.4byte	.LVL70
	.2byte	0x1
	.byte	0x54
	.4byte	.LVL70
	.4byte	.LFE5
	.2byte	0x5
	.byte	0x3
	.4byte	pfn_hids_cb
	.4byte	0
	.4byte	0
.LLST26:
	.4byte	.LVL57
	.4byte	.LVL61
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL61
	.4byte	.LFE4
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x50
	.byte	0x9f
	.4byte	0
	.4byte	0
.LLST27:
	.4byte	.LVL57
	.4byte	.LVL60
	.2byte	0x1
	.byte	0x51
	.4byte	.LVL60
	.4byte	.LFE4
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x51
	.byte	0x9f
	.4byte	0
	.4byte	0
.LLST28:
	.4byte	.LVL57
	.4byte	.LVL58
	.2byte	0x1
	.byte	0x52
	.4byte	.LVL58
	.4byte	.LFE4
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x52
	.byte	0x9f
	.4byte	0
	.4byte	0
.LLST29:
	.4byte	.LVL57
	.4byte	.LVL59
	.2byte	0x1
	.byte	0x53
	.4byte	.LVL59
	.4byte	.LVL64
	.2byte	0x1
	.byte	0x59
	.4byte	.LVL64
	.4byte	.LFE4
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x53
	.byte	0x9f
	.4byte	0
	.4byte	0
.LLST30:
	.4byte	.LVL57
	.4byte	.LVL64
	.2byte	0x2
	.byte	0x91
	.sleb128 0
	.4byte	.LVL64
	.4byte	.LFE4
	.2byte	0x2
	.byte	0x7d
	.sleb128 0
	.4byte	0
	.4byte	0
.LLST18:
	.4byte	.LVL36
	.4byte	.LVL40
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL40
	.4byte	.LVL41-1
	.2byte	0x2
	.byte	0x91
	.sleb128 -40
	.4byte	.LVL41-1
	.4byte	.LFE3
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x50
	.byte	0x9f
	.4byte	0
	.4byte	0
.LLST19:
	.4byte	.LVL36
	.4byte	.LVL38
	.2byte	0x1
	.byte	0x51
	.4byte	.LVL38
	.4byte	.LFE3
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x51
	.byte	0x9f
	.4byte	0
	.4byte	0
.LLST20:
	.4byte	.LVL36
	.4byte	.LVL39
	.2byte	0x1
	.byte	0x52
	.4byte	.LVL39
	.4byte	.LFE3
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x52
	.byte	0x9f
	.4byte	0
	.4byte	0
.LLST21:
	.4byte	.LVL36
	.4byte	.LVL37
	.2byte	0x1
	.byte	0x53
	.4byte	.LVL37
	.4byte	.LFE3
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x53
	.byte	0x9f
	.4byte	0
	.4byte	0
.LLST7:
	.4byte	.LVL21
	.4byte	.LVL23
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL23
	.4byte	.LVL25
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x50
	.byte	0x9f
	.4byte	.LVL25
	.4byte	.LVL26
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL26
	.4byte	.LVL33
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x50
	.byte	0x9f
	.4byte	.LVL33
	.4byte	.LVL34
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL34
	.4byte	.LFE2
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x50
	.byte	0x9f
	.4byte	0
	.4byte	0
.LLST8:
	.4byte	.LVL21
	.4byte	.LVL31
	.2byte	0x1
	.byte	0x51
	.4byte	.LVL31
	.4byte	.LVL33
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x51
	.byte	0x9f
	.4byte	.LVL33
	.4byte	.LFE2
	.2byte	0x1
	.byte	0x51
	.4byte	0
	.4byte	0
.LLST9:
	.4byte	.LVL21
	.4byte	.LVL23
	.2byte	0x1
	.byte	0x52
	.4byte	.LVL23
	.4byte	.LVL25
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x52
	.byte	0x9f
	.4byte	.LVL25
	.4byte	.LVL27
	.2byte	0x1
	.byte	0x52
	.4byte	.LVL27
	.4byte	.LVL33
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x52
	.byte	0x9f
	.4byte	.LVL33
	.4byte	.LVL35
	.2byte	0x1
	.byte	0x52
	.4byte	.LVL35
	.4byte	.LFE2
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x52
	.byte	0x9f
	.4byte	0
	.4byte	0
.LLST10:
	.4byte	.LVL21
	.4byte	.LVL24
	.2byte	0x1
	.byte	0x53
	.4byte	.LVL24
	.4byte	.LVL25
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x53
	.byte	0x9f
	.4byte	.LVL25
	.4byte	.LVL30
	.2byte	0x1
	.byte	0x53
	.4byte	.LVL30
	.4byte	.LVL33
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x53
	.byte	0x9f
	.4byte	.LVL33
	.4byte	.LVL35
	.2byte	0x1
	.byte	0x53
	.4byte	.LVL35
	.4byte	.LFE2
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x53
	.byte	0x9f
	.4byte	0
	.4byte	0
.LLST11:
	.4byte	.LVL21
	.4byte	.LVL25
	.2byte	0x2
	.byte	0x91
	.sleb128 0
	.4byte	.LVL25
	.4byte	.LFE2
	.2byte	0x2
	.byte	0x91
	.sleb128 0
	.4byte	0
	.4byte	0
.LLST12:
	.4byte	.LVL21
	.4byte	.LVL25
	.2byte	0x2
	.byte	0x91
	.sleb128 4
	.4byte	.LVL25
	.4byte	.LFE2
	.2byte	0x2
	.byte	0x91
	.sleb128 4
	.4byte	0
	.4byte	0
.LLST13:
	.4byte	.LVL21
	.4byte	.LVL25
	.2byte	0x2
	.byte	0x91
	.sleb128 8
	.4byte	.LVL25
	.4byte	.LFE2
	.2byte	0x2
	.byte	0x91
	.sleb128 8
	.4byte	0
	.4byte	0
.LLST14:
	.4byte	.LVL28
	.4byte	.LVL29
	.2byte	0x1
	.byte	0x54
	.4byte	0
	.4byte	0
.LLST15:
	.4byte	.LVL28
	.4byte	.LVL29
	.2byte	0x2
	.byte	0x91
	.sleb128 0
	.4byte	0
	.4byte	0
.LLST16:
	.4byte	.LVL28
	.4byte	.LVL29
	.2byte	0x2
	.byte	0x31
	.byte	0x9f
	.4byte	0
	.4byte	0
.LLST0:
	.4byte	.LVL0
	.4byte	.LVL3
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL3
	.4byte	.LVL4
	.2byte	0x2
	.byte	0x7d
	.sleb128 0
	.4byte	.LVL4
	.4byte	.LVL5
	.2byte	0x2
	.byte	0x91
	.sleb128 -24
	.4byte	.LVL5
	.4byte	.LVL6
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL6
	.4byte	.LVL8-1
	.2byte	0x2
	.byte	0x7d
	.sleb128 0
	.4byte	.LVL8-1
	.4byte	.LVL9
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x50
	.byte	0x9f
	.4byte	.LVL9
	.4byte	.LVL10
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL10
	.4byte	.LVL12-1
	.2byte	0x2
	.byte	0x7d
	.sleb128 0
	.4byte	.LVL12-1
	.4byte	.LVL13
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x50
	.byte	0x9f
	.4byte	.LVL13
	.4byte	.LVL14
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL14
	.4byte	.LVL16-1
	.2byte	0x2
	.byte	0x7d
	.sleb128 0
	.4byte	.LVL16-1
	.4byte	.LVL17
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x50
	.byte	0x9f
	.4byte	.LVL17
	.4byte	.LVL18
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL18
	.4byte	.LVL19
	.2byte	0x2
	.byte	0x7d
	.sleb128 0
	.4byte	.LVL19
	.4byte	.LVL20
	.2byte	0x2
	.byte	0x91
	.sleb128 -24
	.4byte	.LVL20
	.4byte	.LFE1
	.2byte	0x2
	.byte	0x7d
	.sleb128 -24
	.4byte	0
	.4byte	0
.LLST1:
	.4byte	.LVL0
	.4byte	.LVL7
	.2byte	0x1
	.byte	0x51
	.4byte	.LVL7
	.4byte	.LVL9
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x51
	.byte	0x9f
	.4byte	.LVL9
	.4byte	.LVL11
	.2byte	0x1
	.byte	0x51
	.4byte	.LVL11
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
	.4byte	.LVL17
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x51
	.byte	0x9f
	.4byte	.LVL17
	.4byte	.LFE1
	.2byte	0x1
	.byte	0x51
	.4byte	0
	.4byte	0
.LLST2:
	.4byte	.LVL0
	.4byte	.LVL2
	.2byte	0x1
	.byte	0x52
	.4byte	.LVL2
	.4byte	.LFE1
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x52
	.byte	0x9f
	.4byte	0
	.4byte	0
.LLST3:
	.4byte	.LVL0
	.4byte	.LVL1
	.2byte	0x1
	.byte	0x53
	.4byte	.LVL1
	.4byte	.LFE1
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x53
	.byte	0x9f
	.4byte	0
	.4byte	0
.LLST4:
	.4byte	.LVL0
	.4byte	.LVL5
	.2byte	0x2
	.byte	0x91
	.sleb128 0
	.4byte	.LVL5
	.4byte	.LVL20
	.2byte	0x2
	.byte	0x91
	.sleb128 0
	.4byte	.LVL20
	.4byte	.LFE1
	.2byte	0x2
	.byte	0x7d
	.sleb128 0
	.4byte	0
	.4byte	0
.LLST5:
	.4byte	.LVL0
	.4byte	.LVL5
	.2byte	0x2
	.byte	0x91
	.sleb128 4
	.4byte	.LVL5
	.4byte	.LVL20
	.2byte	0x2
	.byte	0x91
	.sleb128 4
	.4byte	.LVL20
	.4byte	.LFE1
	.2byte	0x2
	.byte	0x7d
	.sleb128 4
	.4byte	0
	.4byte	0
.LLST6:
	.4byte	.LVL0
	.4byte	.LVL3
	.2byte	0x2
	.byte	0x30
	.byte	0x9f
	.4byte	.LVL3
	.4byte	.LVL5
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL5
	.4byte	.LVL8
	.2byte	0x2
	.byte	0x30
	.byte	0x9f
	.4byte	.LVL8
	.4byte	.LVL9
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL9
	.4byte	.LVL12
	.2byte	0x2
	.byte	0x30
	.byte	0x9f
	.4byte	.LVL12
	.4byte	.LVL13
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL13
	.4byte	.LVL16
	.2byte	0x2
	.byte	0x30
	.byte	0x9f
	.4byte	.LVL16
	.4byte	.LVL17
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL17
	.4byte	.LVL18
	.2byte	0x2
	.byte	0x30
	.byte	0x9f
	.4byte	.LVL18
	.4byte	.LFE1
	.2byte	0x1
	.byte	0x50
	.4byte	0
	.4byte	0
.LLST22:
	.4byte	.LVL43
	.4byte	.LVL44
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL44
	.4byte	.LFE0
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x50
	.byte	0x9f
	.4byte	0
	.4byte	0
.LLST23:
	.4byte	.LVL43
	.4byte	.LVL52
	.2byte	0x1
	.byte	0x51
	.4byte	.LVL52
	.4byte	.LVL54
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x51
	.byte	0x9f
	.4byte	.LVL54
	.4byte	.LFE0
	.2byte	0x1
	.byte	0x51
	.4byte	0
	.4byte	0
.LLST24:
	.4byte	.LVL43
	.4byte	.LVL47
	.2byte	0x1
	.byte	0x52
	.4byte	.LVL47
	.4byte	.LVL48
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x52
	.byte	0x9f
	.4byte	.LVL48
	.4byte	.LVL49
	.2byte	0x1
	.byte	0x52
	.4byte	.LVL49
	.4byte	.LVL50
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x52
	.byte	0x9f
	.4byte	.LVL50
	.4byte	.LVL51
	.2byte	0x1
	.byte	0x52
	.4byte	.LVL51
	.4byte	.LVL53-1
	.2byte	0x1
	.byte	0x53
	.4byte	.LVL53-1
	.4byte	.LVL54
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x52
	.byte	0x9f
	.4byte	.LVL54
	.4byte	.LVL55
	.2byte	0x1
	.byte	0x52
	.4byte	.LVL55
	.4byte	.LVL56
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x52
	.byte	0x9f
	.4byte	.LVL56
	.4byte	.LFE0
	.2byte	0x1
	.byte	0x52
	.4byte	0
	.4byte	0
.LLST25:
	.4byte	.LVL43
	.4byte	.LVL45
	.2byte	0x2
	.byte	0x31
	.byte	0x9f
	.4byte	.LVL45
	.4byte	.LVL46
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL46
	.4byte	.LFE0
	.2byte	0x2
	.byte	0x31
	.byte	0x9f
	.4byte	0
	.4byte	0
	.section	.debug_aranges,"",%progbits
	.4byte	0x44
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
	.4byte	.LFB0
	.4byte	.LFE0-.LFB0
	.4byte	.LFB4
	.4byte	.LFE4-.LFB4
	.4byte	.LFB5
	.4byte	.LFE5-.LFB5
	.4byte	0
	.4byte	0
	.section	.debug_ranges,"",%progbits
.Ldebug_ranges0:
	.4byte	.LBB4
	.4byte	.LBE4
	.4byte	.LBB7
	.4byte	.LBE7
	.4byte	0
	.4byte	0
	.4byte	.LBB8
	.4byte	.LBE8
	.4byte	.LBB9
	.4byte	.LBE9
	.4byte	.LBB10
	.4byte	.LBE10
	.4byte	0
	.4byte	0
	.4byte	.LFB1
	.4byte	.LFE1
	.4byte	.LFB2
	.4byte	.LFE2
	.4byte	.LFB3
	.4byte	.LFE3
	.4byte	.LFB0
	.4byte	.LFE0
	.4byte	.LFB4
	.4byte	.LFE4
	.4byte	.LFB5
	.4byte	.LFE5
	.4byte	0
	.4byte	0
	.section	.debug_line,"",%progbits
.Ldebug_line0:
	.section	.debug_str,"MS",%progbits,1
.LASF264:
	.ascii	"REPORT_PROCOCOL_MODE\000"
.LASF162:
	.ascii	"TRACE_MODULE_FS\000"
.LASF195:
	.ascii	"TRACE_MODULE_SNOOP\000"
.LASF211:
	.ascii	"APP_RESULT_INVALID_OFFSET\000"
.LASF275:
	.ascii	"T_HID_WRITE_PARAMETER\000"
.LASF283:
	.ascii	"write_msg\000"
.LASF322:
	.ascii	"GNU C11 6.5.0 -march=armv8-m.main+dsp -mthumb -mcms"
	.ascii	"e -mfloat-abi=soft -mabi=aapcs -g -gdwarf-3 -gdwarf"
	.ascii	"-3 -O3 -fstack-usage -fdata-sections -ffunction-sec"
	.ascii	"tions\000"
.LASF40:
	.ascii	"_on_exit_args\000"
.LASF127:
	.ascii	"_daylight\000"
.LASF108:
	.ascii	"_wctomb_state\000"
.LASF323:
	.ascii	"../../../component/common/bluetooth/realtek/sdk/src"
	.ascii	"/ble/profile/server/hids.c\000"
.LASF159:
	.ascii	"TRACE_MODULE_BOOT\000"
.LASF161:
	.ascii	"TRACE_MODULE_AES\000"
.LASF199:
	.ascii	"flags\000"
.LASF105:
	.ascii	"_r48\000"
.LASF284:
	.ascii	"not_ind_data\000"
.LASF193:
	.ascii	"TRACE_MODULE_L2CAP\000"
.LASF131:
	.ascii	"TYPE_UPPERSTACK_MESSAGE\000"
.LASF110:
	.ascii	"_signal_buf\000"
.LASF11:
	.ascii	"unsigned int\000"
.LASF303:
	.ascii	"p_data\000"
.LASF160:
	.ascii	"TRACE_MODULE_DLPS\000"
.LASF306:
	.ascii	"cause\000"
.LASF174:
	.ascii	"TRACE_MODULE_FLASH\000"
.LASF54:
	.ascii	"_lbfsize\000"
.LASF52:
	.ascii	"_flags\000"
.LASF250:
	.ascii	"HID_EXTERNAL_REPORT_REFER\000"
.LASF279:
	.ascii	"index\000"
.LASF179:
	.ascii	"TRACE_MODULE_SDIO\000"
.LASF69:
	.ascii	"_errno\000"
.LASF276:
	.ascii	"write_type\000"
.LASF302:
	.ascii	"p_func\000"
.LASF267:
	.ascii	"NOTIFY_DISABLE\000"
.LASF254:
	.ascii	"HID_INFO\000"
.LASF164:
	.ascii	"TRACE_MODULE_QDECODE\000"
.LASF185:
	.ascii	"TRACE_MODULE_PROFILE\000"
.LASF176:
	.ascii	"TRACE_MODULE_PINMUX\000"
.LASF197:
	.ascii	"TRACE_MODULE_LOWERSTACK\000"
.LASF132:
	.ascii	"TYPE_UPPERSTACK_BINARY\000"
.LASF192:
	.ascii	"TRACE_MODULE_SDP\000"
.LASF13:
	.ascii	"_LOCK_RECURSIVE_T\000"
.LASF56:
	.ascii	"_read\000"
.LASF259:
	.ascii	"T_HID_INFO\000"
.LASF112:
	.ascii	"_mbrlen_state\000"
.LASF271:
	.ascii	"voice_enable\000"
.LASF232:
	.ascii	"SERVICE_CALLBACK_TYPE_INDIFICATION_NOTIFICATION\000"
.LASF71:
	.ascii	"_stdout\000"
.LASF281:
	.ascii	"T_HID_NOT_IND_DATA\000"
.LASF15:
	.ascii	"_fpos_t\000"
.LASF181:
	.ascii	"TRACE_MODULE_DSP\000"
.LASF257:
	.ascii	"b_country_code\000"
.LASF47:
	.ascii	"_fns\000"
.LASF238:
	.ascii	"P_FUN_GATT_WRITE_ATTR_CB\000"
.LASF55:
	.ascii	"_cookie\000"
.LASF251:
	.ascii	"HID_BOOT_KB_IN_REPORT\000"
.LASF129:
	.ascii	"TYPE_UPPERSTACK_RESET\000"
.LASF187:
	.ascii	"TRACE_MODULE_GAP\000"
.LASF269:
	.ascii	"reportLen\000"
.LASF29:
	.ascii	"_Bigint\000"
.LASF177:
	.ascii	"TRACE_MODULE_PWM\000"
.LASF37:
	.ascii	"__tm_wday\000"
.LASF134:
	.ascii	"TYPE_UPPERSTACK_BDADDR1\000"
.LASF324:
	.ascii	"/cygdrive/d/PUYA/HE3/sdk-ameba-v7.1d/project/realte"
	.ascii	"k_amebaz2_v0_example/GCC-RELEASE\000"
.LASF79:
	.ascii	"_result\000"
.LASF290:
	.ascii	"hid_info\000"
.LASF125:
	.ascii	"uint32_t\000"
.LASF33:
	.ascii	"__tm_hour\000"
.LASF244:
	.ascii	"T_FUN_GATT_SERVICE_CBS\000"
.LASF20:
	.ascii	"__count\000"
.LASF32:
	.ascii	"__tm_min\000"
.LASF121:
	.ascii	"_impure_ptr\000"
.LASF220:
	.ascii	"T_APP_RESULT\000"
.LASF118:
	.ascii	"_nextf\000"
.LASF95:
	.ascii	"_rand48\000"
.LASF261:
	.ascii	"HID_OUTPUT_TYPE\000"
.LASF234:
	.ascii	"SERVICE_CALLBACK_TYPE_WRITE_CHAR_VALUE\000"
.LASF80:
	.ascii	"_result_k\000"
.LASF266:
	.ascii	"NOTIFY_ENABLE\000"
.LASF10:
	.ascii	"long long unsigned int\000"
.LASF101:
	.ascii	"_asctime_buf\000"
.LASF51:
	.ascii	"__sFILE\000"
.LASF28:
	.ascii	"_wds\000"
.LASF198:
	.ascii	"TRACE_MODULE_NUM\000"
.LASF243:
	.ascii	"cccd_update_cb\000"
.LASF4:
	.ascii	"__uint16_t\000"
.LASF315:
	.ascii	"p_length\000"
.LASF91:
	.ascii	"__FILE\000"
.LASF258:
	.ascii	"bcd_hid\000"
.LASF157:
	.ascii	"TRACE_MODULE_OS\000"
.LASF288:
	.ascii	"msg_data\000"
.LASF235:
	.ascii	"T_SERVICE_CALLBACK_TYPE\000"
.LASF63:
	.ascii	"_offset\000"
.LASF321:
	.ascii	"server_send_data\000"
.LASF291:
	.ascii	"hid_protocol_mode\000"
.LASF262:
	.ascii	"HID_FEATURE_TYPE\000"
.LASF219:
	.ascii	"APP_RESULT_PROC_ALREADY_IN_PROGRESS\000"
.LASF229:
	.ascii	"GATT_PDU_TYPE_ANY\000"
.LASF74:
	.ascii	"_emergency\000"
.LASF299:
	.ascii	"format\000"
.LASF145:
	.ascii	"TYPE_BTLIB\000"
.LASF307:
	.ascii	"callback_data\000"
.LASF183:
	.ascii	"TRACE_MODULE_DFU\000"
.LASF213:
	.ascii	"APP_RESULT_INVALID_PDU\000"
.LASF172:
	.ascii	"TRACE_MODULE_TIMER\000"
.LASF314:
	.ascii	"offset\000"
.LASF31:
	.ascii	"__tm_sec\000"
.LASF150:
	.ascii	"SUBTYPE_DOWN_SNOOP\000"
.LASF277:
	.ascii	"write_parameter\000"
.LASF38:
	.ascii	"__tm_yday\000"
.LASF163:
	.ascii	"TRACE_MODULE_KEYSCAN\000"
.LASF73:
	.ascii	"_inc\000"
.LASF46:
	.ascii	"_ind\000"
.LASF223:
	.ascii	"T_SERVER_ID\000"
.LASF253:
	.ascii	"HID_BOOT_MS_IN_REPORT\000"
.LASF313:
	.ascii	"hids_attr_read_cb\000"
.LASF25:
	.ascii	"_next\000"
.LASF114:
	.ascii	"_mbsrtowcs_state\000"
.LASF326:
	.ascii	"hids_cccd_update_cb\000"
.LASF252:
	.ascii	"HID_BOOT_KB_OUT_REPORT\000"
.LASF200:
	.ascii	"type_value\000"
.LASF128:
	.ascii	"_tzname\000"
.LASF148:
	.ascii	"SUBTYPE_DOWN_MESSAGE\000"
.LASF180:
	.ascii	"TRACE_MODULE_CHARGER\000"
.LASF21:
	.ascii	"__value\000"
.LASF81:
	.ascii	"_p5s\000"
.LASF248:
	.ascii	"HID_REPORT_FEATURE\000"
.LASF317:
	.ascii	"param_type\000"
.LASF154:
	.ascii	"SUBTYPE_BINARY\000"
.LASF214:
	.ascii	"APP_RESULT_ATTR_NOT_FOUND\000"
.LASF116:
	.ascii	"_wcsrtombs_state\000"
.LASF106:
	.ascii	"_mblen_state\000"
.LASF201:
	.ascii	"value_len\000"
.LASF318:
	.ascii	"value_ptr\000"
.LASF186:
	.ascii	"TRACE_MODULE_PROTOCOL\000"
.LASF90:
	.ascii	"char\000"
.LASF34:
	.ascii	"__tm_mday\000"
.LASF87:
	.ascii	"_sig_func\000"
.LASF113:
	.ascii	"_mbrtowc_state\000"
.LASF86:
	.ascii	"_atexit0\000"
.LASF188:
	.ascii	"TRACE_MODULE_BTE\000"
.LASF168:
	.ascii	"TRACE_MODULE_GDMA\000"
.LASF166:
	.ascii	"TRACE_MODULE_3DG\000"
.LASF191:
	.ascii	"TRACE_MODULE_SMP\000"
.LASF130:
	.ascii	"TYPE_UPPERSTACK_FORMAT\000"
.LASF23:
	.ascii	"_flock_t\000"
.LASF256:
	.ascii	"T_HIDS_PARAM_TYPE\000"
.LASF282:
	.ascii	"read_value_index\000"
.LASF274:
	.ascii	"report_data\000"
.LASF278:
	.ascii	"T_HID_WRITE_MSG\000"
.LASF228:
	.ascii	"T_WRITE_TYPE\000"
.LASF17:
	.ascii	"__wch\000"
.LASF94:
	.ascii	"_iobs\000"
.LASF123:
	.ascii	"uint8_t\000"
.LASF272:
	.ascii	"protocol_mode\000"
.LASF59:
	.ascii	"_close\000"
.LASF77:
	.ascii	"__sdidinit\000"
.LASF146:
	.ascii	"SUBTYPE_DIRECT\000"
.LASF237:
	.ascii	"P_FUN_GATT_READ_ATTR_CB\000"
.LASF126:
	.ascii	"_timezone\000"
.LASF169:
	.ascii	"TRACE_MODULE_I2C\000"
.LASF70:
	.ascii	"_stdin\000"
.LASF103:
	.ascii	"_gamma_signgam\000"
.LASF216:
	.ascii	"APP_RESULT_INSUFFICIENT_RESOURCES\000"
.LASF9:
	.ascii	"long long int\000"
.LASF316:
	.ascii	"pp_value\000"
.LASF273:
	.ascii	"suspend_mode\000"
.LASF49:
	.ascii	"_base\000"
.LASF82:
	.ascii	"_freelist\000"
.LASF97:
	.ascii	"_mult\000"
.LASF24:
	.ascii	"__ULong\000"
.LASF153:
	.ascii	"SUBTYPE_STRING\000"
.LASF155:
	.ascii	"SUBTYPE_INDEX\000"
.LASF255:
	.ascii	"HID_CONTROL_POINT\000"
.LASF115:
	.ascii	"_wcrtomb_state\000"
.LASF208:
	.ascii	"APP_RESULT_REJECT\000"
.LASF270:
	.ascii	"report\000"
.LASF53:
	.ascii	"_file\000"
.LASF260:
	.ascii	"HID_INPUT_TYPE\000"
.LASF225:
	.ascii	"WRITE_WITHOUT_RESPONSE\000"
.LASF295:
	.ascii	"hids_attr_tbl\000"
.LASF140:
	.ascii	"TYPE_UPPERSTACK_RAMDATA5\000"
.LASF78:
	.ascii	"__cleanup\000"
.LASF136:
	.ascii	"TYPE_UPPERSTACK_RAMDATA1\000"
.LASF137:
	.ascii	"TYPE_UPPERSTACK_RAMDATA2\000"
.LASF138:
	.ascii	"TYPE_UPPERSTACK_RAMDATA3\000"
.LASF139:
	.ascii	"TYPE_UPPERSTACK_RAMDATA4\000"
.LASF22:
	.ascii	"_mbstate_t\000"
.LASF141:
	.ascii	"TYPE_UPPERSTACK_RAMDATA6\000"
.LASF142:
	.ascii	"TYPE_UPPERSTACK_RAMDATA7\000"
.LASF143:
	.ascii	"TYPE_UPPERSTACK_RAMDATA8\000"
.LASF39:
	.ascii	"__tm_isdst\000"
.LASF144:
	.ascii	"TYPE_PLATFORM_DBG_DIRECT\000"
.LASF311:
	.ascii	"p_write_ind_post_proc\000"
.LASF202:
	.ascii	"p_value_context\000"
.LASF117:
	.ascii	"_h_errno\000"
.LASF236:
	.ascii	"P_FUN_WRITE_IND_POST_PROC\000"
.LASF319:
	.ascii	"trace_log_buffer\000"
.LASF221:
	.ascii	"_Bool\000"
.LASF184:
	.ascii	"TRACE_MODULE_RFCOMM\000"
.LASF35:
	.ascii	"__tm_mon\000"
.LASF210:
	.ascii	"APP_RESULT_PREP_QUEUE_FULL\000"
.LASF12:
	.ascii	"long double\000"
.LASF189:
	.ascii	"TRACE_MODULE_BTIF\000"
.LASF124:
	.ascii	"uint16_t\000"
.LASF151:
	.ascii	"SUBTYPE_UP_SNOOP\000"
.LASF57:
	.ascii	"_write\000"
.LASF263:
	.ascii	"BOOT_PROTOCOL_MODE\000"
.LASF231:
	.ascii	"GATT_PDU_TYPE_INDICATION\000"
.LASF304:
	.ascii	"data_len\000"
.LASF206:
	.ascii	"APP_RESULT_PENDING\000"
.LASF293:
	.ascii	"external_report_refer\000"
.LASF45:
	.ascii	"_atexit\000"
.LASF66:
	.ascii	"_mbstate\000"
.LASF173:
	.ascii	"TRACE_MODULE_UART\000"
.LASF203:
	.ascii	"permissions\000"
.LASF280:
	.ascii	"value\000"
.LASF209:
	.ascii	"APP_RESULT_NOT_RELEASE\000"
.LASF2:
	.ascii	"short int\000"
.LASF286:
	.ascii	"conn_id\000"
.LASF217:
	.ascii	"APP_RESULT_APP_ERR\000"
.LASF6:
	.ascii	"long int\000"
.LASF194:
	.ascii	"TRACE_MODULE_HCI\000"
.LASF239:
	.ascii	"P_FUN_GATT_CCCD_UPDATE_CB\000"
.LASF309:
	.ascii	"length\000"
.LASF298:
	.ascii	"service_id\000"
.LASF312:
	.ascii	"hids_attr_write_cb\000"
.LASF147:
	.ascii	"SUBTYPE_FORMAT\000"
.LASF89:
	.ascii	"__sf\000"
.LASF27:
	.ascii	"_sign\000"
.LASF207:
	.ascii	"APP_RESULT_ACCEPT\000"
.LASF268:
	.ascii	"T_HID_NOTIFY\000"
.LASF190:
	.ascii	"TRACE_MODULE_GATT\000"
.LASF133:
	.ascii	"TYPE_UPPERSTACK_STRING\000"
.LASF327:
	.ascii	"hids_set_parameter\000"
.LASF64:
	.ascii	"_data\000"
.LASF18:
	.ascii	"__wchb\000"
.LASF122:
	.ascii	"_global_impure_ptr\000"
.LASF36:
	.ascii	"__tm_year\000"
.LASF158:
	.ascii	"TRACE_MODULE_OSIF\000"
.LASF215:
	.ascii	"APP_RESULT_ATTR_NOT_LONG\000"
.LASF230:
	.ascii	"GATT_PDU_TYPE_NOTIFICATION\000"
.LASF156:
	.ascii	"TRACE_MODULE_PATCH\000"
.LASF102:
	.ascii	"_localtime_buf\000"
.LASF120:
	.ascii	"_unused\000"
.LASF3:
	.ascii	"__uint8_t\000"
.LASF85:
	.ascii	"_new\000"
.LASF83:
	.ascii	"_cvtlen\000"
.LASF26:
	.ascii	"_maxwds\000"
.LASF109:
	.ascii	"_l64a_buf\000"
.LASF296:
	.ascii	"hids_attr_tbl_len\000"
.LASF320:
	.ascii	"server_add_service\000"
.LASF170:
	.ascii	"TRACE_MODULE_RTC\000"
.LASF287:
	.ascii	"msg_type\000"
.LASF265:
	.ascii	"T_HID_PROTOCOL_MODE\000"
.LASF62:
	.ascii	"_blksize\000"
.LASF182:
	.ascii	"TRACE_MODULE_APP\000"
.LASF30:
	.ascii	"__tm\000"
.LASF218:
	.ascii	"APP_RESULT_CCCD_IMPROPERLY_CONFIGURED\000"
.LASF241:
	.ascii	"read_attr_cb\000"
.LASF65:
	.ascii	"_lock\000"
.LASF19:
	.ascii	"sizetype\000"
.LASF242:
	.ascii	"write_attr_cb\000"
.LASF8:
	.ascii	"long unsigned int\000"
.LASF93:
	.ascii	"_niobs\000"
.LASF16:
	.ascii	"wint_t\000"
.LASF233:
	.ascii	"SERVICE_CALLBACK_TYPE_READ_CHAR_VALUE\000"
.LASF292:
	.ascii	"hid_suspand_mode\000"
.LASF42:
	.ascii	"_dso_handle\000"
.LASF204:
	.ascii	"T_ATTRIB_APPL\000"
.LASF297:
	.ascii	"hids_cbs\000"
.LASF84:
	.ascii	"_cvtbuf\000"
.LASF1:
	.ascii	"unsigned char\000"
.LASF7:
	.ascii	"__uint32_t\000"
.LASF205:
	.ascii	"APP_RESULT_SUCCESS\000"
.LASF111:
	.ascii	"_getdate_err\000"
.LASF135:
	.ascii	"TYPE_UPPERSTACK_BDADDR2\000"
.LASF227:
	.ascii	"WRITE_LONG\000"
.LASF98:
	.ascii	"_add\000"
.LASF224:
	.ascii	"WRITE_REQUEST\000"
.LASF308:
	.ascii	"attrib_index\000"
.LASF226:
	.ascii	"WRITE_SIGNED_WITHOUT_RESPONSE\000"
.LASF310:
	.ascii	"p_value\000"
.LASF48:
	.ascii	"__sbuf\000"
.LASF249:
	.ascii	"HID_REPORT_MAP\000"
.LASF165:
	.ascii	"TRACE_MODULE_IR\000"
.LASF92:
	.ascii	"_glue\000"
.LASF222:
	.ascii	"bond_storage_num\000"
.LASF178:
	.ascii	"TRACE_MODULE_USB\000"
.LASF88:
	.ascii	"__sglue\000"
.LASF100:
	.ascii	"_strtok_last\000"
.LASF107:
	.ascii	"_mbtowc_state\000"
.LASF196:
	.ascii	"TRACE_MODULE_UPPERSTACK\000"
.LASF76:
	.ascii	"_locale\000"
.LASF152:
	.ascii	"SUBTYPE_BDADDR\000"
.LASF171:
	.ascii	"TRACE_MODULE_SPI\000"
.LASF41:
	.ascii	"_fnargs\000"
.LASF0:
	.ascii	"signed char\000"
.LASF68:
	.ascii	"_reent\000"
.LASF5:
	.ascii	"short unsigned int\000"
.LASF328:
	.ascii	"memcpy\000"
.LASF175:
	.ascii	"TRACE_MODULE_GPIO\000"
.LASF301:
	.ascii	"hids_send_report\000"
.LASF43:
	.ascii	"_fntypes\000"
.LASF240:
	.ascii	"P_FUN_SERVER_GENERAL_CB\000"
.LASF245:
	.ascii	"HID_PROTOCOL_MODE\000"
.LASF305:
	.ascii	"ccc_bits\000"
.LASF50:
	.ascii	"_size\000"
.LASF14:
	.ascii	"_off_t\000"
.LASF300:
	.ascii	"hids_add_service\000"
.LASF61:
	.ascii	"_nbuf\000"
.LASF99:
	.ascii	"_unused_rand\000"
.LASF149:
	.ascii	"SUBTYPE_UP_MESSAGE\000"
.LASF285:
	.ascii	"T_HID_UPSTREAM_MSG_DATA\000"
.LASF75:
	.ascii	"_unspecified_locale_info\000"
.LASF67:
	.ascii	"_flags2\000"
.LASF246:
	.ascii	"HID_REPORT_INPUT\000"
.LASF44:
	.ascii	"_is_cxa\000"
.LASF167:
	.ascii	"TRACE_MODULE_ADC\000"
.LASF212:
	.ascii	"APP_RESULT_INVALID_VALUE_SIZE\000"
.LASF96:
	.ascii	"_seed\000"
.LASF104:
	.ascii	"_rand_next\000"
.LASF325:
	.ascii	"__locale_t\000"
.LASF247:
	.ascii	"HID_REPORT_OUTPUT\000"
.LASF58:
	.ascii	"_seek\000"
.LASF294:
	.ascii	"pfn_hids_cb\000"
.LASF72:
	.ascii	"_stderr\000"
.LASF119:
	.ascii	"_nmalloc\000"
.LASF60:
	.ascii	"_ubuf\000"
.LASF289:
	.ascii	"T_HID_CALLBACK_DATA\000"
	.ident	"GCC: (Realtek ASDK-6.5.0 Build 3215) 6.5.0"
