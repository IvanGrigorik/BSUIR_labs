	.file	"main.cpp"
	.text
	.section	.text._ZNKSt5ctypeIcE8do_widenEc,"axG",@progbits,_ZNKSt5ctypeIcE8do_widenEc,comdat
	.align 2
	.p2align 4
	.weak	_ZNKSt5ctypeIcE8do_widenEc
	.type	_ZNKSt5ctypeIcE8do_widenEc, @function
_ZNKSt5ctypeIcE8do_widenEc:
.LFB1347:
	.cfi_startproc
	movl	%esi, %eax
	ret
	.cfi_endproc
.LFE1347:
	.size	_ZNKSt5ctypeIcE8do_widenEc, .-_ZNKSt5ctypeIcE8do_widenEc
	.text
	.align 2
	.p2align 4
	.type	_ZNSt6vectorIdSaIdEEixEm.isra.0, @function
_ZNSt6vectorIdSaIdEEixEm.isra.0:
.LFB10387:
	.cfi_startproc
	leaq	(%rdi,%rsi,8), %rax
	ret
	.cfi_endproc
.LFE10387:
	.size	_ZNSt6vectorIdSaIdEEixEm.isra.0, .-_ZNSt6vectorIdSaIdEEixEm.isra.0
	.align 2
	.p2align 4
	.type	_ZNSt6vectorIS_IdSaIdEESaIS1_EEixEm.isra.0, @function
_ZNSt6vectorIS_IdSaIdEESaIS1_EEixEm.isra.0:
.LFB10388:
	.cfi_startproc
	leaq	(%rsi,%rsi,2), %rax
	leaq	(%rdi,%rax,8), %rax
	ret
	.cfi_endproc
.LFE10388:
	.size	_ZNSt6vectorIS_IdSaIdEESaIS1_EEixEm.isra.0, .-_ZNSt6vectorIS_IdSaIdEESaIS1_EEixEm.isra.0
	.p2align 4
	.type	_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_.isra.0, @function
_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_.isra.0:
.LFB10389:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	pushq	%rbx
	.cfi_def_cfa_offset 24
	.cfi_offset 3, -24
	subq	$8, %rsp
	.cfi_def_cfa_offset 32
	movq	(%rdi), %rax
	movq	-24(%rax), %rax
	movq	240(%rdi,%rax), %rbp
	testq	%rbp, %rbp
	je	.L12
	cmpb	$0, 56(%rbp)
	movq	%rdi, %rbx
	je	.L7
	movsbl	67(%rbp), %esi
.L8:
	movq	%rbx, %rdi
	call	_ZNSo3putEc
	addq	$8, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 24
	popq	%rbx
	.cfi_def_cfa_offset 16
	movq	%rax, %rdi
	popq	%rbp
	.cfi_def_cfa_offset 8
	jmp	_ZNSo5flushEv
.L7:
	.cfi_restore_state
	movq	%rbp, %rdi
	call	_ZNKSt5ctypeIcE13_M_widen_initEv
	movq	0(%rbp), %rax
	movl	$10, %esi
	movq	48(%rax), %rax
	cmpq	$_ZNKSt5ctypeIcE8do_widenEc, %rax
	je	.L8
	movl	$10, %esi
	movq	%rbp, %rdi
	call	*%rax
	movsbl	%al, %esi
	jmp	.L8
.L12:
	call	_ZSt16__throw_bad_castv
	.cfi_endproc
.LFE10389:
	.size	_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_.isra.0, .-_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_.isra.0
	.p2align 4
	.globl	_Z18sum_small_matricesRSt6vectorIS_IdSaIdEESaIS1_EERKS3_
	.type	_Z18sum_small_matricesRSt6vectorIS_IdSaIdEESaIS1_EERKS3_, @function
_Z18sum_small_matricesRSt6vectorIS_IdSaIdEESaIS1_EERKS3_:
.LFB9519:
	.cfi_startproc
	movq	(%rdi), %rdi
	movq	(%rsi), %r8
	xorl	%esi, %esi
	.p2align 4,,10
	.p2align 3
.L14:
	movq	(%r8,%rsi), %rcx
	movq	(%rdi,%rsi), %rdx
	xorl	%eax, %eax
	.p2align 4,,10
	.p2align 3
.L15:
	vmovsd	(%rdx,%rax), %xmm0
	vaddsd	(%rcx,%rax), %xmm0, %xmm0
	vmovsd	%xmm0, (%rdx,%rax)
	addq	$8, %rax
	cmpq	$80, %rax
	jne	.L15
	addq	$24, %rsi
	cmpq	$240, %rsi
	jne	.L14
	ret
	.cfi_endproc
.LFE9519:
	.size	_Z18sum_small_matricesRSt6vectorIS_IdSaIdEESaIS1_EERKS3_, .-_Z18sum_small_matricesRSt6vectorIS_IdSaIdEESaIS1_EERKS3_
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC2:
	.string	"Matrix not equal!"
.LC3:
	.string	" Index:"
.LC4:
	.string	"Matrix equal"
	.text
	.p2align 4
	.globl	_Z7compareRSt6vectorIS_IS_IS_IdSaIdEESaIS1_EESaIS3_EESaIS5_EES8_
	.type	_Z7compareRSt6vectorIS_IS_IS_IdSaIdEESaIS1_EESaIS3_EESaIS5_EES8_, @function
_Z7compareRSt6vectorIS_IS_IS_IdSaIdEESaIS1_EESaIS3_EESaIS5_EES8_:
.LFB9544:
	.cfi_startproc
	pushq	%r15
	.cfi_def_cfa_offset 16
	.cfi_offset 15, -16
	xorl	%eax, %eax
	pushq	%r14
	.cfi_def_cfa_offset 24
	.cfi_offset 14, -24
	pushq	%r13
	.cfi_def_cfa_offset 32
	.cfi_offset 13, -32
	pushq	%r12
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	xorl	%r12d, %r12d
	pushq	%rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	pushq	%rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	subq	$40, %rsp
	.cfi_def_cfa_offset 96
	movq	(%rdi), %rdi
	movq	(%rsi), %rsi
	vmovq	.LC0(%rip), %xmm4
	vmovsd	.LC1(%rip), %xmm3
.L20:
	movq	(%rdi,%rax), %r14
	movq	(%rsi,%rax), %r11
	xorl	%ecx, %ecx
	xorl	%ebp, %ebp
.L34:
	movq	(%r14,%rcx), %r15
	movq	(%r11,%rcx), %r10
	xorl	%r9d, %r9d
	xorl	%r13d, %r13d
.L32:
	movq	(%r15,%r9), %r8
	movq	(%r10,%r9), %rdx
	xorl	%ebx, %ebx
	.p2align 4,,10
	.p2align 3
.L29:
	vmovsd	(%r8,%rbx,8), %xmm2
	vmovsd	(%rdx,%rbx,8), %xmm1
	vsubsd	%xmm1, %xmm2, %xmm0
	vandpd	%xmm4, %xmm0, %xmm0
	vcomisd	%xmm3, %xmm0
	ja	.L50
	addq	$1, %rbx
	cmpq	$10, %rbx
	jne	.L29
	addl	$1, %r13d
	addq	$24, %r9
	cmpl	$10, %r13d
	jne	.L32
	addl	$1, %ebp
	addq	$24, %rcx
	cmpl	$100, %ebp
	jne	.L34
	addl	$1, %r12d
	addq	$24, %rax
	cmpl	$100, %r12d
	jne	.L20
	movl	$12, %edx
	movl	$.LC4, %esi
	movl	$_ZSt4cout, %edi
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l
	movq	_ZSt4cout(%rip), %rax
	movq	-24(%rax), %rax
	movq	_ZSt4cout+240(%rax), %rbx
	testq	%rbx, %rbx
	je	.L35
	cmpb	$0, 56(%rbx)
	je	.L36
	movsbl	67(%rbx), %r13d
.L37:
	movl	%r13d, %esi
	movl	$_ZSt4cout, %edi
	call	_ZNSo3putEc
	movq	%rax, %rdi
	call	_ZNSo5flushEv
	movl	$1, %eax
	jmp	.L19
	.p2align 4,,10
	.p2align 3
.L50:
	movl	$17, %edx
	movl	$.LC2, %esi
	movl	$_ZSt4cout, %edi
	vmovsd	%xmm1, 8(%rsp)
	vmovsd	%xmm2, (%rsp)
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l
	vmovsd	(%rsp), %xmm2
	movl	$_ZSt4cout, %edi
	vmovsd	%xmm2, %xmm2, %xmm0
	call	_ZNSo9_M_insertIdEERSoT_
	vmovsd	8(%rsp), %xmm1
	movb	$45, 31(%rsp)
	movq	%rax, %r14
	movq	(%rax), %rax
	vmovsd	%xmm1, (%rsp)
	movq	-24(%rax), %rax
	cmpq	$0, 16(%r14,%rax)
	jne	.L51
	movl	$45, %esi
	movq	%r14, %rdi
	call	_ZNSo3putEc
	vmovsd	(%rsp), %xmm1
.L24:
	vmovsd	%xmm1, %xmm1, %xmm0
	movq	%r14, %rdi
	call	_ZNSo9_M_insertIdEERSoT_
	movl	$7, %edx
	movl	$.LC3, %esi
	movq	%rax, %r14
	movq	%rax, %rdi
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l
	movl	%r12d, %esi
	movq	%r14, %rdi
	call	_ZNSolsEi
	movl	%ebp, %esi
	movq	%rax, %rdi
	call	_ZNSolsEi
	movl	%r13d, %esi
	movq	%rax, %rdi
	call	_ZNSolsEi
	movl	%ebx, %esi
	movq	%rax, %rdi
	call	_ZNSolsEi
	movq	%rax, %rbx
	movq	(%rax), %rax
	movq	-24(%rax), %rax
	movq	240(%rbx,%rax), %rbp
	testq	%rbp, %rbp
	je	.L35
	cmpb	$0, 56(%rbp)
	je	.L26
	movsbl	67(%rbp), %esi
.L27:
	movq	%rbx, %rdi
	call	_ZNSo3putEc
	movq	%rax, %rdi
	call	_ZNSo5flushEv
	xorl	%eax, %eax
.L19:
	addq	$40, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 56
	popq	%rbx
	.cfi_def_cfa_offset 48
	popq	%rbp
	.cfi_def_cfa_offset 40
	popq	%r12
	.cfi_def_cfa_offset 32
	popq	%r13
	.cfi_def_cfa_offset 24
	popq	%r14
	.cfi_def_cfa_offset 16
	popq	%r15
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L51:
	.cfi_restore_state
	movq	%r14, %rdi
	movl	$1, %edx
	leaq	31(%rsp), %rsi
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l
	vmovsd	(%rsp), %xmm1
	movq	%rax, %r14
	jmp	.L24
	.p2align 4,,10
	.p2align 3
.L26:
	movq	%rbp, %rdi
	call	_ZNKSt5ctypeIcE13_M_widen_initEv
	movq	0(%rbp), %rax
	movl	$10, %esi
	movq	48(%rax), %rax
	cmpq	$_ZNKSt5ctypeIcE8do_widenEc, %rax
	je	.L27
	movq	%rbp, %rdi
	call	*%rax
	movsbl	%al, %esi
	jmp	.L27
.L36:
	movq	%rbx, %rdi
	call	_ZNKSt5ctypeIcE13_M_widen_initEv
	movq	(%rbx), %rax
	movq	48(%rax), %rax
	cmpq	$_ZNKSt5ctypeIcE8do_widenEc, %rax
	je	.L37
	movl	$10, %esi
	movq	%rbx, %rdi
	call	*%rax
	movsbl	%al, %r13d
	jmp	.L37
.L35:
	call	_ZSt16__throw_bad_castv
	.cfi_endproc
.LFE9544:
	.size	_Z7compareRSt6vectorIS_IS_IS_IdSaIdEESaIS1_EESaIS3_EESaIS5_EES8_, .-_Z7compareRSt6vectorIS_IS_IS_IdSaIdEESaIS1_EESaIS3_EESaIS5_EES8_
	.section	.rodata._ZNSt6vectorIdSaIdEEC2EmRKS0_.str1.8,"aMS",@progbits,1
	.align 8
.LC5:
	.string	"cannot create std::vector larger than max_size()"
	.section	.text._ZNSt6vectorIdSaIdEEC2EmRKS0_,"axG",@progbits,_ZNSt6vectorIdSaIdEEC5EmRKS0_,comdat
	.align 2
	.p2align 4
	.weak	_ZNSt6vectorIdSaIdEEC2EmRKS0_
	.type	_ZNSt6vectorIdSaIdEEC2EmRKS0_, @function
_ZNSt6vectorIdSaIdEEC2EmRKS0_:
.LFB9806:
	.cfi_startproc
	pushq	%r13
	.cfi_def_cfa_offset 16
	.cfi_offset 13, -16
	movq	%rsi, %rax
	pushq	%r12
	.cfi_def_cfa_offset 24
	.cfi_offset 12, -24
	pushq	%rbp
	.cfi_def_cfa_offset 32
	.cfi_offset 6, -32
	pushq	%rbx
	.cfi_def_cfa_offset 40
	.cfi_offset 3, -40
	subq	$8, %rsp
	.cfi_def_cfa_offset 48
	shrq	$60, %rax
	jne	.L58
	vpxor	%xmm0, %xmm0, %xmm0
	movq	$0, 16(%rdi)
	movq	%rdi, %rbx
	movq	%rsi, %rbp
	vmovdqu	%xmm0, (%rdi)
	testq	%rsi, %rsi
	je	.L59
	leaq	0(,%rsi,8), %r13
	movq	%r13, %rdi
	call	_Znwm
	vmovq	%rax, %xmm1
	leaq	(%rax,%r13), %r12
	movq	$0x000000000, (%rax)
	leaq	8(%rax), %rdi
	vpunpcklqdq	%xmm1, %xmm1, %xmm0
	movq	%r12, 16(%rbx)
	vmovdqu	%xmm0, (%rbx)
	cmpq	$1, %rbp
	je	.L56
	cmpq	%rdi, %r12
	je	.L55
	leaq	-8(%r13), %rdx
	xorl	%esi, %esi
	call	memset
.L55:
	movq	%r12, 8(%rbx)
	addq	$8, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 40
	popq	%rbx
	.cfi_def_cfa_offset 32
	popq	%rbp
	.cfi_def_cfa_offset 24
	popq	%r12
	.cfi_def_cfa_offset 16
	popq	%r13
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L59:
	.cfi_restore_state
	xorl	%r12d, %r12d
	movq	$0, (%rdi)
	movq	$0, 16(%rdi)
	movq	%r12, 8(%rbx)
	addq	$8, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 40
	popq	%rbx
	.cfi_def_cfa_offset 32
	popq	%rbp
	.cfi_def_cfa_offset 24
	popq	%r12
	.cfi_def_cfa_offset 16
	popq	%r13
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L56:
	.cfi_restore_state
	movq	%rdi, %r12
	movq	%r12, 8(%rbx)
	addq	$8, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 40
	popq	%rbx
	.cfi_def_cfa_offset 32
	popq	%rbp
	.cfi_def_cfa_offset 24
	popq	%r12
	.cfi_def_cfa_offset 16
	popq	%r13
	.cfi_def_cfa_offset 8
	ret
.L58:
	.cfi_restore_state
	movl	$.LC5, %edi
	call	_ZSt20__throw_length_errorPKc
	.cfi_endproc
.LFE9806:
	.size	_ZNSt6vectorIdSaIdEEC2EmRKS0_, .-_ZNSt6vectorIdSaIdEEC2EmRKS0_
	.weak	_ZNSt6vectorIdSaIdEEC1EmRKS0_
	.set	_ZNSt6vectorIdSaIdEEC1EmRKS0_,_ZNSt6vectorIdSaIdEEC2EmRKS0_
	.section	.text._ZNSt6vectorIdSaIdEED2Ev,"axG",@progbits,_ZNSt6vectorIdSaIdEED5Ev,comdat
	.align 2
	.p2align 4
	.weak	_ZNSt6vectorIdSaIdEED2Ev
	.type	_ZNSt6vectorIdSaIdEED2Ev, @function
_ZNSt6vectorIdSaIdEED2Ev:
.LFB9809:
	.cfi_startproc
	movq	(%rdi), %rdi
	testq	%rdi, %rdi
	je	.L62
	jmp	_ZdlPv
	.p2align 4,,10
	.p2align 3
.L62:
	ret
	.cfi_endproc
.LFE9809:
	.size	_ZNSt6vectorIdSaIdEED2Ev, .-_ZNSt6vectorIdSaIdEED2Ev
	.weak	_ZNSt6vectorIdSaIdEED1Ev
	.set	_ZNSt6vectorIdSaIdEED1Ev,_ZNSt6vectorIdSaIdEED2Ev
	.section	.text._ZNSt6vectorIS_IdSaIdEESaIS1_EED2Ev,"axG",@progbits,_ZNSt6vectorIS_IdSaIdEESaIS1_EED5Ev,comdat
	.align 2
	.p2align 4
	.weak	_ZNSt6vectorIS_IdSaIdEESaIS1_EED2Ev
	.type	_ZNSt6vectorIS_IdSaIdEESaIS1_EED2Ev, @function
_ZNSt6vectorIS_IdSaIdEESaIS1_EED2Ev:
.LFB9821:
	.cfi_startproc
	pushq	%r12
	.cfi_def_cfa_offset 16
	.cfi_offset 12, -16
	pushq	%rbp
	.cfi_def_cfa_offset 24
	.cfi_offset 6, -24
	pushq	%rbx
	.cfi_def_cfa_offset 32
	.cfi_offset 3, -32
	movq	8(%rdi), %rbp
	movq	(%rdi), %rbx
	cmpq	%rbx, %rbp
	je	.L64
	movq	%rdi, %r12
	.p2align 4,,10
	.p2align 3
.L66:
	movq	(%rbx), %rdi
	testq	%rdi, %rdi
	je	.L65
	call	_ZdlPv
.L65:
	addq	$24, %rbx
	cmpq	%rbx, %rbp
	jne	.L66
	movq	(%r12), %rbx
.L64:
	testq	%rbx, %rbx
	je	.L72
	movq	%rbx, %rdi
	popq	%rbx
	.cfi_remember_state
	.cfi_def_cfa_offset 24
	popq	%rbp
	.cfi_def_cfa_offset 16
	popq	%r12
	.cfi_def_cfa_offset 8
	jmp	_ZdlPv
	.p2align 4,,10
	.p2align 3
.L72:
	.cfi_restore_state
	popq	%rbx
	.cfi_def_cfa_offset 24
	popq	%rbp
	.cfi_def_cfa_offset 16
	popq	%r12
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE9821:
	.size	_ZNSt6vectorIS_IdSaIdEESaIS1_EED2Ev, .-_ZNSt6vectorIS_IdSaIdEESaIS1_EED2Ev
	.weak	_ZNSt6vectorIS_IdSaIdEESaIS1_EED1Ev
	.set	_ZNSt6vectorIS_IdSaIdEESaIS1_EED1Ev,_ZNSt6vectorIS_IdSaIdEESaIS1_EED2Ev
	.section	.text._ZNSt6vectorIS_IS_IdSaIdEESaIS1_EESaIS3_EED2Ev,"axG",@progbits,_ZNSt6vectorIS_IS_IdSaIdEESaIS1_EESaIS3_EED5Ev,comdat
	.align 2
	.p2align 4
	.weak	_ZNSt6vectorIS_IS_IdSaIdEESaIS1_EESaIS3_EED2Ev
	.type	_ZNSt6vectorIS_IS_IdSaIdEESaIS1_EESaIS3_EED2Ev, @function
_ZNSt6vectorIS_IS_IdSaIdEESaIS1_EESaIS3_EED2Ev:
.LFB9839:
	.cfi_startproc
	pushq	%r14
	.cfi_def_cfa_offset 16
	.cfi_offset 14, -16
	pushq	%r13
	.cfi_def_cfa_offset 24
	.cfi_offset 13, -24
	pushq	%r12
	.cfi_def_cfa_offset 32
	.cfi_offset 12, -32
	pushq	%rbp
	.cfi_def_cfa_offset 40
	.cfi_offset 6, -40
	pushq	%rbx
	.cfi_def_cfa_offset 48
	.cfi_offset 3, -48
	movq	8(%rdi), %r13
	movq	(%rdi), %r12
	cmpq	%r12, %r13
	je	.L75
	movq	%rdi, %r14
	.p2align 4,,10
	.p2align 3
.L80:
	movq	8(%r12), %rbp
	movq	(%r12), %rbx
	cmpq	%rbx, %rbp
	je	.L76
	.p2align 4,,10
	.p2align 3
.L78:
	movq	(%rbx), %rdi
	testq	%rdi, %rdi
	je	.L77
	call	_ZdlPv
.L77:
	addq	$24, %rbx
	cmpq	%rbx, %rbp
	jne	.L78
	movq	(%r12), %rbx
.L76:
	testq	%rbx, %rbx
	je	.L79
	movq	%rbx, %rdi
	call	_ZdlPv
.L79:
	addq	$24, %r12
	cmpq	%r12, %r13
	jne	.L80
	movq	(%r14), %r12
.L75:
	testq	%r12, %r12
	je	.L90
	popq	%rbx
	.cfi_remember_state
	.cfi_def_cfa_offset 40
	movq	%r12, %rdi
	popq	%rbp
	.cfi_def_cfa_offset 32
	popq	%r12
	.cfi_def_cfa_offset 24
	popq	%r13
	.cfi_def_cfa_offset 16
	popq	%r14
	.cfi_def_cfa_offset 8
	jmp	_ZdlPv
.L90:
	.cfi_restore_state
	popq	%rbx
	.cfi_def_cfa_offset 40
	popq	%rbp
	.cfi_def_cfa_offset 32
	popq	%r12
	.cfi_def_cfa_offset 24
	popq	%r13
	.cfi_def_cfa_offset 16
	popq	%r14
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE9839:
	.size	_ZNSt6vectorIS_IS_IdSaIdEESaIS1_EESaIS3_EED2Ev, .-_ZNSt6vectorIS_IS_IdSaIdEESaIS1_EESaIS3_EED2Ev
	.weak	_ZNSt6vectorIS_IS_IdSaIdEESaIS1_EESaIS3_EED1Ev
	.set	_ZNSt6vectorIS_IS_IdSaIdEESaIS1_EESaIS3_EED1Ev,_ZNSt6vectorIS_IS_IdSaIdEESaIS1_EESaIS3_EED2Ev
	.section	.text._ZNSt6vectorIS_IS_IS_IdSaIdEESaIS1_EESaIS3_EESaIS5_EED2Ev,"axG",@progbits,_ZNSt6vectorIS_IS_IS_IdSaIdEESaIS1_EESaIS3_EESaIS5_EED5Ev,comdat
	.align 2
	.p2align 4
	.weak	_ZNSt6vectorIS_IS_IS_IdSaIdEESaIS1_EESaIS3_EESaIS5_EED2Ev
	.type	_ZNSt6vectorIS_IS_IS_IdSaIdEESaIS1_EESaIS3_EESaIS5_EED2Ev, @function
_ZNSt6vectorIS_IS_IS_IdSaIdEESaIS1_EESaIS3_EESaIS5_EED2Ev:
.LFB9851:
	.cfi_startproc
	pushq	%r15
	.cfi_def_cfa_offset 16
	.cfi_offset 15, -16
	pushq	%r14
	.cfi_def_cfa_offset 24
	.cfi_offset 14, -24
	pushq	%r13
	.cfi_def_cfa_offset 32
	.cfi_offset 13, -32
	pushq	%r12
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	pushq	%rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	pushq	%rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	subq	$24, %rsp
	.cfi_def_cfa_offset 80
	movq	8(%rdi), %r14
	movq	(%rdi), %r13
	movq	%rdi, 8(%rsp)
	cmpq	%r13, %r14
	je	.L93
	.p2align 4,,10
	.p2align 3
.L101:
	movq	8(%r13), %r12
	movq	0(%r13), %rbp
	cmpq	%rbp, %r12
	je	.L94
	.p2align 4,,10
	.p2align 3
.L99:
	movq	8(%rbp), %rbx
	movq	0(%rbp), %r15
	cmpq	%r15, %rbx
	je	.L95
	.p2align 4,,10
	.p2align 3
.L97:
	movq	(%r15), %rdi
	testq	%rdi, %rdi
	je	.L96
	call	_ZdlPv
.L96:
	addq	$24, %r15
	cmpq	%r15, %rbx
	jne	.L97
	movq	0(%rbp), %r15
.L95:
	testq	%r15, %r15
	je	.L98
	movq	%r15, %rdi
	call	_ZdlPv
.L98:
	addq	$24, %rbp
	cmpq	%rbp, %r12
	jne	.L99
	movq	0(%r13), %rbp
.L94:
	testq	%rbp, %rbp
	je	.L100
	movq	%rbp, %rdi
	call	_ZdlPv
.L100:
	addq	$24, %r13
	cmpq	%r13, %r14
	jne	.L101
	movq	8(%rsp), %rax
	movq	(%rax), %r13
.L93:
	testq	%r13, %r13
	je	.L115
	addq	$24, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 56
	movq	%r13, %rdi
	popq	%rbx
	.cfi_def_cfa_offset 48
	popq	%rbp
	.cfi_def_cfa_offset 40
	popq	%r12
	.cfi_def_cfa_offset 32
	popq	%r13
	.cfi_def_cfa_offset 24
	popq	%r14
	.cfi_def_cfa_offset 16
	popq	%r15
	.cfi_def_cfa_offset 8
	jmp	_ZdlPv
.L115:
	.cfi_restore_state
	addq	$24, %rsp
	.cfi_def_cfa_offset 56
	popq	%rbx
	.cfi_def_cfa_offset 48
	popq	%rbp
	.cfi_def_cfa_offset 40
	popq	%r12
	.cfi_def_cfa_offset 32
	popq	%r13
	.cfi_def_cfa_offset 24
	popq	%r14
	.cfi_def_cfa_offset 16
	popq	%r15
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE9851:
	.size	_ZNSt6vectorIS_IS_IS_IdSaIdEESaIS1_EESaIS3_EESaIS5_EED2Ev, .-_ZNSt6vectorIS_IS_IS_IdSaIdEESaIS1_EESaIS3_EESaIS5_EED2Ev
	.weak	_ZNSt6vectorIS_IS_IS_IdSaIdEESaIS1_EESaIS3_EESaIS5_EED1Ev
	.set	_ZNSt6vectorIS_IS_IS_IdSaIdEESaIS1_EESaIS3_EESaIS5_EED1Ev,_ZNSt6vectorIS_IS_IS_IdSaIdEESaIS1_EESaIS3_EESaIS5_EED2Ev
	.section	.text._ZNSt12_Destroy_auxILb0EE9__destroyIPSt6vectorIdSaIdEEEEvT_S6_,"axG",@progbits,_ZNSt12_Destroy_auxILb0EE9__destroyIPSt6vectorIdSaIdEEEEvT_S6_,comdat
	.p2align 4
	.weak	_ZNSt12_Destroy_auxILb0EE9__destroyIPSt6vectorIdSaIdEEEEvT_S6_
	.type	_ZNSt12_Destroy_auxILb0EE9__destroyIPSt6vectorIdSaIdEEEEvT_S6_, @function
_ZNSt12_Destroy_auxILb0EE9__destroyIPSt6vectorIdSaIdEEEEvT_S6_:
.LFB10226:
	.cfi_startproc
	cmpq	%rsi, %rdi
	je	.L127
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsi, %rbp
	pushq	%rbx
	.cfi_def_cfa_offset 24
	.cfi_offset 3, -24
	movq	%rdi, %rbx
	subq	$8, %rsp
	.cfi_def_cfa_offset 32
	.p2align 4,,10
	.p2align 3
.L120:
	movq	(%rbx), %rdi
	testq	%rdi, %rdi
	je	.L119
	call	_ZdlPv
.L119:
	addq	$24, %rbx
	cmpq	%rbx, %rbp
	jne	.L120
	addq	$8, %rsp
	.cfi_def_cfa_offset 24
	popq	%rbx
	.cfi_def_cfa_offset 16
	popq	%rbp
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L127:
	.cfi_restore 3
	.cfi_restore 6
	ret
	.cfi_endproc
.LFE10226:
	.size	_ZNSt12_Destroy_auxILb0EE9__destroyIPSt6vectorIdSaIdEEEEvT_S6_, .-_ZNSt12_Destroy_auxILb0EE9__destroyIPSt6vectorIdSaIdEEEEvT_S6_
	.section	.text._ZNSt23mersenne_twister_engineImLm32ELm624ELm397ELm31ELm2567483615ELm11ELm4294967295ELm7ELm2636928640ELm15ELm4022730752ELm18ELm1812433253EE11_M_gen_randEv,"axG",@progbits,_ZNSt23mersenne_twister_engineImLm32ELm624ELm397ELm31ELm2567483615ELm11ELm4294967295ELm7ELm2636928640ELm15ELm4022730752ELm18ELm1812433253EE11_M_gen_randEv,comdat
	.align 2
	.p2align 4
	.weak	_ZNSt23mersenne_twister_engineImLm32ELm624ELm397ELm31ELm2567483615ELm11ELm4294967295ELm7ELm2636928640ELm15ELm4022730752ELm18ELm1812433253EE11_M_gen_randEv
	.type	_ZNSt23mersenne_twister_engineImLm32ELm624ELm397ELm31ELm2567483615ELm11ELm4294967295ELm7ELm2636928640ELm15ELm4022730752ELm18ELm1812433253EE11_M_gen_randEv, @function
_ZNSt23mersenne_twister_engineImLm32ELm624ELm397ELm31ELm2567483615ELm11ELm4294967295ELm7ELm2636928640ELm15ELm4022730752ELm18ELm1812433253EE11_M_gen_randEv:
.LFB10284:
	.cfi_startproc
	movq	%rdi, %r9
	movq	(%rdi), %rsi
	movl	$2567483615, %r8d
	leaq	1816(%rdi), %rdi
	movq	%r9, %rax
	.p2align 4,,10
	.p2align 3
.L132:
	andq	$-2147483648, %rsi
	movq	%rsi, %rdx
	movq	8(%rax), %rsi
	movq	%rsi, %rcx
	andl	$2147483647, %ecx
	orq	%rdx, %rcx
	movq	%rcx, %rdx
	shrq	%rdx
	xorq	3176(%rax), %rdx
	andl	$1, %ecx
	je	.L131
	xorq	%r8, %rdx
.L131:
	movq	%rdx, (%rax)
	addq	$8, %rax
	cmpq	%rdi, %rax
	jne	.L132
	movq	$-2147483648, %rdi
	movl	$2567483615, %ecx
	leaq	4984(%r9), %rdx
	vmovq	%rdi, %xmm5
	movl	$2147483647, %edi
	vmovq	%rcx, %xmm6
	vmovq	%rdi, %xmm4
	movl	$1, %edi
	vpunpcklqdq	%xmm5, %xmm5, %xmm5
	vmovq	%rdi, %xmm3
	vpunpcklqdq	%xmm4, %xmm4, %xmm4
	vpxor	%xmm7, %xmm7, %xmm7
	vpunpcklqdq	%xmm3, %xmm3, %xmm3
	vpunpcklqdq	%xmm6, %xmm6, %xmm6
	.p2align 4,,10
	.p2align 3
.L133:
	vpand	8(%rax), %xmm4, %xmm1
	vpand	(%rax), %xmm5, %xmm0
	addq	$16, %rax
	vpor	%xmm1, %xmm0, %xmm0
	vpsrlq	$1, %xmm0, %xmm1
	vpand	%xmm3, %xmm0, %xmm0
	vpxor	-1832(%rax), %xmm1, %xmm1
	vpcmpeqq	%xmm7, %xmm0, %xmm0
	vpxor	%xmm6, %xmm1, %xmm2
	vpblendvb	%xmm0, %xmm1, %xmm2, %xmm0
	vmovdqu	%xmm0, -16(%rax)
	cmpq	%rax, %rdx
	jne	.L133
	movq	4984(%r9), %rdx
	movq	(%r9), %rax
	movq	$0, 4992(%r9)
	andl	$2147483647, %eax
	andq	$-2147483648, %rdx
	orq	%rax, %rdx
	movq	%rdx, %rax
	shrq	%rax
	xorq	3168(%r9), %rax
	xorq	%rax, %rcx
	andl	$1, %edx
	cmovne	%rcx, %rax
	movq	%rax, 4984(%r9)
	ret
	.cfi_endproc
.LFE10284:
	.size	_ZNSt23mersenne_twister_engineImLm32ELm624ELm397ELm31ELm2567483615ELm11ELm4294967295ELm7ELm2636928640ELm15ELm4022730752ELm18ELm1812433253EE11_M_gen_randEv, .-_ZNSt23mersenne_twister_engineImLm32ELm624ELm397ELm31ELm2567483615ELm11ELm4294967295ELm7ELm2636928640ELm15ELm4022730752ELm18ELm1812433253EE11_M_gen_randEv
	.section	.text.unlikely,"ax",@progbits
.LCOLDB16:
	.text
.LHOTB16:
	.p2align 4
	.globl	_Z20randomize_one_matrixRSt6vectorIS_IS_IS_IdSaIdEESaIS1_EESaIS3_EESaIS5_EE
	.type	_Z20randomize_one_matrixRSt6vectorIS_IS_IS_IdSaIdEESaIS1_EESaIS3_EESaIS5_EE, @function
_Z20randomize_one_matrixRSt6vectorIS_IS_IS_IdSaIdEESaIS1_EESaIS3_EESaIS5_EE:
.LFB9518:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	.cfi_lsda 0x3,.LLSDA9518
	pushq	%r15
	.cfi_def_cfa_offset 16
	.cfi_offset 15, -16
	pushq	%r14
	.cfi_def_cfa_offset 24
	.cfi_offset 14, -24
	pushq	%r13
	.cfi_def_cfa_offset 32
	.cfi_offset 13, -32
	pushq	%r12
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	pushq	%rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	pushq	%rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	movq	%rdi, %rbx
	subq	$10072, %rsp
	.cfi_def_cfa_offset 10128
	leaq	5072(%rsp), %rbp
	leaq	48(%rsp), %rdi
	movl	$1634100580, 5072(%rsp)
	leaq	5056(%rsp), %rsi
	movq	%rbp, 5056(%rsp)
	movl	$1953264993, 5075(%rsp)
	movq	$7, 5064(%rsp)
	movb	$0, 5079(%rsp)
.LEHB0:
	call	_ZNSt13random_device7_M_initERKNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE
.LEHE0:
	movq	5056(%rsp), %rdi
	cmpq	%rbp, %rdi
	je	.L143
	call	_ZdlPv
.L143:
	leaq	48(%rsp), %rdi
.LEHB1:
	call	_ZNSt13random_device9_M_getvalEv
.LEHE1:
	movl	%eax, %ecx
	movl	$1, %edx
	movq	%rcx, 5056(%rsp)
.L147:
	movq	%rcx, %rax
	shrq	$30, %rax
	xorq	%rcx, %rax
	imulq	$1812433253, %rax, %rax
	leal	(%rax,%rdx), %ecx
	movq	%rcx, 5056(%rsp,%rdx,8)
	addq	$1, %rdx
	cmpq	$624, %rdx
	jne	.L147
	movq	8(%rbx), %rax
	movq	(%rbx), %rcx
	vxorps	%xmm3, %xmm3, %xmm3
	movq	$624, 10048(%rsp)
	movq	%rax, 40(%rsp)
	movq	%rcx, 32(%rsp)
	cmpq	%rcx, %rax
	je	.L151
.L150:
	movq	32(%rsp), %rax
	movq	8(%rax), %rcx
	movq	(%rax), %r13
	movq	%rcx, 24(%rsp)
	cmpq	%r13, %rcx
	je	.L154
.L153:
	movq	8(%r13), %r12
	movq	0(%r13), %rbp
	flds	.LC14(%rip)
	cmpq	%r12, %rbp
	je	.L183
	.p2align 4,,10
	.p2align 3
.L162:
	movq	0(%rbp), %rdx
	movq	8(%rbp), %rbx
	cmpq	%rdx, %rbx
	je	.L155
	movq	10048(%rsp), %rsi
	vmovsd	.LC12(%rip), %xmm2
	movq	%rdx, %r15
	.p2align 4,,10
	.p2align 3
.L156:
	movq	%rsi, %rax
	movl	$2, %r14d
	vxorpd	%xmm1, %xmm1, %xmm1
	vmovsd	%xmm2, 8(%rsp)
	cmpq	$623, %rsi
	ja	.L184
.L157:
	leaq	1(%rax), %rsi
	movq	5056(%rsp,%rax,8), %rax
	movq	%rsi, 10048(%rsp)
	movq	%rax, %rdi
	shrq	$11, %rdi
	movl	%edi, %edi
	xorq	%rdi, %rax
	movq	%rax, %rdi
	salq	$7, %rdi
	andl	$2636928640, %edi
	xorq	%rdi, %rax
	movq	%rax, %rdi
	salq	$15, %rdi
	andl	$4022730752, %edi
	xorq	%rdi, %rax
	movq	%rax, %rdi
	shrq	$18, %rdi
	xorq	%rdi, %rax
	js	.L158
	vcvtsi2sdq	%rax, %xmm3, %xmm0
.L159:
	vmulsd	8(%rsp), %xmm0, %xmm0
	fld	%st(0)
	fmull	8(%rsp)
	vaddsd	%xmm0, %xmm1, %xmm1
	fstpl	8(%rsp)
	cmpl	$1, %r14d
	je	.L181
	movl	$1, %r14d
	movq	%rsi, %rax
	cmpq	$623, %rsi
	jbe	.L157
	fstp	%st(0)
	jmp	.L180
	.p2align 4,,10
	.p2align 3
.L184:
	fstp	%st(0)
.L180:
	leaq	5056(%rsp), %rdi
	vmovsd	%xmm1, 16(%rsp)
	call	_ZNSt23mersenne_twister_engineImLm32ELm624ELm397ELm31ELm2567483615ELm11ELm4294967295ELm7ELm2636928640ELm15ELm4022730752ELm18ELm1812433253EE11_M_gen_randEv
	movq	.LC12(%rip), %rcx
	flds	.LC14(%rip)
	vxorps	%xmm3, %xmm3, %xmm3
	movq	10048(%rsp), %rax
	vmovsd	16(%rsp), %xmm1
	vmovq	%rcx, %xmm2
	jmp	.L157
	.p2align 4,,10
	.p2align 3
.L181:
	vdivsd	8(%rsp), %xmm1, %xmm1
	vcomisd	%xmm2, %xmm1
	jnb	.L166
	vxorpd	%xmm0, %xmm0, %xmm0
	vaddsd	%xmm0, %xmm1, %xmm1
.L161:
	vmovsd	%xmm1, (%r15)
	addq	$8, %r15
	cmpq	%r15, %rbx
	jne	.L156
.L155:
	addq	$24, %rbp
	cmpq	%rbp, %r12
	jne	.L162
	fstp	%st(0)
	jmp	.L163
.L183:
	fstp	%st(0)
.L163:
	addq	$24, %r13
	cmpq	%r13, 24(%rsp)
	jne	.L153
.L154:
	addq	$24, 32(%rsp)
	movq	32(%rsp), %rax
	cmpq	%rax, 40(%rsp)
	jne	.L150
.L151:
	leaq	48(%rsp), %rdi
	call	_ZNSt13random_device7_M_finiEv
	addq	$10072, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 56
	popq	%rbx
	.cfi_def_cfa_offset 48
	popq	%rbp
	.cfi_def_cfa_offset 40
	popq	%r12
	.cfi_def_cfa_offset 32
	popq	%r13
	.cfi_def_cfa_offset 24
	popq	%r14
	.cfi_def_cfa_offset 16
	popq	%r15
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L158:
	.cfi_restore_state
	movq	%rax, %rdi
	andl	$1, %eax
	shrq	%rdi
	orq	%rax, %rdi
	vcvtsi2sdq	%rdi, %xmm3, %xmm0
	vaddsd	%xmm0, %xmm0, %xmm0
	jmp	.L159
	.p2align 4,,10
	.p2align 3
.L166:
	vmovsd	.LC13(%rip), %xmm1
	jmp	.L161
.L168:
	movq	%rax, %rbx
	jmp	.L145
.L167:
	movq	%rax, %rbx
	jmp	.L164
	.globl	__gxx_personality_v0
	.section	.gcc_except_table,"a",@progbits
.LLSDA9518:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE9518-.LLSDACSB9518
.LLSDACSB9518:
	.uleb128 .LEHB0-.LFB9518
	.uleb128 .LEHE0-.LEHB0
	.uleb128 .L168-.LFB9518
	.uleb128 0
	.uleb128 .LEHB1-.LFB9518
	.uleb128 .LEHE1-.LEHB1
	.uleb128 .L167-.LFB9518
	.uleb128 0
.LLSDACSE9518:
	.text
	.cfi_endproc
	.section	.text.unlikely
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	.cfi_lsda 0x3,.LLSDAC9518
	.type	_Z20randomize_one_matrixRSt6vectorIS_IS_IS_IdSaIdEESaIS1_EESaIS3_EESaIS5_EE.cold, @function
_Z20randomize_one_matrixRSt6vectorIS_IS_IS_IdSaIdEESaIS1_EESaIS3_EESaIS5_EE.cold:
.LFSB9518:
.L145:
	.cfi_def_cfa_offset 10128
	.cfi_offset 3, -56
	.cfi_offset 6, -48
	.cfi_offset 12, -40
	.cfi_offset 13, -32
	.cfi_offset 14, -24
	.cfi_offset 15, -16
	movq	5056(%rsp), %rdi
	cmpq	%rbp, %rdi
	jne	.L182
	vzeroupper
.L146:
	movq	%rbx, %rdi
.LEHB2:
	call	_Unwind_Resume
.LEHE2:
.L164:
	leaq	48(%rsp), %rdi
	vzeroupper
	call	_ZNSt13random_device7_M_finiEv
	movq	%rbx, %rdi
.LEHB3:
	call	_Unwind_Resume
.LEHE3:
.L182:
	vzeroupper
	call	_ZdlPv
	jmp	.L146
	.cfi_endproc
.LFE9518:
	.section	.gcc_except_table
.LLSDAC9518:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSEC9518-.LLSDACSBC9518
.LLSDACSBC9518:
	.uleb128 .LEHB2-.LCOLDB16
	.uleb128 .LEHE2-.LEHB2
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB3-.LCOLDB16
	.uleb128 .LEHE3-.LEHB3
	.uleb128 0
	.uleb128 0
.LLSDACSEC9518:
	.section	.text.unlikely
	.text
	.size	_Z20randomize_one_matrixRSt6vectorIS_IS_IS_IdSaIdEESaIS1_EESaIS3_EESaIS5_EE, .-_Z20randomize_one_matrixRSt6vectorIS_IS_IS_IdSaIdEESaIS1_EESaIS3_EESaIS5_EE
	.section	.text.unlikely
	.size	_Z20randomize_one_matrixRSt6vectorIS_IS_IS_IdSaIdEESaIS1_EESaIS3_EESaIS5_EE.cold, .-_Z20randomize_one_matrixRSt6vectorIS_IS_IS_IdSaIdEESaIS1_EESaIS3_EESaIS5_EE.cold
.LCOLDE16:
	.text
.LHOTE16:
	.section	.text._ZSt18__do_uninit_fill_nIPSt6vectorIdSaIdEEmS2_ET_S4_T0_RKT1_,"axG",@progbits,_ZSt18__do_uninit_fill_nIPSt6vectorIdSaIdEEmS2_ET_S4_T0_RKT1_,comdat
	.p2align 4
	.weak	_ZSt18__do_uninit_fill_nIPSt6vectorIdSaIdEEmS2_ET_S4_T0_RKT1_
	.type	_ZSt18__do_uninit_fill_nIPSt6vectorIdSaIdEEmS2_ET_S4_T0_RKT1_, @function
_ZSt18__do_uninit_fill_nIPSt6vectorIdSaIdEEmS2_ET_S4_T0_RKT1_:
.LFB10293:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	.cfi_lsda 0x3,.LLSDA10293
	pushq	%r15
	.cfi_def_cfa_offset 16
	.cfi_offset 15, -16
	pushq	%r14
	.cfi_def_cfa_offset 24
	.cfi_offset 14, -24
	pushq	%r13
	.cfi_def_cfa_offset 32
	.cfi_offset 13, -32
	pushq	%r12
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	pushq	%rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	pushq	%rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	subq	$24, %rsp
	.cfi_def_cfa_offset 80
	movq	%rdi, 8(%rsp)
	testq	%rsi, %rsi
	je	.L195
	movq	(%rdx), %r14
	movq	%rsi, %r13
	movq	%rdx, %r12
	movq	%rdi, %rbp
	movabsq	$9223372036854775800, %r15
	jmp	.L192
	.p2align 4,,10
	.p2align 3
.L202:
	cmpq	%rbx, %r15
	jb	.L201
	movq	%rbx, %rdi
.LEHB4:
	call	_Znwm
	movq	%rax, %rcx
.L187:
	vmovq	%rcx, %xmm1
	addq	%rcx, %rbx
	vpunpcklqdq	%xmm1, %xmm1, %xmm0
	movq	%rbx, 16(%rbp)
	vmovdqu	%xmm0, 0(%rbp)
	movq	8(%r12), %rax
	movq	(%r12), %r14
	movq	%rax, %rbx
	subq	%r14, %rbx
	cmpq	%r14, %rax
	je	.L191
	movq	%rcx, %rdi
	movq	%rbx, %rdx
	movq	%r14, %rsi
	call	memmove
	movq	%rax, %rcx
.L191:
	addq	%rbx, %rcx
	addq	$24, %rbp
	movq	%rcx, -16(%rbp)
	subq	$1, %r13
	je	.L185
.L192:
	movq	8(%r12), %rbx
	vpxor	%xmm0, %xmm0, %xmm0
	movq	$0, 16(%rbp)
	vmovdqu	%xmm0, 0(%rbp)
	subq	%r14, %rbx
	jne	.L202
	xorl	%ecx, %ecx
	jmp	.L187
	.p2align 4,,10
	.p2align 3
.L195:
	movq	8(%rsp), %rbp
.L185:
	addq	$24, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 56
	movq	%rbp, %rax
	popq	%rbx
	.cfi_def_cfa_offset 48
	popq	%rbp
	.cfi_def_cfa_offset 40
	popq	%r12
	.cfi_def_cfa_offset 32
	popq	%r13
	.cfi_def_cfa_offset 24
	popq	%r14
	.cfi_def_cfa_offset 16
	popq	%r15
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L201:
	.cfi_restore_state
	testq	%rbx, %rbx
	jns	.L189
	call	_ZSt28__throw_bad_array_new_lengthv
	.p2align 4,,10
	.p2align 3
.L189:
	call	_ZSt17__throw_bad_allocv
.LEHE4:
.L197:
	movq	%rax, %rdi
.L193:
	vzeroupper
	call	__cxa_begin_catch
	movq	8(%rsp), %rdi
	movq	%rbp, %rsi
	call	_ZNSt12_Destroy_auxILb0EE9__destroyIPSt6vectorIdSaIdEEEEvT_S6_
.LEHB5:
	call	__cxa_rethrow
.LEHE5:
.L198:
	movq	%rax, %rbx
.L194:
	vzeroupper
	call	__cxa_end_catch
	movq	%rbx, %rdi
.LEHB6:
	call	_Unwind_Resume
.LEHE6:
	.cfi_endproc
.LFE10293:
	.section	.gcc_except_table
	.align 4
.LLSDA10293:
	.byte	0xff
	.byte	0x3
	.uleb128 .LLSDATT10293-.LLSDATTD10293
.LLSDATTD10293:
	.byte	0x1
	.uleb128 .LLSDACSE10293-.LLSDACSB10293
.LLSDACSB10293:
	.uleb128 .LEHB4-.LFB10293
	.uleb128 .LEHE4-.LEHB4
	.uleb128 .L197-.LFB10293
	.uleb128 0x1
	.uleb128 .LEHB5-.LFB10293
	.uleb128 .LEHE5-.LEHB5
	.uleb128 .L198-.LFB10293
	.uleb128 0
	.uleb128 .LEHB6-.LFB10293
	.uleb128 .LEHE6-.LEHB6
	.uleb128 0
	.uleb128 0
.LLSDACSE10293:
	.byte	0x1
	.byte	0
	.align 4
	.long	0

.LLSDATT10293:
	.section	.text._ZSt18__do_uninit_fill_nIPSt6vectorIdSaIdEEmS2_ET_S4_T0_RKT1_,"axG",@progbits,_ZSt18__do_uninit_fill_nIPSt6vectorIdSaIdEEmS2_ET_S4_T0_RKT1_,comdat
	.size	_ZSt18__do_uninit_fill_nIPSt6vectorIdSaIdEEmS2_ET_S4_T0_RKT1_, .-_ZSt18__do_uninit_fill_nIPSt6vectorIdSaIdEEmS2_ET_S4_T0_RKT1_
	.section	.text._ZNSt6vectorIS_IdSaIdEESaIS1_EEC2EmRKS1_RKS2_,"axG",@progbits,_ZNSt6vectorIS_IdSaIdEESaIS1_EEC5EmRKS1_RKS2_,comdat
	.align 2
	.p2align 4
	.weak	_ZNSt6vectorIS_IdSaIdEESaIS1_EEC2EmRKS1_RKS2_
	.type	_ZNSt6vectorIS_IdSaIdEESaIS1_EEC2EmRKS1_RKS2_, @function
_ZNSt6vectorIS_IdSaIdEESaIS1_EEC2EmRKS1_RKS2_:
.LFB9818:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	.cfi_lsda 0x3,.LLSDA9818
	movabsq	$384307168202282325, %rax
	pushq	%r13
	.cfi_def_cfa_offset 16
	.cfi_offset 13, -16
	pushq	%r12
	.cfi_def_cfa_offset 24
	.cfi_offset 12, -24
	pushq	%rbp
	.cfi_def_cfa_offset 32
	.cfi_offset 6, -32
	pushq	%rbx
	.cfi_def_cfa_offset 40
	.cfi_offset 3, -40
	subq	$8, %rsp
	.cfi_def_cfa_offset 48
	cmpq	%rsi, %rax
	jb	.L218
	vpxor	%xmm0, %xmm0, %xmm0
	leaq	(%rsi,%rsi,2), %r12
	movq	%rdi, %rbp
	movq	%rsi, %rbx
	movq	$0, 16(%rdi)
	movq	%rdx, %r13
	salq	$3, %r12
	vmovdqu	%xmm0, (%rdi)
	xorl	%edi, %edi
	testq	%rsi, %rsi
	je	.L205
	movq	%r12, %rdi
.LEHB7:
	call	_Znwm
.LEHE7:
	movq	%rax, %rdi
.L205:
	addq	%rdi, %r12
	vmovq	%rdi, %xmm1
	movq	%r13, %rdx
	movq	%rbx, %rsi
	movq	%r12, 16(%rbp)
	vpunpcklqdq	%xmm1, %xmm1, %xmm0
	vmovdqu	%xmm0, 0(%rbp)
.LEHB8:
	call	_ZSt18__do_uninit_fill_nIPSt6vectorIdSaIdEEmS2_ET_S4_T0_RKT1_
.LEHE8:
	movq	%rax, 8(%rbp)
	addq	$8, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 40
	popq	%rbx
	.cfi_def_cfa_offset 32
	popq	%rbp
	.cfi_def_cfa_offset 24
	popq	%r12
	.cfi_def_cfa_offset 16
	popq	%r13
	.cfi_def_cfa_offset 8
	ret
.L218:
	.cfi_restore_state
	movl	$.LC5, %edi
.LEHB9:
	call	_ZSt20__throw_length_errorPKc
.L209:
	movq	%rax, %rbx
.L206:
	movq	0(%rbp), %rdi
	testq	%rdi, %rdi
	je	.L215
	vzeroupper
	call	_ZdlPv
.L207:
	movq	%rbx, %rdi
	call	_Unwind_Resume
.LEHE9:
.L215:
	vzeroupper
	jmp	.L207
	.cfi_endproc
.LFE9818:
	.section	.gcc_except_table
.LLSDA9818:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE9818-.LLSDACSB9818
.LLSDACSB9818:
	.uleb128 .LEHB7-.LFB9818
	.uleb128 .LEHE7-.LEHB7
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB8-.LFB9818
	.uleb128 .LEHE8-.LEHB8
	.uleb128 .L209-.LFB9818
	.uleb128 0
	.uleb128 .LEHB9-.LFB9818
	.uleb128 .LEHE9-.LEHB9
	.uleb128 0
	.uleb128 0
.LLSDACSE9818:
	.section	.text._ZNSt6vectorIS_IdSaIdEESaIS1_EEC2EmRKS1_RKS2_,"axG",@progbits,_ZNSt6vectorIS_IdSaIdEESaIS1_EEC5EmRKS1_RKS2_,comdat
	.size	_ZNSt6vectorIS_IdSaIdEESaIS1_EEC2EmRKS1_RKS2_, .-_ZNSt6vectorIS_IdSaIdEESaIS1_EEC2EmRKS1_RKS2_
	.weak	_ZNSt6vectorIS_IdSaIdEESaIS1_EEC1EmRKS1_RKS2_
	.set	_ZNSt6vectorIS_IdSaIdEESaIS1_EEC1EmRKS1_RKS2_,_ZNSt6vectorIS_IdSaIdEESaIS1_EEC2EmRKS1_RKS2_
	.section	.text.unlikely
.LCOLDB17:
	.text
.LHOTB17:
	.p2align 4
	.globl	_Z17multiply_matricesRSt6vectorIS_IdSaIdEESaIS1_EES4_
	.type	_Z17multiply_matricesRSt6vectorIS_IdSaIdEESaIS1_EES4_, @function
_Z17multiply_matricesRSt6vectorIS_IdSaIdEESaIS1_EES4_:
.LFB9540:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	.cfi_lsda 0x3,.LLSDA9540
	pushq	%r13
	.cfi_def_cfa_offset 16
	.cfi_offset 13, -16
	pushq	%r12
	.cfi_def_cfa_offset 24
	.cfi_offset 12, -24
	movq	%rsi, %r12
	movl	$10, %esi
	pushq	%rbp
	.cfi_def_cfa_offset 32
	.cfi_offset 6, -32
	movq	%rdx, %rbp
	pushq	%rbx
	.cfi_def_cfa_offset 40
	.cfi_offset 3, -40
	movq	%rdi, %rbx
	subq	$56, %rsp
	.cfi_def_cfa_offset 96
	leaq	22(%rsp), %rdx
	leaq	24(%rsp), %rdi
.LEHB10:
	call	_ZNSt6vectorIdSaIdEEC1EmRKS0_
.LEHE10:
	leaq	23(%rsp), %rcx
	leaq	24(%rsp), %rdx
	movq	%rbx, %rdi
	movl	$10, %esi
.LEHB11:
	call	_ZNSt6vectorIS_IdSaIdEESaIS1_EEC1EmRKS1_RKS2_
.LEHE11:
	leaq	24(%rsp), %rdi
	call	_ZNSt6vectorIdSaIdEED1Ev
	movq	(%r12), %r13
	movq	(%rbx), %r12
	movq	0(%rbp), %r10
	xorl	%ebp, %ebp
.L220:
	movq	%rbp, %rsi
	movq	%r13, %rdi
	xorl	%ecx, %ecx
	call	_ZNSt6vectorIS_IdSaIdEESaIS1_EEixEm.isra.0
	movq	%r12, %rdi
	movq	(%rax), %r9
	call	_ZNSt6vectorIS_IdSaIdEESaIS1_EEixEm.isra.0
	movq	(%rax), %r11
	.p2align 4,,10
	.p2align 3
.L224:
	movq	%rcx, %rsi
	movq	%r11, %rdi
	xorl	%edx, %edx
	call	_ZNSt6vectorIdSaIdEEixEm.isra.0
	fldl	(%rax)
	movq	%rax, %r8
	.p2align 4,,10
	.p2align 3
.L221:
	movq	%rdx, %rsi
	movq	%r9, %rdi
	fstpl	8(%rsp)
	addq	$1, %rdx
	call	_ZNSt6vectorIdSaIdEEixEm.isra.0
	movq	%r10, %rdi
	fldl	(%rax)
	fstpl	(%rsp)
	call	_ZNSt6vectorIS_IdSaIdEESaIS1_EEixEm.isra.0
	movq	%rcx, %rsi
	movq	(%rax), %rdi
	call	_ZNSt6vectorIdSaIdEEixEm.isra.0
	fldl	(%rsp)
	fmull	(%rax)
	fldl	8(%rsp)
	faddp	%st, %st(1)
	fstl	(%r8)
	cmpq	$10, %rdx
	jne	.L221
	fstp	%st(0)
	addq	$1, %rcx
	cmpq	$10, %rcx
	jne	.L224
	addq	$1, %rbp
	cmpq	$10, %rbp
	jne	.L220
	addq	$56, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 40
	movq	%rbx, %rax
	popq	%rbx
	.cfi_def_cfa_offset 32
	popq	%rbp
	.cfi_def_cfa_offset 24
	popq	%r12
	.cfi_def_cfa_offset 16
	popq	%r13
	.cfi_def_cfa_offset 8
	ret
.L226:
	.cfi_restore_state
	movq	%rax, %rbx
	jmp	.L225
	.section	.gcc_except_table
.LLSDA9540:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE9540-.LLSDACSB9540
.LLSDACSB9540:
	.uleb128 .LEHB10-.LFB9540
	.uleb128 .LEHE10-.LEHB10
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB11-.LFB9540
	.uleb128 .LEHE11-.LEHB11
	.uleb128 .L226-.LFB9540
	.uleb128 0
.LLSDACSE9540:
	.text
	.cfi_endproc
	.section	.text.unlikely
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	.cfi_lsda 0x3,.LLSDAC9540
	.type	_Z17multiply_matricesRSt6vectorIS_IdSaIdEESaIS1_EES4_.cold, @function
_Z17multiply_matricesRSt6vectorIS_IdSaIdEESaIS1_EES4_.cold:
.LFSB9540:
.L225:
	.cfi_def_cfa_offset 96
	.cfi_offset 3, -40
	.cfi_offset 6, -32
	.cfi_offset 12, -24
	.cfi_offset 13, -16
	leaq	24(%rsp), %rdi
	call	_ZNSt6vectorIdSaIdEED1Ev
	movq	%rbx, %rdi
.LEHB12:
	call	_Unwind_Resume
.LEHE12:
	.cfi_endproc
.LFE9540:
	.section	.gcc_except_table
.LLSDAC9540:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSEC9540-.LLSDACSBC9540
.LLSDACSBC9540:
	.uleb128 .LEHB12-.LCOLDB17
	.uleb128 .LEHE12-.LEHB12
	.uleb128 0
	.uleb128 0
.LLSDACSEC9540:
	.section	.text.unlikely
	.text
	.size	_Z17multiply_matricesRSt6vectorIS_IdSaIdEESaIS1_EES4_, .-_Z17multiply_matricesRSt6vectorIS_IdSaIdEESaIS1_EES4_
	.section	.text.unlikely
	.size	_Z17multiply_matricesRSt6vectorIS_IdSaIdEESaIS1_EES4_.cold, .-_Z17multiply_matricesRSt6vectorIS_IdSaIdEESaIS1_EES4_.cold
.LCOLDE17:
	.text
.LHOTE17:
	.section	.text.unlikely
.LCOLDB19:
	.text
.LHOTB19:
	.p2align 4
	.globl	_Z21multiply_matrices_avxRSt6vectorIS_IdSaIdEESaIS1_EES4_
	.type	_Z21multiply_matrices_avxRSt6vectorIS_IdSaIdEESaIS1_EES4_, @function
_Z21multiply_matrices_avxRSt6vectorIS_IdSaIdEESaIS1_EES4_:
.LFB9520:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	.cfi_lsda 0x3,.LLSDA9520
	pushq	%r13
	.cfi_def_cfa_offset 16
	.cfi_offset 13, -16
	movq	%rdx, %r13
	pushq	%r12
	.cfi_def_cfa_offset 24
	.cfi_offset 12, -24
	movq	%rsi, %r12
	pushq	%rbp
	.cfi_def_cfa_offset 32
	.cfi_offset 6, -32
	pushq	%rbx
	.cfi_def_cfa_offset 40
	.cfi_offset 3, -40
	movq	%rdi, %rbx
	movl	$80, %edi
	subq	$40, %rsp
	.cfi_def_cfa_offset 80
.LEHB13:
	call	_Znwm
.LEHE13:
	vpxor	%xmm0, %xmm0, %xmm0
	movl	$240, %edi
	movq	$0, 16(%rbx)
	leaq	80(%rax), %rdx
	movq	$0x000000000, (%rax)
	movq	%rax, %rbp
	movq	%rax, (%rsp)
	leaq	8(%rax), %rax
	vmovdqu	%xmm0, 8(%rbp)
	movq	%rdx, 16(%rsp)
	movq	$0, 64(%rax)
	vmovdqu	%xmm0, 16(%rax)
	vmovdqu	%xmm0, 32(%rax)
	vmovdqu	%xmm0, 48(%rax)
	vpxor	%xmm0, %xmm0, %xmm0
	vmovdqu	%xmm0, (%rbx)
	movq	%rdx, 8(%rsp)
.LEHB14:
	call	_Znwm
.LEHE14:
	vmovq	%rax, %xmm2
	movq	%rax, %rdi
	movq	%rsp, %rdx
	movl	$10, %esi
	leaq	240(%rax), %rax
	vpunpcklqdq	%xmm2, %xmm2, %xmm0
	movq	%rax, 16(%rbx)
	vmovdqu	%xmm0, (%rbx)
.LEHB15:
	call	_ZSt18__do_uninit_fill_nIPSt6vectorIdSaIdEEmS2_ET_S4_T0_RKT1_
.LEHE15:
	movq	%rax, 8(%rbx)
	movq	%rbp, %rdi
	call	_ZdlPv
	movq	0(%r13), %r10
	movq	(%r12), %r12
	xorl	%r11d, %r11d
	movq	(%rbx), %rbp
	leaq	240(%r10), %r8
.L231:
	movq	(%r12,%r11), %r9
	movq	0(%rbp,%r11), %rdi
	xorl	%esi, %esi
	.p2align 4,,10
	.p2align 3
.L238:
	vmovsd	(%rdi), %xmm1
	movq	%r9, %rdx
	movq	%r10, %rax
	.p2align 4,,10
	.p2align 3
.L235:
	movq	(%rax), %rcx
	addq	$24, %rax
	addq	$8, %rdx
	vmovsd	(%rcx,%rsi), %xmm0
	vmulsd	-8(%rdx), %xmm0, %xmm0
	vaddsd	%xmm0, %xmm1, %xmm1
	vmovsd	%xmm1, (%rdi)
	cmpq	%rax, %r8
	jne	.L235
	addq	$8, %rsi
	addq	$8, %rdi
	cmpq	$80, %rsi
	jne	.L238
	addq	$24, %r11
	cmpq	$240, %r11
	jne	.L231
	addq	$40, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 40
	movq	%rbx, %rax
	popq	%rbx
	.cfi_def_cfa_offset 32
	popq	%rbp
	.cfi_def_cfa_offset 24
	popq	%r12
	.cfi_def_cfa_offset 16
	popq	%r13
	.cfi_def_cfa_offset 8
	ret
.L239:
	.cfi_restore_state
	movq	%rax, %r12
	vzeroupper
	jmp	.L234
.L240:
	movq	%rax, %r12
	jmp	.L232
	.section	.gcc_except_table
.LLSDA9520:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE9520-.LLSDACSB9520
.LLSDACSB9520:
	.uleb128 .LEHB13-.LFB9520
	.uleb128 .LEHE13-.LEHB13
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB14-.LFB9520
	.uleb128 .LEHE14-.LEHB14
	.uleb128 .L239-.LFB9520
	.uleb128 0
	.uleb128 .LEHB15-.LFB9520
	.uleb128 .LEHE15-.LEHB15
	.uleb128 .L240-.LFB9520
	.uleb128 0
.LLSDACSE9520:
	.text
	.cfi_endproc
	.section	.text.unlikely
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	.cfi_lsda 0x3,.LLSDAC9520
	.type	_Z21multiply_matrices_avxRSt6vectorIS_IdSaIdEESaIS1_EES4_.cold, @function
_Z21multiply_matrices_avxRSt6vectorIS_IdSaIdEESaIS1_EES4_.cold:
.LFSB9520:
.L232:
	.cfi_def_cfa_offset 80
	.cfi_offset 3, -40
	.cfi_offset 6, -32
	.cfi_offset 12, -24
	.cfi_offset 13, -16
	movq	(%rbx), %rdi
	testq	%rdi, %rdi
	je	.L245
	vzeroupper
	call	_ZdlPv
.L234:
	movq	%rbp, %rdi
	call	_ZdlPv
	movq	%r12, %rdi
.LEHB16:
	call	_Unwind_Resume
.LEHE16:
.L245:
	vzeroupper
	jmp	.L234
	.cfi_endproc
.LFE9520:
	.section	.gcc_except_table
.LLSDAC9520:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSEC9520-.LLSDACSBC9520
.LLSDACSBC9520:
	.uleb128 .LEHB16-.LCOLDB19
	.uleb128 .LEHE16-.LEHB16
	.uleb128 0
	.uleb128 0
.LLSDACSEC9520:
	.section	.text.unlikely
	.text
	.size	_Z21multiply_matrices_avxRSt6vectorIS_IdSaIdEESaIS1_EES4_, .-_Z21multiply_matrices_avxRSt6vectorIS_IdSaIdEESaIS1_EES4_
	.section	.text.unlikely
	.size	_Z21multiply_matrices_avxRSt6vectorIS_IdSaIdEESaIS1_EES4_.cold, .-_Z21multiply_matrices_avxRSt6vectorIS_IdSaIdEESaIS1_EES4_.cold
.LCOLDE19:
	.text
.LHOTE19:
	.section	.text.unlikely
.LCOLDB20:
	.text
.LHOTB20:
	.p2align 4
	.globl	_Z26multiply_matrices_manuallyRSt6vectorIS_IdSaIdEESaIS1_EES4_
	.type	_Z26multiply_matrices_manuallyRSt6vectorIS_IdSaIdEESaIS1_EES4_, @function
_Z26multiply_matrices_manuallyRSt6vectorIS_IdSaIdEESaIS1_EES4_:
.LFB9542:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	.cfi_lsda 0x3,.LLSDA9542
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%r15
	pushq	%r14
	.cfi_offset 15, -24
	.cfi_offset 14, -32
	movq	%rdi, %r14
	pushq	%r13
	.cfi_offset 13, -40
	movq	%rsi, %r13
	pushq	%r12
	.cfi_offset 12, -48
	movq	%rdx, %r12
	pushq	%rbx
	andq	$-32, %rsp
	subq	$64, %rsp
	.cfi_offset 3, -56
	movq	%rdi, 8(%rsp)
	movl	$80, %edi
.LEHB17:
	call	_Znwm
.LEHE17:
	vpxor	%xmm0, %xmm0, %xmm0
	movl	$240, %edi
	movq	$0, 16(%r14)
	leaq	80(%rax), %rdx
	movq	$0x000000000, (%rax)
	movq	%rax, %rbx
	movq	%rax, 32(%rsp)
	leaq	8(%rax), %rax
	vmovdqu	%xmm0, 8(%rbx)
	movq	%rdx, 48(%rsp)
	movq	$0, 64(%rax)
	vmovdqu	%xmm0, 16(%rax)
	vmovdqu	%xmm0, 32(%rax)
	vmovdqu	%xmm0, 48(%rax)
	vpxor	%xmm0, %xmm0, %xmm0
	vmovdqu	%xmm0, (%r14)
	movq	%rdx, 40(%rsp)
.LEHB18:
	call	_Znwm
.LEHE18:
	vmovq	%rax, %xmm4
	movq	%rax, %rdi
	leaq	32(%rsp), %rdx
	movl	$10, %esi
	leaq	240(%rax), %rax
	vpunpcklqdq	%xmm4, %xmm4, %xmm0
	movq	%rax, 16(%r14)
	vmovdqu	%xmm0, (%r14)
.LEHB19:
	call	_ZSt18__do_uninit_fill_nIPSt6vectorIdSaIdEEmS2_ET_S4_T0_RKT1_
.LEHE19:
	movq	%rax, 8(%r14)
	movq	%rbx, %rdi
	movq	%r14, 8(%rsp)
	call	_ZdlPv
	movq	0(%r13), %rax
	movq	8(%rsp), %rbx
	xorl	%esi, %esi
	vxorpd	%xmm1, %xmm1, %xmm1
	movq	%rax, 16(%rsp)
	movq	(%r12), %rax
	movq	(%rbx), %rbx
	movq	72(%rax), %r15
	movq	48(%rax), %r14
	movq	24(%rax), %r13
	movq	(%rax), %r12
	movq	96(%rax), %r11
	movq	120(%rax), %r10
	movq	144(%rax), %r9
	movq	168(%rax), %r8
	movq	192(%rax), %rdi
	movq	216(%rax), %rax
	movq	%rax, 24(%rsp)
	.p2align 4,,10
	.p2align 3
.L248:
	movq	16(%rsp), %rax
	movq	(%rax,%rsi), %rdx
	xorl	%eax, %eax
	.p2align 4,,10
	.p2align 3
.L255:
	vmovsd	(%r14,%rax), %xmm2
	vmovsd	(%r12,%rax), %xmm0
	movq	24(%rsp), %rcx
	vmovhpd	(%r15,%rax), %xmm2, %xmm2
	vmovhpd	0(%r13,%rax), %xmm0, %xmm0
	vinsertf128	$0x1, %xmm2, %ymm0, %ymm0
	vmovsd	(%r9,%rax), %xmm2
	vmulpd	(%rdx), %ymm0, %ymm0
	vmovhpd	(%r8,%rax), %xmm2, %xmm2
	vextractf128	$0x1, %ymm0, %xmm3
	vaddpd	%xmm0, %xmm3, %xmm3
	vmovsd	(%r11,%rax), %xmm0
	vmovhpd	(%r10,%rax), %xmm0, %xmm0
	vinsertf128	$0x1, %xmm2, %ymm0, %ymm0
	vaddpd	%xmm1, %xmm3, %xmm3
	vmulpd	32(%rdx), %ymm0, %ymm0
	vextractf128	$0x1, %ymm0, %xmm2
	vaddpd	%xmm0, %xmm2, %xmm2
	vmovsd	(%rdi,%rax), %xmm0
	vmovhpd	(%rcx,%rax), %xmm0, %xmm0
	movq	(%rbx,%rsi), %rcx
	vmulpd	64(%rdx), %xmm0, %xmm0
	vaddpd	%xmm3, %xmm2, %xmm2
	addq	%rax, %rcx
	addq	$8, %rax
	vaddpd	%xmm2, %xmm0, %xmm0
	vhaddpd	%xmm0, %xmm0, %xmm0
	vaddsd	(%rcx), %xmm0, %xmm0
	vmovsd	%xmm0, (%rcx)
	cmpq	$80, %rax
	jne	.L255
	addq	$24, %rsi
	cmpq	$240, %rsi
	jne	.L248
.L258:
	movq	8(%rsp), %rax
	vzeroupper
	leaq	-40(%rbp), %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	.cfi_remember_state
	.cfi_def_cfa 7, 8
	ret
.L257:
	.cfi_restore_state
	movq	%rax, %r12
	vzeroupper
	jmp	.L251
.L259:
	movq	%rax, %r12
	jmp	.L249
	.section	.gcc_except_table
.LLSDA9542:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE9542-.LLSDACSB9542
.LLSDACSB9542:
	.uleb128 .LEHB17-.LFB9542
	.uleb128 .LEHE17-.LEHB17
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB18-.LFB9542
	.uleb128 .LEHE18-.LEHB18
	.uleb128 .L257-.LFB9542
	.uleb128 0
	.uleb128 .LEHB19-.LFB9542
	.uleb128 .LEHE19-.LEHB19
	.uleb128 .L259-.LFB9542
	.uleb128 0
.LLSDACSE9542:
	.text
	.cfi_endproc
	.section	.text.unlikely
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	.cfi_lsda 0x3,.LLSDAC9542
	.type	_Z26multiply_matrices_manuallyRSt6vectorIS_IdSaIdEESaIS1_EES4_.cold, @function
_Z26multiply_matrices_manuallyRSt6vectorIS_IdSaIdEESaIS1_EES4_.cold:
.LFSB9542:
.L249:
	.cfi_def_cfa 6, 16
	.cfi_offset 3, -56
	.cfi_offset 6, -16
	.cfi_offset 12, -48
	.cfi_offset 13, -40
	.cfi_offset 14, -32
	.cfi_offset 15, -24
	movq	8(%rsp), %rax
	movq	(%rax), %rdi
	testq	%rdi, %rdi
	je	.L263
	vzeroupper
	call	_ZdlPv
.L251:
	movq	%rbx, %rdi
	call	_ZdlPv
	movq	%r12, %rdi
.LEHB20:
	call	_Unwind_Resume
.LEHE20:
.L263:
	vzeroupper
	jmp	.L251
	.cfi_endproc
.LFE9542:
	.section	.gcc_except_table
.LLSDAC9542:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSEC9542-.LLSDACSBC9542
.LLSDACSBC9542:
	.uleb128 .LEHB20-.LCOLDB20
	.uleb128 .LEHE20-.LEHB20
	.uleb128 0
	.uleb128 0
.LLSDACSEC9542:
	.section	.text.unlikely
	.text
	.size	_Z26multiply_matrices_manuallyRSt6vectorIS_IdSaIdEESaIS1_EES4_, .-_Z26multiply_matrices_manuallyRSt6vectorIS_IdSaIdEESaIS1_EES4_
	.section	.text.unlikely
	.size	_Z26multiply_matrices_manuallyRSt6vectorIS_IdSaIdEESaIS1_EES4_.cold, .-_Z26multiply_matrices_manuallyRSt6vectorIS_IdSaIdEESaIS1_EES4_.cold
.LCOLDE20:
	.text
.LHOTE20:
	.section	.text._ZSt18__do_uninit_fill_nIPSt6vectorIS0_IS0_IdSaIdEESaIS2_EESaIS4_EEmS6_ET_S8_T0_RKT1_,"axG",@progbits,_ZSt18__do_uninit_fill_nIPSt6vectorIS0_IS0_IdSaIdEESaIS2_EESaIS4_EEmS6_ET_S8_T0_RKT1_,comdat
	.p2align 4
	.weak	_ZSt18__do_uninit_fill_nIPSt6vectorIS0_IS0_IdSaIdEESaIS2_EESaIS4_EEmS6_ET_S8_T0_RKT1_
	.type	_ZSt18__do_uninit_fill_nIPSt6vectorIS0_IS0_IdSaIdEESaIS2_EESaIS4_EEmS6_ET_S8_T0_RKT1_, @function
_ZSt18__do_uninit_fill_nIPSt6vectorIS0_IS0_IdSaIdEESaIS2_EESaIS4_EEmS6_ET_S8_T0_RKT1_:
.LFB10299:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	.cfi_lsda 0x3,.LLSDA10299
	pushq	%r15
	.cfi_def_cfa_offset 16
	.cfi_offset 15, -16
	pushq	%r14
	.cfi_def_cfa_offset 24
	.cfi_offset 14, -24
	pushq	%r13
	.cfi_def_cfa_offset 32
	.cfi_offset 13, -32
	pushq	%r12
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	pushq	%rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	pushq	%rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	subq	$72, %rsp
	.cfi_def_cfa_offset 128
	movq	%rdi, 56(%rsp)
	movq	%rsi, 48(%rsp)
	movq	%rdx, 32(%rsp)
	testq	%rsi, %rsi
	je	.L309
	movq	%rdi, 16(%rsp)
.L286:
	movq	32(%rsp), %rax
	vpxor	%xmm0, %xmm0, %xmm0
	movq	8(%rax), %rbx
	subq	(%rax), %rbx
	movq	16(%rsp), %rax
	movq	$0, 16(%rax)
	vmovdqu	%xmm0, (%rax)
	je	.L295
	movabsq	$9223372036854775800, %rax
	cmpq	%rbx, %rax
	jb	.L320
	movq	%rbx, %rdi
.LEHB21:
	call	_Znwm
.LEHE21:
	movq	%rax, 24(%rsp)
.L267:
	movq	24(%rsp), %r15
	movq	16(%rsp), %rax
	vmovddup	24(%rsp), %xmm0
	addq	%r15, %rbx
	vmovdqu	%xmm0, (%rax)
	movq	%rbx, 16(%rax)
	movq	32(%rsp), %rax
	movq	8(%rax), %rdx
	movq	(%rax), %r13
	movq	%rdx, 40(%rsp)
	cmpq	%r13, %rdx
	je	.L296
.L281:
	movq	8(%r13), %rbx
	vpxor	%xmm0, %xmm0, %xmm0
	subq	0(%r13), %rbx
	movq	$0, 16(%r15)
	vmovdqu	%xmm0, (%r15)
	je	.L297
	movabsq	$9223372036854775800, %rax
	cmpq	%rbx, %rax
	jb	.L321
	movq	%rbx, %rdi
.LEHB22:
	call	_Znwm
.LEHE22:
	movq	%rax, 8(%rsp)
.L271:
	movq	8(%rsp), %r12
	vmovddup	8(%rsp), %xmm0
	vmovdqu	%xmm0, (%r15)
	addq	%r12, %rbx
	movq	%rbx, 16(%r15)
	movq	8(%r13), %r14
	movq	0(%r13), %rbp
	cmpq	%rbp, %r14
	jne	.L280
	jmp	.L298
	.p2align 4,,10
	.p2align 3
.L323:
	movabsq	$9223372036854775800, %rax
	cmpq	%rbx, %rax
	jb	.L322
	movq	%rbx, %rdi
.LEHB23:
	call	_Znwm
	movq	%rax, %rcx
.L275:
	vmovq	%rcx, %xmm1
	addq	%rcx, %rbx
	vpunpcklqdq	%xmm1, %xmm1, %xmm0
	movq	%rbx, 16(%r12)
	vmovdqu	%xmm0, (%r12)
	movq	8(%rbp), %rax
	movq	0(%rbp), %rsi
	movq	%rax, %rbx
	subq	%rsi, %rbx
	cmpq	%rsi, %rax
	je	.L279
	movq	%rcx, %rdi
	movq	%rbx, %rdx
	call	memmove
	movq	%rax, %rcx
.L279:
	addq	%rbx, %rcx
	addq	$24, %rbp
	addq	$24, %r12
	movq	%rcx, -16(%r12)
	cmpq	%rbp, %r14
	je	.L274
.L280:
	movq	8(%rbp), %rbx
	vpxor	%xmm0, %xmm0, %xmm0
	subq	0(%rbp), %rbx
	movq	$0, 16(%r12)
	vmovdqu	%xmm0, (%r12)
	jne	.L323
	xorl	%ecx, %ecx
	jmp	.L275
	.p2align 4,,10
	.p2align 3
.L298:
	movq	8(%rsp), %r12
	.p2align 4,,10
	.p2align 3
.L274:
	movq	%r12, 8(%r15)
	addq	$24, %r13
	addq	$24, %r15
	cmpq	%r13, 40(%rsp)
	jne	.L281
.L270:
	movq	16(%rsp), %rax
	movq	%r15, 8(%rax)
	addq	$24, %rax
	subq	$1, 48(%rsp)
	movq	%rax, 16(%rsp)
	jne	.L286
	movq	%rax, 56(%rsp)
.L309:
	movq	56(%rsp), %rax
	addq	$72, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 56
	popq	%rbx
	.cfi_def_cfa_offset 48
	popq	%rbp
	.cfi_def_cfa_offset 40
	popq	%r12
	.cfi_def_cfa_offset 32
	popq	%r13
	.cfi_def_cfa_offset 24
	popq	%r14
	.cfi_def_cfa_offset 16
	popq	%r15
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L297:
	.cfi_restore_state
	movq	$0, 8(%rsp)
	jmp	.L271
	.p2align 4,,10
	.p2align 3
.L322:
	testq	%rbx, %rbx
	jns	.L277
	call	_ZSt28__throw_bad_array_new_lengthv
	.p2align 4,,10
	.p2align 3
.L295:
	movq	$0, 24(%rsp)
	jmp	.L267
	.p2align 4,,10
	.p2align 3
.L277:
	call	_ZSt17__throw_bad_allocv
.LEHE23:
.L321:
	testq	%rbx, %rbx
	jns	.L273
.LEHB24:
	call	_ZSt28__throw_bad_array_new_lengthv
.L296:
	movq	24(%rsp), %r15
	jmp	.L270
.L273:
	call	_ZSt17__throw_bad_allocv
.LEHE24:
.L320:
	testq	%rbx, %rbx
	jns	.L269
.LEHB25:
	call	_ZSt28__throw_bad_array_new_lengthv
.L269:
	call	_ZSt17__throw_bad_allocv
.LEHE25:
.L305:
	movq	%rax, %rdi
	jmp	.L282
.L303:
	movq	%rax, %rdi
	jmp	.L285
.L300:
	movq	%rax, %rdi
	jmp	.L291
.L282:
	vzeroupper
	call	__cxa_begin_catch
	movq	8(%rsp), %rdi
	movq	%r12, %rsi
	call	_ZNSt12_Destroy_auxILb0EE9__destroyIPSt6vectorIdSaIdEEEEvT_S6_
.LEHB26:
	call	__cxa_rethrow
.LEHE26:
.L283:
	vzeroupper
	call	__cxa_end_catch
	movq	(%r15), %rdi
	testq	%rdi, %rdi
	jne	.L324
.L284:
	movq	%rbx, %rdi
.L285:
	vzeroupper
	call	__cxa_begin_catch
	movq	24(%rsp), %rbx
.L287:
	cmpq	%r15, %rbx
	je	.L325
	movq	%rbx, %rdi
	addq	$24, %rbx
	call	_ZNSt6vectorIS_IdSaIdEESaIS1_EED1Ev
	jmp	.L287
.L289:
	vzeroupper
	call	__cxa_end_catch
	movq	16(%rsp), %rax
	movq	(%rax), %rdi
	testq	%rdi, %rdi
	je	.L290
	call	_ZdlPv
.L290:
	movq	%rbx, %rdi
.L291:
	vzeroupper
	call	__cxa_begin_catch
	movq	56(%rsp), %rbx
.L292:
	movq	16(%rsp), %rax
	cmpq	%rax, %rbx
	je	.L326
	movq	%rbx, %rdi
	addq	$24, %rbx
	call	_ZNSt6vectorIS_IS_IdSaIdEESaIS1_EESaIS3_EED1Ev
	jmp	.L292
.L304:
	movq	%rax, %rbx
	jmp	.L283
.L326:
.LEHB27:
	call	__cxa_rethrow
.LEHE27:
.L301:
	movq	%rax, %rbx
	jmp	.L294
.L325:
.LEHB28:
	call	__cxa_rethrow
.LEHE28:
.L294:
	vzeroupper
	call	__cxa_end_catch
	movq	%rbx, %rdi
.LEHB29:
	call	_Unwind_Resume
.LEHE29:
.L324:
	call	_ZdlPv
	jmp	.L284
.L302:
	movq	%rax, %rbx
	jmp	.L289
	.cfi_endproc
.LFE10299:
	.section	.gcc_except_table
	.align 4
.LLSDA10299:
	.byte	0xff
	.byte	0x3
	.uleb128 .LLSDATT10299-.LLSDATTD10299
.LLSDATTD10299:
	.byte	0x1
	.uleb128 .LLSDACSE10299-.LLSDACSB10299
.LLSDACSB10299:
	.uleb128 .LEHB21-.LFB10299
	.uleb128 .LEHE21-.LEHB21
	.uleb128 .L300-.LFB10299
	.uleb128 0x1
	.uleb128 .LEHB22-.LFB10299
	.uleb128 .LEHE22-.LEHB22
	.uleb128 .L303-.LFB10299
	.uleb128 0x1
	.uleb128 .LEHB23-.LFB10299
	.uleb128 .LEHE23-.LEHB23
	.uleb128 .L305-.LFB10299
	.uleb128 0x1
	.uleb128 .LEHB24-.LFB10299
	.uleb128 .LEHE24-.LEHB24
	.uleb128 .L303-.LFB10299
	.uleb128 0x1
	.uleb128 .LEHB25-.LFB10299
	.uleb128 .LEHE25-.LEHB25
	.uleb128 .L300-.LFB10299
	.uleb128 0x1
	.uleb128 .LEHB26-.LFB10299
	.uleb128 .LEHE26-.LEHB26
	.uleb128 .L304-.LFB10299
	.uleb128 0x1
	.uleb128 .LEHB27-.LFB10299
	.uleb128 .LEHE27-.LEHB27
	.uleb128 .L301-.LFB10299
	.uleb128 0
	.uleb128 .LEHB28-.LFB10299
	.uleb128 .LEHE28-.LEHB28
	.uleb128 .L302-.LFB10299
	.uleb128 0x3
	.uleb128 .LEHB29-.LFB10299
	.uleb128 .LEHE29-.LEHB29
	.uleb128 0
	.uleb128 0
.LLSDACSE10299:
	.byte	0x1
	.byte	0
	.byte	0
	.byte	0x7d
	.align 4
	.long	0

.LLSDATT10299:
	.section	.text._ZSt18__do_uninit_fill_nIPSt6vectorIS0_IS0_IdSaIdEESaIS2_EESaIS4_EEmS6_ET_S8_T0_RKT1_,"axG",@progbits,_ZSt18__do_uninit_fill_nIPSt6vectorIS0_IS0_IdSaIdEESaIS2_EESaIS4_EEmS6_ET_S8_T0_RKT1_,comdat
	.size	_ZSt18__do_uninit_fill_nIPSt6vectorIS0_IS0_IdSaIdEESaIS2_EESaIS4_EEmS6_ET_S8_T0_RKT1_, .-_ZSt18__do_uninit_fill_nIPSt6vectorIS0_IS0_IdSaIdEESaIS2_EESaIS4_EEmS6_ET_S8_T0_RKT1_
	.section	.text._ZNSt6vectorIS_IdSaIdEESaIS1_EEC2ERKS3_,"axG",@progbits,_ZNSt6vectorIS_IdSaIdEESaIS1_EEC5ERKS3_,comdat
	.align 2
	.p2align 4
	.weak	_ZNSt6vectorIS_IdSaIdEESaIS1_EEC2ERKS3_
	.type	_ZNSt6vectorIS_IdSaIdEESaIS1_EEC2ERKS3_, @function
_ZNSt6vectorIS_IdSaIdEESaIS1_EEC2ERKS3_:
.LFB10312:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	.cfi_lsda 0x3,.LLSDA10312
	pushq	%r15
	.cfi_def_cfa_offset 16
	.cfi_offset 15, -16
	vpxor	%xmm0, %xmm0, %xmm0
	pushq	%r14
	.cfi_def_cfa_offset 24
	.cfi_offset 14, -24
	pushq	%r13
	.cfi_def_cfa_offset 32
	.cfi_offset 13, -32
	movq	%rdi, %r13
	pushq	%r12
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	pushq	%rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	movq	%rsi, %rbp
	pushq	%rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	subq	$24, %rsp
	.cfi_def_cfa_offset 80
	movq	8(%rsi), %rbx
	subq	(%rsi), %rbx
	vmovdqu	%xmm0, (%rdi)
	movq	$0, 16(%rdi)
	je	.L340
	movabsq	$9223372036854775800, %rax
	cmpq	%rbx, %rax
	jb	.L352
	movq	%rbx, %rdi
.LEHB30:
	call	_Znwm
.LEHE30:
	movq	%rax, 8(%rsp)
.L328:
	movq	8(%rsp), %r12
	vmovddup	8(%rsp), %xmm0
	vmovdqu	%xmm0, 0(%r13)
	addq	%r12, %rbx
	movq	%rbx, 16(%r13)
	movq	8(%rbp), %r14
	movq	0(%rbp), %rbp
	cmpq	%r14, %rbp
	je	.L341
	movabsq	$9223372036854775800, %r15
	jmp	.L336
	.p2align 4,,10
	.p2align 3
.L354:
	cmpq	%rbx, %r15
	jb	.L353
	movq	%rbx, %rdi
.LEHB31:
	call	_Znwm
	movq	%rax, %rcx
.L331:
	vmovq	%rcx, %xmm1
	addq	%rcx, %rbx
	vpunpcklqdq	%xmm1, %xmm1, %xmm0
	movq	%rbx, 16(%r12)
	vmovdqu	%xmm0, (%r12)
	movq	8(%rbp), %rax
	movq	0(%rbp), %rsi
	movq	%rax, %rbx
	subq	%rsi, %rbx
	cmpq	%rsi, %rax
	je	.L335
	movq	%rcx, %rdi
	movq	%rbx, %rdx
	call	memmove
	movq	%rax, %rcx
.L335:
	addq	%rbx, %rcx
	addq	$24, %rbp
	addq	$24, %r12
	movq	%rcx, -16(%r12)
	cmpq	%rbp, %r14
	je	.L330
.L336:
	movq	8(%rbp), %rbx
	vpxor	%xmm0, %xmm0, %xmm0
	subq	0(%rbp), %rbx
	movq	$0, 16(%r12)
	vmovdqu	%xmm0, (%r12)
	jne	.L354
	xorl	%ecx, %ecx
	jmp	.L331
	.p2align 4,,10
	.p2align 3
.L341:
	movq	8(%rsp), %r12
.L330:
	movq	%r12, 8(%r13)
	addq	$24, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 56
	popq	%rbx
	.cfi_def_cfa_offset 48
	popq	%rbp
	.cfi_def_cfa_offset 40
	popq	%r12
	.cfi_def_cfa_offset 32
	popq	%r13
	.cfi_def_cfa_offset 24
	popq	%r14
	.cfi_def_cfa_offset 16
	popq	%r15
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L340:
	.cfi_restore_state
	movq	$0, 8(%rsp)
	jmp	.L328
	.p2align 4,,10
	.p2align 3
.L353:
	testq	%rbx, %rbx
	jns	.L333
	call	_ZSt28__throw_bad_array_new_lengthv
	.p2align 4,,10
	.p2align 3
.L333:
	call	_ZSt17__throw_bad_allocv
.LEHE31:
.L352:
.LEHB32:
	call	_ZSt28__throw_bad_array_new_lengthv
.LEHE32:
.L344:
	movq	%rax, %rdi
.L337:
	vzeroupper
	call	__cxa_begin_catch
	movq	8(%rsp), %rdi
	movq	%r12, %rsi
	call	_ZNSt12_Destroy_auxILb0EE9__destroyIPSt6vectorIdSaIdEEEEvT_S6_
.LEHB33:
	call	__cxa_rethrow
.LEHE33:
.L343:
	movq	%rax, %rbx
.L338:
	vzeroupper
	call	__cxa_end_catch
	movq	0(%r13), %rdi
	testq	%rdi, %rdi
	je	.L339
	call	_ZdlPv
.L339:
	movq	%rbx, %rdi
.LEHB34:
	call	_Unwind_Resume
.LEHE34:
	.cfi_endproc
.LFE10312:
	.section	.gcc_except_table
	.align 4
.LLSDA10312:
	.byte	0xff
	.byte	0x3
	.uleb128 .LLSDATT10312-.LLSDATTD10312
.LLSDATTD10312:
	.byte	0x1
	.uleb128 .LLSDACSE10312-.LLSDACSB10312
.LLSDACSB10312:
	.uleb128 .LEHB30-.LFB10312
	.uleb128 .LEHE30-.LEHB30
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB31-.LFB10312
	.uleb128 .LEHE31-.LEHB31
	.uleb128 .L344-.LFB10312
	.uleb128 0x1
	.uleb128 .LEHB32-.LFB10312
	.uleb128 .LEHE32-.LEHB32
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB33-.LFB10312
	.uleb128 .LEHE33-.LEHB33
	.uleb128 .L343-.LFB10312
	.uleb128 0
	.uleb128 .LEHB34-.LFB10312
	.uleb128 .LEHE34-.LEHB34
	.uleb128 0
	.uleb128 0
.LLSDACSE10312:
	.byte	0x1
	.byte	0
	.align 4
	.long	0

.LLSDATT10312:
	.section	.text._ZNSt6vectorIS_IdSaIdEESaIS1_EEC2ERKS3_,"axG",@progbits,_ZNSt6vectorIS_IdSaIdEESaIS1_EEC5ERKS3_,comdat
	.size	_ZNSt6vectorIS_IdSaIdEESaIS1_EEC2ERKS3_, .-_ZNSt6vectorIS_IdSaIdEESaIS1_EEC2ERKS3_
	.weak	_ZNSt6vectorIS_IdSaIdEESaIS1_EEC1ERKS3_
	.set	_ZNSt6vectorIS_IdSaIdEESaIS1_EEC1ERKS3_,_ZNSt6vectorIS_IdSaIdEESaIS1_EEC2ERKS3_
	.section	.text._ZNSt6vectorIS_IS_IdSaIdEESaIS1_EESaIS3_EEC2EmRKS3_RKS4_,"axG",@progbits,_ZNSt6vectorIS_IS_IdSaIdEESaIS1_EESaIS3_EEC5EmRKS3_RKS4_,comdat
	.align 2
	.p2align 4
	.weak	_ZNSt6vectorIS_IS_IdSaIdEESaIS1_EESaIS3_EEC2EmRKS3_RKS4_
	.type	_ZNSt6vectorIS_IS_IdSaIdEESaIS1_EESaIS3_EEC2EmRKS3_RKS4_, @function
_ZNSt6vectorIS_IS_IdSaIdEESaIS1_EESaIS3_EEC2EmRKS3_RKS4_:
.LFB9836:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	.cfi_lsda 0x3,.LLSDA9836
	movabsq	$384307168202282325, %rax
	pushq	%r14
	.cfi_def_cfa_offset 16
	.cfi_offset 14, -16
	pushq	%r13
	.cfi_def_cfa_offset 24
	.cfi_offset 13, -24
	pushq	%r12
	.cfi_def_cfa_offset 32
	.cfi_offset 12, -32
	pushq	%rbp
	.cfi_def_cfa_offset 40
	.cfi_offset 6, -40
	pushq	%rbx
	.cfi_def_cfa_offset 48
	.cfi_offset 3, -48
	cmpq	%rsi, %rax
	jb	.L374
	vpxor	%xmm0, %xmm0, %xmm0
	movq	$0, 16(%rdi)
	movq	%rdi, %r13
	movq	%rsi, %rbx
	vmovdqu	%xmm0, (%rdi)
	testq	%rsi, %rsi
	je	.L375
	leaq	(%rsi,%rsi,2), %rbp
	movq	%rdx, %r12
	salq	$3, %rbp
	movq	%rbp, %rdi
.LEHB35:
	call	_Znwm
.LEHE35:
	vmovq	%rax, %xmm1
	addq	%rax, %rbp
	movq	%rax, %r14
	vpunpcklqdq	%xmm1, %xmm1, %xmm0
	movq	%rbp, 16(%r13)
	movq	%rax, %rbp
	vmovdqu	%xmm0, 0(%r13)
	.p2align 4,,10
	.p2align 3
.L359:
	movq	%r12, %rsi
	movq	%rbp, %rdi
.LEHB36:
	call	_ZNSt6vectorIS_IdSaIdEESaIS1_EEC1ERKS3_
.LEHE36:
	addq	$24, %rbp
	subq	$1, %rbx
	jne	.L359
	movq	%rbp, 8(%r13)
	popq	%rbx
	.cfi_remember_state
	.cfi_def_cfa_offset 40
	popq	%rbp
	.cfi_def_cfa_offset 32
	popq	%r12
	.cfi_def_cfa_offset 24
	popq	%r13
	.cfi_def_cfa_offset 16
	popq	%r14
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L375:
	.cfi_restore_state
	xorl	%ebp, %ebp
	movq	$0, (%rdi)
	movq	$0, 16(%rdi)
	movq	%rbp, 8(%r13)
	popq	%rbx
	.cfi_remember_state
	.cfi_def_cfa_offset 40
	popq	%rbp
	.cfi_def_cfa_offset 32
	popq	%r12
	.cfi_def_cfa_offset 24
	popq	%r13
	.cfi_def_cfa_offset 16
	popq	%r14
	.cfi_def_cfa_offset 8
	ret
.L374:
	.cfi_restore_state
	movl	$.LC5, %edi
.LEHB37:
	call	_ZSt20__throw_length_errorPKc
.LEHE37:
.L366:
	movq	%rax, %rdi
.L360:
	vzeroupper
	call	__cxa_begin_catch
.L361:
	cmpq	%rbp, %r14
	je	.L376
	movq	%r14, %rdi
	addq	$24, %r14
	call	_ZNSt6vectorIS_IdSaIdEESaIS1_EED1Ev
	jmp	.L361
.L376:
.LEHB38:
	call	__cxa_rethrow
.LEHE38:
.L365:
	movq	%rax, %rbx
.L363:
	vzeroupper
	call	__cxa_end_catch
	movq	0(%r13), %rdi
	testq	%rdi, %rdi
	je	.L364
	call	_ZdlPv
.L364:
	movq	%rbx, %rdi
.LEHB39:
	call	_Unwind_Resume
.LEHE39:
	.cfi_endproc
.LFE9836:
	.section	.gcc_except_table
	.align 4
.LLSDA9836:
	.byte	0xff
	.byte	0x3
	.uleb128 .LLSDATT9836-.LLSDATTD9836
.LLSDATTD9836:
	.byte	0x1
	.uleb128 .LLSDACSE9836-.LLSDACSB9836
.LLSDACSB9836:
	.uleb128 .LEHB35-.LFB9836
	.uleb128 .LEHE35-.LEHB35
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB36-.LFB9836
	.uleb128 .LEHE36-.LEHB36
	.uleb128 .L366-.LFB9836
	.uleb128 0x1
	.uleb128 .LEHB37-.LFB9836
	.uleb128 .LEHE37-.LEHB37
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB38-.LFB9836
	.uleb128 .LEHE38-.LEHB38
	.uleb128 .L365-.LFB9836
	.uleb128 0
	.uleb128 .LEHB39-.LFB9836
	.uleb128 .LEHE39-.LEHB39
	.uleb128 0
	.uleb128 0
.LLSDACSE9836:
	.byte	0x1
	.byte	0
	.align 4
	.long	0

.LLSDATT9836:
	.section	.text._ZNSt6vectorIS_IS_IdSaIdEESaIS1_EESaIS3_EEC2EmRKS3_RKS4_,"axG",@progbits,_ZNSt6vectorIS_IS_IdSaIdEESaIS1_EESaIS3_EEC5EmRKS3_RKS4_,comdat
	.size	_ZNSt6vectorIS_IS_IdSaIdEESaIS1_EESaIS3_EEC2EmRKS3_RKS4_, .-_ZNSt6vectorIS_IS_IdSaIdEESaIS1_EESaIS3_EEC2EmRKS3_RKS4_
	.weak	_ZNSt6vectorIS_IS_IdSaIdEESaIS1_EESaIS3_EEC1EmRKS3_RKS4_
	.set	_ZNSt6vectorIS_IS_IdSaIdEESaIS1_EESaIS3_EEC1EmRKS3_RKS4_,_ZNSt6vectorIS_IS_IdSaIdEESaIS1_EESaIS3_EEC2EmRKS3_RKS4_
	.section	.text.unlikely
.LCOLDB21:
	.text
.LHOTB21:
	.p2align 4
	.globl	_Z9calculateRSt6vectorIS_IS_IS_IdSaIdEESaIS1_EESaIS3_EESaIS5_EES8_
	.type	_Z9calculateRSt6vectorIS_IS_IS_IdSaIdEESaIS1_EESaIS3_EESaIS5_EES8_, @function
_Z9calculateRSt6vectorIS_IS_IS_IdSaIdEESaIS1_EESaIS3_EESaIS5_EES8_:
.LFB9541:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	.cfi_lsda 0x3,.LLSDA9541
	pushq	%r15
	.cfi_def_cfa_offset 16
	.cfi_offset 15, -16
	movq	%rdi, %r15
	movl	$80, %edi
	pushq	%r14
	.cfi_def_cfa_offset 24
	.cfi_offset 14, -24
	pushq	%r13
	.cfi_def_cfa_offset 32
	.cfi_offset 13, -32
	pushq	%r12
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	pushq	%rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	pushq	%rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	subq	$152, %rsp
	.cfi_def_cfa_offset 208
	movq	%rdx, 24(%rsp)
	movq	%rsi, 16(%rsp)
.LEHB40:
	call	_Znwm
.LEHE40:
	vpxor	%xmm0, %xmm0, %xmm0
	movl	$240, %edi
	leaq	80(%rax), %rdx
	movq	$0x000000000, (%rax)
	movq	%rax, %r12
	movq	%rax, 48(%rsp)
	leaq	8(%rax), %rax
	vmovdqu	%xmm0, 8(%r12)
	movq	%rdx, 64(%rsp)
	movq	$0, 64(%rax)
	vmovdqu	%xmm0, 16(%rax)
	vmovdqu	%xmm0, 32(%rax)
	vmovdqu	%xmm0, 48(%rax)
	vpxor	%xmm0, %xmm0, %xmm0
	movq	%rdx, 56(%rsp)
	vmovdqu	%xmm0, 88(%rsp)
.LEHB41:
	call	_Znwm
.LEHE41:
	movq	%rax, %r13
	movq	%rax, 80(%rsp)
	leaq	48(%rsp), %rdx
	leaq	240(%rax), %rax
	movl	$10, %esi
	movq	%r13, %rdi
	movq	%rax, 96(%rsp)
.LEHB42:
	call	_ZSt18__do_uninit_fill_nIPSt6vectorIdSaIdEEmS2_ET_S4_T0_RKT1_
.LEHE42:
	vpxor	%xmm0, %xmm0, %xmm0
	movl	$2400, %edi
	movq	%rax, 32(%rsp)
	movq	%rax, 88(%rsp)
	vmovdqu	%xmm0, 120(%rsp)
.LEHB43:
	call	_Znwm
.LEHE43:
	leaq	2400(%rax), %r14
	movq	%rax, 112(%rsp)
	movq	%rax, %rbx
	movq	%rax, %rbp
	leaq	80(%rsp), %rax
	movq	%r14, 128(%rsp)
	movq	%rax, (%rsp)
.L381:
	movq	(%rsp), %rsi
	movq	%rbp, %rdi
.LEHB44:
	call	_ZNSt6vectorIS_IdSaIdEESaIS1_EEC1ERKS3_
.LEHE44:
	addq	$24, %rbp
	cmpq	%rbp, %r14
	jne	.L381
	vpxor	%xmm0, %xmm0, %xmm0
	movl	$2400, %edi
	movq	%rbp, 120(%rsp)
	movq	$0, 16(%r15)
	vmovdqu	%xmm0, (%r15)
.LEHB45:
	call	_Znwm
.LEHE45:
	vmovq	%rax, %xmm1
	movq	%rax, %rdi
	leaq	2400(%rax), %rax
	movl	$100, %esi
	movq	%rax, 16(%r15)
	vpunpcklqdq	%xmm1, %xmm1, %xmm0
	leaq	112(%rsp), %rax
	vmovdqu	%xmm0, (%r15)
	movq	%rax, %rdx
	movq	%rax, 8(%rsp)
.LEHB46:
	call	_ZSt18__do_uninit_fill_nIPSt6vectorIS0_IS0_IdSaIdEESaIS2_EESaIS4_EEmS6_ET_S8_T0_RKT1_
.LEHE46:
	movq	%rax, 8(%r15)
	movq	%rbx, %r14
	cmpq	%rbp, %rbx
	je	.L398
.L388:
	movq	8(%r14), %rcx
	movq	(%r14), %rax
	cmpq	%rax, %rcx
	je	.L394
.L396:
	movq	(%rax), %rdi
	testq	%rdi, %rdi
	je	.L395
	movq	%rax, 40(%rsp)
	movq	%rcx, (%rsp)
	call	_ZdlPv
	movq	40(%rsp), %rax
	movq	(%rsp), %rcx
.L395:
	addq	$24, %rax
	cmpq	%rax, %rcx
	jne	.L396
	movq	(%r14), %rax
.L394:
	testq	%rax, %rax
	je	.L397
	movq	%rax, %rdi
	call	_ZdlPv
.L397:
	addq	$24, %r14
	cmpq	%r14, %rbp
	jne	.L388
.L398:
	movq	%rbx, %rdi
	movq	%r13, %rbx
	call	_ZdlPv
	cmpq	%r13, 32(%rsp)
	je	.L390
.L389:
	movq	(%rbx), %rdi
	testq	%rdi, %rdi
	je	.L400
	call	_ZdlPv
.L400:
	addq	$24, %rbx
	cmpq	%rbx, 32(%rsp)
	jne	.L389
.L390:
	movq	%r13, %rdi
	call	_ZdlPv
	movq	%r12, %rdi
	call	_ZdlPv
	movq	$0, (%rsp)
.L399:
	xorl	%r14d, %r14d
.L409:
	xorl	%ebp, %ebp
	.p2align 4,,10
	.p2align 3
.L406:
	movq	24(%rsp), %rax
	movq	(%rsp), %rbx
	movq	8(%rsp), %r12
	movq	(%rax), %rax
	movq	%r12, %rdi
	movq	(%rax,%rbp), %rdx
	movq	16(%rsp), %rax
	movq	(%rax), %rax
	addq	%r14, %rdx
	movq	(%rax,%rbx), %rsi
	addq	%rbp, %rsi
.LEHB47:
	call	_Z17multiply_matricesRSt6vectorIS_IdSaIdEESaIS1_EES4_
.LEHE47:
	movq	(%r15), %rax
	movq	%r12, %rsi
	movq	(%rax,%rbx), %rcx
	addq	%r14, %rcx
	movq	%rcx, %rdi
	call	_Z18sum_small_matricesRSt6vectorIS_IdSaIdEESaIS1_EERKS3_
	movq	112(%rsp), %r12
	movq	120(%rsp), %rbx
	movq	%r12, %r13
	cmpq	%r12, %rbx
	je	.L405
	.p2align 4,,10
	.p2align 3
.L401:
	movq	0(%r13), %rdi
	testq	%rdi, %rdi
	je	.L404
	call	_ZdlPv
.L404:
	addq	$24, %r13
	cmpq	%r13, %rbx
	jne	.L401
.L405:
	testq	%r12, %r12
	je	.L403
	movq	%r12, %rdi
	call	_ZdlPv
.L403:
	addq	$24, %rbp
	cmpq	$2400, %rbp
	jne	.L406
	addq	$24, %r14
	cmpq	$2400, %r14
	jne	.L409
	addq	$24, (%rsp)
	movq	(%rsp), %rax
	cmpq	$2400, %rax
	jne	.L399
	addq	$152, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 56
	movq	%r15, %rax
	popq	%rbx
	.cfi_def_cfa_offset 48
	popq	%rbp
	.cfi_def_cfa_offset 40
	popq	%r12
	.cfi_def_cfa_offset 32
	popq	%r13
	.cfi_def_cfa_offset 24
	popq	%r14
	.cfi_def_cfa_offset 16
	popq	%r15
	.cfi_def_cfa_offset 8
	ret
.L414:
	.cfi_restore_state
	movq	%rax, %rbx
	vzeroupper
	jmp	.L380
.L417:
	movq	%rax, %rbx
	jmp	.L410
.L421:
	movq	%rax, %rbx
	jmp	.L391
.L416:
	movq	%rax, %rbx
	leaq	112(%rsp), %rax
	movq	%rax, 8(%rsp)
	vzeroupper
	jmp	.L393
.L420:
	movq	%rax, %rdi
	jmp	.L383
.L415:
	movq	%rax, %rbx
	leaq	80(%rsp), %rax
	movq	%rax, (%rsp)
	vzeroupper
	jmp	.L387
.L418:
	movq	%rax, %rbx
	jmp	.L379
	.section	.gcc_except_table
	.align 4
.LLSDA9541:
	.byte	0xff
	.byte	0x3
	.uleb128 .LLSDATT9541-.LLSDATTD9541
.LLSDATTD9541:
	.byte	0x1
	.uleb128 .LLSDACSE9541-.LLSDACSB9541
.LLSDACSB9541:
	.uleb128 .LEHB40-.LFB9541
	.uleb128 .LEHE40-.LEHB40
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB41-.LFB9541
	.uleb128 .LEHE41-.LEHB41
	.uleb128 .L414-.LFB9541
	.uleb128 0
	.uleb128 .LEHB42-.LFB9541
	.uleb128 .LEHE42-.LEHB42
	.uleb128 .L418-.LFB9541
	.uleb128 0
	.uleb128 .LEHB43-.LFB9541
	.uleb128 .LEHE43-.LEHB43
	.uleb128 .L415-.LFB9541
	.uleb128 0
	.uleb128 .LEHB44-.LFB9541
	.uleb128 .LEHE44-.LEHB44
	.uleb128 .L420-.LFB9541
	.uleb128 0x1
	.uleb128 .LEHB45-.LFB9541
	.uleb128 .LEHE45-.LEHB45
	.uleb128 .L416-.LFB9541
	.uleb128 0
	.uleb128 .LEHB46-.LFB9541
	.uleb128 .LEHE46-.LEHB46
	.uleb128 .L421-.LFB9541
	.uleb128 0
	.uleb128 .LEHB47-.LFB9541
	.uleb128 .LEHE47-.LEHB47
	.uleb128 .L417-.LFB9541
	.uleb128 0
.LLSDACSE9541:
	.byte	0x1
	.byte	0
	.align 4
	.long	0

.LLSDATT9541:
	.text
	.cfi_endproc
	.section	.text.unlikely
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	.cfi_lsda 0x3,.LLSDAC9541
	.type	_Z9calculateRSt6vectorIS_IS_IS_IdSaIdEESaIS1_EESaIS3_EESaIS5_EES8_.cold, @function
_Z9calculateRSt6vectorIS_IS_IS_IdSaIdEESaIS1_EESaIS3_EESaIS5_EES8_.cold:
.LFSB9541:
.L391:
	.cfi_def_cfa_offset 208
	.cfi_offset 3, -56
	.cfi_offset 6, -48
	.cfi_offset 12, -40
	.cfi_offset 13, -32
	.cfi_offset 14, -24
	.cfi_offset 15, -16
	movq	(%r15), %rdi
	testq	%rdi, %rdi
	je	.L447
	vzeroupper
	call	_ZdlPv
.L393:
	movq	8(%rsp), %rdi
	call	_ZNSt6vectorIS_IS_IdSaIdEESaIS1_EESaIS3_EED1Ev
.L387:
	movq	(%rsp), %rdi
	call	_ZNSt6vectorIS_IdSaIdEESaIS1_EED1Ev
.L380:
	movq	%r12, %rdi
	call	_ZdlPv
	movq	%rbx, %rdi
.LEHB48:
	call	_Unwind_Resume
.L410:
	movq	%r15, %rdi
	vzeroupper
	call	_ZNSt6vectorIS_IS_IS_IdSaIdEESaIS1_EESaIS3_EESaIS5_EED1Ev
	movq	%rbx, %rdi
	call	_Unwind_Resume
.LEHE48:
.L383:
	vzeroupper
	call	__cxa_begin_catch
	movq	%rbx, %r13
.L384:
	cmpq	%rbp, %r13
	je	.L449
	movq	%r13, %rdi
	addq	$24, %r13
	call	_ZNSt6vectorIS_IdSaIdEESaIS1_EED1Ev
	jmp	.L384
.L447:
	vzeroupper
	jmp	.L393
.L379:
	movq	%r13, %rdi
	vzeroupper
	call	_ZdlPv
	jmp	.L380
.L449:
.LEHB49:
	call	__cxa_rethrow
.LEHE49:
.L419:
	movq	%rax, %rbp
	vzeroupper
	call	__cxa_end_catch
	movq	%rbx, %rdi
	movq	%rbp, %rbx
	call	_ZdlPv
	jmp	.L387
	.cfi_endproc
.LFE9541:
	.section	.gcc_except_table
	.align 4
.LLSDAC9541:
	.byte	0xff
	.byte	0x3
	.uleb128 .LLSDATTC9541-.LLSDATTDC9541
.LLSDATTDC9541:
	.byte	0x1
	.uleb128 .LLSDACSEC9541-.LLSDACSBC9541
.LLSDACSBC9541:
	.uleb128 .LEHB48-.LCOLDB21
	.uleb128 .LEHE48-.LEHB48
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB49-.LCOLDB21
	.uleb128 .LEHE49-.LEHB49
	.uleb128 .L419-.LCOLDB21
	.uleb128 0
.LLSDACSEC9541:
	.byte	0x1
	.byte	0
	.align 4
	.long	0

.LLSDATTC9541:
	.section	.text.unlikely
	.text
	.size	_Z9calculateRSt6vectorIS_IS_IS_IdSaIdEESaIS1_EESaIS3_EESaIS5_EES8_, .-_Z9calculateRSt6vectorIS_IS_IS_IdSaIdEESaIS1_EESaIS3_EESaIS5_EES8_
	.section	.text.unlikely
	.size	_Z9calculateRSt6vectorIS_IS_IS_IdSaIdEESaIS1_EESaIS3_EESaIS5_EES8_.cold, .-_Z9calculateRSt6vectorIS_IS_IS_IdSaIdEESaIS1_EESaIS3_EESaIS5_EES8_.cold
.LCOLDE21:
	.text
.LHOTE21:
	.section	.text.unlikely
.LCOLDB22:
	.text
.LHOTB22:
	.p2align 4
	.globl	_Z13calculate_avxRSt6vectorIS_IS_IS_IdSaIdEESaIS1_EESaIS3_EESaIS5_EES8_
	.type	_Z13calculate_avxRSt6vectorIS_IS_IS_IdSaIdEESaIS1_EESaIS3_EESaIS5_EES8_, @function
_Z13calculate_avxRSt6vectorIS_IS_IS_IdSaIdEESaIS1_EESaIS3_EESaIS5_EES8_:
.LFB9530:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	.cfi_lsda 0x3,.LLSDA9530
	pushq	%r15
	.cfi_def_cfa_offset 16
	.cfi_offset 15, -16
	movq	%rdi, %r15
	movl	$80, %edi
	pushq	%r14
	.cfi_def_cfa_offset 24
	.cfi_offset 14, -24
	pushq	%r13
	.cfi_def_cfa_offset 32
	.cfi_offset 13, -32
	pushq	%r12
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	pushq	%rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	pushq	%rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	subq	$152, %rsp
	.cfi_def_cfa_offset 208
	movq	%rdx, 24(%rsp)
	movq	%rsi, 16(%rsp)
.LEHB50:
	call	_Znwm
.LEHE50:
	vpxor	%xmm0, %xmm0, %xmm0
	movl	$240, %edi
	leaq	80(%rax), %rdx
	movq	$0x000000000, (%rax)
	movq	%rax, %r12
	movq	%rax, 48(%rsp)
	leaq	8(%rax), %rax
	vmovdqu	%xmm0, 8(%r12)
	movq	%rdx, 64(%rsp)
	movq	$0, 64(%rax)
	vmovdqu	%xmm0, 16(%rax)
	vmovdqu	%xmm0, 32(%rax)
	vmovdqu	%xmm0, 48(%rax)
	vpxor	%xmm0, %xmm0, %xmm0
	movq	%rdx, 56(%rsp)
	vmovdqu	%xmm0, 88(%rsp)
.LEHB51:
	call	_Znwm
.LEHE51:
	movq	%rax, %r13
	movq	%rax, 80(%rsp)
	leaq	48(%rsp), %rdx
	leaq	240(%rax), %rax
	movl	$10, %esi
	movq	%r13, %rdi
	movq	%rax, 96(%rsp)
.LEHB52:
	call	_ZSt18__do_uninit_fill_nIPSt6vectorIdSaIdEEmS2_ET_S4_T0_RKT1_
.LEHE52:
	vpxor	%xmm0, %xmm0, %xmm0
	movl	$2400, %edi
	movq	%rax, 32(%rsp)
	movq	%rax, 88(%rsp)
	vmovdqu	%xmm0, 120(%rsp)
.LEHB53:
	call	_Znwm
.LEHE53:
	leaq	2400(%rax), %r14
	movq	%rax, 112(%rsp)
	movq	%rax, %rbx
	movq	%rax, %rbp
	leaq	80(%rsp), %rax
	movq	%r14, 128(%rsp)
	movq	%rax, (%rsp)
.L454:
	movq	(%rsp), %rsi
	movq	%rbp, %rdi
.LEHB54:
	call	_ZNSt6vectorIS_IdSaIdEESaIS1_EEC1ERKS3_
.LEHE54:
	addq	$24, %rbp
	cmpq	%rbp, %r14
	jne	.L454
	vpxor	%xmm0, %xmm0, %xmm0
	movl	$2400, %edi
	movq	%rbp, 120(%rsp)
	movq	$0, 16(%r15)
	vmovdqu	%xmm0, (%r15)
.LEHB55:
	call	_Znwm
.LEHE55:
	vmovq	%rax, %xmm1
	movq	%rax, %rdi
	leaq	2400(%rax), %rax
	movl	$100, %esi
	movq	%rax, 16(%r15)
	vpunpcklqdq	%xmm1, %xmm1, %xmm0
	leaq	112(%rsp), %rax
	vmovdqu	%xmm0, (%r15)
	movq	%rax, %rdx
	movq	%rax, 8(%rsp)
.LEHB56:
	call	_ZSt18__do_uninit_fill_nIPSt6vectorIS0_IS0_IdSaIdEESaIS2_EESaIS4_EEmS6_ET_S8_T0_RKT1_
.LEHE56:
	movq	%rax, 8(%r15)
	movq	%rbx, %r14
	cmpq	%rbp, %rbx
	je	.L471
.L461:
	movq	8(%r14), %rcx
	movq	(%r14), %rax
	cmpq	%rax, %rcx
	je	.L467
.L469:
	movq	(%rax), %rdi
	testq	%rdi, %rdi
	je	.L468
	movq	%rax, 40(%rsp)
	movq	%rcx, (%rsp)
	call	_ZdlPv
	movq	40(%rsp), %rax
	movq	(%rsp), %rcx
.L468:
	addq	$24, %rax
	cmpq	%rax, %rcx
	jne	.L469
	movq	(%r14), %rax
.L467:
	testq	%rax, %rax
	je	.L470
	movq	%rax, %rdi
	call	_ZdlPv
.L470:
	addq	$24, %r14
	cmpq	%r14, %rbp
	jne	.L461
.L471:
	movq	%rbx, %rdi
	movq	%r13, %rbx
	call	_ZdlPv
	cmpq	%r13, 32(%rsp)
	je	.L463
.L462:
	movq	(%rbx), %rdi
	testq	%rdi, %rdi
	je	.L473
	call	_ZdlPv
.L473:
	addq	$24, %rbx
	cmpq	%rbx, 32(%rsp)
	jne	.L462
.L463:
	movq	%r13, %rdi
	call	_ZdlPv
	movq	%r12, %rdi
	call	_ZdlPv
	movq	$0, (%rsp)
.L472:
	xorl	%r14d, %r14d
.L482:
	xorl	%ebp, %ebp
	.p2align 4,,10
	.p2align 3
.L479:
	movq	24(%rsp), %rax
	movq	(%rsp), %rbx
	movq	8(%rsp), %r12
	movq	(%rax), %rax
	movq	%r12, %rdi
	movq	(%rax,%rbp), %rdx
	movq	16(%rsp), %rax
	movq	(%rax), %rax
	addq	%r14, %rdx
	movq	(%rax,%rbx), %rsi
	addq	%rbp, %rsi
.LEHB57:
	call	_Z21multiply_matrices_avxRSt6vectorIS_IdSaIdEESaIS1_EES4_
.LEHE57:
	movq	(%r15), %rax
	movq	%r12, %rsi
	movq	(%rax,%rbx), %rcx
	addq	%r14, %rcx
	movq	%rcx, %rdi
	call	_Z18sum_small_matricesRSt6vectorIS_IdSaIdEESaIS1_EERKS3_
	movq	112(%rsp), %r12
	movq	120(%rsp), %rbx
	movq	%r12, %r13
	cmpq	%r12, %rbx
	je	.L478
	.p2align 4,,10
	.p2align 3
.L474:
	movq	0(%r13), %rdi
	testq	%rdi, %rdi
	je	.L477
	call	_ZdlPv
.L477:
	addq	$24, %r13
	cmpq	%r13, %rbx
	jne	.L474
.L478:
	testq	%r12, %r12
	je	.L476
	movq	%r12, %rdi
	call	_ZdlPv
.L476:
	addq	$24, %rbp
	cmpq	$2400, %rbp
	jne	.L479
	addq	$24, %r14
	cmpq	$2400, %r14
	jne	.L482
	addq	$24, (%rsp)
	movq	(%rsp), %rax
	cmpq	$2400, %rax
	jne	.L472
	addq	$152, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 56
	movq	%r15, %rax
	popq	%rbx
	.cfi_def_cfa_offset 48
	popq	%rbp
	.cfi_def_cfa_offset 40
	popq	%r12
	.cfi_def_cfa_offset 32
	popq	%r13
	.cfi_def_cfa_offset 24
	popq	%r14
	.cfi_def_cfa_offset 16
	popq	%r15
	.cfi_def_cfa_offset 8
	ret
.L487:
	.cfi_restore_state
	movq	%rax, %rbx
	vzeroupper
	jmp	.L453
.L490:
	movq	%rax, %rbx
	jmp	.L483
.L494:
	movq	%rax, %rbx
	jmp	.L464
.L489:
	movq	%rax, %rbx
	leaq	112(%rsp), %rax
	movq	%rax, 8(%rsp)
	vzeroupper
	jmp	.L466
.L493:
	movq	%rax, %rdi
	jmp	.L456
.L488:
	movq	%rax, %rbx
	leaq	80(%rsp), %rax
	movq	%rax, (%rsp)
	vzeroupper
	jmp	.L460
.L491:
	movq	%rax, %rbx
	jmp	.L452
	.section	.gcc_except_table
	.align 4
.LLSDA9530:
	.byte	0xff
	.byte	0x3
	.uleb128 .LLSDATT9530-.LLSDATTD9530
.LLSDATTD9530:
	.byte	0x1
	.uleb128 .LLSDACSE9530-.LLSDACSB9530
.LLSDACSB9530:
	.uleb128 .LEHB50-.LFB9530
	.uleb128 .LEHE50-.LEHB50
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB51-.LFB9530
	.uleb128 .LEHE51-.LEHB51
	.uleb128 .L487-.LFB9530
	.uleb128 0
	.uleb128 .LEHB52-.LFB9530
	.uleb128 .LEHE52-.LEHB52
	.uleb128 .L491-.LFB9530
	.uleb128 0
	.uleb128 .LEHB53-.LFB9530
	.uleb128 .LEHE53-.LEHB53
	.uleb128 .L488-.LFB9530
	.uleb128 0
	.uleb128 .LEHB54-.LFB9530
	.uleb128 .LEHE54-.LEHB54
	.uleb128 .L493-.LFB9530
	.uleb128 0x1
	.uleb128 .LEHB55-.LFB9530
	.uleb128 .LEHE55-.LEHB55
	.uleb128 .L489-.LFB9530
	.uleb128 0
	.uleb128 .LEHB56-.LFB9530
	.uleb128 .LEHE56-.LEHB56
	.uleb128 .L494-.LFB9530
	.uleb128 0
	.uleb128 .LEHB57-.LFB9530
	.uleb128 .LEHE57-.LEHB57
	.uleb128 .L490-.LFB9530
	.uleb128 0
.LLSDACSE9530:
	.byte	0x1
	.byte	0
	.align 4
	.long	0

.LLSDATT9530:
	.text
	.cfi_endproc
	.section	.text.unlikely
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	.cfi_lsda 0x3,.LLSDAC9530
	.type	_Z13calculate_avxRSt6vectorIS_IS_IS_IdSaIdEESaIS1_EESaIS3_EESaIS5_EES8_.cold, @function
_Z13calculate_avxRSt6vectorIS_IS_IS_IdSaIdEESaIS1_EESaIS3_EESaIS5_EES8_.cold:
.LFSB9530:
.L464:
	.cfi_def_cfa_offset 208
	.cfi_offset 3, -56
	.cfi_offset 6, -48
	.cfi_offset 12, -40
	.cfi_offset 13, -32
	.cfi_offset 14, -24
	.cfi_offset 15, -16
	movq	(%r15), %rdi
	testq	%rdi, %rdi
	je	.L520
	vzeroupper
	call	_ZdlPv
.L466:
	movq	8(%rsp), %rdi
	call	_ZNSt6vectorIS_IS_IdSaIdEESaIS1_EESaIS3_EED1Ev
.L460:
	movq	(%rsp), %rdi
	call	_ZNSt6vectorIS_IdSaIdEESaIS1_EED1Ev
.L453:
	movq	%r12, %rdi
	call	_ZdlPv
	movq	%rbx, %rdi
.LEHB58:
	call	_Unwind_Resume
.L483:
	movq	%r15, %rdi
	vzeroupper
	call	_ZNSt6vectorIS_IS_IS_IdSaIdEESaIS1_EESaIS3_EESaIS5_EED1Ev
	movq	%rbx, %rdi
	call	_Unwind_Resume
.LEHE58:
.L456:
	vzeroupper
	call	__cxa_begin_catch
	movq	%rbx, %r13
.L457:
	cmpq	%rbp, %r13
	je	.L522
	movq	%r13, %rdi
	addq	$24, %r13
	call	_ZNSt6vectorIS_IdSaIdEESaIS1_EED1Ev
	jmp	.L457
.L520:
	vzeroupper
	jmp	.L466
.L452:
	movq	%r13, %rdi
	vzeroupper
	call	_ZdlPv
	jmp	.L453
.L522:
.LEHB59:
	call	__cxa_rethrow
.LEHE59:
.L492:
	movq	%rax, %rbp
	vzeroupper
	call	__cxa_end_catch
	movq	%rbx, %rdi
	movq	%rbp, %rbx
	call	_ZdlPv
	jmp	.L460
	.cfi_endproc
.LFE9530:
	.section	.gcc_except_table
	.align 4
.LLSDAC9530:
	.byte	0xff
	.byte	0x3
	.uleb128 .LLSDATTC9530-.LLSDATTDC9530
.LLSDATTDC9530:
	.byte	0x1
	.uleb128 .LLSDACSEC9530-.LLSDACSBC9530
.LLSDACSBC9530:
	.uleb128 .LEHB58-.LCOLDB22
	.uleb128 .LEHE58-.LEHB58
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB59-.LCOLDB22
	.uleb128 .LEHE59-.LEHB59
	.uleb128 .L492-.LCOLDB22
	.uleb128 0
.LLSDACSEC9530:
	.byte	0x1
	.byte	0
	.align 4
	.long	0

.LLSDATTC9530:
	.section	.text.unlikely
	.text
	.size	_Z13calculate_avxRSt6vectorIS_IS_IS_IdSaIdEESaIS1_EESaIS3_EESaIS5_EES8_, .-_Z13calculate_avxRSt6vectorIS_IS_IS_IdSaIdEESaIS1_EESaIS3_EESaIS5_EES8_
	.section	.text.unlikely
	.size	_Z13calculate_avxRSt6vectorIS_IS_IS_IdSaIdEESaIS1_EESaIS3_EESaIS5_EES8_.cold, .-_Z13calculate_avxRSt6vectorIS_IS_IS_IdSaIdEESaIS1_EESaIS3_EESaIS5_EES8_.cold
.LCOLDE22:
	.text
.LHOTE22:
	.section	.text.unlikely
.LCOLDB23:
	.text
.LHOTB23:
	.p2align 4
	.globl	_Z18calculate_manuallyRSt6vectorIS_IS_IS_IdSaIdEESaIS1_EESaIS3_EESaIS5_EES8_
	.type	_Z18calculate_manuallyRSt6vectorIS_IS_IS_IdSaIdEESaIS1_EESaIS3_EESaIS5_EES8_, @function
_Z18calculate_manuallyRSt6vectorIS_IS_IS_IdSaIdEESaIS1_EESaIS3_EESaIS5_EES8_:
.LFB9543:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	.cfi_lsda 0x3,.LLSDA9543
	pushq	%r15
	.cfi_def_cfa_offset 16
	.cfi_offset 15, -16
	movq	%rdi, %r15
	movl	$80, %edi
	pushq	%r14
	.cfi_def_cfa_offset 24
	.cfi_offset 14, -24
	pushq	%r13
	.cfi_def_cfa_offset 32
	.cfi_offset 13, -32
	pushq	%r12
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	pushq	%rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	pushq	%rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	subq	$152, %rsp
	.cfi_def_cfa_offset 208
	movq	%rdx, 24(%rsp)
	movq	%rsi, 16(%rsp)
.LEHB60:
	call	_Znwm
.LEHE60:
	vpxor	%xmm0, %xmm0, %xmm0
	movl	$240, %edi
	leaq	80(%rax), %rdx
	movq	$0x000000000, (%rax)
	movq	%rax, %r12
	movq	%rax, 48(%rsp)
	leaq	8(%rax), %rax
	vmovdqu	%xmm0, 8(%r12)
	movq	%rdx, 64(%rsp)
	movq	$0, 64(%rax)
	vmovdqu	%xmm0, 16(%rax)
	vmovdqu	%xmm0, 32(%rax)
	vmovdqu	%xmm0, 48(%rax)
	vpxor	%xmm0, %xmm0, %xmm0
	movq	%rdx, 56(%rsp)
	vmovdqu	%xmm0, 88(%rsp)
.LEHB61:
	call	_Znwm
.LEHE61:
	movq	%rax, %r13
	movq	%rax, 80(%rsp)
	leaq	48(%rsp), %rdx
	leaq	240(%rax), %rax
	movl	$10, %esi
	movq	%r13, %rdi
	movq	%rax, 96(%rsp)
.LEHB62:
	call	_ZSt18__do_uninit_fill_nIPSt6vectorIdSaIdEEmS2_ET_S4_T0_RKT1_
.LEHE62:
	vpxor	%xmm0, %xmm0, %xmm0
	movl	$2400, %edi
	movq	%rax, 32(%rsp)
	movq	%rax, 88(%rsp)
	vmovdqu	%xmm0, 120(%rsp)
.LEHB63:
	call	_Znwm
.LEHE63:
	leaq	2400(%rax), %r14
	movq	%rax, 112(%rsp)
	movq	%rax, %rbx
	movq	%rax, %rbp
	leaq	80(%rsp), %rax
	movq	%r14, 128(%rsp)
	movq	%rax, (%rsp)
.L527:
	movq	(%rsp), %rsi
	movq	%rbp, %rdi
.LEHB64:
	call	_ZNSt6vectorIS_IdSaIdEESaIS1_EEC1ERKS3_
.LEHE64:
	addq	$24, %rbp
	cmpq	%rbp, %r14
	jne	.L527
	vpxor	%xmm0, %xmm0, %xmm0
	movl	$2400, %edi
	movq	%rbp, 120(%rsp)
	movq	$0, 16(%r15)
	vmovdqu	%xmm0, (%r15)
.LEHB65:
	call	_Znwm
.LEHE65:
	vmovq	%rax, %xmm1
	movq	%rax, %rdi
	leaq	2400(%rax), %rax
	movl	$100, %esi
	movq	%rax, 16(%r15)
	vpunpcklqdq	%xmm1, %xmm1, %xmm0
	leaq	112(%rsp), %rax
	vmovdqu	%xmm0, (%r15)
	movq	%rax, %rdx
	movq	%rax, 8(%rsp)
.LEHB66:
	call	_ZSt18__do_uninit_fill_nIPSt6vectorIS0_IS0_IdSaIdEESaIS2_EESaIS4_EEmS6_ET_S8_T0_RKT1_
.LEHE66:
	movq	%rax, 8(%r15)
	movq	%rbx, %r14
	cmpq	%rbp, %rbx
	je	.L544
.L534:
	movq	8(%r14), %rcx
	movq	(%r14), %rax
	cmpq	%rax, %rcx
	je	.L540
.L542:
	movq	(%rax), %rdi
	testq	%rdi, %rdi
	je	.L541
	movq	%rax, 40(%rsp)
	movq	%rcx, (%rsp)
	call	_ZdlPv
	movq	40(%rsp), %rax
	movq	(%rsp), %rcx
.L541:
	addq	$24, %rax
	cmpq	%rax, %rcx
	jne	.L542
	movq	(%r14), %rax
.L540:
	testq	%rax, %rax
	je	.L543
	movq	%rax, %rdi
	call	_ZdlPv
.L543:
	addq	$24, %r14
	cmpq	%r14, %rbp
	jne	.L534
.L544:
	movq	%rbx, %rdi
	movq	%r13, %rbx
	call	_ZdlPv
	cmpq	%r13, 32(%rsp)
	je	.L536
.L535:
	movq	(%rbx), %rdi
	testq	%rdi, %rdi
	je	.L546
	call	_ZdlPv
.L546:
	addq	$24, %rbx
	cmpq	%rbx, 32(%rsp)
	jne	.L535
.L536:
	movq	%r13, %rdi
	call	_ZdlPv
	movq	%r12, %rdi
	call	_ZdlPv
	movq	$0, (%rsp)
.L545:
	xorl	%r14d, %r14d
.L555:
	xorl	%ebp, %ebp
	.p2align 4,,10
	.p2align 3
.L552:
	movq	24(%rsp), %rax
	movq	(%rsp), %rbx
	movq	8(%rsp), %r12
	movq	(%rax), %rax
	movq	%r12, %rdi
	movq	(%rax,%rbp), %rdx
	movq	16(%rsp), %rax
	movq	(%rax), %rax
	addq	%r14, %rdx
	movq	(%rax,%rbx), %rsi
	addq	%rbp, %rsi
.LEHB67:
	call	_Z26multiply_matrices_manuallyRSt6vectorIS_IdSaIdEESaIS1_EES4_
.LEHE67:
	movq	(%r15), %rax
	movq	%r12, %rsi
	movq	(%rax,%rbx), %rcx
	addq	%r14, %rcx
	movq	%rcx, %rdi
	call	_Z18sum_small_matricesRSt6vectorIS_IdSaIdEESaIS1_EERKS3_
	movq	112(%rsp), %r12
	movq	120(%rsp), %rbx
	movq	%r12, %r13
	cmpq	%r12, %rbx
	je	.L551
	.p2align 4,,10
	.p2align 3
.L547:
	movq	0(%r13), %rdi
	testq	%rdi, %rdi
	je	.L550
	call	_ZdlPv
.L550:
	addq	$24, %r13
	cmpq	%r13, %rbx
	jne	.L547
.L551:
	testq	%r12, %r12
	je	.L549
	movq	%r12, %rdi
	call	_ZdlPv
.L549:
	addq	$24, %rbp
	cmpq	$2400, %rbp
	jne	.L552
	addq	$24, %r14
	cmpq	$2400, %r14
	jne	.L555
	addq	$24, (%rsp)
	movq	(%rsp), %rax
	cmpq	$2400, %rax
	jne	.L545
	addq	$152, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 56
	movq	%r15, %rax
	popq	%rbx
	.cfi_def_cfa_offset 48
	popq	%rbp
	.cfi_def_cfa_offset 40
	popq	%r12
	.cfi_def_cfa_offset 32
	popq	%r13
	.cfi_def_cfa_offset 24
	popq	%r14
	.cfi_def_cfa_offset 16
	popq	%r15
	.cfi_def_cfa_offset 8
	ret
.L560:
	.cfi_restore_state
	movq	%rax, %rbx
	vzeroupper
	jmp	.L526
.L563:
	movq	%rax, %rbx
	jmp	.L556
.L567:
	movq	%rax, %rbx
	jmp	.L537
.L562:
	movq	%rax, %rbx
	leaq	112(%rsp), %rax
	movq	%rax, 8(%rsp)
	vzeroupper
	jmp	.L539
.L566:
	movq	%rax, %rdi
	jmp	.L529
.L561:
	movq	%rax, %rbx
	leaq	80(%rsp), %rax
	movq	%rax, (%rsp)
	vzeroupper
	jmp	.L533
.L564:
	movq	%rax, %rbx
	jmp	.L525
	.section	.gcc_except_table
	.align 4
.LLSDA9543:
	.byte	0xff
	.byte	0x3
	.uleb128 .LLSDATT9543-.LLSDATTD9543
.LLSDATTD9543:
	.byte	0x1
	.uleb128 .LLSDACSE9543-.LLSDACSB9543
.LLSDACSB9543:
	.uleb128 .LEHB60-.LFB9543
	.uleb128 .LEHE60-.LEHB60
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB61-.LFB9543
	.uleb128 .LEHE61-.LEHB61
	.uleb128 .L560-.LFB9543
	.uleb128 0
	.uleb128 .LEHB62-.LFB9543
	.uleb128 .LEHE62-.LEHB62
	.uleb128 .L564-.LFB9543
	.uleb128 0
	.uleb128 .LEHB63-.LFB9543
	.uleb128 .LEHE63-.LEHB63
	.uleb128 .L561-.LFB9543
	.uleb128 0
	.uleb128 .LEHB64-.LFB9543
	.uleb128 .LEHE64-.LEHB64
	.uleb128 .L566-.LFB9543
	.uleb128 0x1
	.uleb128 .LEHB65-.LFB9543
	.uleb128 .LEHE65-.LEHB65
	.uleb128 .L562-.LFB9543
	.uleb128 0
	.uleb128 .LEHB66-.LFB9543
	.uleb128 .LEHE66-.LEHB66
	.uleb128 .L567-.LFB9543
	.uleb128 0
	.uleb128 .LEHB67-.LFB9543
	.uleb128 .LEHE67-.LEHB67
	.uleb128 .L563-.LFB9543
	.uleb128 0
.LLSDACSE9543:
	.byte	0x1
	.byte	0
	.align 4
	.long	0

.LLSDATT9543:
	.text
	.cfi_endproc
	.section	.text.unlikely
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	.cfi_lsda 0x3,.LLSDAC9543
	.type	_Z18calculate_manuallyRSt6vectorIS_IS_IS_IdSaIdEESaIS1_EESaIS3_EESaIS5_EES8_.cold, @function
_Z18calculate_manuallyRSt6vectorIS_IS_IS_IdSaIdEESaIS1_EESaIS3_EESaIS5_EES8_.cold:
.LFSB9543:
.L537:
	.cfi_def_cfa_offset 208
	.cfi_offset 3, -56
	.cfi_offset 6, -48
	.cfi_offset 12, -40
	.cfi_offset 13, -32
	.cfi_offset 14, -24
	.cfi_offset 15, -16
	movq	(%r15), %rdi
	testq	%rdi, %rdi
	je	.L593
	vzeroupper
	call	_ZdlPv
.L539:
	movq	8(%rsp), %rdi
	call	_ZNSt6vectorIS_IS_IdSaIdEESaIS1_EESaIS3_EED1Ev
.L533:
	movq	(%rsp), %rdi
	call	_ZNSt6vectorIS_IdSaIdEESaIS1_EED1Ev
.L526:
	movq	%r12, %rdi
	call	_ZdlPv
	movq	%rbx, %rdi
.LEHB68:
	call	_Unwind_Resume
.L556:
	movq	%r15, %rdi
	vzeroupper
	call	_ZNSt6vectorIS_IS_IS_IdSaIdEESaIS1_EESaIS3_EESaIS5_EED1Ev
	movq	%rbx, %rdi
	call	_Unwind_Resume
.LEHE68:
.L529:
	vzeroupper
	call	__cxa_begin_catch
	movq	%rbx, %r13
.L530:
	cmpq	%rbp, %r13
	je	.L595
	movq	%r13, %rdi
	addq	$24, %r13
	call	_ZNSt6vectorIS_IdSaIdEESaIS1_EED1Ev
	jmp	.L530
.L593:
	vzeroupper
	jmp	.L539
.L525:
	movq	%r13, %rdi
	vzeroupper
	call	_ZdlPv
	jmp	.L526
.L595:
.LEHB69:
	call	__cxa_rethrow
.LEHE69:
.L565:
	movq	%rax, %rbp
	vzeroupper
	call	__cxa_end_catch
	movq	%rbx, %rdi
	movq	%rbp, %rbx
	call	_ZdlPv
	jmp	.L533
	.cfi_endproc
.LFE9543:
	.section	.gcc_except_table
	.align 4
.LLSDAC9543:
	.byte	0xff
	.byte	0x3
	.uleb128 .LLSDATTC9543-.LLSDATTDC9543
.LLSDATTDC9543:
	.byte	0x1
	.uleb128 .LLSDACSEC9543-.LLSDACSBC9543
.LLSDACSBC9543:
	.uleb128 .LEHB68-.LCOLDB23
	.uleb128 .LEHE68-.LEHB68
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB69-.LCOLDB23
	.uleb128 .LEHE69-.LEHB69
	.uleb128 .L565-.LCOLDB23
	.uleb128 0
.LLSDACSEC9543:
	.byte	0x1
	.byte	0
	.align 4
	.long	0

.LLSDATTC9543:
	.section	.text.unlikely
	.text
	.size	_Z18calculate_manuallyRSt6vectorIS_IS_IS_IdSaIdEESaIS1_EESaIS3_EESaIS5_EES8_, .-_Z18calculate_manuallyRSt6vectorIS_IS_IS_IdSaIdEESaIS1_EESaIS3_EESaIS5_EES8_
	.section	.text.unlikely
	.size	_Z18calculate_manuallyRSt6vectorIS_IS_IS_IdSaIdEESaIS1_EESaIS3_EESaIS5_EES8_.cold, .-_Z18calculate_manuallyRSt6vectorIS_IS_IS_IdSaIdEESaIS1_EESaIS3_EESaIS5_EES8_.cold
.LCOLDE23:
	.text
.LHOTE23:
	.section	.rodata.str1.1
.LC24:
	.string	"With AVX took me "
.LC25:
	.string	" milliseconds."
.LC26:
	.string	"Without AVX took me "
.LC27:
	.string	"With manually AVX took me "
	.section	.text.unlikely
.LCOLDB28:
	.section	.text.startup,"ax",@progbits
.LHOTB28:
	.p2align 4
	.globl	main
	.type	main, @function
main:
.LFB9545:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	.cfi_lsda 0x3,.LLSDA9545
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movl	$10, %esi
	pushq	%rbx
	.cfi_def_cfa_offset 24
	.cfi_offset 3, -24
	subq	$184, %rsp
	.cfi_def_cfa_offset 208
	leaq	14(%rsp), %rdx
	leaq	80(%rsp), %rdi
.LEHB70:
	call	_ZNSt6vectorIdSaIdEEC1EmRKS0_
.LEHE70:
	leaq	15(%rsp), %rcx
	leaq	80(%rsp), %rdx
	movl	$10, %esi
	leaq	112(%rsp), %rdi
.LEHB71:
	call	_ZNSt6vectorIS_IdSaIdEESaIS1_EEC1EmRKS1_RKS2_
.LEHE71:
	leaq	48(%rsp), %rcx
	leaq	112(%rsp), %rdx
	movl	$100, %esi
	leaq	144(%rsp), %rdi
.LEHB72:
	call	_ZNSt6vectorIS_IS_IdSaIdEESaIS1_EESaIS3_EEC1EmRKS3_RKS4_
.LEHE72:
	vpxor	%xmm0, %xmm0, %xmm0
	movl	$2400, %edi
	vmovdqu	%xmm0, 24(%rsp)
.LEHB73:
	call	_Znwm
.LEHE73:
	movq	%rax, %rbx
	movq	%rax, 16(%rsp)
	movl	$100, %esi
	leaq	2400(%rax), %rax
	leaq	144(%rsp), %rdx
	movq	%rbx, %rdi
	movq	%rax, 32(%rsp)
.LEHB74:
	call	_ZSt18__do_uninit_fill_nIPSt6vectorIS0_IS0_IdSaIdEESaIS2_EESaIS4_EEmS6_ET_S8_T0_RKT1_
.LEHE74:
	leaq	144(%rsp), %rdi
	movq	%rax, 24(%rsp)
	call	_ZNSt6vectorIS_IS_IdSaIdEESaIS1_EESaIS3_EED1Ev
	leaq	112(%rsp), %rdi
	call	_ZNSt6vectorIS_IdSaIdEESaIS1_EED1Ev
	movq	80(%rsp), %rdi
	testq	%rdi, %rdi
	je	.L598
	call	_ZdlPv
.L598:
	leaq	13(%rsp), %rdx
	movl	$10, %esi
	leaq	80(%rsp), %rdi
.LEHB75:
	call	_ZNSt6vectorIdSaIdEEC1EmRKS0_
.LEHE75:
	leaq	14(%rsp), %rcx
	leaq	80(%rsp), %rdx
	movl	$10, %esi
	leaq	112(%rsp), %rdi
.LEHB76:
	call	_ZNSt6vectorIS_IdSaIdEESaIS1_EEC1EmRKS1_RKS2_
.LEHE76:
	leaq	15(%rsp), %rcx
	leaq	112(%rsp), %rdx
	movl	$100, %esi
	leaq	144(%rsp), %rdi
.LEHB77:
	call	_ZNSt6vectorIS_IS_IdSaIdEESaIS1_EESaIS3_EEC1EmRKS3_RKS4_
.LEHE77:
	vpxor	%xmm0, %xmm0, %xmm0
	movl	$2400, %edi
	vmovdqu	%xmm0, 56(%rsp)
.LEHB78:
	call	_Znwm
.LEHE78:
	movq	%rax, %rbx
	movq	%rax, 48(%rsp)
	movl	$100, %esi
	leaq	2400(%rax), %rax
	leaq	144(%rsp), %rdx
	movq	%rbx, %rdi
	movq	%rax, 64(%rsp)
.LEHB79:
	call	_ZSt18__do_uninit_fill_nIPSt6vectorIS0_IS0_IdSaIdEESaIS2_EESaIS4_EEmS6_ET_S8_T0_RKT1_
.LEHE79:
	leaq	144(%rsp), %rdi
	movq	%rax, 56(%rsp)
	call	_ZNSt6vectorIS_IS_IdSaIdEESaIS1_EESaIS3_EED1Ev
	leaq	112(%rsp), %rdi
	call	_ZNSt6vectorIS_IdSaIdEESaIS1_EED1Ev
	movq	80(%rsp), %rdi
	testq	%rdi, %rdi
	je	.L602
	call	_ZdlPv
.L602:
	leaq	16(%rsp), %rbp
	movq	%rbp, %rdi
.LEHB80:
	call	_Z20randomize_one_matrixRSt6vectorIS_IS_IS_IdSaIdEESaIS1_EESaIS3_EESaIS5_EE
	leaq	48(%rsp), %rdi
	call	_Z20randomize_one_matrixRSt6vectorIS_IS_IS_IdSaIdEESaIS1_EESaIS3_EESaIS5_EE
	call	_ZNSt6chrono3_V212steady_clock3nowEv
	leaq	48(%rsp), %rdx
	movq	%rbp, %rsi
	leaq	80(%rsp), %rdi
	movq	%rax, %rbx
	call	_Z13calculate_avxRSt6vectorIS_IS_IS_IdSaIdEESaIS1_EESaIS3_EESaIS5_EES8_
.LEHE80:
	call	_ZNSt6chrono3_V212steady_clock3nowEv
	movl	$.LC24, %esi
	movl	$_ZSt4cout, %edi
	movabsq	$4835703278458516699, %rdx
	subq	%rbx, %rax
	movq	%rax, %rcx
	imulq	%rdx
	sarq	$63, %rcx
	sarq	$18, %rdx
	movq	%rdx, %rbx
	subq	%rcx, %rbx
.LEHB81:
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
	movq	%rax, %rdi
	movq	%rbx, %rsi
	call	_ZNSo9_M_insertIlEERSoT_
	movq	%rax, %rdi
	movl	$.LC25, %esi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
	movq	%rax, %rdi
	call	_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_.isra.0
	call	_ZNSt6chrono3_V212steady_clock3nowEv
	leaq	48(%rsp), %rdx
	movq	%rbp, %rsi
	leaq	112(%rsp), %rdi
	movq	%rax, %rbx
	call	_Z9calculateRSt6vectorIS_IS_IS_IdSaIdEESaIS1_EESaIS3_EESaIS5_EES8_
.LEHE81:
	call	_ZNSt6chrono3_V212steady_clock3nowEv
	movl	$.LC26, %esi
	movl	$_ZSt4cout, %edi
	movabsq	$4835703278458516699, %rdx
	subq	%rbx, %rax
	movq	%rax, %rcx
	imulq	%rdx
	sarq	$63, %rcx
	sarq	$18, %rdx
	movq	%rdx, %rbx
	subq	%rcx, %rbx
.LEHB82:
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
	movq	%rax, %rdi
	movq	%rbx, %rsi
	call	_ZNSo9_M_insertIlEERSoT_
	movq	%rax, %rdi
	movl	$.LC25, %esi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
	movq	%rax, %rdi
	call	_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_.isra.0
	leaq	80(%rsp), %rsi
	leaq	112(%rsp), %rdi
	call	_Z7compareRSt6vectorIS_IS_IS_IdSaIdEESaIS1_EESaIS3_EESaIS5_EES8_
	call	_ZNSt6chrono3_V212steady_clock3nowEv
	leaq	48(%rsp), %rdx
	movq	%rbp, %rsi
	leaq	144(%rsp), %rdi
	movq	%rax, %rbx
	call	_Z18calculate_manuallyRSt6vectorIS_IS_IS_IdSaIdEESaIS1_EESaIS3_EESaIS5_EES8_
.LEHE82:
	call	_ZNSt6chrono3_V212steady_clock3nowEv
	movl	$.LC27, %esi
	movl	$_ZSt4cout, %edi
	movabsq	$4835703278458516699, %rdx
	subq	%rbx, %rax
	movq	%rax, %rcx
	imulq	%rdx
	sarq	$63, %rcx
	sarq	$18, %rdx
	movq	%rdx, %rbx
	subq	%rcx, %rbx
.LEHB83:
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
	movq	%rax, %rdi
	movq	%rbx, %rsi
	call	_ZNSo9_M_insertIlEERSoT_
	movq	%rax, %rdi
	movl	$.LC25, %esi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
	movq	%rax, %rdi
	call	_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_.isra.0
	leaq	144(%rsp), %rsi
	leaq	80(%rsp), %rdi
	call	_Z7compareRSt6vectorIS_IS_IS_IdSaIdEESaIS1_EESaIS3_EESaIS5_EES8_
.LEHE83:
	leaq	144(%rsp), %rdi
	call	_ZNSt6vectorIS_IS_IS_IdSaIdEESaIS1_EESaIS3_EESaIS5_EED1Ev
	leaq	112(%rsp), %rdi
	call	_ZNSt6vectorIS_IS_IS_IdSaIdEESaIS1_EESaIS3_EESaIS5_EED1Ev
	leaq	80(%rsp), %rdi
	call	_ZNSt6vectorIS_IS_IS_IdSaIdEESaIS1_EESaIS3_EESaIS5_EED1Ev
	leaq	48(%rsp), %rdi
	call	_ZNSt6vectorIS_IS_IS_IdSaIdEESaIS1_EESaIS3_EESaIS5_EED1Ev
	movq	%rbp, %rdi
	call	_ZNSt6vectorIS_IS_IS_IdSaIdEESaIS1_EESaIS3_EESaIS5_EED1Ev
	addq	$184, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 24
	xorl	%eax, %eax
	popq	%rbx
	.cfi_def_cfa_offset 16
	popq	%rbp
	.cfi_def_cfa_offset 8
	ret
.L628:
	.cfi_restore_state
	movq	%rax, %rbp
	jmp	.L603
.L617:
	movq	%rax, %rbx
	vzeroupper
	jmp	.L605
.L626:
	movq	%rax, %rbx
	jmp	.L612
.L616:
	movq	%rax, %rbx
	vzeroupper
	jmp	.L606
.L625:
	movq	%rax, %rbx
	vzeroupper
	jmp	.L613
.L627:
	movq	%rax, %rbp
	jmp	.L599
.L618:
	movq	%rax, %rbx
	vzeroupper
	jmp	.L600
.L624:
	movq	%rax, %rbx
	vzeroupper
	jmp	.L614
.L623:
	movq	%rax, %rbx
	vzeroupper
	jmp	.L615
.L621:
	movq	%rax, %rbx
	vzeroupper
	jmp	.L604
.L620:
	movq	%rax, %rbx
	vzeroupper
	jmp	.L608
.L619:
	movq	%rax, %rbx
	vzeroupper
	jmp	.L609
.L622:
	movq	%rax, %rbx
	leaq	16(%rsp), %rbp
	vzeroupper
	jmp	.L611
	.section	.gcc_except_table
.LLSDA9545:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE9545-.LLSDACSB9545
.LLSDACSB9545:
	.uleb128 .LEHB70-.LFB9545
	.uleb128 .LEHE70-.LEHB70
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB71-.LFB9545
	.uleb128 .LEHE71-.LEHB71
	.uleb128 .L616-.LFB9545
	.uleb128 0
	.uleb128 .LEHB72-.LFB9545
	.uleb128 .LEHE72-.LEHB72
	.uleb128 .L617-.LFB9545
	.uleb128 0
	.uleb128 .LEHB73-.LFB9545
	.uleb128 .LEHE73-.LEHB73
	.uleb128 .L618-.LFB9545
	.uleb128 0
	.uleb128 .LEHB74-.LFB9545
	.uleb128 .LEHE74-.LEHB74
	.uleb128 .L627-.LFB9545
	.uleb128 0
	.uleb128 .LEHB75-.LFB9545
	.uleb128 .LEHE75-.LEHB75
	.uleb128 .L622-.LFB9545
	.uleb128 0
	.uleb128 .LEHB76-.LFB9545
	.uleb128 .LEHE76-.LEHB76
	.uleb128 .L619-.LFB9545
	.uleb128 0
	.uleb128 .LEHB77-.LFB9545
	.uleb128 .LEHE77-.LEHB77
	.uleb128 .L620-.LFB9545
	.uleb128 0
	.uleb128 .LEHB78-.LFB9545
	.uleb128 .LEHE78-.LEHB78
	.uleb128 .L621-.LFB9545
	.uleb128 0
	.uleb128 .LEHB79-.LFB9545
	.uleb128 .LEHE79-.LEHB79
	.uleb128 .L628-.LFB9545
	.uleb128 0
	.uleb128 .LEHB80-.LFB9545
	.uleb128 .LEHE80-.LEHB80
	.uleb128 .L623-.LFB9545
	.uleb128 0
	.uleb128 .LEHB81-.LFB9545
	.uleb128 .LEHE81-.LEHB81
	.uleb128 .L624-.LFB9545
	.uleb128 0
	.uleb128 .LEHB82-.LFB9545
	.uleb128 .LEHE82-.LEHB82
	.uleb128 .L625-.LFB9545
	.uleb128 0
	.uleb128 .LEHB83-.LFB9545
	.uleb128 .LEHE83-.LEHB83
	.uleb128 .L626-.LFB9545
	.uleb128 0
.LLSDACSE9545:
	.section	.text.startup
	.cfi_endproc
	.section	.text.unlikely
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	.cfi_lsda 0x3,.LLSDAC9545
	.type	main.cold, @function
main.cold:
.LFSB9545:
.L603:
	.cfi_def_cfa_offset 208
	.cfi_offset 3, -24
	.cfi_offset 6, -16
	movq	%rbx, %rdi
	vzeroupper
	movq	%rbp, %rbx
	call	_ZdlPv
.L604:
	leaq	144(%rsp), %rdi
	call	_ZNSt6vectorIS_IS_IdSaIdEESaIS1_EESaIS3_EED1Ev
.L608:
	leaq	112(%rsp), %rdi
	call	_ZNSt6vectorIS_IdSaIdEESaIS1_EED1Ev
.L609:
	movq	80(%rsp), %rdi
	testq	%rdi, %rdi
	je	.L610
	call	_ZdlPv
.L610:
	leaq	16(%rsp), %rbp
	jmp	.L611
.L599:
	movq	%rbx, %rdi
	vzeroupper
	movq	%rbp, %rbx
	call	_ZdlPv
.L600:
	leaq	144(%rsp), %rdi
	call	_ZNSt6vectorIS_IS_IdSaIdEESaIS1_EESaIS3_EED1Ev
.L605:
	leaq	112(%rsp), %rdi
	call	_ZNSt6vectorIS_IdSaIdEESaIS1_EED1Ev
.L606:
	movq	80(%rsp), %rdi
	testq	%rdi, %rdi
	je	.L607
	call	_ZdlPv
.L607:
	movq	%rbx, %rdi
.LEHB84:
	call	_Unwind_Resume
.L612:
	leaq	144(%rsp), %rdi
	vzeroupper
	call	_ZNSt6vectorIS_IS_IS_IdSaIdEESaIS1_EESaIS3_EESaIS5_EED1Ev
.L613:
	leaq	112(%rsp), %rdi
	call	_ZNSt6vectorIS_IS_IS_IdSaIdEESaIS1_EESaIS3_EESaIS5_EED1Ev
.L614:
	leaq	80(%rsp), %rdi
	call	_ZNSt6vectorIS_IS_IS_IdSaIdEESaIS1_EESaIS3_EESaIS5_EED1Ev
.L615:
	leaq	48(%rsp), %rdi
	call	_ZNSt6vectorIS_IS_IS_IdSaIdEESaIS1_EESaIS3_EESaIS5_EED1Ev
.L611:
	movq	%rbp, %rdi
	call	_ZNSt6vectorIS_IS_IS_IdSaIdEESaIS1_EESaIS3_EESaIS5_EED1Ev
	movq	%rbx, %rdi
	call	_Unwind_Resume
.LEHE84:
	.cfi_endproc
.LFE9545:
	.section	.gcc_except_table
.LLSDAC9545:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSEC9545-.LLSDACSBC9545
.LLSDACSBC9545:
	.uleb128 .LEHB84-.LCOLDB28
	.uleb128 .LEHE84-.LEHB84
	.uleb128 0
	.uleb128 0
.LLSDACSEC9545:
	.section	.text.unlikely
	.section	.text.startup
	.size	main, .-main
	.section	.text.unlikely
	.size	main.cold, .-main.cold
.LCOLDE28:
	.section	.text.startup
.LHOTE28:
	.p2align 4
	.type	_GLOBAL__sub_I__Z20randomize_one_matrixRSt6vectorIS_IS_IS_IdSaIdEESaIS1_EESaIS3_EESaIS5_EE, @function
_GLOBAL__sub_I__Z20randomize_one_matrixRSt6vectorIS_IS_IS_IdSaIdEESaIS1_EESaIS3_EESaIS5_EE:
.LFB10379:
	.cfi_startproc
	subq	$8, %rsp
	.cfi_def_cfa_offset 16
	movl	$_ZStL8__ioinit, %edi
	call	_ZNSt8ios_base4InitC1Ev
	movl	$__dso_handle, %edx
	movl	$_ZStL8__ioinit, %esi
	movl	$_ZNSt8ios_base4InitD1Ev, %edi
	addq	$8, %rsp
	.cfi_def_cfa_offset 8
	jmp	__cxa_atexit
	.cfi_endproc
.LFE10379:
	.size	_GLOBAL__sub_I__Z20randomize_one_matrixRSt6vectorIS_IS_IS_IdSaIdEESaIS1_EESaIS3_EESaIS5_EE, .-_GLOBAL__sub_I__Z20randomize_one_matrixRSt6vectorIS_IS_IS_IdSaIdEESaIS1_EESaIS3_EESaIS5_EE
	.section	.init_array,"aw"
	.align 8
	.quad	_GLOBAL__sub_I__Z20randomize_one_matrixRSt6vectorIS_IS_IS_IdSaIdEESaIS1_EESaIS3_EESaIS5_EE
	.local	_ZStL8__ioinit
	.comm	_ZStL8__ioinit,1,1
	.section	.rodata.cst16,"aM",@progbits,16
	.align 16
.LC0:
	.long	-1
	.long	2147483647
	.long	0
	.long	0
	.section	.rodata.cst8,"aM",@progbits,8
	.align 8
.LC1:
	.long	1202590843
	.long	1065646817
	.align 8
.LC12:
	.long	0
	.long	1072693248
	.align 8
.LC13:
	.long	-1
	.long	1072693247
	.section	.rodata.cst4,"aM",@progbits,4
	.align 4
.LC14:
	.long	1333788672
	.hidden	__dso_handle
	.ident	"GCC: (GNU) 12.2.1 20221121 (Red Hat 12.2.1-4)"
	.section	.note.GNU-stack,"",@progbits
