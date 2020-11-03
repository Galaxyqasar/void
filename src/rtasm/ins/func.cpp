#include "ins/func.hpp"

namespace rtasm {
	void Func::call(Label &pos) {
		emit(0xe8, pos);
	}
	void Func::call(reg64 addr) {}
	void Func::ret(imm16 ds) {
		if(ds > 0) {
			emit(0xc2, ds);
		}
		else {
			emit(0xc3);
		}
	}
}