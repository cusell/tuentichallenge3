

;
; +-------------------------------------------------------------------------+
; |   This file	has been generated by The Interactive Disassembler (IDA)    |
; |	      Copyright	(c) 2011 Hex-Rays, <support@hex-rays.com>	    |
; |			 License info: B3-432E-F558-21			    |
; |				Ilfak Guilfanov				    |
; +-------------------------------------------------------------------------+
;
; Format      :	ELF for	Intel 386 (Executable)
; Imagebase   :	8048000
;

		.686p
		.mmx
		.model flat
.intel_syntax noprefix

; ===========================================================================

; Segment type:	Pure code
; Segment permissions: Read/Execute
_text		segment	dword public 'CODE' use32
		assume cs:_text
		;org 80480B8h
		assume es:nothing, ss:nothing, ds:_text, fs:nothing, gs:nothing

; =============== S U B	R O U T	I N E =======================================

; Attributes: noreturn bp-based	frame

		public start
start		proc near

var_1C		= dword	ptr -1Ch
var_18		= dword	ptr -18h
var_10		= dword	ptr -10h
arg_0		= byte ptr  8

		push	ebp
		mov	ebp, esp
		push	edi
		push	esi
		push	ebx
		sub	esp, 10h
		mov	eax, [ebp+4]
		lea	edi, [ebp+arg_0]
		mov	[ebp+var_10], eax
		xor	edx, edx	; addr
		mov	eax, 1Ah
		mov	ebx, edx	; ptrace_request
		mov	ecx, edx	; pid
		mov	esi, edx	; data
		int	80h		; LINUX	- sys_ptrace
		test	eax, eax
		jnz	short loc_804813C
		cmp	[ebp+var_10], 2
		jnz	short loc_804813C
		mov	edi, [edi+4]
		mov	[ebp+var_1C], edi
		mov	[ebp+var_18], 539h
		jmp	short loc_804812B
; ---------------------------------------------------------------------------

loc_80480F2:				; CODE XREF: start+78j
		imul	eax, [ebp+var_18], 41A7h
		mov	[ebp+var_10], eax
		mov	esi, 7FFFFFFh
		xor	edx, edx
		div	esi
		mov	[ebp+var_18], edx
		mov	esi, edi
		sub	esi, [ebp+var_1C]
		cmp	esi, 1Ch
		ja	short loc_8048127
		and	edx, 0FFh
		xor	ecx, edx
		movzx	eax, byte_8048148[esi]
		cmp	ecx, eax
		jnz	short loc_8048127
		jmp	short loc_804812A
; ---------------------------------------------------------------------------

loc_8048127:				; CODE XREF: start+58j	start+6Bj
		or	ebx, 0FFFFFFFFh

loc_804812A:				; CODE XREF: start+6Dj
		inc	edi

loc_804812B:				; CODE XREF: start+38j
		movsx	ecx, byte ptr [edi]
		test	cl, cl
		jnz	short loc_80480F2
		sub	edi, [ebp+var_1C]
		cmp	edi, 1Ch
		jbe	short loc_804813C
		jmp	short loc_804813F
; ---------------------------------------------------------------------------

loc_804813C:				; CODE XREF: start+23j	start+29j ...
		or	ebx, 0FFFFFFFFh	; status

loc_804813F:				; CODE XREF: start+82j
		mov	eax, 1
		int	80h		; LINUX	- sys_exit
start		endp

; ---------------------------------------------------------------------------

loc_8048146:				; CODE XREF: .text:loc_8048146j
		jmp	short loc_8048146
; ---------------------------------------------------------------------------
byte_8048148	db 78h			; DATA XREF: start+62r
		db 0A3h, 65h, 55h
		dd 0DA90F5EDh, 685CDA54h, 0D675E1C8h, 867EB742h, 6592170Ah
		dd 7847AE0Ch
		db 0F7h
_text		ends


		end start
