#pragma once

namespace rtasm {
	enum class reg8 {
		al, cl, dl, bl, ah, ch, dh, bh,
		spl = ah, bpl, sil, dil,
		r8b, r9b, r10b, r11b,
		r12b, r13b, r14b, r15b
	};

	enum class reg16 {
		ax, cx, dx, bx,
		sp, bp, si, di,
		r8w, r9w, r10w, r11w,
		r12w, r13w, r14w, r15w
	};

	enum class reg32 {
		eax, ecx, edx, ebx,
		esp, ebp, esi, edi,
		r8d, r9d, r10d, r11d,
		r12d, r13d, r14d, r15d
	};

	enum class reg64 {
		rax, rcx, rdx, rbx,
		rsp, rbp, rsi, rdi,
		r8, r9, r10, r11,
		r12, r13, r14, r15
	};
}